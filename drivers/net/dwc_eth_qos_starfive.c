// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2023 StarFive Technology Co., Ltd.
 * Author: Yanhong Wang<yanhong.wang@starfivetech.com>
 */

#include <common.h>
#include <asm/cache.h>
#include <asm/gpio.h>
#include <clk.h>
#include <dm.h>
#include <eth_phy.h>
#include <net.h>
#include <regmap.h>
#include <reset.h>
#include <syscon.h>
#include <linux/iopoll.h>
#include <asm/io.h>
#include "dwc_eth_qos.h"
#include <generic-phy.h>
#include <wait_bit.h>
#include <starfive/jhb100/clk.h>

#define EQOS_MAC_PORT_SELECT_100MBPS BIT(15)
#define EQOS_MAC_CFG_SPEED_100MBPS	 BIT(16)

#define STARFIVE_DWMAC_PHY_INFT_RGMII	0x1
#define STARFIVE_DWMAC_PHY_INFT_SGMII	0x2
#define STARFIVE_DWMAC_PHY_INFT_RMII	0x4
#define STARFIVE_DWMAC_PHY_INFT_FIELD	0x7U

#define STARFIVE_JHB100_GMAC0_RMII_BASE 0x11C00000

struct starfive_platform_data {
	struct regmap *regmap;
	struct reset_ctl_bulk resets;
	struct clk_bulk clks;
	phy_interface_t interface;
	u32 offset;
	u32 shift;
	bool tx_use_rgmii_clk;
	struct phy phy;
};

static int eqos_interface_init_jh7110(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;
	struct ofnode_phandle_args args;
	unsigned int mode;
	int ret;

	switch (data->interface) {
	case PHY_INTERFACE_MODE_RMII:
		mode = STARFIVE_DWMAC_PHY_INFT_RMII;
		break;

	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_ID:
		mode = STARFIVE_DWMAC_PHY_INFT_RGMII;
		break;

	default:
		return -EINVAL;
	}

	ret = dev_read_phandle_with_args(dev, "starfive,syscon", NULL,
					 2, 0, &args);
	if (ret)
		return ret;

	if (args.args_count != 2)
		return -EINVAL;

	data->offset = args.args[0];
	data->shift = args.args[1];
	data->regmap = syscon_regmap_lookup_by_phandle(dev, "starfive,syscon");
	if (IS_ERR(data->regmap)) {
		ret = PTR_ERR(data->regmap);
		pr_err("Failed to get regmap: %d\n", ret);
		return ret;
	}

	return regmap_update_bits(data->regmap, data->offset,
				  STARFIVE_DWMAC_PHY_INFT_FIELD << data->shift,
				  mode << data->shift);
}

static int eqos_set_tx_clk_speed_jh7110(struct udevice *dev)
{
	struct eqos_priv *eqos = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;
	struct clk *pclk, *c;
	ulong rate;
	int ret;

	/* Generally, the rgmii_tx clock is provided by the internal clock,
	 * which needs to match the corresponding clock frequency according
	 * to different speeds. If the rgmii_tx clock is provided by the
	 * external rgmii_rxin, there is no need to configure the clock
	 * internally, because rgmii_rxin will be adaptively adjusted.
	 */
	if (data->tx_use_rgmii_clk)
		return 0;

	switch (eqos->phy->speed) {
	case SPEED_1000:
		rate = 125 * 1000 * 1000;
		break;
	case SPEED_100:
		rate = 25 * 1000 * 1000;
		break;
	case SPEED_10:
		rate = 2.5 * 1000 * 1000;
		break;
	default:
		pr_err("invalid speed %d", eqos->phy->speed);
		return -EINVAL;
	}

	/* eqos->clk_tx clock has no set rate operation, so just set the parent
	 * clock rate directly
	 */
	ret = clk_get_by_id(eqos->clk_tx.id, &c);
	if (ret)
		return ret;

	pclk = clk_get_parent(c);
	if (pclk) {
		ret = clk_set_rate(pclk, rate);
		if (ret < 0) {
			pr_err("jh7110 (clk_tx, %lu) failed: %d", rate, ret);
			return ret;
		}
	}

	return 0;
}

static ulong eqos_get_tick_clk_rate_jh7110(struct udevice *dev)
{
	struct eqos_priv *eqos = dev_get_priv(dev);

	return clk_get_rate(&eqos->clk_tx);
}

