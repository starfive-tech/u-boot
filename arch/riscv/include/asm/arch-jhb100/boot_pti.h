/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_PTI_H
#define _BOOT_PTI_H

#include <linux/types.h>

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

enum ctl_boot_stage {
	BOOTSTG_U_BOOT_SPL	= 0,
	BOOTSTG_U_BOOT_PROPER	= 1,
	BOOTSTG_KERNEL		= 2
};

enum sts_image_flag {
	ACT_IMG		= 0,
	GOL_IMG		= 1,
	TEMP_IMG	= 2,
	BA0_IMG		= 3,
	BA1_IMG		= 4
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

#define BOOT_TRIAL_CNT		1
#define MAX_BOOT_TRIAL_UART	4

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
	u32 rsvd_1		: 1;
	u32 retry_cnt		: 4;
	u32 rsvd_2		: 19;
	u32 error		: 1;
};

typedef struct {
	struct boot_ctrl_reg	boot_ctrl_reg;
} ap_boot_ctl_reg;

typedef struct {
	struct boot_stat_reg	boot_stat_reg;
} ap_boot_sts_reg;

struct boot_reg_info {
	unsigned int idx;
	enum image_type img_type;
	ap_boot_ctl_reg *ctl_base_addr;
	ap_boot_sts_reg *sts_base_addr;
};

void starfive_set_ap_ctl_boot_stage(int img_type, int ctl_boot_stage);
void starfive_set_ap_sts_image_flag(int img_type, int sts_image_flag);
void starfive_set_ap_sts_boot_src(int img_type, int sts_boot_src);
int starfive_get_partition_num(int boot_src, int part_type, int img_type);
int starfive_get_partition_offset(int boot_src, int part_type, int img_type);
int starfive_get_sfc_cs_line_num(void);
int starfive_get_sfc_cs(int part_type, int img_type);
int starfive_req_img_auth_storage(int boot_src, int part_type, int img_type);
int starfive_req_img_auth_memory(int boot_src, int part_type, int img_type);
int starfive_pre_os_boot_notify(int part_type);
void starfive_set_boot_ctrl_reg(int img_type);
void starfive_set_boot_stat_reg(int boot_src, int part_type, int img_type);
void starfive_add_ap_sts_retry_cnt(int img_type, int cnt);
int starfive_get_ap_sts_retry_cnt(int img_type);
int starfive_get_ap_ctl_boot_stage(int img_type);

#endif /* _BOOT_PTI_H */
