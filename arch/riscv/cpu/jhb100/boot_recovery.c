// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
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

static int do_starfive_check_img_rec_map(struct cmd_tbl *cmdtp, int flag, int argc,
					 char *const argv[])
{
	int fb_rec_map = starfive_get_fb_rec_map();

	argc--; argv++;
	if (argc) {
		switch (hextoul(argv[0], NULL)) {
		case 1:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case 2:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
				BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		default:
			printf("Unknown argument, refer to help command...\n");
		}
	}
	return CMD_RET_FAILURE;
}

static int do_starfive_print_rec_map(struct cmd_tbl *cmdtp, int flag, int argc,
				     char *const argv[])
{
	int fb_rec_map = starfive_get_fb_rec_map();
	printf("Recovery Mapping Status...%x\n", fb_rec_map);

	argc--; argv++;
	if (argv[0]) {
		static const char *part_name[] = {"SPI Primary", "SPI Secondary",
					          "EMMC Primary", "EMMC Secondary",
					          "UFS Primary", "UFS Secondary"};
		static const char *comp_name[] = {"L0 FW", "L1 FW",
					          "U-boot SPL", "U-boot Proper",
					          "Kernel"};
		int first_bit_pos = FB_RCV_ZSBL_SET_L0_FW_CLEAR_MSK;
		int last_bit_pos = FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK
				<< BOOT_SRC_PART_UFS_SECONDARY_BIT_POS;

		for (int i = first_bit_pos, j = 0; i <= last_bit_pos; i <<= 1, j++) {
			if (fb_rec_map & i)
				printf("%s - %s failed verification\n",
					part_name[(j % 6)], comp_name[j / 6]);
		}
	}
	return CMD_RET_SUCCESS;
}

static int do_starfive_authenticate(struct cmd_tbl *cmdtp, int flag, int argc,
				    char *const argv[])
{
	struct bootm_info bm_info;
	int ret;
	int states = BOOTM_STATE_START | BOOTM_STATE_FINDOS |
		     BOOTM_STATE_FINDOTHER;

	argc--; argv++;
	bootm_init(&bm_info);
	if (argc)
		bm_info.addr_img = argv[0];
	if (argc > 1)
		bm_info.conf_ramdisk = argv[1];
	if (argc > 2)
		bm_info.conf_fdt = argv[2];

	/* set up argc and argv[] since some OSes use them */
	bm_info.argc = argc;
	bm_info.argv = argv;
	bm_info.cmd_name = "bootm";

	ret = bootm_run_states(&bm_info, states);

	if (!ret)
		printf("Authentication success...\n");

	return ret ? CMD_RET_FAILURE : CMD_RET_SUCCESS;
}

U_BOOT_LONGHELP(checkimgrcmap,
	"[arg\n    - Check authentication status from recovery mapping\n"
	"\tpass: 1 - spi primary\n"
	"\t      2 - spi secondary\n"
);

U_BOOT_LONGHELP(printrcmap,
	"[arg\n    - Read recovery mapping status register\n"
	"\tpassing non-zero arg publish descriptive recovery mapping status\n"
);

U_BOOT_LONGHELP(authbm,
	"[addr [arg ...]]\n    - authenticate image stored in memory\n"
	"\tpassing arguments 'arg ...'; when verifying a Linux kernel,\n"
#if defined(CONFIG_OF_LIBFDT)
	"\tWhen authenticating an initrd image\n"
	"\ta second argument is required which is the address of the\n"
	"\tinitrd image. Otherwise, a '-' can be used in place\n"
	"\tWhen authenticating a flat device-tree\n"
	"\ta third argument is required which is the address of the\n"
	"\tdevice-tree blob.\n"
#endif
);

U_BOOT_CMD(checkimgrcmap, CONFIG_SYS_MAXARGS, 1, do_starfive_check_img_rec_map,
	   "Check authentication status from recovery mapping",
	   checkimgrcmap_help_text
);

U_BOOT_CMD(printrcmap, CONFIG_SYS_MAXARGS, 1, do_starfive_print_rec_map,
	   "Get recovery mapping status",
	   printrcmap_help_text
);

U_BOOT_CMD(authbm, CONFIG_SYS_MAXARGS, 1, do_starfive_authenticate,
	   "Authenticate FIT image from memory",
	   authbm_help_text
);
