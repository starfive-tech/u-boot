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

static const char *hostusb_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusb_600",
};

static const char *hostusb_200_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusb_200",
};

static const char *hostusb_100_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusb_100",
};

static const char *hostusbcmn_500_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusbcmn_500",
};

static const char *hostusbcmn_480_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusbcmn_480",
};

static const char *bmcper1_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper1_600",
};

static const char *bmcper1_200_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper1_200",
};

static const char *bmcper1_400_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per1_400",
};

static const char *bmcper1_250_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper1_250",
};

static const char *bmcper1_800_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per1_800",
};

static const char *bmcper0_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper0_600",
};

static const char *bmcper0_200_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper0_200",
};

static const char *bmcper0_400_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per0_400",
};

static const char *bmcper0_125_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per0_125",
};

static const char *pll6_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "pll6",
};

static struct clk_info sys2crg_clk_info[] = {
	/* root */
	{ JHB100_SYS2CLK_APB_MAIN_SYS2,	"apb_main_sys2",
		"pll1",		NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS2CLK_APB_OSC_SYS2,	"apb_osc_sys2",
		"",	apb_mux,	CLK_MUX,	0 },
	/* jtag mst*/
	{ JHB100_SYS2CLK_JTAGM_200,	"jtagm_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_JTAGM_100,	"jtagm_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	/* hostusbcmn */
	{ JHB100_SYS2CLK_HOSTUSB_600,	"hostusb_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_HOSTUSB_INIT,	"hostusb_init",
		"",	hostusb_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_HOSTUSB_200,	"hostusb_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_HOSTUSB_TARG,	"hostusb_targ",
		"",	hostusb_200_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_HOSTUSB_100,	"hostusb_100",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS2CLK_HOSTUSBCMN_TARG,	"hostusbcmn_targ",
		"",	hostusb_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_HOSTUSBCMN_500,	"hostusbcmn_500",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_HOSTUSBCMN_500_OSC,	"hostusbcmn_500_osc",
		"",	hostusbcmn_500_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_HOSTUSBCMN_480,	"hostusbcmn_480",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_HOSTUSBCMN_480_OSC,	"hostusbcmn_480_osc",
		"",	hostusbcmn_480_mux,	CLK_MUX,	0 },
	/* bmcperiph1 */
	{ JHB100_SYS2CLK_BMCPER1_600,	"bmcper1_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_BMCPER1_INIT,	"per1_init",
		"",	bmcper1_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER1_200,	"bmcper1_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_BMCPER1_TARG,	"per1_targ",
		"",	bmcper1_200_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER1_400,	"per1_400",
		"pll0",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS2CLK_BMCPER1_400_OSC,	"bmcper1_400_osc",
		"",	bmcper1_400_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_UFS_REF,	"ufs_ref",
		"pll7",		NULL,	CLK_GDIV,	5 },
	{ JHB100_SYS2CLK_BMCPER1_250,	"bmcper1_250",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_BMCPER1_250_OSC,	"bmcper1_250_osc",
		"",	bmcper1_250_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER1_143,	"bmcper1_143",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS2CLK_BMCPER1_800,	"per1_800",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_BMCPER1_800_OSC,	"bmcper1_800_osc",
		"",	bmcper1_800_mux,	CLK_MUX,	0 },
	/* bmcperiph0 */
	{ JHB100_SYS2CLK_BMCPER0_600,	"bmcper0_600",
		"pll0",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_BMCPER0_INIT,	"per0_init",
		"",	bmcper0_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER0_200,	"bmcper0_200",
		"pll1",		NULL,	CLK_GDIV,	3 },
	{ JHB100_SYS2CLK_BMCPER0_TARG,	"per0_targ",
		"",	bmcper0_200_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER0_400,	"per0_400",
		"pll0",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS2CLK_BMCPER0_400_OSC,	"bmcper0_400_osc",
		"",	bmcper0_400_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER0_125,	"per0_125",
		"pll1",		NULL,	CLK_GDIV,	4 },
	{ JHB100_SYS2CLK_BMCPER0_125_OSC,	"bmcper0_125_osc",
		"",	bmcper0_125_mux,	CLK_MUX,	0 },
	{ JHB100_SYS2CLK_BMCPER0_PLL6,		"bmcper0_pll6",
		"",	pll6_mux,	CLK_GMUX,	0 },
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
