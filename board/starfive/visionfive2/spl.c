// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 Starfive, Inc.
 * Author:	yanhong <yanhong.wang@starfivetech.com>
 *
 */

#include <common.h>
#include <init.h>
#include <asm/arch/spl.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/arch/jh7110-regs.h>
#include <image.h>
#include <linux/bitops.h>
#include <log.h>
#include <linux/delay.h>
#include <spl.h>

#define MODE_SELECT_REG		0x1702002c

struct starfive_pll0_freq {
	u32 freq;
	u32 prediv;
	u32 fbdiv;
	u32 postdiv1;
	u32 dacpd; /* Both daxpd and dsmpd set 1 while integer multiple mode */
	u32 dsmpd; /* Both daxpd and dsmpd set 0 while fraction multiple mode */
};

enum starfive_cpu_freq {
	CPU_FREQ_375 = 0,
	CPU_FREQ_500,
	CPU_FREQ_625,
	CPU_FREQ_750,
	CPU_FREQ_875,
	CPU_FREQ_1000,
	CPU_FREQ_1250,
	CPU_FREQ_1375,
	CPU_FREQ_1500,
	CPU_FREQ_1625,
	CPU_FREQ_1750,
	CPU_FREQ_1800,
	CPU_FREQ_MAX = CPU_FREQ_1800
};

struct starfive_pll0_freq jh7110_pll0_freq[] = {
	{
		.freq = CPU_FREQ_375,
		.prediv = 8,
		.fbdiv = 125,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_500,
		.prediv = 6,
		.fbdiv = 125,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_625,
		.prediv = 24,
		.fbdiv = 625,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_750,
		.prediv = 4,
		.fbdiv = 125,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_875,
		.prediv = 24,
		.fbdiv = 875,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_1000,
		.prediv = 3,
		.fbdiv = 125,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_1250,
		.prediv = 12,
		.fbdiv = 625,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_1375,
		.prediv = 24,
		.fbdiv = 1375,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_1500,
		.prediv = 2,
		.fbdiv = 125,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_1625,
		.prediv = 24,
		.fbdiv = 1625,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_1750,
		.prediv = 12,
		.fbdiv = 875,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
	{
		.freq = CPU_FREQ_1800,
		.prediv = 3,
		.fbdiv = 225,
		.postdiv1 = 1,
		.dacpd = 1,
		.dsmpd = 1
	},
};

int spl_board_init_f(void)
{
	int ret;

	ret = spl_soc_init();
	if (ret) {
		debug("JH7110 SPL init failed: %d\n", ret);
		return ret;
	}

	return 0;
}

u32 spl_boot_device(void)
{
	int boot_mode = 0;

	boot_mode = readl((const volatile void *)MODE_SELECT_REG) & 0x3;
	switch (boot_mode) {
	case 0:
		return BOOT_DEVICE_SPI;
	case 1:
		return BOOT_DEVICE_MMC2;
	case 2:
		return BOOT_DEVICE_MMC1;
	case 3:
		return BOOT_DEVICE_UART;
	default:
		debug("Unsupported boot device 0x%x.\n",
		      boot_mode);
		return BOOT_DEVICE_NONE;
	}
}

struct image_header *spl_get_load_buffer(ssize_t offset, size_t size)
{
	return (struct image_header *)(STARFIVE_SPL_BOOT_LOAD_ADDR);
}

static int spl_cpu_set_rate(enum starfive_cpu_freq rate)
{
	struct starfive_pll0_freq *cpu_freq;
	int i;

	if (rate < 0 || rate > CPU_FREQ_MAX) {
		debug("invalid input value=%d\n", rate);
		return -EINVAL;
	}

	for (i = 0; i<CPU_FREQ_MAX; i++) {
		if (jh7110_pll0_freq[i].freq == rate) {
			cpu_freq = &jh7110_pll0_freq[i];
			break;
		}
	}

	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_24, PLL0_DACPD_MASK,
		(cpu_freq->dacpd << PLL0_DACPD_SHIFT) & PLL0_DACPD_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_24, PLL0_DSMPD_MASK,
		(cpu_freq->dsmpd << PLL0_DSMPD_SHIFT) & PLL0_DSMPD_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_36, PLL0_PREDIV_MASK,
		(cpu_freq->prediv << PLL0_PREDIV_SHIFT) & PLL0_PREDIV_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_28, PLL0_FBDIV_MASK,
		(cpu_freq->fbdiv << PLL0_FBDIV_SHIFT) & PLL0_FBDIV_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_32, PLL0_POSTDIV1_MASK,
		((cpu_freq->postdiv1 >> 1) << PLL0_POSTDIV1_SHIFT) & PLL0_POSTDIV1_MASK);
	return 0;
}

