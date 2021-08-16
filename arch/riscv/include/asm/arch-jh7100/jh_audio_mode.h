/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#ifndef _SIFIVE_AIC_AUDIO_H
#define _SIFIVE_AIC_AUDIO_H
///#include "vad.h"
//#include <drivers/designware_axi_dma.h>
//#include <drivers/designware_axi_dma_reg.h>

enum adci2s_sel{
	SYS_ADCI2S_NONE = -1,
	SYS_ADCI2S_SD0_SEL = 0,
	SYS_ADCI2S_SD1_SEL,
	SYS_ADCI2S_SD2_SEL,
	SYS_ADCI2S_SD0_1_SEL,
	SYS_ADCI2S_SD0_2_SEL,
	SYS_ADCI2S_SD1_2_SEL,
	SYS_ADCI2S_SD0_1_2_SEL,
};

enum audio_mode{
	AUDIO_IN_NONE = -1,
	AUDIO_IN_GPIO_SD2 = 0,
	AUDIO_IN_GPIO_SD1,
	AUDIO_IN_SPIO_SD0,
	AUDIO_IN_DAC16K_SD0,
	AUDIO_IN_ANA_ADC_SD1,
	AUDIO_IN_ANA_ADC_SD0,
	AUDIO_IN_PDM_SD1,
	AUDIO_IN_PDM_SD0,
};

enum audio_output_mode{
	AUDIO_OUT_NONE = -1,
	AUDIO_OUT_MEM = 0,
	AUDIO_OUT_DACI2S_DACAP = 1,
	AUDIO_OUT_I2S1OUT_DACAP,
	AUDIO_OUT_PWMDAC,
	AUDIO_OUT_PCM,
	AUDIO_OUT_SPDIF,
};

enum adci2s_rxmode{
	ADCI2S_POLLING = 0,
	ADCI2S_FIFO_IRQ,
	ADCI2S_DMA,
};


enum dmac_src_mode{
	NONE = -1,
	PERI2MEM_I2SDAC_RECIEV,
	MEM2PERI_PWMDAC_SEND,
};
struct damc_irq_mode
{
	unsigned char ch;
	unsigned int mode;
};


#define DMAC_PWAMDAC_POLLING_LEN	2
#define DMAC_PWAMDAC_IRQ_LEN	3


/* DMA 16 req SELECT */
#define PWMDAC_DMAREQ	4
#define SPDIF_DMAREQ	5
#define PDM_I2S_ADC_DMAREQ	1
#define PCM_TX_DMAREQ	4
#define PCM_RX_DMAREQ	5

/* dmac 8 CH */
#define DMAC_CH0	0
#define DMAC_CH1	1
#define DMAC_CH2	2
#define DMAC_CH3	3
#define DMAC_CH4	4
#define DMAC_CH5	5
#define DMAC_CH6	6
#define DMAC_CH7	7

#define PDM_I2SADC_MEM_BUF	0x38000*2


#endif /* _SIFIVE_AIC_AUDIO_H */
