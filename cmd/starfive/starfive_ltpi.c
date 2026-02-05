// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2026 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Zhi Wei Lim <zhiwei.lim@starfivetech.com>
 */

#include <common.h>
#include <command.h>
#include <env.h>
#include <malloc.h>
#include <misc.h>
#include <linux/types.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/bitfield.h>
#include <linux/delay.h>
#include <asm/io.h>

/* LTPI Base Address */
#define LTPI_0_BASE_ADDR				0x11900000UL
#define LTPI_1_BASE_ADDR				0x11910000UL

/* PER0_SYSCON */
#define JHB100_PER0_SYSCON_ADDR_0			0x11a09000UL
#define JHB100_PER0_SYSCON_ADDR_4			0x11a09004UL

/* PER0CRG */
#define JHB100_PER0CRG_ADDR				0x11a08000UL
#define JHB100_PER0CLK_PH0_LTPI0_OFFSET			0x84
#define JHB100_PER0CLK_CLK_PH0_LTPI0_OFFSET		0x88
#define JHB100_PER0CLK_PH0_LTPI1_OFFSET			0x8c
#define JHB100_PER0CLK_CLK_PH0_LTPI1_OFFSET		0x90
#define JHB100_PER0CLK_PH90_LTPI0_OFFSET		0x94
#define JHB100_PER0CLK_CLK_PH90_LTPI0_OFFSET		0x98
#define JHB100_PER0CLK_PH90_LTPI1_OFFSET		0x9c
#define JHB100_PER0CLK_CLK_PH90_LTPI1_OFFSET		0xa0
#define JHB100_PER0CRG_CORE_LTPI0_OFFSET		0xa4
#define JHB100_PER0CRG_CLK_CORE_LTPI0_OFFSET		0xa8
#define JHB100_PER0CRG_CORE_LTPI1_OFFSET		0xac
#define JHB100_PER0CRG_CLK_CORE_LTPI1_OFFSET		0xb0
#define JHB100_PER0CRG_CLK_BASE_LTPI0			0x238
#define JHB100_PER0CRG_CLK_BASE_LTPI1			0x23c
#define JHB100_PER0CRG_CLK_PCLK_LTPI0			0x268
#define JHB100_PER0CRG_CLK_PCLK_LTPI1			0x26c
#define JHB100_PER0CRG_MAIN_ICG_EN_LTPI0_OFFSET		0x440
#define JHB100_PER0CRG_MAIN_ICG_EN_LTPI1_OFFSET		0x444
#define JHB100_PER0CRG_RESET_ASSERT1_OFFSET		0x558
#define JHB100_RSTN_LTPI0				BIT(24)
#define JHB100_RSTN_LTPI1				BIT(25)

/* The LTPI Register Offset */
#define STARFIVE_REG_LINK_STA				0x00
#define STARFIVE_REG_DET_CAP_L				0x04
#define STARFIVE_REG_DET_CAP_R				0x08
#define STARFIVE_REG_PLT_ID_L				0x0C
#define STARFIVE_REG_PLT_ID_R				0x10
#define STARFIVE_REG_ADV_CAP_LOCAL_L			0x14
#define STARFIVE_REG_ADV_CAP_LOCAL_H			0x18
#define STARFIVE_REG_ADV_CAP_REMOTE_L			0x1C
#define STARFIVE_REG_ADV_CAP_REMOTE_H			0x20
#define STARFIVE_REG_DEF_CFG_L				0x24
#define STARFIVE_REG_DEF_CFG_H				0x28
#define STARFIVE_REG_LINK_ALI_ERR_CNT			0x2C
#define STARFIVE_REG_LINK_LST_ERR_CNT			0x30
#define STARFIVE_REG_CRC_ERR_CNT			0x34
#define STARFIVE_REG_UKN_COM_ERR_CNT			0x38
#define STARFIVE_REG_SPD_TMO_ERR_CNT			0x3C
#define STARFIVE_REG_LINK_CFG_ACPT_TMO_ERR_CNT		0x40
#define STARFIVE_REG_LINK_TRN_RX_FRM_CNT_L		0x44
#define STARFIVE_REG_LINK_TRN_RX_FRM_CNT_H		0x48
#define STARFIVE_REG_LINK_TRN_TX_FRM_CNT_L		0x4C
#define STARFIVE_REG_LINK_TRN_TX_FRM_CNT_H		0x50
#define STARFIVE_REG_OP_RX_FRM_CNT			0x54
#define STARFIVE_REG_OP_TX_FRM_CNT			0x58
#define STARFIVE_REG_LINK_CTL				0x80
#define STARFIVE_REG_LINK_CTL2				0x100
#define STARFIVE_REG_LINK_CTL3				0x104
#define STARFIVE_REG_IRQ_ERR				0x120
#define STARFIVE_REG_IRQ_MASK				0x124
#define STARFIVE_REG_REQ_ADDR				0x140
#define STARFIVE_REG_REQ_DATA				0x144
#define STARFIVE_REG_REQ_ATTR				0x148
#define STARFIVE_REG_RESP_ADDR				0x14C
#define STARFIVE_REG_RESP_DATA				0x150
#define STARFIVE_REG_RESP_ATTR				0x154
#define STARFIVE_REG_REQ_RESP_STA			0x158
#define STARFIVE_REG_REQ_RESP_CTL			0x15C
#define STARFIVE_REG_PC_X1				0x180
#define STARFIVE_REG_PC_X2				0x184
#define STARFIVE_REG_PC_X3				0x188
#define STARFIVE_REG_PC_X4				0x18C
#define STARFIVE_REG_PC_X6				0x190
#define STARFIVE_REG_PC_X8				0x194
#define STARFIVE_REG_PC_X10				0x198
#define STARFIVE_REG_PC_X12				0x19C
#define STARFIVE_REG_PC_X16				0x1A0
#define STARFIVE_REG_PC_X24				0x1A4
#define STARFIVE_REG_PC_X32				0x1A8
#define STARFIVE_REG_PC_X40				0x1AC
#define STARFIVE_REG_LPB_BIST				0x1D0

