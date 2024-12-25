// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2019 STMicroelectronics - All Rights Reserved
 * Author(s): Yannick Fertre <yannick.fertre@st.com> for STMicroelectronics.
 *            Philippe Cornu <philippe.cornu@st.com> for STMicroelectronics.
 *
 * This seeed panel driver is inspired from the Linux Kernel driver
 * drivers/gpu/drm/panel/panel-raydium-seeed.c.
 */
#include <common.h>
#include <backlight.h>
#include <dm.h>
#include <mipi_dsi.h>
#include <panel.h>
#include <asm/gpio.h>
#include <dm/device_compat.h>
#include <linux/delay.h>
#include <power/regulator.h>
#include <i2c.h>

/* I2C registers of the Atmel microcontroller. */
enum REG_ADDR {
	REG_ID = 0x80,
	REG_PORTA, /* BIT(2) for horizontal flip, BIT(3) for vertical flip */
	REG_PORTB,
	REG_PORTC,
	REG_PORTD,
	REG_POWERON,
	REG_PWM,
	REG_DDRA,
	REG_DDRB,
	REG_DDRC,
	REG_DDRD,
	REG_TEST,
	REG_WR_ADDRL,
	REG_WR_ADDRH,
	REG_READH,
	REG_READL,
	REG_WRITEH,
	REG_WRITEL,
	REG_ID2,
};

/* DSI D-PHY Layer Registers */
#define D0W_DPHYCONTTX 0x0004
#define CLW_DPHYCONTRX 0x0020
#define D0W_DPHYCONTRX 0x0024
#define D1W_DPHYCONTRX 0x0028
#define COM_DPHYCONTRX 0x0038
#define CLW_CNTRL 0x0040
#define D0W_CNTRL 0x0044
#define D1W_CNTRL 0x0048
#define DFTMODE_CNTRL 0x0054

/* DSI PPI Layer Registers */
#define PPI_STARTPPI 0x0104
#define PPI_BUSYPPI 0x0108
#define PPI_LINEINITCNT 0x0110
#define PPI_LPTXTIMECNT 0x0114
#define PPI_CLS_ATMR 0x0140
#define PPI_D0S_ATMR 0x0144
#define PPI_D1S_ATMR 0x0148
#define PPI_D0S_CLRSIPOCOUNT 0x0164
#define PPI_D1S_CLRSIPOCOUNT 0x0168
#define CLS_PRE 0x0180
#define D0S_PRE 0x0184
#define D1S_PRE 0x0188
#define CLS_PREP 0x01A0
#define D0S_PREP 0x01A4
#define D1S_PREP 0x01A8
#define CLS_ZERO 0x01C0
#define D0S_ZERO 0x01C4
#define D1S_ZERO 0x01C8
#define PPI_CLRFLG 0x01E0
#define PPI_CLRSIPO 0x01E4
#define HSTIMEOUT 0x01F0
#define HSTIMEOUTENABLE 0x01F4

/* DSI Protocol Layer Registers */
#define DSI_STARTDSI 0x0204
#define DSI_BUSYDSI 0x0208
#define DSI_LANEENABLE 0x0210
#define DSI_LANEENABLE_CLOCK BIT(0)
#define DSI_LANEENABLE_D0 BIT(1)
#define DSI_LANEENABLE_D1 BIT(2)

#define DSI_LANESTATUS0 0x0214
#define DSI_LANESTATUS1 0x0218
#define DSI_INTSTATUS 0x0220
#define DSI_INTMASK 0x0224
#define DSI_INTCLR 0x0228
#define DSI_LPTXTO 0x0230
#define DSI_MODE 0x0260
#define DSI_PAYLOAD0 0x0268
#define DSI_PAYLOAD1 0x026C
#define DSI_SHORTPKTDAT 0x0270
#define DSI_SHORTPKTREQ 0x0274
#define DSI_BTASTA 0x0278
#define DSI_BTACLR 0x027C

/* DSI General Registers */
#define DSIERRCNT 0x0300
#define DSISIGMOD 0x0304

/* DSI Application Layer Registers */
#define APLCTRL 0x0400
#define APLSTAT 0x0404
#define APLERR 0x0408
#define PWRMOD 0x040C
#define RDPKTLN 0x0410
#define PXLFMT 0x0414
#define MEMWRCMD 0x0418

/* LCDC/DPI Host Registers */
#define LCDCTRL 0x0420
#define HSR 0x0424
#define HDISPR 0x0428
#define VSR 0x042C
#define VDISPR 0x0430
#define VFUEN 0x0434

/* DBI-B Host Registers */
#define DBIBCTRL 0x0440

/* SPI Master Registers */
#define SPICMR 0x0450
#define SPITCR 0x0454

/* System Controller Registers */
#define SYSSTAT 0x0460
#define SYSCTRL 0x0464
#define SYSPLL1 0x0468
#define SYSPLL2 0x046C
#define SYSPLL3 0x0470
#define SYSPMCTRL 0x047C

