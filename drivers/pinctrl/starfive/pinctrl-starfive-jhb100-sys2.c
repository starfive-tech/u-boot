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

#define JHB100_SYSTOP_SYS2_NGPIO		37
#define JHB100_SYSTOP_SYS2_PADCFG_BASE		0x10

/* registers */
#define JHB100_SYSTOP_SYS2_GPIO_O_SEL		0x0bc
#define JHB100_SYSTOP_SYS2_GPIO_OEN_SEL		0x0c4
#define JHB100_SYSTOP_SYS2_GPIOIN		0x0cc
#define JHB100_SYSTOP_SYS2_FUNC_SEL		0x0d4

#define JHB100_SYSTOP_SYS2_GPIOEN0		0x0e0
#define JHB100_SYSTOP_SYS2_GPIOEN1		0x0e4
#define JHB100_SYSTOP_SYS2_GPIOIS0		0x0e8
#define JHB100_SYSTOP_SYS2_GPIOIS1		0x0ec
#define JHB100_SYSTOP_SYS2_GPIOIC0		0x0f0
#define JHB100_SYSTOP_SYS2_GPIOIC1		0x0f4
#define JHB100_SYSTOP_SYS2_GPIOIE0		0x0f8
#define JHB100_SYSTOP_SYS2_GPIOIE1		0x0fc
#define JHB100_SYSTOP_SYS2_GPIOIHL0		0x100
#define JHB100_SYSTOP_SYS2_GPIOIHL1		0x104
#define JHB100_SYSTOP_SYS2_GPIOIBE0		0x108
#define JHB100_SYSTOP_SYS2_GPIOIBE1		0x10c
#define JHB100_SYSTOP_SYS2_GPIOIEV0		0x110
#define JHB100_SYSTOP_SYS2_GPIOIEV1		0x114

/* SPL only needs pins 0-31 (UART0-14 TX/RX use pad indices 0-31).
 * Pins 32-36 are non-UART pads not used in SPL. */
#ifdef CONFIG_SPL_BUILD
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
	[0]	= { 0xd4,	0,	1 },
	[1]	= { 0xd4,	2,	1 },
	[2]	= { 0xd4,	4,	1 },
	[3]	= { 0xd4,	6,	1 },
	[4]	= { 0xd4,	8,	1 },
	[5]	= { 0xd4,	10,	1 },
	[6]	= { 0xd4,	12,	1 },
	[7]	= { 0xd4,	14,	1 },
	[8]	= { 0xd4,	16,	1 },
	[9]	= { 0xd4,	18,	1 },
	[10]	= { 0xd4,	20,	1 },
	[11]	= { 0xd4,	22,	1 },
	[12]	= { 0xd4,	24,	3 },
	[13]	= { 0xd4,	26,	3 },
	[14]	= { 0xd4,	28,	3 },
	[15]	= { 0xd4,	30,	3 },
	[16]	= { 0xd8,	0,	3 },
	[17]	= { 0xd8,	2,	3 },
	[18]	= { 0xd8,	4,	2 },
	[19]	= { 0xd8,	6,	2 },
	[20]	= { 0xd8,	8,	3 },
	[21]	= { 0xd8,	10,	3 },
	[22]	= { 0xd8,	12,	3 },
	[23]	= { 0xd8,	14,	3 },
	[24]	= { 0xd8,	16,	3 },
	[25]	= { 0xd8,	18,	3 },
	[26]	= { 0xd8,	20,	3 },
	[27]	= { 0xd8,	22,	3 },
	[28]	= { 0xd8,	24,	2 },
	[29]	= { 0xd8,	26,	2 },
	[30]	= { 0xd8,	28,	2 },
	[31]	= { 0xd8,	30,	2 },
};
#else
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
	STARFIVE_PINCTRL(32,	"SYSTOP_SYS2_GPIO32"),
	STARFIVE_PINCTRL(33,	"SYSTOP_SYS2_GPIO33"),
	STARFIVE_PINCTRL(34,	"SYSTOP_SYS2_GPIO34"),
	STARFIVE_PINCTRL(35,	"SYSTOP_SYS2_GPIO35"),
	STARFIVE_PINCTRL(36,	"SYSTOP_SYS2_GPIO36"),
};

static const struct jhb100_gpio_func_sel
	jhb100_systop_sys2_func_sel[ARRAY_SIZE(jhb100_systop_sys2_pins)] = {
	[0]	= { 0xd4,	0,	1 },
	[1]	= { 0xd4,	2,	1 },
	[2]	= { 0xd4,	4,	1 },
	[3]	= { 0xd4,	6,	1 },
	[4]	= { 0xd4,	8,	1 },
	[5]	= { 0xd4,	10,	1 },
	[6]	= { 0xd4,	12,	1 },
	[7]	= { 0xd4,	14,	1 },
	[8]	= { 0xd4,	16,	1 },
	[9]	= { 0xd4,	18,	1 },
	[10]	= { 0xd4,	20,	1 },
	[11]	= { 0xd4,	22,	1 },
	[12]	= { 0xd4,	24,	3 },
	[13]	= { 0xd4,	26,	3 },
	[14]	= { 0xd4,	28,	3 },
	[15]	= { 0xd4,	30,	3 },
	[16]	= { 0xd8,	0,	3 },
	[17]	= { 0xd8,	2,	3 },
	[18]	= { 0xd8,	4,	2 },
	[19]	= { 0xd8,	6,	2 },
	[20]	= { 0xd8,	8,	3 },
	[21]	= { 0xd8,	10,	3 },
	[22]	= { 0xd8,	12,	3 },
	[23]	= { 0xd8,	14,	3 },
	[24]	= { 0xd8,	16,	3 },
	[25]	= { 0xd8,	18,	3 },
	[26]	= { 0xd8,	20,	3 },
	[27]	= { 0xd8,	22,	3 },
	[28]	= { 0xd8,	24,	2 },
	[29]	= { 0xd8,	26,	2 },
	[30]	= { 0xd8,	28,	2 },
	[31]	= { 0xd8,	30,	2 },
	[32]	= { 0xdc,	0,	2 },
	[33]	= { 0xdc,	2,	1 },
	[34]	= { 0xdc,	4,	1 },
	[35]	= { 0xdc,	6,	1 },
	[36]	= { 0xdc,	8,	1 },
};
#endif /* CONFIG_SPL_BUILD */

static void jhb100_systop_sys2_init_hw(struct udevice *dev)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	/* mask all GPIO interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS2_GPIOEN0);
	writel(0U, priv->base + JHB100_SYSTOP_SYS2_GPIOEN1);
	/* clear all interrupts */
	writel(0U, priv->base + JHB100_SYSTOP_SYS2_GPIOIC0);
	writel(0U, priv->base + JHB100_SYSTOP_SYS2_GPIOIC1);
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
	.debouce_width_mask		= GENMASK(31, 15),
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
	.bind		= starfive_pinctrl_bind,
};
