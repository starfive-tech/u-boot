// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2018 Microsemi Corporation.
 * Padmarao Begari, Microsemi Corporation <padmarao.begari@microsemi.com>
 * Copyright (C) 2018 Joey Hewitt <joey@joeyhewitt.com>
 */

#include <common.h>
#include <env.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <dm/uclass.h>
#include <dm/device.h>
#include <misc.h>
#include <inttypes.h>
#include <netdev.h>
#include <phy_interface.h>
#include <flash.h>

#include <asm/arch/io.h>
#include <asm/arch/global_reg.h>
#include <asm/arch/ezGPIO_fullMux_ctrl_macro.h>
#include <asm/arch/clkgen_ctrl_macro.h>
#include <asm/arch/syscon_sysmain_ctrl_macro.h>
#include <asm/arch/rstgen_ctrl_macro.h>
#include <asm/arch/audio_rst_gen_ctrl_macro.h>
#include <asm/arch/audio_clk_gen_ctrl_macro.h>
#include <asm/arch/audio_sys_ctrl_macro.h>
#include <asm/arch/vic_iopad.h>
#include <asm/arch/vic_module_reset_clkgen.h>
#include <asm/arch/vic_ptc.h>

#include <asm/arch/vout_sys_clkgen_ctrl_macro.h>
#include <asm/arch/vout_sys_rstgen_ctrl_macro.h>
#include <asm/arch/vout_sys_syscon_macro.h>
#include <asm/arch/vad.h>
#include <asm/arch/syscon_remap_vp6_noc_macro.h>
#include <asm/arch/syscon_iopad_ctrl_macro.h>

DECLARE_GLOBAL_DATA_PTR;

/* added by chenjieqin for ptc on 20200824 */
/* pwm channel for pwm mode */
enum ptc_pwm_num{
    PTC_PWM_NONE = -1,
	PTC_PWM_0 = 0,
	PTC_PWM_1,
	PTC_PWM_2,
	PTC_PWM_3,
	PTC_PWM_NUM,
};
/* end */

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

#define SET_SPI_GPIO(id,sdo,sdi,sclk,cs) {			\
	SET_GPIO_##sdo##_dout_spi##id##_pad_txd;		\
	SET_GPIO_##sdo##_doen_LOW;						\
	SET_GPIO_spi##id##_pad_rxd(sdi);				\
	SET_GPIO_##sdi##_doen_HIGH;						\
	SET_GPIO_##sclk##_dout_spi##id##_pad_sck_out;	\
	SET_GPIO_##sclk##_doen_LOW;						\
	SET_GPIO_##cs##_dout_spi##id##_pad_ss_0_n;		\
	SET_GPIO_##cs##_doen_LOW;						\
	}

#define INIT_FUNC_DEF(name) \
	static void _##name##_init(void)

#define INIT_FUNC_CALL(name)\
	_##name##_init()

struct sifive_gpio_regs *g_aloe_gpio = (struct sifive_gpio_regs *) SIFIVE_BASE_GPIO;

#if defined(CONFIG_VIC_BEAGLE_V)
static void *gpio_ctrl_base = NULL;

static void *get_gpio_ctrl_base(void)
{
	if (!gpio_ctrl_base) {
		uint32_t function;
		ulong FUNCTION_GPIO_CTRL_BASE[] = {
			syscon_iopad_ctrl_register0_REG_ADDR,   //_SET_SYSCON_REG_register0_SCFG_gpio_pad_ctrl_0
			syscon_iopad_ctrl_register0_REG_ADDR,   //_SET_SYSCON_REG_register0_SCFG_gpio_pad_ctrl_0
			syscon_iopad_ctrl_register68_REG_ADDR,  //_SET_SYSCON_REG_register68_SCFG_funcshare_pad_ctrl_36
			syscon_iopad_ctrl_register67_REG_ADDR,  //_SET_SYSCON_REG_register67_SCFG_funcshare_pad_ctrl_34
			syscon_iopad_ctrl_register32_REG_ADDR,  //_SET_SYSCON_REG_register32_SCFG_funcshare_pad_ctrl_0
			syscon_iopad_ctrl_register32_REG_ADDR,  //_SET_SYSCON_REG_register32_SCFG_funcshare_pad_ctrl_0
			syscon_iopad_ctrl_register32_REG_ADDR,  //_SET_SYSCON_REG_register32_SCFG_funcshare_pad_ctrl_0
		};

		_GET_SYSCON_REG_register104_SCFG_io_padshare_sel(function);
		gpio_ctrl_base = (void *)FUNCTION_GPIO_CTRL_BASE[function];
		debug("function: %d, gpio_ctrl_base: %p\n", function, gpio_ctrl_base);
	}
	return gpio_ctrl_base;
}
void sys_set_gpio_iocfg(int pad, uint16_t val)
{
	ulong reg_n = (ulong)(pad >> 1);
	void *reg_addr = get_gpio_ctrl_base() + (reg_n << 2);

	uint32_t reg_val_old = readl(reg_addr);
	uint32_t reg_val_new = reg_val_old;

	if (pad & 1) {
		reg_val_new &= ~(0xffff << 16);
		reg_val_new |= (uint32_t)val << 16;
	} else {
		reg_val_new &= ~(0xffff << 0);
		reg_val_new |= (uint32_t)val << 0;
	}

	if (reg_val_old != reg_val_new) {
		debug("set gpio%d iocfg(@%p): %08x -> %08x\n", pad, reg_addr, reg_val_old, reg_val_new);
		writel(reg_val_new, reg_addr);
	}
}

uint16_t sys_get_gpio_iocfg(int pad)
{
	ulong reg_n = (ulong)(pad >> 1);
	void *reg_addr = get_gpio_ctrl_base() + (reg_n << 2);
	uint32_t reg_val = readl(reg_addr);
	uint16_t iocfg = (reg_val >> ((pad & 1) ? 16 : 0)) & 0xffff;

	return iocfg;
}
static void sys_funcshare_io_input_en(void)
{
	uint32_t function;

	gpio_ctrl_base = 0;
	_GET_SYSCON_REG_register104_SCFG_io_padshare_sel(function);
	if (function != 0) {
		const uint16_t IO_INPUT_EN = BIT(7)|BIT(6); /* [7]input_enable | [6]schemit_input_enable */
		const int GPIO_NUM = 64;
		uint16_t io_cfg;
		int i;
		for (i = 0; i < GPIO_NUM; i++) {
			io_cfg = sys_get_gpio_iocfg(i);
			if ((io_cfg & IO_INPUT_EN) != IO_INPUT_EN) {
				debug("funcshare pad %d: input enable\n", i);
				sys_set_gpio_iocfg(i, io_cfg|IO_INPUT_EN);
			}
		}
	}
}
#endif