/* GPIO Registers */
#define GPIOC 0x0480
#define GPIOO 0x0484
#define GPIOI 0x0488

/* I2C Registers */
#define I2CCLKCTRL 0x0490

/* Chip/Rev Registers */
#define IDREG 0x04A0

/* printf Registers */
#define WCMDQUEUE 0x0500
#define RCMDQUEUE 0x0504

enum cmd_type {
	CMD_TYPE_DCS,
	CMD_TYPE_DELAY,
};

struct jadard_init_cmd {
	enum cmd_type type;
	const char *data;
	size_t len;
};

#define _INIT_CMD_DCS(...)					\
	{							\
		.type	= CMD_TYPE_DCS,				\
		.data	= (char[]){__VA_ARGS__},		\
		.len	= sizeof((char[]){__VA_ARGS__})		\
	}							\

#define _INIT_CMD_DELAY(...)					\
	{							\
		.type	= CMD_TYPE_DELAY,			\
		.data	= (char[]){__VA_ARGS__},		\
		.len	= sizeof((char[]){__VA_ARGS__})		\
	}

static const struct jadard_init_cmd cz101b4001_init_cmds[] = {
	_INIT_CMD_DCS(0xE0,0xAB,0xBA),
	_INIT_CMD_DCS(0xE1,0xBA,0xAB),
	_INIT_CMD_DCS(0xB1,0x10,0x01,0x47,0xFF),
	_INIT_CMD_DCS(0xB2,0x0C,0x14,0x04,0x50,0x50,0x14),
	_INIT_CMD_DCS(0xB3,0x56,0x53,0x00),
	_INIT_CMD_DCS(0xB4,0x33,0x30,0x04),
	_INIT_CMD_DCS(0xB6,0xB0,0x00,0x00,0x10,0x00,0x10,0x00),
	_INIT_CMD_DCS(0xB8,0x05,0x12,0x29,0x49,0x48,0x00,0x00),
	_INIT_CMD_DCS(0xB9,0x7C,0x65,0x55,0x49,0x46,0x36,0x3B,0x24,0x3D,0x3C,0x3D,0x5C,0x4C,0x55,0x47,0x46,0x39,0x26,0x06,0x7C,0x65,0x55,0x49,0x46,0x36,0x3B,0x24,0x3D,0x3C,0x3D,0x5C,0x4C,0x55,0x47,0x46,0x39,0x26,0x06),
	_INIT_CMD_DCS(0xC0,0xFF,0x87,0x12,0x34,0x44,0x44,0x44,0x44,0x98,0x04,0x98,0x04,0x0F,0x00,0x00,0xC1),
	_INIT_CMD_DCS(0xC1,0x54,0x94,0x02,0x85,0x9F,0x00,0x7F,0x00,0x54,0x00),
	_INIT_CMD_DCS(0xC2,0x17,0x09,0x08,0x89,0x08,0x11,0x22,0x20,0x44,0xFF,0x18,0x00),
	_INIT_CMD_DCS(0xC3,0x86,0x46,0x05,0x05,0x1C,0x1C,0x1D,0x1D,0x02,0x1F,0x1F,0x1E,0x1E,0x0F,0x0F,0x0D,0x0D,0x13,0x13,0x11,0x11,0x00),
	_INIT_CMD_DCS(0xC4,0x07,0x07,0x04,0x04,0x1C,0x1C,0x1D,0x1D,0x02,0x1F,0x1F,0x1E,0x1E,0x0E,0x0E,0x0C,0x0C,0x12,0x12,0x10,0x10,0x00),
	_INIT_CMD_DCS(0xC6,0x2A,0x2A),
	_INIT_CMD_DCS(0xC8,0x21,0x00,0x31,0x42,0x34,0x16),
	_INIT_CMD_DCS(0xCA,0xCB,0x43),
	_INIT_CMD_DCS(0xCD,0x0E,0x4B,0x4B,0x20,0x19,0x6B,0x06,0xB3),
	_INIT_CMD_DCS(0xD2,0xE3,0x2B,0x38,0x00),
	_INIT_CMD_DCS(0xD4,0x00,0x01,0x00,0x0E,0x04,0x44,0x08,0x10,0x00,0x00,0x00),
	_INIT_CMD_DCS(0xE6,0x80,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF),
	_INIT_CMD_DCS(0xF0,0x12,0x03,0x20,0x00,0xFF),
	_INIT_CMD_DCS(0xF3,0x00),

	_INIT_CMD_DELAY(120),
};

#define msleep(a) udelay(a * 1000)

struct seeed_panel_priv {
	struct udevice *reg;
	struct udevice *backlight;
	struct gpio_desc *sel_gpio;   //select
	struct gpio_desc blen;
	struct gpio_desc enable;
};

static const struct display_timing default_timing = {
	.pixelclock.typ		= 66000000,
	.hactive.typ		= 800,
	.hfront_porch.typ	= 44,
	.hback_porch.typ	= 5,
	.hsync_len.typ		= 5,
	.vactive.typ		= 1280,
	.vfront_porch.typ	= 5,
	.vback_porch.typ	= 5,
	.vsync_len.typ		= 5,
};

