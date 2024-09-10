// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC bmcperiph0 controller
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_BMCPERIPH0_NGPIO			59
#define JHB100_BMCPERIPH0_PADCFG_BASE		0x0

/* registers */
#define JHB100_BMCPERIPH0_GPIO_O_SEL		0x0ec
#define JHB100_BMCPERIPH0_GPIO_OEN_SEL		0x0f4
#define JHB100_BMCPERIPH0_GPIOIN		0x0fc
#define JHB100_BMCPERIPH0_FUNC_SEL		0x104

#define JHB100_BMCPERIPH0_GPIOEN0		0x114
#define JHB100_BMCPERIPH0_GPIOEN1		0x118
#define JHB100_BMCPERIPH0_GPIOIS0		0x11c
#define JHB100_BMCPERIPH0_GPIOIS1		0x120
#define JHB100_BMCPERIPH0_GPIOIC0		0x124
#define JHB100_BMCPERIPH0_GPIOIC1		0x128
#define JHB100_BMCPERIPH0_GPIOIE0		0x12c
#define JHB100_BMCPERIPH0_GPIOIE1		0x130
#define JHB100_BMCPERIPH0_GPIOIHL0		0x134
#define JHB100_BMCPERIPH0_GPIOIHL1		0x138
#define JHB100_BMCPERIPH0_GPIOIBE0		0x13c
#define JHB100_BMCPERIPH0_GPIOIBE1		0x140
#define JHB100_BMCPERIPH0_GPIOIEV0		0x144
#define JHB100_BMCPERIPH0_GPIOIEV1		0x148