static int eqos_start_clks_jh7110(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	return clk_enable_bulk(&data->clks);
}

static int eqos_stop_clks_jh7110(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	return clk_disable_bulk(&data->clks);
}

static int eqos_start_resets_jh7110(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	return reset_deassert_bulk(&data->resets);
}

static int eqos_stop_resets_jh7110(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	return reset_assert_bulk(&data->resets);
}

static int eqos_remove_resources_jh7110(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	reset_assert_bulk(&data->resets);
	clk_disable_bulk(&data->clks);

	return 0;
}

static int eqos_probe_resources_jh7110(struct udevice *dev)
{
	struct eqos_priv *eqos = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data;
	int ret;

	data = calloc(1, sizeof(struct starfive_platform_data));
	if (!data)
		return -ENOMEM;

	pdata->priv_pdata = data;
	data->interface = eqos->config->interface(dev);
	if (data->interface == PHY_INTERFACE_MODE_NA) {
		pr_err("Invalid PHY interface\n");
		return -EINVAL;
	}

	ret = reset_get_bulk(dev, &data->resets);
	if (ret < 0)
		return ret;

	ret = clk_get_bulk(dev, &data->clks);
	if (ret < 0)
		return ret;

	ret = clk_get_by_name(dev, "gtx", &eqos->clk_tx);
	if (ret)
		return ret;

	data->tx_use_rgmii_clk = dev_read_bool(dev, "starfive,tx-use-rgmii-clk");

	return eqos_interface_init_jh7110(dev);
}

static int eqos_interface_init_jhb100(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;
	unsigned int mode;
	struct ofnode_phandle_args phy_phandle;
	int ret;

	switch (data->interface) {
	case PHY_INTERFACE_MODE_RMII:
		mode = STARFIVE_DWMAC_PHY_INFT_RMII;
		break;

	case PHY_INTERFACE_MODE_RGMII:
	case PHY_INTERFACE_MODE_RGMII_ID:
		mode = STARFIVE_DWMAC_PHY_INFT_RGMII;
		break;

	case PHY_INTERFACE_MODE_SGMII:
		return 0;

	default:
		printf("Undefined phy interface\n");
		return -EINVAL;
	}

	ret = dev_read_phandle_with_args(dev, "starfive,syscon", NULL,
					2, 0, &phy_phandle);
	if (ret)
		return ret;

	if (phy_phandle.args_count != 2)
		return -EINVAL;

	data->offset = phy_phandle.args[0];
	data->shift = phy_phandle.args[1];
	data->regmap = syscon_regmap_lookup_by_phandle(dev, "starfive,syscon");
	if (IS_ERR(data->regmap)) {
		ret = PTR_ERR(data->regmap);
		printf("Failed to get regmap: %d\n", ret);
		return ret;
	}

	return regmap_update_bits(data->regmap, data->offset,
					STARFIVE_DWMAC_PHY_INFT_FIELD << data->shift,
					mode << data->shift);
}

static int eqos_set_tx_clk_speed_jhb100(struct udevice *dev)
{
	struct eqos_priv *eqos = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;
	ulong rate;
	int ret;

	switch (eqos->phy->speed) {
	case SPEED_1000:
		rate = 125 * 1000 * 1000;
		break;
	case SPEED_100:
		rate = 25 * 1000 * 1000;
		break;
	case SPEED_10:
		rate = 2.5 * 1000 * 1000;
		break;
	default:
		printf("invalid speed %d", eqos->phy->speed);
		return -EINVAL;
	}

	ret = clk_set_rate(&eqos->clk_tx, rate);
	if (ret < 0) {
		printf("clk_set_rate(clk_tx, %lu) failed: %d", rate, ret);
		return ret;
	}

	if (data->interface == PHY_INTERFACE_MODE_RMII) {
		u32 val = readl(&eqos->mac_regs->configuration);
		val |= EQOS_MAC_PORT_SELECT_100MBPS;
		val |= EQOS_MAC_CFG_SPEED_100MBPS;
		writel(val, &eqos->mac_regs->configuration);
	} else if (data->interface == PHY_INTERFACE_MODE_SGMII) {
		ret = clk_set_rate(&eqos->clk_rx, rate);
		if (ret < 0) {
			printf("clk_set_rate(clk_rx, %lu) failed: %d", rate, ret);
			return ret;
		}
	}

	return 0;
}

