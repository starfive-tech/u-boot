/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_SRC_STARFIVE_H
#define _BOOT_SRC_STARFIVE_H

#include <asm/io.h>

#define BOOT_STRAP_ADDR				0x001301A050
#define AP_BOOT_CTL_REG_ADDR			0x0013018018
#define UBOOT_SPL_BOOT_STS_REG_ADDR		0x001301801c
#define UBOOT_PROPER_BOOT_STS_REG_ADDR		0x0013018020
#define KERNEL_BOOT_STS_REG_ADDR		0x0013018024
#define AP_BOOT_COUNTER_ADDR			0x0013018028

#define BOOT_SRC_UART		0x0
#define BOOT_SRC_EMMC		0x1
#define BOOT_SRC_UFS		0x2
#define BOOT_SRC_SFC		0x3
#define BOOT_SRC_GMAC		0x4
#define BOOT_SRC_AUTO_DETECT	0x5
/* Debugging */
#define HARD_SELECT_BOOT_SRC_RAM	0x6
#define BOOT_SRC_MASK			GENMASK(1, 0)
#define BMC_FLASH_MODE_MASK		GENMASK(0, 0)

#define BOOT_SRC_SHIFT			0x6
#define BMC_FLASH_MODE_SHIFT		0x1a

/* Get boot source reg value */
#define GET_BOOT_STRAP		readl((const void *)BOOT_STRAP_ADDR)
#define GET_BOOT_SRC		((GET_BOOT_STRAP >> BOOT_SRC_SHIFT) & BOOT_SRC_MASK)
#define GET_BMC_FLASH_MDOE	((GET_BOOT_STRAP >> BMC_FLASH_MODE_SHIFT) & \
				BMC_FLASH_MODE_MASK)

u32 jhb100_get_boot_device(void);

#endif /* _BOOT_SRC_STARFIVE_H */
