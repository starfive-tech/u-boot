// SPDX-License-Identifier: GPL-2.0+
/**
 ******************************************************************************
 * @file  board.c
 * @author  StarFive Technology
 * @version  V1.0
 * @date  23/05/2024
 * @brief
 ******************************************************************************
 * @copy
 *
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
 * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
 * TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE FOR ANY
 * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
 * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
 * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
 *
 * COPYRIGHT 2024 Shanghai StarFive Technology Co., Ltd.
 */
#include <dm.h>
#include <spl.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/spl.h>

u32 jhb100_get_boot_device(void)
{
	int boot_mode = BOOT_SRC_SFC;

	switch (boot_mode) {
	case BOOT_SRC_SFC:
		return BOOT_DEVICE_SPI;
	case BOOT_SRC_EMMC:
		return BOOT_DEVICE_MMC1;
	case BOOT_SRC_UFS:
		return BOOT_DEVICE_MMC1;
	case BOOT_SRC_UART:
		return BOOT_DEVICE_UART;
	case BOOT_SRC_AUTO_DETECT:
		return BOOT_DEVICE_RAM;
	case BOOT_SRC_GMAC:
		return BOOT_DEVICE_CPGMAC;
	case HARD_SELECT_BOOT_SRC_RAM:
		return BOOT_DEVICE_RAM;
	default:
		debug("Unsupported boot device 0x%x but trying MMC1\n", boot_mode);
		return BOOT_DEVICE_NOR;
	}
}

int mmc_get_env_dev(void)
{
	switch (jhb100_get_boot_device()) {
	case BOOT_DEVICE_MMC1:
		return 0;
	case BOOT_DEVICE_MMC2:
		return 1;
	default:
#ifdef CONFIG_SYS_MMC_ENV_DEV
		return CONFIG_SYS_MMC_ENV_DEV;
#else
		return 0;
#endif
	}
}
