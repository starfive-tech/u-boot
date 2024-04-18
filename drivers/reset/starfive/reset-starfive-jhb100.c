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
#include "reset-starfive.h"

#define BITS_PER_REG 32
#define NUM_RESETS(x)		((x) + 1)

static const struct starfive_reset_info jhb100_sys_info = {
	.nr_resets = NUM_RESETS(JHB100_SYSRST_BMCPCIERP_PCIE_RP_PERST_N),
	.assert_offset = 0xcc,
	.status_offset = 0xd0,
};

static const struct starfive_reset_info jhb100_sys1_info = {
	.nr_resets = NUM_RESETS(JHB100_SYS1RST_PCU9_APB),
	.assert_offset = 0x90,
	.status_offset = 0x94,
};

static const struct starfive_reset_info jhb100_sys2_info = {
	.nr_resets = NUM_RESETS(JHB100_SYS2RST_PCU10_APB),
	.assert_offset = 0xbc,
	.status_offset = 0xc0,
};

static const struct starfive_reset_info jhb100_per0_info = {
	.nr_resets = NUM_RESETS(JHB100_PER0RST_MAIN_RSTN_SOL14),
	.assert_offset = 0x344,
	.status_offset = 0x350,
};

static const struct starfive_reset_info jhb100_per1_info = {
	.nr_resets = NUM_RESETS(JHB100_PER1RST_DMAC4_1CH_ARESETN_M1),
	.assert_offset = 0x100,
	.status_offset = 0x10c,
};

static const struct starfive_reset_info jhb100_per2_info = {
	.nr_resets = NUM_RESETS(JHB100_PER2RST_ADC_PRESETN),
	.assert_offset = 0xe4,
	.status_offset = 0xec,
};

static const struct starfive_reset_info jhb100_per3_info = {
	.nr_resets = NUM_RESETS(JHB100_PER3RST_MAIN_RSTN_IOMUX),
	.assert_offset = 0x98,
	.status_offset = 0x9c,
};

static const struct starfive_reset_info jhb100_vout_info = {
	.nr_resets = NUM_RESETS(JHB100_VOUTRST_MAIN_RSTN_U3_VOUT_DYNSW),
	.assert_offset = 0x44,
	.status_offset = 0x48,
};

static const struct starfive_reset_info jhb100_vce_info = {
	.nr_resets = NUM_RESETS(JHB100_VCERST_NCNOC_VCE1_VREC_INIT),
	.assert_offset = 0x28,
	.status_offset = 0x2c,
};

static const struct starfive_reset_info jhb100_gpu_info = {
	.nr_resets = NUM_RESETS(JHB100_GPU0RST_MAIN_RSTN_GC620L),
	.assert_offset = 0x14,
	.status_offset = 0x18,
};

static const struct starfive_reset_info jhb100_usb_info = {
	.nr_resets = NUM_RESETS(JHB100_USBRST_SENSORS3_PD_INF),
	.assert_offset = 0x20,
	.status_offset = 0x24,
};

static const struct starfive_reset_info jhb100_host_info = {
	.nr_resets = NUM_RESETS(JHB100_HOST0RST_APB_UART1_RST_N),
	.assert_offset = 0x8c,
	.status_offset = 0x94,
};

static const struct starfive_reset_info jhb100_pcierp_info = {
	.nr_resets = NUM_RESETS(JHB100_PCIERPRST_PCIE_RP_SW_DBI_RESETN),
	.assert_offset = 0x40,
	.status_offset = 0x44,
};

static const struct starfive_reset_info jhb100_hostusb_info = {
	.nr_resets = NUM_RESETS(JHB100_HUSB0RST_XHCI_WRAP_VAUX),
	.assert_offset = 0x60,
	.status_offset = 0x64,
};

static const struct starfive_reset_info jhb100_hostusbcmn_info = {
	.nr_resets = NUM_RESETS(JHB100_HUSBCMNRST_SENSORS9_PD_INF),
	.assert_offset = 0x8,
	.status_offset = 0xc,
};

static const struct starfive_reset_info jhb100_hostusbdev_info = {
	.nr_resets = NUM_RESETS(JHB100_HUSBD0RST_SENSORS7_PD_INF),
	.assert_offset = 0x84,
	.status_offset = 0x88,
};

