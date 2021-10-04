// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#include <dm.h>
#include <spl.h>

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
	return 0;
}
