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

static struct clk_info sys0crg_clk_info[] = {
	/* bmcpcierp */
	{ JHB100_SYS0CLK_BMCPCIERP_600,	"bmcpcierp_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_BMCPCIERP_100,	"bmcpcierp_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS0CLK_PCIE_REF_CML,	"pcie_ref_cml",
		"pll0",			NULL,	CLK_DIVIDER,	5 },
	{ JHB100_SYS0CLK_BMCPCIERP_NCNOC_DATA_INIT,	"bmcpcierp_ncnoc_data_init",
		"bmcpcierp_600",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYS0CLK_BMCPCIERP_NCNOC_CFG_INIT,	"bmcpcierp_ncnoc_cfg_init",
		"bmcpcierp_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYS0CLK_BMCPCIERP_NCNOC_TARG,	"bmcpcierp_ncnoc_targ",
		"bmcpcierp_600",	NULL,	CLK_GATE,	0 },
	{ JHB100_SYS0CLK_BMCPCIERP_PCU,	"bmcpcierp_pcu",
		"osc",			NULL,	CLK_GATE,	0 },
	/* hostss0 */
	{ JHB100_SYS0CLK_HOSTSS0_100,	"hostss0_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS0CLK_HOSTSS0_600,	"hostss0_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_HOSTSS0_PHY_SCAN_400,	"hostss0_phy_scan_400",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_GPIO_ESPI0_66,	"gpio_espi0_66",
		"pll2",			NULL,	CLK_DIVIDER,	4 },
	/* bmcusb */
	{ JHB100_SYS0CLK_BMCUSB_600,	"bmcusb_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_BMCUSB_200,	"bmcusb_200",
		"pll1",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_BMCUSB_SCANCLK,	"bmcusb_scanclk",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_BMCUSB_480M_SCANCLK,	"bmcusb_480m_scanclk",
		"bmcusb_scanclk",	NULL,	CLK_GATE,	0 },
	/* vce */
	{ JHB100_SYS0CLK_VCE_600,	"vce_600",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS0CLK_VCE_100,	"vce_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	/* bmcperiph2 */
	{ JHB100_SYS0CLK_BMCPER2_600,	"per2_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_BMCPER2_100,	"per2_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS0CLK_BMCPER2_400,	"per2_400",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS0CLK_BMCPER2_125,	"per2_125",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	/* hostss1 */
	{ JHB100_SYS0CLK_HOSTSS1_600,	"hostss1_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_HOSTSS1_PHY_SCAN_400,	"hostss1_phy_scan_400",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF,	"hostss1_phy_scan_400_icg_buf",
		"hostss1_phy_scan_400",	NULL,	CLK_GATE,	0 },
	/* npu */
	{ JHB100_SYS0CLK_NPU_600,	"sys1_npu_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	/* vout */
	{ JHB100_SYS0CLK_VOUT_600,	"vout_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_VOUT_AUX,	"vout_aux",
		"pll0",			NULL,	CLK_DIVIDER,	8 },
	/* bmcperiph3 */
	{ JHB100_SYS0CLK_BMCPER3_600,	"per3_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	/* hostusb */
	{ JHB100_SYS0CLK_HOSTUSB_600,	"hostusb_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	/* hostusbcmn */
	{ JHB100_SYS0CLK_HOSTUSBCMN_480,	"hostusbcmn_480",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	/* bmcperiph1 */
	{ JHB100_SYS0CLK_BMCPER1_600,	"per1_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_BMCPER1_800,	"per1_800",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	/* bmcperiph0 */
	{ JHB100_SYS0CLK_BMCPER0_600,	"per0_600",
		"pll0",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS0CLK_BMCPER0_400,	"per0_400",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS0CLK_BMCPER0_800,	"per0_800",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	/* gpu0 */
	{ JHB100_SYS0CLK_GPU0_600,	"sys2_gpu0_600",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
	/* gpu1 */
	{ JHB100_SYS0CLK_GPU1_600,	"sys2_gpu1_600",
		"pll0",			NULL,	CLK_DIVIDER,	4 },
};

static int jhb100_sys0crg_probe(struct udevice *dev)
{
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	starfive_clk_init(reg, sys, sys0crg_clk_info, ARRAY_SIZE(sys0crg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(sys);

JHB100_CLK_OPS(sys);

static const struct udevice_id jhb100_sys0crg_match[] = {
	{ .compatible = "starfive,jhb100-sys0crg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(sys0crg) = {
	.name = "clk-starfive-jhb100-sys0",
	.id = UCLASS_CLK,
	.of_match = jhb100_sys0crg_match,
	.probe = jhb100_sys0crg_probe,
	.ops = &jhb100_sys_clk_ops,
	.bind = jhb100_clk_bind,
};
