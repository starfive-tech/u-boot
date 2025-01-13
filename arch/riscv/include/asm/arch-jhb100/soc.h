/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _STARFIVE_SOC_H
#define _STARFIVE_SOC_H

#define JHB100_CACHEABLE_DDR_BASE_ADDR		(0x40000000UL)
#define JHB100_UNCACHEABLE_DDR_BASE_ADDR	(0x400000000UL)

static inline bool is_cpu_addr(dma_addr_t addr)
{
	return ((addr) >= JHB100_CACHEABLE_DDR_BASE_ADDR &&
		(addr) < JHB100_UNCACHEABLE_DDR_BASE_ADDR);
}

static inline dma_addr_t cpu_to_dma_addr(dma_addr_t addr)
{
	if (is_cpu_addr(addr)) {
		return JHB100_UNCACHEABLE_DDR_BASE_ADDR +
			((addr) - JHB100_CACHEABLE_DDR_BASE_ADDR);
	}

	return addr;
}

#endif /* _STARFIVE_SOC_H */
