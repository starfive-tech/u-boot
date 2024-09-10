// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC Systop sys2
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_SYSTOP_SYS2_NGPIO		32
#define JHB100_SYSTOP_SYS2_PADCFG_BASE		0x0

/* registers */
#define JHB100_SYSTOP_SYS2_GPIO_O_SEL		0x094
#define JHB100_SYSTOP_SYS2_GPIO_OEN_SEL		0x098
#define JHB100_SYSTOP_SYS2_GPIOIN		0x09c
#define JHB100_SYSTOP_SYS2_FUNC_SEL		0x0a0

#define JHB100_SYSTOP_SYS2_GPIOEN0		0x0ac
#define JHB100_SYSTOP_SYS2_GPIOIS0		0x0b0
#define JHB100_SYSTOP_SYS2_GPIOIC0		0x0b4
#define JHB100_SYSTOP_SYS2_GPIOIE0		0x0b8
#define JHB100_SYSTOP_SYS2_GPIOIHL0		0x0bc
#define JHB100_SYSTOP_SYS2_GPIOIBE0		0x0c0
#define JHB100_SYSTOP_SYS2_GPIOIEV0		0x0c4

static const struct starfive_pinctrl_pin jhb100_systop_sys2_pins[] = {
	STARFIVE_PINCTRL(0,	"SYSTOP_SYS2_GPIO0"),
	STARFIVE_PINCTRL(1,	"SYSTOP_SYS2_GPIO1"),
	STARFIVE_PINCTRL(2,	"SYSTOP_SYS2_GPIO2"),
	STARFIVE_PINCTRL(3,	"SYSTOP_SYS2_GPIO3"),
	STARFIVE_PINCTRL(4,	"SYSTOP_SYS2_GPIO4"),
	STARFIVE_PINCTRL(5,	"SYSTOP_SYS2_GPIO5"),
	STARFIVE_PINCTRL(6,	"SYSTOP_SYS2_GPIO6"),
	STARFIVE_PINCTRL(7,	"SYSTOP_SYS2_GPIO7"),
	STARFIVE_PINCTRL(8,	"SYSTOP_SYS2_GPIO8"),
	STARFIVE_PINCTRL(9,	"SYSTOP_SYS2_GPIO9"),
	STARFIVE_PINCTRL(10,	"SYSTOP_SYS2_GPIO10"),
	STARFIVE_PINCTRL(11,	"SYSTOP_SYS2_GPIO11"),
	STARFIVE_PINCTRL(12,	"SYSTOP_SYS2_GPIO12"),
	STARFIVE_PINCTRL(13,	"SYSTOP_SYS2_GPIO13"),
	STARFIVE_PINCTRL(14,	"SYSTOP_SYS2_GPIO14"),
	STARFIVE_PINCTRL(15,	"SYSTOP_SYS2_GPIO15"),
	STARFIVE_PINCTRL(16,	"SYSTOP_SYS2_GPIO16"),
	STARFIVE_PINCTRL(17,	"SYSTOP_SYS2_GPIO17"),
	STARFIVE_PINCTRL(18,	"SYSTOP_SYS2_GPIO18"),
	STARFIVE_PINCTRL(19,	"SYSTOP_SYS2_GPIO19"),
	STARFIVE_PINCTRL(20,	"SYSTOP_SYS2_GPIO20"),
	STARFIVE_PINCTRL(21,	"SYSTOP_SYS2_GPIO21"),
	STARFIVE_PINCTRL(22,	"SYSTOP_SYS2_GPIO22"),
	STARFIVE_PINCTRL(23,	"SYSTOP_SYS2_GPIO23"),
	STARFIVE_PINCTRL(24,	"SYSTOP_SYS2_GPIO24"),
	STARFIVE_PINCTRL(25,	"SYSTOP_SYS2_GPIO25"),
	STARFIVE_PINCTRL(26,	"SYSTOP_SYS2_GPIO26"),
	STARFIVE_PINCTRL(27,	"SYSTOP_SYS2_GPIO27"),
	STARFIVE_PINCTRL(28,	"SYSTOP_SYS2_GPIO28"),
	STARFIVE_PINCTRL(29,	"SYSTOP_SYS2_GPIO29"),
	STARFIVE_PINCTRL(30,	"SYSTOP_SYS2_GPIO30"),
	STARFIVE_PINCTRL(31,	"SYSTOP_SYS2_GPIO31"),
};

