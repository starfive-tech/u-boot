// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */

#include <stdio.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <asm/arch/starfive_pcu.h>
#include <asm/arch/saif_init.h>

struct pwr_policy_cap_t {
	u32 sta_off_cap			: 1;
	u32 sta_ret_cap			: 1;
	u32 sta_memslp_cap		: 1;
	u32 sta_on_cap			: 1;
	u32 sta_warmrst_cap		: 1;
	u32 rsv0			: 11;
	u32 dyn_off_cap			: 1;
	u32 dyn_ret_cap			: 1;
	u32 dyn_memslp_cap		: 1;
	u32 dyn_on_cap			: 1;
	u32 dyn_warmrst_cap		: 1;
	u32 rsv1			: 11;
};

struct pcu_status_t {
	u32 pwr_trans_in_prog		: 1;
	u32 bisr_busy			: 1;
	u32 pwr_request_status		: 2;
	u32 rsv0			: 4;
	u32 curr_pwr_mode		: 4;
	u32 curr_pwr_dyn		: 1;
	u32 logpwr_ack			: 1;
	u32 rsv1			: 18;
};

struct pwr_policy_ctrl_t {
	u32 pwr_policy_mode		: 4;
	u32 pwr_dyn_en			: 1;
	u32 rsv				: 27;
};

struct pwr_req_cfg_t {
	u32 warmrst_devreq_dis		: 1;
	u32 rsv				: 31;
};

struct hardware_event_indication_t {
	u32 hw_event			: 5;
	u32 rsv				: 27;
};

struct hardware_event_mask_t {
	u32 hw_event_mask		: 5;
	u32 rsv				: 27;
};

struct pwr_mode_entry_delay_cfg_t {
	u32 pm_off_dly			: 8;
	u32 pm_ret_dly			: 8;
	u32 pm_memslp_dly		: 8;
	u32 rsv				: 8;
};

struct pwr_switch_n_retention_delay_cfg_t {
	u32 logpwr_dly			: 8;
	u32 logret_dly			: 8;
	u32 ramsd_dly			: 8;
	u32 ramslp_dly			: 8;
};

struct device_ctrl_delay_cfg_t {
	u32 rst_dly			: 8;
	u32 clk_dly			: 8;
	u32 iso_dly			: 8;
	u32 devreq_dly			: 4;
	u32 rsv				: 4;
};

struct intr_status_t {
	u32 sta_accept_irq		: 1;
	u32 sta_reject_irq		: 1;
	u32 dyn_accept_irq		: 1;
	u32 dyn_reject_irq		: 1;
	u32 pwr_trans_comp_irq		: 1;
	u32 unspt_policy_irq		: 1;
	u32 rsv0			: 11;
	u32 hw_event_off_irq		: 1;
	u32 hw_event_retention_irq	: 1;
	u32 hw_event_memslp_irq		: 1;
	u32 hw_event_on_irq		: 1;
	u32 hw_event_warmrst_irq	: 1;
	u32 rsv1			: 11;
};

struct intr_mask_t {
	u32 sta_accept_irq_mask		: 1;
	u32 sta_reject_irq_mask		: 1;
	u32 dyn_accept_irq_mask		: 1;
	u32 dyn_reject_irq_mask		: 1;
	u32 pwr_trans_comp_irq_mask	: 1;
	u32 unspt_policy_irq_mask	: 1;
	u32 rsv				: 26;
};

struct hardware_event_edge_detect_cfg_t {
	u32 rise_detect			: 5;
	u32 rsv0			: 11;
	u32 fall_detect			: 5;
	u32 rsv1			: 11;
};

typedef struct {
	struct pwr_policy_cap_t				pwr_policy_cap;
	struct pcu_status_t				pcu_status;
	struct pwr_policy_ctrl_t			pwr_policy_ctrl;
	struct pwr_req_cfg_t				pwr_req_cfg;
	struct hardware_event_indication_t		hardware_event_indication;
	struct hardware_event_mask_t			hardware_event_mask;
	struct pwr_mode_entry_delay_cfg_t		pwr_mode_entry_delay_cfg;
	struct pwr_switch_n_retention_delay_cfg_t	pwr_switch_n_retention_delay_cfg;
	struct device_ctrl_delay_cfg_t			device_ctrl_delay_cfg;
	struct intr_status_t				intr_status;
	struct intr_mask_t				intr_mask;
	struct hardware_event_edge_detect_cfg_t		hardware_event_edge_detect_cfg;
} pcu_registers;

struct pcu_info {
	unsigned int idx;
	enum pcu_domain pd;
	pcu_registers *base_addr;
	unsigned int irq_num;
};

