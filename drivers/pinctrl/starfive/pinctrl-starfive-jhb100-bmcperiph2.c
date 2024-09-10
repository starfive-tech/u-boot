// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC bmcperiph2 controller
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_BMCPERIPH2_NGPIO			37
#define JHB100_BMCPERIPH2_PADCFG_BASE		0x0
#define JHB100_BMCPERIPH2_VSELCFG_BASE		0x94

/* registers */
#define JHB100_BMCPERIPH2_GPIO_O_SEL		0x0d0
#define JHB100_BMCPERIPH2_GPIO_OEN_SEL		0x0d8
#define JHB100_BMCPERIPH2_GPIOIN		0x0e0
#define JHB100_BMCPERIPH2_FUNC_SEL		0x0e8

#define JHB100_BMCPERIPH2_GPIOEN0		0x0f8
#define JHB100_BMCPERIPH2_GPIOEN1		0x0fc
#define JHB100_BMCPERIPH2_GPIOIS0		0x100
#define JHB100_BMCPERIPH2_GPIOIS1		0x104
#define JHB100_BMCPERIPH2_GPIOIC0		0x108
#define JHB100_BMCPERIPH2_GPIOIC1		0x10c
#define JHB100_BMCPERIPH2_GPIOIE0		0x110
#define JHB100_BMCPERIPH2_GPIOIE1		0x114
#define JHB100_BMCPERIPH2_GPIOIHL0		0x118
#define JHB100_BMCPERIPH2_GPIOIHL1		0x11c
#define JHB100_BMCPERIPH2_GPIOIBE0		0x120
#define JHB100_BMCPERIPH2_GPIOIBE1		0x124
#define JHB100_BMCPERIPH2_GPIOIEV0		0x128
#define JHB100_BMCPERIPH2_GPIOIEV1		0x12c

