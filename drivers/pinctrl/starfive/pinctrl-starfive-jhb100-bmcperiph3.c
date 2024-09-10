// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC bmcperiph3 controller
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_BMCPERIPH3_NGPIO			0
#define JHB100_BMCPERIPH3_VSELCFG_BASE		0x0

/* registers */
#define JHB100_BMCPERIPH3_GPIO_O_SEL		0x030
#define JHB100_BMCPERIPH3_GPIO_OEN_SEL		0x034
#define JHB100_BMCPERIPH3_GPIOIN		0x038
#define JHB100_BMCPERIPH3_FUNC_SEL		0x03c

#define JHB100_BMCPERIPH3_GPIOEN0		0x040
#define JHB100_BMCPERIPH3_GPIOIS0		0x044
#define JHB100_BMCPERIPH3_GPIOIC0		0x048
#define JHB100_BMCPERIPH3_GPIOIE0		0x04c
#define JHB100_BMCPERIPH3_GPIOIHL0		0x050
#define JHB100_BMCPERIPH3_GPIOIBE0		0x054
#define JHB100_BMCPERIPH3_GPIOIEV0		0x058

static const struct starfive_pinctrl_pin jhb100_bmcperiph3_pins[] = {
	STARFIVE_PINCTRL(0,	"BMCPERIPH3_GPIO0"),
	STARFIVE_PINCTRL(1,	"BMCPERIPH3_GPIO1"),
	STARFIVE_PINCTRL(2,	"BMCPERIPH3_GPIO2"),
	STARFIVE_PINCTRL(3,	"BMCPERIPH3_GPIO3"),
	STARFIVE_PINCTRL(4,	"BMCPERIPH3_GPIO4"),
	STARFIVE_PINCTRL(5,	"BMCPERIPH3_GPIO5"),
	STARFIVE_PINCTRL(6,	"BMCPERIPH3_GPIO6"),
	STARFIVE_PINCTRL(7,	"BMCPERIPH3_GPIO7"),
	STARFIVE_PINCTRL(8,	"BMCPERIPH3_GPIO8"),
	STARFIVE_PINCTRL(9,	"BMCPERIPH3_GPIO9"),
	STARFIVE_PINCTRL(10,	"BMCPERIPH3_GPIO10"),
};

static const struct jhb100_gpio_func_sel
	jhb100_bmcperiph3_func_sel[ARRAY_SIZE(jhb100_bmcperiph3_pins)] = {
	[0]	= { 0x03c,	0,	1 },
	[1]	= { 0x03c,	2,	1 },
	[2]	= { 0x03c,	4,	1 },
	[3]	= { 0x03c,	6,	1 },
	[4]	= { 0x03c,	8,	1 },
	[5]	= { 0x03c,	10,	1 },
	[6]	= { 0x03c,	12,	1 },
	[7]	= { 0x03c,	14,	1 },
	[8]	= { 0x03c,	16,	1 },
	[9]	= { 0x03c,	18,	1 },
	[10]	= { 0x03c,	20,	1 },
};

static void jhb100_bmcperiph3_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH3_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH3_GPIOIC0);
}

static int jhb100_bmcperiph3_set_one_pin_mux(struct udevice *dev, u32 pin,
					     u32 func, int gpioval)
{
	if (func)
		starfive_set_function(dev, pin, func);

	starfive_set_gmacvsel(dev, pin, gpioval);

	return 0;
}

static const struct jhb100_pinctrl_soc_info jhb100_bmcperiph3_pinctrl_info = {
	.pins				= jhb100_bmcperiph3_pins,
	.npins				= ARRAY_SIZE(jhb100_bmcperiph3_pins),
	.ngpios				= JHB100_BMCPERIPH3_NGPIO,
	.name				= "BMCPERIPH3_GPIO",
	.gpio_o_sel_reg_base		= JHB100_BMCPERIPH3_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_BMCPERIPH3_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_vsel_mask			= GENMASK(1, 0),
	.gpio_vselcfg_base		= JHB100_BMCPERIPH3_VSELCFG_BASE,
	.gpio_func_sel_reg_base		= JHB100_BMCPERIPH3_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_BMCPERIPH3_GPIOIN,
	.func_sel			= jhb100_bmcperiph3_func_sel,
	.gpio_init_hw			= jhb100_bmcperiph3_init_hw,
	.set_one_pinmux			= jhb100_bmcperiph3_set_one_pin_mux,
};

static int jhb100_bmcperiph3_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_bmcperiph3_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph3",
		.data = (ulong)&jhb100_bmcperiph3_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_bmcperiph3_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-bmcperiph3",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_bmcperiph3_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_bmcperiph3_pinctrl_probe,
};
