/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#ifndef __JH_PTC_H__
#define __JH_PTC_H__

#define PTC_EN		(1<<0)
#define PTC_ECLK	(1<<1)  /* 1:ptc_ecgt signal increment RPTC_CNTR. 0:system clock increment RPTC_CNTR. */
//#define PTC_ECLK	(0<<1)  /* 1:ptc_ecgt signal increment RPTC_CNTR. 0:system clock increment RPTC_CNTR. */

#define PTC_NEC		(1<<2)  /* gate:system clock or ptc_ecgt input signal to increment RPTC_CNTR. If gate function is enabled, PWM periods can be automatically adjusted with the capture input. */
#define PTC_OE		(1<<3)  /* enbale PWM output */
#define PTC_SIGNLE	(1<<4)  /* 1:single operation; 0:continue operation */
#define PTC_INTE	(1<<5)  /* Timer/Counter interrput enable */
#define PTC_INT		(1<<6)  /* interrupt status, write 1 to clear */
#define	PTC_CNTRRST	(1<<7)  /* 0:clear reset */
#define	PTC_CAPTE	(1<<8)  /* ptc_capt to increment RPTC_CNTR.*/


#define PTC_BASE_ADDR_SUB(N)		(PWM_BASE_ADDR + ((N > 3) ? ((N - 4) * 0x10 + (1 << 15)) : (N * 0x10)))
/// (0xA9040000 + N*0x10)
#define PTC_RPTC_CNTR(N)		(PTC_BASE_ADDR_SUB(N))
#define PTC_RPTC_HRC(N)			(PTC_BASE_ADDR_SUB(N) + 0x4)
#define PTC_RPTC_LRC(N)			(PTC_BASE_ADDR_SUB(N) + 0x8)
#define PTC_RPTC_CTRL(N)		(PTC_BASE_ADDR_SUB(N) + 0xC)

enum ptc_func_num{
	PTC_CAPT_0 = 0,
	PTC_CAPT_1,
	PTC_CAPT_2,
	PTC_CAPT_3,
	PTC_CAPT_4,
	PTC_CAPT_5,
	PTC_CAPT_6,
	PTC_CAPT_7,
	PTC_CAPT_ALL,
};

enum ptc_capt_mode{
	PTC_CAPT_CONTINUE = 0,
	PTC_CAPT_SINGLE,
};

void ptc_reset_clock(void);
void ptc_reset(void);

#endif
