// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018, Bin Meng <bmeng.cn@gmail.com>
 */
#include <common.h>
#include <fdtdec.h>
#include <init.h>
#include <linux/sizes.h>

#ifdef CONFIG_ID_EEPROM
#include <asm/arch/eeprom.h>
#define STARFIVE_JH7110_EEPROM_DDRINFO_OFFSET	91
#endif

DECLARE_GLOBAL_DATA_PTR;

#ifdef CONFIG_ID_EEPROM
static bool check_eeprom_dram_info(phys_size_t size)
{
	switch (size) {
	case 0x40000000:
	case 0x80000000:
	case 0x100000000:
	case 0x200000000:
	case 0x400000000:
		return true;
	default:
		return false;
	}
}

static void resize_ddr_from_eeprom(void)
{
	u32 offset = STARFIVE_JH7110_EEPROM_DDRINFO_OFFSET;
	phys_size_t size;
	u32 len = 1;
	u8 data = 0;
	int ret;

	/* read memory size info */
	ret = get_data_from_eeprom(offset, len, &data);
	if (ret == len) {
		size = ((phys_size_t)hextoul(&data, NULL)) << 30;
		if (check_eeprom_dram_info(size))
			gd->ram_size = size;
	}

}
#endif /* CONFIG_ID_EEPROM */

int dram_init(void)
{
	int ret;

	ret = fdtdec_setup_mem_size_base();
	if (ret)
	return ret;

#ifdef CONFIG_ID_EEPROM
	resize_ddr_from_eeprom();
#endif
	return 0;
}

int dram_init_banksize(void)
{
	int ret;

	ret = fdtdec_setup_memory_banksize();
	if (ret)
		return ret;

	gd->bd->bi_dram[0].size = gd->ram_size;

	return 0;
}

ulong board_get_usable_ram_top(ulong total_size)
{
#ifdef CONFIG_64BIT
	/*
	 * Ensure that we run from first 4GB so that all
	 * addresses used by U-Boot are 32bit addresses.
	 *
	 * This in-turn ensures that 32bit DMA capable
	 * devices work fine because DMA mapping APIs will
	 * provide 32bit DMA addresses only.
	 */
	if (gd->ram_top > SZ_4G)
		return SZ_4G;
#endif
	return gd->ram_top;
}
