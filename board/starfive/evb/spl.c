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

/* set PLL0 output to 1.5GHz*/
__maybe_unused static void spl_cpu_fre_150(void)
{
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_24, PLL0_DACPD_MASK,
		BIT(PLL0_DACPD_SHIFT) & PLL0_DACPD_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_24, PLL0_DSMPD_MASK,
		BIT(PLL0_DSMPD_SHIFT) & PLL0_DSMPD_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_36, PLL0_PREDIV_MASK,
		BIT(PLL0_PREDIV_SHIFT) & PLL0_PREDIV_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_28, PLL0_FBDIV_MASK,
		(125 << PLL0_FBDIV_SHIFT) & PLL0_FBDIV_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_32, PLL0_POSTDIV1_MASK,
		BIT(PLL0_POSTDIV1_SHIFT) & PLL0_POSTDIV1_MASK);
}

/* set PLL0 output to 1.25GHz*/
static void spl_cpu_fre_125(void)
{
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_24, PLL0_DACPD_MASK,
		BIT(PLL0_DACPD_SHIFT) & PLL0_DACPD_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_24, PLL0_DSMPD_MASK,
		BIT(PLL0_DSMPD_SHIFT) & PLL0_DSMPD_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_36, PLL0_PREDIV_MASK,
		BIT(PLL0_PREDIV_SHIFT) & PLL0_PREDIV_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_28, PLL0_FBDIV_MASK,
		(52 << PLL0_FBDIV_SHIFT) & PLL0_FBDIV_MASK);
	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_32, PLL0_POSTDIV1_MASK,
		(0 << PLL0_POSTDIV1_SHIFT) & PLL0_POSTDIV1_MASK);
}


void board_init_f(ulong dummy)
{
	int ret;

	spl_cpu_fre_125();

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

	clrsetbits_le32(SYS_CRG_BASE + CLK_SDIO_SOURCEMUX_OFFSET,
	CLK_SDIO_SCLK_SW_MASK,
	(0 << CLK_SDIO_SCLK_SW_SHIFT) & CLK_SDIO_SCLK_SW_MASK);

	/*set GPIO to 1.8v*/
	setbits_le32(SYS_SYSCON_BASE + 0xC, 0xf);

	/* reset emmc */
	SYS_IOMUX_DOEN(22, LOW);
	SYS_IOMUX_DOUT(22, 19);
	/* reset sdio */
	SYS_IOMUX_DOEN(24, LOW);
	SYS_IOMUX_DOUT(24, 66);

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