static const struct udevice_id jhb100_reset_ids[] = {
	{
		.compatible = "starfive,jhb100-syscrg",
		.data = (ulong)&jhb100_sys_info,
	},
	{
		.compatible = "starfive,jhb100-sys1crg",
		.data = (ulong)&jhb100_sys1_info,
	},
	{
		.compatible = "starfive,jhb100-sys2crg",
		.data = (ulong)&jhb100_sys2_info,
	},
	{
		.compatible = "starfive,jhb100-per0crg",
		.data = (ulong)&jhb100_per0_info,
	},
	{
		.compatible = "starfive,jhb100-per1crg",
		.data = (ulong)&jhb100_per1_info,
	},
	{
		.compatible = "starfive,jhb100-per2crg",
		.data = (ulong)&jhb100_per2_info,
	},
	{
		.compatible = "starfive,jhb100-per3crg",
		.data = (ulong)&jhb100_per3_info,
	},
	{
		.compatible = "starfive,jhb100-voutcrg",
		.data = (ulong)&jhb100_vout_info,
	},
	{
		.compatible = "starfive,jhb100-vcecrg",
		.data = (ulong)&jhb100_vce_info,
	},
	{
		.compatible = "starfive,jhb100-gpu0crg",
		.data = (ulong)&jhb100_gpu_info,
	},
	{
		.compatible = "starfive,jhb100-gpu1crg",
		.data = (ulong)&jhb100_gpu_info,
	},
	{
		.compatible = "starfive,jhb100-usbcrg",
		.data = (ulong)&jhb100_usb_info,
	},
	{
		.compatible = "starfive,jhb100-host0crg",
		.data = (ulong)&jhb100_host_info,
	},
	{
		.compatible = "starfive,jhb100-host1crg",
		.data = (ulong)&jhb100_host_info,
	},
	{
		.compatible = "starfive,jhb100-pcierpcrg",
		.data = (ulong)&jhb100_pcierp_info,
	},
	{
		.compatible = "starfive,jhb100-husb0crg",
		.data = (ulong)&jhb100_hostusb_info,
	},
	{
		.compatible = "starfive,jhb100-husb1crg",
		.data = (ulong)&jhb100_hostusb_info,
	},
	{
		.compatible = "starfive,jhb100-husbcmncrg",
		.data = (ulong)&jhb100_hostusbcmn_info,
	},
	{
		.compatible = "starfive,jhb100-husbd0crg",
		.data = (ulong)&jhb100_hostusbdev_info,
	},
	{
		.compatible = "starfive,jhb100-husbd1crg",
		.data = (ulong)&jhb100_hostusbdev_info,
	},
	{ /* sentinel */ }
};

static struct starfive_reset_info *jhb100_reset_get_cfg(const char *compat)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(jhb100_reset_ids); i++) {
		if (!strcmp(compat, jhb100_reset_ids[i].compatible))
			return (struct starfive_reset_info *)jhb100_reset_ids[i].data;
	}

	return NULL;
}

static int jhb100_reset_probe(struct udevice *dev)
{
	struct starfive_reset_priv *priv = dev_get_priv(dev);
	struct starfive_reset_info *cfg;
	const char *compat;

	priv->reg = (void __iomem *)dev_read_addr_index(dev, 0);
	if (IS_ERR(priv->reg)) {
		dev_err(dev, "failed to get reg (error %ld)\n", PTR_ERR(priv->reg));
		return PTR_ERR(priv->reg);
	}

	compat = ofnode_get_property(dev_ofnode(dev), "compatible", NULL);
	if (!compat)
		return -EINVAL;

	cfg = jhb100_reset_get_cfg(compat);
	if (!cfg)
		return -EINVAL;

	/* jhb100 reset private data */
	priv->starfive_reset_info = cfg;

	return 0;
}

U_BOOT_DRIVER(starfive_reset) = {
	.name = "starfive_reset",
	.id = UCLASS_RESET,
	.probe = jhb100_reset_probe,
	.priv_auto = sizeof(struct starfive_reset_priv),
	.ops = &starfive_reset_ops,
};
