/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#ifndef _SFC_JH_MODULE_RESET_CLKGEN_H
#define _SFC_JH_MODULE_RESET_CLKGEN_H

#include <asm/arch/jh_iopad.h>

#define jh_ptc_pwm_reset_clk_enable {   \
    _DISABLE_CLOCK_clk_pwm_apb_; \
    _ASSERT_RESET_rstgen_rstn_pwm_apb_;  \
    _ENABLE_CLOCK_clk_pwm_apb_; \
    _CLEAR_RESET_rstgen_rstn_pwm_apb_;  \
}

#define jh_ptc_pwm_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_pwm_apb_; \
    _ASSERT_RESET_rstgen_rstn_pwm_apb_;  \
}

/* pwmdac reset and clkgen */
#define jh_pwmdac_reset_clk_enable { \
    _ENABLE_CLOCK_clk_apb_pwmdac_;  \
    _ENABLE_CLOCK_clk_dac_mclk_;    \
    _SWITCH_CLOCK_clk_dac_mclk_SOURCE_clk_audio_12288_; \
    _DIVIDE_CLOCK_clk_dac_mclk_(3); \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_pwmdac_;    \
}

#define jh_pwmdac_reset_clk_disable { \
    _ASSERT_RESET_audio_rst_gen_rstn_apb_pwmdac_;   \
	_DISABLE_CLOCK_clk_apb_pwmdac_; \
}

/* spdif reset and clkgen */
#define jh_spdif_reset_clk_enable	{	\
    _CLEAR_RESET_audio_rst_gen_rstn_apb_spdif_; \
    _ENABLE_CLOCK_clk_spdif_;   \
    _ENABLE_CLOCK_clk_apb_spdif_;   \
}

#define jh_spdif_reset_clk_disable	{	\
	_ASSERT_RESET_audio_rst_gen_rstn_apb_spdif_;    \
	_DISABLE_CLOCK_clk_spdif_;  \
	_DISABLE_CLOCK_clk_apb_spdif_;  \
}

/* pdm reset and clkgen */
/*#define jh_pdm_reset_clk_enable	{	\
    _DIVIDE_CLOCK_clk_cpu_core_(20) \
    _ENABLE_CLOCK_clk_apb_pdm_; \
    _ENABLE_CLOCK_clk_pdm_mclk_;    \
    _SWITCH_CLOCK_clk_pdm_mclk_SOURCE_clk_audio_src_;   \
    _DIVIDE_CLOCK_clk_pdm_mclk_(1); \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_pdm_;   \
    _DIVIDE_CLOCK_clk_pdm_mclk_(4); \
}*/
#define jh_pdm_reset_clk_enable	{	\
    _ENABLE_CLOCK_clk_apb_pdm_; \
    _ENABLE_CLOCK_clk_pdm_mclk_;    \
    _SWITCH_CLOCK_clk_pdm_mclk_SOURCE_clk_audio_12288_;   \
    _DIVIDE_CLOCK_clk_pdm_mclk_(3); \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_pdm_;   \
}

/* mclk 3MHz */


#define jh_pdm_reset_clk_disable	{	\
	_DISABLE_CLOCK_clk_apb_pdm_;    \
	_DISABLE_CLOCK_clk_pdm_mclk_;   \
	_ASSERT_RESET_audio_rst_gen_rstn_apb_pdm_;  \
}

/* i2sadc clk and reset mclk-->bclk-->lrclk
 * mclk锛�  12.288 MHz / 6 = 2.048 MHz
 * bclk锛�  mclk / 2        = 1.024 Khz
 * lrclk锛� bclk / 64      = 16 KHz
*/
#define jh_i2sadc_reset_clk_enable	{	\
    _SWITCH_CLOCK_clk_adc_mclk_SOURCE_clk_audio_12288_; \
    _ENABLE_CLOCK_clk_adc_mclk_;    \
    _ENABLE_CLOCK_clk_apb_i2sadc_;  \
    _DIVIDE_CLOCK_clk_adc_mclk_(1); \
    _SWITCH_CLOCK_clk_i2sadc_bclk_SOURCE_clk_adc_mclk_; \
    _DIVIDE_CLOCK_clk_i2sadc_bclk_(1);  \
    _SWITCH_CLOCK_clk_i2sadc_bclk_SOURCE_clk_i2sadc_bclk_iopad_;    \
    _CLEAR_RESET_audio_rst_gen_rstn_i2sadc_srst_;   \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2sadc_;    \
}

#define jh_i2sadc_reset_clk_disable	{	\
    _DISABLE_CLOCK_clk_apb_i2sadc_; \
    _ASSERT_RESET_audio_rst_gen_rstn_apb_i2sadc_;   \
    _ASSERT_RESET_audio_rst_gen_rstn_i2sadc_srst_;  \
}

/* i2sdac0 reset and clkgen mclk-->bclk-->lrclk
 * mclk: 12.288 / 3   = 4.096 MHz
 * bclk: mclk / 4     = 1.024 MHz
 * lrclk:bclk / 64    = 16 KHz
 */
#define jh_i2sdac_reset_clk_enable	{	\
    _SWITCH_CLOCK_clk_dac_mclk_SOURCE_clk_audio_12288_; \
    _ENABLE_CLOCK_clk_dac_mclk_;    \
    _ENABLE_CLOCK_clk_apb_i2sdac_;   \
    _DIVIDE_CLOCK_clk_dac_mclk_(3);  \
    _SWITCH_CLOCK_clk_i2sdac_bclk_SOURCE_clk_dac_mclk_; \
    _DIVIDE_CLOCK_clk_i2sdac_bclk_(4);   \
    _SWITCH_CLOCK_clk_i2sdac_lrclk_SOURCE_clk_i2sdac_bclk_; \
    _DIVIDE_CLOCK_clk_i2sdac_lrclk_(64);  \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2sdac_;    \
    _CLEAR_RESET_audio_rst_gen_rstn_i2sdac_srst_;   \
}

