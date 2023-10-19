// SPDX-License-Identifier: GPL-2.0+ OR BSD-3-Clause
/*
 * Copyright (c) 2021 StarFive Technology Co., Ltd.
 */

#include <common.h>
#include <dm.h>
#include <fdtdec.h>
#include <init.h>
#include <ram.h>
#include <syscon.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <clk.h>
#include <wait_bit.h>
#include <linux/bitops.h>

DECLARE_GLOBAL_DATA_PTR;

struct starfive_ddrctl {
	volatile u32 ctl_settings[1];
};

struct starfive_ddrphy {
	volatile u32 phy_settings[1];
};

/**
 * struct starfive_ddr_info
 *
 * @dev: pointer for the device
 * @info: UCLASS RAM information
 * @clk: clock
 * @ctl: controller base address
 * @phy: PHY base address
 */
struct starfive_ddr_info {
	struct udevice *dev;
	struct ram_info info;
	struct clk clk;
	struct starfive_ddrctl *ctl;
	struct starfive_ddrphy *phy;
};

struct starfive_ddr_params {
	struct starfive_ddrctl ctrl_regs;
	struct starfive_ddrphy phy_regs;
};

struct starfive_ddr_plat {
	struct starfive_ddr_params ddr_params;
};

static int starfive_ddr_probe(struct udevice *dev)
{
	struct starfive_ddr_info *priv = dev_get_priv(dev);
#if defined(CONFIG_SPL_BUILD)
	int ret;
#endif

	debug("starfive_ddr_probe\n");

	/* Get memory base and size */
	fdtdec_setup_mem_size_base();
	priv->info.base = gd->ram_base;
	priv->info.size = gd->ram_size;

#if defined(CONFIG_SPL_BUILD)
	debug("starfive_ddr_probe probing clock and setup ctl/phy settings\n");
	priv->dev = dev;

	ret = clk_get_by_index(dev, 0, &priv->clk);
	if (ret) {
		debug("clk_get_by_index error:%d\n", ret);
		return ret;
	}
#endif

	return 0;
}

static int starfive_ddr_get_info(struct udevice *dev, struct ram_info *info)
{
	struct starfive_ddr_info *priv = dev_get_priv(dev);

	*info = priv->info;

	return 0;
}

static struct ram_ops starfive_ddr_ops = {
	.get_info = starfive_ddr_get_info,
};

static const struct udevice_id starfive_ddr_ids[] = {
	{ .compatible = "starfive,dubhe-ddr" },
	{ }
};

U_BOOT_DRIVER(starfive_ddr) = {
	.name = "starfive_ddr",
	.id = UCLASS_RAM,
	.of_match = starfive_ddr_ids,
	.ops = &starfive_ddr_ops,
	.probe = starfive_ddr_probe,
	.priv_auto = sizeof(struct starfive_ddr_info),
#if defined(CONFIG_SPL_BUILD)
	.plat_auto = sizeof(struct starfive_ddr_plat),
#endif
};
