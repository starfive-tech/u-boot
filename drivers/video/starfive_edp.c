// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2019 STMicroelectronics - All Rights Reserved
 * Author(s): Yannick Fertre <yannick.fertre@st.com> for STMicroelectronics.
 *            Philippe Cornu <philippe.cornu@st.com> for STMicroelectronics.
 *
 * This edp panel driver is inspired from the Linux Kernel driver
 * drivers/gpu/drm/panel/panel-raydium-edp.c.
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
#include <asm/arch/gpio.h>
#include <asm/arch/jh7110-regs.h>
#include <asm/io.h>


#define	UART_DEBUG
#define TEST_EDID // read eDP panel EDID
#define EDP_2G7
#define LINK_TRAIN_ENABLE
#define LT8911EXB_RST_PIN GPIO41
#define BOE_14INCH_MAX_LANES 4

#define _1080P_eDP_Panel_
#define _MIPI_Lane_ 4   // 3 /2 / 1
#define _MIPI_data_PN_Swap_En	0xF0
#define _MIPI_data_PN_Swap_Dis	0x00
#define _MIPI_data_PN_ _MIPI_data_PN_Swap_Dis

#define	NO_SWAP				0x00    // 3210 default
#define MIPI_DATA_3210		0       // default
#define MIPI_DATA_0123		21
#define MIPI_DATA_2103		20

#define MIPI_DATA_SEQ 		NO_SWAP

#define _Nvid 0         // 0: 0x0080,default
static int Nvid_Val[] = { 0x0080, 0x0800 };
#define usleep_range(a, b) udelay((b))

#ifdef _1080P_eDP_Panel_

#define eDP_lane		2
#define PCR_PLL_PREDIV	0x40

static int MIPI_Timing[] =
{ 88, 	44, 148, 	1920, 	2200, 	4, 		5, 	36, 	1080, 	1125, 		14850 };   // VESA


//#define _6bit_ // eDP panel Color Depth，262K color
#define _8bit_                                              // eDP panel Color Depth，16.7M color

#endif

enum {
	hfp = 0,
	hs,
	hbp,
	hact,
	htotal,
	vfp,
	vs,
	vbp,
	vact,
	vtotal,
	pclk_10khz
};

u8		Read_DPCD010A = 0x00;
bool	ScrambleMode = 0;
bool	flag_mipi_on = 0;
#ifdef TEST_EDID // read eDP panel EDID
u8		EDID_DATA[128] = { 0 };
u16		EDID_Timing[11] = { 0 };
bool	EDID_Reply = 0;
#endif

static inline void sys_modl(void *addr, uint32_t mask, uint32_t val)
{
	uint32_t tmp;

	tmp = readl(addr);
	tmp &= ~mask;
	tmp |= (val & mask);

	debug("tmp 0x%x\n", tmp);
	writel(tmp, addr);
}

struct edp_panel_priv {
	struct udevice *reg;
	struct udevice *backlight;

	struct gpio_desc *reset_gpio;   //reset
	struct gpio_desc *pwm_gpio;  	//power
	struct gpio_desc *bl_gpio;  	//backlight
};

static const struct display_timing default_timing = {
	.pixelclock.typ		= 148500000,
	.hactive.typ		= 1920,
	.hfront_porch.typ	= 88,
	.hback_porch.typ	= 148,
	.hsync_len.typ		= 44,
	.vactive.typ		= 1080,
	.vfront_porch.typ	= 34,
	.vback_porch.typ	= 6,
	.vsync_len.typ		= 5,
};

static int edp_panel_i2c_write(struct udevice *dev, uint addr, uint8_t data)
{
	uint8_t valb;
	int err;
	valb = data;

	err = dm_i2c_write(dev, addr, &valb, 1);
	return err;
}

static int edp_panel_i2c_read(struct udevice *dev, uint8_t addr, uint8_t *data)
{
	uint8_t valb;
	int err;

	err = dm_i2c_read(dev, addr, &valb, 1);
	if (err)
		return err;

	*data = (int)valb;
	return 0;
}

static u8 LT8911EXB_IIC_Read_byte(struct udevice *dev, u8 reg)
{
	uint8_t valb;
	int err;

	err = dm_i2c_read(dev, reg, &valb, 1);
	if (err)
		return err;
	udelay(10);

	return (int)valb;

}

static void LT8911EXB_IIC_Write_byte(struct udevice *dev,u8 reg, u8 val)
{
	dm_i2c_write(dev, reg, &val, 1);
	udelay(10);
}

u8 boe_i2c_read(struct udevice *dev,u8 reg){
	return LT8911EXB_IIC_Read_byte(dev,reg);
}

void boe_i2c_write(struct udevice *dev,u8 reg, u8 val){
	LT8911EXB_IIC_Write_byte(dev,reg,val);
}

void Reset_LT8911EXB(struct udevice *dev)
{
	struct edp_panel_priv *priv = dev_get_priv(dev);

	dm_gpio_set_value(priv->pwm_gpio, 0);
	dm_gpio_set_value(priv->bl_gpio, 0);

	dm_gpio_set_value(priv->reset_gpio, 0);

}

void LT8911EX_ChipID(struct udevice *dev)                                         
{
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );
	LT8911EXB_IIC_Write_byte(dev, 0x08, 0x7f );

#ifdef UART_DEBUG
	debug( "\r\nLT8911EXB chip ID: 0x%x", LT8911EXB_IIC_Read_byte(dev, 0x00 ) );
	debug( ",0x%x", LT8911EXB_IIC_Read_byte(dev, 0x01 ) );
	debug( ",0x%x", LT8911EXB_IIC_Read_byte(dev, 0x02 ) );
#endif
}

void LT8911EXB_read_edid(struct udevice *dev)
{
#ifdef TEST_EDID
	u8 reg, i, j;
//	bool	aux_reply, aux_ack, aux_nack, aux_defer;
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
	LT8911EXB_IIC_Write_byte(dev, 0x00, 0x20 ); //Soft Link train
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa6 );
	LT8911EXB_IIC_Write_byte(dev, 0x2a, 0x01 );

	/*set edid offset addr*/
	LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x40 ); //CMD
	LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x00 ); //addr[15:8]
	LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x50 ); //addr[7:0]
	LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x00 ); //data lenth
	LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x00 ); //data lenth
	LT8911EXB_IIC_Write_byte(dev, 0x2c, 0x00 ); //start Aux read edid

#ifdef UART_DEBUG
	debug( "\r\n" );
	debug( "\r\nRead eDP EDID......" );
