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
	[1] = "apb_main_sys1",
};

static const char *hostss1_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostss1_100",
};

static const char *hostss1_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostss1_600",
};

static const char *gpu0_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "gpu0_600",
};

static const char *gpu0_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "gpu0_100",
};

static const char *gpu1_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "gpu1_600",
};

static const char *gpu1_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "gpu1_100",
};

static const char *vout_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "vout_600",
};

static const char *vout_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "vout_100",
};

static const char *bmcper3_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper3_600",
};

static const char *bmcper3_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper3_100",
};

static const char *bmcper3_125_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per3_125",
};

static struct clk_info sys1crg_clk_info[] = {
	/* root */
	{ JHB100_SYS1CLK_APB_MAIN_SYS1,	"apb_main_sys1",
		"pll1",		NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS1CLK_APB_OSC_SYS1,	"apb_osc_sys1",
		"",	apb_mux,	CLK_MUX,	0 },
	/* top noc*/
	{ JHB100_SYS1CLK_NCNOC1_600,	"ncnoc1_600",
		"pll0",		NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS1CLK_NCNOC1_200,	"ncnoc1_200",
		"pll1",		NULL,	CLK_DIVIDER,	3 },
	/* bcu */
	{ JHB100_SYS1CLK_BCU0_PCLK,	"bcu0_pclk",
		"osc",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS1CLK_NCNOC_SYSTOP_CLK_BCU0,	"ncnoc_systop_clk_bcu0",
		"bcu0_pclk",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYS1CLK_BCU0_DFT_BISR,	"bcu0_dft_bisr",
		"osc",		NULL,	CLK_GATE,	0 },
	/* hostss1 */
	{ JHB100_SYS1CLK_HOSTSS1_100,	"hostss1_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS1CLK_HOSTSS1_CFG,	"hostss1_cfg",
		"",	hostss1_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYS1CLK_HOSTSS1_600,	"hostss1_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS1CLK_HOSTSS1_DATA,	"hostss1_data",
		"",	hostss1_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYS1CLK_HOSTSS1_PHY_SCAN_200,	"hostss1_phy_scan_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS1CLK_HOSTSS1_PHY_SCAN_500,	"hostss1_phy_scan_500",
		"pll1",		NULL,	CLK_GDIV,	2 },
	{ JHB100_SYS1CLK_HOSTSS1_REF_CML,	"hostss1_ref_cml",
		"pll1",		NULL,	CLK_DIVIDER,	4 },
	/* gpu0 */
	{ JHB100_SYS1CLK_GPU0_600,	"gpu0_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS1CLK_GPU0_INIT,	"gpu0_init",
		"",	gpu0_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYS1CLK_GPU0_100,	"gpu0_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS1CLK_GPU0_TARG,	"gpu0_targ",
		"",	gpu0_100_mux,	CLK_MUX,	0 },
	/* gpu1 */
	{ JHB100_SYS1CLK_GPU1_600,	"gpu1_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS1CLK_GPU1_INIT,	"gpu1_init",
		"",	gpu1_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYS1CLK_GPU1_100,	"gpu1_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS1CLK_GPU1_TARG,	"gpu1_targ",
		"",	gpu1_100_mux,	CLK_MUX,	0 },
	/* vout */
	{ JHB100_SYS1CLK_VOUT_600,	"vout_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS1CLK_VOUT_INIT,	"vout_init",
		"",	vout_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYS1CLK_VOUT_100,	"vout_100",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS1CLK_VOUT_TARG,	"vout_targ",
		"",	vout_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYS1CLK_VOUT_AUX,	"vout_aux",
		"pll0",		NULL,	CLK_DIVIDER,	8 },
	{ JHB100_SYS1CLK_VOUT_SCAN_1000,	"vout_scan_1000",
		"pll1",		NULL,	CLK_GATE,	0 },
	{ JHB100_SYS1CLK_VOUT_SCAN_800,	"vout_scan_800",
		"pll0",		NULL,	CLK_GDIV,	3 },
	/* bmcperiph3 */
	{ JHB100_SYS1CLK_BMCPER3_600,	"bmcper3_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS1CLK_BMCPER3_INIT,	"per3_init",
		"",	bmcper3_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYS1CLK_BMCPER3_100,	"bmcper3_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS1CLK_BMCPER3_TARG,	"per3_targ",
		"",	bmcper3_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYS1CLK_BMCPER3_125,	"per3_125",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS1CLK_BMCPER3_125_OSC,	"bmcper3_125_osc",
		"",	bmcper3_125_mux,	CLK_MUX,	0 },
};

static int jhb100_sys1crg_probe(struct udevice *dev)
{
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	starfive_clk_init(reg, sys1, sys1crg_clk_info, ARRAY_SIZE(sys1crg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(sys1);

JHB100_CLK_OPS(sys1);

static const struct udevice_id jhb100_sys1crg_match[] = {
	{ .compatible = "starfive,jhb100-sys1crg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(sys1crg) = {
	.name = "clk-starfive-jhb100-sys1",
	.id = UCLASS_CLK,
	.of_match = jhb100_sys1crg_match,
	.probe = jhb100_sys1crg_probe,
	.ops = &jhb100_sys1_clk_ops,
	.bind = jhb100_clk_bind,
};