static struct pcu_info pcus[] = {
	{.idx = 0,
	 .pd = PD_DC0,
	 .base_addr = (pcu_registers *)U2_PCU__ITG_BD_APB__BASE_ADDR,
	 .irq_num = U0_DOM_BMCCPUSS_U0_XBAR_TOP_IRQ_SOURCE__U2_PCU_PCU_IRQ_O},  /* pcu dc 0 */
	{.idx = 1,
	 .pd = PD_HOST0_USB,
	 .base_addr = (pcu_registers *)U4_PCU__ITG_BD_APB__BASE_ADDR,
	 .irq_num = U0_DOM_BMCCPUSS_U0_XBAR_TOP_IRQ_SOURCE__U4_PCU_PCU_IRQ_O},  /* pcu host usb 0 */
	{.idx = 2,
	 .pd = PD_HOSTSS_i0,
	 .base_addr = (pcu_registers *)U8_PCU__ITG_BD_APB__BASE_ADDR,
	 .irq_num = U0_DOM_BMCCPUSS_U0_XBAR_TOP_IRQ_SOURCE__U8_PCU_PCU_IRQ_O},  /* pcu hostss 0 */
};

static char *power_dom_name[] = {"DC0", "HOST0_USB", "HOSTSS_i0"};

#if 0
static void (*pcu_enable[])(void) = {
	dc0_pcu_enable,
	hostusb0_pcu_enable,
	hostss0_pcu_enable,
};

static void (*pcu_disable[])(void) = {
	dc0_pcu_disable,
	hostusb0_pcu_disable,
	hostss0_pcu_disable,
};
#endif

void dc0_pcu_enable(void)
{
	_CLEAR_RESET_RSTGEN_MAIN_RSTN_PCU_DC0_;
}

void dc0_pcu_disable(void)
{
	_ASSERT_RESET_RSTGEN_MAIN_RSTN_PCU_DC0_;
}

void hostusb0_pcu_enable(void)
{
	_CLEAR_RESET_RSTGEN_MAIN_RSTN_PCU_HOSTUSB0_;
}

void hostusb0_pcu_disable(void)
{
	_ASSERT_RESET_RSTGEN_MAIN_RSTN_PCU_HOSTUSB0_;
}

void hostss0_pcu_enable(void)
{
	_CLEAR_RESET_RSTGEN_MAIN_RSTN_PCU_HOSTSS0_;
}

void hostss0_pcu_disable(void)
{
	_ASSERT_RESET_RSTGEN_MAIN_RSTN_PCU_HOSTSS0_;
}

int starfive_pcu_set_pwr_mode(enum pcu_domain pd, enum pcu_pwr_policy_mode pwr_policy_mode)
{
	int retry = 10;
	struct pcu_info *pcu = &pcus[pd];

	printf("Configuring Power Domain [%s]\n", power_dom_name[pd]);
	/* TODO: Temporary solution for powering up subsys domain
	 * Turn on by setting Power Policy Control register
	 * FIX for RTL0.5.1 PCU bug, remove later
	 * _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_;
	 * _CLEAR_RESET_RSTGEN_RSTN_U0_BCU_DFT_BISR_RST_;
	 */

	/* TODO: There may be a race condition with L1 FW as L1 init the power system
	 * only after booting SPL, hence u'x' domain signal is enabled by default already
	 * pcu_disable[pcu->idx]();
	 * pcu_enable[pcu->idx]();
	 */

	if (!pcu->base_addr->pwr_policy_cap.sta_on_cap) {
		printf("[FAILURE] No Static ON capability ....\n");
		return 0;
	}

	if (pcu->base_addr->pcu_status.curr_pwr_mode == pwr_policy_mode) {
		printf("[WARNING] No need to transfer...\n");
	} else {
		if (pwr_policy_mode == PM_ON) {
			printf("Software Initiate Static ON...\n");
			pcu->base_addr->pwr_policy_ctrl.pwr_dyn_en = 0;
			pcu->base_addr->pwr_policy_ctrl.pwr_policy_mode = PM_ON;
		} else if (pwr_policy_mode == PM_OFF) {
			printf("Software Initiate Static OFF...\n");
			pcu->base_addr->pwr_policy_ctrl.pwr_dyn_en = 1;
			pcu->base_addr->pwr_policy_ctrl.pwr_policy_mode = PM_OFF;
		}
	}

	do {
		if (pcu->base_addr->intr_status.pwr_trans_comp_irq &&
		    !pcu->base_addr->pcu_status.pwr_trans_in_prog) {
			printf("Power mode Transition is completed...\n");
			break;
		}
		udelay(1000);
		--retry;
	} while (retry);

	if (!retry) {
		printf("[FAILURE] Power Mode Transition timeout....\n");
	} else {
		if (pcu->base_addr->pcu_status.pwr_request_status == 1)
			printf("[SUCCESS] Power Request Status accepted...\n");
		else
			printf("[FAILURE] Power Request Status rejected...\n");
	}
	return 0;
}
