// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	ZhiWei Lim <zhiwei.lim@starfivetech.com>
 *
 */

 #include "clk.h"
 #include "clk-starfive-common.h"
 #include <dt-bindings/clock/starfive,jhb100-crg.h>
 #include <linux/clk-provider.h>

static const char *gmac2_rmii_mux[MAX_NUM_PARENTS] = {
	[0] = "per2_gmac2_rmii_ref",
	[1] = "gmac2_rmii_50",
};

static const char *gmac2_rgmii_125_mux[MAX_NUM_PARENTS] = {
	[0] = "per2_gmac2_rgmii_rx",
	[1] = "per2_125",
};

static const char *gmac2_tx_mux[MAX_NUM_PARENTS] = {
	[0] = "gmac2_rmii_div",
	[1] = "gmac2_rgmii_div",
};

static const char *gmac2_rx_mux[MAX_NUM_PARENTS] = {
	[0] = "gmac2_rmii_div",
	[1] = "gmac2_rgmii_125_mux",
};

static const char *gmac2_txck_mux[MAX_NUM_PARENTS] = {
	[0] = "gmac2_rmii_50",
	[1] = "gmac2_tx_mux",
};

static const char *gmac3_tx_125_mux[MAX_NUM_PARENTS] = {
	[0] = "per2_gmac3_sgmii_tx",
	[1] = "per2_125",
};

static const char *gmac3_rx_125_mux[MAX_NUM_PARENTS] = {
	[0] = "per2_gmac3_sgmii_rx",
	[1] = "per2_125",
};

