// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */

#include <blk.h>
#include <common.h>
#include <command.h>
#include <part.h>
#include <display_options.h>
#include <env.h>
#include <env_internal.h>

#define UFS_GPP_1ST_LUN		4
#define UFS_GPP_LAST_8MB	0x800000

static int do_starfive_get_ufs_gpp_size(struct cmd_tbl *cmdtp, int flag, int argc,
					char *const argv[])
{
	struct blk_desc *desc;
	int ret = blk_get_desc(UCLASS_SCSI, UFS_GPP_1ST_LUN, &desc);

	if (ret)
		return CMD_RET_FAILURE;

	if (desc->lba > 0L && desc->blksz > 0L) {
		ulong bsz, mbsz, blksize;
		lbaint_t lba;

		lba = desc->lba;
		blksize = desc->blksz;
		bsz = (lba * blksize);
		mbsz = bsz / (1024 * 1024);
#if defined(CONFIG_SYS_64BIT_LBA)
		printf (" Capacity: %lu MB = (%llu x %lu)\n",
			mbsz,
			lba,
			desc->blksz);
#else
		printf (" Capacity: %lu MB = (%lu x %lu) B\n",
			mbsz,
			(ulong)lba,
			desc->blksz);
#endif
		env_set_hex("cap_bif_hdr_ufs_offs", (ulong)((bsz - UFS_GPP_LAST_8MB) / blksize));
		return CMD_RET_SUCCESS;
	}
	return CMD_RET_FAILURE;
}

U_BOOT_LONGHELP(getufsgppsz,
		"- Get UFS GPP partition size and set the start block address of raw image\n"
		"  to 'cap_bif_hdr_ufs_offs' u-boot environment variable\n"
);

U_BOOT_CMD(getufsgppsz, CONFIG_SYS_MAXARGS, 1, do_starfive_get_ufs_gpp_size,
	   "Get UFS GPPP size",
	   getufsgppsz_help_text
);
