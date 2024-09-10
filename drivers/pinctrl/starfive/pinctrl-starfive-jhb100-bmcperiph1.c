// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC bmcperiph1 controller
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_BMCPERIPH1_NGPIO			35
#define JHB100_BMCPERIPH1_PADCFG_BASE		0x0

#define JHB100_BMCPERIPH1_SFC0_PIN_START	5
#define JHB100_BMCPERIPH1_SFC0_PIN_END		11

/* registers */
#define JHB100_BMCPERIPH1_GPIO_O_SEL		0x090
#define JHB100_BMCPERIPH1_GPIO_OEN_SEL		0x098
#define JHB100_BMCPERIPH1_GPIOIN		0x0a0
#define JHB100_BMCPERIPH1_FUNC_SEL		0x0a8

#define JHB100_BMCPERIPH1_GPIOEN0		0x0b4
#define JHB100_BMCPERIPH1_GPIOEN1		0x0b8
#define JHB100_BMCPERIPH1_GPIOIS0		0x0bc
#define JHB100_BMCPERIPH1_GPIOIS1		0x0c0
#define JHB100_BMCPERIPH1_GPIOIC0		0x0c4
#define JHB100_BMCPERIPH1_GPIOIC1		0x0c8
#define JHB100_BMCPERIPH1_GPIOIE0		0x0cc
#define JHB100_BMCPERIPH1_GPIOIE1		0x0d0
#define JHB100_BMCPERIPH1_GPIOIHL0		0x0d4
#define JHB100_BMCPERIPH1_GPIOIHL1		0x0d8
#define JHB100_BMCPERIPH1_GPIOIBE0		0x0dc
#define JHB100_BMCPERIPH1_GPIOIBE1		0x0e0
#define JHB100_BMCPERIPH1_GPIOIEV0		0x0e4
#define JHB100_BMCPERIPH1_GPIOIEV1		0x0e8

static const struct starfive_pinctrl_pin jhb100_bmcperiph1_pins[] = {
	STARFIVE_PINCTRL(0,	"BMCPERIPH1_GPIO0"),
	STARFIVE_PINCTRL(1,	"BMCPERIPH1_GPIO1"),
	STARFIVE_PINCTRL(2,	"BMCPERIPH1_GPIO2"),
	STARFIVE_PINCTRL(3,	"BMCPERIPH1_GPIO3"),
	STARFIVE_PINCTRL(4,	"BMCPERIPH1_GPIO4"),
	STARFIVE_PINCTRL(5,	"BMCPERIPH1_SFC0_SS0"),
	STARFIVE_PINCTRL(6,	"BMCPERIPH1_SFC0_SS1"),
	STARFIVE_PINCTRL(7,	"BMCPERIPH1_SFC0_SCLK_OUT"),
	STARFIVE_PINCTRL(8,	"BMCPERIPH1_SFC0_MOSI0"),
	STARFIVE_PINCTRL(9,	"BMCPERIPH1_SFC0_MISO0"),
	STARFIVE_PINCTRL(10,	"BMCPERIPH1_SFC0_MOSI1"),
	STARFIVE_PINCTRL(11,	"BMCPERIPH1_SFC0_MISO1"),
	STARFIVE_PINCTRL(12,	"BMCPERIPH1_GPIO12"),
	STARFIVE_PINCTRL(13,	"BMCPERIPH1_GPIO13"),
	STARFIVE_PINCTRL(14,	"BMCPERIPH1_GPIO14"),
	STARFIVE_PINCTRL(15,	"BMCPERIPH1_GPIO15"),
	STARFIVE_PINCTRL(16,	"BMCPERIPH1_GPIO16"),
	STARFIVE_PINCTRL(17,	"BMCPERIPH1_GPIO17"),
	STARFIVE_PINCTRL(18,	"BMCPERIPH1_GPIO18"),
	STARFIVE_PINCTRL(19,	"BMCPERIPH1_GPIO19"),
	STARFIVE_PINCTRL(20,	"BMCPERIPH1_GPIO20"),
	STARFIVE_PINCTRL(21,	"BMCPERIPH1_GPIO21"),
	STARFIVE_PINCTRL(22,	"BMCPERIPH1_GPIO22"),
	STARFIVE_PINCTRL(23,	"BMCPERIPH1_GPIO23"),
	STARFIVE_PINCTRL(24,	"BMCPERIPH1_GPIO24"),
	STARFIVE_PINCTRL(25,	"BMCPERIPH1_GPIO25"),
	STARFIVE_PINCTRL(26,	"BMCPERIPH1_GPIO26"),
	STARFIVE_PINCTRL(27,	"BMCPERIPH1_GPIO27"),
	STARFIVE_PINCTRL(28,	"BMCPERIPH1_GPIO28"),
	STARFIVE_PINCTRL(29,	"BMCPERIPH1_GPIO29"),
	STARFIVE_PINCTRL(30,	"BMCPERIPH1_GPIO30"),
	STARFIVE_PINCTRL(31,	"BMCPERIPH1_GPIO31"),
	STARFIVE_PINCTRL(32,	"BMCPERIPH1_GPIO32"),
	STARFIVE_PINCTRL(33,	"BMCPERIPH1_GPIO33"),
	STARFIVE_PINCTRL(34,	"BMCPERIPH1_GPIO34"),
};

