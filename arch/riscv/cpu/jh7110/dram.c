// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018, Bin Meng <bmeng.cn@gmail.com>
 */

#include <common.h>
#include <asm/arch/eeprom.h>
#include <fdtdec.h>
#include <init.h>
#include <linux/sizes.h>

DECLARE_GLOBAL_DATA_PTR;

static bool check_eeprom_dram_info(phys_size_t size)
{
	switch (size) {
	case 0x80000000:
	case 0x100000000:
	case 0x200000000:
	case 0x400000000:
		return true;
	default:
		return false;
	}
}

int dram_init(void)
{
	int ret;
	u8 data;
	u32 len;
	u32 offset;
	phys_size_t size;

	data = 0;
	len = 1;
	offset = 91; /*offset of memory size stored in eeprom*/
	ret = fdtdec_setup_mem_size_base();
	if (ret)
		goto err;

	/*read memory size info*/
	ret = get_data_from_eeprom(offset, len, &data);
	if (ret == len) {
		size = ((phys_size_t)hextoul(&data, NULL)) << 30;
		if (check_eeprom_dram_info(size))
			gd->ram_size = size;
	}

	ret = 0;
err:
	return ret;
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