/* Channel support macros */
#define LTPI_CAP_GPIO_CHANNEL		BIT(0)
#define LTPI_CAP_I2C_CHANNEL		BIT(1)
#define LTPI_CAP_UART_CHANNEL		BIT(2)
#define LTPI_CAP_DATA_CHANNEL		BIT(3)

/* STARFIVE_REG_LINK_STA reg */
#define LINK_ALIGN_MSK			BIT(0)
#define LINK_ALIGN_SFT			0
#define DDR_MOD_MSK			BIT(7)
#define DDR_MOD_SFT			7
#define LINK_SPEED_MSK			GENMASK(11, 8)
#define LINK_SPEED_SFT			8
#define R_LINK_STA_MSK			GENMASK(15, 12)
#define R_LINK_STA_SFT			12
#define L_LINK_STA_MSK			GENMASK(19, 16)
#define L_LINK_STA_SFT			16

/* STARFIVE_REG_DET_CAP_L reg */
#define FREQ_150_MHZ_MSK		BIT(12)
#define DDR_SUP_MSK			BIT(23)

/* STARFIVE_REG_LINK_CTL reg */
#define LINK_SW_RST_MSK			BIT(0)
#define LINK_SW_RST_SFT			0
#define LINK_RETRN_REQ_MSK		BIT(1)
#define LINK_RETRN_REQ_SFT		1
#define DAT_CH_RST_MSK			BIT(9)
#define DAT_CH_RST_SFT			9
#define AUTO_MOV_CFG_STA_MSK		BIT(10)
#define AUTO_MOV_CFG_STA_SFT		10
#define TRIG_CFG_STA_MSK		BIT(11)
#define TRIG_CFG_STA_SFT		11

/* STARFIVE_REG_LINK_CTL2 */
#define LINK_CST_IO_EN_MSK		BIT(0)

/* STARFIVE_REG_REQ_ATTR reg */
#define LTPI_ATTR_WRITE_BIT		BIT(16)
#define LTPI_ATTR_TAG_SHIFT		24
#define LTPI_ATTR_BYTE_EN_MASK		0xF

/* STARFIVE_REG_RESP_ATTR reg */
#define LTPI_RESP_CRC_ERR_BIT		BIT(18)

/* STARFIVE_REG_REQ_RESP_STA reg */
#define LTPI_RESP_READY_BIT		BIT(0)
#define LTPI_REQ_READY_BIT		BIT(1)

/* STARFIVE_REG_REQ_RESP_CTL reg */
#define LTPI_REQ_TRIGGER_BIT		BIT(1)

/* UART Max Baud Rate Encoding */
#define LTPI_UART_BAUD_300		0x00
#define LTPI_UART_BAUD_600		0x01
#define LTPI_UART_BAUD_1200		0x02
#define LTPI_UART_BAUD_1800		0x03
#define LTPI_UART_BAUD_2400		0x04
#define LTPI_UART_BAUD_4800		0x05
#define LTPI_UART_BAUD_9600		0x06
#define LTPI_UART_BAUD_19200		0x07
#define LTPI_UART_BAUD_38400		0x08
#define LTPI_UART_BAUD_57600		0x09
#define LTPI_UART_BAUD_115200		0x0A
#define LTPI_UART_BAUD_230400		0x0B
#define LTPI_UART_BAUD_460800		0x0C
#define LTPI_UART_BAUD_576000		0x0D
#define LTPI_UART_BAUD_921600		0x0E

/* I2C Speed Capabilities */
#define LTPI_CAP_I2C_SPEED_100KHZ	0x0	/* 100 KHz */
#define LTPI_CAP_I2C_SPEED_400KHZ	0x1	/* 400 KHz */

/* Miscellaneous */
#define LTPI_TIMEOUT_MS				1000
#define LTPI_LINK_RST_DELAY_US			10
#define LTPI_REQ_TIMEOUT_MS			10
#define LTPI_RESP_TIMEOUT_MS			10
#define LTPI_SPEED_FREQ_ID_MAX			13
#define LTPI_PLL_CLOCK_FREQ			2400000000
#define LTPI_CONTROLLER_CLOCK_SOURCE_FREQ	(LTPI_PLL_CLOCK_FREQ / 2 / 5)
#define LTPI_MAX_ATTEMPT			10
#define JHB100_MAIN_CLK_ENABLE			BIT(31)

enum starfive_ltpi_link_state {
	STA_LINK_DET,
	STA_LINK_SPD,
	STA_LINK_ADV,
	STA_LINK_CFG,
	STA_LINK_OP,
	STA_LINK_MAX,
};

enum starfive_ltpi_gpio_type {
	LTPI_GPIO_TYPE_LL = 0,		/* Low Latency GPIO */
	LTPI_GPIO_TYPE_NL		/* Normal Latency GPIO */
};

struct starfive_ltpi_cap_config {
	u8 supported_channels;		/* Supported channels bitmap */
	u16 ll_gpio_caps;		/* LL GPIO capabilities */
	u16 nl_gpio_caps;		/* NL GPIO capabilities */
	u8 i2c_caps;			/* I2C capabilities */
	u32 i2c_speed;			/* I2C speed capabilities */
	bool is_echo_supported;		/* Echo supported */
	u8 uart_caps;			/* UART capabilities */
	u8 uart_max_baud_rate;		/* UART baud rate */
	bool is_uart_flow_ctrl_enabled;	/* UART flow control */
};

struct ltpi_clk_desc {
	u32 main_icg_en;
	u32 ph0_div;
	u32 ph90_div;
	u32 ph0_en;
	u32 ph90_en;
	u32 core_div;
	u32 core_clk;
	u32 base_clk;
	u32 pclk;
	u32 reset_bit;
	const char *name;
};

static const u32 starfive_ltpi_spd_sup_sdr_60m[LTPI_SPEED_FREQ_ID_MAX] = {
	24, 12, 8, 6, 4, 0, 0, 0, 0, 0, 0, 0, 0
};

