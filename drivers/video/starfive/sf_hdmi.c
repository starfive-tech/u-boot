// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2017 Theobroma Systems Design und Consulting GmbH
 */

#include <common.h>
#include <clk.h>
#include <display.h>
#include <dm.h>
#include <dw_hdmi.h>
#include <edid.h>
#include <regmap.h>
#include <syscon.h>
#include <asm/gpio.h>
#include <asm/io.h>
#include <power/regulator.h>
#include "sf_hdmi.h"

static int rk3399_hdmi_enable(struct udevice *dev, int panel_bpp,
			      const struct display_timing *edid)
{
	return 0;
}

int rk_hdmi_read_edid(struct udevice *dev, u8 *buf, int buf_size)
{
 	return 0;
}

static int rk3399_hdmi_of_to_plat(struct udevice *dev)
{
	return 0;
}

static int rk3399_hdmi_probe(struct udevice *dev)
{
	return 0;
}

static const struct dm_display_ops rk3399_hdmi_ops = {
	.read_edid = rk_hdmi_read_edid,
	.enable = rk3399_hdmi_enable,
};

static const struct udevice_id rk3399_hdmi_ids[] = {
	{ .compatible = "rockchip,rk3288-dw-hdmi" },
	{ }
};

U_BOOT_DRIVER(rk3399_hdmi_rockchip) = {
	.name = "rk3399_hdmi_rockchip",
	.id = UCLASS_DISPLAY,
	.of_match = rk3399_hdmi_ids,
	.ops = &rk3399_hdmi_ops,
	.of_to_plat = rk3399_hdmi_of_to_plat,
	.probe = rk3399_hdmi_probe,
	.priv_auto	= sizeof(struct rk_hdmi_priv),
};