#endif

	mdelay( 20 ); //more than 10ms
	reg = LT8911EXB_IIC_Read_byte(dev, 0x25);
	
	debug( "\r\nRead eDP EDID.reg = %02x.....\n", reg);
	if( ( reg & 0x0f ) == 0x0c )
	{
		for( j = 0; j < 8; j++ )
		{
			if( j == 7 )
			{
				LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x10 ); //MOT
			}else
			{
				LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x50 );
			}

			LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x00 );
			LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x50 );
			LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x0f );
			LT8911EXB_IIC_Write_byte(dev, 0x2c, 0x00 ); //start Aux read edid
			mdelay( 50 );                         //more than 50ms

			if( LT8911EXB_IIC_Read_byte(dev, 0x39 ) == 0x31 )
			{
				LT8911EXB_IIC_Read_byte(dev, 0x2b );
				for( i = 0; i < 16; i++ )
				{
					EDID_DATA[j * 16 + i] = LT8911EXB_IIC_Read_byte(dev, 0x2b );
				}

				EDID_Reply = 1;
			}else
			{
				EDID_Reply = 0;
#ifdef UART_DEBUG
				debug( "\r\nno_reply" );
				debug( "\r\n" );
#endif
				debug("\r\n*************End***************");
				return;
			}
		}

#ifdef UART_DEBUG

		for( i = 0; i < 128; i++ ) //print edid data
		{
			if( ( i % 16 ) == 0 )
			{
				debug( "\r\n" );
			}
			debug( "%d, ", EDID_DATA[i] );
		}

		EDID_Timing[hfp] = ( ( EDID_DATA[0x41] & 0xC0 ) * 4 + EDID_DATA[0x3e] );

		EDID_Timing[hs] = ( ( EDID_DATA[0x41] & 0x30 ) * 16 + EDID_DATA[0x3f] );

		EDID_Timing[hbp] = ( ( ( EDID_DATA[0x3a] & 0x0f ) * 0x100 + EDID_DATA[0x39] ) - ( ( EDID_DATA[0x41] & 0x30 ) * 16 + EDID_DATA[0x3f] ) - ( ( EDID_DATA[0x41] & 0xC0 ) * 4 + EDID_DATA[0x3e] ) );

		EDID_Timing[hact] = ( ( EDID_DATA[0x3a] & 0xf0 ) * 16 + EDID_DATA[0x38] );

		EDID_Timing[htotal] = ( ( EDID_DATA[0x3a] & 0xf0 ) * 16 + EDID_DATA[0x38] + ( ( EDID_DATA[0x3a] & 0x0f ) * 0x100 + EDID_DATA[0x39] ) );

		EDID_Timing[vfp] = ( ( EDID_DATA[0x41] & 0x0c ) * 4 + ( EDID_DATA[0x40] & 0xf0 ) / 16 );

		EDID_Timing[vs] = ( ( EDID_DATA[0x41] & 0x03 ) * 16 + (EDID_DATA[0x40] & 0x0f) );

		EDID_Timing[vbp] = ( ( ( EDID_DATA[0x3d] & 0x03 ) * 0x100 + EDID_DATA[0x3c] ) - ( ( EDID_DATA[0x41] & 0x03 ) * 16 + ( EDID_DATA[0x40] & 0x0f ) ) - ( ( EDID_DATA[0x41] & 0x0c ) * 4 + ( EDID_DATA[0x40] & 0xf0 ) / 16 ) );

		EDID_Timing[vact] = ( ( EDID_DATA[0x3d] & 0xf0 ) * 16 + EDID_DATA[0x3b] );

		EDID_Timing[vtotal] = ( ( EDID_DATA[0x3d] & 0xf0 ) * 16 + EDID_DATA[0x3b] + ( ( EDID_DATA[0x3d] & 0x03 ) * 0x100 + EDID_DATA[0x3c] ) );

		EDID_Timing[pclk_10khz] = ( EDID_DATA[0x37] * 0x100 + EDID_DATA[0x36] );
#endif
	}

	return;

#endif
}

