/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _AP_CORE_STARFIVE_H
#define _AP_CORE_STARFIVE_H

#include <asm/io.h>

/* BMC cores status register */
#define SYS2_SYSCON_BMC_CORE_ADDR	0x00130180bc

/* Status of from first BMC cores */
#define SOC_OTP_AP_CORE_DISABLE_MSK	0x10

/* Get BMC AP cores status */
#define GET_SOC_OTP_AP_CORE_STAT(x)                     \
        (readl((const void *)SYS2_SYSCON_BMC_CORE_ADDR) \
        & (SOC_OTP_AP_CORE_DISABLE_MSK << x))

#endif /* _AP_CORE_STARFIVE_H */