/* end */
INIT_FUNC_DEF(wave511)
{
    _ENABLE_CLOCK_clk_vdec_axi_;
    _ENABLE_CLOCK_clk_vdecbrg_mainclk_;
    _ENABLE_CLOCK_clk_vdec_bclk_;
    _ENABLE_CLOCK_clk_vdec_cclk_;
    _ENABLE_CLOCK_clk_vdec_apb_;

    _CLEAR_RESET_rstgen_rstn_vdecbrg_main_;
    _CLEAR_RESET_rstgen_rstn_vdec_axi_;
    _CLEAR_RESET_rstgen_rstn_vdec_bclk_;
    _CLEAR_RESET_rstgen_rstn_vdec_cclk_;
    _CLEAR_RESET_rstgen_rstn_vdec_apb_;
}

INIT_FUNC_DEF(gc300)
{
    _SET_SYSCON_REG_register20_u0_syscon_162_SCFG_gc300_csys_req(1);

    //nic and noc associate clk rst
    _ENABLE_CLOCK_clk_jpeg_axi_;
    _ENABLE_CLOCK_clk_jpcgc300_mainclk_;
    _ENABLE_CLOCK_clk_vdecbrg_mainclk_;

    udelay(2000);
    //gc300 clk and rst
    _ENABLE_CLOCK_clk_gc300_2x_;
    _ENABLE_CLOCK_clk_gc300_ahb_;
    _ENABLE_CLOCK_clk_gc300_axi_;

    _CLEAR_RESET_rstgen_rstn_gc300_2x_;
    _CLEAR_RESET_rstgen_rstn_gc300_axi_;
    _CLEAR_RESET_rstgen_rstn_gc300_ahb_;

    udelay(2000);
    //nic and noc associate clk rst;
    _CLEAR_RESET_rstgen_rstn_jpeg_axi_;
    _CLEAR_RESET_rstgen_rstn_jpcgc300_main_;
    _CLEAR_RESET_rstgen_rstn_vdecbrg_main_;
}

INIT_FUNC_DEF(codaj21)
{
    _ENABLE_CLOCK_clk_jpeg_axi_;
    _ENABLE_CLOCK_clk_jpeg_cclk_;
    _ENABLE_CLOCK_clk_jpeg_apb_;

    _CLEAR_RESET_rstgen_rstn_jpeg_axi_;
    _CLEAR_RESET_rstgen_rstn_jpeg_cclk_;
    _CLEAR_RESET_rstgen_rstn_jpeg_apb_;
}

INIT_FUNC_DEF(nvdla)
{
	_SET_SYSCON_REG_register16_SCFG_nbdla_clkgating_en(1);
	_ENABLE_CLOCK_clk_dla_bus_;
	_ENABLE_CLOCK_clk_dla_axi_;
	_ENABLE_CLOCK_clk_dlanoc_axi_;
	_ENABLE_CLOCK_clk_dla_apb_;
	_ENABLE_CLOCK_clk_nnenoc_axi_;
	_ENABLE_CLOCK_clk_dlaslv_axi_;

	_CLEAR_RESET_rstgen_rstn_dla_axi_;
	_CLEAR_RESET_rstgen_rstn_dlanoc_axi_;
	_CLEAR_RESET_rstgen_rstn_dla_apb_;
	_CLEAR_RESET_rstgen_rstn_nnenoc_axi_;
	_CLEAR_RESET_rstgen_rstn_dlaslv_axi_;
}

INIT_FUNC_DEF(wave521)
{
    _ENABLE_CLOCK_clk_venc_axi_;
    _ENABLE_CLOCK_clk_vencbrg_mainclk_;
    _ENABLE_CLOCK_clk_venc_bclk_;
    _ENABLE_CLOCK_clk_venc_cclk_;
    _ENABLE_CLOCK_clk_venc_apb_;

    _CLEAR_RESET_rstgen_rstn_venc_axi_;
    _CLEAR_RESET_rstgen_rstn_vencbrg_main_;
    _CLEAR_RESET_rstgen_rstn_venc_bclk_;
    _CLEAR_RESET_rstgen_rstn_venc_cclk_;
    _CLEAR_RESET_rstgen_rstn_venc_apb_;
}

INIT_FUNC_DEF(gmac)
{
	/*phy must use gpio to hardware reset*/
    _ENABLE_CLOCK_clk_gmac_ahb_;
    _ENABLE_CLOCK_clk_gmac_ptp_refclk_;
    _ENABLE_CLOCK_clk_gmac_gtxclk_;
    _ASSERT_RESET_rstgen_rstn_gmac_ahb_;

    _CLEAR_RESET_rstgen_rstn_gmac_ahb_;

#if defined(CONFIG_VIC_BEAGLE_V)
	_SET_SYSCON_REG_register89_SCFG_funcshare_pad_ctrl_57(0x00c30080);
	_SET_SYSCON_REG_register90_SCFG_funcshare_pad_ctrl_58(0x00030080);

	_SET_SYSCON_REG_register91_SCFG_funcshare_pad_ctrl_59(0x00030003);
	_SET_SYSCON_REG_register92_SCFG_funcshare_pad_ctrl_60(0x00030003);
	_SET_SYSCON_REG_register93_SCFG_funcshare_pad_ctrl_61(0x00030003);
	_SET_SYSCON_REG_register94_SCFG_funcshare_pad_ctrl_62(0x00030003);

	_SET_SYSCON_REG_register95_SCFG_funcshare_pad_ctrl_63(0x0c800003);

	_SET_SYSCON_REG_register96_SCFG_funcshare_pad_ctrl_64(0x008000c0);
	_SET_SYSCON_REG_register97_SCFG_funcshare_pad_ctrl_65(0x00c000c0);
	_SET_SYSCON_REG_register98_SCFG_funcshare_pad_ctrl_66(0x00c000c0);
	_SET_SYSCON_REG_register99_SCFG_funcshare_pad_ctrl_67(0x00c000c0);
	_SET_SYSCON_REG_register100_SCFG_funcshare_pad_ctrl_68(0x00c000c0);
	_SET_SYSCON_REG_register101_SCFG_funcshare_pad_ctrl_69(0x00c000c0);
	_SET_SYSCON_REG_register102_SCFG_funcshare_pad_ctrl_70(0x00c000c0);
#else
	_SET_SYSCON_REG_register89_SCFG_funcshare_pad_ctrl_57(0x00030080);
	_SET_SYSCON_REG_register90_SCFG_funcshare_pad_ctrl_58(0x00030080);

	_SET_SYSCON_REG_register91_SCFG_funcshare_pad_ctrl_59(0x00030003);
	_SET_SYSCON_REG_register92_SCFG_funcshare_pad_ctrl_60(0x00030003);
	_SET_SYSCON_REG_register93_SCFG_funcshare_pad_ctrl_61(0x00030003);
	_SET_SYSCON_REG_register94_SCFG_funcshare_pad_ctrl_62(0x00030003);

	_SET_SYSCON_REG_register95_SCFG_funcshare_pad_ctrl_63(0x00800003);

	_SET_SYSCON_REG_register96_SCFG_funcshare_pad_ctrl_64(0x00800080);
	_SET_SYSCON_REG_register97_SCFG_funcshare_pad_ctrl_65(0x00800080);
	_SET_SYSCON_REG_register98_SCFG_funcshare_pad_ctrl_66(0x00800080);
	_SET_SYSCON_REG_register99_SCFG_funcshare_pad_ctrl_67(0x00800080);
	_SET_SYSCON_REG_register100_SCFG_funcshare_pad_ctrl_68(0x00800080);
	_SET_SYSCON_REG_register101_SCFG_funcshare_pad_ctrl_69(0x00800080);
	_SET_SYSCON_REG_register102_SCFG_funcshare_pad_ctrl_70(0x00800080);
#endif

#if defined(CONFIG_VIC_EVB_V1)
	SET_GPIO_25_doen_LOW;
    SET_GPIO_25_dout_HIGH;
    udelay(1000);
    SET_GPIO_25_dout_LOW;
    udelay(1000);
    SET_GPIO_25_dout_HIGH;
#elif defined(CONFIG_VIC_BEAGLE_V)
	SET_GPIO_45_doen_LOW;
    SET_GPIO_45_dout_HIGH;
    udelay(1000);
    SET_GPIO_45_dout_LOW;
    udelay(1000);
    SET_GPIO_45_dout_HIGH;
#endif

	_SET_SYSCON_REG_register28_SCFG_gmac_phy_intf_sel(0x1);//rgmii

	_DIVIDE_CLOCK_clk_gmac_gtxclk_(4); //1000M clk

	_SET_SYSCON_REG_register49_SCFG_gmac_gtxclk_dlychain_sel(0x4);
}


