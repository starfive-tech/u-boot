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
#define JHB100_I3C_PADCFG_IE		BIT(0)
#define JHB100_I3C_PADCFG_SMT		BIT(7)
#define JHB100_I3C_PADCFG_MODE_SEL	GENMASK(2, 1)
#define JHB100_I3C_PADCFG_MODE_SHIFT	1
#define JHB100_I2C_LEGACY_FM_PLUS	2

#define JHB100_VGA_ADC_PADCFG_SMT	BIT(7)
#define JHB100_VGA_ADC_PADCFG_SLEW	BIT(6)
#define JHB100_VGA_ADC_PADCFG_PU	BIT(5)
#define JHB100_VGA_ADC_PADCFG_PD	BIT(4)
#define JHB100_VGA_ADC_PADCFG_IE	BIT(3)
#define JHB100_VGA_ADC_PADCFG_BIAS_MASK	(JHB100_VGA_ADC_PADCFG_PU | JHB100_VGA_ADC_PADCFG_PD)
#define JHB100_VGA_ADC_PADCFG_DS_MASK	GENMASK(2, 0)

#define JHB100_PADCFG_VSEL_SHIFT	2
#define JHB100_PADCFG_DB_WIDTH_SHIFT	15

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

#define MAX_DEBOUNCE_WIDTH_STAGES	0x1ffff

#define STARFIVE_PIN_CONFIG_GMAC_VSEL		(PIN_CONFIG_END + 1)
#define STARFIVE_PIN_CONFIG_DEBOUNCE_WIDTH	(PIN_CONFIG_END + 2)
#define STARFIVE_PIN_DRIVE_I2C_FAST_MODE_PLUS	(PIN_CONFIG_END + 3)

/*
 * mux bits:
 * | 31 - 10  |  9 - 8   |  7 - 0  |
 * | reserved | function | gpio nr |
 *
 * func: function value: 0, 1, 2, and 3
 * gpio nr: gpio pad number, 0 through ngpios - 1
 */
static u32 jhb100_pinmux_function(u32 v)
{
	return (v & GENMASK(9, 8)) >> 8;
}

static unsigned int jhb100_pinmux_pin(u32 v)
{
	return v & GENMASK(7, 0);
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
	{ "starfive,gmac_vsel",	STARFIVE_PIN_CONFIG_GMAC_VSEL,	0 },
	{ "starfive,debounce_width", STARFIVE_PIN_CONFIG_DEBOUNCE_WIDTH, 0 },
	{ "starfive,drive-i2c-fast-mode-plus", STARFIVE_PIN_DRIVE_I2C_FAST_MODE_PLUS, 0},
};

static const u8 jhb100_drive_strength_mA[4] = { 2, 4, 8, 12 };
static const u8 jhb100_vga_adc_drive_strength_mA[8] = { 2, 5, 8, 10, 14, 16, 18, 20 };

static u32 jhb100_padcfg_ds_from_mA(u32 v)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(jhb100_drive_strength_mA); i++) {
		if (v <= jhb100_drive_strength_mA[i])
			break;
	}
	return i;
}

static u32 jhb100_vga_adc_padcfg_ds_from_mA(u32 v)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(jhb100_vga_adc_drive_strength_mA); i++) {
		if (v <= jhb100_vga_adc_drive_strength_mA[i])
			break;
	}
	return i;
}

static u32 jhb100_padcfg_ds_from_uA(u32 v)
{
	/* Convert from uA to mA */
	v /= 1000;

	return jhb100_padcfg_ds_from_mA(v);
}