void LT8911EXB_MIPI_Video_Timing(struct udevice *dev)                                    // ( struct video_timing *video_format )
{
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xd0 );
	LT8911EXB_IIC_Write_byte(dev, 0x0d, (u8)( MIPI_Timing[vtotal] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x0e, (u8)( MIPI_Timing[vtotal] % 256 ) );    //vtotal
	LT8911EXB_IIC_Write_byte(dev, 0x0f, (u8)( MIPI_Timing[vact] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x10, (u8)( MIPI_Timing[vact] % 256 ) );      //vactive

	LT8911EXB_IIC_Write_byte(dev, 0x11, (u8)( MIPI_Timing[htotal] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x12, (u8)( MIPI_Timing[htotal] % 256 ) );    //htotal
	LT8911EXB_IIC_Write_byte(dev, 0x13, (u8)( MIPI_Timing[hact] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x14, (u8)( MIPI_Timing[hact] % 256 ) );      //hactive

	LT8911EXB_IIC_Write_byte(dev, 0x15, (u8)( MIPI_Timing[vs] % 256 ) );        //vsa
	LT8911EXB_IIC_Write_byte(dev, 0x16, (u8)( MIPI_Timing[hs] % 256 ) );        //hsa
	LT8911EXB_IIC_Write_byte(dev, 0x17, (u8)( MIPI_Timing[vfp] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x18, (u8)( MIPI_Timing[vfp] % 256 ) );       //vfp

	LT8911EXB_IIC_Write_byte(dev, 0x19, (u8)( MIPI_Timing[hfp] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x1a, (u8)( MIPI_Timing[hfp] % 256 ) );       //hfp
}

void LT8911EXB_eDP_Video_cfg(struct udevice *dev)                                        // ( struct video_timing *video_format )
{
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa8 );
	LT8911EXB_IIC_Write_byte(dev, 0x2d, 0x88 );                                 // MSA from register

#ifdef _Msa_Active_Only_
	LT8911EXB_IIC_Write_byte(dev, 0x05, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x06, 0x00 );                                 //htotal
	LT8911EXB_IIC_Write_byte(dev, 0x07, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x08, 0x00 );                                 //h_start

	LT8911EXB_IIC_Write_byte(dev, 0x09, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x0a, 0x00 );                                 //hsa
	LT8911EXB_IIC_Write_byte(dev, 0x0b, (u8)( MIPI_Timing[hact] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x0c, (u8)( MIPI_Timing[hact] % 256 ) );      //hactive

	LT8911EXB_IIC_Write_byte(dev, 0x0d, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x0e, 0x00 );                                 //vtotal

	LT8911EXB_IIC_Write_byte(dev, 0x11, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x12, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x15, (u8)( MIPI_Timing[vact] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x16, (u8)( MIPI_Timing[vact] % 256 ) );      //vactive

#else

	LT8911EXB_IIC_Write_byte(dev, 0x05, (u8)( MIPI_Timing[htotal] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x06, (u8)( MIPI_Timing[htotal] % 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x07, (u8)( ( MIPI_Timing[hs] + MIPI_Timing[hbp] ) / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x08, (u8)( ( MIPI_Timing[hs] + MIPI_Timing[hbp] ) % 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x09, (u8)( MIPI_Timing[hs] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x0a, (u8)( MIPI_Timing[hs] % 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x0b, (u8)( MIPI_Timing[hact] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x0c, (u8)( MIPI_Timing[hact] % 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x0d, (u8)( MIPI_Timing[vtotal] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x0e, (u8)( MIPI_Timing[vtotal] % 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x11, (u8)( ( MIPI_Timing[vs] + MIPI_Timing[vbp] ) / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x12, (u8)( ( MIPI_Timing[vs] + MIPI_Timing[vbp] ) % 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x14, (u8)( MIPI_Timing[vs] % 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x15, (u8)( MIPI_Timing[vact] / 256 ) );
	LT8911EXB_IIC_Write_byte(dev, 0x16, (u8)( MIPI_Timing[vact] % 256 ) );
#endif
}

void LT8911EXB_init(struct udevice *dev)
{
	u8	i;
	u8	pcr_pll_postdiv;
	u8	pcr_m;
	u16 Temp16;

	/* init */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 ); // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x08, 0x7f ); // i2c over aux issue
	LT8911EXB_IIC_Write_byte(dev, 0x49, 0xff ); // enable 0x87xx

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x82 ); // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x5a, 0x0e ); // GPIO test output

	//for power consumption//
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );
	LT8911EXB_IIC_Write_byte(dev, 0x05, 0x06 );
	LT8911EXB_IIC_Write_byte(dev, 0x43, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x44, 0x1f );
	LT8911EXB_IIC_Write_byte(dev, 0x45, 0xf7 );
	LT8911EXB_IIC_Write_byte(dev, 0x46, 0xf6 );
	LT8911EXB_IIC_Write_byte(dev, 0x49, 0x7f );

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x82 );
#if ( eDP_lane == 2 )
	{
		LT8911EXB_IIC_Write_byte(dev, 0x12, 0x33 );
	}
#elif ( eDP_lane == 1 )
	{
		LT8911EXB_IIC_Write_byte(dev, 0x12, 0x11 );
	}
#endif

	/* mipi Rx analog */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x82 ); // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x32, 0x51 );
	LT8911EXB_IIC_Write_byte(dev, 0x35, 0x22 ); //EQ current 0x22/0x42/0x62/0x82/0xA2/0xC2/0xe2
	LT8911EXB_IIC_Write_byte(dev, 0x3a, 0x77 ); //EQ 12.5db
	LT8911EXB_IIC_Write_byte(dev, 0x3b, 0x77 ); //EQ 12.5db

	LT8911EXB_IIC_Write_byte(dev, 0x4c, 0x0c );
	LT8911EXB_IIC_Write_byte(dev, 0x4d, 0x00 );

	/* dessc_pcr  pll analog */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x82 ); // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x6a, 0x40 );
	LT8911EXB_IIC_Write_byte(dev, 0x6b, PCR_PLL_PREDIV );

	Temp16 = MIPI_Timing[pclk_10khz];

	if( MIPI_Timing[pclk_10khz] < 8800 )
	{
		LT8911EXB_IIC_Write_byte(dev, 0x6e, 0x82 ); //0x44:pre-div = 2 ,pixel_clk=44~ 88MHz
		pcr_pll_postdiv = 0x08;
	}else
	if( MIPI_Timing[pclk_10khz] < 17600 )
	{
		LT8911EXB_IIC_Write_byte(dev, 0x6e, 0x81 ); //0x40:pre-div = 1, pixel_clk =88~176MHz
		pcr_pll_postdiv = 0x04;
	}else
	{
		LT8911EXB_IIC_Write_byte(dev, 0x6e, 0x80 ); //0x40:pre-div = 0, pixel_clk =176~200MHz
		pcr_pll_postdiv = 0x02;
	}

	pcr_m = (u8)( Temp16 * pcr_pll_postdiv / 25 / 100 );

	/* dessc pll digital */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );     // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0xa9, 0x31 );
	LT8911EXB_IIC_Write_byte(dev, 0xaa, 0x17 );
	LT8911EXB_IIC_Write_byte(dev, 0xab, 0xba );
	LT8911EXB_IIC_Write_byte(dev, 0xac, 0xe1 );
	LT8911EXB_IIC_Write_byte(dev, 0xad, 0x47 );
	LT8911EXB_IIC_Write_byte(dev, 0xae, 0x01 );
	LT8911EXB_IIC_Write_byte(dev, 0xae, 0x11 );

	/* Digital Top */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );                             // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0xc0, 0x01 );                             //select mipi Rx
#ifdef _6bit_
	LT8911EXB_IIC_Write_byte(dev, 0xb0, 0xd0 );                             //enable dither
#else
	LT8911EXB_IIC_Write_byte(dev, 0xb0, 0x00 );                             // disable dither
#endif

	/* mipi Rx Digital */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xd0 );                             // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x00, _MIPI_data_PN_ + _MIPI_Lane_ % 4 ); // 0: 4 Lane / 1: 1 Lane / 2 : 2 Lane / 3: 3 Lane
	LT8911EXB_IIC_Write_byte(dev, 0x02, 0x08 );                             //settle
	LT8911EXB_IIC_Write_byte(dev, 0x03, MIPI_DATA_SEQ );             // default is 0x00
	LT8911EXB_IIC_Write_byte(dev, 0x08, 0x00 );
//	LT8911EXB_IIC_Write_byte(dev, 0x0a, 0x12 );               //pcr mode

	LT8911EXB_IIC_Write_byte(dev, 0x0c, 0x80 );                             //fifo position
	LT8911EXB_IIC_Write_byte(dev, 0x1c, 0x80 );                             //fifo position

	//	hs mode:MIPI行采样；vs mode:MIPI帧采样
	LT8911EXB_IIC_Write_byte(dev, 0x24, 0x70 );                             // 0x30  [3:0]  line limit	  //pcr mode( de hs vs)

	LT8911EXB_IIC_Write_byte(dev, 0x31, 0x0a );

	/*stage1 hs mode*/
	LT8911EXB_IIC_Write_byte(dev, 0x25, 0x90 );                             // 0x80		   // line limit
	LT8911EXB_IIC_Write_byte(dev, 0x2a, 0x3a );                             // 0x04		   // step in limit
	LT8911EXB_IIC_Write_byte(dev, 0x21, 0x4f );                             // hs_step
	LT8911EXB_IIC_Write_byte(dev, 0x22, 0xff );

	/*stage2 de mode*/
	LT8911EXB_IIC_Write_byte(dev, 0x0a, 0x02 );                             //de adjust pre line
	LT8911EXB_IIC_Write_byte(dev, 0x38, 0x02 );                             //de_threshold 1
	LT8911EXB_IIC_Write_byte(dev, 0x39, 0x04 );                             //de_threshold 2
	LT8911EXB_IIC_Write_byte(dev, 0x3a, 0x08 );                             //de_threshold 3
	LT8911EXB_IIC_Write_byte(dev, 0x3b, 0x10 );                             //de_threshold 4

	LT8911EXB_IIC_Write_byte(dev, 0x3f, 0x04 );                             //de_step 1
	LT8911EXB_IIC_Write_byte(dev, 0x40, 0x08 );                             //de_step 2
	LT8911EXB_IIC_Write_byte(dev, 0x41, 0x10 );                             //de_step 3
	LT8911EXB_IIC_Write_byte(dev, 0x42, 0x60 );                             //de_step 4

	/*stage2 hs mode*/
	LT8911EXB_IIC_Write_byte(dev, 0x1e, 0x0A );//LT8911EXB_IIC_Write_byte(dev, 0x1e, 0x01 );                             // 0x11
	LT8911EXB_IIC_Write_byte(dev, 0x23, 0xf0 );                             // 0x80			   //

	LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x80 );                             // 0xa0

#ifdef _Test_Pattern_
	LT8911EXB_IIC_Write_byte(dev, 0x26, ( pcr_m | 0x80 ) );
#else

	LT8911EXB_IIC_Write_byte(dev, 0x26, pcr_m );

#endif

	LT8911EXB_MIPI_Video_Timing(dev);         //defualt setting is 1080P

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 ); // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x03, 0x7b ); //PCR reset
	LT8911EXB_IIC_Write_byte(dev, 0x03, 0xff );

#ifdef EDP_2G7
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
	LT8911EXB_IIC_Write_byte(dev, 0x19, 0x31 );
	LT8911EXB_IIC_Write_byte(dev, 0x1a, 0x36 ); // sync m
	LT8911EXB_IIC_Write_byte(dev, 0x1b, 0x00 ); // sync_k [7:0]
	LT8911EXB_IIC_Write_byte(dev, 0x1c, 0x00 ); // sync_k [13:8]

	// txpll Analog
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x82 );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0x00 ); // div hardware mode, for ssc.

//	LT8911EXB_IIC_Write_byte(dev, 0x01, 0x18 );// default : 0x18
	LT8911EXB_IIC_Write_byte(dev, 0x02, 0x42 );
	LT8911EXB_IIC_Write_byte(dev, 0x03, 0x00 ); // txpll en = 0
	LT8911EXB_IIC_Write_byte(dev, 0x03, 0x01 ); // txpll en = 1
//	LT8911EXB_IIC_Write_byte(dev, 0x04, 0x3a );// default : 0x3A

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
	LT8911EXB_IIC_Write_byte(dev, 0x0c, 0x10 ); // cal en = 0

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfc );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfd );

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
	LT8911EXB_IIC_Write_byte(dev, 0x0c, 0x11 ); // cal en = 1

	// ssc
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
	LT8911EXB_IIC_Write_byte(dev, 0x13, 0x83 );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0x41 );
	LT8911EXB_IIC_Write_byte(dev, 0x16, 0x0a );
	LT8911EXB_IIC_Write_byte(dev, 0x18, 0x0a );
	LT8911EXB_IIC_Write_byte(dev, 0x19, 0x33 );
#endif

#ifdef _eDP_1G62_
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
	LT8911EXB_IIC_Write_byte(dev, 0x19, 0x31 );
	LT8911EXB_IIC_Write_byte(dev, 0x1a, 0x20 ); // sync m
	LT8911EXB_IIC_Write_byte(dev, 0x1b, 0x19 ); // sync_k [7:0]
	LT8911EXB_IIC_Write_byte(dev, 0x1c, 0x99 ); // sync_k [13:8]

	// txpll Analog
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x82 );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0x00 ); // div hardware mode, for ssc.
	//	LT8911EXB_IIC_Write_byte(dev, 0x01, 0x18 );// default : 0x18
	LT8911EXB_IIC_Write_byte(dev, 0x02, 0x42 );
	LT8911EXB_IIC_Write_byte(dev, 0x03, 0x00 ); // txpll en = 0
	LT8911EXB_IIC_Write_byte(dev, 0x03, 0x01 ); // txpll en = 1
	//	LT8911EXB_IIC_Write_byte(dev, 0x04, 0x3a );// default : 0x3A

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
	LT8911EXB_IIC_Write_byte(dev, 0x0c, 0x10 ); // cal en = 0

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfc );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfd );

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
	LT8911EXB_IIC_Write_byte(dev, 0x0c, 0x11 ); // cal en = 1

	//ssc
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
	LT8911EXB_IIC_Write_byte(dev, 0x13, 0x83 );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0x41 );
	LT8911EXB_IIC_Write_byte(dev, 0x16, 0x0a );
	LT8911EXB_IIC_Write_byte(dev, 0x18, 0x0a );
	LT8911EXB_IIC_Write_byte(dev, 0x19, 0x33 );