INIT_FUNC_DEF(nne50)
{
    // fix nne50 ram scan fail issue
    _SWITCH_CLOCK_clk_nne_bus_SOURCE_clk_cpu_axi_;

    _ENABLE_CLOCK_clk_nne_ahb_;
    _ENABLE_CLOCK_clk_nne_axi_;
    _ENABLE_CLOCK_clk_nnenoc_axi_ ;
    _CLEAR_RESET_rstgen_rstn_nne_ahb_ ;
    _CLEAR_RESET_rstgen_rstn_nne_axi_ ;
    _CLEAR_RESET_rstgen_rstn_nnenoc_axi_ ;
}

INIT_FUNC_DEF(vp6)
{
    _ASSERT_RESET_rstgen_rst_vp6_DReset_;
    _ASSERT_RESET_rstgen_rst_vp6_Breset_;

    _ENABLE_CLOCK_clk_vp6_core_ ;
    _ENABLE_CLOCK_clk_vp6_axi_ ;
}

INIT_FUNC_DEF(noc)
{
}

/* disable, when we don't realy use it */
#if 0
INIT_FUNC_DEF(syscon)
{
}
#endif
INIT_FUNC_DEF(gpio)
{
	_ENABLE_CLOCK_clk_gpio_apb_;
	_CLEAR_RESET_rstgen_rstn_gpio_apb_;

}

INIT_FUNC_DEF(audio_subsys)
{
    _ENABLE_CLOCK_clk_audio_root_;
    _ENABLE_CLOCK_clk_audio_12288_;
    _ENABLE_CLOCK_clk_audio_src_;
    _ENABLE_CLOCK_clk_audio_12288_;
    _ENABLE_CLOCK_clk_dma1p_ahb_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_bus_;
    _CLEAR_RESET_audio_rst_gen_rstn_dma1p_ahb_;
}

INIT_FUNC_DEF(i2srx_3ch)
{
    _ENABLE_CLOCK_clk_adc_mclk_;
    _ENABLE_CLOCK_clk_apb_i2sadc_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2sadc_;
    _CLEAR_RESET_audio_rst_gen_rstn_i2sadc_srst_;
}

INIT_FUNC_DEF(pdm)
{
    _ENABLE_CLOCK_clk_apb_pdm_;
    _ENABLE_CLOCK_clk_pdm_mclk_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_pdm_;
}

INIT_FUNC_DEF(i2svad)
{
    _ENABLE_CLOCK_clk_apb_i2svad_ ;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2svad_ ;
    _CLEAR_RESET_audio_rst_gen_rstn_i2svad_srst_ ;
}

INIT_FUNC_DEF(spdif)
{
    _ENABLE_CLOCK_clk_spdif_;
    _ENABLE_CLOCK_clk_apb_spdif_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_spdif_;
}

INIT_FUNC_DEF(pwmdac)
{
    _ENABLE_CLOCK_clk_apb_pwmdac_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_pwmdac_;
}

INIT_FUNC_DEF(i2sdac0)
{
    _ENABLE_CLOCK_clk_dac_mclk_;
    _ENABLE_CLOCK_clk_apb_i2sdac_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2sdac_;
    _CLEAR_RESET_audio_rst_gen_rstn_i2sdac_srst_;
}

INIT_FUNC_DEF(i2sdac1)
{
    _ENABLE_CLOCK_clk_i2s1_mclk_;
    _ENABLE_CLOCK_clk_apb_i2s1_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2s1_;
    _CLEAR_RESET_audio_rst_gen_rstn_i2s1_srst_;
}

INIT_FUNC_DEF(i2sdac16k)
{
    _ENABLE_CLOCK_clk_apb_i2sdac16k_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2sdac16k_;
    _CLEAR_RESET_audio_rst_gen_rstn_i2sdac16k_srst_;
}

