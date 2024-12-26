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
#include <asm/arch/spl.h>

int starfive_spl_mmc_load_image(struct spl_image_info *spl_image,
				struct spl_boot_device *bootdev)
{
#ifdef CONFIG_SPL_MMC
	printf("Loading MMC secondary image...\n");
	return spl_mmc_load(spl_image, bootdev,
#ifdef CONFIG_SPL_FS_LOAD_RECOVERY_PAYLOAD_NAME
			    CONFIG_SPL_FS_LOAD_RECOVERY_PAYLOAD_NAME,
#else
			    NULL,
#endif
#ifdef CONFIG_SYS_MMCSD_RAW_MODE_U_BOOT_PARTITION
			    spl_mmc_boot_partition(bootdev->boot_device),
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
	int fb_rec_mmc = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_rec_mmc,
						   BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
						   BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
						   FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
						   CHECK);

	if (!map_stat) {
		/* Images in primary and secondary partition invalid */
		printf("primary and secondary images invalid...\n");
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

	return starfive_spl_mmc_load_image(spl_image, bootdev);
}

SPL_LOAD_IMAGE_METHOD("StarFive MMC1", 1, BOOT_DEVICE_MMC1, spl_mmc_load_image_handler);
