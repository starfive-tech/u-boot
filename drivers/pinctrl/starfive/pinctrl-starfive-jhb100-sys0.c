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

#define JHB100_SYSTOP_SYS0_NGPIO		4
#define JHB100_SYSTOP_SYS0_PADCFG_BASE		0x0c

/* registers */
#define JHB100_SYSTOP_SYS0_GPIO_O_SEL		0x038
#define JHB100_SYSTOP_SYS0_GPIO_OEN_SEL		0x03c
#define JHB100_SYSTOP_SYS0_GPIOIN		0x040
#define JHB100_SYSTOP_SYS0_FUNC_SEL		0x044

#define JHB100_SYSTOP_SYS0_GPIOEN0		0x048
#define JHB100_SYSTOP_SYS0_GPIOIS0		0x04c
#define JHB100_SYSTOP_SYS0_GPIOIC0		0x050
#define JHB100_SYSTOP_SYS0_GPIOIE0		0x054
#define JHB100_SYSTOP_SYS0_GPIOIHL0		0x058
#define JHB100_SYSTOP_SYS0_GPIOIBE0		0x05c
#define JHB100_SYSTOP_SYS0_GPIOIEV0		0x060

static const struct starfive_pinctrl_pin jhb100_systop_sys0_pins[] = {
	STARFIVE_PINCTRL(0,	"SYSTOP_SYS0_GPIO0"),
	STARFIVE_PINCTRL(1,	"SYSTOP_SYS0_GPIO1"),
	STARFIVE_PINCTRL(2,	"SYSTOP_SYS0_GPIO2"),
	STARFIVE_PINCTRL(3,	"SYSTOP_SYS0_BMCPCIERP0_PE2RST_OUT"),
};

static const struct jhb100_gpio_func_sel
	jhb100_systop_sys0_func_sel[ARRAY_SIZE(jhb100_systop_sys0_pins)] = {
	[0]	= { 0x44,	0,	1 },
	[1]	= { 0x44,	2,	1 },
	[2]	= { 0x44,	4,	1 },
	[3]	= { 0x44,	6,	1 },
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
	.bind		= starfive_pinctrl_bind,
};
