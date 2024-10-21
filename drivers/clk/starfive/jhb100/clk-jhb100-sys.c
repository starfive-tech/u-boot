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
	[1] = "apb_main_sys0",
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

static const char *hostss0_espi0_mux[MAX_NUM_PARENTS] = {
	[0] = "sys_espi0",
	[1] = "gpio_espi0_66",
};

static const char *bmcusb_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcusb_600",
};

static const char *bmcusb_200_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcusb_200",
};

static const char *bmccpuss_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "pll1",
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

static const char *hostss1_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostss1_600",
};

static const char *vout_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "vout_600",
};

static const char *bmcper3_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per3_600",
};

static const char *hostusb_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusb_600",
};

static const char *hostusbcmn_480_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "hostusbcmn_480",
};

static const char *bmcper1_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per1_600",
};

static const char *bmcper1_400_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per1_400",
};

static const char *bmcper1_800_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per1_800",
};

static const char *bmcper0_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper0_600",
};

static const char *bmcper0_400_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "per0_400",
};

static const char *bmcper0_800_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "bmcper0_800",
};

static const char *gpu0_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "gpu0_600",
};

static const char *gpu1_600_mux[MAX_NUM_PARENTS] = {
	[0] = "osc",
	[1] = "gpu1_600",
};

static struct clk_info syscrg_clk_info[] = {
	/* root */
	{ JHB100_SYSCLK_APB_MAIN_SYS0,	"apb_main_sys0",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_APB_OSC_SYS0,	"apb_osc_sys0",
		"",	apb_mux,		CLK_MUX,	0 },
	/* top noc 0 */
	{ JHB100_SYSCLK_NCNOC0_600,	"ncnoc0_600",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	/* sim apb */
	{ JHB100_SYSCLK_APB_SIM_APB_ICG_BUF,	"apb_sim_apb_icg_buf",
		"apb_osc_sys0",		NULL,	CLK_GATE,	0 },
	/* bmcpcierp */
	{ JHB100_SYSCLK_BMCPCIERP_600,	"bmcpcierp_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCPCIERP_MAIN,	"bmcpcierp_main",
		"",	bmcpcierp_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_100,	"bmcpcierp_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_BMCPCIERP_CFG,	"bmcpcierp_cfg",
		"",	bmcpcierp_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_PHY_SCAN_400_DFT,	"bmcpcierp_phy_scan_400_dft",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_PCIE_REF_CML,	"pcie_ref_cml",
		"pll0",			NULL,	CLK_DIVIDER,	5 },
	{ JHB100_SYSCLK_BMCPCIERP_OSC,	"bmcpcierp_osc",
		"osc",			NULL,	CLK_GATE,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_NCNOC_DATA_INIT,	"bmcpcierp_ncnoc_data_init",
		"bmcpcierp_main",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_NCNOC_CFG_INIT,	"bmcpcierp_ncnoc_cfg_init",
		"bmcpcierp_cfg",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_NCNOC_TARG,	"bmcpcierp_ncnoc_targ",
		"bmcpcierp_main",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_PCIE_PHY_SCAN_1000_DFT,	"bmcpcierp_pcie_phy_scan_1000_dft",
		"pll1",			NULL,	CLK_GATE,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_PCIE_PHY_SCAN_400_DFT,	"bmcpcierp_pcie_phy_scan_400_dft",
		"bmcpcierp_phy_scan_400_dft",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYSCLK_BMCPCIERP_PCU,	"bmcpcierp_pcu",
		"osc",			NULL,	CLK_GATE,	0 },
	{ JHB100_SYSCLK_U0_PCIE_REF_CML_CMOSIN,	"u0_pcie_ref_cml_cmosin",
		"pcie_ref_cml",		NULL,	CLK_GATE,	0 },
	/* hostss0 */
	{ JHB100_SYSCLK_HOSTSS0_100,	"hostss0_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_HOSTSS0_CFG,	"hostss0_cfg",
		"",	hostss0_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_HOSTSS0_600,	"hostss0_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_HOSTSS0_DATA,	"hostss0_data",
		"",	hostss0_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_HOSTSS0_PHY_SCAN_400,	"hostss0_phy_scan_400",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_GPIO_ESPI0_66,	"gpio_espi0_66",
		"pll2",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_ESPI0_EXT_DFT_MUX,	"espi0_ext_dft_mux",
		"",	hostss0_espi0_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_HOSTSS0_PCIE_PHY_SCAN_400_DFT,	"hostss0_pcie_phy_scan_400_dft",
		"hostss0_phy_scan_400",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYSCLK_HOSTSS0_PCIE_PHY_SCAN_1000_DFT,	"hostss0_pcie_phy_scan_1000_dft",
		"pll1",			NULL,	CLK_GATE,	0 },
	/* bmcusb */
	{ JHB100_SYSCLK_BMCUSB_600,	"bmcusb_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCUSB_INIT,	"bmcusb_init",
		"",	bmcusb_600_mux,		CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCUSB_200,	"bmcusb_200",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCUSB_TARG,	"bmcusb_targ",
		"",	bmcusb_200_mux,		CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCUSB_SCANCLK,	"bmcusb_scanclk",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCUSB_480M_SCANCLK,	"bmcusb_480m_scanclk",
		"bmcusb_scanclk",	NULL,	CLK_GATE,	0 },
	/* bmccpuss */
	{ JHB100_SYSCLK_BMCCPUSS_SYS_OSC,	"bmccpuss_sys_osc",
		"",	bmccpuss_mux,		CLK_GMUX,	0 },
	/* vce */
	{ JHB100_SYSCLK_VCE_600,	"vce_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_VCE_INIT,	"vce_init",
		"",	vce_600_mux,		CLK_MUX,	0 },
	{ JHB100_SYSCLK_VCE_100,	"vce_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_VCE_TARG,	"vce_targ",
		"",	vce_100_mux,		CLK_MUX,	0 },
	/* bmcperiph2 */
	{ JHB100_SYSCLK_BMCPER2_600,	"bmcper2_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCPER2_INIT,	"bmcper2_init",
		"",	bmcper2_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER2_100,	"bmcper2_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_BMCPER2_TARG,	"per2_targ",
		"",	bmcper2_100_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER2_400,	"per2_400",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_BMCPER2_400_OSC,	"bmcper2_400_osc",
		"",	bmcper2_400_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER2_125,	"per2_125",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_BMCPER2_125_OSC,	"bmcper2_125_osc",
		"",	bmcper2_125_mux,	CLK_MUX,	0 },
	/* top noc 1*/
	{ JHB100_SYSCLK_NCNOC1_600,	"ncnoc1_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	/* hostss1 */
	{ JHB100_SYSCLK_HOSTSS1_600,	"hostss1_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_HOSTSS1_DATA,	"hostss1_data",
		"",	hostss1_mux,		CLK_MUX,	0 },
	{ JHB100_SYSCLK_HOSTSS1_PHY_SCAN_400,	"hostss1_phy_scan_400",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_HOSTSS1_PHY_SCAN_400_ICG_BUF,	"hostss1_phy_scan_400_icg_buf",
		"hostss1_phy_scan_400",	NULL,	CLK_GATE,	0 },
	/* vout */
	{ JHB100_SYSCLK_VOUT_600,	"vout_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_VOUT_INIT,	"vout_init",
		"",	vout_600_mux,		CLK_MUX,	0 },
	{ JHB100_SYSCLK_VOUT_AUX,	"vout_aux",
		"pll0",			NULL,	CLK_DIVIDER,	8 },
	{ JHB100_SYSCLK_VOUT_SCAN_800_DFT,	"vout_scan_800_dft",
		"pll0",			NULL,	CLK_DIVIDER,	2 },
	/* bmcperiph3 */
	{ JHB100_SYSCLK_BMCPER3_600,	"per3_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCPER3_INIT,	"bmcper3_init",
		"",	bmcper3_600_mux,	CLK_MUX,	0 },
	/* hostusb */
	{ JHB100_SYSCLK_HOSTUSB_600,	"hostusb_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_HOSTUSB_INIT,	"hostusb_init",
		"",	hostusb_600_mux,	CLK_MUX,	0 },
	/* hostusbcmn */
	{ JHB100_SYSCLK_HOSTUSBCMN_480,	"hostusbcmn_480",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_HOSTUSBCMN_480_OSC,	"hostusbcmn_480_osc",
		"",	hostusbcmn_480_mux,	CLK_MUX,	0 },
	/* bmcperiph1 */
	{ JHB100_SYSCLK_BMCPER1_600,	"per1_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCPER1_INIT,	"per1_init",
		"",	bmcper1_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER1_400,	"per1_400",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_BMCPER1_400_OSC,	"bmcper1_400_osc",
		"",	bmcper1_400_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER1_800,	"per1_800",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCPER1_800_OSC,	"bmcper1_800_osc",
		"",	bmcper1_800_mux,	CLK_MUX,	0 },
	/* bmcperiph0 */
	{ JHB100_SYSCLK_BMCPER0_600,	"bmcper0_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCPER0_INIT,	"per0_init",
		"",	bmcper0_600_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER0_400,	"per0_400",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYSCLK_BMCPER0_400_OSC,	"bmcper0_400_osc",
		"",	bmcper0_400_mux,	CLK_MUX,	0 },
	{ JHB100_SYSCLK_BMCPER0_800,	"bmcper0_800",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_BMCPER1_800_OSC,	"per0_800_osc",
		"",	bmcper0_800_mux,	CLK_MUX,	0 },
	/* gpu0 */
	{ JHB100_SYSCLK_GPU0_600,	"gpu0_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_GPU0_INIT,	"sys2_gpu0_init",
		"",	gpu0_600_mux,		CLK_MUX,	0 },
	/* gpu1 */
	{ JHB100_SYSCLK_GPU1_600,	"gpu1_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYSCLK_GPU1_INIT,	"sys2_gpu1_init",
		"",	gpu1_600_mux,		CLK_MUX,	0 },
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