#define jh_i2sdac_reset_clk_disable	{	\
    _DISABLE_CLOCK_clk_apb_i2sdac_; \
    _ASSERT_RESET_audio_rst_gen_rstn_apb_i2sdac_;   \
    _ASSERT_RESET_audio_rst_gen_rstn_i2sdac_srst_;  \
}

/* i2s1 [i2sdac1] reset and clkgen mclk-->bclk-->lrclk
 * mclk: 12.288 / 3   = 4.096 MHz
 * bclk: mclk / 4     = 1.024 MHz
 * lrclk:bclk / 64    = 16 KHz
 */
#define jh_i2s1_reset_clk_enable	{	\
    _SWITCH_CLOCK_clk_i2s1_mclk_SOURCE_clk_audio_12288_;    \
    _ENABLE_CLOCK_clk_i2s1_mclk_;   \
    _DIVIDE_CLOCK_clk_i2s1_mclk_(3); \
    _SWITCH_CLOCK_clk_i2s1_bclk_SOURCE_clk_i2s1_mclk_;  \
    _DIVIDE_CLOCK_clk_i2s1_bclk_(4); \
    _SWITCH_CLOCK_clk_i2s1_lrclk_SOURCE_clk_i2s1_bclk_; \
    _DIVIDE_CLOCK_clk_i2s1_lrclk_(16);    \
    _ENABLE_CLOCK_clk_apb_i2s1_;    \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2s1_;  \
    _CLEAR_RESET_audio_rst_gen_rstn_i2s1_srst_; \
}

#define jh_i2s1_reset_clk_disable	{	\
    _DISABLE_CLOCK_clk_apb_i2s1_;   \
    _DISABLE_CLOCK_clk_i2s1_mclk_;  \
    _ASSERT_RESET_audio_rst_gen_rstn_apb_i2s1_; \
    _ASSERT_RESET_audio_rst_gen_rstn_i2s1_srst_;    \
}

/* i2sdac16k reset and clkgen */
#define jh_i2sdac16k_reset_clk_enable	{	\
    _SWITCH_CLOCK_clk_dac_mclk_SOURCE_clk_audio_12288_;    \
    _ENABLE_CLOCK_clk_dac_mclk_;    \
    _DIVIDE_CLOCK_clk_dac_mclk_(6); \
    _ENABLE_CLOCK_clk_apb_i2sdac16k_;   \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2sdac16k_; \
    _CLEAR_RESET_audio_rst_gen_rstn_i2sdac16k_srst_;    \
}

#define jh_i2sdac16k_reset_clk_disable	{	\
    _DISABLE_CLOCK_clk_apb_i2sdac16k_;  \
    _ASSERT_RESET_audio_rst_gen_rstn_apb_i2sdac16k_;    \
    _ASSERT_RESET_audio_rst_gen_rstn_i2sdac16k_srst_;   \
}

/* i2svad reset and clkgen */
#define jh_i2svad_reset_clk_enable	{	\
    _ENABLE_CLOCK_clk_apb_i2svad_;   \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2svad_; \
    _CLEAR_RESET_audio_rst_gen_rstn_i2svad_srst_;    \
}

#define jh_i2svad_reset_clk_disable	{	\
    _DISABLE_CLOCK_clk_apb_i2svad_;  \
    _ASSERT_RESET_audio_rst_gen_rstn_apb_i2svad_;    \
    _ASSERT_RESET_audio_rst_gen_rstn_i2svad_srst_;   \
}


/* musb reset and clkgen */
#define jh_musb_reset_clk_enable	{	\
	/*_ASSERT_RESET_rstn_ahb_usb_;*/ \
}

#define jh_musb_reset_clk_disable	{	\
	/*_ASSERT_RESET_rstn_ahb_usb_;*/ \
}

#define jh_uart0_reset_clk_gpio_isp_enable {    \
    _ENABLE_CLOCK_clk_uart0_apb_;   \
    _ENABLE_CLOCK_clk_uart0_core_;  \
    _DIVIDE_CLOCK_clk_uart0_core_(8);	\
    _CLEAR_RESET_rstgen_rstn_uart0_core_;    \
    _CLEAR_RESET_rstgen_rstn_uart0_apb_; \
    SET_GPIO_uart0_pad_sin(FPGA_UART0_RXD);   \
    SET_GPIO_13_doen_HIGH;  \
    SET_GPIO_12_dout_uart0_pad_sout;    \
    SET_GPIO_12_doen_LOW;  \
}

#define jh_uart0_reset_clk_gpio_misc_enable {    \
    _ENABLE_CLOCK_clk_uart0_apb_;   \
    _ENABLE_CLOCK_clk_uart0_core_;  \
    _CLEAR_RESET_rstgen_rstn_uart0_core_;    \
    _CLEAR_RESET_rstgen_rstn_uart0_apb_; \
    SET_GPIO_uart0_pad_sin(FPGA_UART0_RXD);   \
    SET_GPIO_5_doen_HIGH;    \
    SET_GPIO_6_dout_uart0_pad_sout;  \
    SET_GPIO_6_doen_LOW; \
}

#define jh_uart0_reset_clk_gpio_evb_enable {    \
    _ENABLE_CLOCK_clk_uart0_apb_;   \
    _ENABLE_CLOCK_clk_uart0_core_;  \
    _CLEAR_RESET_rstgen_rstn_uart0_core_;    \
    _CLEAR_RESET_rstgen_rstn_uart0_apb_; \
    SET_GPIO_uart0_pad_sin(FPGA_UART0_RXD);   \
    SET_GPIO_5_doen_HIGH;    \
    SET_GPIO_6_dout_uart0_pad_sout;  \
    SET_GPIO_6_doen_LOW; \
}

