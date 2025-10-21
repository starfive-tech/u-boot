// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC ADC1 controller
 *
 * Copyright (C) 2025 StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <dm/read.h>
#include <dm/device_compat.h>
#include <linux/io.h>

#include "pinctrl-starfive-jhb100.h"

#define JHB100_ADC1_NGPIO		8
#define JHB100_ADC1_PADCFG_BASE		0x00

/* registers */
#define JHB100_ADC1_GPIO_O_SEL		0x020
#define JHB100_ADC1_GPIO_OEN_SEL	0x024
#define JHB100_ADC1_GPIOIN		0x028
#define JHB100_ADC1_FUNC_SEL		0x02c

#define JHB100_ADC1_GPIOEN0		0x030
#define JHB100_ADC1_GPIOIS0		0x034
#define JHB100_ADC1_GPIOIC0		0x038
#define JHB100_ADC1_GPIOIE0		0x03c
#define JHB100_ADC1_GPIOIHL0		0x040
#define JHB100_ADC1_GPIOIBE0		0x044
#define JHB100_ADC1_GPIOIEV0		0x048
#define JHB100_ADC1_GPIOIRTE		0x04c

static const struct starfive_pinctrl_pin jhb100_adc1_pins[] = {
	STARFIVE_PINCTRL(0,	"ADC1_GPIO0"),
	STARFIVE_PINCTRL(1,	"ADC1_GPIO1"),
	STARFIVE_PINCTRL(2,	"ADC1_GPIO2"),
	STARFIVE_PINCTRL(3,	"ADC1_GPIO3"),
	STARFIVE_PINCTRL(4,	"ADC1_GPIO4"),
	STARFIVE_PINCTRL(5,	"ADC1_GPIO5"),
	STARFIVE_PINCTRL(6,	"ADC1_GPIO6"),
	STARFIVE_PINCTRL(7,	"ADC1_GPIO7"),
};

static const struct jhb100_gpio_func_sel
	jhb100_adc1_func_sel[ARRAY_SIZE(jhb100_adc1_pins)] = {
	[0]	= { 0x2c,	0,	1 },
	[1]	= { 0x2c,	2,	1 },
	[2]	= { 0x2c,	4,	1 },
	[3]	= { 0x2c,	6,	1 },
	[4]	= { 0x2c,	8,	1 },
	[5]	= { 0x2c,	10,	1 },
	[6]	= { 0x2c,	12,	1 },
	[7]	= { 0x2c,	14,	1 },
};

static void jhb100_adc1_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_ADC1_GPIOEN0);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_ADC1_GPIOIC0);
}

static int jhb100_adc1_set_one_pin_mux(struct udevice *dev, u32 pin,
				       u32 func, int gpioval)
{
	return starfive_set_one_pin_mux(dev, pin, func, gpioval);
}

static int jhb100_adc1_get_padcfg_base(struct udevice *dev, u32 pin)
{
	if (pin < JHB100_ADC1_NGPIO)
		return JHB100_ADC1_PADCFG_BASE;
	puts("Not a valid adc1 pin number!\n");
	return -1;
}

static const struct jhb100_pinctrl_soc_info jhb100_adc1_pinctrl_info = {
	.pins				= jhb100_adc1_pins,
	.npins				= ARRAY_SIZE(jhb100_adc1_pins),
	.ngpios				= JHB100_ADC1_NGPIO,
	.name				= "ADC1_GPIO",
	.gpio_o_sel_reg_base		= JHB100_ADC1_GPIO_O_SEL,
	.gpio_o_sel_mask		= GENMASK(0, 0),
	.gpio_oen_sel_reg_base		= JHB100_ADC1_GPIO_OEN_SEL,
	.gpio_oen_sel_mask		= GENMASK(0, 0),
	.gpio_func_sel_reg_base		= JHB100_ADC1_FUNC_SEL,
	.gpio_func_sel_mask		= GENMASK(1, 0),
	.gpioin_reg_base		= JHB100_ADC1_GPIOIN,
	.func_sel			= jhb100_adc1_func_sel,
	.gpio_init_hw			= jhb100_adc1_init_hw,
	.set_one_pinmux			= jhb100_adc1_set_one_pin_mux,
	.get_padcfg_base		= jhb100_adc1_get_padcfg_base,
	.debouce_width_mask		= GENMASK(31, 15),
	.is_vga_adc_pad			= true,
};

static int jhb100_adc1_pinctrl_probe(struct udevice *dev)
{
	struct jhb100_pinctrl_soc_info *info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	return starfive_pinctrl_probe(dev, info);
}

static const struct udevice_id jhb100_adc1_pinctrl_ids[] = {
	{
		.compatible = "starfive,jhb100-pinctrl-adc1",
		.data = (ulong)&jhb100_adc1_pinctrl_info,
	},
	{ /* sentinel */ }
};

U_BOOT_DRIVER(jhb100_adc1_pinctrl) = {
	.name		= "starfive-jhb100-sys-pinctrl-adc1",
	.id		= UCLASS_PINCTRL,
	.of_match	= jhb100_adc1_pinctrl_ids,
	.priv_auto	= sizeof(struct starfive_pinctrl_priv),
	.ops		= &starfive_pinctrl_ops,
	.probe		= jhb100_adc1_pinctrl_probe,
	.bind		= starfive_pinctrl_bind,
};
