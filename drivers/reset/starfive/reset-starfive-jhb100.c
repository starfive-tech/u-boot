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
	.nr_resets = NUM_RESETS(JHB100_SYSRST_BMCPCIERP_RSTN_CRG),
	.assert_offset = 0x1b0,
	.status_offset = 0x1b4,
};

static const struct starfive_reset_info jhb100_sys1_info = {
	.nr_resets = NUM_RESETS(JHB100_SYS1RST_MAIN_RSTN_PCU_HOSTSS1),
	.assert_offset = 0x74,
	.status_offset = 0x78,
};

static const struct starfive_reset_info jhb100_sys2_info = {
	.nr_resets = NUM_RESETS(JHB100_SYS2RST_MAIN_RSTN_PCU_GPU1),
	.assert_offset = 0xc8,
	.status_offset = 0xcc,
};

static const struct starfive_reset_info jhb100_per0_info = {
	.nr_resets = NUM_RESETS(JHB100_PER0RST_GPIO_IOMUX_PRESETN),
	.assert_offset = 0x550,
	.status_offset = 0x55c,
};

static const struct starfive_reset_info jhb100_per1_info = {
	.nr_resets = NUM_RESETS(JHB100_PER1RST_MAIN_RSTN_PERIPH1_RAS),
	.assert_offset = 0x134,
	.status_offset = 0x138,
};

static const struct starfive_reset_info jhb100_per2_info = {
	.nr_resets = NUM_RESETS(JHB100_PER2RST_MAIN_RSTN_SENSORS10),
	.assert_offset = 0x11c,
	.status_offset = 0x120,
};

static const struct starfive_reset_info jhb100_per3_info = {
	.nr_resets = NUM_RESETS(JHB100_PER3RST_IOMUX_PRESETN),
	.assert_offset = 0x94,
	.status_offset = 0x98,
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
