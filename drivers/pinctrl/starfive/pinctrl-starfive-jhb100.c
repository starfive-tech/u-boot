// SPDX-License-Identifier: GPL-2.0
/*
 * Pinctrl / GPIO driver for StarFive JHB100 SoC
 *
 * Copyright (C) 2024 Shanghai StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <clk.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/lists.h>
#include <dm/pinctrl.h>
#include <asm-generic/gpio.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/ioport.h>
#include <dm/device_compat.h>

#include "pinctrl-starfive-jhb100.h"

/* pad control bits offset */
#define JHB100_PADCFG_SMT		BIT(6)
#define JHB100_PADCFG_SLEW		BIT(5)
#define JHB100_PADCFG_PU		BIT(4)
#define JHB100_PADCFG_PD		BIT(3)
#define JHB100_PADCFG_BIAS_MASK		(JHB100_PADCFG_PU | JHB100_PADCFG_PD)
#define JHB100_PADCFG_IE		BIT(2)

#define JHB100_RGMII_PADCFG_VSEL	GENMASK(3, 2)
#define JHB100_RGMII_PADCFG_SLEW	BIT(1)
#define JHB100_RGMII_PADCFG_IE		BIT(0)
#define JHB100_RGMII_VSEL_1_8V		0U
#define JHB100_RGMII_VSEL_2_5V		1U
#define JHB100_RGMII_VSEL_3_3V		0U

#define JHB100_PADCFG_VSEL_SHIFT	2

#define JHB100_PADCFG_DS_MASK		GENMASK(1, 0)
#define JHB100_PADCFG_DS_2MA		0U
#define JHB100_PADCFG_DS_4MA		1U
#define JHB100_PADCFG_DS_8MA		2U
#define JHB100_PADCFG_DS_12MA		3U

#define GPOUT_LOW			0
#define GPOUT_HIGH			1
#define GPI_NONE			0xff
#define GPOEN_ENABLE			0
#define GPOEN_DISABLE			1

#define GPIO_NUM_PER_WORD		32

#define IS_SET_GMAC_VSEL		BIT(12)
#define IS_SET_GPIO_VAL			BIT(10)

/*
 * mux bits:
 * | 31 - 15  | 14 - 13  |   12     |   11    |   10    |  9 - 8   |  7 - 0  |
 * | reserved | gmacvsel |  is-vsel | gpioval | is-gpio | function | gpio nr |
 *
 * gmacvsel: RGMII GMAC pads' voltage selection, 0 = 1.8V/3.3V and 1 = 2.5V
 * is-vsel: 1 = set GMAC pads VSEL
 * gpioval: GPIO output value if pad is GPIO, 1 = logic 1 and 0 = logic 0
 * is-gpio: 1 = set GPIO logic level
 * func: function value: 0, 1, or 2
 * gpio nr: gpio pad number, 0 through ngpios - 1
 */
#define GMACMUX(n, func, gmacvsel) ( \
		(((gmacvsel)  & 0x3) << 13) | \
		((1 << 12)) | \
		(((func) & 0x3) << 8) | \
		((n) & 0xff))

#define GPIOVAL(n, func, gpioval) ( \
		(((gpioval) & 0x1) << 11) | \
		((1 << 10)) | \
		(((func) & 0x3) << 8) | \
		((n) & 0xff))

static u32 jhb100_pinmux_function(u32 v)
{
	return (v & GENMASK(9, 8)) >> 8;
}

static unsigned int jhb100_pinmux_pin(u32 v)
{
	return v & GENMASK(7, 0);
}

static u32 jhb100_pinmux_gpioval(u32 v)
{
	return (v & GENMASK(11, 11)) >> 11;
}

static u32 jhb100_pinmux_gmacvsel(u32 v)
{
	return (v & GENMASK(14, 13)) >> 13;
}

