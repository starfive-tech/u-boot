// SPDX-License-Identifier: GPL-2.0+
/*
 * Synopsys DesignWare Multimedia Card Interface driver
 * extensions used in StarFive JH 7100.
 *
 * Copyright (C) 2019 Synopsys
 * Author: Eugeniy Paltsev <Eugeniy.Paltsev@synopsys.com>
 * Modified by StarFive Technology
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <dwmmc.h>
#include <errno.h>
#include <fdtdec.h>
#include <dm/device_compat.h>
#include <linux/libfdt.h>
#include <linux/err.h>
#include <malloc.h>

#define CLOCK_MIN		400000	/*  400 kHz */
#define FIFO_MIN		8
#define FIFO_MAX		4096
#define DWMMC_BUS_FREQ		100000000

struct starfive_jh_dwmci_plat {
	struct mmc_config	cfg;
	struct mmc		mmc;
};

struct starfive_jh_dwmci_priv_data {
	struct dwmci_host	host;
	u32			f_max;
};

static int starfive_jh_dwmmc_of_to_plat(struct udevice *dev)
{
	struct starfive_jh_dwmci_priv_data *priv = dev_get_priv(dev);
	struct dwmci_host *host = &priv->host;
	u32 fifo_depth;
	int ret;

	host->ioaddr = dev_read_addr_ptr(dev);

	/*
	 * If fifo-depth is unset don't set fifoth_val - we will try to
	 * auto detect it.
	 */
	ret = dev_read_u32(dev, "fifo-depth", &fifo_depth);
	if (!ret) {
		if (fifo_depth < FIFO_MIN || fifo_depth > FIFO_MAX)
			return -EINVAL;
	}
	host->fifoth_val = MSIZE(0x2) |
			   RX_WMARK(fifo_depth / 2 - 1) |
			   TX_WMARK(fifo_depth / 2);


	host->buswidth = dev_read_u32_default(dev, "bus-width", 4);
	if (host->buswidth != 1 && host->buswidth != 4 && host->buswidth != 8)
		return -EINVAL;

	/*
	 * If max-frequency is unset don't set priv->f_max - we will use
	 * host->bus_hz in probe() instead.
	 */
	ret = dev_read_u32(dev, "max-frequency", &priv->f_max);
	if (!ret && priv->f_max < CLOCK_MIN)
		return -EINVAL;

//	host->fifo_mode = dev_read_bool(dev, "fifo-mode");
	host->name = dev->name;
	host->dev_index = 0;
	host->priv = priv;

	return 0;
}

int starfive_jh_dwmmc_getcd(struct udevice *dev)
{
	struct starfive_jh_dwmci_priv_data *priv = dev_get_priv(dev);
	struct dwmci_host *host = &priv->host;

	u32 ret = dwmci_readl(host, DWMCI_CDETECT);
#if CONFIG_IS_ENABLED(TARGET_STARFIVE_JH7100)
	printf("MMC CD is 0x%x, force to True.\n", ret);
	return 1;
#else
	return !(ret & 1);
#endif
}

struct dm_mmc_ops starfive_jh_dwmci_dm_ops;

static int starfive_jh_dwmmc_probe(struct udevice *dev)
{
#ifdef CONFIG_BLK
	struct starfive_jh_dwmci_plat *plat = dev_get_plat(dev);
#else
	int ret;
#endif
	struct mmc_uclass_priv *upriv = dev_get_uclass_priv(dev);
	struct starfive_jh_dwmci_priv_data *priv = dev_get_priv(dev);
	struct dwmci_host *host = &priv->host;
	unsigned int clock_max;

	/* Extend generic 'dm_dwmci_ops' with our 'getcd' implementation */
	memcpy(&starfive_jh_dwmci_dm_ops, &dm_dwmci_ops, sizeof(struct dm_mmc_ops));
	starfive_jh_dwmci_dm_ops.get_cd = starfive_jh_dwmmc_getcd;

	host->bus_hz = DWMMC_BUS_FREQ;

	if (!priv->f_max)
		clock_max = host->bus_hz;
	else
		clock_max = min_t(unsigned int, host->bus_hz, priv->f_max);

#ifdef CONFIG_BLK
	dwmci_setup_cfg(&plat->cfg, host, clock_max, CLOCK_MIN);
	host->mmc = &plat->mmc;
#else
	ret = add_dwmci(host, clock_max, CLOCK_MIN);
	if (ret)
		return ret;
#endif
	host->mmc->priv = &priv->host;
	upriv->mmc = host->mmc;
	host->mmc->dev = dev;

	return dwmci_probe(dev);
}

static int starfive_jh_dwmmc_bind(struct udevice *dev)
{
#ifdef CONFIG_BLK
	struct starfive_jh_dwmci_plat *plat = dev_get_plat(dev);
	int ret;

	ret = dwmci_bind(dev, &plat->mmc, &plat->cfg);
	if (ret)
		return ret;
#endif

	return 0;
}

static const struct udevice_id starfive_jh_dwmmc_ids[] = {
	{ .compatible = "snps,dw-mshc" },
	{ }
};

U_BOOT_DRIVER(starfive_jh_dwmmc_drv) = {
	.name				= "JH DWMMC0",
	.id				= UCLASS_MMC,
	.of_match			= starfive_jh_dwmmc_ids,
	.of_to_plat			= starfive_jh_dwmmc_of_to_plat,
	.ops				= &starfive_jh_dwmci_dm_ops,
	.bind				= starfive_jh_dwmmc_bind,
	.probe				= starfive_jh_dwmmc_probe,
	.priv_auto			= sizeof(struct starfive_jh_dwmci_priv_data),
	.plat_auto			= sizeof(struct starfive_jh_dwmci_plat),
};