static const struct jhb100_gpio_func_sel
	jhb100_systop_sys2_func_sel[ARRAY_SIZE(jhb100_systop_sys2_pins)] = {
	[0]	= { 0xa0,	0,	2 },
	[1]	= { 0xa0,	2,	2 },
	[2]	= { 0xa0,	4,	2 },
	[3]	= { 0xa0,	6,	2 },
	[4]	= { 0xa0,	8,	2 },
	[5]	= { 0xa0,	10,	2 },
	[6]	= { 0xa0,	12,	2 },
	[7]	= { 0xa0,	14,	2 },
	[8]	= { 0xa0,	16,	1 },
	[9]	= { 0xa0,	18,	1 },
	[10]	= { 0xa0,	20,	1 },
	[11]	= { 0xa0,	22,	1 },
	[12]	= { 0xa0,	24,	2 },
	[13]	= { 0xa0,	26,	2 },
	[14]	= { 0xa0,	28,	2 },
	[15]	= { 0xa0,	30,	2 },
	[16]	= { 0xa4,	0,	2 },
	[17]	= { 0xa4,	2,	2 },
	[18]	= { 0xa4,	4,	2 },
	[19]	= { 0xa4,	6,	2 },
	[20]	= { 0xa4,	8,	1 },
	[21]	= { 0xa4,	10,	1 },
	[22]	= { 0xa4,	12,	1 },
	[23]	= { 0xa4,	14,	1 },
	[24]	= { 0xa4,	16,	1 },
	[25]	= { 0xa4,	18,	1 },
	[26]	= { 0xa4,	20,	1 },
	[27]	= { 0xa4,	22,	2 },
	[28]	= { 0xa4,	24,	2 },
	[29]	= { 0xa4,	26,	2 },
	[30]	= { 0xa4,	28,	2 },
	[31]	= { 0xa4,	30,	2 },
};

static void jhb100_systop_sys2_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS2_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS2_GPIOIC0);
}

static int jhb100_systop_sys2_set_one_pin_mux(struct udevice *dev, u32 pin,
					      u32 func, int gpioval)
{
	return starfive_set_one_pin_mux(dev, pin, func, gpioval);
}

static int jhb100_systop_sys2_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_SYSTOP_SYS2_NGPIO)
		return JHB100_SYSTOP_SYS2_PADCFG_BASE;
	puts("Not a valid SYSTOP SYS2 pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_systop_sys2_pinctrl_info = {
	.pins				= jhb100_systop_sys2_pins,
	.npins				= ARRAY_SIZE(jhb100_systop_sys2_pins),
	.ngpios				= JHB100_SYSTOP_SYS2_NGPIO,
	.name				= "SYSTOP_SYS2_GPIO",
	.gpio_o_sel_reg_base		= JHB100_SYSTOP_SYS2_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_SYSTOP_SYS2_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_SYSTOP_SYS2_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_SYSTOP_SYS2_GPIOIN,
	.func_sel			= jhb100_systop_sys2_func_sel,
	.gpio_init_hw			= jhb100_systop_sys2_init_hw,
	.set_one_pinmux			= jhb100_systop_sys2_set_one_pin_mux,
	.get_padcfg_base		= jhb100_systop_sys2_get_padcfg_base,
};

static int jhb100_systop_sys2_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_systop_sys2_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-systop-sys2",
		.data = (ulong)&jhb100_systop_sys2_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_systop_sys2_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-systop-sys2",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_systop_sys2_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_systop_sys2_pinctrl_probe,
};
