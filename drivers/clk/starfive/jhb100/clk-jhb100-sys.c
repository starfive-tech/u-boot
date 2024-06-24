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
	[1] = "apb_main",
};

static const char *bmcpcierp_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcpcierp_600",
};

static const char *bmcpcierp_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcpcierp_100",
};

static const char *hostss0_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostss0_100",
};

static const char *hostss0_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostss0_600",
};

static const char *bmcusb_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcusb_600",
};

static const char *bmcusb_200_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcusb_200",
};

static const char *vce_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "vce_600",
};

static const char *vce_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "vce_100",
};

static const char *bmcper2_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper2_600",
};

static const char *bmcper2_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper2_100",
};

static const char *bmcper2_400_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per2_400",
};

static const char *bmcper2_125_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per2_125",
};

static struct clk_info syscrg_clk_info[] = {
	/* root */
	{ JHB100_SYSCLK_APB_MAIN,	"apb_main",
		"pll1",		NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_APB_OSC,	"apb_osc",
		"",	apb_mux,	CLK_MUX,	0 },
	/* top noc */
	{ JHB100_SYSCLK_NCNOC0_600,	"ncnoc0_600",
		"pll0",		NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_NCNOC0_SYSTOP_CLK_NCNOC_DATA2,	"ncnoc0_systop_clk_ncnoc_data2",
		"ncnoc0_600",	NULL,	CLK_INV,	0 },
	/* debug */
	{ JHB100_SYSCLK_DEBUG_200,	"debug_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	/* sim apb */
	{ JHB100_SYSCLK_APB_SIM_APB,	"apb_sim_apb",
		"osc",		NULL,	CLK_GATE,	0 },
	/* bmcpcierp */
	{ JHB100_SYSCLK_BMCPCIERP_600,	"bmcpcierp_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYSCLK_BMCPCIERP_MAIN,	"bmcpcierp_main",
		"",	bmcpcierp_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_100,	"bmcpcierp_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYSCLK_BMCPCIERP_CFG,	"bmcpcierp_cfg",
		"",	bmcpcierp_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_PHY_SCAN_200,	"bmcpcierp_phy_scan_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYSCLK_BMCPCIERP_PHY_SCAN_500,	"bmcpcierp_phy_scan_500",
		"pll1",		NULL,	CLK_GDIV,	2 },
	{ JHB100_SYSCLK_BMCPCIERP_REF_CML,	"bmcpcierp_ref_cml",
		"pll1",		NULL,	CLK_DIVIDER,	4 },
	/* hostss0 */
	{ JHB100_SYSCLK_HOSTSS0_100,	"hostss0_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYSCLK_HOSTSS0_CFG,	"hostss0_cfg",
		"",	hostss0_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_HOSTSS0_600,	"hostss0_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYSCLK_HOSTSS0_DATA,	"hostss0_data",
		"",	hostss0_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_HOSTSS0_PHY_SCAN_200,	"hostss0_phy_scan_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYSCLK_HOSTSS0_PHY_SCAN_500,	"hostss0_phy_scan_500",
		"pll1",		NULL,	CLK_GDIV,	2 },
	{ JHB100_SYSCLK_HOSTSS0_REF_CML,	"hostss0_ref_cml",
		"pll1",		NULL,	CLK_DIVIDER,	4 },
	/* bmcusb */
	{ JHB100_SYSCLK_BMCUSB_600,	"bmcusb_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYSCLK_BMCUSB_INIT,	"bmcusb_init",
		"",	bmcusb_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCUSB_200,	"bmcusb_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYSCLK_BMCUSB_TARG,	"bmcusb_targ",
		"",	bmcusb_200_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCUSB_SCANCLK,	"bmcusb_scanclk",
		"pll0",		NULL,	CLK_GDIV,	3 },
	/* vce */
	{ JHB100_SYSCLK_VCE_600,	"vce_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYSCLK_VCE_INIT,	"vce_init",
		"",	vce_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_VCE_100,	"vce_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYSCLK_VCE_TARG,	"vce_targ",
		"",	vce_100_mux,	CLK_MUX,	0 },
	/* bmcperiph2 */
	{ JHB100_SYSCLK_BMCPER2_600,	"bmcper2_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYSCLK_BMCPER2_INIT,	"bmcper2_init",
		"",	bmcper2_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER2_100,	"bmcper2_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYSCLK_BMCPER2_TARG,	"per2_targ",
		"",	bmcper2_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER2_400,	"per2_400",
		"pll0",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYSCLK_BMCPER2_400_OSC,	"bmcper2_400_osc",
		"",	bmcper2_400_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER2_125,	"per2_125",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYSCLK_BMCPER2_125_OSC,	"bmcper2_125_osc",
		"",	bmcper2_125_mux,	CLK_MUX,	0 },
};

static int jhb100_syscrg_probe(struct udevice *dev)
{
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	starfive_clk_init(reg, sys, syscrg_clk_info, ARRAY_SIZE(syscrg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(sys);

JHB100_CLK_OPS(sys);

static const struct udevice_id jhb100_syscrg_match[] = {
	{ .compatible = "starfive,jhb100-syscrg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(syscrg) = {
	.name = "clk-starfive-jhb100-sys",
	.id = UCLASS_CLK,
	.of_match = jhb100_syscrg_match,
	.probe = jhb100_syscrg_probe,
	.ops = &jhb100_sys_clk_ops,
	.bind = jhb100_clk_bind,
};
