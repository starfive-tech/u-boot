/* SPDX-License-Identifier: GPL-2.0+ */
/**
  ******************************************************************************
  * @file  jhb100.c
  * @author  StarFive Technology
  * @version  V1.0
  * @date  25/04/2024
  * @brief
  ******************************************************************************
  * @copy
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 2024 Shanghai StarFive Technology Co., Ltd.
  */

#include <asm/arch/boot_src.h>
#include <dm/ofnode.h>
#include <env.h>
#include <env_internal.h>
#include <init.h>
#include <linux/delay.h>
#include <spl.h>

int board_init(void)
{
	/* Required to perform early initialization
	*  in order to start watchdog successfully
	*/
	arch_early_init_r();

	return 0;
}

enum env_location env_get_location(enum env_operation op, int prio)
{
	int boot_mode = GET_BOOT_SRC;

	if (prio) {
		debug("Could not find persistent storage\n");
		return ENVL_UNKNOWN;
	}

	switch (boot_mode) {
	case BOOT_SRC_SFC:
		debug("Boot source: SPI flash\n");
		if (IS_ENABLED(CONFIG_ENV_IS_IN_SPI_FLASH))
			return ENVL_SPI_FLASH;
		break;
	case BOOT_SRC_EMMC:
		debug("Boot source: eMMC\n");
		if (IS_ENABLED(CONFIG_ENV_IS_IN_FAT))
			return ENVL_FAT;
		if (IS_ENABLED(CONFIG_ENV_IS_IN_MMC))
			return ENVL_MMC;
		break;
	case BOOT_SRC_UFS:
		debug("Boot source: UFS\n");
		if (IS_ENABLED(CONFIG_ENV_IS_IN_FAT))
			return ENVL_FAT;
		if (IS_ENABLED(CONFIG_ENV_IS_IN_MMC))
			return ENVL_MMC;
		break;
	default:
		printf("Could not find persistent storage for environment\n");
		break;
	}

	/* Define this based on priority of the persistent storage to choose, for now
	 * we choose SPI flash > MMC > FAT
	 */
	if (IS_ENABLED(CONFIG_ENV_IS_IN_SPI_FLASH))
		return ENVL_SPI_FLASH;
	if (IS_ENABLED(CONFIG_ENV_IS_IN_FAT))
		return ENVL_FAT;
	if (IS_ENABLED(CONFIG_ENV_IS_IN_MMC))
		return ENVL_MMC;

	/* If CONFIG_ENV_IS_NOWHERE is enabled and no other config is enabled,
	 * this function falls back to here
	 */
	return ENVL_NOWHERE;
}

#ifdef CONFIG_BOARD_LATE_INIT
static void env_get_boot_dev(void)
{
	switch (jhb100_get_boot_device()) {
	case BOOT_DEVICE_SPI:
		env_set("bootdev", "spi");
		break;
	case BOOT_DEVICE_MMC1:
		env_set("mmcdev", "0");
		env_set("bootdev", "mmc1");
		break;
	case BOOT_DEVICE_UART:
		env_set("bootdev", "uart");
		break;
	case BOOT_DEVICE_RAM:
		env_set("bootdev", "ram");
		break;
	default:
		env_set("bootdev", "uart");
		break;
	}
}

static int env_get_spi_flash_offs(void)
{
	ofnode node, sbnode0, sbnode1;
	u32 reg[2];

	/* Find flash 0 if available */
	node = ofnode_by_compatible(ofnode_null(), "jedec,spi-nor");
	if (!ofnode_valid(node))
		return log_msg_ret("Cannot find SPI flash 0\n", -ENOENT);

	/* Find flash 1 if available */
	node = ofnode_by_compatible(node, "jedec,spi-nor");
	if (!ofnode_valid(node))
		return log_msg_ret("Cannot find SPI flash 1\n", -ENOENT);

	sbnode0 = ofnode_find_subnode(node, "partitions");
	if (!ofnode_valid(sbnode0))
		return log_msg_ret("Cannot find partition node", -EPERM);

	sbnode1 = ofnode_find_subnode(sbnode0, "partition@0");
	if (!ofnode_valid(sbnode1))
		return log_msg_ret("Cannot find kernel primary node", -EPERM);

	env_set("kernel_fit_spi_prim_off", "0x0");
	if (!ofnode_read_u32_array(sbnode1, "reg", reg, 2))
		env_set_hex("kernel_fit_spi_prim_off", (ulong)reg[0]);

	sbnode1 = ofnode_find_subnode(sbnode0, "partition@1");
	if (!ofnode_valid(sbnode1))
		return log_msg_ret("Cannot find kernel secondary node", -EPERM);

	env_set("kernel_fit_spi_sec_off", "0xd00000");
	if (!ofnode_read_u32_array(sbnode1, "reg", reg, 2))
		env_set_hex("kernel_fit_spi_sec_off", (ulong)reg[0]);

	return 0;
}

int board_late_init(void)
{
	env_get_boot_dev();
	env_get_spi_flash_offs();
	return 0;
}
#endif
