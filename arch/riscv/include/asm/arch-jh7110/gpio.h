// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 Starfive, Inc.
 * Author:	yanhong <yanhong.wang@starfivetech.com>
 *
 */

#ifndef _GPIO_STARFIVE_H_
#define _GPIO_STARFIVE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GPIO_NUM_SHIFT	2 /*one dword include 4 gpios*/
#define GPIO_BYTE_SHIFT	3

#define GPIO_INDEX_MASK	0x3

#define GPIO_DOEN_MASK	0x3f
#define GPIO_DOUT_MASK	0x7f
#define GPIO_DIN_MASK	0x7f

#define NR_GPIOS		64

#define GPIO_OFFSET(gpio)	\
	(((gpio) >> GPIO_NUM_SHIFT) << GPIO_NUM_SHIFT)

#define GPIO_SHIFT(gpio) \
	(((gpio) & GPIO_INDEX_MASK) << GPIO_BYTE_SHIFT)

enum gpio_state {
	LOW,
	HIGH
};

#define GPIO_DOEN	0x0
#define GPIO_DOUT	0x40
#define GPIO_DIN	0x80
#define GPIO_EN		0xdc
#define GPIO_LOW_IE		0x100
#define GPIO_HIGH_IE	0x104

/* Details about a GPIO bank */
struct starfive_gpio_platdata {
	void		*base;
};

#ifdef __cplusplus
}
#endif

#endif /* _GPIO_STARFIVE_H_ */
