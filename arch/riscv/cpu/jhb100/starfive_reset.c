// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	Wei Sheng Ch'ng <weisheng.chng@starfivetech.com>
 *
 */

#include <string.h>
#include <asm/arch/ap_core.h>
#include <asm/arch/starfive_reset.h>

static char *reset_id_str[] = {"POR", "WDT0", "PERST0", "PERST1", "eSPI0", "eSPI1", "Host0_SW",
			       "Host0_PCIe0_SW", "Host1_SW", "Host1_PCIe_SW", "BMC", "WDT1"};

void starfive_get_reset_event(char *parsed_str)
{
	int reset_id = GET_RESET_EVENT_ID;
	int is_single_node = GET_SOC_OTP_DUAL_NODE_STAT;
	int subsequent_str = 0;
	parsed_str[0] = '\0';

	for (int idx = 1, i = 0; idx <= RESET_EVENT_MSK; idx <<= 1, i++) {
		if (reset_id & idx) {
			if (is_single_node && (idx & (RESET_EVENT_PERSTN1 |
						      RESET_EVENT_ESPI1_RSTN |
						      RESET_EVENT_SYSCFG_RSTN_HOST1 |
						      RESET_EVENT_SYSCFG_RSTN_HOST1_PCIE)))
				continue;

			/* Found reset event, continue */
			if (subsequent_str) {
				/* More than 1 reset event */
				strcat(parsed_str, "+");
			} else {
				subsequent_str++;
			}
			strcat(parsed_str, reset_id_str[i]);
		}
	}

	/* User command or unknown reset */
	if (!subsequent_str)
		strcat(parsed_str, "Unknown");
}