INIT_FUNC_DEF(usb)
{
#if !defined(CONFIG_VIC_BEAGLE_V)
    uint32_t read_v=MA_INW(gpioen_REG_ADDR + 0x48);
#endif

    _ENABLE_CLOCK_clk_usb_axi_;
    _ENABLE_CLOCK_clk_usbphy_125m_;
    _ENABLE_CLOCK_clk_usb_lpm_clk_predft_;
    _ENABLE_CLOCK_clk_usb_stb_clk_predft_;
    _ENABLE_CLOCK_clk_apb_usb_;

    _CLEAR_RESET_rstgen_rstn_usb_axi_;
    _CLEAR_RESET_audio_rst_gen_rstn_apb_usb_;
    _CLEAR_RESET_audio_rst_gen_rst_axi_usb_;
    _CLEAR_RESET_audio_rst_gen_rst_usb_pwrup_rst_n_;
    _CLEAR_RESET_audio_rst_gen_rst_usb_PONRST_;

    /* for host */
    SET_GPIO_usb_over_current(-1);

#if defined(CONFIG_VIC_BEAGLE_V)
	/* config strap */
	_SET_SYSCON_REG_SCFG_usb0_mode_strap(0x2);
	_SET_SYSCON_REG_SCFG_usb7_PLL_EN(0x1);
	_SET_SYSCON_REG_SCFG_usb7_U3_EQ_EN(0x1);
	_SET_SYSCON_REG_SCFG_usb7_U3_SSRX_SEL(0x1);
	_SET_SYSCON_REG_SCFG_usb7_U3_SSTX_SEL(0x1);
	_SET_SYSCON_REG_SCFG_usb3_utmi_iddig(0x1);
#else
    if(!((read_v >> 22) & 0x1)) {
        /* config strap */
        _SET_SYSCON_REG_SCFG_usb0_mode_strap(0x2);
        _SET_SYSCON_REG_SCFG_usb7_PLL_EN(0x1);

        _SET_SYSCON_REG_SCFG_usb7_U3_EQ_EN(0x1);
        _SET_SYSCON_REG_SCFG_usb7_U3_SSRX_SEL(0x1);
        _SET_SYSCON_REG_SCFG_usb7_U3_SSTX_SEL(0x1);

        _SET_SYSCON_REG_SCFG_usb3_utmi_iddig(0x1);
    }
#endif
}

INIT_FUNC_DEF(sgdma1p)
{
    _ENABLE_CLOCK_clk_sgdma1p_axi_;
    _CLEAR_RESET_rstgen_rstn_sgdma1p_axi_;
}

/* disable, when we don't realy use it */
#if 0
INIT_FUNC_DEF(qspi)
{
    _ENABLE_CLOCK_clk_qspi_ahb_;
    _ENABLE_CLOCK_clk_qspi_apb_;
    _ENABLE_CLOCK_clk_qspi_refclk_;

    _CLEAR_RESET_rstgen_rstn_qspi_ahb_;
    _CLEAR_RESET_rstgen_rstn_qspi_core_;
    _CLEAR_RESET_rstgen_rstn_qspi_apb_;
}
#endif
INIT_FUNC_DEF(sgdma2p)
{
    _ENABLE_CLOCK_clk_dma2pnoc_axi_;
    _ENABLE_CLOCK_clk_sgdma2p_axi_;
    _ENABLE_CLOCK_clk_sgdma2p_ahb_;

    _CLEAR_RESET_rstgen_rstn_sgdma2p_ahb_;
    _CLEAR_RESET_rstgen_rstn_sgdma2p_axi_;
    _CLEAR_RESET_rstgen_rstn_dma2pnoc_aix_;
}

INIT_FUNC_DEF(sdio0)
{
#if defined(CONFIG_VIC_BEAGLE_V)
    _ENABLE_CLOCK_clk_sdio0_ahb_;
    _ENABLE_CLOCK_clk_sdio0_cclkint_;

    _CLEAR_RESET_rstgen_rstn_sdio0_ahb_;

	SET_GPIO_sdio0_pad_card_detect_n(55);
	SET_GPIO_55_doen_HIGH;

	SET_GPIO_54_dout_sdio0_pad_cclk_out;
	SET_GPIO_54_doen_LOW;

	SET_GPIO_53_doen_reverse_(1);
	SET_GPIO_53_doen_sdio0_pad_ccmd_oe;
	SET_GPIO_53_dout_sdio0_pad_ccmd_out;
	SET_GPIO_sdio0_pad_ccmd_in(53);

    _SET_SYSCON_REG_register58_SCFG_funcshare_pad_ctrl_26(0x00c000c0);

	SET_GPIO_49_doen_reverse_(1);
	SET_GPIO_50_doen_reverse_(1);
	SET_GPIO_51_doen_reverse_(1);
	SET_GPIO_52_doen_reverse_(1);

	SET_GPIO_49_doen_sdio0_pad_cdata_oe_bit0;
	SET_GPIO_49_dout_sdio0_pad_cdata_out_bit0;
	SET_GPIO_sdio0_pad_cdata_in_bit0(49);
    _SET_SYSCON_REG_register56_SCFG_funcshare_pad_ctrl_24(0x00c000c0);

	SET_GPIO_50_doen_sdio0_pad_cdata_oe_bit1;
	SET_GPIO_50_dout_sdio0_pad_cdata_out_bit1;
	SET_GPIO_sdio0_pad_cdata_in_bit1(50);

	SET_GPIO_51_doen_sdio0_pad_cdata_oe_bit2;
	SET_GPIO_51_dout_sdio0_pad_cdata_out_bit2;
	SET_GPIO_sdio0_pad_cdata_in_bit2(51);

    _SET_SYSCON_REG_register57_SCFG_funcshare_pad_ctrl_25(0x00c000c0);

	SET_GPIO_52_doen_sdio0_pad_cdata_oe_bit3;
	SET_GPIO_52_dout_sdio0_pad_cdata_out_bit3;
	SET_GPIO_sdio0_pad_cdata_in_bit3(52);
    _SET_SYSCON_REG_register58_SCFG_funcshare_pad_ctrl_26(0x00c000c0);

#if 0//wifi module
	SET_GPIO_sdio0_pad_card_detect_n(55);
	SET_GPIO_55_doen_HIGH;

	SET_GPIO_33_dout_sdio0_pad_cclk_out;
	SET_GPIO_33_doen_LOW;

	SET_GPIO_29_doen_reverse_(1);
	SET_GPIO_29_doen_sdio0_pad_ccmd_oe;
	SET_GPIO_29_dout_sdio0_pad_ccmd_out;
	SET_GPIO_sdio0_pad_ccmd_in(29);


	SET_GPIO_36_doen_reverse_(1);
	SET_GPIO_30_doen_reverse_(1);
	SET_GPIO_34_doen_reverse_(1);
	SET_GPIO_31_doen_reverse_(1);

	SET_GPIO_36_doen_sdio0_pad_cdata_oe_bit0;
	SET_GPIO_36_dout_sdio0_pad_cdata_out_bit0;
	SET_GPIO_sdio0_pad_cdata_in_bit0(36);


	SET_GPIO_30_doen_sdio0_pad_cdata_oe_bit1;
	SET_GPIO_30_dout_sdio0_pad_cdata_out_bit1;
	SET_GPIO_sdio0_pad_cdata_in_bit1(30);

	SET_GPIO_34_doen_sdio0_pad_cdata_oe_bit2;
	SET_GPIO_34_dout_sdio0_pad_cdata_out_bit2;
	SET_GPIO_sdio0_pad_cdata_in_bit2(34);



	SET_GPIO_31_doen_sdio0_pad_cdata_oe_bit3;
	SET_GPIO_31_dout_sdio0_pad_cdata_out_bit3;
	SET_GPIO_sdio0_pad_cdata_in_bit3(31);



    SET_GPIO_37_doen_LOW;
    SET_GPIO_37_dout_HIGH;
    udelay(5000);
    SET_GPIO_37_dout_LOW;
    udelay(5000);
    SET_GPIO_37_dout_HIGH;
#endif

#else
	SET_GPIO_sdio0_pad_card_detect_n(26);
	SET_GPIO_26_doen_HIGH;

	SET_GPIO_33_dout_sdio0_pad_cclk_out;
	SET_GPIO_33_doen_LOW;

	SET_GPIO_34_doen_reverse_(1);
	SET_GPIO_34_doen_sdio0_pad_ccmd_oe;
	SET_GPIO_34_dout_sdio0_pad_ccmd_out;
	SET_GPIO_sdio0_pad_ccmd_in(34);

	SET_GPIO_32_doen_reverse_(1);
	SET_GPIO_31_doen_reverse_(1);
	SET_GPIO_30_doen_reverse_(1);
	SET_GPIO_36_doen_reverse_(1);

	SET_GPIO_32_doen_sdio0_pad_cdata_oe_bit0;
	SET_GPIO_32_dout_sdio0_pad_cdata_out_bit0;
	SET_GPIO_sdio0_pad_cdata_in_bit0(32);

	SET_GPIO_31_doen_sdio0_pad_cdata_oe_bit1;
	SET_GPIO_31_dout_sdio0_pad_cdata_out_bit1;
	SET_GPIO_sdio0_pad_cdata_in_bit1(31);

	SET_GPIO_30_doen_sdio0_pad_cdata_oe_bit2;
	SET_GPIO_30_dout_sdio0_pad_cdata_out_bit2;
	SET_GPIO_sdio0_pad_cdata_in_bit2(30);

	SET_GPIO_36_doen_sdio0_pad_cdata_oe_bit3;
	SET_GPIO_36_dout_sdio0_pad_cdata_out_bit3;
	SET_GPIO_sdio0_pad_cdata_in_bit3(36);
#endif
}

