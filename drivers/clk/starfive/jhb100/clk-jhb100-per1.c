// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	ZhiWei Lim <zhiwei.lim@starfivetech.com>
 *
 */

 #include "clk.h"
 #include "clk-starfive-common.h"
 #include <dt-bindings/clock/starfive,jhb100-crg.h>
 #include <linux/clk-provider.h>

#ifdef CONFIG_SPL_BUILD
static struct clk_info per1crg_clk_info[] = {
#ifdef CONFIG_DESIGNWARE_SPI
	{ JHB100_PER1CLK_MAIN_ICG_EN_SFC0,	"main_icg_en_sfc0",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SFC1,	"main_icg_en_sfc1",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SFC2,	"main_icg_en_sfc2",
		"per1_200",	NULL,	CLK_GATE,	0 },
#endif
#ifdef CONFIG_MMC
	{ JHB100_PER1CLK_EMMC0_BCLK,		"emmc0_bclk",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_EMMC0_CCLK,		"emmc0_cclk",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_EMMC0,	"main_icg_en_emmc0",
		"per1_200",	NULL,	CLK_GATE,	0 },
#endif
#ifdef CONFIG_DWC_UFS_STARFIVE
	{ JHB100_PER1CLK_100,		"per1_100",
		"per1_600",	NULL,	CLK_DIVIDER,	4 },
	{ JHB100_PER1CLK_UFS_REF,	"ufs_ref",
		"pll7",		NULL,	CLK_DIVIDER,	7 },
	{ JHB100_PER1CLK_UFS_300,	"ufs_300",
		"per1_600",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_UFS_150,	"ufs_150",
		"per1_600",	NULL,	CLK_DIVIDER,	4 },
	{ JHB100_PER1CLK_UFS_400,	"ufs_400",
		"per1_800",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_UFS_75,	"ufs_75",
		"ufs_150",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_UFS_37_5,	"ufs_37_5",
		"ufs_75",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_UFS_7_5,	"ufs_7_5",
		"ufs_75",	NULL,	CLK_DIVIDER,	4 },
	{ JHB100_PER1CLK_UFS_1_875,	"ufs_1_875",
		"ufs_7_5",	NULL,	CLK_DIVIDER,	3 },
	{ JHB100_PER1CLK_UFS_7_143,	"ufs_7_143",
		"per1_143",	NULL,	CLK_DIVIDER,	5 },
	{ JHB100_PER1CLK_UFS_3_5715,	"ufs_3_5715",
		"ufs_7_143",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_UFS,	"main_icg_en_ufs",
		"per1_100",	NULL,	CLK_GATE,	0 },
#endif
};
#else
static struct clk_info per1crg_clk_info[] = {
	{ JHB100_PER1CLK_100,	"per1_100",
		"per1_600",	NULL,	CLK_DIVIDER,	4 },
	{ JHB100_PER1CLK_1,	"per1_1",
		"per1_100",	NULL,	CLK_DIVIDER,	7 },
	{ JHB100_PER1CLK_200_DIVN0,	"200_divn0",
		"per1_800",	NULL,	CLK_DIVIDER,	9 },
	{ JHB100_PER1CLK_200_DIVN1,	"200_divn1",
		"per1_800",	NULL,	CLK_DIVIDER,	9 },
	{ JHB100_PER1CLK_200_DIVN2,	"200_divn2",
		"per1_800",	NULL,	CLK_DIVIDER,	9 },
	{ JHB100_PER1CLK_200_DIVN3,	"200_divn3",
		"per1_800",	NULL,	CLK_DIVIDER,	9 },
	{ JHB100_PER1CLK_200_CCLK_DIV,	"200_cclk_div",
		"per1_200",	NULL,	CLK_DIVIDER,	11 },
	{ JHB100_PER1CLK_SGPIO0_PCLK,	"sgpio0_pclk",
		"per1_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_SGPIO0_DCLK,	"sgpio0_dclk",
		"per1_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_SGPIO1_PCLK,	"sgpio1_pclk",
		"per1_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_SGPIO1_DCLK,	"sgpio1_dclk",
		"per1_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_EMMC0_BCLK,	"emmc0_bclk",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_EMMC0_CCLK,	"emmc0_cclk",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_DMAC1_1CH_CORE,	"dmac1_1ch_core",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_DMAC1_1CH_ACLK,	"dmac1_1ch_aclk",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_DMAC2_1CH_CORE,	"dmac2_1ch_core",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_DMAC2_1CH_ACLK,	"dmac2_1ch_aclk",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_DMAC3_1CH_CORE,	"dmac3_1ch_core",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_DMAC3_1CH_ACLK,	"dmac3_1ch_aclk",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_DMAC0_2CH_CORE,	"dmac0_2ch_core",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_DMAC0_2CH_ACLK,	"dmac0_2ch_aclk",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_UFS_REF,	"ufs_ref",
		"pll7",		NULL,	CLK_DIVIDER,	7 },
	{ JHB100_PER1CLK_UFS_300,	"ufs_300",
		"per1_600",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_UFS_150,	"ufs_150",
		"per1_600",	NULL,	CLK_DIVIDER,	4 },
	{ JHB100_PER1CLK_UFS_400,	"ufs_400",
		"per1_800",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_UFS_75,	"ufs_75",
		"ufs_150",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_UFS_37_5,	"ufs_37_5",
		"ufs_75",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_UFS_7_5,	"ufs_7_5",
		"ufs_75",	NULL,	CLK_DIVIDER,	4 },
	{ JHB100_PER1CLK_UFS_1_875,	"ufs_1_875",
		"ufs_7_5",	NULL,	CLK_DIVIDER,	3 },
	{ JHB100_PER1CLK_UFS_7_143,	"ufs_7_143",
		"per1_143",	NULL,	CLK_DIVIDER,	5 },
	{ JHB100_PER1CLK_UFS_3_5715,	"ufs_3_5715",
		"ufs_7_143",	NULL,	CLK_DIVIDER,	2 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SFC0,	"main_icg_en_sfc0",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SFC1,	"main_icg_en_sfc1",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SFC2,	"main_icg_en_sfc2",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SPI0,	"main_icg_en_spi0",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_EMMC0,	"main_icg_en_emmc0",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SGPIO0,	"main_icg_en_sgpio0",
		"per1_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SGPIO1,	"main_icg_en_sgpio1",
		"per1_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_SENSORS_PERIPH1,	"main_icg_en_sensors_periph1",
		"per1_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_DMAC_SFC0,	"main_icg_en_dmac_sfc0",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_DMAC_SFC1,	"main_icg_en_dmac_sfc1",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_DMAC_SFC2,	"main_icg_en_dmac_sfc2",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_DMAC_SPI0,	"main_icg_en_dmac_spi0",
		"per1_200",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_RAS,	"main_icg_en_ras",
		"per1_100",	NULL,	CLK_GATE,	0 },
	{ JHB100_PER1CLK_MAIN_ICG_EN_UFS,	"main_icg_en_ufs",
		"per1_100",	NULL,	CLK_GATE,	0 },
};
#endif /* CONFIG_SPL_BUILD */

static int jhb100_per1crg_probe(struct udevice *dev)
{
	int ret;
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	/* Make sure sys0crg and sys2crg drivers are instantiated first. */
	ret = jhb100_clk_check_parent(DM_DRIVER_GET(sys0crg));
	if (ret)
		return ret;

	ret = jhb100_clk_check_parent(DM_DRIVER_GET(sys2crg));
	if (ret)
		return ret;

	starfive_clk_init(reg, per1, per1crg_clk_info, ARRAY_SIZE(per1crg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(per1);

JHB100_CLK_OPS(per1);

static const struct udevice_id jhb100_per1crg_match[] = {
	{ .compatible = "starfive,jhb100-per1crg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(per1crg) = {
	.name = "clk-starfive-jhb100-per1",
	.id = UCLASS_CLK,
	.of_match = jhb100_per1crg_match,
	.probe = jhb100_per1crg_probe,
	.ops = &jhb100_per1_clk_ops,
	.bind = jhb100_clk_bind,
	.flags = DM_FLAG_PRE_RELOC,
};
