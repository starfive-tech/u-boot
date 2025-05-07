// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 * Author:	Wei Sheng Ch'ng <weisheng.chng@starfivetech.com>
 */

#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_src.h>
#include <bootm.h>
#include <command.h>
#include <env.h>
#include <linux/bitops.h>
#include <mapmem.h>
#include <dm.h>
#include <image.h>
#include <log.h>

void restore_deep_bootcmd(void)
{
	/* This is deep restoration of critical boot envs */
	const char * const boot_vars[13] = {
		"bootfile",
		"fitbootfile",
		"fitbootrecfile",
		"fdtfile",
		"fdt_addr_r",
		"kernel_addr_r",
		"kernel_comp_addr_r",
		"kernel_fit_load_size",
		"kernel_fit_comp_load_size",
		"loadaddr",
		"ramdiskfile",
		"ramdisk_size",
		"ramdisk_addr_r",
	};

	/*
	 * Restore the above boot envs to their default values, in case users
	 * managed to override or delete them.
	 */
	env_set_default_vars(13, (char * const *)boot_vars, 0);
}

void restore_bootcmd_utils(void)
{
	const char * const boot_vars[2] = {
		"auth_and_boot",
		"uncompfitimage",
	};

	/*
	 * Restore the above SFC boot envs to their default values, in case users
	 * managed to override or delete them.
	 */
	env_set_default_vars(2, (char * const *)boot_vars, 0);
}

void restore_bootcmd_sfc(void)
{
	const char * const boot_vars[8] = {
		"loadfitimagespiprim",
		"loadfitimagespisec",
		"loadcompfitimagespiprim",
		"loadcompfitimagespisec",
		"kernel_fit_spi_prim_off",
		"kernel_fit_spi_sec_off",
		"kernel_auth_boot_spi",
		"kernel_comp_auth_boot_spi",
	};

	/*
	 * Restore the above SFC boot envs to their default values, in case users
	 * managed to override or delete them.
	 */
	env_set_default_vars(8, (char * const *)boot_vars, 0);
}

void restore_bootcmd_emmc(void)
{
	const char * const boot_vars[8] = {
		"mmcdev",
		"mmcpart",
		"loadfitimagefatprim",
		"loadfitimagefatsec",
		"loadcompfitimagefatprim",
		"loadcompfitimagefatsec",
		"kernel_auth_boot_emmc",
		"kernel_comp_auth_boot_emmc",
	};

	/*
	 * Restore the above eMMC boot envs to their default values, in case users
	 * managed to override or delete them.
	 */
	env_set_default_vars(8, (char * const *)boot_vars, 0);
}

static int do_starfive_bootcmd_restore(struct cmd_tbl *cmdtp, int flag, int argc,
				       char *const argv[])
{
	if (argc == 1)
		goto err;
	restore_bootcmd_utils();

	while (--argc > 0) {
		if (**++argv == '-') {
			char *c_arg = *argv;

			/* Force deep restore critical boot command */
			switch (*++c_arg) {
			case 'f':
				restore_deep_bootcmd();
				restore_bootcmd_emmc();
				restore_bootcmd_sfc();

				printf("All Boot Command Restored!\n");
				return CMD_RET_SUCCESS;
			default:
				goto err;
			}
		} else {
			switch (hextoul(argv[0], NULL)) {
			case 1:
				restore_bootcmd_emmc();
				printf("eMMC Boot Command Restored!\n");
				break;
			case 2:
				restore_bootcmd_sfc();
				printf("SFC Boot Command Restored!\n");
				break;
			default:
				goto err;
			}
		}
	}
	return CMD_RET_SUCCESS;
err:
	printf("Unknown argument, refer to help command...\n");
	return CMD_RET_USAGE;
}

U_BOOT_LONGHELP(bootcmdrest,
		"[arg\n    - Set critical boot command into env variables\n"
		"\tpass: 1 - emmc\n"
		"\t      2 - sfc\n"
		"\t     -f - deep restore\n"
		"\tIf no arg passed, restore everything\n"
		"\tAuthentication and booting function is loaded from default environment\n"
		"\tThe critical boot command is then added to any customised environments\n"
		"\twithout overriding or erasing user's environments\n"
		"\tCritical boot command if present in user's environment though\n"
		"\twill always be overridden after running this command\n"
);

U_BOOT_CMD(bootcmdrest, CONFIG_SYS_MAXARGS, 1, do_starfive_bootcmd_restore,
	   "Correct critical boot command",
	   bootcmdrest_help_text
);
