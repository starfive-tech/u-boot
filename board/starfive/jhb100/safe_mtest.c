// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2026 StarFive Technology Co., Ltd.
 */

#include <asm/global_data.h>
#include <command.h>
#include <common.h>
#include <lmb.h>
#include <linux/kernel.h>
#include "safe_mtest.h"

DECLARE_GLOBAL_DATA_PTR;

static int safe_mtest_region(phys_addr_t start, phys_addr_t end)
{
	char cmd[96];

	start = roundup(start, sizeof(ulong));
	end = rounddown(end, sizeof(ulong));
	if (end <= start)
		return 0;

	snprintf(cmd, sizeof(cmd), "mtest %llx %llx 0 1",
		 (unsigned long long)start,
		 (unsigned long long)(end - 1));

	return run_command(cmd, 0);

}

static int safe_mtest_memory_region(struct lmb *lmb,
				    const struct lmb_property *memory)
{
	phys_addr_t cursor = memory->base;
	phys_addr_t mem_end = memory->base + memory->size;
	unsigned long i;
	int ret;

	for (i = 0; i < lmb->reserved.cnt && cursor < mem_end; i++) {
		const struct lmb_property *reserved = &lmb->reserved.region[i];
		phys_addr_t res_start = reserved->base;
		phys_addr_t res_end = reserved->base + reserved->size;

		if (res_end <= cursor || res_start >= mem_end)
			continue;

		if (cursor < res_start) {
			ret = safe_mtest_region(cursor, res_start);
			if (ret)
				return ret;
		}

		cursor = max(cursor, res_end);
	}

	if (cursor < mem_end)
		return safe_mtest_region(cursor, mem_end);

	return 0;
}

static void lmb_reserved_sort(struct lmb *lmb)
{
	unsigned long i, j;

	for (i = 1; i < lmb->reserved.cnt; i++) {
		struct lmb_property key = lmb->reserved.region[i];

		for (j = i; j > 0 && lmb->reserved.region[j - 1].base > key.base; j--)
			lmb->reserved.region[j] = lmb->reserved.region[j - 1];

		lmb->reserved.region[j] = key;
	}
}

int starfive_safe_mtest_run(void)
{
	struct lmb lmb;
	unsigned long i;
	int ret;

	lmb_init_and_reserve(&lmb, gd->bd, (void *)gd->fdt_blob);
	lmb_reserved_sort(&lmb);

	for (i = 0; i < lmb.memory.cnt; i++) {
		ret = safe_mtest_memory_region(&lmb, &lmb.memory.region[i]);
		if (ret) {
			puts("safe_mtest: failed\n");
			return ret;
		}
	}

	puts("safe_mtest: passed\n");

	return 0;
}
