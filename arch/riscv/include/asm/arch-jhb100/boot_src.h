/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_SRC_STARFIVE_H
#define _BOOT_SRC_STARFIVE_H

#include <asm/io.h>

#define AON_SCRATCHPAD0_BASE_ADDR  0x001F32001C

#define BOOT_SRC_SFC            0x0
#define BOOT_SRC_EMMC           0x1
#define BOOT_SRC_UFS            0x2
#define BOOT_SRC_UART           0x3
#define BOOT_SRC_GMAC           0x4
#define BOOT_SRC_AUTO_DETECT    0x5
/*Debugging*/
#define HARD_SELECT_BOOT_SRC_RAM   0x6
#define BOOT_SRC_MASK              GENMASK(1, 0)

/*Get boot source reg value*/
#define GET_AON_SCRATCHPAD0(x)     readl((const void *)AON_SCRATCHPAD0_BASE_ADDR + ((x) << 2))
#define GET_BOOT_SRC               (GET_AON_SCRATCHPAD0(0) & BOOT_SRC_MASK)

u32 jhb100_get_boot_device(void);

#endif /* _BOOT_SRC_STARFIVE_H */