static const struct ltpi_clk_desc ltpi_desc[] = {
	[0] = {
		.main_icg_en = JHB100_PER0CRG_MAIN_ICG_EN_LTPI0_OFFSET,
		.ph0_div     = JHB100_PER0CLK_PH0_LTPI0_OFFSET,
		.ph90_div    = JHB100_PER0CLK_PH90_LTPI0_OFFSET,
		.ph0_en      = JHB100_PER0CLK_CLK_PH0_LTPI0_OFFSET,
		.ph90_en     = JHB100_PER0CLK_CLK_PH90_LTPI0_OFFSET,
		.core_div    = JHB100_PER0CRG_CORE_LTPI0_OFFSET,
		.core_clk    = JHB100_PER0CRG_CLK_CORE_LTPI0_OFFSET,
		.base_clk    = JHB100_PER0CRG_CLK_BASE_LTPI0,
		.pclk        = JHB100_PER0CRG_CLK_PCLK_LTPI0,
		.reset_bit   = JHB100_RSTN_LTPI0,
		.name        = "LTPI0",
	},
	[1] = {
		.main_icg_en = JHB100_PER0CRG_MAIN_ICG_EN_LTPI1_OFFSET,
		.ph0_div     = JHB100_PER0CLK_PH0_LTPI1_OFFSET,
		.ph90_div    = JHB100_PER0CLK_PH90_LTPI1_OFFSET,
		.ph0_en      = JHB100_PER0CLK_CLK_PH0_LTPI1_OFFSET,
		.ph90_en     = JHB100_PER0CLK_CLK_PH90_LTPI1_OFFSET,
		.core_div    = JHB100_PER0CRG_CORE_LTPI1_OFFSET,
		.core_clk    = JHB100_PER0CRG_CLK_CORE_LTPI1_OFFSET,
		.base_clk    = JHB100_PER0CRG_CLK_BASE_LTPI1,
		.pclk        = JHB100_PER0CRG_CLK_PCLK_LTPI1,
		.reset_bit   = JHB100_RSTN_LTPI1,
		.name        = "LTPI1",
	},
};

static int ltpi_clock_enable(int id)
{
	const struct ltpi_clk_desc *d;
	void *syscon0 = (void *)JHB100_PER0_SYSCON_ADDR_0;
	void *syscon4 = (void *)JHB100_PER0_SYSCON_ADDR_4;
	void *crg;
	u32 val, timeout;
	u32 controller_clk_div;

	if (id < 0 || id > 1)
		return -EINVAL;

	d = &ltpi_desc[id];

	/* Disable PLL output & gate post-divider */
	val = readl(syscon0);
	val &= ~BIT(14);
	val |= BIT(15);
	writel(val, syscon0);

	/* Program PLL fractional divider */
	val = readl(syscon4);
	val |= 0x7dd4;
	writel(val, syscon4);

	/* Ungate post-divider */
	val = readl(syscon0);
	val &= ~BIT(15);
	writel(val, syscon0);

	/* Wait for PLL lock */
	timeout = 300;
	while (timeout--) {
		val = readl(syscon4);
		if (val & BIT(24))
			break;
		mdelay(10);
	}

	if (!(val & BIT(24))) {
		printf("%s PLL lock timeout\n", d->name);
		return -ETIMEDOUT;
	}

	controller_clk_div =
		LTPI_CONTROLLER_CLOCK_SOURCE_FREQ / 60000000;

	/* Disable main clock */
	crg = (void *)(JHB100_PER0CRG_ADDR + d->main_icg_en);
	writel(readl(crg) & ~JHB100_MAIN_CLK_ENABLE, crg);

	/* Program PH dividers */
	crg = (void *)(JHB100_PER0CRG_ADDR + d->ph0_div);
	writel((readl(crg) & ~0xFFFFFF) | 8, crg);

	crg = (void *)(JHB100_PER0CRG_ADDR + d->ph90_div);
	writel((readl(crg) & ~0xFFFFFF) | 8, crg);

	/* Enable PH clocks */
	crg = (void *)(JHB100_PER0CRG_ADDR + d->ph0_en);
	writel(readl(crg) | JHB100_MAIN_CLK_ENABLE, crg);

	crg = (void *)(JHB100_PER0CRG_ADDR + d->ph90_en);
	writel(readl(crg) | JHB100_MAIN_CLK_ENABLE, crg);

	/* Core divider */
	crg = (void *)(JHB100_PER0CRG_ADDR + d->core_div);
	writel((readl(crg) & ~0xFFFFFF) | controller_clk_div, crg);

	/* Enable clocks */
	crg = (void *)(JHB100_PER0CRG_ADDR + d->core_clk);
	writel(readl(crg) | JHB100_MAIN_CLK_ENABLE, crg);

	crg = (void *)(JHB100_PER0CRG_ADDR + d->base_clk);
	writel(readl(crg) | JHB100_MAIN_CLK_ENABLE, crg);

	crg = (void *)(JHB100_PER0CRG_ADDR + d->pclk);
	writel(readl(crg) | JHB100_MAIN_CLK_ENABLE, crg);

	/* Reset */
	crg = (void *)(JHB100_PER0CRG_ADDR +
		       JHB100_PER0CRG_RESET_ASSERT1_OFFSET);
	val = readl(crg);
	val |= d->reset_bit;
	writel(val, crg);
	udelay(10);
	val &= ~d->reset_bit;
	writel(val, crg);

	/* Enable clock gating */
	crg = (void *)(JHB100_PER0CRG_ADDR + d->main_icg_en);
	writel(readl(crg) | JHB100_MAIN_CLK_ENABLE, crg);

	/* Enable PLL output */
	val = readl(syscon0);
	val |= BIT(14);
	writel(val, syscon0);

	return 0;
}

static inline void __iomem *starfive_ltpi_base(int id)
{
	return (id == 0) ? (void __iomem *)LTPI_0_BASE_ADDR
			 : (void __iomem *)LTPI_1_BASE_ADDR;
}

static inline void starfive_ltpi_clr_cnt(void __iomem *base, u32 start, u32 end)
{
	for (u32 off = start; off <= end; off += 4)
		writel(GENMASK(31, 0), base + off);
}

