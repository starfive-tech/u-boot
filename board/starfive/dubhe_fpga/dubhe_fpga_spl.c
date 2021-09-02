// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#include <spl.h>

int spl_board_init_f(void)
{
	return 0;
}

void board_boot_order(u32 *spl_boot_list)
{
	spl_boot_list[0] = BOOT_DEVICE_SPI;
}

int board_fit_config_name_match(const char *name)
{
	return 0;
}
