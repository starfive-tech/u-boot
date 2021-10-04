<<<<<<< HEAD
// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 StarFive Technology Co., Ltd.
 * Author: Yanhong Wang<yanhong.wang@starfivetech.com>
 */

#include <common.h>
#include <asm/arch/regs.h>
#include <asm/io.h>
#include <clk.h>
#include <dm.h>
#include <fdtdec.h>
#include <init.h>
#include <linux/bitops.h>
#include <linux/sizes.h>
#include <linux/delay.h>
#include <ram.h>
#include <reset.h>

#include "starfive_ddr.h"

DECLARE_GLOBAL_DATA_PTR;

struct starfive_ddr_priv {
	struct udevice	*dev;
	struct ram_info info;
	void __iomem	*ctrlreg;
	void __iomem	*phyreg;
	struct reset_ctl_bulk rst;
	struct clk	clk;
	u32	fre;
};

static int starfive_ddr_setup(struct udevice *dev, struct starfive_ddr_priv *priv)
{
	enum ddr_size_t size;

	switch (priv->info.size) {
	case SZ_2G:
		size = DDR_SIZE_2G;
		break;

	case SZ_4G:
		size = DDR_SIZE_4G;
		break;

	case 0x200000000:
		size = DDR_SIZE_8G;
		break;

	case 0x400000000:
	default:
		pr_err("unsupport size %lx\n", priv->info.size);
		return -EINVAL;
	}

	ddr_phy_train(priv->phyreg + (PHY_BASE_ADDR << 2));
	ddr_phy_util(priv->phyreg + (PHY_AC_BASE_ADDR << 2));
	ddr_phy_start(priv->phyreg, size);

	DDR_REG_SET(BUS, DDR_BUS_OSC_DIV2);
	ddrcsr_boot(priv->ctrlreg, priv->ctrlreg + SEC_CTRL_ADDR,
		    priv->phyreg, size);

	return 0;
}

static int starfive_ddr_probe(struct udevice *dev)
{
	struct starfive_ddr_priv *priv = dev_get_priv(dev);
	fdt_addr_t addr;
	u64 rate;
	int ret;

	priv->info.base = gd->ram_base;
	priv->info.size = gd->ram_size;

	priv->dev = dev;
	addr = dev_read_addr_index(dev, 0);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->ctrlreg = (void __iomem *)addr;
	addr = dev_read_addr_index(dev, 1);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	priv->phyreg = (void __iomem *)addr;
	ret = dev_read_u32(dev, "clock-frequency", &priv->fre);
	if (ret)
		return ret;

	switch (priv->fre) {
	case 2133:
		rate = 1066000000;
		break;

	case 2800:
		rate = 1400000000;
		break;

	default:
		pr_err("Unknown DDR frequency %d\n", priv->fre);
		return  -EINVAL;
	};

	ret = reset_get_bulk(dev, &priv->rst);
	if (ret)
		return ret;

	ret = reset_deassert_bulk(&priv->rst);
	if (ret < 0)
		return ret;

	ret = clk_get_by_index(dev, 0, &priv->clk);
	if (ret)
		goto err_free_reset;

	ret = clk_set_rate(&priv->clk, rate);
	if (ret < 0)
		goto err_free_reset;

	ret = starfive_ddr_setup(dev, priv);
	printf("DDR version: dc2e84f0.\n");

	return ret;

err_free_reset:
	reset_release_bulk(&priv->rst);

	return ret;
=======
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
>>>>>>> Add DDR driver framework
}

static int starfive_ddr_get_info(struct udevice *dev, struct ram_info *info)
{
<<<<<<< HEAD
	struct starfive_ddr_priv *priv = dev_get_priv(dev);
=======
	struct starfive_ddr_info *priv = dev_get_priv(dev);
>>>>>>> Add DDR driver framework

	*info = priv->info;

	return 0;
}

static struct ram_ops starfive_ddr_ops = {
	.get_info = starfive_ddr_get_info,
};

static const struct udevice_id starfive_ddr_ids[] = {
<<<<<<< HEAD
	{ .compatible = "starfive,jh7110-dmc" },
=======
	{ .compatible = "starfive,dubhe-ddr" },
>>>>>>> Add DDR driver framework
	{ }
};

U_BOOT_DRIVER(starfive_ddr) = {
	.name = "starfive_ddr",
	.id = UCLASS_RAM,
	.of_match = starfive_ddr_ids,
	.ops = &starfive_ddr_ops,
	.probe = starfive_ddr_probe,
<<<<<<< HEAD
	.priv_auto = sizeof(struct starfive_ddr_priv),
=======
	.priv_auto = sizeof(struct starfive_ddr_info),
#if defined(CONFIG_SPL_BUILD)
	.plat_auto = sizeof(struct starfive_ddr_plat),
#endif
>>>>>>> Add DDR driver framework
};