INIT_FUNC_DEF(sdio1)
{
    _ENABLE_CLOCK_clk_sdio1_ahb_;
    _ENABLE_CLOCK_clk_sdio1_cclkint_;

    _CLEAR_RESET_rstgen_rstn_sdio1_ahb_;

#if defined(CONFIG_VIC_BEAGLE_V)
	SET_GPIO_33_dout_sdio1_pad_cclk_out;
	SET_GPIO_33_doen_LOW;

	SET_GPIO_29_doen_reverse_(1);
	SET_GPIO_29_doen_sdio1_pad_ccmd_oe;
	SET_GPIO_29_dout_sdio1_pad_ccmd_out;
	SET_GPIO_sdio1_pad_ccmd_in(29);

	SET_GPIO_36_doen_reverse_(1);
	SET_GPIO_30_doen_reverse_(1);
	SET_GPIO_34_doen_reverse_(1);
	SET_GPIO_31_doen_reverse_(1);

	SET_GPIO_36_doen_sdio1_pad_cdata_oe_bit0;
	SET_GPIO_36_dout_sdio1_pad_cdata_out_bit0;
	SET_GPIO_sdio1_pad_cdata_in_bit0(36);

	SET_GPIO_30_doen_sdio1_pad_cdata_oe_bit1;
	SET_GPIO_30_dout_sdio1_pad_cdata_out_bit1;
	SET_GPIO_sdio1_pad_cdata_in_bit1(30);

	SET_GPIO_34_doen_sdio1_pad_cdata_oe_bit2;
	SET_GPIO_34_dout_sdio1_pad_cdata_out_bit2;
	SET_GPIO_sdio1_pad_cdata_in_bit2(34);

	SET_GPIO_31_doen_sdio1_pad_cdata_oe_bit3;
	SET_GPIO_31_dout_sdio1_pad_cdata_out_bit3;
	SET_GPIO_sdio1_pad_cdata_in_bit3(31);

    SET_GPIO_37_doen_LOW;
    SET_GPIO_37_dout_HIGH;
    udelay(5000);
    SET_GPIO_37_dout_LOW;
    udelay(5000);
    SET_GPIO_37_dout_HIGH;
#endif
}

INIT_FUNC_DEF(spi2ahb)
{
    _ENABLE_CLOCK_clk_spi2ahb_ahb_;
    _ENABLE_CLOCK_clk_spi2ahb_core_;

    _CLEAR_RESET_rstgen_rstn_spi2ahb_ahb_;
    _CLEAR_RESET_rstgen_rstn_spi2ahb_core_;
}

INIT_FUNC_DEF(ezmaster)
{
    _ENABLE_CLOCK_clk_ezmaster_ahb_;
    _CLEAR_RESET_rstgen_rstn_ezmaster_ahb_;
}

INIT_FUNC_DEF(secengine)
{
    _ENABLE_CLOCK_clk_sec_ahb_;
    _ENABLE_CLOCK_clk_aes_clk_;
    _ENABLE_CLOCK_clk_sha_clk_;
    _ENABLE_CLOCK_clk_pka_clk_;

    _CLEAR_RESET_rstgen_rstn_sec_ahb_;
    _CLEAR_RESET_rstgen_rstn_aes_;
    _CLEAR_RESET_rstgen_rstn_pka_;
    _CLEAR_RESET_rstgen_rstn_sha_;
}

