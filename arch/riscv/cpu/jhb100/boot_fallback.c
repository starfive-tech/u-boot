// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#include <dm.h>
#include <hang.h>
#include <log.h>
#include <spl.h>
#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_src.h>

static int starfive_spl_load_image(struct spl_image_info *spl_image,
			struct spl_image_loader *loader)
{
	int ret;
	struct spl_boot_device bootdev;

	bootdev.boot_device = loader->boot_device;
	bootdev.boot_device_name = NULL;
	ret = loader->load_image(spl_image, &bootdev);
	return ret;
}

static int starfive_boot_from_devices(struct spl_image_info *spl_image,
			u32 spl_boot_list[], int count)
{
	struct spl_image_loader *drv =
		ll_entry_start(struct spl_image_loader, spl_image_loader);
	const int n_ents =
		ll_entry_count(struct spl_image_loader, spl_image_loader);
	int ret = -ENODEV;
	int i;

	for (i = 0; i < count && spl_boot_list[i] != BOOT_DEVICE_NONE; i++) {
		struct spl_image_loader *loader;
		int bootdev = spl_boot_list[i];

		for (loader = drv; loader != drv + n_ents; loader++) {
			if (bootdev != loader->boot_device)
				continue;

			if (loader) {
				printf("Trying to boot from %s\n",
					spl_loader_name(loader));
			} else {
				puts(SPL_TPL_PROMPT
					"Unsupported Boot Device!\n");
			}

			if (loader &&
				!starfive_spl_load_image(spl_image, loader)) {
				spl_image->boot_device = bootdev;
				return 0;
			}
		}
	}
	return ret;
}

/* Entry level detect phase for broken images in particular partition */
void starfive_board_boot_order(u32 *spl_boot_list)
{
	/* TODO: Change the source before build */
	int boot_src = GET_BOOT_SRC;
	int chk_map = 0;
	int fb_rec_map = starfive_get_fb_rec_map();
	int i;

	switch (boot_src) {
	case BOOT_SRC_SFC:
		chk_map = starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				CHECK);
		if (!chk_map) {
			/* Hang because both images broken */
			hang();
		} else {
			/* Primary or/and secondary is present */
			starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				SET);
			starfive_set_fb_rec_map(fb_rec_map);
		}
		spl_boot_list[0] = BOOT_DEVICE_SPI;
		break;
	case BOOT_SRC_AUTO_DETECT:
	/* AUTO DETECT mode */
	/* SPI > eMMC > UFS > UART */
		i = 0;

		if (starfive_fb_rec_map_handler(&fb_rec_map,
			BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
			BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
			FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
			CHECK)) {
			spl_boot_list[i] = BOOT_DEVICE_SPI;
			i += 1;
		}
		if (starfive_fb_rec_map_handler(&fb_rec_map,
			BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
			BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
			FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
			CHECK)) {
			spl_boot_list[i] = BOOT_DEVICE_SPI;
			i += 1;
		}
		if (starfive_fb_rec_map_handler(&fb_rec_map,
			BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
			BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
			FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
			CHECK)) {
			spl_boot_list[i] = BOOT_DEVICE_MMC1;
			i += 1;
		}
		if (starfive_fb_rec_map_handler(&fb_rec_map,
			BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
			BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
			FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
			CHECK)) {
			spl_boot_list[i] = BOOT_DEVICE_MMC1;
			i += 1;
		}
		if (!i)
			spl_boot_list[i] = BOOT_DEVICE_UART;
		break;
	case BOOT_SRC_EMMC:
		chk_map = starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
				BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				CHECK);
		if (!chk_map) {
			hang();
		} else {
			starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
				BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				SET);
			starfive_set_fb_rec_map(fb_rec_map);
		}
		spl_boot_list[0] = BOOT_DEVICE_MMC1;
		break;
	case BOOT_SRC_UART:
		spl_boot_list[0] = BOOT_DEVICE_UART;
		break;
	case BOOT_SRC_GMAC:
		spl_boot_list[0] = BOOT_DEVICE_CPGMAC;
		break;
	default:
		debug("Unsupported boot device 0x%x, trying UART..\n", boot_src);
		spl_boot_list[0] = BOOT_DEVICE_UART;
	}
}

void starfive_fallback_handler(void)
{
	u32 spl_boot_list[] = {
		BOOT_DEVICE_NONE,
		BOOT_DEVICE_NONE,
		BOOT_DEVICE_NONE,
		BOOT_DEVICE_NONE,
		BOOT_DEVICE_NONE,
	};
	struct spl_image_info spl_image;
	int ret;

	spl_image.boot_device = BOOT_DEVICE_NONE;
	starfive_board_boot_order(spl_boot_list);
	ret = starfive_boot_from_devices(&spl_image, spl_boot_list,
					ARRAY_SIZE(spl_boot_list));

	if (ret) {
		printf("Failed to boot from all boot devices\n");
		hang();
	}
}