/*
SET_GPIO_uart0_pad_ctsn(FPGA_UART0_CTSN);  \
SET_GPIO_uart0_pad_dcdn(-1);  \
SET_GPIO_uart0_pad_dsrn(-1);  \
SET_GPIO_uart0_pad_rin(-1);   \
SET_GPIO_7_doen_HIGH; \
*/

#define jh_uart0_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_uart0_apb_;  \
    _ASSERT_RESET_rstgen_rstn_uart0_apb_;   \
    _ASSERT_RESET_rstgen_rstn_uart0_core_;   \
}

#define jh_uart1_reset_clk_gpio_isp_enable {    \
    _ENABLE_CLOCK_clk_uart1_apb_;   \
    _ENABLE_CLOCK_clk_uart1_core_;  \
    _CLEAR_RESET_rstgen_rstn_uart1_core_;   \
    _CLEAR_RESET_rstgen_rstn_uart1_apb_;    \
    SET_GPIO_12_dout_uart1_pad_sout;    \
    SET_GPIO_uart1_pad_sin(FPGA_UART1_RXD);   \
    SET_GPIO_13_doen_HIGH;  \
    SET_GPIO_12_doen_LOW;  \
}
#if 1 //simon
#define jh_uart1_reset_clk_gpio_misc_enable {    \
    _ENABLE_CLOCK_clk_uart1_apb_;   \
    _ENABLE_CLOCK_clk_uart1_core_;  \
    _CLEAR_RESET_rstgen_rstn_uart1_core_;   \
    _CLEAR_RESET_rstgen_rstn_uart1_apb_;    \
    SET_GPIO_6_dout_uart1_pad_sout;    \
    SET_GPIO_uart1_pad_sin(FPGA_UART1_RXD);   \
    SET_GPIO_5_doen_HIGH;  \
    SET_GPIO_6_doen_LOW;  \
}
#else //hongya-vp6
#define jh_uart1_reset_clk_gpio_misc_enable {    \
        _ENABLE_CLOCK_clk_uart1_apb_;   \
        _ENABLE_CLOCK_clk_uart1_core_;  \
        _CLEAR_RESET_rstgen_rstn_uart1_core_;   \
        _CLEAR_RESET_rstgen_rstn_uart1_apb_;    \
        SET_GPIO_uart1_pad_sin(FPGA_UART1_RXD);   \
        SET_GPIO_11_doen_HIGH;  \
        SET_GPIO_12_dout_uart1_pad_sout;    \
        SET_GPIO_12_doen_LOW;  \
    }

#endif

#define jh_uart1_reset_clk_gpio_evb_enable {    \
		_ENABLE_CLOCK_clk_uart1_apb_;	\
		_ENABLE_CLOCK_clk_uart1_core_;	\
		_CLEAR_RESET_rstgen_rstn_uart1_core_;	\
		_CLEAR_RESET_rstgen_rstn_uart1_apb_;	\
		SET_GPIO_10_dout_uart1_pad_sout;	\
		SET_GPIO_uart1_pad_sin(FPGA_UART1_RXD);   \
		SET_GPIO_9_doen_HIGH;  \
		SET_GPIO_10_doen_LOW;  \
}


#define jh_uart1_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_uart1_apb_;  \
    _ASSERT_RESET_rstgen_rstn_uart1_apb_;   \
    _ASSERT_RESET_rstgen_rstn_uart1_core_;  \
}
/*
#define jh_uart2_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_uart2_apb_;  \
    _ASSERT_RESET_rstgen_rstn_uart2_apb_;   \
    _ASSERT_RESET_rstgen_rstn_uart2_core_;  \
}
*/
#define jh_uart2_reset_clk_gpio_isp_enable {    \
	jh_uart2_reset_clk_disable;	\
    _ENABLE_CLOCK_clk_uart2_apb_;   \
    _ENABLE_CLOCK_clk_uart2_core_;  \
    _CLEAR_RESET_rstgen_rstn_uart2_core_;   \
    _CLEAR_RESET_rstgen_rstn_uart2_apb_;    \
    SET_GPIO_uart2_pad_sin(FPGA_UART2_RXD); \
    SET_GPIO_13_doen_HIGH;  \
    SET_GPIO_12_dout_uart2_pad_sout;    \
    SET_GPIO_12_doen_LOW;  \
}

#define jh_uart2_reset_clk_gpio_misc_enable {    \
	jh_uart2_reset_clk_disable;	\
    _ENABLE_CLOCK_clk_uart2_apb_;   \
    _ENABLE_CLOCK_clk_uart2_core_;  \
	_CLEAR_RESET_rstgen_rstn_uart2_core_;   \
    _CLEAR_RESET_rstgen_rstn_uart2_apb_;    \
    SET_GPIO_uart2_pad_sin(FPGA_UART2_RXD); \
    SET_GPIO_13_doen_HIGH;  \
    SET_GPIO_14_dout_uart2_pad_sout;    \
    SET_GPIO_14_doen_LOW;   \
}

#define jh_uart2_reset_clk_gpio_evb_enable {    \
	jh_uart2_reset_clk_disable;	\
    _ENABLE_CLOCK_clk_uart2_apb_;   \
    _ENABLE_CLOCK_clk_uart2_core_;  \
	_CLEAR_RESET_rstgen_rstn_uart2_core_;   \
    _CLEAR_RESET_rstgen_rstn_uart2_apb_;    \
    SET_GPIO_uart2_pad_sin(FPGA_UART2_RXD); \
    SET_GPIO_5_doen_HIGH;  \
    SET_GPIO_6_dout_uart2_pad_sout;    \
    SET_GPIO_6_doen_LOW;   \
}