static void starfive_ltpi_set_maxspeed(void __iomem *base)
{
	u32 reg;

	for (int i = 0; i < ARRAY_SIZE(starfive_ltpi_spd_sup_sdr_60m); i++)
		writel(starfive_ltpi_spd_sup_sdr_60m[i], base + STARFIVE_REG_PC_X1 + i * 4);

	reg = readl(base + STARFIVE_REG_DET_CAP_L);
	reg &= ~(GENMASK(23, 8));
	reg |= DDR_SUP_MSK | FREQ_150_MHZ_MSK;
	writel(reg, base + STARFIVE_REG_DET_CAP_L);
}

static inline void starfive_ltpi_speed_cap_set(void __iomem *base)
{
	starfive_ltpi_set_maxspeed(base);
}

static inline void starfive_ltpi_set_auto_cfg(void __iomem *base)
{
	writel(readl(base + STARFIVE_REG_LINK_CTL) | AUTO_MOV_CFG_STA_MSK,
	       base + STARFIVE_REG_LINK_CTL);
}

static inline void starfive_ltpi_retrain_start(void __iomem *base)
{
	writel(readl(base + STARFIVE_REG_LINK_CTL) | LINK_RETRN_REQ_MSK,
	       base + STARFIVE_REG_LINK_CTL);
}

static inline void starfive_ltpi_enable_custom(void __iomem *base, bool enable)
{
	u32 reg = readl(base + STARFIVE_REG_LINK_CTL2);

	if (enable)
		reg |= LINK_CST_IO_EN_MSK;
	else
		reg &= ~LINK_CST_IO_EN_MSK;

	writel(reg, base + STARFIVE_REG_LINK_CTL2);
}

static void starfive_ltpi_clr_all(void __iomem *base)
{
	starfive_ltpi_clr_cnt(base,
			      STARFIVE_REG_LINK_ALI_ERR_CNT,
			      STARFIVE_REG_LINK_CFG_ACPT_TMO_ERR_CNT);

	starfive_ltpi_clr_cnt(base,
			      STARFIVE_REG_LINK_TRN_RX_FRM_CNT_L,
			      STARFIVE_REG_OP_TX_FRM_CNT);

	writel(GENMASK(31, 0), base + STARFIVE_REG_IRQ_ERR);
}

static inline void starfive_ltpi_start(void __iomem *base)
{
	starfive_ltpi_clr_all(base);
	starfive_ltpi_retrain_start(base);
}

static void starfive_ltpi_default_frame_init(void __iomem *base,
					     struct starfive_ltpi_cap_config *caps)
{
	u32 cap_low, cap_high;
	u8 supported_channels = caps->supported_channels & 0x1F;
	u16 nl_gpio_count = caps->nl_gpio_caps & 0x3FF;
	u8 i2c_enable = (caps->i2c_caps & 0x3F) |
			(caps->is_echo_supported ? BIT(6) : 0);

	cap_low = supported_channels |
		  (nl_gpio_count << 8) |
		  (i2c_enable << 24);

	u8 i2c_speed = caps->i2c_speed & 0x3F;
	u8 uart_cfg = ((caps->uart_caps & 0x03) << 5) |
		      (caps->is_uart_flow_ctrl_enabled ? BIT(4) : 0) |
		      (caps->uart_max_baud_rate & 0x0F);

	u16 i2c_ext = ((caps->i2c_caps >> 6) & 0xFF) |
		      (((caps->i2c_speed >> 6) & 0xFF) << 8);

	cap_high = i2c_speed |
		   (uart_cfg << 8) |
		   (i2c_ext << 16);

	writel(cap_low,  base + STARFIVE_REG_ADV_CAP_LOCAL_L);
	writel(cap_high, base + STARFIVE_REG_ADV_CAP_LOCAL_H);

	starfive_ltpi_enable_custom(base, false);
}

static bool starfive_ltpi_link_is_up(void __iomem *base)
{
	u32 state = readl(base + STARFIVE_REG_LINK_STA);

	return (FIELD_GET(L_LINK_STA_MSK, state) == STA_LINK_OP) &&
	       (FIELD_GET(R_LINK_STA_MSK, state) == STA_LINK_OP);
}

static inline int starfive_ltpi_local_state_get(void __iomem *base)
{
	return (readl(base + STARFIVE_REG_LINK_STA) >> 16) & 0xF;
}

static void starfive_ltpi_supported_channels(u8 channels, char *buf)
{
	buf[0] = '\0';

	if (channels & LTPI_CAP_GPIO_CHANNEL)
		strcat(buf, "GPIO ");
	if (channels & LTPI_CAP_I2C_CHANNEL)
		strcat(buf, "I2C ");
	if (channels & LTPI_CAP_UART_CHANNEL)
		strcat(buf, "UART ");
	if (channels & LTPI_CAP_DATA_CHANNEL)
		strcat(buf, "DATA ");

	if (!buf[0])
		strcpy(buf, "none");
	else
		buf[strlen(buf) - 1] = '\0';
}

static const char *starfive_ltpi_i2c_speed_str(u8 speed)
{
	switch (speed & 0x3F) {
	case LTPI_CAP_I2C_SPEED_100KHZ: return "100kHz";
	case LTPI_CAP_I2C_SPEED_400KHZ: return "400kHz";
	default: return "unknown";
	}
}

static void starfive_ltpi_i2c_caps_str(u8 caps, char *buf)
{
	int i;
	bool first = true;

	buf[0] = '\0';

	if (!(caps & 0x3F)) {
		strcpy(buf, "none");
		return;
	}

	for (i = 0; i < 6; i++) {
		if (caps & BIT(i)) {
			if (!first)
				strcat(buf, " ");
			sprintf(buf + strlen(buf), "I2C%d", i);
			first = false;
		}
	}
}

static const char *starfive_ltpi_uart_caps_str(u8 caps)
{
	switch (caps & 0x03) {
	case 0: return "off";
	case 1: return "UART0";
	case 2: return "UART1";
	case 3: return "UART0+UART1";
	default: return "unknown";
	}
}

