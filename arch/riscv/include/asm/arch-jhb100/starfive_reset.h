/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	Wei Sheng Ch'ng <weisheng.chng@starfivetech.com>
 *
 */

#ifndef _STARFIVE_RESET_H
#define _STARFIVE_RESET_H

#include <asm/io.h>
#include <asm/arch/ap_core.h>

/* Reset Event Status Register */
#define RESET_EVENT_ADDR			0x0013010034
#define RESET_EVENT_MSK				0xFFF
#define SOC_OTP_DUAL_NODE_DISABLE_MSK		0x800

/* Reset Event */
#define RESET_EVENT_SYSRSTN_POR			0x001	// Power-On Reset
#define RESET_EVENT_SCP_WDT			0x002	// SCP WDT Reset
#define RESET_EVENT_PERSTN0			0x004	// PCIe0 Reset
#define RESET_EVENT_PERSTN1			0x008	// PCIe1 Reset
#define RESET_EVENT_ESPI0_RSTN			0x010	// eSPI0 Reset
#define RESET_EVENT_ESPI1_RSTN			0x020	// eSPI1 Reset
#define RESET_EVENT_SYSCFG_RSTN_HOST0		0x040	// Host0 SW Reset
#define RESET_EVENT_SYSCFG_RSTN_HOST0_PCIE	0x080	// Host0 PCIE SW Reset
#define RESET_EVENT_SYSCFG_RSTN_HOST1		0x100	// Host1 SW Reset
#define RESET_EVENT_SYSCFG_RSTN_HOST1_PCIE	0x200	// Host1 PCIE SW Reset
#define RESET_EVENT_SYSCFG_SW_BMC_SEC_SCP	0x400	// SCP Reset
#define RESET_EVENT_SYSCFG_SW_BMC_NON_SEC_AP	0x800	// AP WDT Reset

/* Read Reset Event Utility */
#define GET_RESET_EVENT_ID		(readl((const void *)RESET_EVENT_ADDR) & \
					 RESET_EVENT_MSK)

/* Get BMC AP cores status */
#define GET_SOC_OTP_DUAL_NODE_STAT	\
	(readl((const void *)SYS2_SYSCON_SOC_OTPSTRAP_STAT1_ADDR)	\
	 & (SOC_OTP_DUAL_NODE_DISABLE_MSK))

void starfive_get_reset_event(char *str);

#endif /* _STARFIVE_RESET_H */
