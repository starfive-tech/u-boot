/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 StarFive
 *
 */
#ifndef __ASM_RISCV_ARCH_IO_H
#define __ASM_RISCV_ARCH_IO_H
#ifdef __KERNEL__

#include <asm/io.h>

#define MA_OUTW(io, val)	(*(volatile uint32_t __iomem *)(io) = (uint32_t)(val))
#define MA_INW(io)		(*(volatile uint32_t __iomem *)(io))

#endif	/* __KERNEL__ */
#endif	/* __ASM_RISCV_ARCH_IO_H */