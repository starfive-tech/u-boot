// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 Starfive, Inc.
 * Author:	yanhong <yanhong.wang@starfivetech.com>
 *
 */

#ifndef __STARFIVE_DDR_H__
#define __STARFIVE_DDR_H__

#include <common.h>
#include <asm/io.h>
#include <inttypes.h>

#define SYS_CRG_BASE		0x13020000
#define SYS_SYSCON_BASE		0x13030000

#define CLK_DDR_BUS_REG		(SYS_CRG_BASE + 0xAC)
#define CLK_AXI_CTRL_REG	(SYS_CRG_BASE + 0xB0)

#define SYS_SYSCON_40_REG	(SYS_SYSCON_BASE + 0x28)
#define SYS_SYSCON_36_REG	(SYS_SYSCON_BASE + 0x24)
#define SYS_SYSCON_44_REG	(SYS_SYSCON_BASE + 0x2c)

#define RESET_ASSERT0_REG	(SYS_CRG_BASE + 0x2F8)
#define RESET_ASSERT1_REG	(SYS_CRG_BASE + 0x2FC)
#define RESET_ASSERT2_REG	(SYS_CRG_BASE + 0x300)
#define RESET_ASSERT3_REG	(SYS_CRG_BASE + 0x304)

#define RESET_STATUS0_REG	(SYS_CRG_BASE + 0x308)
#define RESET_STATUS1_REG	(SYS_CRG_BASE + 0x30C)
#define RESET_STATUS2_REG	(SYS_CRG_BASE + 0x310)
#define RESET_STATUS3_REG	(SYS_CRG_BASE + 0x314)

#define RSTN_AXI_MASK		(0x1 << 6)
#define RSTN_OSC_MASK		(0x1 << 7)
#define RSTN_APB_MASK		(0x1 << 8)

#define CLK_DDR_BUS_MASK    	0x3000000U
#define PLL1_PD_MASK		0x8000000U
#define PLL1_DACPD_MASK		0x8000U
#define PLL1_DSMPD_MASK		0x10000U
#define PLL1_FRAC_MASK		0xFFFFFFU
#define PLL1_FBDIV_MASK		0x1FFE0000U
#define PLL1_PREDIV_MASK	0x3FU
#define PLL1_POSTDIV1_MASK	0x30000000U
#define CLK_AXI_EN_MASK		0x80000000U

struct ddr_reg_set{
	u32 offset;
	u32 val;
};

struct ddr_reg_clrset{
	u32 offset;
	u32 mask;
	u32 val;
};

enum ddr_size_t {
	DDR_SIZE_2G,
	DDR_SIZE_4G,
	DDR_SIZE_8G,
	DDR_SIZE_16G,
};

void ddr_phy_train(u32 *phyreg);
void ddr_phy_util(u32 *phyreg);
void ddr_phy_start(u32 *phyreg, enum ddr_size_t size);
void ddrcsr_boot(u32 *csrreg, u32 *secreg, u32 *phyreg, enum ddr_size_t size);

#define DDR_REG_TRIGGER(addr, mask, value) \
	out_le32((addr), (in_le32(addr) & (mask)) | (value))

#endif /*__STARFIVE_DDR_H__*/