#endif

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );

	for( i = 0; i < 5; i++ ) //Check Tx PLL
	{
		mdelay( 5 );
		if( LT8911EXB_IIC_Read_byte(dev, 0x37 ) & 0x02 )
		{
			debug( "\r\nLT8911 tx pll locked" );
			break;
		}else
		{
			debug( "\r\nLT8911 tx pll unlocked" );
			LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );
			LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfc );
			LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfd );

			LT8911EXB_IIC_Write_byte(dev, 0xff, 0x87 );
			LT8911EXB_IIC_Write_byte(dev, 0x0c, 0x10 );
			LT8911EXB_IIC_Write_byte(dev, 0x0c, 0x11 );
		}
	}

	// AUX reset
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 ); // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x07, 0xfe );
	LT8911EXB_IIC_Write_byte(dev, 0x07, 0xff );
	LT8911EXB_IIC_Write_byte(dev, 0x0a, 0xfc );
	LT8911EXB_IIC_Write_byte(dev, 0x0a, 0xfe );

	/* tx phy */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x82 ); // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x11, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x13, 0x10 );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0x0c );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0x08 );
	LT8911EXB_IIC_Write_byte(dev, 0x13, 0x20 );

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x82 ); // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x0e, 0x35 );
//	LT8911EXB_IIC_Write_byte(dev, 0x12, 0xff );
//	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x80 );
//	LT8911EXB_IIC_Write_byte(dev, 0x40, 0x22 );

	/*eDP Tx Digital */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa8 ); // Change Reg bank