void starfive_set_gpioval(struct udevice *dev, unsigned int pin,
			  unsigned int val)
{
	u32 dout, doen, fs;
	void __iomem *reg_gpio_o;
	void __iomem *reg_gpio_oen;
	void __iomem *reg_gpio_func_sel;

	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);
	struct jhb100_pinctrl_soc_info *info = priv->info;
	unsigned int aligned_offset = 4 * (pin / 32);
	unsigned int shift = pin % 32;
	unsigned int fs_offset = 4 * (pin / 16);
	unsigned int fs_shift = 2 * (pin % 16);

	u32 gpio_o_mask = ((info->gpio_o_sel_mask) << shift);
	u32 gpio_oen_mask = ((info->gpio_oen_sel_mask) << shift);
	u32 func_sel_mask = ((info->gpio_func_sel_mask) << fs_shift);

	reg_gpio_o = priv->base + info->gpio_o_sel_reg_base + aligned_offset;
	reg_gpio_oen = priv->base + info->gpio_oen_sel_reg_base + aligned_offset;
	reg_gpio_func_sel = priv->base + info->gpio_func_sel_reg_base + fs_offset;

	fs = readl(reg_gpio_func_sel);
	if (fs & func_sel_mask) {
		fs &= ~func_sel_mask;
		writel(fs, reg_gpio_func_sel);
	}

	dout = (val == GPOUT_HIGH ? GPOUT_HIGH : GPOUT_LOW) << shift;
	doen = (val == GPI_NONE ? GPOEN_DISABLE : GPOEN_ENABLE) << shift;
	dout |= readl(reg_gpio_o) & ~gpio_o_mask;
	writel(dout, reg_gpio_o);
	doen |= readl(reg_gpio_oen) & ~gpio_oen_mask;
	writel(doen, reg_gpio_oen);
}

void starfive_set_gmacvsel(struct udevice *dev, u32 pin,
			   unsigned int val)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);
	u32 vsel_mask, dout;
	void __iomem *reg_vsel;

	if (!priv->info->gpio_vsel_mask)
		return;

	reg_vsel = priv->base + priv->info->gpio_vselcfg_base + 4 * pin;
	vsel_mask = priv->info->gpio_vsel_mask << JHB100_PADCFG_VSEL_SHIFT;
	dout = val << JHB100_PADCFG_VSEL_SHIFT;

	dout |= readl(reg_vsel) & ~vsel_mask;
	writel(dout, reg_vsel);
}

void starfive_set_function(struct udevice *dev, u32 pin, u32 func)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);
	const struct jhb100_gpio_func_sel *fs = &priv->info->func_sel[pin];
	void __iomem *func_sel_reg;
	u32 func_sel_mask, func_sel_val;

	if (!fs->offset || func > fs->max)
		return;

	func_sel_reg = priv->base + fs->offset;
	func_sel_mask = ((fs->max > 1) ? GENMASK(1, 0) : GENMASK(0, 0)) << fs->shift;
	func_sel_val = func << fs->shift;

	func_sel_val |= readl(func_sel_reg) & ~func_sel_mask;
	writel(func_sel_val, func_sel_reg);
}

int starfive_set_one_pin_mux(struct udevice *dev, u32 pin,
			     u32 func, int gpioval)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);

	if (func)
		starfive_set_function(dev, pin, func);

	if (pin < priv->info->ngpios && func == 0)
		starfive_set_gpioval(dev, pin, gpioval);

	return 0;
}

static const struct pinconf_param starfive_pinconf_params[] = {
	{ "bias-disable",	PIN_CONFIG_BIAS_DISABLE,	0 },
	{ "bias-pull-up",	PIN_CONFIG_BIAS_PULL_UP,	1 },
	{ "bias-pull-down",	PIN_CONFIG_BIAS_PULL_DOWN,	1 },
	{ "drive-strength",	PIN_CONFIG_DRIVE_STRENGTH,	0 },
	{ "input-schmitt-enable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 1 },
	{ "input-schmitt-disable", PIN_CONFIG_INPUT_SCHMITT_ENABLE, 0 },
	{ "input-enable",	PIN_CONFIG_INPUT_ENABLE,	1 },
	{ "input-disable",	PIN_CONFIG_INPUT_ENABLE,	0 },
	{ "slew-rate",		PIN_CONFIG_SLEW_RATE,		0 },
};

static const u8 starfive_drive_strength_mA[4] = { 2, 4, 8, 12 };

static u32 starfive_padcfg_ds_from_mA(u32 v)
{
	int i;

	for (i = 0; i < 3; i++) {
		if (v <= starfive_drive_strength_mA[i])
			break;
	}
	return i;
}

static u32 starfive_padcfg_ds_from_uA(u32 v)
{
	/* Convert from uA to mA */
	v /= 1000;

	return starfive_padcfg_ds_from_mA(v);
}

static void starfive_padcfg_rmw(struct udevice *dev,
				unsigned int pin, u32 mask, u32 value)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);
	struct jhb100_pinctrl_soc_info *info = priv->info;
	void __iomem *reg;
	int padcfg_base;

	if (!info->get_padcfg_base)
		return;

	padcfg_base = info->get_padcfg_base(dev, pin);
	if (padcfg_base < 0)
		return;

	reg = priv->base + padcfg_base + 4 * pin;
	value &= mask;

	value |= readl(reg) & ~mask;
	writel(value, reg);
}

