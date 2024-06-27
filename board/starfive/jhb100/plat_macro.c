// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#include <asm/io.h>
#include <asm/arch/plat_macro.h>
#include <linux/iopoll.h>

// Cast addr in io operations to avoid compile warnings
#define __CAST_I(x)		(const volatile void *)((uintptr_t)(x))
#define __CAST_O(x)		(volatile void *)((uintptr_t)(x))

#ifndef MA_INW
#define MA_INW(io)		readl(__CAST_I(io))
#endif
#ifndef MA_OUTW
#define MA_OUTW(io, v)		writel(v, __CAST_O(io))
#endif

uint32_t itg_get_reg(uint32_t addr, uint32_t shift, uint32_t mask)
{
	uint32_t tmp;

	tmp = MA_INW(addr);
	tmp = (tmp & mask) >> shift;
	return tmp;
}

void itg_set_reg(uint32_t addr, uint32_t data, uint32_t shift, uint32_t mask)
{
	uint32_t tmp;

	tmp = MA_INW(addr);
	tmp &= ~mask;
	tmp |= (data << shift) & mask;
	MA_OUTW(addr, tmp);
}

void itg_assert_rst(uint32_t addr, uint32_t addr_status, uint32_t mask)
{
	uint32_t tmp;

	tmp = MA_INW(addr);
	tmp |= mask;
	MA_OUTW(addr, tmp);

	do {
		tmp = MA_INW(addr_status);
	} while ((tmp & mask) != 0);
}

void itg_clear_rst(uint32_t addr, uint32_t addr_status, uint32_t mask)
{
	uint32_t tmp;

	tmp = MA_INW(addr);
	tmp &= ~mask;
	MA_OUTW(addr, tmp);
	do {
		tmp = MA_INW(addr_status);
	} while ((tmp & mask) != mask);
}