static const char *starfive_ltpi_uart_baud_str(u8 baud)
{
	switch (baud & 0x0F) {
	case LTPI_UART_BAUD_300:     return "300";
	case LTPI_UART_BAUD_600:     return "600";
	case LTPI_UART_BAUD_1200:    return "1200";
	case LTPI_UART_BAUD_1800:    return "1800";
	case LTPI_UART_BAUD_2400:    return "2400";
	case LTPI_UART_BAUD_4800:    return "4800";
	case LTPI_UART_BAUD_9600:    return "9600";
	case LTPI_UART_BAUD_19200:   return "19200";
	case LTPI_UART_BAUD_38400:   return "38400";
	case LTPI_UART_BAUD_57600:   return "57600";
	case LTPI_UART_BAUD_115200:  return "115200";
	case LTPI_UART_BAUD_230400:  return "230400";
	case LTPI_UART_BAUD_460800:  return "460800";
	case LTPI_UART_BAUD_576000:  return "576000";
	case LTPI_UART_BAUD_921600:  return "921600";
	default: return "unknown";
	}
}

static void starfive_ltpi_dump_caps(int id,
				    struct starfive_ltpi_cap_config *caps)
{
	char buf[64];
	u8 channels = caps->supported_channels & 0x1F;

	starfive_ltpi_supported_channels(channels, buf);
	printf("LTPI%d capabilities (default frame):\n", id);
	printf("  supported channels       : %s\n", buf);

	/* GPIO */
	if (channels & LTPI_CAP_GPIO_CHANNEL)
		printf("  nl gpio count            : %u\n",
		       caps->nl_gpio_caps & 0x3FF);

	/* I2C */
	if (channels & LTPI_CAP_I2C_CHANNEL) {
		starfive_ltpi_i2c_caps_str(caps->i2c_caps, buf);
		printf("  i2c capabilities         : %s\n", buf);
		printf("  i2c speed                : %s\n",
		       starfive_ltpi_i2c_speed_str(caps->i2c_speed));
		printf("  i2c echo support         : %s\n",
		       caps->is_echo_supported ? "yes" : "no");
	}

	/* UART */
	if (channels & LTPI_CAP_UART_CHANNEL) {
		printf("  uart capabilities        : %s\n",
		       starfive_ltpi_uart_caps_str(caps->uart_caps));
		printf("  uart flow control        : %s\n",
		       caps->is_uart_flow_ctrl_enabled ? "enabled" : "disabled");
		printf("  uart max baud rate       : %s\n",
		       starfive_ltpi_uart_baud_str(caps->uart_max_baud_rate));
	}

	printf("\n");
}

static void starfive_ltpi_init(int id,
			       struct starfive_ltpi_cap_config *config)
{
	void __iomem *base = starfive_ltpi_base(id);
	const unsigned long timeout = LTPI_TIMEOUT_MS;
	unsigned long start;
	bool operational = false;
	int ret;

	/* Enable clock */
	ret = ltpi_clock_enable(id);
	if (ret) {
		printf("ERROR: LTPI%d clock enable failed (%d)\n", id, ret);
		return;
	}

	/* Configure speed & capabilities */
	starfive_ltpi_speed_cap_set(base);
	starfive_ltpi_default_frame_init(base, config);
	starfive_ltpi_set_auto_cfg(base);

	/* Start training */
	starfive_ltpi_start(base);

	/* Wait for training start */
	start = get_timer(0);
	while (!(readl(base + STARFIVE_REG_LINK_STA) & BIT(12))) {
		if (get_timer(start) > timeout) {
			printf("LTPI%d: training start timeout\n", id);
			return;
		}
		mdelay(1);
	}

	/* Retry training */
	for (int i = 0; i < LTPI_MAX_ATTEMPT; i++) {
		start = get_timer(0);

		while (get_timer(start) <= timeout) {
			if (starfive_ltpi_local_state_get(base) == STA_LINK_OP) {
				operational = true;
				break;
			}
			mdelay(10);
		}

		if (operational) {
			printf("LTPI%d: operational, link up (DDR, 150 MHz)\n", id);
			starfive_ltpi_dump_caps(id, config);
			break;
		}

		printf("LTPI%d: retraining attempt %d\n", id, i + 1);
		starfive_ltpi_clr_all(base);
		starfive_ltpi_retrain_start(base);
	}

	starfive_ltpi_clr_all(base);
}

static int starfive_ltpi_gpio_enable(void __iomem *base,
				     enum starfive_ltpi_gpio_type type,
				     u16 gpio_num,
				     u16 gpio_range,
				     bool enable)
{
	u32 base_offset;
	u32 reg_offset;
	u32 bit_pos;
	u32 mask;
	u16 remaining = gpio_range;

	base_offset = (type == LTPI_GPIO_TYPE_LL) ? 0x1000 : 0x2000;

	while (remaining) {
		u32 bits_in_reg;

		bit_pos = gpio_num % 32;
		bits_in_reg = min_t(u32, 32 - bit_pos, remaining);

		mask = (bits_in_reg == 32) ? 0xFFFFFFFF
			: ((1U << bits_in_reg) - 1) << bit_pos;

		reg_offset = (enable ? 0x100 : 0x80) +
			     (gpio_num / 32) * 4;

		writel(mask, base + base_offset + reg_offset);

		gpio_num += bits_in_reg;
		remaining -= bits_in_reg;
	}

	return 0;
}

static int starfive_ltpi_gpio_output_set(void __iomem *base,
					 enum starfive_ltpi_gpio_type type,
					 u16 pin_start,
					 u16 pin_range,
					 bool enable)
{
	u32 base_offset;
	u16 remaining = pin_range;
	u16 gpio = pin_start;
	u32 reg_offset;
	u32 bit_pos;
	u32 bits_in_reg;
	u32 mask;

	base_offset = (type == LTPI_GPIO_TYPE_LL) ? 0x1000 : 0x2000;

	while (remaining) {
		reg_offset = (gpio / 32) * 4;
		bit_pos = gpio % 32;
		bits_in_reg = (remaining > (32 - bit_pos)) ? (32 - bit_pos) : remaining;
		mask = ((1U << bits_in_reg) - 1) << bit_pos;
		writel(enable ? mask : 0, base + base_offset + reg_offset);

		gpio += bits_in_reg;
		remaining -= bits_in_reg;
	}

	return 0;
}