INIT_FUNC_DEF(uart0)
{
    _ENABLE_CLOCK_clk_uart0_apb_;
    _ENABLE_CLOCK_clk_uart0_core_;

    _CLEAR_RESET_rstgen_rstn_uart0_apb_;
    _CLEAR_RESET_rstgen_rstn_uart0_core_;

#if defined(CONFIG_VIC_BEAGLE_V)
    SET_GPIO_uart0_pad_sin(40);
    SET_GPIO_40_doen_HIGH;
    SET_GPIO_41_dout_uart0_pad_sout;
    SET_GPIO_41_doen_LOW;

    SET_GPIO_42_dout_uart0_pad_rtsn;
    SET_GPIO_42_doen_LOW;
    SET_GPIO_uart0_pad_ctsn(39);
    SET_GPIO_39_doen_HIGH;

    SET_GPIO_35_doen_LOW;
    SET_GPIO_35_dout_HIGH;
#elif defined(CONFIG_VIC_EVB_V1)
    SET_GPIO_uart0_pad_sin(5);
    SET_GPIO_5_doen_HIGH;
    SET_GPIO_6_dout_uart0_pad_sout;
    SET_GPIO_6_doen_LOW;

    SET_GPIO_8_dout_uart0_pad_rtsn;
    SET_GPIO_8_doen_LOW;
    SET_GPIO_uart0_pad_ctsn(7);
    SET_GPIO_7_doen_HIGH;
#endif

}
#if defined(CONFIG_VIC_EVB_V1)
INIT_FUNC_DEF(uart1)
{
    _ENABLE_CLOCK_clk_uart1_apb_;
    _ENABLE_CLOCK_clk_uart1_core_;

    _CLEAR_RESET_rstgen_rstn_uart1_apb_;
    _CLEAR_RESET_rstgen_rstn_uart1_core_;

    SET_GPIO_uart1_pad_sin(9);
    SET_GPIO_9_doen_HIGH;
    SET_GPIO_10_dout_uart1_pad_sout;
    SET_GPIO_10_doen_LOW;
}
#endif

INIT_FUNC_DEF(spi0)
{
    _ENABLE_CLOCK_clk_spi0_apb_;
    _ENABLE_CLOCK_clk_spi0_core_;

    _CLEAR_RESET_rstgen_rstn_spi0_apb_;
    _CLEAR_RESET_rstgen_rstn_spi0_core_;
}

INIT_FUNC_DEF(spi1)
{
    _ENABLE_CLOCK_clk_spi1_apb_;
    _ENABLE_CLOCK_clk_spi1_core_;

    _CLEAR_RESET_rstgen_rstn_spi1_apb_;
    _CLEAR_RESET_rstgen_rstn_spi1_core_;
}

INIT_FUNC_DEF(i2c0)
{
    _ENABLE_CLOCK_clk_i2c0_apb_;
    _ENABLE_CLOCK_clk_i2c0_core_;

    _CLEAR_RESET_rstgen_rstn_i2c0_apb_;
    _CLEAR_RESET_rstgen_rstn_i2c0_core_;

#if defined(CONFIG_VIC_BEAGLE_V)
	SET_GPIO_62_dout_LOW;
	SET_GPIO_61_dout_LOW;

	SET_GPIO_62_doen_reverse_(1);
	SET_GPIO_61_doen_reverse_(1);

	SET_GPIO_62_doen_i2c0_pad_sck_oe;
	SET_GPIO_61_doen_i2c0_pad_sda_oe;

	SET_GPIO_i2c0_pad_sck_in(62);
	SET_GPIO_i2c0_pad_sda_in(61);
#elif defined(CONFIG_VIC_EVB_V1)
	SET_GPIO_16_dout_LOW;
	SET_GPIO_17_dout_LOW;

	SET_GPIO_16_doen_reverse_(1);
	SET_GPIO_17_doen_reverse_(1);

	SET_GPIO_16_doen_i2c0_pad_sck_oe;
	SET_GPIO_17_doen_i2c0_pad_sda_oe;

	SET_GPIO_i2c0_pad_sck_in(16);
	SET_GPIO_i2c0_pad_sda_in(17);
#endif

}

INIT_FUNC_DEF(i2c1)
{
    _ENABLE_CLOCK_clk_i2c1_apb_;
    _ENABLE_CLOCK_clk_i2c1_core_;

    _CLEAR_RESET_rstgen_rstn_i2c1_apb_;
    _CLEAR_RESET_rstgen_rstn_i2c1_core_;
#if defined(CONFIG_VIC_BEAGLE_V)
	SET_GPIO_47_dout_LOW;
	SET_GPIO_48_dout_LOW;

	SET_GPIO_47_doen_reverse_(1);
	SET_GPIO_48_doen_reverse_(1);

	SET_GPIO_47_doen_i2c1_pad_sck_oe;
	SET_GPIO_48_doen_i2c1_pad_sda_oe;

	SET_GPIO_i2c1_pad_sck_in(47);
	SET_GPIO_i2c1_pad_sda_in(48);
#elif defined(CONFIG_VIC_EVB_V1)
	SET_GPIO_18_dout_LOW;
	SET_GPIO_19_dout_LOW;

	SET_GPIO_18_doen_reverse_(1);
	SET_GPIO_19_doen_reverse_(1);

	SET_GPIO_18_doen_i2c1_pad_sck_oe;
	SET_GPIO_19_doen_i2c1_pad_sda_oe;

	SET_GPIO_i2c1_pad_sck_in(18);
	SET_GPIO_i2c1_pad_sda_in(19);
#endif
}

INIT_FUNC_DEF(trng)
{
    _ENABLE_CLOCK_clk_trng_apb_;
    _CLEAR_RESET_rstgen_rstn_trng_apb_;
}

INIT_FUNC_DEF(otp)
{
    _ENABLE_CLOCK_clk_otp_apb_;
    _CLEAR_RESET_rstgen_rstn_otp_apb_;
}

INIT_FUNC_DEF(vp6_intc)
{
    _ENABLE_CLOCK_clk_vp6intc_apb_;
    _CLEAR_RESET_rstgen_rstn_vp6intc_apb_;
}

INIT_FUNC_DEF(spi2)
{
    _ENABLE_CLOCK_clk_spi2_apb_;
    _ENABLE_CLOCK_clk_spi2_core_;
	_ASSERT_RESET_rstgen_rstn_spi2_core_;
	_ASSERT_RESET_rstgen_rstn_spi2_apb_;

    _CLEAR_RESET_rstgen_rstn_spi2_apb_;
    _CLEAR_RESET_rstgen_rstn_spi2_core_;
	/* Modifying the GPIO interface of SPI2 */
	SET_SPI_GPIO(2, 11, 12, 18, 19);
}

INIT_FUNC_DEF(spi3)
{
    _ENABLE_CLOCK_clk_spi3_apb_;
    _ENABLE_CLOCK_clk_spi3_core_;

    _CLEAR_RESET_rstgen_rstn_spi3_apb_;
    _CLEAR_RESET_rstgen_rstn_spi3_core_;
}
#if 0
INIT_FUNC_DEF(uart2)
{
    _ENABLE_CLOCK_clk_uart2_apb_;
    _ENABLE_CLOCK_clk_uart2_core_;

    _CLEAR_RESET_rstgen_rstn_uart2_apb_;
    _CLEAR_RESET_rstgen_rstn_uart2_core_;
}
/* disable, when we don't realy use it */

INIT_FUNC_DEF(uart3)
{
    _ENABLE_CLOCK_clk_uart3_apb_;
    _ENABLE_CLOCK_clk_uart3_core_;

    _CLEAR_RESET_rstgen_rstn_uart3_apb_;
    _CLEAR_RESET_rstgen_rstn_uart3_core_;
}
#endif

