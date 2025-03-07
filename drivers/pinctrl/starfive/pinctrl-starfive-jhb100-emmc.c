// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC eMMC controller
 *
 * Copyright (C) 2025 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_EMMC_NGPIO		12
#define JHB100_EMMC_PADCFG_BASE		0x00

/* registers */
#define JHB100_EMMC_GPIO_O_SEL		0x030
#define JHB100_EMMC_GPIO_OEN_SEL	0x034
#define JHB100_EMMC_GPIOIN		0x038
#define JHB100_EMMC_FUNC_SEL		0x03c

#define JHB100_EMMC_GPIOEN0		0x040
#define JHB100_EMMC_GPIOIS0		0x044
#define JHB100_EMMC_GPIOIC0		0x048
#define JHB100_EMMC_GPIOIE0		0x04c
#define JHB100_EMMC_GPIOIHL0		0x050
#define JHB100_EMMC_GPIOIBE0		0x044
#define JHB100_EMMC_GPIOIEV0		0x058

static const struct starfive_pinctrl_pin jhb100_emmc_pins[] = {
	STARFIVE_PINCTRL(0,	"EMMC_GPIO0"),
	STARFIVE_PINCTRL(1,	"EMMC_GPIO1"),
	STARFIVE_PINCTRL(2,	"EMMC_GPIO2"),
	STARFIVE_PINCTRL(3,	"EMMC_GPIO3"),
	STARFIVE_PINCTRL(4,	"EMMC_GPIO4"),
	STARFIVE_PINCTRL(5,	"EMMC_GPIO5"),
	STARFIVE_PINCTRL(6,	"EMMC_GPIO6"),
	STARFIVE_PINCTRL(7,	"EMMC_GPIO7"),
	STARFIVE_PINCTRL(8,	"EMMC_GPIO8"),
	STARFIVE_PINCTRL(9,	"EMMC_GPIO9"),
	STARFIVE_PINCTRL(10,	"EMMC_GPIO10"),
	STARFIVE_PINCTRL(11,	"EMMC_GPIO11"),
};

static const struct jhb100_gpio_func_sel
	jhb100_emmc_func_sel[ARRAY_SIZE(jhb100_emmc_pins)] = {
	[0]	= { 0x3c,	0,	1 },
	[1]	= { 0x3c,	2,	1 },
	[2]	= { 0x3c,	4,	1 },
	[3]	= { 0x3c,	6,	1 },
	[4]	= { 0x3c,	8,	1 },
	[5]	= { 0x3c,	10,	1 },
	[6]	= { 0x3c,	12,	1 },
	[7]	= { 0x3c,	14,	1 },
	[8]	= { 0x3c,	16,	1 },
	[9]	= { 0x3c,	18,	1 },
	[10]	= { 0x3c,	20,	1 },
	[11]	= { 0x3c,	22,	1 },
};

static void jhb100_emmc_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_EMMC_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_EMMC_GPIOIC0);
}

static int jhb100_emmc_set_one_pin_mux(struct udevice *dev, u32 pin,
				       u32 func, int gpioval)
{
	return starfive_set_one_pin_mux(dev, pin, func, gpioval);
}

static int jhb100_emmc_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_EMMC_NGPIO)
		return JHB100_EMMC_PADCFG_BASE;
	puts("Not a valid eMMC pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_emmc_pinctrl_info = {
	.pins				= jhb100_emmc_pins,
	.npins				= ARRAY_SIZE(jhb100_emmc_pins),
	.ngpios				= JHB100_EMMC_NGPIO,
	.name				= "EMMC_GPIO",
	.gpio_o_sel_reg_base		= JHB100_EMMC_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_EMMC_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_EMMC_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_EMMC_GPIOIN,
	.func_sel			= jhb100_emmc_func_sel,
	.gpio_init_hw			= jhb100_emmc_init_hw,
	.set_one_pinmux			= jhb100_emmc_set_one_pin_mux,
	.get_padcfg_base		= jhb100_emmc_get_padcfg_base,
};

static int jhb100_emmc_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_emmc_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-pinctrl-emmc",
		.data = (ulong)&jhb100_emmc_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_emmc_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-emmc",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_emmc_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_emmc_pinctrl_probe,
	.bind		= starfive_pinctrl_bind,
};
