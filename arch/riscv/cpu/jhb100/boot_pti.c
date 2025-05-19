// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */

#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <linux/bitops.h>
#include <dm.h>
#include <log.h>
#include <spl.h>

int starfive_get_partition_num(int boot_src, int part_type, int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	// TODO: Get GPP partition based on partition type
	switch (boot_src) {
	case BOOT_SRC_SFC:
		break;
	case BOOT_SRC_EMMC:
		if (img_type == IMG_TYPE_UBOOT_PROPER) {
			return (part_type == PT_ACTIVE) ?
				EMMC_BOOT0_PART : EMMC_BOOT1_PART;
		} else if (img_type == IMG_TYPE_KERNEL) {
			return (part_type == PT_ACTIVE) ?
				EMMC_GPP1_PART : EMMC_GPP2_PART;
		}
		break;
	default:
		printf("Unknown boot source\n");
	}
	return 0;
}

int starfive_get_partition_offset(int boot_src, int part_type, int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	// TODO: Get raw offset from partition
	switch (boot_src) {
	case BOOT_SRC_SFC:
		if (img_type == IMG_TYPE_UBOOT_PROPER) {
			return (part_type == PT_ACTIVE) ?
				SFC_UBOOT_PROPER_ACTIVE_OFFS : SFC_UBOOT_PROPER_GOLDEN_OFFS;
		} else if (img_type == IMG_TYPE_KERNEL) {
			return (part_type == PT_ACTIVE) ?
				SFC_KERNEL_ACTIVE_OFFS : SFC_KERNEL_GOLDEN_OFFS;
		}
		break;
	case BOOT_SRC_EMMC:
		if (img_type == IMG_TYPE_UBOOT_PROPER) {
			return (part_type == PT_ACTIVE) ?
				(EMMC_UBOOT_PROPER_ACTIVE_OFFS / MMC_BLK_SIZE)
				 : (EMMC_UBOOT_PROPER_GOLDEN_OFFS / MMC_BLK_SIZE);
		} else if (img_type == IMG_TYPE_KERNEL) {
			return (part_type == PT_ACTIVE) ?
				(EMMC_KERNEL_ACTIVE_OFFS / MMC_BLK_SIZE)
				 : (EMMC_KERNEL_GOLDEN_OFFS / MMC_BLK_SIZE);
		}
		break;
	default:
		printf("Unknown boot source\n");
	}
	return 0;
}

void starfive_set_boot_ctrl_reg(int img_type)
{
	writel(img_type, (void *)BOOT_CTRL_REG_ADDR);
}

void starfive_set_boot_stat_reg(int boot_src, int part_type, int img_type)
{
	// TODO: Sync with FW
}
