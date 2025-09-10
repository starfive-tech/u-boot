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

#include <asm/arch/boot_env.h>
#include <asm/arch/boot_fdt.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/boot_mapping.h>
#include <asm/arch/starfive_reset.h>
#include <asm/arch/bootcmd_restore.h>
#include <dm/ofnode.h>
#include <env.h>
#include <env_internal.h>
#include <init.h>
#include <linux/delay.h>
#include <spl.h>

static int env_changed_id;

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

int ft_board_setup(void *blob, struct bd_info *bd)
{
	jhb100_fdt_fixup(blob);

	return 0;
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

	sbnode1 = ofnode_find_subnode(sbnode0, "partition@6");
	if (!ofnode_valid(sbnode1))
		return log_msg_ret("Cannot find kernel primary node", -EPERM);

	env_set("kernel_fit_spi_prim_off", "0x690000");
	if (!ofnode_read_u32_array(sbnode1, "reg", reg, 2))
		env_set_hex("kernel_fit_spi_prim_off", (ulong)reg[0]);

	sbnode1 = ofnode_find_subnode(sbnode0, "partition@7");
	if (!ofnode_valid(sbnode1))
		return log_msg_ret("Cannot find kernel secondary node", -EPERM);

	env_set("kernel_fit_spi_sec_off", "0x1690000");
	if (!ofnode_read_u32_array(sbnode1, "reg", reg, 2))
		env_set_hex("kernel_fit_spi_sec_off", (ulong)reg[0]);

	return 0;
}

void env_add_bootarg_reset_event(void)
{
	env_filter_add_bootarg(starfive_get_reset_event, "reset_event=", NULL);
	env_changed_id = env_get_id();
}

/* We do critical boot command restoration here in the case user save
 * and then load their custom environment from persistent storages.
 * This will not override any additional custom environments added by user,
 * instead append critical boot command on top of it.
 * However, this overrides critical boot command if added by user.
 */
void env_restore_bootcmd(void)
{
	restore_bootcmd_utils();

	if (IS_ENABLED(CONFIG_ENV_IS_IN_SPI_FLASH))
		restore_bootcmd_sfc();
	if (IS_ENABLED(CONFIG_ENV_IS_IN_FAT))
		restore_bootcmd_emmc();

	env_changed_id = env_get_id();
}

void uboot_starfive_fb_rec_map_handler(void)
{
	int boot_mode = GET_BOOT_SRC;
	int fb_map_reg = starfive_get_fb_rec_map();

	switch (boot_mode) {
	case BOOT_SRC_SFC:
		starfive_fb_rec_map_handler(&fb_map_reg,
					    BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
					    BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
					    FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					    CLEAR);
		break;
	case BOOT_SRC_EMMC:
		starfive_fb_rec_map_handler(&fb_map_reg,
					    BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
					    BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
					    FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					    CLEAR);
		break;
	case BOOT_SRC_UFS:
		starfive_fb_rec_map_handler(&fb_map_reg,
					    BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
					    BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
					    FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					    CLEAR);
		break;
	default:
		return;
	}

	starfive_set_fb_rec_map(fb_map_reg);
}

int board_late_init(void)
{
	env_get_boot_dev();
	env_get_spi_flash_offs();
	env_restore_bootcmd();
	/* Add or replace reset_event argument to bootargs */
	env_add_bootarg_reset_event();

	uboot_starfive_fb_rec_map_handler();

	return 0;
}

#ifndef CONFIG_SPL_BUILD
static int last_stage_init(void)
{
	int env_id = env_get_id();

	/* Update only when the environment has changed */
	if (env_changed_id != env_id) {
		env_changed_id = env_id;
		env_save();
	}

	starfive_clear_ap_sts_retry_cnt(BOOTSTG_U_BOOT_SPL);
	starfive_clear_ap_sts_retry_cnt(BOOTSTG_U_BOOT_PROPER);
	starfive_clear_ap_sts_error(BOOTSTG_U_BOOT_SPL);
	starfive_clear_ap_sts_error(BOOTSTG_U_BOOT_PROPER);

	return 0;
}
EVENT_SPY_SIMPLE(EVT_LAST_STAGE_INIT, last_stage_init);
#endif

#endif
