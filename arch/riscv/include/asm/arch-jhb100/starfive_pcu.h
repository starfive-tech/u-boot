/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _STARFIVE_PCU_H
#define _STARFIVE_PCU_H

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

void u2_pcu_enable(void);
void u2_pcu_disable(void);
void u4_pcu_enable(void);
void u4_pcu_disable(void);
void u8_pcu_enable(void);
void u8_pcu_disable(void);
void starfive_pcu_enable(enum pcu_domain pd);
void starfive_pcu_disable(enum pcu_domain pd);
int starfive_pcu_set_pwr_mode(enum pcu_domain pd, enum pcu_pwr_policy_mode pwr_mode);

#endif /* _STARFIVE_PCU_H */
