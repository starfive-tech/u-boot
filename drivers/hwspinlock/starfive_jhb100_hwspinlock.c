// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	Wei Sheng Ch'ng <weisheng.chng@starfivetech.com>
 *
 */
#define LOG_CATEGORY UCLASS_HWSPINLOCK

#include <clk.h>
#include <dm.h>
#include <hwspinlock.h>
#include <malloc.h>
#include <asm/io.h>
#include <linux/bitops.h>

/* JHB100 HW Spinlock attributes */
#define STARFIVE_JHB100_MUTEX_NUM_LOCKS		0x10

/* JHB100 HW Spinlock register offset */
#define STARFIVE_JHB100_HWS_AP_LOCK_REQ		0x8
#define STARFIVE_JHB100_HWS_AP_LOCK_REL		0xC
#define STARFIVE_JHB100_HWS_LOCK_STAT		0x10
#define STARFIVE_JHB100_HWS_CSR_RSV_ADDR_WIDTH	0x1FFC

/* Lock request and release bit */
#define AP_LOCK_BIT				BIT(0)

/* Lock and unlock utility */
#define AP_DO_LOCK(addr, a)	writel((AP_LOCK_BIT << (a)), (void *)((addr) + \
					STARFIVE_JHB100_HWS_AP_LOCK_REQ))
#define AP_DO_UNLOCK(addr, a)	writel((AP_LOCK_BIT << (a)), (void *)((addr) + \
					STARFIVE_JHB100_HWS_AP_LOCK_REL))

/* Common lock status */
#define LOCK_STAT_IDX(addr, a)	((readl((void *)((addr) + STARFIVE_JHB100_HWS_LOCK_STAT)) & \
				  GENMASK(1 + 2 * (a), 2 * (a))) >> 2 * (a))

#define STAT_UNLOCK		0
#define STAT_SC_LOCK		0x1
#define STAT_AP_LOCK		0x2

struct starfive_jhb100_hws_priv {
	fdt_addr_t base;
};

static int starfive_jhb100_hws_lock(struct udevice *dev, int idx)
{
	struct starfive_jhb100_hws_priv *priv = dev_get_priv(dev);

	/* Minimal checks as HW spinlock needs to be quick */
	if (idx >= STARFIVE_JHB100_MUTEX_NUM_LOCKS)
		return -EINVAL;

	/* It's locked! */
	if (LOCK_STAT_IDX(priv->base, idx) == STAT_SC_LOCK)
		return -EBUSY;

	/* Do a lock */
	AP_DO_LOCK(priv->base, idx);

	if (LOCK_STAT_IDX(priv->base, idx) != STAT_AP_LOCK)
		return -EINVAL;

	return 0;
}

static int starfive_jhb100_hws_unlock(struct udevice *dev, int idx)
{
	struct starfive_jhb100_hws_priv *priv = dev_get_priv(dev);

	/* Minimal checks as HW spinlock needs to be quick */
	if (idx >= STARFIVE_JHB100_MUTEX_NUM_LOCKS)
		return -EINVAL;

	/* It's unlocked! */
	if (LOCK_STAT_IDX(priv->base, idx) != STAT_AP_LOCK)
		return -EINVAL;

	/* Do an unlock */
	AP_DO_UNLOCK(priv->base, idx);

	return 0;
}

static int starfive_jhb100_hws_probe(struct udevice *dev)
{
	struct starfive_jhb100_hws_priv *priv = dev_get_priv(dev);
	struct clk clk;
	int ret;

	priv->base = dev_read_addr(dev);
	if (priv->base == FDT_ADDR_T_NONE)
		return -EINVAL;

	ret = clk_get_by_index(dev, 0, &clk);
	if (ret)
		return ret;

	return clk_enable(&clk);
}

static const struct hwspinlock_ops starfive_jhb100_hwspinlock_ops = {
	.lock = starfive_jhb100_hws_lock,
	.unlock = starfive_jhb100_hws_unlock,
};

static const struct udevice_id starfive_jhb100_hwspinlock_ids[] = {
	{ .compatible = "starfive,jhb100-hwspinlock" },
	{}
};

U_BOOT_DRIVER(starfive_jhb100_hwspinlock) = {
	.name = "starfive_jhb100_hwspinlock",
	.id = UCLASS_HWSPINLOCK,
	.of_match = starfive_jhb100_hwspinlock_ids,
	.ops = &starfive_jhb100_hwspinlock_ops,
	.probe = starfive_jhb100_hws_probe,
	.priv_auto	= sizeof(struct starfive_jhb100_hws_priv),
};
