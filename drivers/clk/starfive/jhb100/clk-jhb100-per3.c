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

static const char *gmac1_tx_125_mux[MAX_NUM_PARENTS] = {
	[0] = "per3_gmac1_sgmii_tx",
	[1] = "per3_125",
};

static const char *gmac1_rx_125_mux[MAX_NUM_PARENTS] = {
	[0] = "per3_gmac1_sgmii_rx",
	[1] = "per3_125",
};

static const char *gmac0_rmii_mux[MAX_NUM_PARENTS] = {
	[0] = "gmac0_rmii_pll",
	[1] = "per3_gmac0_rmii_rclki",
};

static struct clk_info per3crg_clk_info[] = {
	{ JHB100_PER3CLK_300,			"per3_300",
		"per3_600",		NULL,	CLK_DIVIDER,	9 },
	{ JHB100_PER3CLK_200,			"per3_200",
		"per3_600",		NULL,	CLK_DIVIDER,	9 },
	{ JHB100_PER3CLK_GMAC1_PTP_REF,		"gmac1_ptp_ref",
		"per3_100",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER3CLK_GMAC1_TX_125_MUX,	"gmac1_tx_125_mux",
		"",	gmac1_tx_125_mux,	CLK_MUX,	0 },
	{ JHB100_PER3CLK_GMAC1_TX,		"gmac1_tx",
		"gmac1_tx_125_mux",	NULL,	CLK_DIVIDER,	6 },
	{ JHB100_PER3CLK_GMAC1_RX_125_MUX,	"gmac1_rx_125_mux",
		"",	gmac1_rx_125_mux,	CLK_MUX,	0 },
	{ JHB100_PER3CLK_GMAC1_RX,		"gmac1_rx",
		"gmac1_rx_125_mux",	NULL,	CLK_DIVIDER,	6 },
	{ JHB100_PER3CLK_GMAC0_PTP_REF,		"gmac0_ptp_ref",
		"per3_100",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER3CLK_GMAC0_RMII_PLL,	"gmac0_rmii_pll",
		"per3_100",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER3CLK_GMAC0_RMII_MUX,	"gmac0_rmii_mux",
		"",	gmac0_rmii_mux,		CLK_MUX,	0 },
	{ JHB100_PER3CLK_GMAC0_RMII_MUX_DIV2,	"gmac0_rmii_mux_div2",
		"gmac0_rmii_mux",	NULL,	CLK_DIVIDER,	5 },
	{ JHB100_PER3CLK_ETHER0_RMII_CLK_TX_I,	"ether0_rmii_clk_tx_i",
		"gmac0_rmii_mux_div2",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_RMII_CLK_RX_I,	"ether0_rmii_clk_rx_i",
		"gmac0_rmii_mux_div2",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_RMII_CLK_PTP_REF_I,	"ether0_rmii_clk_ptp_ref_i",
		"gmac0_ptp_ref",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_RMII_CLK_RMII_I,	"ether0_rmii_clk_rmii_i",
		"gmac0_rmii_mux",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_RMII_CLK_CSR_I,	"ether0_rmii_clk_csr_i",
		"per3_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_RMII_ACLK_I,	"ether0_rmii_aclk_i",
		"per3_300",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_GMAC0_RMII_RCLKO,	"gmac0_rmii_rclko",
		"gmac0_rmii_pll",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_CLK_TX_I,	"ether0_sgmii_clk_tx_i",
		"gmac1_tx",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_CLK_RX_I,	"ether0_sgmii_clk_rx_i",
		"gmac1_rx",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_CLK_TX_125_I,	"ether0_sgmii_clk_tx_125_i",
		"gmac1_tx_125_mux",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_CLK_RX_125_I,	"ether0_sgmii_clk_rx_125_i",
		"gmac1_rx_125_mux",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_CLK_PTP_REF_I,	"ether0_sgmii_clk_ptp_ref_i",
		"gmac1_ptp_ref",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_CLK_REF_25_I,	"ether0_sgmii_clk_ref_25_i",
		"osc",			NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_CLK_CSR_I,	"ether0_sgmii_clk_csr_i",
		"per3_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_ACLK_I,	"ether0_sgmii_aclk_i",
		"per3_300",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_ETHER0_SGMII_PHY_PCLK_I,	"ether0_sgmii_phy_pclk_i",
		"per3_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_SENSORS_PERIPH3,	"main_icg_en_sensors_periph3",
		"per3_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_PECI0,	"main_icg_en_peci0",
		"per3_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_PECI1,	"main_icg_en_peci1",
		"per3_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_GMAC0,	"main_icg_en_gmac0",
		"per3_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_GMAC1,	"main_icg_en_gmac1",
		"per3_100",		NULL,	CLK_GATE,	0 },
};

static int jhb100_per3crg_probe(struct udevice *dev)
{
	int ret;
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	/* Make sure sys0crg and sys1crg drivers are instantiated first. */
	ret = jhb100_clk_check_parent(DM_DRIVER_GET(sys0crg));
	if (ret)
		return ret;

	ret = jhb100_clk_check_parent(DM_DRIVER_GET(sys1crg));
	if (ret)
		return ret;

	starfive_clk_init(reg, per3, per3crg_clk_info, ARRAY_SIZE(per3crg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(per3);

JHB100_CLK_OPS(per3);

static const struct udevice_id jhb100_per3crg_match[] = {
	{ .compatible = "starfive,jhb100-per3crg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(per3crg) = {
	.name = "clk-starfive-jhb100-per3",
	.id = UCLASS_CLK,
	.of_match = jhb100_per3crg_match,
	.probe = jhb100_per3crg_probe,
	.ops = &jhb100_per3_clk_ops,
	.bind = jhb100_clk_bind,
};
