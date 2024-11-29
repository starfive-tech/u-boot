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

#define JHB100_BMCPERIPH2_NGPIO			31
#define JHB100_BMCPERIPH2_PADCFG_BASE		0x04

#define JHB100_BMCPERIPH2_VSELCFG_PIN_START	19
#define JHB100_BMCPERIPH2_VSELCFG_PIN_END	30

/* registers */
#define JHB100_BMCPERIPH2_GPIO_O_SEL		0x080
#define JHB100_BMCPERIPH2_GPIO_OEN_SEL		0x084
#define JHB100_BMCPERIPH2_GPIOIN		0x088
#define JHB100_BMCPERIPH2_FUNC_SEL		0x08c

#define JHB100_BMCPERIPH2_GPIOEN0		0x094
#define JHB100_BMCPERIPH2_GPIOIS0		0x098
#define JHB100_BMCPERIPH2_GPIOIC0		0x09c
#define JHB100_BMCPERIPH2_GPIOIE0		0x0a0
#define JHB100_BMCPERIPH2_GPIOIHL0		0x0a4
#define JHB100_BMCPERIPH2_GPIOIBE0		0x0a8
#define JHB100_BMCPERIPH2_GPIOIEV0		0x0ac

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
};

static const struct jhb100_gpio_func_sel
	jhb100_bmcperiph2_func_sel[ARRAY_SIZE(jhb100_bmcperiph2_pins)] = {
	[0]	= { 0x08c,	0,	3 },
	[1]	= { 0x08c,	2,	3 },
	[2]	= { 0x08c,	4,	3 },
	[3]	= { 0x08c,	6,	3 },
	[4]	= { 0x08c,	8,	3 },
	[5]	= { 0x08c,	10,	3 },
	[6]	= { 0x08c,	12,	3 },
	[7]	= { 0x08c,	14,	3 },
	[8]	= { 0x08c,	16,	3 },
	[9]	= { 0x08c,	18,	3 },
	[10]	= { 0x08c,	20,	3 },
	[11]	= { 0x08c,	22,	3 },
	[12]	= { 0x08c,	24,	3 },
	[13]	= { 0x08c,	26,	3 },
	[14]	= { 0x08c,	28,	3 },
	[15]	= { 0x08c,	30,	3 },
	[16]	= { 0x090,	0,	1 },
	[17]	= { 0x090,	2,	1 },
	[18]	= { 0x090,	4,	1 },
	[19]	= { 0x090,	6,	2 },
	[20]	= { 0x090,	8,	2 },
	[21]	= { 0x090,	10,	2 },
	[22]	= { 0x090,	12,	2 },
	[23]	= { 0x090,	14,	1 },
	[24]	= { 0x090,	16,	1 },
	[25]	= { 0x090,	18,	2 },
	[26]	= { 0x090,	20,	2 },
	[27]	= { 0x090,	22,	2 },
	[28]	= { 0x090,	24,	2 },
	[29]	= { 0x090,	26,	1 },
	[30]	= { 0x090,	28,	1 },
};

static void jhb100_bmcperiph2_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH2_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH2_GPIOIC0);
}

static bool jhb100_bmcperiph2_is_vselcfg(u32 pin)
{
	return (pin >= JHB100_BMCPERIPH2_VSELCFG_PIN_START &&
		pin <= JHB100_BMCPERIPH2_VSELCFG_PIN_END);
}

static int jhb100_bmcperiph2_set_one_pin_mux(struct udevice *dev, u32 pin,
					     u32 func, int gpioval)
{
	return starfive_set_one_pin_mux(dev, pin, func, gpioval);
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
	.gpio_func_sel_reg_base		= JHB100_BMCPERIPH2_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_BMCPERIPH2_GPIOIN,
	.func_sel			= jhb100_bmcperiph2_func_sel,
	.gpio_init_hw			= jhb100_bmcperiph2_init_hw,
	.set_one_pinmux			= jhb100_bmcperiph2_set_one_pin_mux,
	.get_padcfg_base		= jhb100_bmcperiph2_get_padcfg_base,
	.is_vselcfg			= jhb100_bmcperiph2_is_vselcfg,
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
