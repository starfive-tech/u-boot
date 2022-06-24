// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 Starfive, Inc.
 * Author:	yanhong <yanhong.wang@starfivetech.com>
 *
 */

#include <common.h>
#include <dm.h>
#include <fdtdec.h>
#include <init.h>
#include <ram.h>
#include <syscon.h>
#include <asm/io.h>
#include <clk.h>
#include <wait_bit.h>
#include <linux/bitops.h>

#include "starfive_ddr.h"

DECLARE_GLOBAL_DATA_PTR;

struct starfive_ddr_priv {
	struct udevice	*dev;
	struct ram_info info;
	void __iomem	*ctrlreg;
	void __iomem	*phyreg;
	u32	fre;
};

static void ddr_assert_rst(ulong addr, ulong addr_status,
			u32 mask)
{
	uint32_t tmp;

	out_le32(addr, in_le32(addr) | mask);
	do {
		tmp = in_le32(addr_status);
	} while ((tmp & mask) != 0);
}

static void ddr_clear_rst(ulong addr, ulong addr_status,
			u32 mask)
{
	uint32_t tmp;

	out_le32(addr, in_le32(addr) & (~mask));
	do {
		tmp = in_le32(addr_status);
	} while ((tmp & mask) != mask);
}

static int starfive_ddr_setup(struct udevice *dev, struct starfive_ddr_priv *priv)
{
	enum ddr_size_t size;

	switch (priv->info.size) {
	case 0x80000000:
		size = DDR_SIZE_2G;
		break;
	case 0x100000000:
		size = DDR_SIZE_4G;
		break;
	case 0x200000000:
	case 0x400000000:
	default:
		pr_err("unsupport size %lx\n", priv->info.size);
		return -1;
	}
	ddr_phy_train(priv->phyreg + (2048 << 2));
	ddr_phy_util(priv->phyreg + (4096 << 2));
	ddr_phy_start(priv->phyreg, size);

	clrsetbits_le32(CLK_DDR_BUS_REG, CLK_DDR_BUS_MASK, 0<<24);

	ddrcsr_boot(priv->ctrlreg, priv->ctrlreg + 0x1000,
		   priv->phyreg, size);

	return 0;
}

static int starfive_ddr_probe(struct udevice *dev)
{
	struct starfive_ddr_priv *priv = dev_get_priv(dev);
	fdt_addr_t addr;
	int ret;

	priv->dev = dev;
	addr = dev_read_addr_index(dev, 0);
	priv->ctrlreg = (void __iomem *)addr;
	addr = dev_read_addr_index(dev, 1);
	priv->phyreg = (void __iomem *)addr;
	ret = dev_read_u32(dev, "clock-frequency", &priv->fre);
	if (ret) {
		pr_err("clock-frequency not found in dt %d\n", ret);
		return ret;
	}
	/* Read memory base and size from DT */
	fdtdec_setup_mem_size_base();
	priv->info.base = gd->ram_base;
	priv->info.size = gd->ram_size;

	switch (priv->fre) {
	case 2133:
		clrsetbits_le32(CLK_DDR_BUS_REG, CLK_DDR_BUS_MASK, 0<<24);
		clrsetbits_le32(SYS_SYSCON_40_REG, PLL1_PD_MASK, 1<<27);
		clrsetbits_le32(SYS_SYSCON_36_REG, PLL1_DACPD_MASK, 0<<15);
		clrsetbits_le32(SYS_SYSCON_36_REG, PLL1_DSMPD_MASK, 0<<16);
		clrsetbits_le32(SYS_SYSCON_40_REG, PLL1_FRAC_MASK, 0xe00000<<0);
		clrsetbits_le32(SYS_SYSCON_36_REG, PLL1_FBDIV_MASK, 0x58<<17);
		clrsetbits_le32(SYS_SYSCON_44_REG, PLL1_PREDIV_MASK, 0x1<<0);
		clrsetbits_le32(SYS_SYSCON_40_REG, PLL1_POSTDIV1_MASK, 0x1<<28);
		clrsetbits_le32(SYS_SYSCON_40_REG, PLL1_PD_MASK, 0<<27);
		udelay(100);
		clrsetbits_le32(CLK_DDR_BUS_REG, CLK_DDR_BUS_MASK, (1<<24)&CLK_DDR_BUS_MASK);

		ddr_assert_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_OSC_MASK);
		ddr_clear_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_OSC_MASK);
		ddr_assert_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_APB_MASK);
		ddr_clear_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_APB_MASK);
		clrsetbits_le32(CLK_AXI_CTRL_REG, CLK_AXI_EN_MASK, (0<<31)&CLK_AXI_EN_MASK);

		ddr_assert_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_AXI_MASK);
		ddr_clear_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_AXI_MASK);

		clrsetbits_le32(CLK_AXI_CTRL_REG, CLK_AXI_EN_MASK, (1<<31)&CLK_AXI_EN_MASK);
		break;

	case 2800:
		clrsetbits_le32(CLK_DDR_BUS_REG, CLK_DDR_BUS_MASK, 0<<24);
		clrsetbits_le32(SYS_SYSCON_40_REG, PLL1_PD_MASK, 1<<27);
		clrsetbits_le32(SYS_SYSCON_36_REG, PLL1_DACPD_MASK, 0<<15);
		clrsetbits_le32(SYS_SYSCON_36_REG, PLL1_DSMPD_MASK, 0<<16);
		clrsetbits_le32(SYS_SYSCON_40_REG, PLL1_FRAC_MASK, 0xAAAAAA<<0);
		clrsetbits_le32(SYS_SYSCON_36_REG, PLL1_FBDIV_MASK, 0x74<<16);
		clrsetbits_le32(SYS_SYSCON_44_REG, PLL1_PREDIV_MASK, 2<<0);
		clrsetbits_le32(SYS_SYSCON_40_REG, PLL1_POSTDIV1_MASK, 0<<28);
		clrsetbits_le32(SYS_SYSCON_40_REG, PLL1_PD_MASK, 0<<27);

		clrsetbits_le32(CLK_DDR_BUS_REG, CLK_DDR_BUS_MASK, 1<<24);

		ddr_assert_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_OSC_MASK);
		ddr_clear_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_OSC_MASK);
		ddr_assert_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_APB_MASK);
		ddr_clear_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_APB_MASK);
		ddr_assert_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_AXI_MASK);
		ddr_clear_rst(RESET_ASSERT1_REG, RESET_STATUS1_REG,
				RSTN_AXI_MASK);
		break;
	default:
		printk("Unknown DDR frequency %d\n", priv->fre);
		break;
	};

	ret = starfive_ddr_setup(dev, priv);
	printf("DDR version: 600a6366.\n");

	return ret;
}

static int starfive_ddr_get_info(struct udevice *dev, struct ram_info *info)
{
	struct starfive_ddr_priv *priv = dev_get_priv(dev);

	*info = priv->info;

	return 0;
}

static struct ram_ops starfive_ddr_ops = {
	.get_info = starfive_ddr_get_info,
};

static const struct udevice_id starfive_ddr_ids[] = {
	{ .compatible = "starfive,jh7110-ddr" },
	{ }
};

U_BOOT_DRIVER(starfive_ddr) = {
	.name = "starfive_ddr",
	.id = UCLASS_RAM,
	.of_match = starfive_ddr_ids,
	.ops = &starfive_ddr_ops,
	.probe = starfive_ddr_probe,
	.priv_auto = sizeof(struct starfive_ddr_priv),
};
