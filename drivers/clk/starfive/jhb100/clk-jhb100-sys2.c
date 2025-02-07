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

static struct clk_info sys2crg_clk_info[] = {
	/* jtag mst*/
	{ JHB100_SYS2CLK_JTAGM0_200,	"jtagm0_200",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS2CLK_JTAGM1_200,	"jtagm1_200",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS2CLK_JTAGM0_100,	"jtagm0_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_JTAGM1_100,	"jtagm1_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_JTAGM0_ATPG_TCLOCK,	"jtagm0_atpg_tclock",
		"jtagm0_100",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_SYS2CLK_JTAGM1_ATPG_TCLOCK,	"jtagm1_atpg_tclock",
		"jtagm1_100",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_SYS2CLK_JTAG0_MST_WRAP_HCLK,	"jtag0_mst_wrap_hclk",
		"jtagm0_200",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_JTAG0_MST_WRAP_CLK_JTAG,	"jtag0_mst_wrap_clk_jtag",
		"jtagm0_200",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_JTAG0_MST_WRAP_APB_PCLK,	"jtag0_mst_wrap_apb_pclk",
		"jtagm0_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_JTAG0_MST_WRAP_ATPG_TCLOCK,	"jtag0_mst_wrap_atpg_tclock",
		"jtagm0_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_JTAG1_MST_WRAP_HCLK,	"jtag1_mst_wrap_hclk",
		"jtagm1_200",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_JTAG1_MST_WRAP_CLK_JTAG,	"jtag1_mst_wrap_clk_jtag",
		"jtagm1_200",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_JTAG1_MST_WRAP_APB_PCLK,	"jtag1_mst_wrap_apb_pclk",
		"jtagm1_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_JTAG1_MST_WRAP_ATPG_TCLOCK,	"jtag1_mst_wrap_atpg_tclock",
		"jtagm1_100",		NULL,	CLK_GATE,	0 },
	/* hostusbcmn */
	{ JHB100_SYS2CLK_HOSTUSB_100,	"hostusb_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_HOSTUSBCMN_500,	"hostusbcmn_500",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	/* bmcperiph1 */
	{ JHB100_SYS2CLK_BMCPER1_200,	"per1_200",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS2CLK_BMCPER1_250,	"per1_250",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS2CLK_BMCPER1_143,	"per1_143",
		"pll1",			NULL,	CLK_GATE,	0 },
	/* bmcperiph0 */
	{ JHB100_SYS2CLK_BMCPER0_200,	"per0_200_init",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	/* gpu0 */
	{ JHB100_SYS2CLK_GPU0_100,	"gpu0_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_GPU0_BUS_CLK,	"gpu0_bus_clk",
		"sys2_gpu0_600",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_GPU0_APB_CLK,	"gpu0_apb_clk",
		"gpu0_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_GPU0_OSC_CLK,	"gpu0_osc_clk",
		"osc",			NULL,	CLK_GATE,	0 },
	/* gpu1 */
	{ JHB100_SYS2CLK_GPU1_100,	"gpu1_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_GPU1_BUS_CLK,	"gpu1_bus_clk",
		"sys2_gpu1_600",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_GPU1_APB_CLK,	"gpu1_apb_clk",
		"gpu1_100",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_GPU1_OSC_CLK,	"gpu1_osc_clk",
		"osc",			NULL,	CLK_GATE,	0 },
	/* main icg */
	{ JHB100_SYS2CLK_MAIN_ICG_EN_JTAG0,	"main_icg_en_jtag0",
		"jtagm0_200",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_MAIN_ICG_EN_JTAG1,	"main_icg_en_jtag1",
		"jtagm1_200",		NULL,	CLK_GATE,	0 },
};

static int jhb100_sys2crg_probe(struct udevice *dev)
{
	int ret;
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	/* Make sure sys0crg driver is instantiated first. */
	ret = jhb100_clk_check_parent(DM_DRIVER_GET(sys0crg));
	if (ret)
		return ret;

	starfive_clk_init(reg, sys2, sys2crg_clk_info, ARRAY_SIZE(sys2crg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(sys2);

JHB100_CLK_OPS(sys2);

static const struct udevice_id jhb100_sys2crg_match[] = {
	{ .compatible = "starfive,jhb100-sys2crg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(sys2crg) = {
	.name = "clk-starfive-jhb100-sys2",
	.id = UCLASS_CLK,
	.of_match = jhb100_sys2crg_match,
	.probe = jhb100_sys2crg_probe,
	.ops = &jhb100_sys2_clk_ops,
	.bind = jhb100_clk_bind,
};