static int seeed_panel_i2c_write(struct udevice *dev, uint addr, uint mask, uint data)
{
	uint8_t valb;
	int err = 0;

	if (mask != 0xff){
		err = dm_i2c_read(dev, addr, &valb, 1);
		if (err)
			return err;
	}
	valb &= ~mask;
	valb |= data;

	err = dm_i2c_write(dev, addr, &valb, 1);
	return err;
}

static int seeed_panel_i2c_read(struct udevice *dev, uint8_t addr, uint8_t *data)
{
	uint8_t valb;
	int err;

	err = dm_i2c_read(dev, addr, &valb, 1);
	if (err)
		return err;

	*data = (int)valb;
	return 0;
}

static void rpi_touchscreen_write(struct udevice *dev, u16 reg, u32 val)
{
	struct mipi_dsi_panel_plat *plat = dev_get_plat(dev);
	struct mipi_dsi_device *device = plat->device;
	int err;

    u8 msg[] = {
        reg,
        reg >> 8,
        val,
        val >> 8,
        val >> 16,
        val >> 24,
    };

	err = mipi_dsi_dcs_write_buffer(device, msg, sizeof(msg));
	if (err < 0)
		dev_err(dev, "MIPI DSI DCS write buffer failed: %d\n", err);

    return;
}

static int rm68200_panel_enable_backlight(struct udevice *dev)
{
	struct mipi_dsi_panel_plat *plat = dev_get_plat(dev);
	struct mipi_dsi_device *device = plat->device;
	int ret;
	int i;
	u8 reg_value = 0;
	u32 num_init_cmds;
	int err;

	num_init_cmds = ARRAY_SIZE(cz101b4001_init_cmds);

	ret = mipi_dsi_attach(device);
	if (ret < 0)
		return ret;

	for (i = 0; i < num_init_cmds; i++) {
		//const struct jadard_init_cmd *cmd = cz101b4001_init_cmds[i];
		switch (cz101b4001_init_cmds[i].type) {
		case CMD_TYPE_DELAY:
			msleep(cz101b4001_init_cmds[i].data[0]);
			err = 0;
			break;

		case CMD_TYPE_DCS:
			/*err = mipi_dsi_dcs_write(dsi, cmd->data[0],
						 cmd->len <= 1 ? NULL : &cmd->data[1],
						 cmd->len - 1);
			*/
			err = mipi_dsi_dcs_write_buffer(device, cz101b4001_init_cmds[i].data, cz101b4001_init_cmds[i].len);
			break;
		default:
			err = -EINVAL;
		}

		if (err < 0) {
			printf("failed to write CMD#0x%x\n", cz101b4001_init_cmds[i].data[0]);
			return err;
		}
	}

	err = mipi_dsi_dcs_exit_sleep_mode(device);
	if (err < 0)
		printf("failed to exit sleep mode ret = %d\n", err);
	msleep(120);

	err =  mipi_dsi_dcs_set_display_on(device);
	if (err < 0)
		printf(dev, "failed to set display on ret = %d\n", err);

	return 0;
}

static int rm68200_panel_get_display_timing(struct udevice *dev,
					    struct display_timing *timings)
{
	memcpy(timings, &default_timing, sizeof(*timings));
	return 0;
}

static int rm68200_panel_of_to_plat(struct udevice *dev)
{
	return 0;
}

static int rm68200_panel_probe(struct udevice *dev)
{
	struct mipi_dsi_panel_plat *plat = dev_get_plat(dev);
	struct seeed_panel_priv *priv = dev_get_priv(dev);
	int ret;

	printf("%s,-----------\n", __func__);

	u8 reg_value = 0;

	/* fill characteristics of DSI data link */
	plat->lanes = 4;
	plat->format = MIPI_DSI_FMT_RGB888;
	plat->mode_flags = MIPI_DSI_MODE_VIDEO |
			   MIPI_DSI_MODE_VIDEO_BURST |
			   MIPI_DSI_MODE_LPM;

	return 0;
}

static const struct panel_ops rm68200_panel_ops = {
	.enable_backlight = rm68200_panel_enable_backlight,
	.get_display_timing = rm68200_panel_get_display_timing,
};

static const struct udevice_id rm68200_panel_ids[] = {
	{ .compatible = "starfive,seeed" },
	{ }
};

U_BOOT_DRIVER(seeed_panel) = {
	.name			  = "seeed_panel",
	.id			  = UCLASS_PANEL,
	.of_match		  = rm68200_panel_ids,
	.ops			  = &rm68200_panel_ops,
	.of_to_plat	  = rm68200_panel_of_to_plat,
	.probe			  = rm68200_panel_probe,
	.plat_auto	= sizeof(struct mipi_dsi_panel_plat),
	.priv_auto	= sizeof(struct seeed_panel_priv),
};
