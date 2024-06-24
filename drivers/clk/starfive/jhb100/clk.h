/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#ifndef __CLK_STARFIVE_H
#define __CLK_STARFIVE_H

/* the number of fixed clocks in DTS */
#define JHB100_EXTCLK_END		14

#define JHB100_SYSCLK_NUM_CLKS		(JHB100_SYSCLK_BMCPER2_125_OSC + 1)
#define JHB100_SYS1CLK_NUM_CLKS		(JHB100_SYS1CLK_BMCPER3_125_OSC + 1)
#define JHB100_SYS2CLK_NUM_CLKS		(JHB100_SYS2CLK_BMCPER0_PLL6 + 1)
#define JHB100_PER0CLK_NUM_CLKS		(JHB100_PER0CLK_125_I3C15 + 1)
#define JHB100_PER1CLK_NUM_CLKS		(JHB100_PER1CLK_MAIN_ICG_EN_UFS + 1)
#define JHB100_PER2CLK_NUM_CLKS		(JHB100_PER2CLK_MAIN_ICG_EN_GMAC3 + 1)
#define JHB100_PER3CLK_NUM_CLKS		(JHB100_PER3CLK_MAIN_ICG_EN_GMAC1_TX_I + 1)

#define STARFIVE_CLK_ENABLE_SHIFT	31 /* [31] */
#define STARFIVE_CLK_INVERT_SHIFT	30 /* [30] */
#define STARFIVE_CLK_MUX_SHIFT		24 /* [29:24] */
#define STARFIVE_CLK_DIV_SHIFT		0 /* [23:0] */

#define OFFSET(id)			((id) * 4)
#define JHB100_SYS_ID_TRANS(id)		(JHB100_EXTCLK_END + (id))
#define JHB100_SYS1_ID_TRANS(id)	(JHB100_SYS_ID_TRANS(JHB100_SYSCLK_NUM_CLKS) + (id))
#define JHB100_SYS2_ID_TRANS(id)	(JHB100_SYS1_ID_TRANS(JHB100_SYS1CLK_NUM_CLKS) + (id))
#define JHB100_PER0_ID_TRANS(id)	(JHB100_SYS2_ID_TRANS(JHB100_SYS2CLK_NUM_CLKS) + (id))
#define JHB100_PER1_ID_TRANS(id)	(JHB100_PER0_ID_TRANS(JHB100_PER0CLK_NUM_CLKS) + (id))
#define JHB100_PER2_ID_TRANS(id)	(JHB100_PER1_ID_TRANS(JHB100_PER1CLK_NUM_CLKS) + (id))
#define JHB100_PER3_ID_TRANS(id)	(JHB100_PER2_ID_TRANS(JHB100_PER2CLK_NUM_CLKS) + (id))
#define MAX_NUM_PARENTS			2

#define _JHB100_CLK_OF_XLATE(_name)						\
static int jhb100_##_name##_clk_of_xlate(struct clk *clk,			\
					 struct ofnode_phandle_args *args)	\
{										\
	if (args->args_count > 1) {						\
		debug("Invalid args_count: %d\n", args->args_count);		\
		return -EINVAL;							\
	}									\
	if (args->args_count)							\
		clk->id = starfive_clk_id_trans(_name, args->args[0]);		\
	else									\
		clk->id = 0;							\
										\
	return 0;								\
}										\

#define JHB100_CLK_OF_XLATE(name)	_JHB100_CLK_OF_XLATE(name)

#define _JHB100_CLK_OPS(_name)					\
static const struct clk_ops jhb100_##_name##_clk_ops = {	\
	.set_rate = ccf_clk_set_rate,				\
	.get_rate = ccf_clk_get_rate,				\
	.set_parent = ccf_clk_set_parent,			\
	.enable = ccf_clk_enable,				\
	.disable = ccf_clk_disable,				\
	.of_xlate = jhb100_##_name##_clk_of_xlate,		\
}

#define JHB100_CLK_OPS(name)		_JHB100_CLK_OPS(name)

enum clk_component_t {
	CLK_GATE = 0,
	CLK_INV,
	CLK_MUX,
	CLK_DIVIDER,
	CLK_MDIV,
	CLK_GDIV,
	CLK_GMUX,
	CLK_COMPOSITE
};

struct clk_info {
	unsigned long id;
	const char *name;
	const char *parent_name;
	const char * const *parent_names;
	enum clk_component_t component;
	unsigned char div_width;	/* 0 if not used */
};

enum clk_type_t {
	sys = 0,
	sys1,
	sys2,
	per0,
	per1,
	per2,
	per3
};

#endif