#ifdef _Test_Pattern_

	LT8911EXB_IIC_Write_byte(dev, 0x24, 0x50 ); // bit2 ~ bit 0 : test panttern image mode
	LT8911EXB_IIC_Write_byte(dev, 0x25, 0x70 ); // bit6 ~ bit 4 : test Pattern color
	LT8911EXB_IIC_Write_byte(dev, 0x27, 0x50 ); //0x50:Pattern; 0x10:mipi video

//	LT8911EXB_IIC_Write_byte(dev, 0x2d, 0x00 ); //  pure color setting
//	LT8911EXB_IIC_Write_byte(dev, 0x2d, 0x84 ); // black color
	LT8911EXB_IIC_Write_byte(dev, 0x2d, 0x88 ); //  block

#else
	LT8911EXB_IIC_Write_byte(dev, 0x27, 0x10 ); //0x50:Pattern; 0x10:mipi video
#endif

#ifdef _6bit_
	LT8911EXB_IIC_Write_byte(dev, 0x17, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x18, 0x00 );
#else
	// _8bit_
	LT8911EXB_IIC_Write_byte(dev, 0x17, 0x10 );
	LT8911EXB_IIC_Write_byte(dev, 0x18, 0x20 );
#endif

	/* nvid */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa0 );                             // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x00, (u8)( Nvid_Val[_Nvid] / 256 ) );    // 0x08
	LT8911EXB_IIC_Write_byte(dev, 0x01, (u8)( Nvid_Val[_Nvid] % 256 ) );    // 0x00
}

void LT8911EXB_video_check(struct udevice *dev)
{
	u32 reg = 0x00;
	/* mipi byte clk check*/
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );     // Change Reg bank
	LT8911EXB_IIC_Write_byte(dev, 0x1d, 0x00 );     //FM select byte clk
	LT8911EXB_IIC_Write_byte(dev, 0x40, 0xf7 );
	LT8911EXB_IIC_Write_byte(dev, 0x41, 0x30 );

	//#ifdef _eDP_scramble_
	if( ScrambleMode )
	{
		LT8911EXB_IIC_Write_byte(dev, 0xa1, 0x82 ); //eDP scramble mode;
	}
	//#else
	else
	{
		LT8911EXB_IIC_Write_byte(dev, 0xa1, 0x02 ); // DP scramble mode;
	}
	//#endif

//	LT8911EXB_IIC_Write_byte(dev, 0x17, 0xf0 ); // 0xf0:Close scramble; 0xD0 : Open scramble

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0x7d );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfd );

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );
	mdelay(20);
	if( LT8911EXB_IIC_Read_byte(dev, 0x50 ) == 0x03 )
	{
		reg	   = LT8911EXB_IIC_Read_byte(dev, 0x4d );
		reg	   = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x4e );
		reg	   = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x4f );

		debug( "\r\nvideo check: mipi byteclk = %d ", reg ); // mipi byteclk = reg * 1000
		debug( "\r\nvideo check: mipi bitrate = %d ", reg * 8 ); // mipi byteclk = reg * 1000
		debug( "\r\nvideo check: mipi pclk = %d ", reg /3 * 4 * 1000 ); // mipi byteclk = reg * 1000
	}else
	{
		debug( "\r\nvideo check: mipi clk unstable" );
	}

	/* mipi vtotal check*/
	reg	   = LT8911EXB_IIC_Read_byte(dev, 0x76 );
	reg	   = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x77 );

	debug( "\r\nvideo check: Vtotal =  %d", reg);

	/* mipi word count check*/
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xd0 );
	reg	   = LT8911EXB_IIC_Read_byte(dev, 0x82 );
	reg	   = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x83 );
	reg	   = reg / 3;

	debug( "\r\nvideo check: Hact(word counter) =  %d", reg);

	/* mipi Vact check*/
	reg	   = LT8911EXB_IIC_Read_byte(dev, 0x85 );
	reg	   = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x86 );

	debug( "\r\nvideo check: Vact = %d", reg);
}

void DpcdWrite(struct udevice *dev, u32 Address, u8 Data )
{
	/***************************
	   注意大小端的问题!
	   这里默认是大端模式

	   Pay attention to the Big-Endian and Little-Endian!
	   The default mode is Big-Endian here.

	 ****************************/
	u8	AddressH   = 0x0f & ( Address >> 16 );
	u8	AddressM   = 0xff & ( Address >> 8 );
	u8	AddressL   = 0xff & Address;

	u8	reg;

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa6 );
	LT8911EXB_IIC_Write_byte(dev, 0x2b, ( 0x80 | AddressH ) );  //CMD
	LT8911EXB_IIC_Write_byte(dev, 0x2b, AddressM );             //addr[15:8]
	LT8911EXB_IIC_Write_byte(dev, 0x2b, AddressL );             //addr[7:0]
	LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x00 );                 //data lenth
	LT8911EXB_IIC_Write_byte(dev, 0x2b, Data );                 //data
	LT8911EXB_IIC_Write_byte(dev, 0x2c, 0x00 );                 //start Aux

	mdelay( 20 );                                         //more than 10ms
	reg = LT8911EXB_IIC_Read_byte(dev, 0x25 );

	if( ( reg & 0x0f ) == 0x0c )
	{
		return;
	}
}

