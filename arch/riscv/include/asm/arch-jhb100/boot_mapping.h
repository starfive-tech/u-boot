/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_MAPPING_H
#define _BOOT_MAPPING_H

#define FALLBACK_RECOVERY_SCRATCHPAD_ADDR	0x0013018014

/* Storage type bit position */
typedef enum {
	BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS      = 0x0,
	BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS    = 0x1,
	BOOT_SRC_PART_UFS_PRIMARY_BIT_POS       = 0x2,
	BOOT_SRC_PART_UFS_SECONDARY_BIT_POS     = 0x3,
	BOOT_SRC_PART_SPI_PRIMARY_BIT_POS       = 0x4,
	BOOT_SRC_PART_SPI_SECONDARY_BIT_POS     = 0x5,
} FB_REC_MAP_BIT_POS;

/* Allocated bitmaps for components */
typedef enum {
	FB_RCV_L1_FW_SET_SPL_CLEAR_MSK		= 0b1,
	FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK	= 0b1000000,
	FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK	= 0b1000000000000,
} FB_REC_MAP_STATE;

typedef enum {
	SET = 0,
	CLEAR = 1,
	CHECK = 2,
} FB_REC_MAP;

typedef enum {
	PRIMARY = 0,
	SECONDARY = 1,
} FB_REC_MAP_TYPE;

FB_REC_MAP_BIT_POS starfive_get_part(FB_REC_MAP_TYPE p_type);
int starfive_get_fb_rec_map(void);
void starfive_set_fb_rec_map(int val);

int starfive_fb_rec_map_handler(int *reg_map,
		FB_REC_MAP_BIT_POS first_part_bit,
		FB_REC_MAP_BIT_POS last_part_bit,
		FB_REC_MAP_STATE reg_map_msk,
		FB_REC_MAP action);

#endif /* _BOOT_MAPPING_H */
