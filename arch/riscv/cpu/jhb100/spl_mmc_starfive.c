// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */

#include <hang.h>
#include <log.h>
#include <mmc.h>
#include <spl.h>
#include <spl_load.h>
#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/spl.h>

#ifdef JHB100_ENABLE_LOAD_TEMP_IMG_FOR_EMMC
static ulong h_spl_load_read(struct spl_load_info *load, ulong off,
			     ulong size, void *buf)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	struct blk_desc *bd = load->priv;
	lbaint_t sector = off >> bd->log2blksz;
	lbaint_t count = size >> bd->log2blksz;

	return blk_dread(bd, sector, count, buf) << bd->log2blksz;
}

static int starfive_spl_mmc_get_device_index(u32 boot_device)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	switch (boot_device) {
	case BOOT_DEVICE_MMC1:
		return 0;
	}

#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
	printf("spl: unsupported mmc boot device.\n");
#endif

	return -ENODEV;
}

static int starfive_spl_mmc_get_mmc_devnum(struct mmc *mmc)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	struct blk_desc *block_dev;
#if !CONFIG_IS_ENABLED(BLK)
	block_dev = &mmc->block_dev;
#else
	block_dev = mmc_get_blk_desc(mmc);
#endif
	return block_dev->devnum;
}

static int starfive_spl_mmc_find_device(struct mmc **mmcp, u32 boot_device)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int err, mmc_dev;

	mmc_dev = starfive_spl_mmc_get_device_index(boot_device);
	if (mmc_dev < 0)
		return mmc_dev;

#if CONFIG_IS_ENABLED(DM_MMC)
	err = mmc_init_device(mmc_dev);
#else
	err = mmc_initialize(NULL);
#endif /* DM_MMC */
	if (err) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		printf("spl: could not initialize mmc. error: %d\n", err);
#endif
		return err;
	}
	*mmcp = find_mmc_device(mmc_dev);
	err = *mmcp ? 0 : -ENODEV;
	if (err) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		printf("spl: could not find mmc device %d. error: %d\n",
		       mmc_dev, err);
#endif
		return err;
	}

	return 0;
}

int starfive_mmc_load_image_raw_sector(struct spl_image_info *spl_image,
				       struct spl_boot_device *bootdev,
				       struct mmc *mmc, unsigned long sector)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int ret;
	struct blk_desc *bd = mmc_get_blk_desc(mmc);
	struct spl_load_info load;

	load.priv = bd;
	spl_set_bl_len(&load, bd->blksz);
	load.read = h_spl_load_read;
	ret = spl_load(spl_image, bootdev, &load, 0, sector << bd->log2blksz);

	if (ret) {
		if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
			printf("fn(): %s\n", __func__);
		printf("fn(): spl_load() failed\n");

#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		puts("mmc_load_image_raw_sector: mmc block read error\n");
#endif
		return -1;
	}

	return 0;
}

static int starfive_mmc_load_partition(struct spl_image_info *spl_image,
					    struct spl_boot_device *bootdev,
					    struct mmc *mmc, int partition,
					    unsigned long sector)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	struct disk_partition info;
	int err;

	err = part_get_info(mmc_get_blk_desc(mmc), partition, &info);
	if (err) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
		puts("spl: partition error\n");
#endif
		return -1;
	}

#ifdef CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_USE_SECTOR
	return starfive_mmc_load_image_raw_sector(spl_image,
						  bootdev,
						  mmc,
						  info.start + sector);
#else
	return starfive_mmc_load_image_raw_sector(spl_image,
						  bootdev,
						  mmc,
						  info.start);
#endif
}

static int starfive_spl_mmc_get_temp_part(void)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	return starfive_get_partition_num(BOOT_SRC_EMMC,
					  PT_TEMP,
					  IMG_TYPE_UBOOT_PROPER);
}

static struct mmc *mmc;