u8 DpcdRead(struct udevice *dev, u32 Address )
{
	/***************************
	   注意大小端的问题!
	   这里默认是大端模式

	   Pay attention to the Big-Endian and Little-Endian!
	   The default mode is Big-Endian here.

	 ****************************/

	u8	DpcdValue  = 0x00;
	u8	AddressH   = 0x0f & ( Address >> 16 );
	u8	AddressM   = 0xff & ( Address >> 8 );
	u8	AddressL   = 0xff & Address;
	u8	reg;

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
	LT8911EXB_IIC_Write_byte(dev, 0x00, 0x20 );                 //Soft Link train
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa6 );
	LT8911EXB_IIC_Write_byte(dev, 0x2a, 0x01 );

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa6 );
	LT8911EXB_IIC_Write_byte(dev, 0x2b, ( 0x90 | AddressH ) );  //CMD
	LT8911EXB_IIC_Write_byte(dev, 0x2b, AddressM );             //addr[15:8]
	LT8911EXB_IIC_Write_byte(dev, 0x2b, AddressL );             //addr[7:0]
	LT8911EXB_IIC_Write_byte(dev, 0x2b, 0x00 );                 //data lenth
	LT8911EXB_IIC_Write_byte(dev, 0x2c, 0x00 );                 //start Aux read edid

	mdelay( 50 );                                         //more than 10ms
	reg = LT8911EXB_IIC_Read_byte(dev, 0x25 );
	if( ( reg & 0x0f ) == 0x0c )
	{
		if( LT8911EXB_IIC_Read_byte(dev, 0x39 ) == 0x22 )
		{
			LT8911EXB_IIC_Read_byte(dev, 0x2b );
			DpcdValue = LT8911EXB_IIC_Read_byte(dev, 0x2b );
		}


		/*
		   else
		   {
		   //	goto no_reply;
		   //	DpcdValue = 0xff;
		   return DpcdValue;
		   }//*/
	}else
	{
		LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 ); // change bank
		LT8911EXB_IIC_Write_byte(dev, 0x07, 0xfe );
		LT8911EXB_IIC_Write_byte(dev, 0x07, 0xff );
		LT8911EXB_IIC_Write_byte(dev, 0x0a, 0xfc );
		LT8911EXB_IIC_Write_byte(dev, 0x0a, 0xfe );
	}

	return DpcdValue;
}

void LT8911EX_link_train(struct udevice *dev)
{
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );
	LT8911EXB_IIC_Write_byte(dev, 0x06, 0xdf ); // rset VID TX
	LT8911EXB_IIC_Write_byte(dev, 0x06, 0xff );

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );

	if( ScrambleMode )
	{
		LT8911EXB_IIC_Write_byte(dev, 0xa1, 0x82 ); // eDP scramble mode;
		LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
		LT8911EXB_IIC_Write_byte(dev, 0x00, 0x20 ); //Soft Link train
		LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa6 );
		LT8911EXB_IIC_Write_byte(dev, 0x2a, 0x01 );

		DpcdWrite(dev, 0x010a, 0x01 );
		mdelay(10);
		DpcdWrite(dev, 0x0102, 0x00 );
		mdelay(10);
		DpcdWrite(dev, 0x010a, 0x01 );

		mdelay(10);
		//*/
	}
//#else
	else
	{
		LT8911EXB_IIC_Write_byte(dev, 0xa1, 0x02 ); // DP scramble mode;
	}
//#endif

	/* Aux setup */
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
	LT8911EXB_IIC_Write_byte(dev, 0x00, 0x60 );     //Soft Link train
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa6 );
	LT8911EXB_IIC_Write_byte(dev, 0x2a, 0x00 );

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );
	LT8911EXB_IIC_Write_byte(dev, 0x07, 0xfe );
	LT8911EXB_IIC_Write_byte(dev, 0x07, 0xff );
	LT8911EXB_IIC_Write_byte(dev, 0x0a, 0xfc );
	LT8911EXB_IIC_Write_byte(dev, 0x0a, 0xfe );

	/* link train */

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );
	LT8911EXB_IIC_Write_byte(dev, 0x1a, eDP_lane );

#ifdef LINK_TRAIN_ENABLE
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
	LT8911EXB_IIC_Write_byte(dev, 0x00, 0x64 );
	LT8911EXB_IIC_Write_byte(dev, 0x01, 0x0a );
	LT8911EXB_IIC_Write_byte(dev, 0x0c, 0x85 );
	LT8911EXB_IIC_Write_byte(dev, 0x0c, 0xc5 );
#else
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
	LT8911EXB_IIC_Write_byte(dev, 0x00, 0x00 );
	LT8911EXB_IIC_Write_byte(dev, 0x01, 0x0a );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0x80 );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0x81 );
	mdelay( 50 );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0x84 );
	mdelay( 50 );
	LT8911EXB_IIC_Write_byte(dev, 0x14, 0xc0 );
#endif
}

static int LT8911EX_link_train_result(struct udevice *dev)
{
	u8 i, reg;
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
	for( i = 0; i < 10; i++ )
	{
		reg = LT8911EXB_IIC_Read_byte(dev, 0x82 );
		//  Debug_DispStrNum( "\r\n0x82 = ", reg );
		if( reg & 0x20 )
		{
			if( ( reg & 0x1f ) == 0x1e )
			{
				debug( "\r\nLink train success, 0x82 = 0x%x", reg );
				debug( "\r\npanel link rate: 0x%x", LT8911EXB_IIC_Read_byte(dev, 0x83 ) );
				debug( "\r\npanel link count: 0x%x", LT8911EXB_IIC_Read_byte(dev, 0x84 ) );
				mdelay( 10 );
				return 0;
			} else{
				debug( "\r\nLink train fail, 0x82 = 0x%x", reg );
				debug( "\r\npanel link rate: 0x%x", LT8911EXB_IIC_Read_byte(dev, 0x83 ) );
				debug( "\r\npanel link count: 0x%x", LT8911EXB_IIC_Read_byte(dev, 0x84 ) );
				mdelay( 10 );
				return -1;
			}

		}
		else{
			debug( "\r\nlink trian on going..." );
			mdelay( 1 );
		}
		
	}
	return -1;
}

void LT8911EXB_MainLoop(struct udevice *dev)
{
#ifndef _Test_Pattern_
	u16 reg;

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );
	//LT8911EXB_IIC_Write_byte(0x1d,0x00); //FM select byte clk
	//LT8911EXB_IIC_Write_byte(0x40,0xf7);
	//LT8911EXB_IIC_Write_byte(0x41,0x30);

	if( ScrambleMode )
	{
		LT8911EXB_IIC_Write_byte(dev, 0xa1, 0x82 ); //
	}else
	{
		LT8911EXB_IIC_Write_byte(dev, 0xa1, 0x02 ); //
	}

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );     //video check rst
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0x7d );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfd );
	mdelay(10);

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );
	reg	   = LT8911EXB_IIC_Read_byte(dev, 0x76 );
	reg	   = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x77 );

//	if( reg == MIPI_Timing[vtotal] )
	if( ( reg > ( MIPI_Timing[vtotal] - 5 ) ) && ( reg < ( MIPI_Timing[vtotal] + 5 ) ) )
	{
		if( !flag_mipi_on )
		{
			LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 ); //PCR reset
			LT8911EXB_IIC_Write_byte(dev, 0x03, 0x7b );
			LT8911EXB_IIC_Write_byte(dev, 0x03, 0xff );

			LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa8 );
			LT8911EXB_IIC_Write_byte(dev, 0x2d, 0x88 );
			flag_mipi_on = 1;
			debug( "\r\nPCR reset" );
		}
	}else
	{
		LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa8 );
		LT8911EXB_IIC_Write_byte(dev, 0x2d, 0x8c ); //edp output idle pattern;
		flag_mipi_on = 0;
	}