static const struct starfive_pinctrl_pin jhb100_bmcperiph0_pins[] = {
	STARFIVE_PINCTRL(0,	"BMCPERIPH0_GPIO0"),
	STARFIVE_PINCTRL(1,	"BMCPERIPH0_GPIO1"),
	STARFIVE_PINCTRL(2,	"BMCPERIPH0_GPIO2"),
	STARFIVE_PINCTRL(3,	"BMCPERIPH0_GPIO3"),
	STARFIVE_PINCTRL(4,	"BMCPERIPH0_GPIO4"),
	STARFIVE_PINCTRL(5,	"BMCPERIPH0_GPIO5"),
	STARFIVE_PINCTRL(6,	"BMCPERIPH0_GPIO6"),
	STARFIVE_PINCTRL(7,	"BMCPERIPH0_GPIO7"),
	STARFIVE_PINCTRL(8,	"BMCPERIPH0_GPIO8"),
	STARFIVE_PINCTRL(9,	"BMCPERIPH0_GPIO9"),
	STARFIVE_PINCTRL(10,	"BMCPERIPH0_GPIO10"),
	STARFIVE_PINCTRL(11,	"BMCPERIPH0_GPIO11"),
	STARFIVE_PINCTRL(12,	"BMCPERIPH0_GPIO12"),
	STARFIVE_PINCTRL(13,	"BMCPERIPH0_GPIO13"),
	STARFIVE_PINCTRL(14,	"BMCPERIPH0_GPIO14"),
	STARFIVE_PINCTRL(15,	"BMCPERIPH0_GPIO15"),
	STARFIVE_PINCTRL(16,	"BMCPERIPH0_GPIO16"),
	STARFIVE_PINCTRL(17,	"BMCPERIPH0_GPIO17"),
	STARFIVE_PINCTRL(18,	"BMCPERIPH0_GPIO18"),
	STARFIVE_PINCTRL(19,	"BMCPERIPH0_GPIO19"),
	STARFIVE_PINCTRL(20,	"BMCPERIPH0_GPIO20"),
	STARFIVE_PINCTRL(21,	"BMCPERIPH0_GPIO21"),
	STARFIVE_PINCTRL(22,	"BMCPERIPH0_GPIO22"),
	STARFIVE_PINCTRL(23,	"BMCPERIPH0_GPIO23"),
	STARFIVE_PINCTRL(24,	"BMCPERIPH0_GPIO24"),
	STARFIVE_PINCTRL(25,	"BMCPERIPH0_GPIO25"),
	STARFIVE_PINCTRL(26,	"BMCPERIPH0_GPIO26"),
	STARFIVE_PINCTRL(27,	"BMCPERIPH0_GPIO27"),
	STARFIVE_PINCTRL(28,	"BMCPERIPH0_GPIO28"),
	STARFIVE_PINCTRL(29,	"BMCPERIPH0_GPIO29"),
	STARFIVE_PINCTRL(30,	"BMCPERIPH0_GPIO30"),
	STARFIVE_PINCTRL(31,	"BMCPERIPH0_GPIO31"),
	STARFIVE_PINCTRL(32,	"BMCPERIPH0_GPIO32"),
	STARFIVE_PINCTRL(33,	"BMCPERIPH0_GPIO33"),
	STARFIVE_PINCTRL(34,	"BMCPERIPH0_GPIO34"),
	STARFIVE_PINCTRL(35,	"BMCPERIPH0_GPIO35"),
	STARFIVE_PINCTRL(36,	"BMCPERIPH0_GPIO36"),
	STARFIVE_PINCTRL(37,	"BMCPERIPH0_GPIO37"),
	STARFIVE_PINCTRL(38,	"BMCPERIPH0_GPIO38"),
	STARFIVE_PINCTRL(39,	"BMCPERIPH0_GPIO39"),
	STARFIVE_PINCTRL(40,	"BMCPERIPH0_GPIO40"),
	STARFIVE_PINCTRL(41,	"BMCPERIPH0_GPIO41"),
	STARFIVE_PINCTRL(42,	"BMCPERIPH0_GPIO42"),
	STARFIVE_PINCTRL(43,	"BMCPERIPH0_GPIO43"),
	STARFIVE_PINCTRL(44,	"BMCPERIPH0_GPIO44"),
	STARFIVE_PINCTRL(45,	"BMCPERIPH0_GPIO45"),
	STARFIVE_PINCTRL(46,	"BMCPERIPH0_GPIO46"),
	STARFIVE_PINCTRL(47,	"BMCPERIPH0_GPIO47"),
	STARFIVE_PINCTRL(48,	"BMCPERIPH0_GPIO48"),
	STARFIVE_PINCTRL(49,	"BMCPERIPH0_GPIO49"),
	STARFIVE_PINCTRL(50,	"BMCPERIPH0_GPIO50"),
	STARFIVE_PINCTRL(51,	"BMCPERIPH0_GPIO51"),
	STARFIVE_PINCTRL(52,	"BMCPERIPH0_GPIO52"),
	STARFIVE_PINCTRL(53,	"BMCPERIPH0_GPIO53"),
	STARFIVE_PINCTRL(54,	"BMCPERIPH0_GPIO54"),
	STARFIVE_PINCTRL(55,	"BMCPERIPH0_GPIO55"),
	STARFIVE_PINCTRL(56,	"BMCPERIPH0_GPIO56"),
	STARFIVE_PINCTRL(57,	"BMCPERIPH0_GPIO57"),
	STARFIVE_PINCTRL(58,	"BMCPERIPH0_GPIO58"),
};