static const struct starfive_pinctrl_pin jhb100_bmcperiph2_pins[] = {
	STARFIVE_PINCTRL(0,	"BMCPERIPH2_GPIO0"),
	STARFIVE_PINCTRL(1,	"BMCPERIPH2_GPIO1"),
	STARFIVE_PINCTRL(2,	"BMCPERIPH2_GPIO2"),
	STARFIVE_PINCTRL(3,	"BMCPERIPH2_GPIO3"),
	STARFIVE_PINCTRL(4,	"BMCPERIPH2_GPIO4"),
	STARFIVE_PINCTRL(5,	"BMCPERIPH2_GPIO5"),
	STARFIVE_PINCTRL(6,	"BMCPERIPH2_GPIO6"),
	STARFIVE_PINCTRL(7,	"BMCPERIPH2_GPIO7"),
	STARFIVE_PINCTRL(8,	"BMCPERIPH2_GPIO8"),
	STARFIVE_PINCTRL(9,	"BMCPERIPH2_GPIO9"),
	STARFIVE_PINCTRL(10,	"BMCPERIPH2_GPIO10"),
	STARFIVE_PINCTRL(11,	"BMCPERIPH2_GPIO11"),
	STARFIVE_PINCTRL(12,	"BMCPERIPH2_GPIO12"),
	STARFIVE_PINCTRL(13,	"BMCPERIPH2_GPIO13"),
	STARFIVE_PINCTRL(14,	"BMCPERIPH2_GPIO14"),
	STARFIVE_PINCTRL(15,	"BMCPERIPH2_GPIO15"),
	STARFIVE_PINCTRL(16,	"BMCPERIPH2_GPIO16"),
	STARFIVE_PINCTRL(17,	"BMCPERIPH2_GPIO17"),
	STARFIVE_PINCTRL(18,	"BMCPERIPH2_GPIO18"),
	STARFIVE_PINCTRL(19,	"BMCPERIPH2_GPIO19"),
	STARFIVE_PINCTRL(20,	"BMCPERIPH2_GPIO20"),
	STARFIVE_PINCTRL(21,	"BMCPERIPH2_GPIO21"),
	STARFIVE_PINCTRL(22,	"BMCPERIPH2_GPIO22"),
	STARFIVE_PINCTRL(23,	"BMCPERIPH2_GPIO23"),
	STARFIVE_PINCTRL(24,	"BMCPERIPH2_GPIO24"),
	STARFIVE_PINCTRL(25,	"BMCPERIPH2_GPIO25"),
	STARFIVE_PINCTRL(26,	"BMCPERIPH2_GPIO26"),
	STARFIVE_PINCTRL(27,	"BMCPERIPH2_GPIO27"),
	STARFIVE_PINCTRL(28,	"BMCPERIPH2_GPIO28"),
	STARFIVE_PINCTRL(29,	"BMCPERIPH2_GPIO29"),
	STARFIVE_PINCTRL(30,	"BMCPERIPH2_GPIO30"),
	STARFIVE_PINCTRL(31,	"BMCPERIPH2_GPIO31"),
	STARFIVE_PINCTRL(32,	"BMCPERIPH2_GPIO32"),
	STARFIVE_PINCTRL(33,	"BMCPERIPH2_GPIO33"),
	STARFIVE_PINCTRL(34,	"BMCPERIPH2_GPIO34"),
	STARFIVE_PINCTRL(35,	"BMCPERIPH2_GPIO35"),
	STARFIVE_PINCTRL(36,	"BMCPERIPH2_GPIO36"),
	STARFIVE_PINCTRL(37,	"BMCPERIPH2_GPIO37"),
	STARFIVE_PINCTRL(38,	"BMCPERIPH2_GPIO38"),
	STARFIVE_PINCTRL(39,	"BMCPERIPH2_GPIO39"),
	STARFIVE_PINCTRL(40,	"BMCPERIPH2_GPIO40"),
	STARFIVE_PINCTRL(41,	"BMCPERIPH2_GPIO41"),
	STARFIVE_PINCTRL(42,	"BMCPERIPH2_GPIO42"),
	STARFIVE_PINCTRL(43,	"BMCPERIPH2_GPIO43"),
	STARFIVE_PINCTRL(44,	"BMCPERIPH2_GPIO44"),
	STARFIVE_PINCTRL(45,	"BMCPERIPH2_GPIO45"),
	STARFIVE_PINCTRL(46,	"BMCPERIPH2_GPIO46"),
	STARFIVE_PINCTRL(47,	"BMCPERIPH2_GPIO47"),
	STARFIVE_PINCTRL(48,	"BMCPERIPH2_GPIO48"),
	STARFIVE_PINCTRL(49,	"BMCPERIPH2_GPIO49"),
	STARFIVE_PINCTRL(50,	"BMCPERIPH2_GPIO50"),
	STARFIVE_PINCTRL(51,	"BMCPERIPH2_GPIO51"),
};