#ifdef UART_DEBUG
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xd0 );
	reg = LT8911EXB_IIC_Read_byte(dev, 0x87 );
//	reg	   = reg * 256 + HDMI_ReadI2C_Byte( 0x77 );
	if( reg & 0x10 )
	{
		debug( "\r\nPCR Clock stable" );
	}else
	{
		debug( "\r\nPCR Clock unstable" );
	}
	debug( "\r\n " );
#endif

#endif
}

enum
{
	_Level0_ = 0,                                               // 27.8 mA  0x83/0x00
	_Level1_,                                                   // 26.2 mA  0x82/0xe0
	_Level2_,                                                   // 24.6 mA  0x82/0xc0
	_Level3_,                                                   // 23 mA    0x82/0xa0
	_Level4_,                                                   // 21.4 mA  0x82/0x80
	_Level5_,                                                   // 18.2 mA  0x82/0x40
	_Level6_,                                                   // 16.6 mA  0x82/0x20
	_Level7_,                                                   // 15mA     0x82/0x00  // level 1
	_Level8_,                                                   // 12.8mA   0x81/0x00  // level 2
	_Level9_,                                                   // 11.2mA   0x80/0xe0  // level 3
	_Level10_,                                                  // 9.6mA    0x80/0xc0  // level 4
	_Level11_,                                                  // 8mA      0x80/0xa0  // level 5
	_Level12_,                                                  // 6mA      0x80/0x80  // level 6
};

u8	Swing_Setting1[] = { 0x83, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x81, 0x80, 0x80, 0x80, 0x80 };
u8	Swing_Setting2[] = { 0x00, 0xe0, 0xc0, 0xa0, 0x80, 0x40, 0x20, 0x00, 0x00, 0xe0, 0xc0, 0xa0, 0x80 };

u8	Level = _Level7_;   

void LT8911EX_TxSwingPreSet(struct udevice *dev)
{
	LT8911EXB_IIC_Write_byte(dev, 0xFF, 0x82 );
	LT8911EXB_IIC_Write_byte(dev, 0x22, Swing_Setting1[Level] );    //lane 0 tap0
	LT8911EXB_IIC_Write_byte(dev, 0x23, Swing_Setting2[Level] );
	LT8911EXB_IIC_Write_byte(dev, 0x24, 0x80 );                     //lane 0 tap1
	LT8911EXB_IIC_Write_byte(dev, 0x25, 0x00 );

#if ( eDP_lane == 2 )
	LT8911EXB_IIC_Write_byte(dev, 0x26, Swing_Setting1[Level] );    //lane 1 tap0
	LT8911EXB_IIC_Write_byte(dev, 0x27, Swing_Setting2[Level] );
	LT8911EXB_IIC_Write_byte(dev, 0x28, 0x80 );                     //lane 1 tap1
	LT8911EXB_IIC_Write_byte(dev, 0x29, 0x00 );
#endif
}

void PCR_Status(struct udevice *dev)                                         // for debug
{
#ifdef UART_DEBUG
	u8 reg;

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xd0 );
	reg = LT8911EXB_IIC_Read_byte(dev, 0x87 );

	debug( "\r\nReg0xD087 =	");
	debug( " 0x%x ", reg );
	debug( "\r\n " );
	if( reg & 0x10 )
	{
		debug( "\r\nPCR Clock stable" );
	}else
	{
		debug( "\r\nPCR Clock unstable" );
	}
	debug( "\r\n " );
#endif
}

void LT8911_MainLoop(struct udevice *dev)
{
	u16 reg, H_act, V_act;
//	bool	flag_mipi_on = 0;

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );

	if( ScrambleMode )
	{
		LT8911EXB_IIC_Write_byte(dev, 0xa1, 0x82 ); //video check from mipi
	}else
	{
		LT8911EXB_IIC_Write_byte(dev, 0xa1, 0x02 );
	}

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 );     //video check rst
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0x7d );
	LT8911EXB_IIC_Write_byte(dev, 0x09, 0xfd );
	mdelay(10);

	/* mipi word count check*/
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xd0 );
	reg	   = LT8911EXB_IIC_Read_byte(dev, 0x82 );
	reg	   = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x83 );
	H_act  = reg / 3;

#ifdef UART_DEBUG

	debug( "\r\nHact(word counter) =  %d\r\n", H_act ); // H active = word counter / 3

#endif

	/* mipi Vact check*/
	reg	   = LT8911EXB_IIC_Read_byte(dev, 0x85 );
	V_act  = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x86 );

#ifdef UART_DEBUG

	debug( "\r\nVact = %d\r\n ",V_act );
#endif

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0x85 );
	reg	   = LT8911EXB_IIC_Read_byte(dev, 0x76 );
	reg	   = reg * 256 + LT8911EXB_IIC_Read_byte(dev, 0x77 );

#ifdef UART_DEBUG
	debug( "\r\nvideo check: Vtotal = %d\r\n ",reg );
#endif

//	if( reg == MIPI_Timing[vtotal] )
	if( ( reg > ( MIPI_Timing[vtotal] - 5 ) ) && ( reg < ( MIPI_Timing[vtotal] + 5 ) ) )
	{
		if( !flag_mipi_on )
		{
			LT8911EXB_IIC_Write_byte(dev, 0xff, 0x81 ); //PCR reset
			LT8911EXB_IIC_Write_byte(dev, 0x03, 0x7b );
			LT8911EXB_IIC_Write_byte(dev, 0x03, 0xff );

			LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa8 );
			LT8911EXB_IIC_Write_byte(dev, 0x2d, 0x88 );
			flag_mipi_on = 1;
#ifdef UART_DEBUG
			debug( "\r\nPCR reset" );
#endif
		}
	}else
	{
		LT8911EXB_IIC_Write_byte(dev, 0xff, 0xa8 );
		LT8911EXB_IIC_Write_byte(dev, 0x2d, 0x8c ); //edp output idle pattern;
		flag_mipi_on = 0;
	}

#ifdef UART_DEBUG
	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xd0 );
	reg = LT8911EXB_IIC_Read_byte(dev, 0x87 );

	debug( "\r\nReg0xD087 = 0x%x\r\n ",reg );

	if( reg & 0x10 )
	{
		debug( "\r\nPCR Clock stable" );
	}else
	{
		debug( "\r\nPCR Clock unstable" );
	}
	debug( "\r\n " );