/* rtsn:11 ctsn:14 */
#define jh_uart0_isp_4line {   \
    SET_GPIO_11_dout_uart0_pad_rtsn;    \
    SET_GPIO_11_doen_LOW;   \
    SET_GPIO_uart0_pad_ctsn(FPGA_UART0_CTSN);   \
    SET_GPIO_14_doen_HIGH;   \
}

/* rtsn:8 ctsn:7 */
#define jh_uart0_misc_4line {   \
    SET_GPIO_8_dout_uart0_pad_rtsn;    \
    SET_GPIO_8_doen_LOW;   \
    SET_GPIO_uart0_pad_ctsn(FPGA_UART0_CTSN);   \
    SET_GPIO_7_doen_HIGH;   \
}
///SET_GPIO_uart0_pad_ctsn(-2);   /* ZHUA XIN HAO */

/* rtsn:49 ctsn:48 */
#define jh_uart2_4line {   \
    SET_GPIO_49_doen_uart2_pad_rts_n;   \
    SET_GPIO_49_doen_LOW;   \
    SET_GPIO_uart2_pad_cts_n(FPGA_UART2_CTSN);   \
    SET_GPIO_48_doen_LOW;   \
}

#define jh_uart2_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_uart2_apb_;  \
}

#define jh_uart3_reset_clk_gpio_isp_enable {    \
    _ENABLE_CLOCK_clk_uart3_apb_;   \
    _ENABLE_CLOCK_clk_uart3_core_;  \
    _CLEAR_RESET_rstgen_rstn_uart3_core_;    \
    _CLEAR_RESET_rstgen_rstn_uart3_apb_; \
    SET_GPIO_uart3_pad_sin(FPGA_UART3_RXD); \
    SET_GPIO_13_doen_HIGH;  \
    SET_GPIO_12_dout_uart3_pad_sout;    \
    SET_GPIO_12_doen_LOW;  \
}

#if 1  //simon
#define jh_uart3_reset_clk_gpio_misc_enable {    \
    _ENABLE_CLOCK_clk_uart3_apb_;   \
    _ENABLE_CLOCK_clk_uart3_core_;  \
    _CLEAR_RESET_rstgen_rstn_uart3_core_;    \
    _CLEAR_RESET_rstgen_rstn_uart3_apb_; \
    SET_GPIO_uart3_pad_sin(FPGA_UART2_RXD); \
    SET_GPIO_13_doen_HIGH;  \
    SET_GPIO_14_dout_uart3_pad_sout;    \
    SET_GPIO_14_doen_LOW;   \
}
#else  //hongya
#define jh_uart3_reset_clk_gpio_misc_enable {    \
            _ENABLE_CLOCK_clk_uart3_apb_;   \
            _ENABLE_CLOCK_clk_uart3_core_;  \
            _CLEAR_RESET_rstgen_rstn_uart3_core_;    \
            _CLEAR_RESET_rstgen_rstn_uart3_apb_; \
            SET_GPIO_uart3_pad_sin(FPGA_UART3_RXD); \
            SET_GPIO_11_doen_HIGH;  \
            SET_GPIO_12_dout_uart3_pad_sout;    \
            SET_GPIO_12_doen_LOW;   \
}
#endif

#define jh_uart3_reset_clk_gpio_evb_enable {    \
		_ENABLE_CLOCK_clk_uart3_apb_;	\
		_ENABLE_CLOCK_clk_uart3_core_;	\
		_CLEAR_RESET_rstgen_rstn_uart3_core_;	 \
		_CLEAR_RESET_rstgen_rstn_uart3_apb_; \
		SET_GPIO_uart3_pad_sin(FPGA_UART3_RXD); \
		SET_GPIO_13_doen_HIGH;	\
		SET_GPIO_14_dout_uart3_pad_sout;	\
		SET_GPIO_14_doen_LOW;	\
}

#define jh_uart3_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_uart3_apb_;  \
}


#define jh_vdec_reset_clk_enable {   \
    _ENABLE_CLOCK_clk_vdecbrg_mainclk_; \
    _ENABLE_CLOCK_clk_vdec_apb_;    \
    _ENABLE_CLOCK_clk_vdec_axi_;    \
    _ENABLE_CLOCK_clk_vdec_bclk_;   \
    _ENABLE_CLOCK_clk_vdec_cclk_;   \
    _CLEAR_RESET_rstgen_rstn_vdecbrg_main_;   \
    _CLEAR_RESET_rstgen_rstn_vdec_apb_; \
    _CLEAR_RESET_rstgen_rstn_vdec_axi_; \
    _CLEAR_RESET_rstgen_rstn_vdec_bclk_;    \
    _CLEAR_RESET_rstgen_rstn_vdec_cclk_;    \
}

/*
///_SET_SYSCON_REG_SCFG_vdec_remap_bound_addr0(0);  \
///_SET_SYSCON_REG_SCFG_vdec_remap_offset_addr(0); \
///_SET_SYSCON_REG_SCFG_vdec_remap_start_point(0); \
*/

#define jh_vdec_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_vdec_apb_;    \
    _DISABLE_CLOCK_clk_vdec_axi_;   \
    _DISABLE_CLOCK_clk_vdec_bclk_;  \
    _DISABLE_CLOCK_clk_vdec_cclk_;  \
    _ASSERT_RESET_rstgen_rstn_vdec_apb_;    \
    _ASSERT_RESET_rstgen_rstn_vdec_axi_;    \
    _ASSERT_RESET_rstgen_rstn_vdec_bclk_;   \
    _ASSERT_RESET_rstgen_rstn_vdec_cclk_;   \
}
///_DISABLE_CLOCK_clk_vdecbrg_mainclk_;
///_ASSERT_RESET_rstgen_rstn_vdecbrg_main_;