static ulong eqos_get_tick_clk_rate_jhb100(struct udevice *dev)
{
	struct eqos_priv *eqos = dev_get_priv(dev);

	return clk_get_rate(&eqos->clk_tx);
}

static int eqos_start_clks_jhb100(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;
	struct clk *parent_clk, *clk;
	int ret;

	ret = clk_enable_bulk(&data->clks);
	if (ret) {
		printf("Failed to enable clk bulk\n");
		return ret;
	}

	if (dev_read_addr(dev) == STARFIVE_JHB100_GMAC0_RMII_BASE) {
		/*
		 * This handling addresses the issue where the parent clock cannot
		 * be set via the device tree during initialization
		 */
		ret = clk_get_by_id(JHB100_PER3_ID_TRANS(JHB100_PER3CLK_GMAC0_RMII_MUX), &clk);
		if (ret)
			return ret;

		ret = clk_get_by_id(JHB100_PER3_ID_TRANS(JHB100_PER3CLK_GMAC0_RMII_RCLKI), &parent_clk);
		if (ret)
			return ret;

		ret = clk_set_parent(clk, parent_clk);
		if (ret) {
			printf("Failed to set clock parent\n");
			return ret;
		}
	}

	return 0;
}

static int eqos_stop_clks_jhb100(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	return clk_disable_bulk(&data->clks);
}

static int eqos_start_resets_jhb100(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	if (data->interface == PHY_INTERFACE_MODE_SGMII) {
		if (reset_deassert_bulk(&data->resets) == 0)
			return generic_phy_configure(&data->phy, NULL);
		return -EPERM;
	}

	return reset_deassert_bulk(&data->resets);
}

static int eqos_stop_resets_jhb100(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	return reset_assert_bulk(&data->resets);
}

static int eqos_remove_resources_jhb100(struct udevice *dev)
{
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;

	reset_assert_bulk(&data->resets);
	clk_disable_bulk(&data->clks);

	if (data->interface == PHY_INTERFACE_MODE_SGMII)
		generic_phy_power_off(&data->phy);

	return 0;
}

static int eqos_probe_resources_jhb100(struct udevice *dev)
{
	struct eqos_priv *eqos = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data;
	int ret;

	data = calloc(1, sizeof(struct starfive_platform_data));
	if (!data)
		return -ENOMEM;

	pdata->priv_pdata = data;
	pdata->phy_interface = eqos->config->interface(dev);
	data->interface = (dev_read_bool(dev, "snps,use-ncsi")) ?
		PHY_INTERFACE_MODE_RMII : pdata->phy_interface;

	if (data->interface == PHY_INTERFACE_MODE_NA) {
		pr_err("Invalid PHY interface\n");
		return -EINVAL;
	}

	ret = reset_get_bulk(dev, &data->resets);
	if (ret < 0)
		return ret;

	ret = clk_get_bulk(dev, &data->clks);
	if (ret < 0)
		return ret;

	ret = clk_get_by_name(dev, "tx", &eqos->clk_tx);
	if (ret)
		return ret;

	if (data->interface == PHY_INTERFACE_MODE_SGMII) {
		ret = clk_get_by_name(dev, "rx", &eqos->clk_rx);
		if (ret)
			return ret;

		ret = generic_phy_get_by_index(dev, 0, &data->phy);
		if (!ret) {
			ret = generic_phy_init(&data->phy);
			if (ret)
				return ret;
		} else if (ret != -ENOENT) {
			debug("could not get phy (err %d)\n", ret);
			return ret;
		}
	}

	return eqos_interface_init_jhb100(dev);
}

static int eqos_calibrate_pads_jhb100(struct udevice *dev)
{
	struct eqos_priv *eqos = dev_get_priv(dev);
	struct eth_pdata *pdata = dev_get_plat(dev);
	struct starfive_platform_data *data = pdata->priv_pdata;
	int ret;

	if (data->interface == PHY_INTERFACE_MODE_SGMII) {
		/* Initiate internal phy auto negotiation */
		setbits_le32(&eqos->mac_regs->mac_an_counter, BIT(12));
		wait_for_bit_le32(&eqos->mac_regs->mac_an_status,
						BIT(5), false, 500, ret);
		if (ret) {
			printf("sgmii internal phy auto negotiation failed\n");
			return ret;
		}
	}

	return 0;
}

static void eqos_inval_flush_desc_jhb100(void *desc)
{
	/* Designware EQOS IO coherent, in cacheable region
		dont need to invalide/flush descriptor */
}

