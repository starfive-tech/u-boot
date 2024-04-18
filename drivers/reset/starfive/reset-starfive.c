// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2024 StarFive, Inc <zhiwei.lim@starfivetech.com>
 *
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING
 * CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER
 * FOR THEM TO SAVE TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE
 * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY
 * CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE
 * BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION
 * WITH THEIR PRODUCTS.
 */

#include <dm.h>
#include <syscon.h>
#include <log.h>
#include <malloc.h>
#include <reset-uclass.h>
#include <dm/device_compat.h>
#include <dm/of_access.h>
#include <dt-bindings/reset/starfive,jhb100-crg.h>
#include <linux/iopoll.h>
#include "reset-starfive.h"

#define BITS_PER_REG 32

static int starfive_reset_update(struct reset_ctl *rst, bool assert)
{
	struct starfive_reset_priv *priv = dev_get_priv(rst->dev);
	int id = rst->id;
	u32 bank;
	u32 mask, value, done = 0;
	void __iomem *reg;

	bank = id / BITS_PER_REG;
	mask = BIT(id % BITS_PER_REG);

	reg = priv->reg + priv->starfive_reset_info->assert_offset + bank * sizeof(u32);
	value = readl(reg);

	if (!assert)
		done ^= mask;

	if (assert)
		value |= mask;
	else
		value &= ~mask;

	writel(value, reg);

	reg = priv->reg + priv->starfive_reset_info->status_offset + bank * sizeof(u32);

	return readl_poll_timeout(reg, value, (value & mask) == done, 1000);
}

static int starfive_reset_assert(struct reset_ctl *rst)
{
	return starfive_reset_update(rst, true);
}

static int starfive_reset_deassert(struct reset_ctl *rst)
{
	return starfive_reset_update(rst, false);
}

static int starfive_reset_request(struct reset_ctl *rst)
{
	int ret;

	ret = starfive_reset_assert(rst);
	if (ret)
		return ret;

	return starfive_reset_deassert(rst);
}

static int starfive_reset_free(struct reset_ctl *rst)
{
	struct starfive_reset_priv *priv = dev_get_priv(rst->dev);

	debug("%s(rst=%p) (dev=%p, id=%lu) (nr_reset=%d)\n", __func__,
	      rst, rst->dev, rst->id, priv->starfive_reset_info->nr_resets);

	return 0;
}

const struct reset_ops starfive_reset_ops = {
	.request = starfive_reset_request,
	.rfree = starfive_reset_free,
	.rst_assert = starfive_reset_assert,
	.rst_deassert = starfive_reset_deassert,
};