#define jh_venc_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_venc_apb_;    \
    _DISABLE_CLOCK_clk_venc_axi_;    \
    _DISABLE_CLOCK_clk_venc_bclk_;   \
    _DISABLE_CLOCK_clk_venc_cclk_;   \
    _ASSERT_RESET_rstgen_rstn_venc_apb_; \
    _ASSERT_RESET_rstgen_rstn_venc_axi_; \
    _ASSERT_RESET_rstgen_rstn_venc_bclk_;    \
    _ASSERT_RESET_rstgen_rstn_venc_cclk_;    \
}

//_DISABLE_CLOCK_clk_vencbrg_mainclk_;
//_ASSERT_RESET_rstgen_rstn_vencbrg_main_;


#define jh_venc_reset_clk_enable {   \
    _ENABLE_CLOCK_clk_vencbrg_mainclk_; \
    _ENABLE_CLOCK_clk_venc_apb_;    \
    _ENABLE_CLOCK_clk_venc_axi_;    \
    _ENABLE_CLOCK_clk_venc_bclk_;   \
    _ENABLE_CLOCK_clk_venc_cclk_;   \
    _CLEAR_RESET_rstgen_rstn_vencbrg_main_;   \
    _CLEAR_RESET_rstgen_rstn_venc_apb_; \
    _CLEAR_RESET_rstgen_rstn_venc_axi_; \
    _CLEAR_RESET_rstgen_rstn_venc_bclk_;    \
    _CLEAR_RESET_rstgen_rstn_venc_cclk_;    \
}

#define jh_jpeg_reset_clk_enable {   \
    _ENABLE_CLOCK_clk_jpeg_axi_;	\
	_ENABLE_CLOCK_clk_jpeg_cclk_;	\
	_ENABLE_CLOCK_clk_jpeg_apb_;	\
	_CLEAR_RESET_rstgen_rstn_jpeg_axi_;	\
	_CLEAR_RESET_rstgen_rstn_jpeg_cclk_;	\
	_CLEAR_RESET_rstgen_rstn_jpeg_apb_;	\
}

#define jh_jpeg_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_jpeg_axi_;	\
	_DISABLE_CLOCK_clk_jpeg_cclk_;	\
	_DISABLE_CLOCK_clk_jpeg_apb_;	\
	_ASSERT_RESET_rstgen_rstn_jpeg_axi_;	\
	_ASSERT_RESET_rstgen_rstn_jpeg_cclk_;	\
	_ASSERT_RESET_rstgen_rstn_jpeg_apb_;	\
}
/*
///_SET_SYSCON_REG_SCFG_jpeg_remap_en();
///_SET_SYSCON_REG_SCFG_jpeg_remap_start_point();
///_SET_SYSCON_REG_SCFG_jpeg_remap_bound_addr0();
*/

#define jh_nbdla_reset_clk_enable {    \
		_ENABLE_CLOCK_clk_dlaslv_axi_;	 \
		_CLEAR_RESET_rstgen_rstn_dlaslv_axi_; \
		_ENABLE_CLOCK_clk_dla_axi_; 		  \
		_CLEAR_RESET_rstgen_rstn_dla_axi_;	  \
		_ENABLE_CLOCK_clk_nnenoc_axi_;		  \
		_CLEAR_RESET_rstgen_rstn_nnenoc_axi_; \
		_SET_SYSCON_REG_register16_SCFG_nbdla_clkgating_en(1); \
	}

//1: ENABLE; 0:DISABLE


#define jh_nbdla_reset_clk_disable {    \
			_DISABLE_CLOCK_clk_dlaslv_axi_;	 \
			_ASSERT_RESET_rstgen_rstn_dlaslv_axi_; \
			_DISABLE_CLOCK_clk_dla_axi_; 		  \
			_ASSERT_RESET_rstgen_rstn_dla_axi_;	  \
			_DISABLE_CLOCK_clk_nnenoc_axi_;		  \
			_ASSERT_RESET_rstgen_rstn_nnenoc_axi_; \
			_SET_SYSCON_REG_register16_SCFG_nbdla_clkgating_en(0); \
		}

#define jh_trng_reset_clk_enable {   \
    _ENABLE_CLOCK_clk_trng_apb_;	\
	_CLEAR_RESET_rstgen_rstn_trng_apb_;	\
}

#define jh_trng_reset_clk_disable {   \
    _DISABLE_CLOCK_clk_trng_apb_;	\
	_ASSERT_RESET_rstgen_rstn_trng_apb_;	\
}

#define jh_audio_reset_clk_enable {    \
    _ENABLE_CLOCK_clk_audio_root_;  \
    _ENABLE_CLOCK_clk_audio_src_;   \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_bus_;   \
    _ENABLE_CLOCK_clk_apb_i2svad_;  \
    _CLEAR_RESET_audio_rst_gen_rstn_apb_i2svad_; \
}

#define jh_module_reset	{	\
	jh_uart0_reset_clk_disable;    \
	jh_uart1_reset_clk_disable;    \
	jh_uart2_reset_clk_disable;    \
	jh_uart3_reset_clk_disable;    \
	jh_vdec_reset_clk_disable; \
	jh_nbdla_reset_clk_disable;  \
	jh_i2sadc_reset_clk_disable;   \
	jh_jpeg_reset_clk_disable; \
	jh_trng_reset_clk_disable; \
}

#if 0
#define jh_module_reset	{	\
	jh_i2sadc_reset_clk_disable;	\
	jh_i2sdac_reset_clk_disable;	\
	jh_i2sdac16k_reset_clk_disable;	\
	jh_i2s1_reset_clk_disable;	\
	jh_pdm_reset_clk_disable;	\
	jh_pcm_reset_clk_disable;	\
	jh_spdif_reset_clk_disable;	\
	jh_pwmdac_reset_clk_disable;	\
	jh_ptc_reset_clk_disable;	\
	jh_musb_reset_clk_disable;	\
	jh_uart0_reset_clk_disable;    \
	jh_uart1_reset_clk_disable;    \
	jh_uart2_reset_clk_disable;    \
	jh_uart3_reset_clk_disable;    \
}
#endif

