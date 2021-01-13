// SPDX-License-Identifier: GPL-2.0+
/*
 * The 'sbi' command displays information about the SBI implementation.
 *
 * Copyright (c) 2020, Heinrich Schuchardt <xypron.glpk@gmx.de>
 */

#include <common.h>
#include <command.h>
#include <asm/arch-fu540/cache.h>

static int do_cache_debug(struct cmd_tbl *cmdtp, int flag, int argc,
			  char *const argv[])
{
	u32 way_enable;
	if (argc < 2)
		return CMD_RET_USAGE;

	way_enable = simple_strtoul(argv[1], NULL, 10);
	printf("Input is %d !\n", way_enable);
	if (way_enable >= 255)
		return CMD_RET_USAGE;

	way_enable = cache_enable_ways_debug(way_enable);
	printf("Readback is %d !\n", way_enable);

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	cache_debug,	2,	0,	do_cache_debug,
	"cache config debug",
	"wayenable number"
);
