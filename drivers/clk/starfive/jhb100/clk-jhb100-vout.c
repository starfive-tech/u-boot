// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 *
 */

 #include "clk.h"
 #include "clk-starfive-common.h"
 #include <dt-bindings/clock/starfive,jhb100-crg.h>
 #include <linux/clk-provider.h>

static struct clk_info voutcrg_clk_info[] = {
	{ JHB100_VOUTCLK_U0_DC8000_ACLK_DIV, "u0_dc8000_aclk_div",
		"vout_600",		NULL,	CLK_DIVIDER,	3 },
	{ JHB100_VOUTCLK_U1_DC8000_ACLK_DIV, "u1_dc8000_aclk_div",
		"vout_600",		NULL,	CLK_DIVIDER,	3 },
	{ JHB100_VOUTCLK_U0_DC8000_CLK_DIV, "u0_dc8000_clk_div",
		"vout_600",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_VOUTCLK_U1_DC8000_CLK_DIV, "u1_dc8000_clk_div",
		"vout_600",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_VOUTCLK_U0_DC8000_ACLK, "u0_dc8000_aclk",
		"u0_dc8000_aclk_div",	NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_U0_DC8000_CLK, "u0_dc8000_clk",
		"u0_dc8000_clk_div",	NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_U0_DC8000_PIXELCLK0, "u0_dc8000_pixelclk0",
		"vout_pix0",		NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_U1_DC8000_ACLK, "u1_dc8000_aclk",
		"u1_dc8000_aclk_div",	NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_U1_DC8000_CLK, "u1_dc8000_clk",
		"u1_dc8000_clk_div",	NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_U1_DC8000_PIXELCLK0, "u1_dc8000_pixelclk0",
		"vout_pix1",		NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_MAIN_ICG_EN_SENSORS_VOUT, "main_icg_en_sensors_vout",
		"vout_600",		NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_MAIN_ICG_EN_U0_DC8000, "main_icg_en_u0_dc8000",
		"vout_600",		NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_MAIN_ICG_EN_U0_DC8000_SENSOR, "main_icg_en_u0_dc8000_sensor",
		"vout_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_MAIN_ICG_EN_U1_DC8000, "main_icg_en_u1_dc8000",
		"vout_600",		NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_MAIN_ICG_EN_U1_DC8000_SENSOR, "main_icg_en_u1_dc8000_sensor",
		"vout_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_MAIN_ICG_EN_DP_PHY_PCLK, "main_icg_en_dp_phy_pclk",
		"vout_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_VOUTCLK_MAIN_ICG_EN_DP_PHY_SCAN, "main_icg_en_dp_phy_scan",
		"vout_600",		NULL,	CLK_GATE,	0 },
};

static int jhb100_voutcrg_probe(struct udevice *dev)
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

	starfive_clk_init(reg, vout, voutcrg_clk_info, ARRAY_SIZE(voutcrg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(vout);

JHB100_CLK_OPS(vout);

static const struct udevice_id jhb100_voutcrg_match[] = {
	{ .compatible = "starfive,jhb100-voutcrg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(voutcrg) = {
	.name = "clk-starfive-jhb100-vout",
	.id = UCLASS_CLK,
	.of_match = jhb100_voutcrg_match,
	.probe = jhb100_voutcrg_probe,
	.ops = &jhb100_vout_clk_ops,
	.bind = jhb100_clk_bind,
	.flags = DM_FLAG_PRE_RELOC,
};
