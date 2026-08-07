/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Pinctrl / GPIO driver for StarFive SoC
 *
 * Copyright (C) 2024 Shanghai StarFive Technology Co., Ltd.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <clk.h>
#include <reset.h>

#define STARFIVE_PINCTRL(a, b) { .number = a, .name = b }

extern const struct pinctrl_ops starfive_pinctrl_ops;

struct starfive_pinctrl_pin {
	unsigned int number;
	const char *name;
	void *drv_data;
};

struct jhb100_gpio_func_sel {
	u16 offset;
	u8 shift;
	u8 max;
};

struct jhb100_pinctrl_soc_info {
	const struct starfive_pinctrl_pin *pins;
	unsigned int npins;
	unsigned int ngpios;
	const char *name;

	/* gpio gpio_o_sel and gpio_oen_sel register */
	unsigned int gpio_o_sel_reg_base;
	unsigned int gpio_o_sel_mask;
	unsigned int gpio_oen_sel_reg_base;
	unsigned int gpio_oen_sel_mask;
	unsigned int gpio_func_sel_reg_base;
	unsigned int gpio_func_sel_mask;
	unsigned int gpioin_reg_base;

	const struct jhb100_gpio_func_sel *func_sel;
	void (*gpio_init_hw)(struct udevice *dev);
	int (*set_one_pinmux)(struct udevice *dev, u32 pin,
			      u32 func, int gpioval);
	int (*get_padcfg_base)(struct udevice *dev, u32 pin);
	bool (*is_vselcfg)(u32 pin);
	bool (*is_i3cpad)(u32 pin);
	bool is_vga_adc_pad;
	u32 debouce_width_mask;
};

/*
 * struct starfive_pinctrl_priv - private data for Starfive pinctrl driver
 *
 * @padctl_base: base address of the pinctrl device
 * @info: SoC specific data & function
 */
struct starfive_pinctrl_priv {
	void __iomem *base;
	struct jhb100_pinctrl_soc_info *info;
	struct clk_bulk clks;
	struct reset_ctl_bulk resets;
};

void starfive_set_gpioval(struct udevice *dev, unsigned int pin,
			  unsigned int val);
void starfive_set_function(struct udevice *dev, u32 pin, u32 func);
int starfive_set_one_pin_mux(struct udevice *dev, u32 pin,
			     u32 func, int gpioval);
int starfive_pinctrl_probe(struct udevice *dev,
			   const struct jhb100_pinctrl_soc_info *info);
int starfive_pinctrl_bind(struct udevice *dev);
int starfive_pinctrl_enable_clk_reset(struct udevice *dev);
