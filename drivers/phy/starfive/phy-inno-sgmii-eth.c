// SPDX-License-Identifier: GPL-2.0
/*
 * Starfive PHY Innosilicon SGMII Driver
 *
 * Copyright (C) 2025 StarFive Technology Co., Ltd.
 */

#include <dm.h>
#include <dm/device_compat.h>
#include <generic-phy.h>
#include <linux/iopoll.h>
#include <linux/clk-provider.h>
#include <linux/delay.h>

#define PLL_LOCK_STATUS		0x13c0
#define PLL_IS_LOCK			BIT(0)
#define PHY_POLL_TIMEOUT_US	10000

struct inno_sgmii_phy_data {
	struct clk_bulk clks;
};

static int inno_sgmii_phy_exit(struct phy *phy)
{
	struct udevice *dev = phy->dev;
	struct inno_sgmii_phy_data *data = dev_get_priv(dev);

	clk_disable_bulk(&data->clks);

	return 0;
}

static int inno_sgmii_phy_configure(struct phy *phy, void *params)
{
	u32 val;
	int ret;
	void *phy_base = dev_read_addr_ptr(phy->dev);

	if (phy_base) {
		/* Wait for SGMII Internal PHY to be READY */
		ret = readl_poll_timeout(phy_base + PLL_LOCK_STATUS, val,
								(val & PLL_IS_LOCK), PHY_POLL_TIMEOUT_US);
		if (ret) {
			printf("%s sgmii timeout\n", __func__);
			return ret;
		}
	} else {
		printf("Failed to read sgmii phy base\n");
		return -EINVAL;
	}

	return 0;
}

static const struct phy_ops inno_sgmii_phy_ops = {
	.configure = inno_sgmii_phy_configure,
	.exit = inno_sgmii_phy_exit,
};

static int inno_sgmii_phy_probe(struct udevice *dev)
{
	struct inno_sgmii_phy_data *priv = dev_get_plat(dev);
	int ret;

	ret = clk_get_bulk(dev, &priv->clks);
	if (ret < 0)
		return ret;

	ret = clk_enable_bulk(&priv->clks);
	if (ret) {
		printf("%s sgmii clk enable failed\n", __func__);
		return ret;
	}

	return 0;
}

static const struct udevice_id inno_sgmii_phy_of_match[] = {
	{
		.compatible = "starfive,dwmac-inno-sgmii-phy",
	},
	{}
};

U_BOOT_DRIVER(dwmac_sgmii_phy_driver) = {
	.name = "starfive-dwmac-sgmii-phy",
	.id = UCLASS_PHY,
	.of_match = inno_sgmii_phy_of_match,
	.probe = inno_sgmii_phy_probe,
	.ops = &inno_sgmii_phy_ops,
	.priv_auto = sizeof(struct inno_sgmii_phy_data),
};
