/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#ifndef __VAD_H__
#define __VAD_H__


#define VAD_LEFT_MARGIN               I2S_VAD_BASE_ADDR + 0x800
#define VAD_RIGHT_MARGIN              I2S_VAD_BASE_ADDR + 0x804
#define VAD_N_LOW_CONT_FRAMES         I2S_VAD_BASE_ADDR + 0x808
#define VAD_N_LOW_SEEK_FRAMES         I2S_VAD_BASE_ADDR + 0x80C
#define VAD_N_HIGH_CONT_FRAMES        I2S_VAD_BASE_ADDR + 0x810
#define VAD_N_HIGH_SEEK_FRAMES        I2S_VAD_BASE_ADDR + 0x814
#define VAD_N_SPEECH_LOW_HIGH_FRAMES  I2S_VAD_BASE_ADDR + 0x818
#define VAD_N_SPEECH_LOW_SEEK_FRAMES  I2S_VAD_BASE_ADDR + 0x81C
#define VAD_MEAN_SIL_FRAMES           I2S_VAD_BASE_ADDR + 0x820
#define VAD_N_ALPHA                   I2S_VAD_BASE_ADDR + 0x824
#define VAD_N_BETA                    I2S_VAD_BASE_ADDR + 0x828
#define VAD_FIFO_DEPTH                I2S_VAD_BASE_ADDR + 0x82C
#define VAD_LR_SEL                    I2S_VAD_BASE_ADDR + 0x840
#define VAD_SW                        I2S_VAD_BASE_ADDR + 0x844
#define VAD_LEFT_WD                   I2S_VAD_BASE_ADDR + 0x848
#define VAD_RIGHT_WD                  I2S_VAD_BASE_ADDR + 0x84C
#define VAD_STOP_DELAY                I2S_VAD_BASE_ADDR + 0x850
#define VAD_ADDR_START                I2S_VAD_BASE_ADDR + 0x854
#define VAD_ADDR_WRAP                 I2S_VAD_BASE_ADDR + 0x858
#define VAD_MEM_SW                    I2S_VAD_BASE_ADDR + 0x85C
#define VAD_SPINT_CLR                 I2S_VAD_BASE_ADDR + 0x860
#define VAD_SPINT_EN                  I2S_VAD_BASE_ADDR + 0x864
#define VAD_SLINT_CLR                 I2S_VAD_BASE_ADDR + 0x868
#define VAD_SLINT_EN                  I2S_VAD_BASE_ADDR + 0x86C
#define VAD_RAW_SPINT                 I2S_VAD_BASE_ADDR + 0x870
#define VAD_RAW_SLINT                 I2S_VAD_BASE_ADDR + 0x874
#define VAD_SPINT                     I2S_VAD_BASE_ADDR + 0x878
#define VAD_SLINT                     I2S_VAD_BASE_ADDR + 0x87C

#define VAD_XMEM_ADDR                (I2S_VAD_BASE_ADDR + 0x880)  //16bit index
#define SCFG_vad_i2s_ctrl_REG_ADDR   (I2S_VAD_BASE_ADDR + 0x884)
#define VAD_AIX_MEM_ADDR             (0x701F0000)

#define  _SET_SYSCON_REG_SCFG_ctrl_i2sadc_enable { \
	uint32_t value = MA_INW(VAD_SW); \
	value &= ~(1<<1); \
	value |= (1<<1); \
	MA_OUTW(VAD_SW, value); \
}

#define _SET_SYSCON_REG_SCFG_ctrl_i2sadc_disable { \
	uint32_t value = MA_INW(VAD_SW); \
	value &= ~(1<<1); \
	MA_OUTW(VAD_SW, value); \
}

#define _SET_SYSCON_REG_SCFG_aon_i2s_ctrl_adci2s_d0_sel(v) { \
	uint32_t _ezchip_macro_read_value_=MA_INW(SCFG_vad_i2s_ctrl_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x7); \
	_ezchip_macro_read_value_ |= (v&0x7); \
	MA_OUTW(SCFG_vad_i2s_ctrl_REG_ADDR,_ezchip_macro_read_value_); \
}

#define _GET_SYSCON_REG_SCFG_aon_i2s_ctrl_adci2s_d0_sel(_ezchip_read_value_) { \
	uint32_t _ezchip_macro_read_value_=MA_INW(SCFG_vad_i2s_ctrl_REG_ADDR); \
	_ezchip_macro_read_value_ &= 0x7;\
}

#define _SET_SYSCON_REG_SCFG_aon_i2s_ctrl_adci2s_d1_sel(v) { \
	uint32_t _ezchip_macro_read_value_=MA_INW(SCFG_vad_i2s_ctrl_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x7<<3); \
	_ezchip_macro_read_value_ |= (v&0x7)<<3; \
	MA_OUTW(SCFG_vad_i2s_ctrl_REG_ADDR,_ezchip_macro_read_value_); \
}

#define _GET_SYSCON_REG_SCFG_aon_i2s_ctrl_adci2s_d1_sel(_ezchip_read_value_) { \
	uint32_t _ezchip_macro_read_value_=MA_INW(SCFG_vad_i2s_ctrl_REG_ADDR) >> 3; \
	_ezchip_macro_read_value_ &= 0x7;\
}

#define _SET_SYSCON_REG_SCFG_aon_i2s_ctrl_adci2s_d2_sel(v) { \
	uint32_t _ezchip_macro_read_value_=MA_INW(SCFG_vad_i2s_ctrl_REG_ADDR); \
	_ezchip_macro_read_value_ &= ~(0x7<<6); \
	_ezchip_macro_read_value_ |= (v&0x7)<<6; \
	MA_OUTW(SCFG_vad_i2s_ctrl_REG_ADDR,_ezchip_macro_read_value_); \
}

#define _GET_SYSCON_REG_SCFG_aon_i2s_ctrl_adci2s_d2_sel(_ezchip_read_value_) { \
	uint32_t _ezchip_macro_read_value_=MA_INW(SCFG_vad_i2s_ctrl_REG_ADDR) >> 6; \
	_ezchip_macro_read_value_ &= 0x7;\
}

#endif
