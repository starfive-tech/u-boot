// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright 2024 StarFive, Inc. All rights reserved.
 * Author: ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

#include <clk.h>
#include <dm.h>
#include <time.h>
#include <timer.h>
#include <asm/io.h>
#include <dm/device-internal.h>
#include <linux/err.h>

#define STF_TIMER_LOAD_LSB	(0x04)
#define STF_TIMER_LOAD_MSB	(0x08)
#define STF_TIMER_VALUE_LSB	(0x0C)
#define STF_TIMER_VALUE_MSB	(0x10)
#define STF_TIMER_RELOAD_LSB	(0x14)
#define STF_TIMER_RELOAD_MSB	(0x18)
#define STF_TIMER_INT_CLR	(0x20)
#define STF_TIMER_INT_MASK	(0x24)
#define STF_TIMER_CTL		(0x28)

//Timer Control Register
#define CTRL_SINGLE_RUN		(0x1 << 0)
#define CTRL_CONSTANT_PERIOD	(0x0 << 1)
#define CTRL_FREE_RUN		(0x1 << 1)
#define CTRL_TIMER_SIZE_64	(0x1 << 2)
#define CTRL_TIMER_STOP		(0x0 << 3)
#define CTRL_TIMER_START	(0x1 << 3)

#define MAX_COUNTER_VAL_64	(0xFFFFFFFFFFFFFFFFUL)
#define MAX_COUNTER_VAL_32	(0xFFFFFFFFUL)

struct starfive_dual_timer_priv {
	void __iomem *base;
	u64 timer_size;
};

static u64 notrace starfive_dual_timer_get_count(struct udevice *dev)
{
	u32 cnt_l, cnt_h;
	struct starfive_dual_timer_priv *priv = dev_get_priv(dev);

	cnt_l = readl(priv->base + STF_TIMER_VALUE_LSB);
	cnt_h = readl(priv->base + STF_TIMER_VALUE_MSB);

	return priv->timer_size - (cnt_l | ((u64)cnt_h << 32));
}

static const struct timer_ops starfive_dual_timer_ops = {
	.get_count = starfive_dual_timer_get_count,
};

static int starfive_dual_timer_probe(struct udevice *dev)
{
	struct timer_dev_priv *uc_priv = dev_get_uclass_priv(dev);
	struct starfive_dual_timer_priv *priv = dev_get_priv(dev);
	int timer_channel;
	struct clk clk;
	int ret;
	u32 reg_val = 0;

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -EINVAL;

	timer_channel = dev_read_u32_default(dev, "channel", 0);
	priv->base = priv->base + (0x40 * timer_channel);

	/* Get clock rate from channel selected */
	ret = clk_get_by_index(dev, timer_channel + 1, &clk);
	if (ret)
		return ret;

	ret = clk_enable(&clk);
	if (ret)
		return ret;
	uc_priv->clock_rate = clk_get_rate(&clk);

	/*
	 * Initiate timer, channel 0
	 * Unmask Interrupt Mask
	 */
	writel(0, priv->base + STF_TIMER_INT_MASK);

	/* Set Reload value */
	priv->timer_size = dev_read_bool(dev, "timer-32bit") ? MAX_COUNTER_VAL_32
			   : MAX_COUNTER_VAL_64;
	writel(priv->timer_size & 0xFFFFFFFF, priv->base + STF_TIMER_LOAD_LSB);
	writel((priv->timer_size >> 32) & 0xFFFFFFFF, priv->base + STF_TIMER_LOAD_MSB);

	/* Single run mode Setting */
	if (dev_read_bool(dev, "single-run"))
		reg_val |= CTRL_SINGLE_RUN;

	/* Use 64-bit timer */
	if (!dev_read_bool(dev, "timer-32bit"))
		reg_val	|= CTRL_TIMER_SIZE_64;

	/* Enable to start timer */
	reg_val |= CTRL_TIMER_START;
	writel(reg_val, priv->base + STF_TIMER_CTL);

	return 0;
}

static const struct udevice_id starfive_dual_timer_ids[] = {
	{ .compatible = "starfive,jhb100-timer" },
	{ }
};

U_BOOT_DRIVER(jhb100_starfive_dual_timer) = {
	.name		= "starfive_dual_timer",
	.id		= UCLASS_TIMER,
	.of_match	= starfive_dual_timer_ids,
	.probe		= starfive_dual_timer_probe,
	.ops		= &starfive_dual_timer_ops,
	.priv_auto	= sizeof(struct starfive_dual_timer_priv),
};
