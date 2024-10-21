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

static const char *apb_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "apb_main_sys2",
};

static const char *hostusb_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusb_100",
};

static const char *hostusbcmn_500_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusbcmn_500",
};

static const char *bmcper1_200_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per1_200",
};

static const char *bmcper1_250_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper1_250",
};

static const char *bmcper0_200_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper0_200",
};

static const char *bmcper0_125_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per0_125",
};

static const char *gpu0_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "gpu0_100",
};

static const char *gpu1_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "gpu1_100",
};

static struct clk_info sys2crg_clk_info[] = {
	/* root */
	{ JHB100_SYS2CLK_APB_MAIN_SYS2,	"apb_main_sys2",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_APB_OSC_SYS2,	"apb_osc_sys2",
		"",	apb_mux,		CLK_MUX,	0 },
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
	{ JHB100_SYS2CLK_HOSTUSBCMN_TARG,	"hostusbcmn_targ",
		"",	hostusb_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_HOSTUSBCMN_500,	"hostusbcmn_500",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS2CLK_HOSTUSBCMN_500_OSC,	"hostusbcmn_500_osc",
		"",	hostusbcmn_500_mux,	CLK_MUX,	0 },
	/* bmcperiph1 */
	{ JHB100_SYS2CLK_BMCPER1_200,	"per1_200",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS2CLK_BMCPER1_TARG,	"per1_targ",
		"",	bmcper1_200_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER1_250,	"bmcper1_250",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS2CLK_BMCPER1_250_OSC,	"bmcper1_250_osc",
		"",	bmcper1_250_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER1_143_DFT,	"bmcper1_143_dft",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_BMCPER1_143,	"per1_143",
		"bmcper1_143_dft",	NULL,	CLK_GATE,	0 },
	/* bmcperiph0 */
	{ JHB100_SYS2CLK_BMCPER0_200,	"bmcper0_200",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS2CLK_BMCPER0_TARG,	"per0_targ",
		"",	bmcper0_200_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER0_125,	"per0_125",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_BMCPER0_125_OSC,	"bmcper0_125_osc",
		"",	bmcper0_125_mux,	CLK_MUX,	0 },
	/* gpu0 */
	{ JHB100_SYS2CLK_GPU0_100,	"gpu0_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_GPU0_TARG,	"gpu0_targ",
		"",	gpu0_100_mux,		CLK_MUX,	0 },
	{ JHB100_SYS2CLK_GPU0_BUS_CLK,	"gpu0_bus_clk",
		"sys2_gpu0_init",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_GPU0_APB_CLK,	"gpu0_apb_clk",
		"gpu0_targ",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_GPU0_OSC_CLK,	"gpu0_osc_clk",
		"osc",			NULL,	CLK_GATE,	0 },
	/* gpu1 */
	{ JHB100_SYS2CLK_GPU1_100,	"gpu1_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_GPU1_TARG,	"gpu1_targ",
		"",	gpu1_100_mux,		CLK_MUX,	0 },
	{ JHB100_SYS2CLK_GPU1_BUS_CLK,	"gpu1_bus_clk",
		"sys2_gpu1_init",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYS2CLK_GPU1_APB_CLK,	"gpu1_apb_clk",
		"gpu1_targ",		NULL,	CLK_GATE,	0 },
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
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

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
