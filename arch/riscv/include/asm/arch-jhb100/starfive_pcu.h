/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _STARFIVE_PCU_H
#define _STARFIVE_PCU_H

#define U2_PCU_BASE_ADDR	0x00140A2C00
#define U4_PCU_BASE_ADDR	0x00140A2400
#define U8_PCU_BASE_ADDR	0x00140A2000

#define U2_PCU_PCU_IRQ_O	19
#define U4_PCU_PCU_IRQ_O	21
#define U8_PCU_PCU_IRQ_O	25

enum pcu_domain {
	PD_DC0		= 0,
	PD_HOST0_USB	= 1,
	PD_HOSTSS_i0	= 2,
	PD_ALL		= 3
};

enum pcu_pwr_policy_mode {
	PM_OFF		= 0,
	PM_RET		= 1,
	PM_MEMSLP	= 2,
	PM_ON		= 3,
	PM_WARMRST	= 4,
	PM_INVALID	= 5
};

enum pcu_hw_event_indication {
	HW_EVENT_OFF		= 1 << PM_OFF,
	HW_EVENT_RET		= 1 << PM_RET,
	HW_EVENT_MEMSLP		= 1 << PM_MEMSLP,
	HW_EVENT_ON		= 1 << PM_ON,
	HW_EVENT_WARMRST	= 1 << PM_WARMRST,
	HW_EVENT_NO_CHANGE	= 0
};

int starfive_pcu_set_pwr_mode(enum pcu_domain pd, enum pcu_pwr_policy_mode pwr_mode);

#endif /* _STARFIVE_PCU_H */
