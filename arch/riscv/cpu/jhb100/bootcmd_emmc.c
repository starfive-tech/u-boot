// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */

#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/secure_vab.h>
#include <blk.h>
#include <command.h>
#include <display_options.h>
#include <env.h>
#include <env_internal.h>
#include <mmc.h>

#define EMMC_GPP_LAST_8MB	0x800000

static int mmcdev = -1;

static struct mmc *init_mmc_dev(int dev, bool force_init,
				enum bus_mode speed_mode)
{
	struct mmc *mmc;
	mmc = find_mmc_device(dev);
	if (!mmc) {
		printf("no mmc device at slot %x\n", dev);
		return NULL;
	}

	if (!mmc_getcd(mmc))
		force_init = true;

	if (force_init)
		mmc->has_init = 0;

	if (IS_ENABLED(CONFIG_MMC_SPEED_MODE_SET))
		mmc->user_speed_mode = speed_mode;

	if (mmc_init(mmc))
		return NULL;

#ifdef CONFIG_BLOCK_CACHE
	struct blk_desc *bd = mmc_get_blk_desc(mmc);
	blkcache_invalidate(bd->uclass_id, bd->devnum);
#endif

	return mmc;
}

static int do_starfive_get_emmc_gpp_size(struct cmd_tbl *cmdtp, int flag, int argc,
					 char *const argv[])
{
	struct mmc *mmc;
	u32 val;

	if (mmcdev < 0) {
		if (get_mmc_num() > 0)
			mmcdev = 0;
		else {
			puts("No MMC device available\n");
			return CMD_RET_FAILURE;
		}
	}

	mmc = init_mmc_dev(mmcdev, false, MMC_MODES_END);
	if (!mmc)
		return CMD_RET_FAILURE;

	for (int i = 0; i < ARRAY_SIZE(mmc->capacity_gp); i++) {
		if (mmc->capacity_gp[i]) {
			printf("GP%i Capacity: ", i+1);
			print_size(mmc->capacity_gp[i], " ");
			printf("\n");
			val = mmc->capacity_gp[i];
		}
	}
	env_set_hex("cap_bif_hdr_offs", (ulong)((val - EMMC_GPP_LAST_8MB) / MMC_BLK_SIZE));
	return CMD_RET_SUCCESS;
}

U_BOOT_LONGHELP(getemmcgppsz,
		"[arg    - Get eMMC GPP size]\n"
);

U_BOOT_CMD(getemmcgppsz, CONFIG_SYS_MAXARGS, 1, do_starfive_get_emmc_gpp_size,
	   "Get eMMC GPPP size",
	   getemmcgppsz_help_text
);