static int starfive_ltpi_gpio_config_input(void __iomem *base,
					   enum starfive_ltpi_gpio_type type,
					   u16 pin_start,
					   u16 pin_range)
{
	u32 base_offset;
	u16 remaining = pin_range;
	u16 gpio = pin_start;
	u32 reg_offset;
	u32 bit_pos;
	u32 bits_in_reg;
	u32 reg_value;

	base_offset = (type == LTPI_GPIO_TYPE_LL) ? 0x1000 : 0x2000;

	printf("LTPI GPIO %s input status:\n", (type == LTPI_GPIO_TYPE_LL) ? "LL" : "NL");

	while (remaining) {
		reg_offset = 0x180 + (gpio / 32) * 4;
		bit_pos = gpio % 32;
		bits_in_reg = (remaining > (32 - bit_pos)) ? (32 - bit_pos) : remaining;

		reg_value = readl(base + base_offset + reg_offset);

		for (u32 i = 0; i < bits_in_reg; i++) {
			u32 pin = gpio + i;
			bool high = reg_value & (1U << (bit_pos + i));

			printf("  GPI_%u = %s\n", pin, high ? "HIGH" : "LOW");
		}
		gpio += bits_in_reg;
		remaining -= bits_in_reg;
	}

	return 0;
}

static int starfive_ltpi_data_channel_reset(void __iomem *base)
{
	u32 reg;

	reg = readl(base + STARFIVE_REG_LINK_CTL);
	reg |= DAT_CH_RST_MSK;
	writel(reg, base + STARFIVE_REG_LINK_CTL);

	udelay(LTPI_LINK_RST_DELAY_US);

	reg &= ~DAT_CH_RST_MSK;
	writel(reg, base + STARFIVE_REG_LINK_CTL);

	return 0;
}

static int starfive_ltpi_data_channel_send_req(void __iomem *base,
					       u32 data, u32 address,
					       bool is_write)
{
	u32 status;
	u32 req_attr = 0;
	ulong start;
	bool ready;
	static u8 tag;
	u32 byte_enable = LTPI_ATTR_BYTE_EN_MASK;

	/* Wait until request buffer is ready */
	start = get_timer(0);
	do {
		status = readl(base + STARFIVE_REG_REQ_RESP_STA);
		ready = status & LTPI_REQ_READY_BIT;

		if (get_timer(start) > LTPI_REQ_TIMEOUT_MS) {
			printf("LTPI: request buffer timeout\n");
			starfive_ltpi_data_channel_reset(base);
			return -ETIMEDOUT;
		}
	} while (!ready);

	writel(address, base + STARFIVE_REG_REQ_ADDR);

	if (is_write)
		writel(data, base + STARFIVE_REG_REQ_DATA);

	if (is_write)
		req_attr |= LTPI_ATTR_WRITE_BIT;

	req_attr |= ((u32)tag++ << LTPI_ATTR_TAG_SHIFT);
	req_attr |= byte_enable;

	writel(req_attr, base + STARFIVE_REG_REQ_ATTR);

	debug("LTPI: send %s req addr=0x%04X attr=0x%08X\n",
	      is_write ? "WRITE" : "READ", address, req_attr);

	writel(LTPI_REQ_TRIGGER_BIT,
	       base + STARFIVE_REG_REQ_RESP_CTL);

	while (readl(base + STARFIVE_REG_REQ_RESP_CTL) &
	       LTPI_REQ_TRIGGER_BIT)
		;

	return 0;
}

static int starfive_ltpi_data_channel_read_resp(void __iomem *base,
						u32 *addr, u32 *data,
						bool is_write)
{
	u32 status;
	u32 attributes;
	ulong start;

	/* Wait for response ready */
	start = get_timer(0);
	while (1) {
		status = readl(base + STARFIVE_REG_REQ_RESP_STA);
		if (status & LTPI_RESP_READY_BIT)
			break;

		if (get_timer(start) > LTPI_RESP_TIMEOUT_MS) {
			printf("LTPI: read response timeout\n");
			starfive_ltpi_data_channel_reset(base);
			return -ETIMEDOUT;
		}
	}

	*addr = readl(base + STARFIVE_REG_RESP_ADDR);
	*data = readl(base + STARFIVE_REG_RESP_DATA);
	attributes = readl(base + STARFIVE_REG_RESP_ATTR);

	writel(1, base + STARFIVE_REG_REQ_RESP_CTL);
	while (readl(base + STARFIVE_REG_REQ_RESP_CTL) & 1)
		;

	/* Check CRC error */
	if (attributes & LTPI_RESP_CRC_ERR_BIT) {
		printf("LTPI: CRC error\n");
		if (is_write)
			printf("  addr=0x%04X\n", *addr);
		else
			printf("  addr=0x%04X data=0x%08X\n",
			       *addr, *data);
		printf("  attr=0x%08X\n", attributes);
		return -EILSEQ;
	}

	return 0;
}

