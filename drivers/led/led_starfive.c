// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 StarFive Technology Co., Ltd.
 * Author:	ZhiWei Lim <zhiwei.lim@starfivetech.com>
 *
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <led.h>
#include <log.h>
#include <asm/io.h>
#include <dm/lists.h>
#include <linux/bitops.h>
#include <clk.h>
#include <dm/device_compat.h>

#define STARFIVE_LED_ENABLE_OFFSET		0x0
#define STARFIVE_LED_NORMAL_PERIOD_OFFSET	0x4
#define STARFIVE_LED_ABNORMAL_PERIOD_OFFSET	0x8

#define STARFIVE_LED_PULSE_DURATION		0x60000
#define STARFIVE_LED_NORMAL_PERIOD		0x7FFFF
#define STARFIVE_LED_ABNORMAL_PERIOD		0

static int starfive_led_probe(struct udevice *dev)
{
	struct clk clk;
	void __iomem *base;
	int ret;

	base = dev_read_addr_ptr(dev);
	if (!base)
		return -EINVAL;

	ret = clk_get_by_index(dev, 0, &clk);
	if (ret)
		return ret;

	ret = clk_enable(&clk);
	if (ret)
		return ret;

	writel(STARFIVE_LED_NORMAL_PERIOD, base + STARFIVE_LED_NORMAL_PERIOD_OFFSET);
	writel(STARFIVE_LED_ABNORMAL_PERIOD, base + STARFIVE_LED_ABNORMAL_PERIOD_OFFSET);

	/* Set pulse duration and generate heartbeat at bit0 */
	writel(STARFIVE_LED_PULSE_DURATION << 1 | 0x1, base + STARFIVE_LED_ENABLE_OFFSET);

	return 0;
}

static int starfive_led_bind(struct udevice *parent)
{
	ofnode node;

	dev_for_each_subnode(node, parent) {
		struct udevice *dev;
		int ret;

		ret = device_bind_driver_to_node(parent, "jhb100-leds",
						 ofnode_get_name(node),
						 node, &dev);
		if (ret)
			return ret;
	}

	return 0;
}

static const struct udevice_id starfive_led_dt_ids[] = {
	{ .compatible = "starfive,jhb100-leds" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(starfive_led) = {
	.name = "jhb100-leds",
	.id = UCLASS_LED,
	.of_match = starfive_led_dt_ids,
	.probe = starfive_led_probe,
	.bind = starfive_led_bind,
};