void board_init_f(ulong dummy)
{
	int ret;

	/* Adjust cpu frequency, the default is 1.25GHz */
	spl_cpu_set_rate(CPU_FREQ_1250);

	/*DDR control depend clk init*/
	clrsetbits_le32(SYS_CRG_BASE, CLK_CPU_ROOT_SW_MASK,
		BIT(CLK_CPU_ROOT_SW_SHIFT) & CLK_CPU_ROOT_SW_MASK);

	clrsetbits_le32(SYS_CRG_BASE + CLK_BUS_ROOT_OFFSET,
		CLK_BUS_ROOT_SW_MASK,
		BIT(CLK_BUS_ROOT_SW_SHIFT) & CLK_BUS_ROOT_SW_MASK);

	clrsetbits_le32(SYS_CRG_BASE + CLK_NOC_BUS_STG_AXI_OFFSET,
		CLK_NOC_BUS_STG_AXI_EN_MASK,
		BIT(CLK_NOC_BUS_STG_AXI_EN_SHIFT)
		& CLK_NOC_BUS_STG_AXI_EN_MASK);

	clrsetbits_le32(AON_CRG_BASE + CLK_AON_APB_FUNC_OFFSET,
		CLK_AON_APB_FUNC_SW_MASK,
		BIT(CLK_AON_APB_FUNC_SW_SHIFT) & CLK_AON_APB_FUNC_SW_MASK);

	clrsetbits_le32(SYS_CRG_BASE + CLK_QSPI_REF_OFFSET,
		CLK_QSPI_REF_SW_MASK,
		(0 << CLK_QSPI_REF_SW_SHIFT) & CLK_QSPI_REF_SW_MASK);

	/*set GPIO to 3.3v*/
	setbits_le32(SYS_SYSCON_BASE + 0xC, 0x0);

	/*uart0 tx*/
	SYS_IOMUX_DOEN(41, LOW);
	SYS_IOMUX_DOUT(41, 20);
	/*uart0 rx*/
	SYS_IOMUX_DOEN(40, HIGH);
	SYS_IOMUX_DIN(40, 14);

	/*jtag*/
	SYS_IOMUX_DOEN(36, HIGH);
	SYS_IOMUX_DIN(36, 4);
	SYS_IOMUX_DOEN(61, HIGH);
	SYS_IOMUX_DIN(61, 19);
	SYS_IOMUX_DOEN(63, HIGH);
	SYS_IOMUX_DIN(63, 20);
	SYS_IOMUX_DOEN(60, HIGH);
	SYS_IOMUX_DIN(60, 29);
	SYS_IOMUX_DOEN(44, 8);
	SYS_IOMUX_DOUT(44, 22);

	/*set sdio0 sdcard clk default div to 4*/
	clrsetbits_le32(SYS_CRG_BASE + CLK_SDIO0_SDCARD_OFFSET,
		CLK_SDIO0_SDCARD_MASK,
		(4 << CLK_SDIO0_SDCARD_SHIFT) & CLK_SDIO0_SDCARD_MASK);

	/* reset emmc */
	SYS_IOMUX_DOEN(22, LOW);
	SYS_IOMUX_DOUT(22, 19);
	/* reset sdio */
	SYS_IOMUX_DOEN(4, LOW);
	SYS_IOMUX_DOUT(4, 55);
	SYS_IOMUX_COMPLEX(5, 44, 57, 19);
	SYS_IOMUX_COMPLEX(0, 45, 58, 20);
	SYS_IOMUX_COMPLEX(1, 46, 59, 21);
	SYS_IOMUX_COMPLEX(2, 47, 60, 22);
	SYS_IOMUX_COMPLEX(3, 48, 61, 23);

	ret = spl_early_init();
	if (ret)
		panic("spl_early_init() failed: %d\n", ret);

	arch_cpu_init_dm();

	preloader_console_init();

	ret = spl_board_init_f();
	if (ret) {
		debug("spl_board_init_f init failed: %d\n", ret);
		return;
	}
}

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
	/* boot using first FIT config */
	return 0;
}
#endif