static int starfive_ltpi_gpio_handler(int id,
				      enum starfive_ltpi_gpio_type type,
				      int pin_start,
				      int pin_range,
				      bool output_high,
				      bool is_input)
{
	void __iomem *ltpi_base;
	struct starfive_ltpi_cap_config config = { 0 };
	int max_range, max_gpio;

	if (id < 0 || id > 1)
		return -EINVAL;

	ltpi_base = starfive_ltpi_base(id);

	/*
	 * GPIO limits for LTPI default frame operations:
	 *
	 * LL (Low Latency) GPIO:
	 *   - max_range: 16 -> maximum number of pins allowed per operation
	 *   - max_gpio : 64 -> total pins supported by the controller
	 * NL (Normal Latency) GPIO:
	 *   - max_range: 32 -> maximum number of pins allowed per operation
	 *   - max_gpio : 256 -> total pins supported by the controller
	 */
	max_range = (type == LTPI_GPIO_TYPE_LL) ? 16 : 32;
	max_gpio  = (type == LTPI_GPIO_TYPE_LL) ? 64 : 256;

	if (pin_start < 0 || pin_start >= max_gpio)
		return -EINVAL;

	if (pin_range < 1 || pin_range > max_range)
		return -EINVAL;

	if (pin_start + pin_range > max_gpio)
		return -EINVAL;

	config.supported_channels = LTPI_CAP_GPIO_CHANNEL;

	if (type == LTPI_GPIO_TYPE_LL)
		config.ll_gpio_caps = pin_range;
	else
		config.nl_gpio_caps = pin_range;

	starfive_ltpi_init(id, &config);

	if (!starfive_ltpi_link_is_up(ltpi_base)) {
		printf("LTPI%d: link down\n", id);
		return -EIO;
	}

	if (is_input) {
		starfive_ltpi_gpio_config_input(ltpi_base, type, pin_start, pin_range);

		printf("LTPI%d GPIO %s configured as INPUT: start=%d range=%d\n",
		       id,
		       (type == LTPI_GPIO_TYPE_LL) ? "LL (Low Latency)" : "NL (Normal Latency)",
		       pin_start,
		       pin_range);
	} else {
		/* Disable all GPIOs first */
		starfive_ltpi_gpio_enable(ltpi_base, type, 0, max_gpio, false);

		/* Enable requested range */
		starfive_ltpi_gpio_enable(ltpi_base, type,
					  pin_start, pin_range, true);

		/* Program GPIO output level */
		starfive_ltpi_gpio_output_set(ltpi_base, type,
					      pin_start, pin_range, output_high);

		printf("LTPI%d GPIO %s configured: start=%d range=%d level=%s\n",
		       id,
		       (type == LTPI_GPIO_TYPE_LL) ? "LL (Low Latency)" : "NL (Normal Latency)",
		       pin_start,
		       pin_range,
		       output_high ? "HIGH" : "LOW");
	}

	return 0;
}

static int starfive_ltpi_data_handler(int id, bool write, u32 addr, u32 value)
{
	void __iomem *ltpi_base;
	struct starfive_ltpi_cap_config config = { 0 };
	int ret;
	u32 resp_data = 0;
	u32 resp_addr = 0;

	if (id < 0 || id > 1)
		return -EINVAL;

	if (addr & 0x3) {
		printf("LTPI%d: invalid addr 0x%04X (must be 4-byte aligned)\n",
		       id, addr);
		return -EINVAL;
	}

	ltpi_base = starfive_ltpi_base(id);

	config.supported_channels = LTPI_CAP_DATA_CHANNEL;

	starfive_ltpi_init(id, &config);

	if (!starfive_ltpi_link_is_up(ltpi_base)) {
		printf("LTPI%d: link down\n", id);
		return -EIO;
	}

	if (write) {
		ret = starfive_ltpi_data_channel_send_req(ltpi_base, value, addr, true);
		if (ret) {
			printf("LTPI%d: write request failed (%d)\n",
			       id, ret);
			return ret;
		}
	} else {
		ret = starfive_ltpi_data_channel_send_req(ltpi_base, 0, addr, false);
		if (ret) {
			printf("LTPI%d: read request failed (%d)\n",
			       id, ret);
			return ret;
		}

		ret = starfive_ltpi_data_channel_read_resp(ltpi_base,
							   &resp_addr,
							   &resp_data,
							   false);
		if (ret) {
			printf("LTPI%d: read response failed (%d)\n",
			       id, ret);
			return ret;
		}

		printf("LTPI%d: data read @0x%04X = 0x%08X (32-bit)\n",
		       id, addr, resp_data);
	}

	return 0;
}

static int starfive_ltpi_uart_handler(int id, u8 mask)
{
	void __iomem *ltpi_base;
	struct starfive_ltpi_cap_config config = { 0 };

	if (id < 0 || id > 1)
		return -EINVAL;

	if (mask > 3)
		return -EINVAL;

	ltpi_base = starfive_ltpi_base(id);

	config.supported_channels = LTPI_CAP_UART_CHANNEL;
	config.uart_caps = mask;
	config.uart_max_baud_rate = LTPI_UART_BAUD_921600;

	starfive_ltpi_init(id, &config);

	if (!starfive_ltpi_link_is_up(ltpi_base)) {
		printf("LTPI%d: link down\n", id);
		return -EIO;
	}

	return 0;
}

static int starfive_ltpi_i2c_handler(int id, u8 mask, u32 speed)
{
	void __iomem *ltpi_base;
	struct starfive_ltpi_cap_config config = { 0 };

	if (id < 0 || id > 1)
		return -EINVAL;

	if (mask > 63)
		return -EINVAL;

	if (speed > 1)
		return -EINVAL;

	ltpi_base = starfive_ltpi_base(id);

	config.supported_channels = LTPI_CAP_I2C_CHANNEL;
	config.is_echo_supported = true;
	config.i2c_speed = speed;
	config.i2c_caps = mask;

	starfive_ltpi_init(id, &config);

	if (!starfive_ltpi_link_is_up(ltpi_base)) {
		printf("LTPI%d: link down\n", id);
		return -EIO;
	}

	return 0;
}

static void starfive_ltpi_gpio_nl(int dev, int pin_start, int pin_range,
				  bool output_high, bool is_input)
{
	int ret;

	ret = starfive_ltpi_gpio_handler(dev, LTPI_GPIO_TYPE_NL, pin_start, pin_range,
					 output_high, is_input);
	if (ret) {
		printf("LTPI UART GPIO NL failed for dev %d (err=%d)\n",
		       dev, ret);
	}
}

static void starfive_ltpi_gpio_ll(int dev, int pin_start, int pin_range,
				  bool output_high, bool is_input)
{
	int ret;

	ret = starfive_ltpi_gpio_handler(dev, LTPI_GPIO_TYPE_LL, pin_start, pin_range,
					 output_high, is_input);
	if (ret) {
		printf("LTPI UART GPIO LL failed for dev %d (err=%d)\n",
		       dev, ret);
	}
}

