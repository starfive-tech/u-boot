// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC Systop sys0h
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_SYSTOP_SYS0H_NGPIO		12
#define JHB100_SYSTOP_SYS0H_PADCFG_BASE		0x0

#define JHB100_SYSTOP_SYS0H_ESPI0_PIN		7

/* registers */
#define JHB100_SYSTOP_SYS0H_GPIO_O_SEL		0x030
#define JHB100_SYSTOP_SYS0H_GPIO_OEN_SEL	0x034
#define JHB100_SYSTOP_SYS0H_GPIOIN		0x038
#define JHB100_SYSTOP_SYS0H_FUNC_SEL		0x03c

#define JHB100_SYSTOP_SYS0H_GPIOEN0		0x040
#define JHB100_SYSTOP_SYS0H_GPIOIS0		0x044
#define JHB100_SYSTOP_SYS0H_GPIOIC0		0x048
#define JHB100_SYSTOP_SYS0H_GPIOIE0		0x04c
#define JHB100_SYSTOP_SYS0H_GPIOIHL0		0x050
#define JHB100_SYSTOP_SYS0H_GPIOIBE0		0x054
#define JHB100_SYSTOP_SYS0H_GPIOIEV0		0x058

static const struct starfive_pinctrl_pin jhb100_systop_sys0h_pins[] = {
	STARFIVE_PINCTRL(0,	"SYSTOP_SYS0H_GPIO0"),
	STARFIVE_PINCTRL(1,	"SYSTOP_SYS0H_GPIO1"),
	STARFIVE_PINCTRL(2,	"SYSTOP_SYS0H_GPIO2"),
	STARFIVE_PINCTRL(3,	"SYSTOP_SYS0H_GPIO3"),
	STARFIVE_PINCTRL(4,	"SYSTOP_SYS0H_GPIO4"),
	STARFIVE_PINCTRL(5,	"SYSTOP_SYS0H_GPIO5"),
	STARFIVE_PINCTRL(6,	"SYSTOP_SYS0H_GPIO6"),
	STARFIVE_PINCTRL(7,	"SYSTOP_SYS0H_ESPI0_RESET"),
	STARFIVE_PINCTRL(8,	"SYSTOP_SYS0H_GPIO8"),
	STARFIVE_PINCTRL(9,	"SYSTOP_SYS0H_GPIO9"),
	STARFIVE_PINCTRL(10,	"SYSTOP_SYS0H_GPIO10"),
	STARFIVE_PINCTRL(11,	"SYSTOP_SYS0H_GPIO11"),
};

static const struct jhb100_gpio_func_sel
	jhb100_systop_sys0h_func_sel[ARRAY_SIZE(jhb100_systop_sys0h_pins)] = {
	[0]	= { 0x3c,	0,	1 },
	[1]	= { 0x3c,	2,	1 },
	[2]	= { 0x3c,	4,	1 },
	[3]	= { 0x3c,	6,	1 },
	[4]	= { 0x3c,	8,	1 },
	[5]	= { 0x3c,	10,	1 },
	[6]	= { 0x3c,	12,	1 },
	[7]	= { 0x3c,	14,	1 },
	[8]	= { 0x3c,	16,	3 },
	[9]	= { 0x3c,	18,	3 },
	[10]	= { 0x3c,	20,	2 },
	[11]	= { 0x3c,	22,	2 },
};

static void jhb100_systop_sys0h_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS0H_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS0H_GPIOIC0);
}

static bool jhb100_systop_sys0h_is_espi_pin(u32 pin)
{
	return (pin == JHB100_SYSTOP_SYS0H_ESPI0_PIN);
}

static int jhb100_systop_sys0h_set_one_pin_mux(struct udevice *dev, u32 pin,
					       u32 func, int gpioval)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	starfive_set_function(dev, pin, func);

	if (pin < priv->info->ngpios) {
		if (jhb100_systop_sys0h_is_espi_pin(pin) && func == 1)
			starfive_set_gpioval(dev, pin, gpioval);

		if (!jhb100_systop_sys0h_is_espi_pin(pin) && func == 0)
			starfive_set_gpioval(dev, pin, gpioval);
	}

	return 0;
}

static int jhb100_systop_sys0h_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_SYSTOP_SYS0H_NGPIO)
		return JHB100_SYSTOP_SYS0H_PADCFG_BASE;
	puts("Not a valid SYSTOP SYS0H pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_systop_sys0h_pinctrl_info = {
	.pins				= jhb100_systop_sys0h_pins,
	.npins				= ARRAY_SIZE(jhb100_systop_sys0h_pins),
	.ngpios				= JHB100_SYSTOP_SYS0H_NGPIO,
	.name				= "SYSTOP_SYS0H_GPIO",
	.gpio_o_sel_reg_base		= JHB100_SYSTOP_SYS0H_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_SYSTOP_SYS0H_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_SYSTOP_SYS0H_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_SYSTOP_SYS0H_GPIOIN,
	.func_sel			= jhb100_systop_sys0h_func_sel,
	.gpio_init_hw			= jhb100_systop_sys0h_init_hw,
	.set_one_pinmux			= jhb100_systop_sys0h_set_one_pin_mux,
	.get_padcfg_base		= jhb100_systop_sys0h_get_padcfg_base,
};

static int jhb100_systop_sys0h_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_systop_sys0h_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-systop-sys0h",
		.data = (ulong)&jhb100_systop_sys0h_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_systop_sys0h_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-systop-sys0h",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_systop_sys0h_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_systop_sys0h_pinctrl_probe,
};