static struct clk_info per2crg_clk_info[] = {
	{ JHB100_PER2CLK_300,			"per2_300",
		"per2_600",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER2CLK_100,			"per2_100",
		"per2_400",		NULL,	CLK_DIVIDER,	4 },
	{ JHB100_PER2CLK_50,			"per2_50",
		"per2_100",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER2CLK_GMAC2_RMII_50,		"gmac2_rmii_50",
		"per2_100",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER2CLK_CAN0_CORE_DIV,		"can0_core_div",
		"per2_400",		NULL,	CLK_DIVIDER,	5 },
	{ JHB100_PER2CLK_CAN1_CORE_DIV,		"can1_core_div",
		"per2_400",		NULL,	CLK_DIVIDER,	5 },
	{ JHB100_PER2CLK_CAN0_TIMER,		"can0_timer",
		"per2_100",		NULL,	CLK_DIVIDER,	7 },
	{ JHB100_PER2CLK_CAN1_TIMER,		"can1_timer",
		"per2_100",		NULL,	CLK_DIVIDER,	7 },
	{ JHB100_PER2CLK_RTC_CORE_DIV,		"rtc_core_div",
		"osc",			NULL,	CLK_DIVIDER,	10 },
	{ JHB100_PER2CLK_GMAC2_RMII_MUX_DLY,	"gmac2_rmii_mux_dly",
		"",	gmac2_rmii_mux,		CLK_MUX,	0 },
	{ JHB100_PER2CLK_GMAC2_RMII_DIV,	"gmac2_rmii_div",
		"gmac2_rmii_mux_dly",	NULL,	CLK_DIVIDER,	5 },
	{ JHB100_PER2CLK_GMAC2_RGMII_125_MUX,	"gmac2_rgmii_125_mux",
		"",	gmac2_rgmii_125_mux,	CLK_MUX,	0 },
	{ JHB100_PER2CLK_GMAC2_RGMII_DIV,	"gmac2_rgmii_div",
		"per2_125",		NULL,	CLK_DIVIDER,	6 },
	{ JHB100_PER2CLK_GMAC2_TX_MUX,		"gmac2_tx_mux",
		"",	gmac2_tx_mux,		CLK_MUX,	0 },
	{ JHB100_PER2CLK_GMAC2_TX_180_BUF,	"gmac2_tx_180_buf",
		"gmac2_tx_mux",		NULL,	CLK_INV,	0 },
	{ JHB100_PER2CLK_GMAC2_RX_MUX_DLY,	"gmac2_rx_mux_dly",
		"",	gmac2_rx_mux,		CLK_MUX,	0 },
	{ JHB100_PER2CLK_GMAC2_RX_180_BUF,	"gmac2_rx_180_buf",
		"gmac2_rx_mux_dly",	NULL,	CLK_INV,	0 },
	{ JHB100_PER2CLK_GMAC2_TXCK_MUX_DLY,	"gmac2_txck_mux_dly",
		"",	gmac2_txck_mux,		CLK_MUX,	0 },
	{ JHB100_PER2CLK_GMAC3_TX_125_MUX,	"gmac3_tx_125_mux",
		"",	gmac3_tx_125_mux,	CLK_MUX,	0 },
	{ JHB100_PER2CLK_GMAC3_RX_125_MUX,	"gmac3_rx_125_mux",
		"",	gmac3_rx_125_mux,	CLK_MUX,	0 },
	{ JHB100_PER2CLK_GMAC3_TX_DIV,		"gmac3_tx_div",
		"gmac3_tx_125_mux",	NULL,	CLK_DIVIDER,	6 },
	{ JHB100_PER2CLK_GMAC3_RX_DIV,		"gmac3_rx_div",
		"gmac3_rx_125_mux",	NULL,	CLK_DIVIDER,	6 },
	{ JHB100_PER2CLK_SENSORS_PERIPH2,	"sensors_periph2",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_FAN_TACH_PCLK,		"fan_tach_pclk",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER0_RMIIANDRGMII_TX_I,	"ether0_rmiiandrgmii_tx_i",
		"gmac2_tx_mux",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER0_RMIIANDRGMII_RX_I,	"ether0_rmiiandrgmii_rx_i",
		"gmac2_rx_mux_dly",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER0_RMIIANDRGMII_TX_180_I,	"ether0_rmiiandrgmii_tx_180_i",
		"gmac2_tx_180_buf",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER0_RMIIANDRGMII_RX_180_I,	"ether0_rmiiandrgmii_rx_180_i",
		"gmac2_rx_180_buf",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER0_RMIIANDRGMII_PTP_REF_I,	"ether0_rmiiandrgmii_ptp_ref_i",
		"per2_50",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER0_RMIIANDRGMII_RMII_I,	"ether0_rmiiandrgmii_rmii_i",
		"gmac2_rmii_mux_dly",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER0_RMIIANDRGMII_CSR_I,	"ether0_rmiiandrgmii_csr_i",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER0_RMIIANDRGMII_ACLK_I,	"ether0_rmiiandrgmii_aclk_i",
		"per2_300",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_RMIIANDRGMII_IOMUX_GMAC2_TXCK,	"rmiiandrgmii_iomux_gmac2_txck",
		"gmac2_txck_mux_dly",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_TX_I,	"ether1_sgmii_tx_i",
		"gmac3_tx_div",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_RX_I,	"ether1_sgmii_rx_i",
		"gmac3_rx_div",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_TX_125_I,	"ether1_sgmii_tx_125_i",
		"gmac3_tx_125_mux",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_RX_125_I,	"ether1_sgmii_rx_125_i",
		"gmac3_rx_125_mux",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_PTP_REF_I,	"ether1_sgmii_ptp_ref_i",
		"per2_50",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_CSR_I,	"ether1_sgmii_csr_i",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_ACLK_I,	"ether1_sgmii_aclk_i",
		"per2_300",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_PHY_PCLK_I,	"ether1_sgmii_phy_pclk_i",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_ETHER1_SGMII_REF_25_I,	"ether1_sgmii_ref_25_i",
		"osc",			NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_MAIN_ICG_EN_CAN0,	"main_icg_en_can0",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_MAIN_ICG_EN_CAN1,	"main_icg_en_can1",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_MAIN_ICG_EN_DMAC_1CH,	"main_icg_en_dmac_1ch",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_MAIN_ICG_EN_RTC_SCAN,	"main_icg_en_rtc_scan",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_MAIN_ICG_EN_ADC0,	"main_icg_en_adc0",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_MAIN_ICG_EN_ADC1,	"main_icg_en_adc1",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_MAIN_ICG_EN_GMAC2,	"main_icg_en_gmac2",
		"per2_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER2CLK_MAIN_ICG_EN_GMAC3,	"main_icg_en_gmac3",
		"per2_100",		NULL,	CLK_GATE,	0 },
};

static int jhb100_per2crg_probe(struct udevice *dev)
{
	int ret;
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	/* Make sure sys0crg driver is instantiated first. */
	ret = jhb100_clk_check_parent(DM_DRIVER_GET(sys0crg));
	if (ret)
		return ret;

	starfive_clk_init(reg, per2, per2crg_clk_info, ARRAY_SIZE(per2crg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(per2);

JHB100_CLK_OPS(per2);

static const struct udevice_id jhb100_per2crg_match[] = {
	{ .compatible = "starfive,jhb100-per2crg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(per2crg) = {
	.name = "clk-starfive-jhb100-per2",
	.id = UCLASS_CLK,
	.of_match = jhb100_per2crg_match,
	.probe = jhb100_per2crg_probe,
	.ops = &jhb100_per2_clk_ops,
	.bind = jhb100_clk_bind,
};
