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

static struct clk_info sys1crg_clk_info[] = {
	/* root */
	{ JHB100_SYS1CLK_APB_MAIN_SYS1,	"apb_main_sys1",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	/* sensor */
	{ JHB100_SYS1CLK_APB_SENSOR_ICG_BUF,	"apb_sensor_icg_buf",
		"apb_main_sys1",	NULL,	CLK_GATE,	0 },
	/* hostss1 */
	{ JHB100_SYS1CLK_GPIO_ESPI1_66,	"gpio_espi1_66",
		"pll2",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS1CLK_HOSTSS1_100,	"hostss1_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS1CLK_HOSTSS1_PHY_SCAN_1000_ICG_BUF,	"hostss1_phy_scan_1000_icg_buf",
		"pll1",			NULL,	CLK_GATE,	0 },
	/* vout */
	{ JHB100_SYS1CLK_VOUT_100,	"vout_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS1CLK_VOUT_PIX0,	"vout_pix0",
		"pll4",			NULL,	CLK_DIVIDER,	3 },
	{ JHB100_SYS1CLK_VOUT_PIX1,	"vout_pix1",
		"pll5",			NULL,	CLK_DIVIDER,	3 },
	/* bmcperiph3 */
	{ JHB100_SYS1CLK_BMCPER3_100,	"per3_100",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
	{ JHB100_SYS1CLK_BMCPER3_125,	"per3_125",
		"pll1",			NULL,	CLK_DIVIDER,	4 },
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