static int starfive_pinconf_set(struct udevice *dev, unsigned int pin,
				unsigned int param, unsigned int arg)
{
	u32 mask = 0;
	u32 value = 0;

	switch (param) {
	case PIN_CONFIG_BIAS_DISABLE:
		mask |= JHB100_PADCFG_BIAS_MASK;
		value &= ~JHB100_PADCFG_BIAS_MASK;
		break;
	case PIN_CONFIG_BIAS_PULL_DOWN:
		if (arg == 0)
			return -EINVAL;
		mask |= JHB100_PADCFG_BIAS_MASK;
		value = (value & ~JHB100_PADCFG_BIAS_MASK) | JHB100_PADCFG_PD;
		break;
	case PIN_CONFIG_BIAS_PULL_UP:
		if (arg == 0)
			return -EINVAL;
		mask |= JHB100_PADCFG_BIAS_MASK;
		value = (value & ~JHB100_PADCFG_BIAS_MASK) | JHB100_PADCFG_PU;
		break;
	case PIN_CONFIG_DRIVE_STRENGTH:
		mask |= JHB100_PADCFG_DS_MASK;
		value = (value & ~JHB100_PADCFG_DS_MASK) |
			starfive_padcfg_ds_from_mA(arg);
		break;
	case PIN_CONFIG_DRIVE_STRENGTH_UA:
		mask |= JHB100_PADCFG_DS_MASK;
		value = (value & ~JHB100_PADCFG_DS_MASK) |
			starfive_padcfg_ds_from_uA(arg);
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		mask |= JHB100_PADCFG_IE;
		if (arg)
			value |= JHB100_PADCFG_IE;
		else
			value &= ~JHB100_PADCFG_IE;
		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		mask |= JHB100_PADCFG_SMT;
		if (arg)
			value |= JHB100_PADCFG_SMT;
		else
			value &= ~JHB100_PADCFG_SMT;
		break;
	case PIN_CONFIG_SLEW_RATE:
		mask |= JHB100_PADCFG_SLEW;
		if (arg)
			value |= JHB100_PADCFG_SLEW;
		else
			value &= ~JHB100_PADCFG_SLEW;
		break;
	default:
		return -EINVAL;
	}

	starfive_padcfg_rmw(dev, pin, mask, value);

	return 0;
}

static int starfive_property_set(struct udevice *dev, u32 pinmux_group)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);
	struct jhb100_pinctrl_soc_info *info = priv->info;

	if (info->set_one_pinmux) {
		if (pinmux_group & IS_SET_GPIO_VAL) {
			info->set_one_pinmux(dev,
				jhb100_pinmux_pin(pinmux_group),
				jhb100_pinmux_function(pinmux_group),
				jhb100_pinmux_gpioval(pinmux_group));
		} else if (pinmux_group & IS_SET_GMAC_VSEL) {
			info->set_one_pinmux(dev,
				jhb100_pinmux_pin(pinmux_group),
				jhb100_pinmux_function(pinmux_group),
				jhb100_pinmux_gmacvsel(pinmux_group));
		} else {
			info->set_one_pinmux(dev,
				jhb100_pinmux_pin(pinmux_group),
				jhb100_pinmux_function(pinmux_group),
				GPI_NONE);
		}
	}

	return jhb100_pinmux_pin(pinmux_group);
}

const struct pinctrl_ops starfive_pinctrl_ops = {
	.set_state = pinctrl_generic_set_state,
	.pinconf_num_params	= ARRAY_SIZE(starfive_pinconf_params),
	.pinconf_params		= starfive_pinconf_params,
	.pinconf_set		= starfive_pinconf_set,
	.pinmux_property_set = starfive_property_set,
};

static int starfive_gpio_get_direction(struct udevice *dev, unsigned int off)
{
	struct udevice *pdev = dev->parent;
	struct starfive_pinctrl_priv *priv = dev_get_priv(pdev);
	struct jhb100_pinctrl_soc_info *info = priv->info;

	unsigned int aligned_offset = 4 * (off / 32);
	unsigned int shift = off % 32;
	u32 gpio_oen_mask = ((info->gpio_oen_sel_mask) << shift);
	void __iomem *reg_gpio_oen = priv->base + info->gpio_oen_sel_reg_base + aligned_offset;
	u32 doen = (readl(reg_gpio_oen) & gpio_oen_mask) >> shift;

	return doen == GPOEN_ENABLE ? GPIOF_OUTPUT : GPIOF_INPUT;
}

