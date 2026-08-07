// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2023 StarFive Technology Co., Ltd.
 */

#include <common.h>
#include <irq_func.h>
#include <asm/arch/soc.h>
#include <asm/cache.h>
#include <asm/io.h>
#include <linux/bitops.h>

/*
 * cleanup_before_linux() is called just before we call linux
 * it prepares the processor for linux
 *
 * we disable interrupt and caches.
 */
int cleanup_before_linux(void)
{
	disable_interrupts();
	cache_flush();

	return 0;
}

#define JHB100_PRODUCT_ID_ADDR		0x13010038UL
#define JHB100_MASK_REV_NUM		GENMASK(3, 0)

u32 jhb100_get_product_rev_num(void)
{
	return (readl((void *)JHB100_PRODUCT_ID_ADDR) & JHB100_MASK_REV_NUM);
}
