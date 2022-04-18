// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 Starfive, Inc.
 * Author:	yanhong <yanhong.wang@starfivetech.com>
 *
 */

#ifndef __STARFIVE_JH7110_REGS_H
#define __STARFIVE_JH7110_REGS_H

/*system control register*/
#define STG_SYSCON_BASE          0x10240000
#define SYS_SYSCON_BASE          0x13030000
#define SYS_IOMUX_BASE           0x13040000
#define AON_SYSCON_BASE          0x17010000

/*gmac cfg*/
#define AON_SYSCFG_12			0xCU
#define SYS_SYSCON_144			0x90U
#define GMAC5_0_SEL_I_SHIFT             0x12U
#define GMAC5_0_SEL_I_MASK              0x1C0000U
#define GMAC5_1_SEL_I_SHIFT             0x2U
#define GMAC5_1_SEL_I_MASK              0x1CU

/*usb cfg*/
#define STG_SYSCON_4			0x4U
#define SYS_SYSCON_24			0x18U
#define SYS_IOMUX_32			0x80U
#define USB_MODE_STRAP_SHIFT		0x10U
#define USB_MODE_STRAP_MASK		0x70000U
#define USB_OTG_SUSPENDM_BYPS_SHIFT     0x14U
#define USB_OTG_SUSPENDM_BYPS_MASK      0x100000U
#define USB_OTG_SUSPENDM_SHIFT          0x13U
#define USB_OTG_SUSPENDM_MASK           0x80000U
#define USB_PLL_EN_SHIFT                0x16U
#define USB_PLL_EN_MASK                 0x400000U
#define USB_REFCLK_MODE_SHIFT           0x17U
#define USB_REFCLK_MODE_MASK            0x800000U
#define PDRSTN_SPLIT_SHIFT		0x11U
#define PDRSTN_SPLIT_MASK		0x20000U
#define IOMUX_USB_SHIFT			0x10U
#define IOMUX_USB_MASK			0x7F0000U

#endif /* __STARFIVE_JH7110_REGS_H */