INIT_FUNC_DEF(i2c2)
{
    _ENABLE_CLOCK_clk_i2c2_apb_;
    _ENABLE_CLOCK_clk_i2c2_core_;

    _CLEAR_RESET_rstgen_rstn_i2c2_apb_;
    _CLEAR_RESET_rstgen_rstn_i2c2_core_;
#if defined(CONFIG_VIC_BEAGLE_V)
	SET_GPIO_60_dout_LOW;
	SET_GPIO_59_dout_LOW;

	SET_GPIO_60_doen_reverse_(1);
	SET_GPIO_59_doen_reverse_(1);

	SET_GPIO_60_doen_i2c2_pad_sck_oe;
	SET_GPIO_59_doen_i2c2_pad_sda_oe;

	SET_GPIO_i2c2_pad_sck_in(60);
	SET_GPIO_i2c2_pad_sda_in(59);
#endif
}

INIT_FUNC_DEF(i2c3)
{
    _ENABLE_CLOCK_clk_i2c3_apb_;
    _ENABLE_CLOCK_clk_i2c3_core_;

    _CLEAR_RESET_rstgen_rstn_i2c3_apb_;
    _CLEAR_RESET_rstgen_rstn_i2c3_core_;
}

/* disable, when we don't realy use it */
#if 0
INIT_FUNC_DEF(wdt)
{
    _ENABLE_CLOCK_clk_wdtimer_apb_;
    _ENABLE_CLOCK_clk_wdt_coreclk_;

    _ASSERT_RESET_rstgen_rstn_wdtimer_apb_;
    _ASSERT_RESET_rstgen_rstn_wdt_;

    _CLEAR_RESET_rstgen_rstn_wdtimer_apb_;
    _CLEAR_RESET_rstgen_rstn_wdt_;
}
#endif
/* added by chenjieqin for ptc on 20200824 */
INIT_FUNC_DEF(ptc)
{
	/* reset clock */
	ptc_reset_clock();

	/* reset cnt */
	ptc_reset();
}


INIT_FUNC_DEF(vout_subsys)
{
    _ENABLE_CLOCK_clk_vout_src_ ;
    _ENABLE_CLOCK_clk_disp_axi_;
    _ENABLE_CLOCK_clk_dispnoc_axi_ ;

    _CLEAR_RESET_rstgen_rstn_vout_src_ ;
    _CLEAR_RESET_rstgen_rstn_disp_axi_ ;
    _CLEAR_RESET_rstgen_rstn_dispnoc_axi_ ;

    _ENABLE_CLOCK_clk_vout_apb_ ;
    _ENABLE_CLOCK_clk_mapconv_apb_ ;
    _ENABLE_CLOCK_clk_mapconv_axi_ ;
    _ENABLE_CLOCK_clk_disp0_axi_ ;
    _ENABLE_CLOCK_clk_disp1_axi_ ;
    _ENABLE_CLOCK_clk_lcdc_oclk_ ;
    _ENABLE_CLOCK_clk_lcdc_axi_ ;
    _ENABLE_CLOCK_clk_vpp0_axi_ ;
    _ENABLE_CLOCK_clk_vpp1_axi_ ;
    _ENABLE_CLOCK_clk_vpp2_axi_ ;
    _ENABLE_CLOCK_clk_pixrawout_apb_ ;
    _ENABLE_CLOCK_clk_pixrawout_axi_ ;
    _ENABLE_CLOCK_clk_csi2tx_strm0_pixclk_ ;
    _ENABLE_CLOCK_clk_csi2tx_strm0_apb_ ;
    _ENABLE_CLOCK_clk_dsi_apb_ ;
    _ENABLE_CLOCK_clk_dsi_sys_clk_ ;
    _ENABLE_CLOCK_clk_ppi_tx_esc_clk_ ;

    _CLEAR_RESET_vout_sys_rstgen_rstn_mapconv_apb_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_mapconv_axi_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_disp0_axi_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_disp1_axi_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_lcdc_oclk_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_lcdc_axi_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_vpp0_axi_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_vpp1_axi_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_vpp2_axi_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_pixrawout_apb_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_pixrawout_axi_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_csi2tx_strm0_apb_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_csi2tx_strm0_pix_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_csi2tx_ppi_tx_esc_ ;

    //_CLEAR_RESET_vout_sys_rstgen_rstn_csi2tx_ppi_txbyte_hs_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_apb_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_sys_ ;
    //TODO:confirm these register
    //_CLEAR_RESET_vout_sys_rstgen_rstn_dsi_dpi_pix_ ;
    //_CLEAR_RESET_vout_sys_rstgen_rstn_dsi_ppi_txbyte_hs_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_ppi_tx_esc_ ;
    _CLEAR_RESET_vout_sys_rstgen_rstn_dsi_ppi_rx_esc_ ;
}

INIT_FUNC_DEF(tmp_sensor)
{
	_DISABLE_CLOCK_clk_temp_apb_;
	_ASSERT_RESET_rstgen_rstn_temp_apb_;
	_DISABLE_CLOCK_clk_temp_sense_;
	_ASSERT_RESET_rstgen_rstn_temp_sense_;

	_ENABLE_CLOCK_clk_temp_apb_;
	_CLEAR_RESET_rstgen_rstn_temp_apb_;
	_ENABLE_CLOCK_clk_temp_sense_;
	_CLEAR_RESET_rstgen_rstn_temp_sense_;
}

INIT_FUNC_DEF(lcdc)
{

}

INIT_FUNC_DEF(pixrawout)
{

}

INIT_FUNC_DEF(vpp0)
{

}

INIT_FUNC_DEF(vpp1)
{

}

INIT_FUNC_DEF(vpp2)
{

}

INIT_FUNC_DEF(map_conv)
{

}

INIT_FUNC_DEF(csi2tx)
{

}
INIT_FUNC_DEF(dsitx)
{

}