#define jh_clkgen_enable {   \
    _ENABLE_CLOCK_clk_pll0_testout_; \
    _ENABLE_CLOCK_clk_pll1_testout_;    \
    _ENABLE_CLOCK_clk_pll2_testout_;    \
    _ENABLE_CLOCK_clk_ahb0_bus_;   \
    _ENABLE_CLOCK_clk_apb1_bus_;   \
    _ENABLE_CLOCK_clk_ahb2_bus_;   \
    _ENABLE_CLOCK_clk_apb2_bus_; \
    _ENABLE_CLOCK_clk_u74_core_; \
    _ENABLE_CLOCK_clk_u74_axi_;    \
    _ENABLE_CLOCK_clk_u74rtc_toggle_;    \
	_ENABLE_CLOCK_clk_sgdma2p_axi_;	\
	_ENABLE_CLOCK_clk_dma2pnoc_axi_;	\
	_ENABLE_CLOCK_clk_sgdma2p_ahb_;	\
	_ENABLE_CLOCK_clk_dla_bus_;	\
	_ENABLE_CLOCK_clk_dla_axi_;	\
	_ENABLE_CLOCK_clk_dlanoc_axi_;	\
	_ENABLE_CLOCK_clk_dla_apb_;	\
	_ENABLE_CLOCK_clk_vp6_core_;	\
	_ENABLE_CLOCK_clk_vp6_axi_;	\
	_ENABLE_CLOCK_clk_vp6_apb_;	\
	_ENABLE_CLOCK_clk_vdec_axi_;	\
	_ENABLE_CLOCK_clk_vdecbrg_mainclk_;	\
	_ENABLE_CLOCK_clk_vdec_bclk_;	\
	_ENABLE_CLOCK_clk_vdec_cclk_;	\
	_ENABLE_CLOCK_clk_vdec_apb_;	\
	_ENABLE_CLOCK_clk_jpeg_axi_;	\
	_ENABLE_CLOCK_clk_jpeg_cclk_;	\
	_ENABLE_CLOCK_clk_jpeg_apb_;	\
	_ENABLE_CLOCK_clk_gc300_2x_;	\
	_ENABLE_CLOCK_clk_gc300_ahb_;	\
	_ENABLE_CLOCK_clk_gc300_axi_;	\
	_ENABLE_CLOCK_clk_jpcgc300_mainclk_;	\
	_ENABLE_CLOCK_clk_venc_axi_;	\
	_ENABLE_CLOCK_clk_vencbrg_mainclk_;	\
	_ENABLE_CLOCK_clk_venc_bclk_;	\
	_ENABLE_CLOCK_clk_venc_cclk_;	\
	_ENABLE_CLOCK_clk_venc_apb_;	\
	_ENABLE_CLOCK_clk_ddrc0_;	\
	_ENABLE_CLOCK_clk_ddrc1_;	\
	_ENABLE_CLOCK_clk_ddrphy_apb_;	\
	_ENABLE_CLOCK_clk_noc_rob_;	\
	_ENABLE_CLOCK_clk_noc_cog_;	\
	_ENABLE_CLOCK_clk_nne_ahb_;	\
	_ENABLE_CLOCK_clk_nne_axi_;	\
	_ENABLE_CLOCK_clk_nnenoc_axi_;	\
	_ENABLE_CLOCK_clk_dlaslv_axi_;	\
	_ENABLE_CLOCK_clk_dspx2c_axi_;	\
	_ENABLE_CLOCK_clk_hifi4_core_;	\
	_ENABLE_CLOCK_clk_hifi4_axi_;	\
	_ENABLE_CLOCK_clk_hifi4noc_axi_;	\
	_ENABLE_CLOCK_clk_sgdma1p_axi_;	\
	_ENABLE_CLOCK_clk_dma1p_axi_;	\
	_ENABLE_CLOCK_clk_x2c_axi_;	\
	_ENABLE_CLOCK_clk_usb_axi_;	\
	_ENABLE_CLOCK_clk_usbnoc_axi_;	\
	_ENABLE_CLOCK_clk_usbphy_125m_;	\
	_ENABLE_CLOCK_clk_usbphy_plldiv25m_;	\
	_ENABLE_CLOCK_clk_audio_12288_;	\
	_ENABLE_CLOCK_clk_audio_src_;	\
	_ENABLE_CLOCK_clk_vin_src_;	\
	_ENABLE_CLOCK_clk_isp0_axi_;	\
	_ENABLE_CLOCK_clk_isp0noc_axi_;	\
	_ENABLE_CLOCK_clk_ispslv_axi_;	\
	_ENABLE_CLOCK_clk_isp1_axi_;	\
	_ENABLE_CLOCK_clk_isp1noc_axi_;	\
	_ENABLE_CLOCK_clk_vin_axi_;	\
	_ENABLE_CLOCK_clk_vinnoc_axi_;	\
	_ENABLE_CLOCK_clk_vout_src_;	\
	_ENABLE_CLOCK_clk_disp_axi_;	\
	_ENABLE_CLOCK_clk_dispnoc_axi_;	\
	_ENABLE_CLOCK_clk_sdio0_ahb_;	\
	_ENABLE_CLOCK_clk_sdio0_cclkint_;	\
	_ENABLE_CLOCK_clk_sdio1_ahb_;	\
	_ENABLE_CLOCK_clk_sdio1_cclkint_;	\
	_ENABLE_CLOCK_clk_gmac_ahb_;	\
	_ENABLE_CLOCK_clk_gmac_ptp_refclk_;	\
	_ENABLE_CLOCK_clk_gmac_gtxclk_;	\
	_ENABLE_CLOCK_clk_gmac_rmii_txclk_;	\
	_ENABLE_CLOCK_clk_gmac_rmii_rxclk_;	\
	_ENABLE_CLOCK_clk_gmac_rmii_;	\
	_ENABLE_CLOCK_clk_gmac_tophyref_;	\
	_ENABLE_CLOCK_clk_spi2ahb_ahb_;	\
	_ENABLE_CLOCK_clk_spi2ahb_core_;	\
	_ENABLE_CLOCK_clk_ezmaster_ahb_;	\
	_ENABLE_CLOCK_clk_e24_ahb_;	\
	_ENABLE_CLOCK_clk_e24rtc_toggle_;	\
	_ENABLE_CLOCK_clk_qspi_ahb_;	\
	_ENABLE_CLOCK_clk_qspi_apb_;	\
	_ENABLE_CLOCK_clk_qspi_refclk_;	\
	_ENABLE_CLOCK_clk_sec_ahb_;	\
	_ENABLE_CLOCK_clk_aes_clk_;	\
	_ENABLE_CLOCK_clk_sha_clk_;	\
	_ENABLE_CLOCK_clk_pka_clk_;	\
	_ENABLE_CLOCK_clk_trng_apb_;	\
	_ENABLE_CLOCK_clk_otp_apb_;	\
	_ENABLE_CLOCK_clk_uart0_apb_;	\
	_ENABLE_CLOCK_clk_uart0_core_;	\
	_ENABLE_CLOCK_clk_uart1_apb_;	\
	_ENABLE_CLOCK_clk_uart1_core_;	\
	_ENABLE_CLOCK_clk_spi0_apb_;	\
	_ENABLE_CLOCK_clk_spi0_core_;	\
	_ENABLE_CLOCK_clk_spi1_apb_;	\
	_ENABLE_CLOCK_clk_spi1_core_;	\
	_ENABLE_CLOCK_clk_i2c0_apb_;	\
	_ENABLE_CLOCK_clk_i2c0_core_;	\
	_ENABLE_CLOCK_clk_i2c1_apb_;	\
	_ENABLE_CLOCK_clk_i2c1_core_;	\
	_ENABLE_CLOCK_clk_gpio_apb_;	\
	_ENABLE_CLOCK_clk_uart2_apb_;	\
	_ENABLE_CLOCK_clk_uart2_core_;	\
	_ENABLE_CLOCK_clk_uart3_apb_;	\
	_ENABLE_CLOCK_clk_uart3_core_;	\
	_ENABLE_CLOCK_clk_spi2_apb_;	\
	_ENABLE_CLOCK_clk_spi2_core_;	\
	_ENABLE_CLOCK_clk_spi3_apb_;	\
	_ENABLE_CLOCK_clk_spi3_core_;	\
	_ENABLE_CLOCK_clk_i2c2_apb_;	\
	_ENABLE_CLOCK_clk_i2c2_core_;	\
	_ENABLE_CLOCK_clk_i2c3_apb_;	\
	_ENABLE_CLOCK_clk_i2c3_core_;	\
	_ENABLE_CLOCK_clk_wdtimer_apb_;	\
	_ENABLE_CLOCK_clk_wdt_coreclk_;	\
	_ENABLE_CLOCK_clk_timer0_coreclk_;	\
	_ENABLE_CLOCK_clk_timer1_coreclk_;	\
	_ENABLE_CLOCK_clk_timer2_coreclk_;	\
	_ENABLE_CLOCK_clk_timer3_coreclk_;	\
	_ENABLE_CLOCK_clk_timer4_coreclk_;	\
	_ENABLE_CLOCK_clk_timer5_coreclk_;	\
	_ENABLE_CLOCK_clk_timer6_coreclk_;	\
	_ENABLE_CLOCK_clk_vp6intc_apb_;	\
	_ENABLE_CLOCK_clk_pwm_apb_;	\
	_ENABLE_CLOCK_clk_msi_apb_;	\
	_ENABLE_CLOCK_clk_temp_apb_;	\
	_ENABLE_CLOCK_clk_temp_sense_;	\
	_ENABLE_CLOCK_clk_syserr_apb_;	\
}

