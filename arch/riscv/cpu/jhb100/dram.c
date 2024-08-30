// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2023 StarFive Technology Co., Ltd.
 */

#include <common.h>
#include <fdtdec.h>
#include <init.h>
#include <linux/sizes.h>

DECLARE_GLOBAL_DATA_PTR;

int dram_init(void)
{
	return fdtdec_setup_mem_size_base();
}

int dram_init_banksize(void)
{
	return fdtdec_setup_memory_banksize();
}

phys_size_t board_get_usable_ram_top(phys_size_t total_size)
{
	return gd->ram_top;
}
