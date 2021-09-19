// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (C) 2021 SiFive
 */

#include <common.h>
#include <cache.h>
#include <dm.h>
#include <asm/io.h>
#include <linux/bitfield.h>
#include <fdt_support.h>

#define SIFIVE_CCACHE_CONFIG		0x000
#define SIFIVE_CCACHE_CONFIG_WAYS	GENMASK(15, 8)

#define SIFIVE_CCACHE_WAY_ENABLE	0x008
#define SIFIVE_CCACHE_FLUSH64		0x200

static bool range_check = false;

struct sifive_ccache {
	void __iomem *base;
	int cache_line_size;
	phys_addr_t flush_start; /* Start physical address of flush range limit. */
	phys_addr_t flush_end; /* End physical address of flush range limit. */
};

static int sifive_ccache_enable(struct udevice *dev)
{
	struct sifive_ccache *priv = dev_get_priv(dev);
	u32 config;
	u32 ways;

	/* Enable all ways of composable cache */
	config = readl(priv->base + SIFIVE_CCACHE_CONFIG);
	ways = FIELD_GET(SIFIVE_CCACHE_CONFIG_WAYS, config);

#if CONFIG_IS_ENABLED(SIFIVE_CCACHE_WAYENABLE_OPT)
	if (CONFIG_SIFIVE_CCACHE_WAYENABLE_NUM < ways)
		ways = CONFIG_SIFIVE_CCACHE_WAYENABLE_NUM;
#endif
	writel(ways - 1, priv->base + SIFIVE_CCACHE_WAY_ENABLE);

	return 0;
}

static int sifive_ccache_get_info(struct udevice *dev, struct cache_info *info)
{
	struct sifive_ccache *priv = dev_get_priv(dev);

	info->base = (uintptr_t)priv->base;

	return 0;
}

static int sifive_ccache_flush_range(struct udevice *dev,
				     unsigned long start, unsigned long end)
{
	unsigned long line;
	volatile unsigned long *flush64;
	struct sifive_ccache *priv = dev_get_priv(dev);

	if (range_check) {
		/* make sure the address is in the range */
		if(start > end ||
		   start < priv->flush_start || end > priv->flush_end)
			return -EINVAL;
	} else {
		pr_warn("skip checking range.");
	}

	/* make sure we won't get into infinite loop below */
	if (!priv->cache_line_size) {
		pr_warn("missing cache_line_size, skip flush.");
		return -EINVAL;
	}

	flush64 = (volatile unsigned long *)(priv->base + SIFIVE_CCACHE_FLUSH64);

	/* memory barrier */
	mb();
	for (line = start; line < end; line += priv->cache_line_size)
		(*flush64) = line;
	/* memory barrier */
	mb();

	return 0;
}

static const struct cache_ops sifive_ccache_ops = {
	.enable = sifive_ccache_enable,
	.get_info = sifive_ccache_get_info,
	.flush_range = sifive_ccache_flush_range,
};

static int sifive_ccache_probe(struct udevice *dev)
{
	int ret;
	uint64_t addr, len;
	struct sifive_ccache *priv = dev_get_priv(dev);

	priv->base = dev_read_addr_ptr(dev);
	if (!priv->base)
		return -EINVAL;

	priv->cache_line_size =
		dev_read_u32_default(dev, "cache-line-size",
				     CONFIG_SYS_CACHELINE_SIZE);

	/* only read range index 0 */
	ret = fdt_read_range((void *)gd->fdt_blob, dev_of_offset(dev), 0,
			     NULL, &addr, &len);
	if (ret) {
		pr_warn("missing flush range, ignore range check.");
		return 0;
	}

	range_check = true;
	priv->flush_start = addr;
	priv->flush_end = addr + len - 1;

	return 0;
}

static const struct udevice_id sifive_ccache_ids[] = {
	{ .compatible = "sifive,fu540-c000-ccache" },
	{ .compatible = "sifive,fu740-c000-ccache" },
	{}
};

U_BOOT_DRIVER(sifive_ccache) = {
	.name = "sifive_ccache",
	.id = UCLASS_CACHE,
	.of_match = sifive_ccache_ids,
	.probe = sifive_ccache_probe,
	.priv_auto = sizeof(struct sifive_ccache),
	.ops = &sifive_ccache_ops,
};