static const struct jhb100_gpio_func_sel
	jhb100_bmcperiph2_func_sel[ARRAY_SIZE(jhb100_bmcperiph2_pins)] = {
	[0]	= { 0x0e8,	0,	1 },
	[1]	= { 0x0e8,	2,	1 },
	[2]	= { 0x0e8,	4,	1 },
	[3]	= { 0x0e8,	6,	1 },
	[4]	= { 0x0e8,	8,	1 },
	[5]	= { 0x0e8,	10,	1 },
	[6]	= { 0x0e8,	12,	1 },
	[7]	= { 0x0e8,	14,	1 },
	[8]	= { 0x0e8,	16,	1 },
	[9]	= { 0x0e8,	18,	1 },
	[10]	= { 0x0e8,	20,	1 },
	[11]	= { 0x0e8,	22,	1 },
	[12]	= { 0x0e8,	24,	1 },
	[13]	= { 0x0e8,	26,	1 },
	[14]	= { 0x0e8,	28,	1 },
	[15]	= { 0x0e8,	30,	1 },
	[16]	= { 0x0ec,	0,	1 },
	[17]	= { 0x0ec,	2,	1 },
	[18]	= { 0x0ec,	4,	1 },
	[19]	= { 0x0ec,	6,	1 },
	[20]	= { 0x0ec,	8,	1 },
	[21]	= { 0x0ec,	10,	1 },
	[22]	= { 0x0ec,	12,	1 },
	[23]	= { 0x0ec,	14,	1 },
	[24]	= { 0x0ec,	16,	1 },
	[25]	= { 0x0ec,	18,	1 },
	[26]	= { 0x0ec,	20,	1 },
	[27]	= { 0x0ec,	22,	1 },
	[28]	= { 0x0ec,	24,	1 },
	[29]	= { 0x0ec,	26,	2 },
	[30]	= { 0x0ec,	28,	1 },
	[31]	= { 0x0ec,	30,	1 },
	[32]	= { 0x0f0,	0,	2 },
	[33]	= { 0x0f0,	2,	1 },
	[34]	= { 0x0f0,	4,	1 },
	[35]	= { 0x0f0,	6,	1 },
	[36]	= { 0x0f0,	8,	1 },
	[37]	= { 0x0f0,	10,	2 },
	[38]	= { 0x0f0,	12,	1 },
	[39]	= { 0x0f0,	14,	1 },
	[40]	= { 0x0f0,	16,	1 },
	[41]	= { 0x0f0,	18,	2 },
	[42]	= { 0x0f0,	20,	2 },
	[43]	= { 0x0f0,	22,	1 },
	[44]	= { 0x0f0,	24,	2 },
	[45]	= { 0x0f0,	26,	2 },
	[46]	= { 0x0f0,	28,	2 },
	[47]	= { 0x0f0,	30,	2 },
	[48]	= { 0x0f4,	0,	2 },
	[49]	= { 0x0f4,	2,	2 },
	[50]	= { 0x0f4,	4,	2 },
	[51]	= { 0x0f4,	6,	2 },
};

static void jhb100_bmcperiph2_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH2_GPIOEN0);
	writel(0U, priv->base + JHB100_BMCPERIPH2_GPIOEN1);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH2_GPIOIC0);
	writel(0U, priv->base + JHB100_BMCPERIPH2_GPIOIC1);
}

static int jhb100_bmcperiph2_set_one_pin_mux(struct udevice *dev, u32 pin,
					     u32 func, int gpioval)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	if (func)
		starfive_set_function(dev, pin, func);

	if (pin < priv->info->ngpios && func == 0)
		starfive_set_gpioval(dev, pin, gpioval);

	if (pin >= priv->info->ngpios)
		starfive_set_gmacvsel(dev, pin - priv->info->ngpios, gpioval);

	return 0;
}

static int jhb100_bmcperiph2_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_BMCPERIPH2_NGPIO)
		return JHB100_BMCPERIPH2_PADCFG_BASE;
	puts("Not a valid BMCPERIPH2 pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_bmcperiph2_pinctrl_info = {
	.pins				= jhb100_bmcperiph2_pins,
	.npins				= ARRAY_SIZE(jhb100_bmcperiph2_pins),
	.ngpios				= JHB100_BMCPERIPH2_NGPIO,
	.name				= "BMCPERIPH2_GPIO",
	.gpio_o_sel_reg_base		= JHB100_BMCPERIPH2_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_BMCPERIPH2_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_vsel_mask			= GENMASK(1, 0),
	.gpio_vselcfg_base		= JHB100_BMCPERIPH2_VSELCFG_BASE,
	.gpio_func_sel_reg_base		= JHB100_BMCPERIPH2_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_BMCPERIPH2_GPIOIN,
	.func_sel			= jhb100_bmcperiph2_func_sel,
	.gpio_init_hw			= jhb100_bmcperiph2_init_hw,
	.set_one_pinmux			= jhb100_bmcperiph2_set_one_pin_mux,
	.get_padcfg_base		= jhb100_bmcperiph2_get_padcfg_base,
};

static int jhb100_bmcperiph2_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_bmcperiph2_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph2",
		.data = (ulong)&jhb100_bmcperiph2_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_bmcperiph2_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-bmcperiph2",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_bmcperiph2_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_bmcperiph2_pinctrl_probe,
};
