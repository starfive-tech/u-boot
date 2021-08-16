// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2021 Shanghai StarFive Technology Co., Ltd.
 * TekkamanV <tekkamanv@starfivetech.com>
 */

#include <inttypes.h>
#include <linux/io.h>

#include <asm/arch/io.h>
#include <asm/arch/jh_ptc.h>
#include <asm/arch/jh_module_reset_clkgen.h>
#include <asm/arch/ezGPIO_fullMux_ctrl_macro.h>
#include <asm/arch/clkgen_ctrl_macro.h>
#include <asm/arch/global_reg.h>
#include <asm/arch/rstgen_ctrl_macro.h>

/* set cntr register */
static void Set_rptc_cntr(uint32_t num, uint32_t data)
{
	MA_OUTW(PTC_RPTC_CNTR(num), data);
}

/* set hrc register */
static void Set_rptc_hrc(uint32_t num, uint32_t data)
{
	MA_OUTW(PTC_RPTC_HRC(num), data);
}

/* set lrc register */
static void Set_rptc_lrc(uint32_t num, uint32_t data)
{
	MA_OUTW(PTC_RPTC_LRC(num), data);
}

/* set capture mode for pwm input signal */
static int Set_ptc_capMode(uint32_t num, uint32_t data)
{
	uint32_t value;

	value = (MA_INW(PTC_RPTC_CTRL(num))& 0x1FF);

	if(data == PTC_CAPT_SINGLE)
	{
		value |= PTC_SIGNLE;
	}
	else if(data == PTC_CAPT_CONTINUE)
	{
		value = ~( (~value) | PTC_SIGNLE);
	}
	MA_OUTW(PTC_RPTC_CTRL(num), value);

	return 0;
}

/* clear cntr in ctrl register */
static void ptc_reset_cntr(uint32_t num)
{
	uint32_t value;
	uint32_t *reg_addr;

	reg_addr = (uint32_t *)PTC_RPTC_CTRL(num);
	value = (MA_INW(reg_addr)& 0x1FF);
	value |= PTC_CNTRRST;
	MA_OUTW(reg_addr, value);
}

/* enable capture mode */
static void ptc_reset_capt(uint32_t num)
{
	uint32_t value;
	uint32_t *reg_addr;

	reg_addr = (uint32_t *)PTC_RPTC_CTRL(num);
	value = (MA_INW(reg_addr)& 0x1FF);
	value |= PTC_CAPTE;
	MA_OUTW(reg_addr, value & 0X1ff);
}

/* reset ctrl register */
static void ptc_reset_ctrl(uint32_t num)
{
	uint32_t value;
	uint32_t *reg_addr;

	reg_addr = (uint32_t *)PTC_RPTC_CTRL(num);
	value = MA_INW(reg_addr);
	value = ~( (~value) | PTC_EN);
	value = ~( (~value) | PTC_ECLK);
	value = ~( (~value) | PTC_OE);
	value = ~( (~value) | PTC_INTE);
	value = ~( (~value) | PTC_INT);
	value |= PTC_INT;
	value = ~( (~value) | PTC_CNTRRST);
	value = ~( (~value) | PTC_CAPTE);

	MA_OUTW(reg_addr, value & 0x1FF);

	value = ~( (~value) | PTC_INT);
	MA_OUTW(PTC_RPTC_CTRL(num), value & 0x1FF);
}

/*set default duty in uboot , pwm period is 400 us ,high level is 200 us */
static void ptc_set_default_duty(uint32_t num)
{
	uint32_t data_hrc = 2000;
	uint32_t data_lrc = 4000;
	uint32_t data_cap_mode = PTC_CAPT_CONTINUE;

	/* set lcr hcr cntr */
	Set_rptc_cntr(num, 0);
	Set_rptc_hrc(num,data_hrc);
	Set_rptc_lrc(num, data_lrc);
	Set_ptc_capMode(num, data_cap_mode);/* 0:continue; 1:single */
}

/* enable pwm mode ,and don't enable interrupt */
static void ptc_start(uint32_t num)
{
	uint32_t value;
	uint32_t *reg_addr;

	reg_addr = (uint32_t *)PTC_RPTC_CTRL(num);

	value = MA_INW(reg_addr);

	value |= PTC_ECLK;
	//value |= ptc_data->capmode; ///0:continue; 1:single
	value |= PTC_EN;
	value |= PTC_OE;
	//value |= PTC_INTE;
	//value &= ~PTC_INT;
	MA_OUTW(reg_addr, value);
}

/* set GPIO PIN MUX */
static void ptc_pinmux_init(uint32_t num)
{
	uint32_t i = 0;

#if defined(CONFIG_JH_STARLIGHT)
	if(num == 0) { /* GPIOB7 */
		SET_GPIO_7_dout_pwm_pad_out_bit0;
		SET_GPIO_7_doen_LOW;
		while(0) {
			for(i=0; i<100; i++) ;
			SET_GPIO_7_dout_HIGH;
		}
	} else if(num == 1) { /* GPIOB5 */
		SET_GPIO_5_dout_pwm_pad_out_bit1;
		SET_GPIO_5_doen_LOW;
	} else if(num == 2) {
		SET_GPIO_45_dout_pwm_pad_out_bit2;
		SET_GPIO_45_doen_LOW;
	}
#elif defined(CONFIG_JH_EVB_V1)
	if(num == 0) {
		SET_GPIO_29_dout_pwm_pad_out_bit0;
		SET_GPIO_29_doen_LOW;
		while(0) {
			SET_GPIO_29_dout_LOW;
			for(i=0; i<100; i++) ;
			SET_GPIO_29_dout_HIGH;
		}
	} else if(num == 1) {
		SET_GPIO_30_dout_pwm_pad_out_bit1;
		SET_GPIO_30_doen_LOW;
	} else if(num == 2) {
		SET_GPIO_31_dout_pwm_pad_out_bit2;
		SET_GPIO_31_doen_LOW;
	} else if(num == 3) {
		SET_GPIO_32_dout_pwm_pad_out_bit3;
		SET_GPIO_32_doen_LOW;
	} else if(num == 4) {
		SET_GPIO_33_dout_pwm_pad_out_bit4;
		SET_GPIO_33_doen_LOW;
	} else if(num == 5) {
		SET_GPIO_34_dout_pwm_pad_out_bit5;
		SET_GPIO_34_doen_LOW;
	} else if(num == 6) {
		SET_GPIO_5_dout_pwm_pad_out_bit6;
		SET_GPIO_5_doen_LOW;
	} else if(num == 7) {
		SET_GPIO_6_dout_pwm_pad_out_bit7;
		SET_GPIO_6_doen_LOW;
	}
#endif
}

/*reset apb clock */
void ptc_reset_clock(void)
{
	jh_ptc_pwm_reset_clk_disable;
	jh_ptc_pwm_reset_clk_enable;
}

/* reset ptc */
void ptc_reset(void)
{
	uint32_t num = 0;

	for(num = 0; num < PTC_CAPT_ALL; num++) {
		/* set pin mux */
		ptc_pinmux_init(num);
		ptc_reset_cntr(num);
		ptc_reset_capt(num);
		ptc_reset_ctrl(num);
		ptc_set_default_duty(num);
	}

	for(num = 0; num < PTC_CAPT_ALL; num++) {
		ptc_start(num);
	}
}