static const struct jhb100_gpio_func_sel
	jhb100_bmcperiph1_func_sel[ARRAY_SIZE(jhb100_bmcperiph1_pins)] = {
	[0]	= { 0x0a8,	0,	1 },
	[1]	= { 0x0a8,	2,	1 },
	[2]	= { 0x0a8,	4,	1 },
	[3]	= { 0x0a8,	6,	1 },
	[4]	= { 0x0a8,	8,	1 },
	[5]	= { 0x0a8,	10,	1 },
	[6]	= { 0x0a8,	12,	1 },
	[7]	= { 0x0a8,	14,	1 },
	[8]	= { 0x0a8,	16,	1 },
	[9]	= { 0x0a8,	18,	1 },
	[10]	= { 0x0a8,	20,	1 },
	[11]	= { 0x0a8,	22,	1 },
	[12]	= { 0x0a8,	24,	1 },
	[13]	= { 0x0a8,	26,	1 },
	[14]	= { 0x0a8,	28,	1 },
	[15]	= { 0x0a8,	30,	1 },
	[16]	= { 0x0ac,	0,	1 },
	[17]	= { 0x0ac,	2,	1 },
	[18]	= { 0x0ac,	4,	1 },
	[19]	= { 0x0ac,	6,	1 },
	[20]	= { 0x0ac,	8,	1 },
	[21]	= { 0x0ac,	10,	1 },
	[22]	= { 0x0ac,	12,	1 },
	[23]	= { 0x0ac,	14,	1 },
	[24]	= { 0x0ac,	16,	1 },
	[25]	= { 0x0ac,	18,	1 },
	[26]	= { 0x0ac,	20,	1 },
	[27]	= { 0x0ac,	22,	1 },
	[28]	= { 0x0ac,	24,	1 },
	[29]	= { 0x0ac,	26,	1 },
	[30]	= { 0x0ac,	28,	1 },
	[31]	= { 0x0ac,	30,	2 },
	[32]	= { 0x0b0,	0,	2 },
	[33]	= { 0x0b0,	2,	2 },
	[34]	= { 0x0b0,	4,	2 },
};

static void jhb100_bmcperiph1_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH1_GPIOEN0);
	writel(0U, priv->base + JHB100_BMCPERIPH1_GPIOEN1);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH1_GPIOIC0);
	writel(0U, priv->base + JHB100_BMCPERIPH1_GPIOIC1);
}

static bool jhb100_bmcperiph1_is_sfc_pin(u32 pin)
{
	return (pin >= JHB100_BMCPERIPH1_SFC0_PIN_START &&
		pin <= JHB100_BMCPERIPH1_SFC0_PIN_END);
}

static int jhb100_bmcperiph1_set_one_pin_mux(struct udevice *dev, u32 pin,
					     u32 func, int gpioval)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	if (func)
		starfive_set_function(dev, pin, func);

	if (pin < priv->info->ngpios) {
		if (jhb100_bmcperiph1_is_sfc_pin(pin) && func == 1)
			starfive_set_gpioval(dev, pin, gpioval);

		if (!jhb100_bmcperiph1_is_sfc_pin(pin) && func == 0)
			starfive_set_gpioval(dev, pin, gpioval);
	}

	return 0;
}

static int jhb100_bmcperiph1_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_BMCPERIPH1_NGPIO)
		return JHB100_BMCPERIPH1_PADCFG_BASE;
	puts("Not a valid BMCPERIPH1 pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_bmcperiph1_pinctrl_info = {
	.pins				= jhb100_bmcperiph1_pins,
	.npins				= ARRAY_SIZE(jhb100_bmcperiph1_pins),
	.ngpios				= JHB100_BMCPERIPH1_NGPIO,
	.name				= "BMCPERIPH1_GPIO",
	.gpio_o_sel_reg_base		= JHB100_BMCPERIPH1_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_BMCPERIPH1_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_BMCPERIPH1_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_BMCPERIPH1_GPIOIN,
	.func_sel			= jhb100_bmcperiph1_func_sel,
	.gpio_init_hw			= jhb100_bmcperiph1_init_hw,
	.set_one_pinmux			= jhb100_bmcperiph1_set_one_pin_mux,
	.get_padcfg_base		= jhb100_bmcperiph1_get_padcfg_base,
};

static int jhb100_bmcperiph1_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_bmcperiph1_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph1",
		.data = (ulong)&jhb100_bmcperiph1_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_bmcperiph1_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-bmcperiph1",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_bmcperiph1_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_bmcperiph1_pinctrl_probe,
};
