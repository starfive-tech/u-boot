// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */

#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <bootm.h>
#include <command.h>
#include <env.h>
#include <env_internal.h>
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
		case 3:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
				BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case 4:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
				BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case 5:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
				BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case 6:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
				BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
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
		static const char *part_name[6] = {"SPI Primary", "SPI Secondary",
						   "EMMC Primary", "EMMC Secondary",
						   "UFS Primary", "UFS Secondary"};
		static const char *comp_name[3] = {"U-boot SPL", "U-boot Proper",
						   "Kernel"};
		int first_bit_pos = FB_RCV_L1_FW_SET_SPL_CLEAR_MSK;
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

static int do_starfive_authenticate_fit_mem(struct cmd_tbl *cmdtp, int flag, int argc,
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

static int do_starfive_authenticate_storage(struct cmd_tbl *cmdtp, int flag, int argc,
					    char *const argv[])
{
	int ret;

	argc--; argv++;
	if (argc) {
		switch (hextoul(argv[0], NULL)) {
		case 1:
			ret = starfive_req_img_auth_storage(BOOT_SRC_EMMC,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			break;
		case 2:
			ret = starfive_req_img_auth_storage(BOOT_SRC_EMMC,
							    PT_GOLDEN,
							    IMG_TYPE_KERNEL);
			break;
		case 3:
			ret = starfive_req_img_auth_memory(BOOT_SRC_SFC,
							   PT_ACTIVE,
							   IMG_TYPE_KERNEL);
			break;
		case 4:
			ret = starfive_req_img_auth_memory(BOOT_SRC_SFC,
							   PT_GOLDEN,
							   IMG_TYPE_KERNEL);
			break;
		default:
			printf("Unknown argument, refer to help command...\n");
		}
	}

	if (ret)
		return CMD_RET_FAILURE;
	return CMD_RET_SUCCESS;
}

static int do_starfive_pre_os_boot_notify(struct cmd_tbl *cmdtp, int flag, int argc,
					  char *const argv[])
{
	starfive_pre_os_boot_notify();
	return CMD_RET_SUCCESS;
}

static int do_starfive_check_sfc_dual_flash(struct cmd_tbl *cmdtp, int flag, int argc,
					    char *const argv[])
{
	if (starfive_get_sfc_cs_line_num() < 2) {
		printf("Only single SPI flash chip detected\n");
		return CMD_RET_FAILURE;
	}
	printf("Dual SPI flash chip detected\n");
	return CMD_RET_SUCCESS;
}

static int do_starfive_get_img_info(struct cmd_tbl *cmdtp, int flag, int argc,
				    char *const argv[])
{
	u32 val;

	argc--; argv++;
	if (argc) {
		switch (hextoul(argv[0], NULL)) {
		case 1:
			val = starfive_get_partition_num(BOOT_SRC_EMMC,
							 PT_ACTIVE,
							 IMG_TYPE_KERNEL);
			env_set_hex("emmc_kernel_act_part_num", (ulong)val);
			val = starfive_get_partition_offset(BOOT_SRC_EMMC,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			env_set_hex("emmc_kernel_act_part_offs", (ulong)val);
			break;
		case 2:
			val = starfive_get_partition_num(BOOT_SRC_EMMC,
							 PT_GOLDEN,
							 IMG_TYPE_KERNEL);
			env_set_hex("emmc_kernel_gol_part_num", (ulong)val);
			val = starfive_get_partition_offset(BOOT_SRC_EMMC,
							    PT_GOLDEN,
							    IMG_TYPE_KERNEL);
			env_set_hex("emmc_kernel_gol_part_offs", (ulong)val);
			break;
		case 3:
			val = starfive_get_partition_offset(BOOT_SRC_SFC,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			env_set_hex("sfc_kernel_act_part_offs", (ulong)val);
			break;
		case 4:
			if (starfive_get_sfc_cs_line_num() < 2) {
				printf("SFC Golden image not found...\n");
				printf("Golden image is stored in second flash chip...\n");
			} else {
				val = starfive_get_partition_offset(BOOT_SRC_SFC,
								    PT_GOLDEN,
								    IMG_TYPE_KERNEL);
				env_set_hex("sfc_kernel_gol_part_offs", (ulong)val);
			}
			break;
		default:
			printf("Unknown argument, refer to help command...\n");
		}
	}
	return CMD_RET_SUCCESS;
}

U_BOOT_LONGHELP(checkimgrcmap,
		"[arg\n    - Check authentication status from recovery mapping\n"
		"\tpass: 1 - spi primary\n"
		"\t      2 - spi secondary\n"
		"\t      3 - emmc primary\n"
		"\t      4 - emmc secondary\n"
		"\t      5 - ufs primary\n"
		"\t      6 - ufs secondary\n"
);

U_BOOT_LONGHELP(printaprcmap,
		"[arg\n    - Read AP recovery mapping status register\n"
		"\tpassing non-zero arg publish descriptive recovery mapping status\n"
);

U_BOOT_LONGHELP(authbm,
		"[addr [arg ...]]\n    - authenticate FIT image stored in memory\n"
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

U_BOOT_LONGHELP(authbimgstorage,
		"[addr [arg ...]]\n    - authenticate image stored in storage\n"
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

U_BOOT_LONGHELP(preosbootnotify,
		"[arg\n    - None\n"
);

U_BOOT_LONGHELP(chksfcdualflash,
		"[arg\n    - None\n"
);

U_BOOT_LONGHELP(getimginfo,
		"[arg\n    - Get image storage information\n"
		"\tpass: 1 - emmc active\n"
		"\t      2 - emmc secondary\n"
		"\t      3 - sfc active\n"
		"\t      4 - sfc active\n"
		"\t      5 - ufs active\n"
		"\t      6 - ufs active\n"
);

U_BOOT_CMD(checkimgrcmap, CONFIG_SYS_MAXARGS, 1, do_starfive_check_img_rec_map,
	   "Check authentication status from recovery mapping",
	   checkimgrcmap_help_text
);

U_BOOT_CMD(printaprcmap, CONFIG_SYS_MAXARGS, 1, do_starfive_print_rec_map,
	   "Get recovery mapping status",
	   printaprcmap_help_text
);

U_BOOT_CMD(authbm, CONFIG_SYS_MAXARGS, 1, do_starfive_authenticate_fit_mem,
	   "Authenticate FIT image from memory",
	   authbm_help_text
);

U_BOOT_CMD(authbimgstorage, CONFIG_SYS_MAXARGS, 1, do_starfive_authenticate_storage,
	   "Authenticate image in persistent storage",
	   authbimgstorage_help_text
);

U_BOOT_CMD(preosbootnotify, CONFIG_SYS_MAXARGS, 1, do_starfive_pre_os_boot_notify,
	   "Notify SCP before booting OS",
	   preosbootnotify_help_text
);

U_BOOT_CMD(chksfcdualflash, CONFIG_SYS_MAXARGS, 1, do_starfive_check_sfc_dual_flash,
	   "Check if dual SPI flash is supported",
	   chksfcdualflash_help_text
);

U_BOOT_CMD(getimginfo, CONFIG_SYS_MAXARGS, 1, do_starfive_get_img_info,
	   "Get Image storage information",
	   getimginfo_help_text
);