static const struct jhb100_gpio_func_sel
	jhb100_bmcperiph0_func_sel[ARRAY_SIZE(jhb100_bmcperiph0_pins)] = {
	[0]	= { 0x104,	0,	1 },
	[1]	= { 0x104,	2,	1 },
	[2]	= { 0x104,	4,	1 },
	[3]	= { 0x104,	6,	1 },
	[4]	= { 0x104,	8,	1 },
	[5]	= { 0x104,	10,	1 },
	[6]	= { 0x104,	12,	1 },
	[7]	= { 0x104,	14,	1 },
	[8]	= { 0x104,	16,	2 },
	[9]	= { 0x104,	18,	2 },
	[10]	= { 0x104,	20,	2 },
	[11]	= { 0x104,	22,	2 },
	[12]	= { 0x104,	24,	2 },
	[13]	= { 0x104,	26,	2 },
	[14]	= { 0x104,	28,	2 },
	[15]	= { 0x104,	30,	2 },
	[16]	= { 0x108,	0,	2 },
	[17]	= { 0x108,	2,	2 },
	[18]	= { 0x108,	4,	2 },
	[19]	= { 0x108,	6,	2 },
	[20]	= { 0x108,	8,	2 },
	[21]	= { 0x108,	10,	2 },
	[22]	= { 0x108,	12,	2 },
	[23]	= { 0x108,	14,	2 },
	[24]	= { 0x108,	16,	2 },
	[25]	= { 0x108,	18,	2 },
	[26]	= { 0x108,	20,	2 },
	[27]	= { 0x108,	22,	2 },
	[28]	= { 0x108,	24,	1 },
	[29]	= { 0x108,	26,	1 },
	[30]	= { 0x108,	28,	2 },
	[31]	= { 0x108,	30,	2 },
	[32]	= { 0x10c,	0,	2 },
	[33]	= { 0x10c,	2,	2 },
	[34]	= { 0x10c,	4,	2 },
	[35]	= { 0x10c,	6,	2 },
	[36]	= { 0x10c,	8,	1 },
	[37]	= { 0x10c,	10,	1 },
	[38]	= { 0x10c,	12,	1 },
	[39]	= { 0x10c,	14,	1 },
	[40]	= { 0x10c,	16,	2 },
	[41]	= { 0x10c,	18,	1 },
	[42]	= { 0x10c,	20,	1 },
	[43]	= { 0x10c,	22,	1 },
	[44]	= { 0x10c,	24,	1 },
	[45]	= { 0x10c,	26,	1 },
	[46]	= { 0x10c,	28,	1 },
	[47]	= { 0x10c,	30,	1 },
	[48]	= { 0x02c,	0,	1 },
	[49]	= { 0x02c,	2,	1 },
	[50]	= { 0x02c,	4,	1 },
	[51]	= { 0x02c,	6,	1 },
	[52]	= { 0x02c,	8,	1 },
	[53]	= { 0x02c,	10,	1 },
	[54]	= { 0x02c,	12,	1 },
	[55]	= { 0x02c,	14,	1 },
	[56]	= { 0x02c,	16,	1 },
	[57]	= { 0x030,	18,	1 },
	[58]	= { 0x030,	20,	1 },
};

static void jhb100_bmcperiph0_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH0_GPIOEN0);
	writel(0U, priv->base + JHB100_BMCPERIPH0_GPIOEN1);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH0_GPIOIC0);
	writel(0U, priv->base + JHB100_BMCPERIPH0_GPIOIC1);
}

static int jhb100_bmcperiph0_set_one_pin_mux(struct udevice *dev, u32 pin,
					     u32 func, int gpioval)
{
	return starfive_set_one_pin_mux(dev, pin, func, gpioval);
}

static int jhb100_bmcperiph0_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_BMCPERIPH0_NGPIO)
		return JHB100_BMCPERIPH0_PADCFG_BASE;
	puts("Not a valid BMCPERIPH0 pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_bmcperiph0_pinctrl_info = {
	.pins				= jhb100_bmcperiph0_pins,
	.npins				= ARRAY_SIZE(jhb100_bmcperiph0_pins),
	.ngpios				= JHB100_BMCPERIPH0_NGPIO,
	.name				= "BMCPERIPH0_GPIO",
	.gpio_o_sel_reg_base		= JHB100_BMCPERIPH0_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_BMCPERIPH0_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_BMCPERIPH0_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_BMCPERIPH0_GPIOIN,
	.func_sel			= jhb100_bmcperiph0_func_sel,
	.gpio_init_hw			= jhb100_bmcperiph0_init_hw,
	.set_one_pinmux			= jhb100_bmcperiph0_set_one_pin_mux,
	.get_padcfg_base		= jhb100_bmcperiph0_get_padcfg_base,
};

static int jhb100_bmcperiph0_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_bmcperiph0_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph0",
		.data = (ulong)&jhb100_bmcperiph0_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_bmcperiph0_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-bmcperiph0",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_bmcperiph0_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_bmcperiph0_pinctrl_probe,
};
