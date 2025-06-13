/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_PTI_H
#define _BOOT_PTI_H

#include <linux/types.h>

#define EMMC_BOOT0_PART		1
#define EMMC_BOOT1_PART		2
/* TODO: Currently these macros are hardcoded to '0' indicating access to UDA
 * This is because not every FPGA station is fused with GPP partition yet.
 * So, to test access to GPP, choose MDC fpga 4 which is configured with GP1
 * partition and change below macro values to select GP1.
 *
 * Assign EMMC_GPP1_PART to value '4' to access GP1 and so on.....
 */
#define EMMC_GPP1_PART		4
#define EMMC_GPP2_PART		5
#define EMMC_GPP3_PART		6
#define EMMC_GPP4_PART		7
#define EMMC_UDA_PART		0

#define SFC_UBOOT_PROPER_ACTIVE_OFFS	0x210000
#define SFC_UBOOT_PROPER_GOLDEN_OFFS	0x210000
#define SFC_KERNEL_ACTIVE_OFFS		0x690000
#define SFC_KERNEL_GOLDEN_OFFS		0x1690000

#define EMMC_UBOOT_PROPER_ACTIVE_OFFS	0x190000
#define EMMC_UBOOT_PROPER_GOLDEN_OFFS	0x190000
#define EMMC_KERNEL_ACTIVE_OFFS		0
#define EMMC_KERNEL_GOLDEN_OFFS		0

/* Partition Type */
enum partition_type {
	PT_ACTIVE,
	PT_GOLDEN,
	PT_TEMP,
	PT_TYPE_MAX
};

/* Image Type */
enum image_type {
	IMG_TYPE_UBOOT_PROPER,
	IMG_TYPE_KERNEL,
	IMG_TYPE_MAX
};

/* GET_BMCFW_INFO EMMC Partition Mapping */
static const int emmc_partition_map[7] = {
	1,  /* 0 -> BOOT0 */
	2,  /* 1 -> BOOT1 */
	4,  /* 2 -> GPP0 */
	5,  /* 3 -> GPP1 */
	6,  /* 4 -> GPP2 */
	7,  /* 5 -> GPP3 */
	0   /* 6 -> UDA */
};

#define BOOT_CTRL_REG_ADDR		0x0013018018
#define SPL_BOOT_STAT_REG_ADDR		0x001301801C
#define UBOOT_PROP_BOOT_STAT_REG_ADDR	0x0013018020
#define KERNEL_BOOT_STAT_REG_ADDR	0x0013018024

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
int starfive_get_sfc_cs(int part_type, int img_type);
int starfive_req_img_auth_storage(int boot_src, int part_type, int img_type);
int starfive_req_img_auth_memory(int boot_src, int part_type, int img_type);
int starfive_pre_os_boot_notify(int part_type);
void starfive_set_boot_ctrl_reg(int img_type);
void starfive_set_boot_stat_reg(int boot_src, int part_type, int img_type);

#endif /* _BOOT_PTI_H */
