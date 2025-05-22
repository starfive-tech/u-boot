// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#include <image.h>
#include <hang.h>
#include <log.h>
#include <spl.h>
#include <spl_load.h>
#include <spi.h>
#include <spi_flash.h>
#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/spl.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/libfdt.h>
#include <rand.h>

/*
 * Custom SPI loading implementation for Starfive. This is a reduced
 * SPI load image function from the mainline but provide leeway for
 * fallback boot feature.
 */
static ulong spl_spi_fit_read(struct spl_load_info *load, ulong sector,
			      ulong count, void *buf)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	struct spi_flash *flash = load->priv;
	ulong ret;

	ret = spi_flash_read(flash, sector, count, buf);
	if (!ret)
		return count;
	else
		return 0;
}

u32 spl_spi_boot_bus(void)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	return CONFIG_SF_DEFAULT_BUS;
}

u32 spl_spi_boot_cs(void)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int fb_rec_spi = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_rec_spi,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				CHECK);

	if (!map_stat) {
		/* Get to CS 1 for Golden partition */
		if (starfive_get_sfc_cs_line_num() < 2)
			return CONFIG_SF_DEFAULT_CS;
		return 1;
	}
	return CONFIG_SF_DEFAULT_CS;
}

unsigned int starfive_spl_spi_get_uboot_offs(void)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int fb_rec_spi = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_rec_spi,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				CHECK);
	if (!map_stat) {
		printf("Loading SFC Golden image...\n");
		return starfive_get_partition_offset(BOOT_SRC_SFC,
						     PT_GOLDEN,
						     IMG_TYPE_UBOOT_PROPER);
	} else if (map_stat == (FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK
				<< BOOT_SRC_PART_SPI_SECONDARY_BIT_POS)) {
		printf("Loading SFC Active image...\n");
		return starfive_get_partition_offset(BOOT_SRC_SFC,
						     PT_ACTIVE,
						     IMG_TYPE_UBOOT_PROPER);
	}
	return CONFIG_SYS_SPI_U_BOOT_OFFS;
}

/*
 * The main entry for SPI booting. It's necessary that SDRAM is already
 * configured and available since this code loads the main U-Boot image
 * from SPI into SDRAM and starts it from there.
 */
static int starfive_spl_spi_load_image(struct spl_image_info *spl_image,
				       struct spl_boot_device *bootdev)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int err = 0;
	unsigned int payload_offs = 0;
	struct spi_flash *flash;
	unsigned int sf_bus = spl_spi_boot_bus();
	unsigned int sf_cs = spl_spi_boot_cs();
	struct spl_load_info load;

	/*
	 * Load U-Boot image from SPI flash into RAM
	 * In DM mode: defaults speed and mode will be
	 * taken from DT when available
	 */
	flash = spi_flash_probe(sf_bus, sf_cs,
				CONFIG_SF_DEFAULT_SPEED,
				CONFIG_SF_DEFAULT_MODE);
	if (!flash) {
		puts("SPI probe failed.\n");
		return -ENODEV;
	}

	load.priv = flash;
	spl_set_bl_len(&load, 1);
	load.read = spl_spi_fit_read;

#if CONFIG_IS_ENABLED(OS_BOOT)
	if (spl_start_uboot()) {
		int err = spl_load(spl_image, bootdev, &load, 0,
				   CFG_SYS_SPI_KERNEL_OFFS);

		if (!err)
			/* Read device tree. */
			return spi_flash_read(flash, CFG_SYS_SPI_ARGS_OFFS,
					      CFG_SYS_SPI_ARGS_SIZE,
					      (void *)CONFIG_SPL_PAYLOAD_ARGS_ADDR);
	}
#endif
	payload_offs = starfive_spl_spi_get_uboot_offs();

	err = spl_load(spl_image, bootdev, &load, 0, payload_offs);
	if (IS_ENABLED(CONFIG_SPI_FLASH_SOFT_RESET))
		err = spi_nor_remove(flash);
	return err;
}

static int spl_spi_load_image_handler(struct spl_image_info *spl_image,
					struct spl_boot_device *bootdev)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int ret = starfive_spl_spi_load_image(spl_image, bootdev);
	int fb_rec_spi = starfive_get_fb_rec_map();

	if (ret) {
		int map_stat = starfive_fb_rec_map_handler(&fb_rec_spi,
					BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
					BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
					FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					CHECK);
		if (!map_stat) {
			/* Images in primary and secondary partition invalid */
			printf("Invalid SFC Active and Golden images found...\n");
			printf("Booting stop...\n");
			hang();
		} else if (map_stat == (FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK
					<< BOOT_SRC_PART_SPI_SECONDARY_BIT_POS)) {
			printf("Invalid SFC Active image found...\n");
			if (starfive_get_sfc_cs_line_num() < 2) {
				printf("Booting stop...\n");
				hang();
			}
			starfive_fb_rec_map_handler(&fb_rec_spi,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				SET);
			starfive_set_fb_rec_map(fb_rec_spi);
		}
	}
	return ret;
}

/* Overriding the default if it happens to be linked in */
SPL_LOAD_IMAGE_METHOD("Starfive SPI", 0, BOOT_DEVICE_SPI, spl_spi_load_image_handler);