static u32 jhb100_vga_adc_padcfg_ds_from_uA(u32 v)
{
	/* Convert from uA to mA */
	v /= 1000;

	return jhb100_vga_adc_padcfg_ds_from_mA(v);
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
	struct starfive_pinctrl_priv *priv = dev_get_priv(dev);
	struct jhb100_pinctrl_soc_info *info = priv->info;
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
		if (info->is_i3cpad && info->is_i3cpad(pin)) {
			return -EINVAL;
		} else if (info->is_vga_adc_pad) {
			mask |= JHB100_VGA_ADC_PADCFG_DS_MASK;
			value = (value & ~JHB100_VGA_ADC_PADCFG_DS_MASK) |
				jhb100_vga_adc_padcfg_ds_from_mA(arg);
		} else {
			mask |= JHB100_PADCFG_DS_MASK;
			value = (value & ~JHB100_PADCFG_DS_MASK) |
				jhb100_padcfg_ds_from_mA(arg);
		}
		break;
	case PIN_CONFIG_DRIVE_STRENGTH_UA:
		if (info->is_i3cpad && info->is_i3cpad(pin)) {
			return -EINVAL;
		} else if (info->is_vga_adc_pad) {
			mask |= JHB100_VGA_ADC_PADCFG_DS_MASK;
			value = (value & ~JHB100_VGA_ADC_PADCFG_DS_MASK) |
				jhb100_vga_adc_padcfg_ds_from_uA(arg);
		} else {
			mask |= JHB100_PADCFG_DS_MASK;
			value = (value & ~JHB100_PADCFG_DS_MASK) |
				jhb100_padcfg_ds_from_uA(arg);
		}
		break;
	case PIN_CONFIG_INPUT_ENABLE:
		if (info->is_vselcfg && info->is_vselcfg(pin)) {
			mask |= JHB100_RGMII_PADCFG_IE;
			if (arg)
				value |= JHB100_RGMII_PADCFG_IE;
			else
				value &= ~JHB100_RGMII_PADCFG_IE;
		} else if (info->is_i3cpad && info->is_i3cpad(pin)) {
			mask |= JHB100_I3C_PADCFG_IE;
			if (arg)
				value |= JHB100_I3C_PADCFG_IE;
			else
				value &= ~JHB100_I3C_PADCFG_IE;
		} else if (info->is_vga_adc_pad) {
			mask |= JHB100_VGA_ADC_PADCFG_IE;
			if (arg)
				value |= JHB100_VGA_ADC_PADCFG_IE;
			else
				value &= ~JHB100_VGA_ADC_PADCFG_IE;
		} else {
			mask |= JHB100_PADCFG_IE;
			if (arg)
				value |= JHB100_PADCFG_IE;
			else
				value &= ~JHB100_PADCFG_IE;
		}
		break;
	case PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		if (info->is_i3cpad && info->is_i3cpad(pin)) {
			mask |= JHB100_I3C_PADCFG_SMT;
			if (arg)
				value |= JHB100_I3C_PADCFG_SMT;
			else
				value &= ~JHB100_I3C_PADCFG_SMT;
		} else if (info->is_vga_adc_pad) {
			mask |= JHB100_VGA_ADC_PADCFG_SMT;
			if (arg)
				value |= JHB100_VGA_ADC_PADCFG_SMT;
			else
				value &= ~JHB100_VGA_ADC_PADCFG_SMT;
		} else {
			mask |= JHB100_PADCFG_SMT;
			if (arg)
				value |= JHB100_PADCFG_SMT;
			else
				value &= ~JHB100_PADCFG_SMT;
		}
		break;
	case PIN_CONFIG_SLEW_RATE:
		if (info->is_i3cpad && info->is_i3cpad(pin)) {
			return -EINVAL;
		} else if (info->is_vselcfg && info->is_vselcfg(pin)) {
			mask |= JHB100_RGMII_PADCFG_SLEW;
			if (arg)
				value |= JHB100_RGMII_PADCFG_SLEW;
			else
				value &= ~JHB100_RGMII_PADCFG_SLEW;
		} else {
			mask |= JHB100_PADCFG_SLEW;
			if (arg)
				value |= JHB100_PADCFG_SLEW;
			else
				value &= ~JHB100_PADCFG_SLEW;
		}
		break;
	case STARFIVE_PIN_CONFIG_DEBOUNCE_WIDTH:
		mask |= info->debouce_width_mask;
		if (arg > MAX_DEBOUNCE_WIDTH_STAGES)
			arg = MAX_DEBOUNCE_WIDTH_STAGES;
		value |= arg ? (arg << JHB100_PADCFG_DB_WIDTH_SHIFT) : 0;
		break;
	case STARFIVE_PIN_CONFIG_GMAC_VSEL:
		if (info->is_vselcfg && info->is_vselcfg(pin)) {
			mask |= JHB100_RGMII_PADCFG_VSEL;
			value |= arg ? (1 << JHB100_PADCFG_VSEL_SHIFT) : 0;
		} else {
			return -EINVAL;
		}
		break;
	case STARFIVE_PIN_DRIVE_I2C_FAST_MODE_PLUS:
		if (info->is_i3cpad && info->is_i3cpad(pin)) {
			mask |= JHB100_I3C_PADCFG_MODE_SEL;
			value |= JHB100_I2C_LEGACY_FM_PLUS <<
				 JHB100_I3C_PADCFG_MODE_SHIFT;
		} else {
			return -EINVAL;
		}
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

	if (info->set_one_pinmux)
		info->set_one_pinmux(dev,
			jhb100_pinmux_pin(pinmux_group),
			jhb100_pinmux_function(pinmux_group),
			GPI_NONE);

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

	if (info->is_vga_adc_pad)
		starfive_padcfg_rmw(pdev, off,
				    JHB100_VGA_ADC_PADCFG_IE | JHB100_VGA_ADC_PADCFG_SMT,
				    JHB100_VGA_ADC_PADCFG_IE | JHB100_VGA_ADC_PADCFG_SMT);
	else if (info->is_vselcfg && info->is_vselcfg(off))
		starfive_padcfg_rmw(pdev, off, JHB100_RGMII_PADCFG_IE, JHB100_RGMII_PADCFG_IE);
	else if (info->is_i3cpad && info->is_i3cpad(off))
		starfive_padcfg_rmw(pdev, off,
				    JHB100_I3C_PADCFG_IE | JHB100_I3C_PADCFG_SMT,
				    JHB100_I3C_PADCFG_IE | JHB100_I3C_PADCFG_SMT);
	else
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

	if (info->is_vga_adc_pad)
		starfive_padcfg_rmw(pdev, off,
				    JHB100_VGA_ADC_PADCFG_IE | JHB100_VGA_ADC_PADCFG_SMT |
				    JHB100_VGA_ADC_PADCFG_BIAS_MASK, JHB100_VGA_ADC_PADCFG_IE);
	else if (info->is_vselcfg && info->is_vselcfg(off))
		starfive_padcfg_rmw(pdev, off, JHB100_RGMII_PADCFG_IE, JHB100_RGMII_PADCFG_IE);
	else if (info->is_i3cpad && info->is_i3cpad(off))
		starfive_padcfg_rmw(pdev, off,
				    JHB100_I3C_PADCFG_IE | JHB100_I3C_PADCFG_SMT,
				    JHB100_I3C_PADCFG_IE);
	else
		starfive_padcfg_rmw(pdev, off,
				    JHB100_PADCFG_IE | JHB100_PADCFG_SMT |
				    JHB100_PADCFG_BIAS_MASK, JHB100_PADCFG_IE);

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

int starfive_pinctrl_bind(struct udevice *dev)
{
	/* The io-domain driver does not have a device node, so bind it here */
	return device_bind_driver_to_node(dev, "starfive_io_domain", dev->name,
		dev_ofnode(dev), NULL);
}