int starfive_spl_mmc_load(struct spl_image_info *spl_image,
			  struct spl_boot_device *bootdev,
			  const char *filename,
			  int raw_part,
			  unsigned long raw_sect)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	u32 boot_mode;
	int err = 0;
	__maybe_unused int part = 0;
	int mmc_dev;

	/* Perform peripheral init only once for an mmc device */
	mmc_dev = starfive_spl_mmc_get_device_index(bootdev->boot_device);
	if (!mmc || starfive_spl_mmc_get_mmc_devnum(mmc) != mmc_dev) {
		err = starfive_spl_mmc_find_device(&mmc, bootdev->boot_device);
		if (err)
			return err;

		err = mmc_init(mmc);
		if (err) {
			mmc = NULL;
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
			printf("spl: mmc init failed with error: %d\n", err);
#endif
			return err;
		}
	}

	boot_mode = spl_mmc_boot_mode(mmc, bootdev->boot_device); //weak: place in spl.c
	err = -EINVAL;
	switch (boot_mode) {
	case MMCSD_MODE_EMMCBOOT:
		part = spl_mmc_emmc_boot_partition(mmc); //weak: place in spl.c
		err = blk_dselect_hwpart(mmc_get_blk_desc(mmc), part);

		if (err) {
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
			puts("spl: mmc partition switch failed\n");
#endif
			return err;
		}
		/* Fallthrough */
	case MMCSD_MODE_RAW:
		debug("spl: mmc boot mode: raw\n");
		raw_sect = spl_mmc_get_uboot_raw_sector(mmc, raw_sect);
		err = starfive_mmc_load_partition(spl_image, bootdev,
						       mmc, raw_part,
						       raw_sect);
		if (!err)
			return err;

		break;
#ifdef CONFIG_SPL_LIBCOMMON_SUPPORT
	default:
		puts("spl: mmc: wrong boot mode\n");
#endif
	}

	return err;
}
#endif

int starfive_spl_mmc_load_image(struct spl_image_info *spl_image,
				struct spl_boot_device *bootdev,
				int boot_part)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
#ifdef CONFIG_SPL_MMC
#ifdef JHB100_ENABLE_LOAD_TEMP_IMG_FOR_EMMC
	if (!boot_part) {
		printf("Loading MMC Temp Image...\n");
		return starfive_spl_mmc_load(spl_image, bootdev,
					     NULL,
					     starfive_spl_mmc_get_temp_part(),
#ifdef CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR
					     CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR);
#else
					     0);
#endif
	}
#endif
	printf("Loading MMC Golden image...\n");
	return spl_mmc_load(spl_image, bootdev,
#ifdef CONFIG_SPL_FS_LOAD_RECOVERY_PAYLOAD_NAME
			    CONFIG_SPL_FS_LOAD_RECOVERY_PAYLOAD_NAME,
#else
			    NULL,
#endif
#ifdef CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_PARTITION
			    spl_mmc_boot_partition(bootdev->boot_device), //weak: place in spl.c
#else
			    0,
#endif
#ifdef CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR
			    CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_SECTOR);
#else
			    0);
#endif
#else
	return -1;
#endif
}

static int spl_mmc_load_image_handler(struct spl_image_info *spl_image,
				      struct spl_boot_device *bootdev)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int fb_rec_mmc = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_rec_mmc,
						   BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
						   BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
						   FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
						   CHECK);

	if (!map_stat) {
		/* Images in Active and Golden partition invalid */
		printf("Invalid MMC Active and Golden images found...\n");
		printf("Booting stop...\n");
		hang();
	} else if (map_stat == (FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK
				<< BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS)) {
		starfive_fb_rec_map_handler(&fb_rec_mmc,
					    BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
					    BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
					    FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					    SET);
		starfive_set_fb_rec_map(fb_rec_mmc);
	}

	return starfive_spl_mmc_load_image(spl_image, bootdev, fb_rec_mmc);
}

SPL_LOAD_IMAGE_METHOD("StarFive MMC1", 1, BOOT_DEVICE_MMC1, spl_mmc_load_image_handler);