static int starfive_gpio_direction_input(struct udevice *dev, unsigned int off)
{
	struct udevice *pdev = dev->parent;
	struct starfive_pinctrl_priv *priv = dev_get_priv(pdev);
	struct jhb100_pinctrl_soc_info *info = priv->info;

	/* enable input and schmitt trigger */
	starfive_padcfg_rmw(pdev, off,
			    JHB100_PADCFG_IE | JHB100_PADCFG_SMT,
			    JHB100_PADCFG_IE | JHB100_PADCFG_SMT);

	if (info->set_one_pinmux)
		info->set_one_pinmux(pdev, off, 0, GPI_NONE);

	return 0;
}

static int starfive_gpio_direction_output(struct udevice *dev,
					  unsigned int off, int val)
{
	struct udevice *pdev = dev->parent;
	struct starfive_pinctrl_priv *priv = dev_get_priv(pdev);
	struct jhb100_pinctrl_soc_info *info = priv->info;

	if (info->set_one_pinmux)
		info->set_one_pinmux(pdev, off, 0, val ? GPOUT_HIGH : GPOUT_LOW);

	/* disable input, schmitt trigger and bias */
	starfive_padcfg_rmw(pdev, off,
			    JHB100_PADCFG_IE | JHB100_PADCFG_SMT |
			    JHB100_PADCFG_BIAS_MASK, 0);

	return 0;
}

static int starfive_gpio_get_value(struct udevice *dev, unsigned int off)
{
	struct udevice *pdev = dev->parent;
	struct starfive_pinctrl_priv *priv = dev_get_priv(pdev);
	struct jhb100_pinctrl_soc_info *info = priv->info;

	void __iomem *reg = priv->base + info->gpioin_reg_base
			+ ((off / GPIO_NUM_PER_WORD) << 2);

	return !!(readl(reg) & BIT(off % GPIO_NUM_PER_WORD));
}

static int starfive_gpio_set_value(struct udevice *dev,
				   unsigned int off, int val)
{
	struct udevice *pdev = dev->parent;
	struct starfive_pinctrl_priv *priv = dev_get_priv(pdev);
	struct jhb100_pinctrl_soc_info *info = priv->info;

	unsigned int aligned_offset = 4 * (off / 32);
	unsigned int shift = off % 32;
	void __iomem *reg_dout = priv->base + info->gpio_o_sel_reg_base + aligned_offset;
	u32 dout = (val ? GPOUT_HIGH : GPOUT_LOW) << shift;
	u32 mask = info->gpio_o_sel_mask << shift;

	dout |= readl(reg_dout) & ~mask;
	writel(dout, reg_dout);

	return 0;
}

static int starfive_gpio_probe(struct udevice *dev)
{
	struct gpio_dev_priv *uc_priv;
	struct udevice *pdev = dev->parent;
	struct starfive_pinctrl_priv *priv = dev_get_priv(pdev);
	struct jhb100_pinctrl_soc_info *info = priv->info;

	uc_priv = dev_get_uclass_priv(dev);
	uc_priv->bank_name = info->name;
	uc_priv->gpio_count = info->ngpios;

	if (!info->gpio_init_hw)
		return -ENXIO;

	info->gpio_init_hw(pdev);

	return 0;
}

static const struct dm_gpio_ops starfive_gpio_ops = {
	.get_function = starfive_gpio_get_direction,
	.direction_input = starfive_gpio_direction_input,
	.direction_output = starfive_gpio_direction_output,
	.get_value = starfive_gpio_get_value,
	.set_value = starfive_gpio_set_value,
};

static struct driver starfive_gpio_driver = {
	.name = "starfive_gpio",
	.id = UCLASS_GPIO,
	.probe = starfive_gpio_probe,
	.ops = &starfive_gpio_ops,
};

static int starfive_gpiochip_register(struct udevice *parent)
{
	struct uclass_driver *drv;
	struct udevice *dev;
	int ret;
	ofnode node;

	drv = lists_uclass_lookup(UCLASS_GPIO);
	if (!drv)
		return -ENOENT;

	node = dev_ofnode(parent);
	ret = device_bind_with_driver_data(parent, &starfive_gpio_driver,
					   "starfive_gpio", 0, node, &dev);

	return (ret == 0) ? 0 : ret;
}

int starfive_pinctrl_probe(struct udevice *dev,
			   const struct jhb100_pinctrl_soc_info *info)
{
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);
	int ret;

	/* Bind pinctrl_info from .data to priv */
	priv->info =
		(struct jhb100_pinctrl_soc_info *)dev_get_driver_data(dev);

	if (!priv->info)
		return -EINVAL;

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -EINVAL;

	/* gpiochip register */
	ret = starfive_gpiochip_register(dev);

	return (ret == 0) ? 0 : ret;
}
