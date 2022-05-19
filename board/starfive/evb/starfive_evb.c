// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 Starfive, Inc.
 * Author:	yanhong <yanhong.wang@starfivetech.com>
 *
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/jh7110-regs.h>
#include <cpu_func.h>
#include <dm/uclass.h>
#include <dm/device.h>
#include <env.h>
#include <inttypes.h>
#include <misc.h>
#include <linux/bitops.h>
#include <asm/arch/gpio.h>

#define SYS_CLOCK_ENABLE(clk) \
	setbits_le32(SYS_CRG_BASE + clk, CLK_ENABLE_MASK)

static void sys_reset_clear(ulong assert, ulong status, u32 rst)
{
	u32 value;

	clrbits_le32(SYS_CRG_BASE + assert, BIT(rst));
	do {
		value = in_le32(SYS_CRG_BASE + status);
	} while ((value & BIT(rst)) != BIT(rst));
}

static void jh7110_timer_init(void)
{
	SYS_CLOCK_ENABLE(TIMER_CLK_APB_SHIFT);
	SYS_CLOCK_ENABLE(TIMER_CLK_TIMER0_SHIFT);
	SYS_CLOCK_ENABLE(TIMER_CLK_TIMER1_SHIFT);
	SYS_CLOCK_ENABLE(TIMER_CLK_TIMER2_SHIFT);
	SYS_CLOCK_ENABLE(TIMER_CLK_TIMER3_SHIFT);

	sys_reset_clear(SYS_CRG_RESET_ASSERT3_SHIFT,
			SYS_CRG_RESET_STATUS3_SHIFT, TIMER_RSTN_APB_SHIFT);
	sys_reset_clear(SYS_CRG_RESET_ASSERT3_SHIFT,
			SYS_CRG_RESET_STATUS3_SHIFT, TIMER_RSTN_TIMER0_SHIFT);
	sys_reset_clear(SYS_CRG_RESET_ASSERT3_SHIFT,
			SYS_CRG_RESET_STATUS3_SHIFT, TIMER_RSTN_TIMER1_SHIFT);
	sys_reset_clear(SYS_CRG_RESET_ASSERT3_SHIFT,
			SYS_CRG_RESET_STATUS3_SHIFT, TIMER_RSTN_TIMER2_SHIFT);
	sys_reset_clear(SYS_CRG_RESET_ASSERT3_SHIFT,
			SYS_CRG_RESET_STATUS3_SHIFT, TIMER_RSTN_TIMER3_SHIFT);
}

static void jh7110_gmac_init(int id)
{
	switch (id) {
	case 0:
		clrsetbits_le32(AON_SYSCON_BASE + AON_SYSCFG_12,
			GMAC5_0_SEL_I_MASK,
			BIT(GMAC5_0_SEL_I_SHIFT) & GMAC5_0_SEL_I_MASK);
		break;

	case 1:
		clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_144,
			GMAC5_1_SEL_I_MASK,
			BIT(GMAC5_1_SEL_I_SHIFT) & GMAC5_1_SEL_I_MASK);
		break;

	default:
		break;
	}
}

static void jh7110_usb_init(void)
{
	clrsetbits_le32(STG_SYSCON_BASE  + STG_SYSCON_4,
		USB_MODE_STRAP_MASK,
		(2<<USB_MODE_STRAP_SHIFT) & USB_MODE_STRAP_MASK);
	clrsetbits_le32(STG_SYSCON_BASE + STG_SYSCON_4,
		USB_OTG_SUSPENDM_BYPS_MASK,
		BIT(USB_OTG_SUSPENDM_BYPS_SHIFT)
		& USB_OTG_SUSPENDM_BYPS_MASK);

	clrsetbits_le32(STG_SYSCON_BASE + STG_SYSCON_4,
		USB_OTG_SUSPENDM_MASK,
		BIT(USB_OTG_SUSPENDM_SHIFT) & USB_OTG_SUSPENDM_MASK);
	clrsetbits_le32(STG_SYSCON_BASE + STG_SYSCON_4,
		USB_PLL_EN_MASK,
		BIT(USB_PLL_EN_SHIFT) & USB_PLL_EN_MASK);
	clrsetbits_le32(STG_SYSCON_BASE + STG_SYSCON_4,
		USB_REFCLK_MODE_MASK,
		BIT(USB_REFCLK_MODE_SHIFT) & USB_REFCLK_MODE_MASK);

	clrsetbits_le32(SYS_SYSCON_BASE + SYS_SYSCON_24,
		PDRSTN_SPLIT_MASK,
		BIT(PDRSTN_SPLIT_SHIFT) & PDRSTN_SPLIT_MASK);
	clrsetbits_le32(SYS_IOMUX_BASE + SYS_IOMUX_32,
		IOMUX_USB_MASK,
		BIT(IOMUX_USB_SHIFT) & IOMUX_USB_MASK);
}

static void jh7110_mmc_init(int id)
{
	if (id == 0) {
		SYS_IOMUX_DOEN(22, LOW);
		SYS_IOMUX_DOUT(22, 19);
	} else {
		SYS_IOMUX_DOEN(24, LOW);
		SYS_IOMUX_DOUT(24, 66);
	}
}

/*enable U74-mc hart1~hart4 prefetcher*/
static void enable_prefetcher(void)
{
	u32 hart;
	u32 *reg;
#define L2_PREFETCHER_BASE_ADDR	0x2030000
#define L2_PREFETCHER_OFFSET	0x2000

	/*hart1~hart4*/
	for (hart = 1; hart < 5; hart++) {
		reg = (u32 *)((u64)(L2_PREFETCHER_BASE_ADDR
			+ hart*L2_PREFETCHER_OFFSET));

		mb(); /* memory barrier */
		setbits_le32(reg, 0x1);
		mb(); /* memory barrier */
	}
}

int board_init(void)
{
	enable_caches();

	/*enable hart1-hart4 prefetcher*/
	enable_prefetcher();

	jh7110_gmac_init(0);
	jh7110_gmac_init(1);
	jh7110_timer_init();

	jh7110_usb_init();

	jh7110_mmc_init(0);
	jh7110_mmc_init(1);

	return 0;
}

#ifdef CONFIG_MISC_INIT_R

int misc_init_r(void)
{
	char mac0[6] = {0x66, 0x34, 0xb0, 0x6c, 0xde, 0xad};
	char mac1[6] = {0x66, 0x34, 0xb0, 0x7c, 0xae, 0x5d};

#if CONFIG_IS_ENABLED(STARFIVE_OTP)
	struct udevice *dev;
	char buf[16];
	int ret;
#define MACADDR_OFFSET 0x8

	ret = uclass_get_device_by_driver(UCLASS_MISC,
				DM_DRIVER_GET(starfive_otp), &dev);
	if (ret) {
		debug("%s: could not find otp device\n", __func__);
		goto err;
	}

	ret = misc_read(dev, MACADDR_OFFSET, buf, sizeof(buf));
	if (ret)
		printf("%s: error reading mac from OTP\n", __func__);
	else
		if (buf[0] != 0xff) {
			memcpy(mac0, buf, 6);
			memcpy(mac1, &buf[8], 6);
		}
err:
#endif
	eth_env_set_enetaddr("eth0addr", mac0);
	eth_env_set_enetaddr("eth1addr", mac1);

	return 0;
}
#endif