#endif
}

/***********************************************************/

void LT8911EXB_LinkTrainResultCheck(struct udevice *dev)
{
#ifdef LINK_TRAIN_ENABLE
	u8	i;
	u8	val;
	//int ret;

	LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
	for( i = 0; i < 10; i++ )
	{
		val = LT8911EXB_IIC_Read_byte(dev, 0x82 );
		if( val & 0x20 )
		{
			if( ( val & 0x1f ) == 0x1e )
			{
#ifdef UART_DEBUG
				//   debug("\r\nLT8911_LinkTrainResultCheck: edp link train successed: 0x%bx", val);
				debug( "\r\nedp link train successed: 0x%x", val );
#endif
				return;
			}else
			{
#ifdef UART_DEBUG
				//debug("\r\nLT8911_LinkTrainResultCheck: edp link train failed: 0x%bx", val);
				debug( "\r\nedp link train failed: 0x%x", val );
#endif
				LT8911EXB_IIC_Write_byte(dev, 0xff, 0xac );
				LT8911EXB_IIC_Write_byte(dev, 0x00, 0x00 );
				LT8911EXB_IIC_Write_byte(dev, 0x01, 0x0a );
				LT8911EXB_IIC_Write_byte(dev, 0x14, 0x80 );
				LT8911EXB_IIC_Write_byte(dev, 0x14, 0x81 );
				mdelay(10);
				LT8911EXB_IIC_Write_byte(dev, 0x14, 0x84 );
				mdelay(10);
				LT8911EXB_IIC_Write_byte(dev, 0x14, 0xc0 );
				//debug("\r\nLT8911_LinkTrainResultCheck: Enable eDP video output while linktrian fail");
			}

#ifdef UART_DEBUG

			val = LT8911EXB_IIC_Read_byte(dev, 0x83 );
			//debug("\r\nLT8911_LinkTrainResultCheck: panel link rate: 0x%bx",val);
			debug( "\r\npanel link rate: 0x%x", val );
			val = LT8911EXB_IIC_Read_byte(dev, 0x84 );
			//debug("\r\nLT8911_LinkTrainResultCheck: panel link count: 0x%bx",val);
			debug( "\r\npanel link count:0x%x ", val );
#endif
			mdelay( 10 ); // return;
		}else
		{
			//debug("\r\nLT8911_LinkTrainResultCheck: link trian on going...");
			mdelay( 10 );
		}
	}
#endif
}

static int edp_panel_enable_backlight(struct udevice *dev)
{
	struct mipi_dsi_panel_plat *plat = dev_get_plat(dev);
	struct mipi_dsi_device *device = plat->device;
	int ret;

	debug("\r\nedp_panel_enable_backlight\r\n");

	ret = mipi_dsi_attach(device);
	if (ret < 0)
		return ret;
	Reset_LT8911EXB(dev);     // 先Reset LT8911EXB ,用GPIO 先拉低LT8911EXB的复位脚 100ms左右，再拉高，保持100ms。

	LT8911EX_ChipID(dev);     // read Chip ID

	LT8911EXB_eDP_Video_cfg(dev);
	
	LT8911EXB_init(dev);

	ScrambleMode = 0;
	
	LT8911EX_TxSwingPreSet(dev);

	LT8911EX_link_train(dev);

	LT8911EXB_LinkTrainResultCheck(dev);
//======================================//
	ret = LT8911EX_link_train_result(dev);	// for debug
	if (ret < 0)
		return ret;

	LT8911EXB_video_check(dev);		// just for Check MIPI Input

	debug("\r\nDpcdRead(0x0202) = 0x%x\r\n",DpcdRead(dev,0x0202));

	PCR_Status(dev);					// just for Check PCR CLK

	return 0;
}

static int edp_panel_get_display_timing(struct udevice *dev,
					    struct display_timing *timings)
{
	memcpy(timings, &default_timing, sizeof(*timings));
	return 0;
}

static int edp_panel_of_to_plat(struct udevice *dev)
{
	return 0;
}

static int edp_panel_probe(struct udevice *dev)
{
	struct mipi_dsi_panel_plat *plat = dev_get_plat(dev);
	struct edp_panel_priv *priv = dev_get_priv(dev);
	u8 regval;

	/* fill characteristics of DSI data link */
	plat->lanes = 4;
	plat->format = MIPI_DSI_FMT_RGB888;
	plat->mode_flags = MIPI_DSI_MODE_VIDEO |
			   MIPI_DSI_MODE_VIDEO_BURST |
			   MIPI_DSI_MODE_LPM;

	priv->reset_gpio = devm_gpiod_get_optional(dev, "reset",
						GPIOD_IS_IN);
	if (IS_ERR(priv->reset_gpio)) {
		pr_err("Failed get reset gpio41\n");
		return PTR_ERR(priv->reset_gpio);
	}

	priv->pwm_gpio = devm_gpiod_get_optional(dev, "pwm",
						GPIOD_IS_OUT);
	if (IS_ERR(priv->pwm_gpio)) {
		pr_err("Failed get power gpio33\n");
		return PTR_ERR(priv->pwm_gpio);
	}

	priv->bl_gpio = devm_gpiod_get_optional(dev, "bl",
						GPIOD_IS_OUT);
	if (IS_ERR(priv->bl_gpio)) {
		pr_err("Failed get bl\n");
		return PTR_ERR(priv->bl_gpio);
	}

	LT8911EXB_init(dev);
	regval = DpcdRead(dev, 0x0101);
	debug("0x0101 DpcdRead regval = 0x%x\n", regval);
	if (regval == 0x00 || regval == 0xff ){
		pr_err("no screen connected\n");
		return -1;
	}

	return 0;
}

static const struct panel_ops edp_panel_ops = {
	.enable_backlight = edp_panel_enable_backlight,
	.get_display_timing = edp_panel_get_display_timing,
};

static const struct udevice_id edp_panel_ids[] = {
	{ .compatible = "lontium,lt8911exb" },
	{ }
};

U_BOOT_DRIVER(edp_panel) = {
	.name			  = "edp_panel",
	.id			  	  = UCLASS_PANEL,
	.of_match		  = edp_panel_ids,
	.ops			  = &edp_panel_ops,
	.of_to_plat	      = edp_panel_of_to_plat,
	.probe			  = edp_panel_probe,
	.plat_auto	      = sizeof(struct mipi_dsi_panel_plat),
	.priv_auto	      = sizeof(struct edp_panel_priv),
};
