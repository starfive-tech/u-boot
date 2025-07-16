// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC Systop sys1
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_SYSTOP_SYS1_NGPIO		8
#define JHB100_SYSTOP_SYS1_PADCFG_BASE		0x04

#define JHB100_SYSTOP_SYS1_ESPI1_PIN		7

/* registers */
#define JHB100_SYSTOP_SYS1_GPIO_O_SEL		0x024
#define JHB100_SYSTOP_SYS1_GPIO_OEN_SEL		0x028
#define JHB100_SYSTOP_SYS1_GPIOIN		0x02c
#define JHB100_SYSTOP_SYS1_FUNC_SEL		0x030

#define JHB100_SYSTOP_SYS1_GPIOEN0		0x034
#define JHB100_SYSTOP_SYS1_GPIOIS0		0x038
#define JHB100_SYSTOP_SYS1_GPIOIC0		0x03c
#define JHB100_SYSTOP_SYS1_GPIOIE0		0x040
#define JHB100_SYSTOP_SYS1_GPIOIHL0		0x044
#define JHB100_SYSTOP_SYS1_GPIOIBE0		0x048
#define JHB100_SYSTOP_SYS1_GPIOIEV0		0x04c

static const struct starfive_pinctrl_pin jhb100_systop_sys1_pins[] = {
	STARFIVE_PINCTRL(0,	"SYSTOP_SYS1_GPIO0"),
	STARFIVE_PINCTRL(1,	"SYSTOP_SYS1_GPIO1"),
	STARFIVE_PINCTRL(2,	"SYSTOP_SYS1_GPIO2"),
	STARFIVE_PINCTRL(3,	"SYSTOP_SYS1_GPIO3"),
	STARFIVE_PINCTRL(4,	"SYSTOP_SYS1_GPIO4"),
	STARFIVE_PINCTRL(5,	"SYSTOP_SYS1_GPIO5"),
	STARFIVE_PINCTRL(6,	"SYSTOP_SYS1_GPIO6"),
	STARFIVE_PINCTRL(7,	"SYSTOP_SYS1_ESPI1_RESET"),
};

static const struct jhb100_gpio_func_sel
	jhb100_systop_sys1_func_sel[ARRAY_SIZE(jhb100_systop_sys1_pins)] = {
	[0]	= { 0x30,	0,	3 },
	[1]	= { 0x30,	2,	3 },
	[2]	= { 0x30,	4,	3 },
	[3]	= { 0x30,	6,	3 },
	[4]	= { 0x30,	8,	3 },
	[5]	= { 0x30,	10,	3 },
	[6]	= { 0x30,	12,	3 },
	[7]	= { 0x30,	14,	3 },
};

static void jhb100_systop_sys1_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS1_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS1_GPIOIC0);
}

static bool jhb100_systop_sys1_is_espi_pin(u32 pin)
{
	return (pin == JHB100_SYSTOP_SYS1_ESPI1_PIN);
}

static int jhb100_systop_sys1_set_one_pin_mux(struct udevice *dev, u32 pin,
					      u32 func, int gpioval)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	starfive_set_function(dev, pin, func);

	if (pin < priv->info->ngpios) {
		if (jhb100_systop_sys1_is_espi_pin(pin) && func == 1)
			starfive_set_gpioval(dev, pin, gpioval);

		if (!jhb100_systop_sys1_is_espi_pin(pin) && func == 0)
			starfive_set_gpioval(dev, pin, gpioval);
	}

	return 0;
}

static int jhb100_systop_sys1_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_SYSTOP_SYS1_NGPIO)
		return JHB100_SYSTOP_SYS1_PADCFG_BASE;
	puts("Not a valid SYSTOP SYS1 pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_systop_sys1_pinctrl_info = {
	.pins				= jhb100_systop_sys1_pins,
	.npins				= ARRAY_SIZE(jhb100_systop_sys1_pins),
	.ngpios				= JHB100_SYSTOP_SYS1_NGPIO,
	.name				= "SYSTOP_SYS1_GPIO",
	.gpio_o_sel_reg_base		= JHB100_SYSTOP_SYS1_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_SYSTOP_SYS1_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_SYSTOP_SYS1_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_SYSTOP_SYS1_GPIOIN,
	.func_sel			= jhb100_systop_sys1_func_sel,
	.gpio_init_hw			= jhb100_systop_sys1_init_hw,
	.set_one_pinmux			= jhb100_systop_sys1_set_one_pin_mux,
	.get_padcfg_base		= jhb100_systop_sys1_get_padcfg_base,
	.debouce_width_mask		= GENMASK(31, 15),
};

static int jhb100_systop_sys1_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_systop_sys1_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-systop-sys1",
		.data = (ulong)&jhb100_systop_sys1_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_systop_sys1_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-systop-sys1",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_systop_sys1_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_systop_sys1_pinctrl_probe,
	.bind		= starfive_pinctrl_bind,
};
