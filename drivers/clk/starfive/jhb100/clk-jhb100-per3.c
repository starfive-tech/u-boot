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

static const char *rmii_mux[MAX_NUM_PARENTS] = {
	[0] = "per3_bus",
	[1] = "per3_gmac0_rmii_rclki",
};

static struct clk_info per3crg_clk_info[] = {
	{ JHB100_PER3CLK_BUS,	"per3_bus",
		"per3_init",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_125M,	"per3_125m",
		"per3_125",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_BUS_100M,	"per3_bus_100m",
		"per3_targ",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_RMII_GMAC0,	"rmii_gmac0",
		"per3_bus",	NULL,	CLK_GDIV,	4 },
	{ JHB100_PER3CLK_RMII_GMAC1,	"rmii_gmac1",
		"per3_bus",	NULL,	CLK_GDIV,	4 },
	{ JHB100_PER3CLK_GMAC0_AXI,	"gmac0_axi",
		"per3_bus",	NULL,	CLK_GDIV,	2 },
	{ JHB100_PER3CLK_GMAC1_AXI,	"gmac1_axi",
		"per3_bus",	NULL,	CLK_GDIV,	2 },
	{ JHB100_PER3CLK_APB_GMAC0,	"apb_gmac0",
		"per3_bus",	NULL,	CLK_GDIV,	3 },
	{ JHB100_PER3CLK_APB_GMAC1,	"apb_gmac1",
		"per3_bus",	NULL,	CLK_GDIV,	3 },
	{ JHB100_PER3CLK_APB_SENSORS_PD,	"apb_sensors_pd",
		"per3_bus",	NULL,	CLK_GDIV,	3 },
	{ JHB100_PER3CLK_APB_SYSCON,	"apb_syscon",
		"per3_125",	NULL,	CLK_DIVIDER,	3 },
	{ JHB100_PER3CLK_APB_SECURE_SYSCON,	"apb_secure_syscon",
		"per3_init",	NULL,	CLK_DIVIDER,	3 },
	{ JHB100_PER3CLK_IOMUX,	"iomux",
		"per3_init",	NULL,	CLK_DIVIDER,	3 },
	{ JHB100_PER3CLK_RMII_MUXED_50M,	"rmii_muxed_50m",
		"",	rmii_mux,	CLK_MUX,	0 },
	{ JHB100_PER3CLK_RMII_DIV2,	"rmii_div2",
		"rmii_muxed_50m",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER3CLK_CRG_PCLK,	"crg_pclk",
		"per3_init",	NULL,	CLK_DIVIDER,	3 },
	{ JHB100_PER3CLK_ETHER0_SGMII_TX_125_I,	"ether0_sgmii_tx_125_i",
		"per3_125",	NULL,	CLK_DIVIDER,	8 },
	{ JHB100_PER3CLK_ETHER0_SGMII_CSR_I,	"ether0_sgmii_csr_i",
		"apb_gmac1",	NULL,	CLK_DIVIDER,	8 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_BUS,	"main_icg_en_bus",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_125M,	"main_icg_en_125m",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_BUS_100M,	"main_icg_en_bus_100m",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_CRG_SECURE_I,	"main_icg_en_crg_secure_i",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_GMAC0_RMII_I,	"main_icg_en_gmac0_rmii_i",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_GMAC1_RMII_I,	"main_icg_en_gmac1_rmii_i",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_GMAC0_AXI_I,	"main_icg_en_gmac0_axi_i",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_GMAC1_AXI_I,	"main_icg_en_gmac1_axi_i",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_PECI0_I,	"main_icg_en_peci0_i",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_APB_GMAC0,	"main_icg_en_apb_gmac0",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_APB_GMAC1,	"main_icg_en_apb_gmac1",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_APB_PECI0,	"main_icg_en_apb_peci0",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_APB_SENSORS_PD,	"main_icg_en_apb_sensors_pd",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_GMAC1_RX_I,	"main_icg_en_gmac1_rx_i",
		"per3_bus",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER3CLK_MAIN_ICG_EN_GMAC1_TX_I,	"main_icg_en_gmac1_tx_i",
		"per3_bus",	NULL,	CLK_GATE,	0 },
};

static int jhb100_per3crg_probe(struct udevice *dev)
{
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

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
