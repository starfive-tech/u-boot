// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 StarFive Technology Co., Ltd.
 *
 */

 #include "clk.h"
 #include "clk-starfive-common.h"
 #include <dt-bindings/clock/starfive,jhb100-crg.h>
 #include <linux/clk-provider.h>

static struct clk_info usbcrg_clk_info[] = {
	{ JHB100_USBCLK_APB_PCLK, "apb_pclk",
		"usb_200",		NULL,	CLK_DIVIDER,	2 },
	{ JHB100_USBCLK_PHY_24M_REFCLK, "phy_24m_refclk",
		"usb_600",		NULL,	CLK_DIVIDER,	5 },
	{ JHB100_USBCLK_USB_REF_CLK, "usb_ref_clk",
		"usb_200",		NULL,	CLK_DIVIDER,	4 },
	{ JHB100_USBCLK_USB_DRD_USB3_BUS_CLK_EARLY,	"usb_drd_usb3_bus_clk_early",
		"usb_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_USBCLK_USB_DRD_USB3_REF_CLK,	"usb_drd_usb3_ref_clk",
		"usb_ref_clk",	NULL,	CLK_GATE,	0 },
	{ JHB100_USBCLK_USB_HOST_USB3_BUS_CLK_EARLY,	"usb_host_usb3_bus_clk_early",
		"usb_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_USBCLK_USB_HOST_USB3_REF_CLK,	"usb_host_usb3_ref_clk",
		"usb_ref_clk",	NULL,	CLK_GATE,	0 },
	{ JHB100_USBCLK_MAIN_ICG_EN_BMCUSB_DRD,	"main_icg_en_bmcusb_drd",
		"usb_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_USBCLK_MAIN_ICG_EN_BMCUSB_HOST,	"main_icg_en_bmcusb_host",
		"usb_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_USBCLK_MAIN_ICG_EN_BMCUSB_SENSORS,	"main_icg_en_bmcusb_sensors",
		"apb_pclk",	NULL,	CLK_GATE,	0 },
};

static int jhb100_usbcrg_probe(struct udevice *dev)
{
	int ret;
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	/* Make sure sys0crg drivers are instantiated first. */
	ret = jhb100_clk_check_parent(DM_DRIVER_GET(sys0crg));
	if (ret)
		return ret;

	starfive_clk_init(reg, usb, usbcrg_clk_info, ARRAY_SIZE(usbcrg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(usb);

JHB100_CLK_OPS(usb);

static const struct udevice_id jhb100_usbcrg_match[] = {
	{ .compatible = "starfive,jhb100-usbcrg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(usbcrg) = {
	.name = "clk-starfive-jhb100-usb",
	.id = UCLASS_CLK,
	.of_match = jhb100_usbcrg_match,
	.probe = jhb100_usbcrg_probe,
	.ops = &jhb100_usb_clk_ops,
	.bind = jhb100_clk_bind,
	.flags = DM_FLAG_PRE_RELOC,
};