static void starfive_ltpi_data_read(int dev, u32 addr)
{
	int ret;

	ret = starfive_ltpi_data_handler(dev, false, addr, 0);
	if (ret) {
		printf("LTPI DATA READ failed for dev %d (err=%d)\n",
		       dev, ret);
	}
}

static void starfive_ltpi_data_write(int dev, u32 addr, u32 value)
{
	int ret;

	ret = starfive_ltpi_data_handler(dev, true, addr, value);
	if (ret) {
		printf("LTPI DATA WRITE failed for dev %d (err=%d)\n",
		       dev, ret);
	}
}

static void starfive_ltpi_uart_config(int dev, u8 mask)
{
	int ret;

	ret = starfive_ltpi_uart_handler(dev, mask);
	if (ret) {
		printf("LTPI UART CONFIG failed for dev %d (err=%d)\n",
		       dev, ret);
	}
}

static void starfive_ltpi_i2c_config(int dev, u8 mask, u32 speed)
{
	int ret;

	ret = starfive_ltpi_i2c_handler(dev, mask, speed);
	if (ret) {
		printf("LTPI I2C CONFIG failed for dev %d (err=%d)\n",
		       dev, ret);
	}
}

static int do_ltpi(struct cmd_tbl *cmdtp, int flag,
		   int argc, char *const argv[])
{
	int dev, pin_start, pin_range;
	u32 addr, val, speed;
	u8 mask;
	bool output_high = false;
	bool is_input = false;

	if (argc < 3)
		return CMD_RET_USAGE;

	/* ---------------- GPIO ---------------- */
	if (!strcmp(argv[1], "gpio")) {
		if (argc != 7)
			return CMD_RET_USAGE;

		dev = simple_strtoul(argv[3], NULL, 0);
		pin_start = simple_strtoul(argv[4], NULL, 0);
		pin_range = simple_strtoul(argv[5], NULL, 0);

		if (!strcmp(argv[6], "set"))
			output_high = true;
		else if (!strcmp(argv[6], "clear"))
			output_high = false;
		else if (!strcmp(argv[6], "input"))
			is_input = true;
		else
			return CMD_RET_USAGE;

		if (!strcmp(argv[2], "nl")) {
			starfive_ltpi_gpio_nl(dev, pin_start, pin_range, output_high, is_input);
			return CMD_RET_SUCCESS;
		}

		if (!strcmp(argv[2], "ll")) {
			starfive_ltpi_gpio_ll(dev, pin_start, pin_range, output_high, is_input);
			return CMD_RET_SUCCESS;
		}

		return CMD_RET_USAGE;
	}

	/* ---------------- DATA ---------------- */
	if (!strcmp(argv[1], "data")) {
		if (!strcmp(argv[2], "read")) {
			if (argc != 5)
				return CMD_RET_USAGE;

			dev = simple_strtoul(argv[3], NULL, 0);
			addr = simple_strtoul(argv[4], NULL, 0);

			starfive_ltpi_data_read(dev, addr);
			return CMD_RET_SUCCESS;
		}

		if (!strcmp(argv[2], "write")) {
			if (argc != 6)
				return CMD_RET_USAGE;

			dev = simple_strtoul(argv[3], NULL, 0);
			addr = simple_strtoul(argv[4], NULL, 0);
			val = simple_strtoul(argv[5], NULL, 0);

			starfive_ltpi_data_write(dev, addr, val);
			return CMD_RET_SUCCESS;
		}

		return CMD_RET_USAGE;
	}

	/* ---------------- UART ---------------- */
	if (!strcmp(argv[1], "uart")) {
		if (!strcmp(argv[2], "config")) {
			if (argc != 5)
				return CMD_RET_USAGE;

			dev = simple_strtoul(argv[3], NULL, 0);
			mask = (u8)simple_strtoul(argv[4], NULL, 0);

			if (mask > 3) {
				printf("Invalid UART mask %u\n", mask);
				return CMD_RET_USAGE;
			}

			starfive_ltpi_uart_config(dev, mask);
			return CMD_RET_SUCCESS;
		}

		return CMD_RET_USAGE;
	}

	/* ---------------- I2C ---------------- */
	if (!strcmp(argv[1], "i2c")) {
		if (!strcmp(argv[2], "config")) {
			if (argc != 6)
				return CMD_RET_USAGE;

			dev = simple_strtoul(argv[3], NULL, 0);
			mask = (u8)simple_strtoul(argv[4], NULL, 0);
			speed = simple_strtoul(argv[5], NULL, 0);

			if (mask > 63) {
				printf("Invalid I2C mask %u\n", mask);
				return CMD_RET_USAGE;
			}

			if (speed > 1) {
				printf("Invalid I2C speed %u\n", speed);
				return CMD_RET_USAGE;
			}

			starfive_ltpi_i2c_config(dev, mask, speed);
			return CMD_RET_SUCCESS;
		}

		return CMD_RET_USAGE;
	}

	return CMD_RET_USAGE;
}

U_BOOT_CMD(ltpi, CONFIG_SYS_MAXARGS, 1, do_ltpi,
	   "StarFive Diagnostic Tool for LTPI",
	   "gpio nl <dev> <pin_start> <pin_range> <set|clear|input>\n"
	   "    - configure LTPI GPIOs to Normal Latency mode\n"
	   "ltpi gpio ll <dev> <pin_start> <pin_range> <set|clear|input>\n"
	   "    - configure LTPI GPIOs to Low Latency mode\n"
	   "ltpi data read <dev> <addr>\n"
	   "    - read from LTPI data registers\n"
	   "ltpi data write <dev> <addr> <value>\n"
	   "    - write to LTPI data registers\n"
	   "ltpi uart config <dev> <mask>\n"
	   "    - configure LTPI UART capability mask\n"
	   "      mask: 0=off, 1=UART0, 2=UART1, 3=UART0+UART1\n"
	   "ltpi i2c config <dev> <mask> <speed>\n"
	   "    - configure LTPI I2C capability mask\n"
	   "      mask: bit0=I2C0, bit1=I2C1, ..., bit5=I2C5\n"
	   "            (0=disable all, 63=all buses)\n"
	   "      speed: 0=100kHz, 1=400kHz\n"
);
