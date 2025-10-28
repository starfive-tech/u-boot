// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */

#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <hang.h>
#include <blk.h>
#include <dm.h>
#include <scsi.h>
#include <spl_load.h>
#include <ufs.h>

static ulong ufs_spl_load_read(struct spl_load_info *load, ulong off,
			       ulong size, void *buf)
{
	struct blk_desc *bd = load->priv;
	lbaint_t count = size >> bd->log2blksz;

	return blk_dread(bd, off, count, buf) << bd->log2blksz;
}

static int starfive_spl_ufs_get_lun(void)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int fb_rec_ufs = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_rec_ufs,
				BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
				BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				CHECK);

	if (!map_stat) {
		/* If golden image is in CS1, return 1 otherwise use default CS0 */
		return starfive_get_partition_num(BOOT_SRC_UFS, PT_GOLDEN, IMG_TYPE_UBOOT_PROPER);
	}
	return starfive_get_partition_num(BOOT_SRC_UFS, PT_ACTIVE, IMG_TYPE_UBOOT_PROPER);
}

static int ufs_load_image_raw_sector(struct spl_image_info *spl_image,
				     struct spl_boot_device *bootdev,
				     unsigned long sector)
{
	int ret;
	struct blk_desc *bd;
	struct spl_load_info load;
	int lun;

	lun = starfive_spl_ufs_get_lun();

	ret = blk_get_desc(UCLASS_SCSI, lun, &bd);
	if (ret)
		return CMD_RET_FAILURE;

	load.priv = bd;
	spl_set_bl_len(&load, bd->blksz);
	load.read = ufs_spl_load_read;
	ret = spl_load(spl_image, bootdev, &load, 0, sector);
	if (ret)
		return -1;

	return 0;
}

static unsigned long spl_ufs_get_uboot_raw_sector(void)
{
	int part = PT_ACTIVE;

	/*TODO: implement get uboot raw sector handling here*/
	return starfive_get_partition_offset(BOOT_SRC_UFS,
					     part,
					     IMG_TYPE_UBOOT_PROPER);
}

int spl_ufs_load(struct spl_image_info *spl_image,
		 struct spl_boot_device *bootdev)
{
	int err = 0;
	unsigned long raw_sect;

	err = scsi_scan(false);
	if (err)
		return CMD_RET_FAILURE;

	raw_sect = spl_ufs_get_uboot_raw_sector();
	err = ufs_load_image_raw_sector(spl_image, bootdev, raw_sect);
	if (!err)
		return err;

	return err;
}

static int spl_ufs_load_image_handler(struct spl_image_info *spl_image,
				      struct spl_boot_device *bootdev)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int ret = spl_ufs_load(spl_image, bootdev);
	int fb_rec_ufs = starfive_get_fb_rec_map();

	if (ret) {
		int map_stat = starfive_fb_rec_map_handler(&fb_rec_ufs,
					BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
					BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
					FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					CHECK);
		if (!map_stat) {
			/* Images in primary and secondary partition invalid */
			printf("Invalid UFS Active and Golden images found...\n");
			printf("Booting stop...\n");
			hang();
		} else if (map_stat == (FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK
					<< BOOT_SRC_PART_UFS_SECONDARY_BIT_POS)) {
			printf("Invalid UFS Active image found...\n");
			starfive_fb_rec_map_handler(&fb_rec_ufs,
				BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
				BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				SET);
			starfive_set_fb_rec_map(fb_rec_ufs);
			starfive_add_ap_sts_retry_cnt(BOOTSTG_U_BOOT_PROPER, BOOT_TRIAL_CNT);
		}
	}
	return ret;
}

/* Overriding the default if it happens to be linked in */
SPL_LOAD_IMAGE_METHOD("Starfive UFS", 0, BOOT_DEVICE_UFS, spl_ufs_load_image_handler);
SPL_LOAD_IMAGE_METHOD("Starfive UFS", 1, BOOT_DEVICE_UFS, spl_ufs_load_image_handler);
