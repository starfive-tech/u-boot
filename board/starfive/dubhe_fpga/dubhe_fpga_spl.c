// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#include <dm.h>
#include <spl.h>
#include <asm/csr.h>
#include <asm/arch-dubhe/csr.h>

extern void (*__riscv_expected_trap)(void);

#define mmio_read64_allowed(csr_mtvec, mmio_addr, cause)		\
	({								\
	register ulong cause_b asm("a3") = (ulong)cause;		\
	register ulong ttmp asm("a4");					\
	register ulong mtvec = (ulong)(&__riscv_expected_trap);		\
	register ulong addr = mmio_addr;				\
	register ulong ret = 0;						\
	*cause = 0;							\
	__asm__ __volatile__(						\
		"add %[ttmp], %[cause_b], zero\n"			\
		"csrrw %[mtvec], " __ASM_STR(csr_mtvec) ", %[mtvec]\n"	\
		"ld %[ret], 0(%[addr])\n"				\
		"csrw " __ASM_STR(csr_mtvec) ", %[mtvec]"		\
	    : [mtvec] "+&r"(mtvec), [cause_b] "+&r"(cause_b),		\
	      [ttmp] "+&r"(ttmp), [ret] "=&r" (ret)			\
	    : [addr] "r" (addr)						\
	    : "memory");						\
	ret;								\
	})

#define STARLINK_ID_ADDR	0x12900270
bool check_starlink(void)
{
	ulong cause, value;
	u8 rev_id, sub_rev_id;

	value = mmio_read64_allowed(CSR_MTVEC, STARLINK_ID_ADDR, &cause);
	if (cause) {
		printf("StarLink not supported\n");
		return false;
	}

	rev_id = value & 0x0f;
	sub_rev_id = (value >> 4) & 0x0f;

	printf("StarLink supported, Rev ID=%u.%u\n", rev_id, sub_rev_id);

	return true;
}

int spl_board_init_f(void)
{
	int ret;
	struct udevice *dev;

	/* Init DRAM */
	ret = uclass_get_device(UCLASS_RAM, 0, &dev);
	if (ret) {
		debug("DRAM init failed: %d\n", ret);
		return ret;
	}

	return 0;
}

void board_boot_order(u32 *spl_boot_list)
{
	spl_boot_list[0] = BOOT_DEVICE_SPI;
}

int board_fit_config_name_match(const char *name)
{
	char config_name[9];
	u32 marchid;

	marchid = csr_read(CSR_MARCHID);

	switch (marchid) {
	case DUBHE90_MARCHID:
		sprintf(config_name, "conf-%s", "90");
		return strcmp(name, config_name);

	case DUBHE80_MARCHID:
		sprintf(config_name, "conf-%s", "80");
		return strcmp(name, config_name);

	case DUBHE70_MARCHID:
		if (check_starlink())
			sprintf(config_name, "conf-%s", "70s");
		else
			sprintf(config_name, "conf-%s", "70a");
		return strcmp(name, config_name);

	default:
		return 0;
	}
}
