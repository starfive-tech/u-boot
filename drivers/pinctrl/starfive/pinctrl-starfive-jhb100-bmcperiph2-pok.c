// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC bmcperiph2_pok (powerok) controller
 *
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_BMCPERIPH2_POK_NGPIO		18
#define JHB100_BMCPERIPH2_POK_PADCFG_BASE	0x04

/* registers */
#define JHB100_BMCPERIPH2_POK_GPIO_O_SEL	0x04c
#define JHB100_BMCPERIPH2_POK_GPIO_OEN_SEL	0x050
#define JHB100_BMCPERIPH2_POK_GPIOIN		0x054
#define JHB100_BMCPERIPH2_POK_FUNC_SEL		0x058

#define JHB100_BMCPERIPH2_POK_GPIOEN0		0x060
#define JHB100_BMCPERIPH2_POK_GPIOIS0		0x064
#define JHB100_BMCPERIPH2_POK_GPIOIC0		0x068
#define JHB100_BMCPERIPH2_POK_GPIOIE0		0x06c
#define JHB100_BMCPERIPH2_POK_GPIOIHL0		0x070
#define JHB100_BMCPERIPH2_POK_GPIOIBE0		0x074
#define JHB100_BMCPERIPH2_POK_GPIOIEV0		0x078

static const struct starfive_pinctrl_pin jhb100_bmcperiph2_pok_pins[] = {
	STARFIVE_PINCTRL(0,	"BMCPERIPH2_POK_GPIO0"),
	STARFIVE_PINCTRL(1,	"BMCPERIPH2_POK_GPIO1"),
	STARFIVE_PINCTRL(2,	"BMCPERIPH2_POK_GPIO2"),
	STARFIVE_PINCTRL(3,	"BMCPERIPH2_POK_GPIO3"),
	STARFIVE_PINCTRL(4,	"BMCPERIPH2_POK_GPIO4"),
	STARFIVE_PINCTRL(5,	"BMCPERIPH2_POK_GPIO5"),
	STARFIVE_PINCTRL(6,	"BMCPERIPH2_POK_GPIO6"),
	STARFIVE_PINCTRL(7,	"BMCPERIPH2_POK_GPIO7"),
	STARFIVE_PINCTRL(8,	"BMCPERIPH2_POK_GPIO8"),
	STARFIVE_PINCTRL(9,	"BMCPERIPH2_POK_GPIO9"),
	STARFIVE_PINCTRL(10,	"BMCPERIPH2_POK_PWM_CHANNEL_0"),
	STARFIVE_PINCTRL(11,	"BMCPERIPH2_POK_PWM_CHANNEL_1"),
	STARFIVE_PINCTRL(12,	"BMCPERIPH2_POK_PWM_CHANNEL_2"),
	STARFIVE_PINCTRL(13,	"BMCPERIPH2_POK_PWM_CHANNEL_3"),
	STARFIVE_PINCTRL(14,	"BMCPERIPH2_POK_PWM_CHANNEL_4"),
	STARFIVE_PINCTRL(15,	"BMCPERIPH2_POK_PWM_CHANNEL_5"),
	STARFIVE_PINCTRL(16,	"BMCPERIPH2_POK_PWM_CHANNEL_6"),
	STARFIVE_PINCTRL(17,	"BMCPERIPH2_POK_PWM_CHANNEL_7"),
};

static const struct jhb100_gpio_func_sel
	jhb100_bmcperiph2_pok_func_sel[ARRAY_SIZE(jhb100_bmcperiph2_pok_pins)] = {
	[0]	= { 0x058,	0,	1 },
	[1]	= { 0x058,	2,	1 },
	[2]	= { 0x058,	4,	2 },
	[3]	= { 0x058,	6,	1 },
	[4]	= { 0x058,	8,	1 },
	[5]	= { 0x058,	10,	2 },
	[6]	= { 0x058,	12,	1 },
	[7]	= { 0x058,	14,	1 },
	[8]	= { 0x058,	16,	1 },
	[9]	= { 0x058,	18,	1 },
	[10]	= { 0x058,	20,	3 },
	[11]	= { 0x058,	22,	3 },
	[12]	= { 0x058,	24,	3 },
	[13]	= { 0x058,	26,	3 },
	[14]	= { 0x058,	28,	3 },
	[15]	= { 0x058,	30,	3 },
	[16]	= { 0x05c,	0,	3 },
	[17]	= { 0x05c,	2,	3 },
};

static void jhb100_bmcperiph2_pok_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH2_POK_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_BMCPERIPH2_POK_GPIOIC0);
}

static int jhb100_bmcperiph2_pok_set_one_pin_mux(struct udevice *dev, u32 pin,
						 u32 func, int gpioval)
{
	return starfive_set_one_pin_mux(dev, pin, func, gpioval);
}

static int jhb100_bmcperiph2_pok_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_BMCPERIPH2_POK_NGPIO)
		return JHB100_BMCPERIPH2_POK_PADCFG_BASE;
	puts("Not a valid BMCPERIPH2_POK pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_bmcperiph2_pok_pinctrl_info = {
	.pins				= jhb100_bmcperiph2_pok_pins,
	.npins				= ARRAY_SIZE(jhb100_bmcperiph2_pok_pins),
	.ngpios				= JHB100_BMCPERIPH2_POK_NGPIO,
	.name				= "BMCPERIPH2_POK_GPIO",
	.gpio_o_sel_reg_base		= JHB100_BMCPERIPH2_POK_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_BMCPERIPH2_POK_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_BMCPERIPH2_POK_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_BMCPERIPH2_POK_GPIOIN,
	.func_sel			= jhb100_bmcperiph2_pok_func_sel,
	.gpio_init_hw			= jhb100_bmcperiph2_pok_init_hw,
	.set_one_pinmux			= jhb100_bmcperiph2_pok_set_one_pin_mux,
	.get_padcfg_base		= jhb100_bmcperiph2_pok_get_padcfg_base,
};

static int jhb100_bmcperiph2_pok_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_bmcperiph2_pok_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph2-pok",
		.data = (ulong)&jhb100_bmcperiph2_pok_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_bmcperiph2_pok_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-bmcperiph2-pok",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_bmcperiph2_pok_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_bmcperiph2_pok_pinctrl_probe,
};