static void eqos_inval_flush_buf_jhb100(void *buf, size_t size)
{
	/* Designware EQOS IO coherent, in cacheable region
		dont need to invalide/flush buffer */
}

static struct eqos_ops eqos_jh7110_ops = {
	.eqos_inval_desc = eqos_inval_desc_generic,
	.eqos_flush_desc = eqos_flush_desc_generic,
	.eqos_inval_buffer = eqos_inval_buffer_generic,
	.eqos_flush_buffer = eqos_flush_buffer_generic,
	.eqos_probe_resources = eqos_probe_resources_jh7110,
	.eqos_remove_resources = eqos_remove_resources_jh7110,
	.eqos_stop_resets = eqos_stop_resets_jh7110,
	.eqos_start_resets = eqos_start_resets_jh7110,
	.eqos_stop_clks = eqos_stop_clks_jh7110,
	.eqos_start_clks = eqos_start_clks_jh7110,
	.eqos_calibrate_pads = eqos_null_ops,
	.eqos_disable_calibration = eqos_null_ops,
	.eqos_set_tx_clk_speed = eqos_set_tx_clk_speed_jh7110,
	.eqos_get_enetaddr = eqos_null_ops,
	.eqos_get_tick_clk_rate = eqos_get_tick_clk_rate_jh7110
};

static struct eqos_ops eqos_jhb100_ops = {
	.eqos_inval_desc = eqos_inval_flush_desc_jhb100,
	.eqos_flush_desc = eqos_inval_flush_desc_jhb100,
	.eqos_inval_buffer = eqos_inval_flush_buf_jhb100,
	.eqos_flush_buffer = eqos_inval_flush_buf_jhb100,
	.eqos_probe_resources = eqos_probe_resources_jhb100,
	.eqos_remove_resources = eqos_remove_resources_jhb100,
	.eqos_stop_resets = eqos_stop_resets_jhb100,
	.eqos_start_resets = eqos_start_resets_jhb100,
	.eqos_stop_clks = eqos_stop_clks_jhb100,
	.eqos_start_clks = eqos_start_clks_jhb100,
	.eqos_calibrate_pads = eqos_calibrate_pads_jhb100,
	.eqos_disable_calibration = eqos_null_ops,
	.eqos_set_tx_clk_speed = eqos_set_tx_clk_speed_jhb100,
	.eqos_get_enetaddr = eqos_null_ops,
	.eqos_get_tick_clk_rate = eqos_get_tick_clk_rate_jhb100
};

/* mdio_wait: There is no need to wait after setting the MAC_MDIO_Address register
 * swr_wait: Software reset bit must be read at least 4 CSR clock cycles
 *          after it is written to 1.
 * config_mac: Enable rx queue to DCB mode.
 * config_mac_mdio: CSR clock range is 250-300 Mhz.
 * axi_bus_width: The width of the data bus is 64 bit.
 */
struct eqos_config __maybe_unused eqos_jh7110_config = {
	.reg_access_always_ok = false,
	.mdio_wait = 0,
	.swr_wait = 4,
	.config_mac = EQOS_MAC_RXQ_CTRL0_RXQ0EN_ENABLED_DCB,
	.config_mac_mdio = EQOS_MAC_MDIO_ADDRESS_CR_250_300,
	.axi_bus_width = EQOS_AXI_WIDTH_64,
	.interface = dev_read_phy_mode,
	.ops = &eqos_jh7110_ops
};

/* mdio_wait: There is no need to wait after setting the MAC_MDIO_Address register
 * swr_wait: Software reset bit must be read at least 4 CSR clock cycles
 *          after it is written to 1.
 * config_mac: Enable rx queue to DCB mode.
 * config_mac_mdio: CSR clock range is 250-300 Mhz.
 * axi_bus_width: The width of the data bus is 64 bit.
 */
struct eqos_config __maybe_unused eqos_jhb100_config = {
	.reg_access_always_ok = false,
	.mdio_wait = 0,
	.swr_wait = 4,
	.config_mac = EQOS_MAC_RXQ_CTRL0_RXQ0EN_ENABLED_DCB,
	.config_mac_mdio = EQOS_MAC_MDIO_ADDRESS_CR_250_300,
	.axi_bus_width = EQOS_AXI_WIDTH_128,
	.interface = dev_read_phy_mode,
	.ops = &eqos_jhb100_ops
};
