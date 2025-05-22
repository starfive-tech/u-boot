/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_PTI_H
#define _BOOT_PTI_H

#include <linux/types.h>

/* Partition Type */
#define PT_ACTIVE	0
#define PT_GOLDEN	1
#define PT_TEMP		2

/* Image Type */
#define IMG_TYPE_UBOOT_SPL	0
#define IMG_TYPE_UBOOT_PROPER	1
#define IMG_TYPE_KERNEL		2

#define BOOT_CTRL_REG_ADDR		0x0013018018
#define SPL_BOOT_STAT_REG_ADDR		0x001301801C
#define UBOOT_PROP_BOOT_STAT_REG_ADDR	0x0013018020
#define KERNEL_BOOT_STAT_REG_ADDR	0x0013018024

#define EMMC_BOOT0_PART		1
#define EMMC_BOOT1_PART		2
#define EMMC_GPP1_PART		3
#define EMMC_GPP2_PART		4
#define EMMC_GPP3_PART		5
#define EMMC_GPP4_PART		6

#define SFC_UBOOT_PROPER_ACTIVE_OFFS	0x210000
#define SFC_UBOOT_PROPER_GOLDEN_OFFS	0x210000
#define SFC_KERNEL_ACTIVE_OFFS		0x690000
#define SFC_KERNEL_GOLDEN_OFFS		0x1690000

#define EMMC_UBOOT_PROPER_ACTIVE_OFFS	0x210000
#define EMMC_UBOOT_PROPER_GOLDEN_OFFS	0x210000
#define EMMC_KERNEL_ACTIVE_OFFS		0
#define EMMC_KERNEL_GOLDEN_OFFS		0

#define MMC_BLK_SIZE		512

struct boot_ctrl_reg {
	u32 boot_stage		: 2; /* Refer Image Type */
	u32 rsvd_0		: 28;
	u32 boot_golden		: 1;
	u32 boot_flag		: 1;
};

struct boot_stat_reg {
	u32 boot_src		: 2;
	u32 rsvd_0		: 2;
	u32 image_flg		: 3; /* Refer Partition Type */
	u32 rsvd_1		: 24;
	u32 error		: 1;
};

int starfive_get_partition_num(int boot_src, int part_type, int img_type);
int starfive_get_partition_offset(int boot_src, int part_type, int img_type);
int starfive_get_sfc_cs_line_num(void);
int starfive_req_img_auth_storage(int boot_src, int part_type, int img_type);
int starfive_req_img_auth_memory(int boot_src, int part_type, int img_type);
void starfive_pre_os_boot_notify(void);
void starfive_set_boot_ctrl_reg(int img_type);
void starfive_set_boot_stat_reg(int boot_src, int part_type, int img_type);

#endif /* _BOOT_PTI_H */