/*init system GPIO*/
int board_hw_init(void)
{
#if defined(CONFIG_VIC_BEAGLE_V)
	sys_funcshare_io_input_en();
#endif
	INIT_FUNC_CALL(wave511);
	INIT_FUNC_CALL(gc300);
	INIT_FUNC_CALL(codaj21);
	INIT_FUNC_CALL(nvdla);
	INIT_FUNC_CALL(wave521);
	INIT_FUNC_CALL(gmac);
	INIT_FUNC_CALL(nne50);
	INIT_FUNC_CALL(vp6);
	INIT_FUNC_CALL(noc);
//	INIT_FUNC_CALL(syscon);
	INIT_FUNC_CALL(gpio);
	INIT_FUNC_CALL(audio_subsys);
	INIT_FUNC_CALL(i2srx_3ch);
	INIT_FUNC_CALL(pdm);
	INIT_FUNC_CALL(i2svad);
	INIT_FUNC_CALL(spdif);
	INIT_FUNC_CALL(pwmdac);
	INIT_FUNC_CALL(i2sdac0);
	INIT_FUNC_CALL(i2sdac1);
	INIT_FUNC_CALL(i2sdac16k);
	INIT_FUNC_CALL(usb);
	INIT_FUNC_CALL(sgdma1p);
//	INIT_FUNC_CALL(qspi);
	INIT_FUNC_CALL(sgdma2p);
	INIT_FUNC_CALL(sdio0);
	INIT_FUNC_CALL(sdio1);
	INIT_FUNC_CALL(spi2ahb);
	INIT_FUNC_CALL(ezmaster);
	INIT_FUNC_CALL(secengine);
	INIT_FUNC_CALL(uart0);
#if defined(CONFIG_VIC_EVB_V1)
	INIT_FUNC_CALL(uart1);
#endif
	INIT_FUNC_CALL(spi0);
	INIT_FUNC_CALL(spi1);
	INIT_FUNC_CALL(i2c0);
	INIT_FUNC_CALL(i2c1);
	INIT_FUNC_CALL(trng);
	INIT_FUNC_CALL(otp);
	INIT_FUNC_CALL(vp6_intc); /*include intc0 and intc1*/
	INIT_FUNC_CALL(spi2);
	INIT_FUNC_CALL(spi3);
//	INIT_FUNC_CALL(uart2);
//	INIT_FUNC_CALL(uart3);
	INIT_FUNC_CALL(i2c2);
	INIT_FUNC_CALL(i2c3);
//	INIT_FUNC_CALL(wdt);
	INIT_FUNC_CALL(ptc);

	/** Video Output Subsystem **/
	INIT_FUNC_CALL(vout_subsys);
	INIT_FUNC_CALL(lcdc);
	INIT_FUNC_CALL(pixrawout);
	INIT_FUNC_CALL(vpp0);
	INIT_FUNC_CALL(vpp1);
	INIT_FUNC_CALL(vpp2);
	INIT_FUNC_CALL(map_conv);
	INIT_FUNC_CALL(csi2tx);
	INIT_FUNC_CALL(dsitx);
	INIT_FUNC_CALL(tmp_sensor);

	return 0;
}

/*
 * Miscellaneous platform dependent initializations
 */

int board_init(void)
{
	gd->bd->bi_boot_params = PHYS_SDRAM_0;

	return 0;
}

void reset_phy(void)
{
//    volatile uint32_t loop;

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
    g_aloe_gpio->OUTPUT_EN  |= 0x00001000ul;  /* Configure pin 12 as an output */
    g_aloe_gpio->OUTPUT_VAL &= 0x0000EFFFul;  /* Clear pin 12 to reset PHY */
    udelay(1000);
    g_aloe_gpio->OUTPUT_VAL  |= 0x00001000ul; /* Take PHY^ out of reset */
    udelay(1000);
    g_aloe_gpio->OUTPUT_VAL &= 0x0000EFFFul;  /* Second reset pulse */
    udelay(1000);
    g_aloe_gpio->OUTPUT_VAL  |= 0x00001000ul; /* Out of reset once more */

    /* Need at least 15mS delay before accessing PHY after reset... */
    udelay(15000);

}

/* This define is a value used for error/unknown serial. If we really care about distinguishing errors and 0 is valid, we'll need a different one. */
#define ERROR_READING_SERIAL_NUMBER        0

#ifdef CONFIG_MISC_INIT_R
static u32 setup_serialnum(void);
static void setup_macaddr(u32 serialnum);

int misc_init_r(void)
{
	if (!env_get("serial#")) {
		u32 serialnum = setup_serialnum();
		setup_macaddr(serialnum);
	}
	return 0;
}
#endif

#ifdef CONFIG_CMD_NET
int board_eth_init(struct bd_info *bis)
{
	int ret = 0;

#if defined(CONFIG_ETH_DESIGNWARE)
	u32 interface = PHY_INTERFACE_MODE_RGMII_TXID;
	if (designware_initialize(SIFIVE_BASE_ETHERNET, interface) >= 0)
		ret++;
#endif
	return ret;
}
#endif

ulong board_flash_get_legacy(ulong base, int banknum, flash_info_t *info)
{
	return 0;
}

/*void *board_fdt_blob_setup(void)
{
	void **ptr = (void *)CONFIG_SYS_SDRAM_BASE;
	if (fdt_magic(*ptr) == FDT_MAGIC)
			return (void *)*ptr;

	return (void *)CONFIG_SYS_FDT_BASE;
}*/

#if CONFIG_IS_ENABLED(SIFIVE_OTP)
static u32 otp_read_serialnum(struct udevice *dev)
{
	u32 serial[2] = {0};
	int ret;
	for (int i = 0xfe * 4; i > 0; i -= 8) {
		ret = misc_read(dev, i, serial, sizeof(serial));
		if (ret) {
			printf("%s: error reading serial from OTP\n", __func__);
			break;
		}
		if (serial[0] == ~serial[1])
			return serial[0];
	}
	return ERROR_READING_SERIAL_NUMBER;
}
#endif

static u32 setup_serialnum(void)
{
	u32 serial = ERROR_READING_SERIAL_NUMBER;

#if CONFIG_IS_ENABLED(SIFIVE_OTP)
	char serial_str[6];
	struct udevice *dev;
	int ret;

	// init OTP
	ret = uclass_get_device_by_driver(UCLASS_MISC, DM_GET_DRIVER(hifive_otp), &dev);
	if (ret) {
		debug("%s: could not find otp device\n", __func__);
		return serial;
	}

	// read serial from OTP and set env var
	serial = otp_read_serialnum(dev);
	snprintf(serial_str, sizeof(serial_str), "%05"PRIu32, serial);
	env_set("serial#", serial_str);
#endif

	return serial;
}

static void setup_macaddr(u32 serialnum) {
	// OR the serial into the MAC -- see SiFive FSBL
	unsigned char mac[6] = {0x66,0x34,0xb0,0x6c,0xde,0xad };
	mac[5] |= (serialnum >>  0) & 0xff;
	mac[4] |= (serialnum >>  8) & 0xff;
	mac[3] |= (serialnum >> 16) & 0xff;
	eth_env_set_enetaddr("ethaddr", mac);
}

void reset_misc(void)
{
	// reset beagelV by GPIO63
	printf("Resetting BeagelV......\n");
	SET_GPIO_63_doen_LOW;
	SET_GPIO_63_dout_HIGH;
}
