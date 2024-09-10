// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC Systop sys0
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_SYSTOP_SYS0_NGPIO		16
#define JHB100_SYSTOP_SYS0_PADCFG_BASE		0x0

/* registers */
#define JHB100_SYSTOP_SYS0_GPIO_O_SEL		0x058
#define JHB100_SYSTOP_SYS0_GPIO_OEN_SEL		0x05c
#define JHB100_SYSTOP_SYS0_GPIOIN		0x060
#define JHB100_SYSTOP_SYS0_FUNC_SEL		0x064
#define JHB100_SYSTOP_SYS0_PCIERP_WAKE		0x068

#define JHB100_SYSTOP_SYS0_GPIOEN0		0x06c
#define JHB100_SYSTOP_SYS0_GPIOIS0		0x070
#define JHB100_SYSTOP_SYS0_GPIOIC0		0x074
#define JHB100_SYSTOP_SYS0_GPIOIE0		0x078
#define JHB100_SYSTOP_SYS0_GPIOIHL0		0x07c
#define JHB100_SYSTOP_SYS0_GPIOIBE0		0x080
#define JHB100_SYSTOP_SYS0_GPIOIEV0		0x084

static const struct starfive_pinctrl_pin jhb100_systop_sys0_pins[] = {
	STARFIVE_PINCTRL(0,	"SYSTOP_SYS0_GPIO0"),
	STARFIVE_PINCTRL(1,	"SYSTOP_SYS0_GPIO1"),
	STARFIVE_PINCTRL(2,	"SYSTOP_SYS0_GPIO2"),
	STARFIVE_PINCTRL(3,	"SYSTOP_SYS0_GPIO3"),
	STARFIVE_PINCTRL(4,	"SYSTOP_SYS0_GPIO4"),
	STARFIVE_PINCTRL(5,	"SYSTOP_SYS0_GPIO5"),
	STARFIVE_PINCTRL(6,	"SYSTOP_SYS0_GPIO6"),
	STARFIVE_PINCTRL(7,	"SYSTOP_SYS0_GPIO7"),
	STARFIVE_PINCTRL(8,	"SYSTOP_SYS0_GPIO8"),
	STARFIVE_PINCTRL(9,	"SYSTOP_SYS0_GPIO9"),
	STARFIVE_PINCTRL(10,	"SYSTOP_SYS0_GPIO10"),
	STARFIVE_PINCTRL(11,	"SYSTOP_SYS0_GPIO11"),
	STARFIVE_PINCTRL(12,	"SYSTOP_SYS0_GPIO12"),
	STARFIVE_PINCTRL(13,	"SYSTOP_SYS0_GPIO13"),
	STARFIVE_PINCTRL(14,	"SYSTOP_SYS0_GPIO14"),
	STARFIVE_PINCTRL(15,	"SYSTOP_SYS0_GPIO15"),
};

static const struct jhb100_gpio_func_sel
	jhb100_systop_sys0_func_sel[ARRAY_SIZE(jhb100_systop_sys0_pins)] = {
	[0]	= { 0x64,	0,	1 },
	[1]	= { 0x64,	2,	1 },
	[2]	= { 0x64,	4,	1 },
	[3]	= { 0x64,	6,	1 },
	[4]	= { 0x64,	8,	2 },
	[5]	= { 0x64,	10,	2 },
	[6]	= { 0x64,	12,	2 },
	[7]	= { 0x64,	14,	2 },
	[8]	= { 0x64,	16,	1 },
	[9]	= { 0x64,	18,	1 },
	[10]	= { 0x64,	20,	1 },
	[11]	= { 0x64,	22,	1 },
	[12]	= { 0x64,	24,	1 },
	[13]	= { 0x64,	26,	1 },
	[14]	= { 0x64,	28,	0 },
	[15]	= { 0x64,	30,	0 },
};

static void jhb100_systop_sys0_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS0_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS0_GPIOIC0);
}

static int jhb100_systop_sys0_set_one_pin_mux(struct udevice *dev, u32 pin,
					      u32 func, int gpioval)
{
	return starfive_set_one_pin_mux(dev, pin, func, gpioval);
}

static int jhb100_systop_sys0_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_SYSTOP_SYS0_NGPIO)
		return JHB100_SYSTOP_SYS0_PADCFG_BASE;
	puts("Not a valid SYSTOP SYS0 pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_systop_sys0_pinctrl_info = {
	.pins				= jhb100_systop_sys0_pins,
	.npins				= ARRAY_SIZE(jhb100_systop_sys0_pins),
	.ngpios				= JHB100_SYSTOP_SYS0_NGPIO,
	.name				= "SYSTOP_SYS0_GPIO",
	.gpio_o_sel_reg_base		= JHB100_SYSTOP_SYS0_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_SYSTOP_SYS0_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_SYSTOP_SYS0_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_SYSTOP_SYS0_GPIOIN,
	.func_sel			= jhb100_systop_sys0_func_sel,
	.gpio_init_hw			= jhb100_systop_sys0_init_hw,
	.set_one_pinmux			= jhb100_systop_sys0_set_one_pin_mux,
	.get_padcfg_base		= jhb100_systop_sys0_get_padcfg_base,
};

static int jhb100_systop_sys0_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_systop_sys0_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-systop-sys0",
		.data = (ulong)&jhb100_systop_sys0_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_systop_sys0_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-systop-sys0",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_systop_sys0_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_systop_sys0_pinctrl_probe,
};
