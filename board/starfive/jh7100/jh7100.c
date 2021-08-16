// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Shanghai StarFive Technology Co., Ltd.
 * Micheal Zhu <michael.zhu@starfivetech.com>
 */

#include <common.h>
#include <cpu_func.h>
#include <env.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <dm.h>
#include <misc.h>
#include <inttypes.h>
#include <netdev.h>
#include <phy_interface.h>
#include <flash.h>
#include <asm/arch/cache.h>

DECLARE_GLOBAL_DATA_PTR;

struct sifive_gpio_regs
{
	volatile uint32_t  INPUT_VAL;   /* 0x0000 */
	volatile uint32_t  INPUT_EN;    /* 0x0004 */
	volatile uint32_t  OUTPUT_VAL;  /* 0x0008 */
	volatile uint32_t  OUTPUT_EN;   /* 0x000C */
	volatile uint32_t  PUE;         /* 0x0010 */
	volatile uint32_t  DS;          /* 0x0014 */
	volatile uint32_t  RISE_IE;     /* 0x0018 */
	volatile uint32_t  RISE_IP;     /* 0x001C */
	volatile uint32_t  FALL_IE;     /* 0x0020 */
	volatile uint32_t  FALL_IP;     /* 0x0024 */
	volatile uint32_t  HIGH_IE;     /* 0x0028 */
	volatile uint32_t  HIGH_IP;     /* 0x002C */
	volatile uint32_t  LOW_IE;      /* 0x0030 */
	volatile uint32_t  LOW_IP;      /* 0x0034 */
	volatile uint32_t  reserved0;   /* 0x0038 */
	volatile uint32_t  reserved1;   /* 0x003C */
	volatile uint32_t  OUT_XOR;     /* 0x0040 */
};

#define SIFIVE_BASE_GPIO		0x10060000
struct sifive_gpio_regs *g_aloe_gpio = (struct sifive_gpio_regs *) SIFIVE_BASE_GPIO;

/*
 * Init includes toggling the reset line which is connected to GPIO 0 pin 12.
 * This is the only pin I can see on the 16 GPIO which is currently set as an.
 * output. We will hard code the setup here to avoid having to have a GPIO
 * driver as well...
 *
 * The Aloe board is strapped for unmanaged mode and needs two pulses of the
 * reset line to configure the device properly.
 *
 * The RX_CLK, TX_CLK and RXD7 pins are strapped high and the remainder low.
 * This selects GMII mode with auto 10/100/1000 and 125MHz clkout.
 */
void reset_phy(void)
{
	g_aloe_gpio->OUTPUT_EN  |= 0x00001000ul;  /* Configure pin 12 as an output */

#define PHY_RST_LOOPS	2

	for (int i = 0; i < PHY_RST_LOOPS; i++) {
		g_aloe_gpio->OUTPUT_VAL &= 0x0000EFFFul;  /* Clear pin 12 to reset PHY */
		udelay(1000);
		g_aloe_gpio->OUTPUT_VAL  |= 0x00001000ul; /* Take PHY^ out of reset */
		udelay(1000);
	}

	/* Need at least 15mS delay before accessing PHY after reset... */
	udelay(15000);
}

/* This define is a value used for error/unknown serial. If we really care about distinguishing errors and 0 is valid, we'll need a different one. */
#define ERROR_READING_SERIAL_NUMBER		0

#if CONFIG_IS_ENABLED(MISC_INIT_R)

#if CONFIG_IS_ENABLED(STARFIVE_OTP)
static u32 otp_read_mac(struct udevice *dev, unsigned char *buf)
 {
	u32 serial[2] = {0};
	int ret = misc_read(dev, STARFIVE_OTP_MAC_OFFSET,
			    serial, sizeof(serial));
	if (ret != sizeof(serial)) {
		printf("%s: error reading mac from OTP\n", __func__);
		return ERROR_READING_SERIAL_NUMBER;
	}

	buf[3] = (serial[0] >> 24) & 0xff;
	buf[2] = (serial[0] >> 16) & 0xff;
	buf[1] = (serial[0] >> 8) & 0xff;
	buf[0] = serial[0] & 0xff;

	buf[5] = (serial[1] >> 8) & 0xff;
	buf[4] = serial[1] & 0xff;

	return ret;
}

static u32 otp_read_serialnum(struct udevice *dev)
{
	u32 serial[2] = {0};
	int ret = misc_read(dev, STARFIVE_OTP_MAC_OFFSET-8,
			    serial, sizeof(serial));
	if (ret != sizeof(serial)) {
		printf("%s: error reading serial from OTP\n", __func__);
		return ERROR_READING_SERIAL_NUMBER;
	}

	if (serial[0] == ~serial[1])
		return serial[0];

	return ERROR_READING_SERIAL_NUMBER;
}
#endif

static u32 jh_read_serialnum(void)
{
	u32 serial = ERROR_READING_SERIAL_NUMBER;
#if CONFIG_IS_ENABLED(STARFIVE_OTP)
	struct udevice *dev;
	char buf[9] = {0};

	if (uclass_get_device_by_driver(UCLASS_MISC,
					DM_DRIVER_GET(starfive_otp), &dev)) {
		debug("%s: could not find otp device\n", __func__);
		return ERROR_READING_SERIAL_NUMBER;
	}

	// read serial from OTP and set env var
	serial = otp_read_serialnum(dev);
	snprintf(buf, sizeof(buf), "%08x", serial);
	env_set("serial#", buf);
#endif

	return serial;
}

static void jh_setup_macaddr(u32 serialnum)
{
#if CONFIG_IS_ENABLED(STARFIVE_OTP)
	struct udevice *dev;
	unsigned char mac[6]={0};

	// init OTP
	if (uclass_get_device_by_driver(UCLASS_MISC,
					DM_DRIVER_GET(starfive_otp), &dev)) {
		debug("%s: could not find otp device\n", __func__);
		return;
	}

	otp_read_mac(dev, mac);
#else
	unsigned char mac[6] = {0x66, 0x34, 0xb0, 0x6c, 0xde, 0xad};
	mac[5] |= (serialnum >>  0) & 0xff;
	mac[4] |= (serialnum >>  8) & 0xff;
	mac[3] |= (serialnum >> 16) & 0xff;
#endif
	eth_env_set_enetaddr("ethaddr", mac);
}

int misc_init_r(void)
{
	if (!env_get("serial#")) {
		u32 serialnum = jh_read_serialnum();
		jh_setup_macaddr(serialnum);
	}
	return 0;
}
#endif

#if CONFIG_IS_ENABLED(CMD_NET)
int board_eth_init(struct bd_info *bis)
{
	int ret = 0;

#if CONFIG_IS_ENABLED(ETH_DESIGNWARE)
#define SIFIVE_BASE_ETHERNET		0x10020000	//GMAC
	u32 interface = PHY_INTERFACE_MODE_RGMII_TXID;
	if (designware_initialize(SIFIVE_BASE_ETHERNET, interface) >= 0)
		ret++;
#endif
	return ret;
}
#endif

/*
 * Miscellaneous platform dependent initializations
 */

int board_init(void)
{
	int ret = 0;

	gd->bd->bi_boot_params = (CONFIG_SYS_SDRAM_BASE + 0x100);

	/* enable all cache ways */
	enable_caches();

	return ret;
}