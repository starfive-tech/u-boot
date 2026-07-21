// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 * Author:	Wei Sheng Ch'ng <weisheng.chng@starfivetech.com>
 */

#include <config.h>
#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_src.h>
#include <bootm.h>
#include <command.h>
#include <env.h>
#include <linux/bitops.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <mapmem.h>
#include <dm.h>
#include <image.h>
#include <log.h>

#define JHB100_ENV_VERSION_VAR	"jhb100_env_version"

/*
 * Values a user is expected to set up once per board on the bench
 * (network identity) and that should survive an env reset triggered
 * by flashing a different defconfig variant.
 */
static const char * const jhb100_env_preserve_vars[] = {
	"ethaddr",
	"eth1addr",
	"eth2addr",
	"eth3addr",
	"ipaddr",
	"serverip",
	"gatewayip",
	"netmask",
};

/*
 * Each defconfig variant (AGT/AB partition layout, SFC/MMC/UFS storage
 * backends compiled in, capsule support present or not, ...) ships a
 * different set of env commands/vars, see JHB100_ENV_VERSION in
 * starfive-jhb100.h. If a board is reflashed with a different defconfig
 * while keeping an old saved environment, stale entries from the previous
 * layout can linger (e.g. dangling "run <cmd-no-longer-defined>" scripts).
 * Detect the mismatch here and reset the environment to the compiled-in
 * defaults for the current build, preserving the identity/network vars
 * above so the user does not need to re-enter them after every switch.
 */
void jhb100_env_check_version(void)
{
	char preserved[ARRAY_SIZE(jhb100_env_preserve_vars)][32];
	bool has_value[ARRAY_SIZE(jhb100_env_preserve_vars)];
	const char *cur_ver = env_get(JHB100_ENV_VERSION_VAR);
	unsigned int i;

	if (cur_ver && !strcmp(cur_ver, JHB100_ENV_VERSION))
		return;

	printf("Environment layout mismatch (found \"%s\", expect \"%s\"), resetting environment to defaults ...\n",
	       cur_ver ? cur_ver : "none", JHB100_ENV_VERSION);

	for (i = 0; i < ARRAY_SIZE(jhb100_env_preserve_vars); i++) {
		const char *val = env_get(jhb100_env_preserve_vars[i]);

		has_value[i] = !!val;
		if (val)
			strlcpy(preserved[i], val, sizeof(preserved[i]));
	}

	env_set_default("board defconfig/env layout changed", 0);

	for (i = 0; i < ARRAY_SIZE(jhb100_env_preserve_vars); i++) {
		if (has_value[i])
			env_set(jhb100_env_preserve_vars[i], preserved[i]);
	}

	env_set(JHB100_ENV_VERSION_VAR, JHB100_ENV_VERSION);
	env_save();
}

void restore_deep_bootcmd(void)
{
	/* This is deep restoration of critical boot envs */
	const char * const boot_vars[] = {
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
	env_set_default_vars(ARRAY_SIZE(boot_vars), (char * const *)boot_vars, 0);
}

void restore_bootcmd_utils(void)
{
	const char * const boot_vars[] = {
		"auth_and_boot",
		"uncompfitimage",
		"kernel_autoboot",
		"bootargs",
		"bootcmd",
		"bootdelay",
		"ethaddr",
		"eth1addr",
		"eth2addr",
		"eth3addr",
		"set_bootargs_root_ram",
		"set_bootargs_root_storage_mmc",
		"set_bootargs_root_storage_ufs",
	};

	/*
	 * Restore the above SFC boot envs to their default values, in case users
	 * managed to override or delete them.
	 */
	env_set_default_vars(ARRAY_SIZE(boot_vars), (char * const *)boot_vars, 0);
}

void restore_bootcmd_sfc(void)
{
	const char * const boot_vars[] = {
		"loadfitimagespiprim",
		"loadfitimagespisec",
		"loadcompfitimagespiprim",
		"loadcompfitimagespisec",
		"loadfitimagespiact",
		"loadfitimagespigol",
		"kernel_fit_spi_prim_off",
		"kernel_fit_spi_sec_off",
		"kernel_auth_boot_spi",
		"kernel_comp_auth_boot_spi",
		"auth_boot_kernel_fit_sfc",
		"auth_pre_os_bootm",
	};

	/*
	 * Restore the above SFC boot envs to their default values, in case users
	 * managed to override or delete them.
	 */
	env_set_default_vars(ARRAY_SIZE(boot_vars), (char * const *)boot_vars, 0);
}

void restore_bootcmd_emmc(void)
{
	const char * const boot_vars[] = {
		"mmcdev",
		"mmcpart",
		"loadfitimagefatprim",
		"loadfitimagefatsec",
		"loadcompfitimagefatprim",
		"loadcompfitimagefatsec",
		"loademmcimgext4",
		"kernel_auth_boot_emmc",
		"kernel_comp_auth_boot_emmc",
		"auth_boot_kernel_fit_emmc",
		"auth_boot_kernel_emmc",
	};

	/*
	 * Restore the above eMMC boot envs to their default values, in case users
	 * managed to override or delete them.
	 */
	env_set_default_vars(ARRAY_SIZE(boot_vars), (char * const *)boot_vars, 0);
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
