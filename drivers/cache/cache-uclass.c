// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2019 Intel Corporation <www.intel.com>
 */

#define LOG_CATEGORY UCLASS_CACHE

#include <common.h>
#include <cache.h>
#include <dm.h>

int cache_get_info(struct udevice *dev, struct cache_info *info)
{
	struct cache_ops *ops = cache_get_ops(dev);

	if (!ops->get_info)
		return -ENOSYS;

	return ops->get_info(dev, info);
}

int cache_enable(struct udevice *dev)
{
	struct cache_ops *ops = cache_get_ops(dev);

	if (!ops->enable)
		return -ENOSYS;

	return ops->enable(dev);
}

int cache_disable(struct udevice *dev)
{
	struct cache_ops *ops = cache_get_ops(dev);

	if (!ops->disable)
		return -ENOSYS;

	return ops->disable(dev);
}


int flush_range(struct udevice *dev, unsigned long start, unsigned long end)
{
	struct cache_ops *ops = cache_get_ops(dev);

	if (!ops->flush_range)
		return -ENOSYS;

	return ops->flush_range(dev, start, end);
}

UCLASS_DRIVER(cache) = {
	.id		= UCLASS_CACHE,
	.name		= "cache",
	.post_bind	= dm_scan_fdt_dev,
};
