// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */

#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
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

static int ufs_load_image_raw_sector(struct spl_image_info *spl_image,
				     struct spl_boot_device *bootdev,
				     unsigned long sector)
{
	int ret;
	struct blk_desc *bd;
	struct spl_load_info load;
	u8 lun;

	lun = starfive_get_partition_num(BOOT_SRC_UFS, PT_ACTIVE,
					 IMG_TYPE_UBOOT_PROPER);

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
	return spl_ufs_load(spl_image, bootdev);
}

/* Overriding the default if it happens to be linked in */
SPL_LOAD_IMAGE_METHOD("Starfive UFS", 0, BOOT_DEVICE_UFS, spl_ufs_load_image_handler);