#define jh_rstgen_enable {   \
	_CLEAR_RESET_rstgen_rstn_u74_axi_;	\
	_CLEAR_RESET_rstgen_rstn_sgdma2p_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_sgdma2p_axi_;	\
	_CLEAR_RESET_rstgen_rstn_dma2pnoc_aix_;	\
	_CLEAR_RESET_rstgen_rstn_dla_axi_;	\
	_CLEAR_RESET_rstgen_rstn_dlanoc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_dla_apb_;	\
	_CLEAR_RESET_rstgen_rstn_vp6_axi_;	\
	_CLEAR_RESET_rstgen_rstn_vp6_apb_;	\
	_CLEAR_RESET_rstgen_rstn_vdecbrg_main_;	\
	_CLEAR_RESET_rstgen_rstn_vdec_axi_;	\
	_CLEAR_RESET_rstgen_rstn_vdec_bclk_;	\
	_CLEAR_RESET_rstgen_rstn_vdec_cclk_;	\
	_CLEAR_RESET_rstgen_rstn_vdec_apb_;	\
	_CLEAR_RESET_rstgen_rstn_jpeg_axi_;	\
	_CLEAR_RESET_rstgen_rstn_jpeg_cclk_;	\
	_CLEAR_RESET_rstgen_rstn_jpeg_apb_;	\
	_CLEAR_RESET_rstgen_rstn_jpcgc300_main_;	\
	_CLEAR_RESET_rstgen_rstn_gc300_2x_;	\
	_CLEAR_RESET_rstgen_rstn_gc300_axi_;	\
	_CLEAR_RESET_rstgen_rstn_gc300_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_venc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_vencbrg_main_;	\
	_CLEAR_RESET_rstgen_rstn_venc_bclk_;	\
	_CLEAR_RESET_rstgen_rstn_venc_cclk_;	\
	_CLEAR_RESET_rstgen_rstn_venc_apb_;	\
	_CLEAR_RESET_rstgen_rstn_ddrphy_apb_;	\
	_CLEAR_RESET_rstgen_rstn_noc_rob_;	\
	_CLEAR_RESET_rstgen_rstn_noc_cog_;	\
	_CLEAR_RESET_rstgen_rstn_hifi4_axi_;	\
	_CLEAR_RESET_rstgen_rstn_hifi4noc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_usb_axi_;	\
	_CLEAR_RESET_rstgen_rstn_usbnoc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_sgdma1p_axi_;	\
	_CLEAR_RESET_rstgen_rstn_dma1p_axi_;	\
	_CLEAR_RESET_rstgen_rstn_x2c_axi_;	\
	_CLEAR_RESET_rstgen_rstn_nne_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_nne_axi_;	\
	_CLEAR_RESET_rstgen_rstn_nnenoc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_dlaslv_axi_;	\
	_CLEAR_RESET_rstgen_rstn_dspx2c_axi_;	\
	_CLEAR_RESET_rstgen_rstn_vin_src_;	\
	_CLEAR_RESET_rstgen_rstn_ispslv_axi_;	\
	_CLEAR_RESET_rstgen_rstn_vin_axi_;	\
	_CLEAR_RESET_rstgen_rstn_vinnoc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_isp0_axi_;	\
	_CLEAR_RESET_rstgen_rstn_isp0noc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_isp1_axi_;	\
	_CLEAR_RESET_rstgen_rstn_isp1noc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_vout_src_;	\
	_CLEAR_RESET_rstgen_rstn_disp_axi_;	\
	_CLEAR_RESET_rstgen_rstn_dispnoc_axi_;	\
	_CLEAR_RESET_rstgen_rstn_sdio0_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_sdio1_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_gmac_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_spi2ahb_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_spi2ahb_core_;	\
	_CLEAR_RESET_rstgen_rstn_ezmaster_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_qspi_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_qspi_core_;	\
	_CLEAR_RESET_rstgen_rstn_qspi_apb_;	\
	_CLEAR_RESET_rstgen_rstn_sec_ahb_;	\
	_CLEAR_RESET_rstgen_rstn_aes_;	\
	_CLEAR_RESET_rstgen_rstn_pka_;	\
	_CLEAR_RESET_rstgen_rstn_sha_;	\
	_CLEAR_RESET_rstgen_rstn_trng_apb_;	\
	_CLEAR_RESET_rstgen_rstn_otp_apb_;	\
	_CLEAR_RESET_rstgen_rstn_uart0_apb_;	\
	_CLEAR_RESET_rstgen_rstn_uart0_core_;	\
	_CLEAR_RESET_rstgen_rstn_uart1_apb_;	\
	_CLEAR_RESET_rstgen_rstn_uart1_core_;	\
	_CLEAR_RESET_rstgen_rstn_spi0_apb_;	\
	_CLEAR_RESET_rstgen_rstn_spi0_core_;	\
	_CLEAR_RESET_rstgen_rstn_spi1_apb_;	\
	_CLEAR_RESET_rstgen_rstn_spi1_core_;	\
	_CLEAR_RESET_rstgen_rstn_i2c0_apb_;	\
	_CLEAR_RESET_rstgen_rstn_i2c0_core_;	\
	_CLEAR_RESET_rstgen_rstn_i2c1_apb_;	\
	_CLEAR_RESET_rstgen_rstn_i2c1_core_;	\
	_CLEAR_RESET_rstgen_rstn_gpio_apb_;	\
	_CLEAR_RESET_rstgen_rstn_uart2_apb_;	\
	_CLEAR_RESET_rstgen_rstn_uart2_core_;	\
	_CLEAR_RESET_rstgen_rstn_uart3_apb_;	\
	_CLEAR_RESET_rstgen_rstn_uart3_core_;	\
	_CLEAR_RESET_rstgen_rstn_spi2_apb_;	\
	_CLEAR_RESET_rstgen_rstn_spi2_core_;	\
	_CLEAR_RESET_rstgen_rstn_spi3_apb_;	\
	_CLEAR_RESET_rstgen_rstn_spi3_core_;	\
	_CLEAR_RESET_rstgen_rstn_i2c2_apb_;	\
	_CLEAR_RESET_rstgen_rstn_i2c2_core_;	\
	_CLEAR_RESET_rstgen_rstn_i2c3_apb_;	\
	_CLEAR_RESET_rstgen_rstn_i2c3_core_;	\
	_CLEAR_RESET_rstgen_rstn_wdtimer_apb_;	\
	_CLEAR_RESET_rstgen_rstn_wdt_;	\
	_CLEAR_RESET_rstgen_rstn_timer0_;	\
	_CLEAR_RESET_rstgen_rstn_timer1_;	\
	_CLEAR_RESET_rstgen_rstn_timer2_;	\
	_CLEAR_RESET_rstgen_rstn_timer3_;	\
	_CLEAR_RESET_rstgen_rstn_timer4_;	\
	_CLEAR_RESET_rstgen_rstn_timer5_;	\
	_CLEAR_RESET_rstgen_rstn_timer6_;	\
	_CLEAR_RESET_rstgen_rstn_vp6intc_apb_;	\
	_CLEAR_RESET_rstgen_rstn_pwm_apb_;	\
	_CLEAR_RESET_rstgen_rstn_msi_apb_;	\
	_CLEAR_RESET_rstgen_rstn_temp_apb_;	\
	_CLEAR_RESET_rstgen_rstn_temp_sense_;	\
	_CLEAR_RESET_rstgen_rstn_syserr_apb_;	\
}

#endif	/* _SFC_JH_MODULE_RESET_CLKGEN_H */
