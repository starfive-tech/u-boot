// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */

#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/secure_vab.h>
#include <bootm.h>
#include <command.h>
#include <env.h>
#include <env_internal.h>
#include <linux/bitops.h>
#include <mapmem.h>
#include <dm.h>
#include <image.h>
#include <log.h>

#define PRIMARY_IMG		1
#define SECONDARY_IMG		2

#define EMMC_PRIMARY		1
#define EMMC_SECONDARY		2
#define UFS_PRIMARY		3
#define UFS_SECONDARY		4
#define SFC_PRIMARY		5
#define SFC_SECONDARY		6

static int do_starfive_check_img_rec_map(struct cmd_tbl *cmdtp, int flag, int argc,
					 char *const argv[])
{
	int fb_rec_map = starfive_get_fb_rec_map();

	argc--; argv++;
	if (argc) {
		switch (hextoul(argv[0], NULL)) {
		case EMMC_PRIMARY:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
				BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case EMMC_SECONDARY:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
				BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case UFS_PRIMARY:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
				BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case UFS_SECONDARY:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
				BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case SFC_PRIMARY:
			if (starfive_fb_rec_map_handler(&fb_rec_map,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
				CHECK))
				return CMD_RET_SUCCESS;
			break;
		case SFC_SECONDARY:
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

static int do_starfive_set_img_rec_map(struct cmd_tbl *cmdtp, int flag, int argc,
				       char *const argv[])
{
	int fb_rec_map = starfive_get_fb_rec_map();

	argc--; argv++;
	if (argc) {
		switch (hextoul(argv[0], NULL)) {
		case EMMC_PRIMARY:
			starfive_fb_rec_map_handler(&fb_rec_map,
						    BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
						    BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
						    FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
						    SET);
			break;
		case EMMC_SECONDARY:
			starfive_fb_rec_map_handler(&fb_rec_map,
						    BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
						    BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
						    FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
						    SET);
			break;
		case UFS_PRIMARY:
			starfive_fb_rec_map_handler(&fb_rec_map,
						    BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
						    BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
						    FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
						    SET);
			break;
		case UFS_SECONDARY:
			starfive_fb_rec_map_handler(&fb_rec_map,
						    BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
						    BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
						    FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
						    SET);
			break;
		case SFC_PRIMARY:
			starfive_fb_rec_map_handler(&fb_rec_map,
						    BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
						    BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
						    FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
						    SET);
			break;
		case SFC_SECONDARY:
			starfive_fb_rec_map_handler(&fb_rec_map,
						    BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
						    BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
						    FB_RCV_UBOOT_PROP_SET_KERNEL_CLEAR_MSK,
						    SET);
			break;
		default:
			printf("Unknown argument, refer to help command...\n");
			return CMD_RET_USAGE;
		}
	}
	starfive_set_fb_rec_map(fb_rec_map);
	return CMD_RET_SUCCESS;
}

static int do_starfive_print_rec_map(struct cmd_tbl *cmdtp, int flag, int argc,
				     char *const argv[])
{
	int fb_rec_map = starfive_get_fb_rec_map();
	printf("Recovery Mapping Status...%x\n", fb_rec_map);

	argc--; argv++;
	if (argv[0]) {
		static const char *part_name[6] = {"eMMC Active", "eMMC Golden",
						   "UFS Active", "UFS Golden",
						   "SFC Active", "SFC Golden"};
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
	int ret = -1;

	argc--; argv++;
	if (argc) {
		switch (hextoul(argv[0], NULL)) {
		case EMMC_PRIMARY:
			ret = starfive_req_img_auth_storage(BOOT_SRC_EMMC,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			if (!ret)
				starfive_set_ap_sts_image_flag(BOOTSTG_KERNEL, ACT_IMG);
			break;
		case EMMC_SECONDARY:
			ret = starfive_req_img_auth_storage(BOOT_SRC_EMMC,
							    PT_GOLDEN,
							    IMG_TYPE_KERNEL);
			if (!ret)
				starfive_set_ap_sts_image_flag(BOOTSTG_KERNEL, GOL_IMG);
			break;
		case UFS_PRIMARY:
			ret = starfive_req_img_auth_storage(BOOT_SRC_UFS,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			if (!ret)
				starfive_set_ap_sts_image_flag(BOOTSTG_KERNEL, ACT_IMG);
			break;
		case UFS_SECONDARY:
			ret = starfive_req_img_auth_storage(BOOT_SRC_UFS,
							    PT_GOLDEN,
							    IMG_TYPE_KERNEL);
			if (!ret)
				starfive_set_ap_sts_image_flag(BOOTSTG_KERNEL, GOL_IMG);
			break;
		case SFC_PRIMARY:
			ret = starfive_req_img_auth_storage(BOOT_SRC_SFC,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			break;
		case SFC_SECONDARY:
			ret = starfive_req_img_auth_storage(BOOT_SRC_SFC,
							    PT_GOLDEN,
							    IMG_TYPE_KERNEL);
			break;
		default:
			printf("Unknown argument, refer to help command...\n");
		}
	}

	starfive_set_ap_ctl_boot_stage(BOOTSTG_KERNEL, BOOTSTG_KERNEL);
	starfive_add_ap_sts_retry_cnt(BOOTSTG_KERNEL, BOOT_TRIAL_CNT);

	if (ret)
		return CMD_RET_FAILURE;
	return CMD_RET_SUCCESS;
}

static int do_starfive_set_kernel_image_flag(struct cmd_tbl *cmdtp, int flag, int argc,
					     char *const argv[])
{
	argc--; argv++;
	if (argc) {
		switch (hextoul(argv[0], NULL)) {
		case PRIMARY_IMG:
			starfive_set_ap_sts_image_flag(BOOTSTG_KERNEL, ACT_IMG);
			break;
		case SECONDARY_IMG:
			starfive_set_ap_sts_image_flag(BOOTSTG_KERNEL, GOL_IMG);
			break;
		default:
			printf("Unknown argument, refer to help command...\n");
		}
	}

	starfive_set_ap_ctl_boot_stage(BOOTSTG_KERNEL, BOOTSTG_KERNEL);
	return CMD_RET_SUCCESS;
}

static int do_starfive_pre_os_boot_notify(struct cmd_tbl *cmdtp, int flag, int argc,
					  char *const argv[])
{
	argc--; argv++;
	if (argc)
		starfive_pre_os_boot_notify(hextoul(argv[0], NULL));

	return CMD_RET_SUCCESS;
}

static int do_starfive_check_sfc_dual_flash(struct cmd_tbl *cmdtp, int flag, int argc,
					    char *const argv[])
{
	if (starfive_get_sfc_cs_line_num() == CONFIG_SF_CS1) {
		printf("Golden image found in CS1...\n");
		env_set_hex("cs_num", (ulong)CONFIG_SF_CS1);
	} else {
		printf("Golden image found in CS0...\n");
		env_set_hex("cs_num", (ulong)CONFIG_SF_DEFAULT_CS);
	}
	return CMD_RET_SUCCESS;
}

static int do_starfive_get_img_info(struct cmd_tbl *cmdtp, int flag, int argc,
				    char *const argv[])
{
	u32 val;

	argc--; argv++;
	if (argc) {
		switch (hextoul(argv[0], NULL)) {
		case EMMC_PRIMARY:
			val = starfive_get_partition_num(BOOT_SRC_EMMC,
							 PT_ACTIVE,
							 IMG_TYPE_KERNEL);
			env_set_hex("emmc_kernel_act_part_num", (ulong)val);
			env_set_hex("blk_num", (ulong)(val - 4));
			val = starfive_get_partition_offset(BOOT_SRC_EMMC,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			env_set_hex("emmc_kernel_act_part_offs", (ulong)val);
			break;
		case EMMC_SECONDARY:
			val = starfive_get_partition_num(BOOT_SRC_EMMC,
							 PT_GOLDEN,
							 IMG_TYPE_KERNEL);
			env_set_hex("emmc_kernel_gol_part_num", (ulong)val);
			env_set_hex("blk_num", (ulong)(val - 4));
			val = starfive_get_partition_offset(BOOT_SRC_EMMC,
							    PT_GOLDEN,
							    IMG_TYPE_KERNEL);
			env_set_hex("emmc_kernel_gol_part_offs", (ulong)val);
			break;
		case UFS_PRIMARY:
			val = starfive_get_partition_num(BOOT_SRC_UFS,
							 PT_ACTIVE,
							 IMG_TYPE_KERNEL);
			env_set_hex("ufs_kernel_act_part_num", (ulong)val);
			val = starfive_get_partition_offset(BOOT_SRC_UFS,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			env_set_hex("ufs_kernel_act_part_offs", (ulong)val);
			break;
		case UFS_SECONDARY:
			val = starfive_get_partition_num(BOOT_SRC_UFS,
							 PT_GOLDEN,
							 IMG_TYPE_KERNEL);
			env_set_hex("ufs_kernel_gol_part_num", (ulong)val);
			val = starfive_get_partition_offset(BOOT_SRC_UFS,
							    PT_GOLDEN,
							    IMG_TYPE_KERNEL);
			env_set_hex("ufs_kernel_gol_part_offs", (ulong)val);
			break;
		case SFC_PRIMARY:
			if (starfive_get_sfc_cs(PT_ACTIVE, IMG_TYPE_KERNEL) == CONFIG_SF_CS1) {
				printf("Active image is stored in CS1...\n");
				env_set_hex("cs_num", (ulong)CONFIG_SF_CS1);
			} else {
				printf("Active image is stored in CS0...\n");
				env_set_hex("cs_num", (ulong)CONFIG_SF_DEFAULT_CS);
			}
			val = starfive_get_partition_offset(BOOT_SRC_SFC,
							    PT_ACTIVE,
							    IMG_TYPE_KERNEL);
			env_set_hex("sfc_kernel_act_part_offs", (ulong)val);
			val = starfive_get_image_size(BOOT_SRC_SFC,
						      PT_ACTIVE,
						      IMG_TYPE_KERNEL);
			env_set_hex("kernel_fit_load_size", (ulong)val);
			env_set_hex("kernel_fit_comp_load_size", (ulong)val);
			break;
		case SFC_SECONDARY:
			if (starfive_get_sfc_cs(PT_GOLDEN, IMG_TYPE_KERNEL) == CONFIG_SF_CS1) {
				printf("Golden image is stored in CS1...\n");
				env_set_hex("cs_num", (ulong)CONFIG_SF_CS1);
			} else {
				printf("Golden image is stored in CS0...\n");
				env_set_hex("cs_num", (ulong)CONFIG_SF_DEFAULT_CS);
			}
			val = starfive_get_partition_offset(BOOT_SRC_SFC,
							    PT_GOLDEN,
							    IMG_TYPE_KERNEL);
			env_set_hex("sfc_kernel_gol_part_offs", (ulong)val);
			val = starfive_get_image_size(BOOT_SRC_SFC,
						      PT_GOLDEN,
						      IMG_TYPE_KERNEL);
			env_set_hex("kernel_fit_load_size", (ulong)val);
			env_set_hex("kernel_fit_comp_load_size", (ulong)val);
			break;
		default:
			printf("Unknown argument, refer to help command...\n");
		}
	}
	return CMD_RET_SUCCESS;
}

static int do_starfive_parse_capsule(struct cmd_tbl *cmdtp, int flag, int argc,
				     char *const argv[])
{
	u32 rofs_blk_size, rofs_ufs_blk_size, rofs_size, rofs_offs, place_holder;

	argc--; argv++;
	if (argc) {
		if (starfive_jhb100_parse_capsule(&rofs_blk_size, &rofs_ufs_blk_size,
						  &rofs_size, &rofs_offs,
						  hextoul(argv[0], NULL)))
			return CMD_RET_FAILURE;

		/* Get eMMC partition from PTI */
		u32 val = starfive_get_partition_num(BOOT_SRC_EMMC,
					     	     PT_TEMP,
					     	     IMG_TYPE_KERNEL);

		env_set_hex("emmc_temp_partition", (ulong)val);
		val = starfive_get_partition_num(BOOT_SRC_EMMC,
					 	 PT_ACTIVE,
					 	 IMG_TYPE_KERNEL);

		env_set_hex("emmc_act_partition", (ulong)val);
		val = starfive_get_partition_num(BOOT_SRC_EMMC,
					 	 PT_GOLDEN,
					 	 IMG_TYPE_KERNEL);

		env_set_hex("emmc_gol_partition", (ulong)val);

		/* Get UFS partition from PTI */
		val = starfive_get_partition_num(BOOT_SRC_UFS,
						 PT_TEMP,
						 IMG_TYPE_KERNEL);

		env_set_hex("ufs_temp_partition", (ulong)val);
		val = starfive_get_partition_num(BOOT_SRC_UFS,
						 PT_ACTIVE,
						 IMG_TYPE_KERNEL);

		env_set_hex("ufs_act_partition", (ulong)val);
		val = starfive_get_partition_num(BOOT_SRC_UFS,
						 PT_GOLDEN,
						 IMG_TYPE_KERNEL);

		env_set_hex("ufs_gol_partition", (ulong)val);

		/* Get SFC CS# from PTI */
		val = starfive_get_sfc_cs(PT_TEMP, IMG_TYPE_KERNEL);
		env_set_hex("sfc_temp_cs", (ulong)val);

		val = starfive_get_sfc_cs(PT_ACTIVE, IMG_TYPE_KERNEL);
		env_set_hex("sfc_act_cs", (ulong)val);

		val = starfive_get_sfc_cs(PT_GOLDEN, IMG_TYPE_KERNEL);
		env_set_hex("sfc_gol_cs", (ulong)val);

		val = starfive_get_sfc_part_size(PT_TEMP,
						 IMG_TYPE_KERNEL);
		env_set_hex("sfc_part_size", (ulong)val);
		place_holder = val;

		val = starfive_get_partition_offset(BOOT_SRC_SFC,
						    PT_TEMP,
						    IMG_TYPE_KERNEL);
		env_set_hex("sfc_temp_part_offs", (ulong)val);
		env_set_hex("sfc_part_last_8mb_temp", (ulong)(place_holder + val - EIGHT_MB));

		val = starfive_get_partition_offset(BOOT_SRC_SFC,
						    PT_ACTIVE,
						    IMG_TYPE_KERNEL);
		env_set_hex("sfc_act_part_offs", (ulong)val);
		env_set_hex("sfc_part_last_8mb_act", (ulong)(place_holder + val - EIGHT_MB));

		val = starfive_get_partition_offset(BOOT_SRC_SFC,
						    PT_GOLDEN,
						    IMG_TYPE_KERNEL);
		env_set_hex("sfc_gol_part_offs", (ulong)val);
		env_set_hex("sfc_part_last_8mb_gol", (ulong)(place_holder + val - EIGHT_MB));

		env_set_hex("8mb_size", (ulong)(EIGHT_MB));

		env_set_hex("rofs_blk_offs", (ulong)(((rofs_offs -
			    hextoul(argv[0], NULL)) / MMC_BLK_SIZE) + 1));
		env_set_hex("rofs_ufs_blk_offs", (ulong)(((rofs_offs -
			    hextoul(argv[0], NULL)) / UFS_BLK_SIZE) + 1));
		env_set_hex("rofs_blk_size", (ulong)rofs_blk_size);
		env_set_hex("rofs_ufs_blk_size", (ulong)rofs_ufs_blk_size);
		env_set_hex("rofs_size", (ulong)rofs_size);
		env_set_hex("rofs_offs", (ulong)rofs_offs);
	} else {
		printf("Unknown argument, refer to help command...\n");
		return CMD_RET_USAGE;
	}

	return CMD_RET_SUCCESS;
}

static int do_starfive_check_secure_boot(struct cmd_tbl *cmdtp, int flag, int argc,
					 char *const argv[])
{
	int ret = starfive_check_secure_boot();

	if (ret < 0)
		return -EINVAL;

	env_set_hex("secureboot", (ulong)(ret));

	return !ret;
}

U_BOOT_LONGHELP(checkimgrcmap,
		"[arg\n    - Check authentication status from recovery mapping\n"
		"\tpass: 1 - eMMC Active\n"
		"\t      2 - eMMC Golden\n"
		"\t      3 - UFS Active\n"
		"\t      4 - UFS Golden\n"
		"\t      5 - SFC Active\n"
		"\t      6 - SFC Golden\n"
);

U_BOOT_LONGHELP(setimgrcmap,
		"[arg\n    - Set authentication status to recovery mapping\n"
		"\tpass: 1 - eMMC Active\n"
		"\t      2 - eMMC Golden\n"
		"\t      3 - UFS Active\n"
		"\t      4 - UFS Golden\n"
		"\t      5 - SFC Active\n"
		"\t      6 - SFC Golden\n"
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

U_BOOT_LONGHELP(setkernelimgflg,
		"[arg\n    - Set AP status image flag\n"
		"\tpass: 1 - Primary\n"
		"\t      2 - Secondary\n"
);

U_BOOT_LONGHELP(preosbootnotify,
		"[arg\n    - Notify secureity core before booting OS\n"
		"\tpass: 0 - Active ROFS validated\n"
		"\t	 1 - Golden ROFS validated\n"
		"\t	 2 - Temp/Recovery ROFS validated\n"
);

U_BOOT_LONGHELP(chksfcdualflash,
		"[arg\n    - None\n"
);

U_BOOT_LONGHELP(getimginfo,
		"[arg\n    - Get image storage information\n"
		"\tpass: 1 - eMMC Active\n"
		"\t      2 - eMMC Golden\n"
		"\t      3 - UFS Active\n"
		"\t      4 - UFS Golden\n"
		"\t      5 - SFC Active\n"
		"\t      6 - SFC Golden\n"
);

U_BOOT_LONGHELP(parsecap,
		"[arg    - Hex address in memory]\n"
);

U_BOOT_LONGHELP(checksecboot,
		"[arg\n    - None\n"
);

U_BOOT_CMD(checkimgrcmap, CONFIG_SYS_MAXARGS, 1, do_starfive_check_img_rec_map,
	   "Check authentication status from recovery mapping",
	   checkimgrcmap_help_text
);

U_BOOT_CMD(setimgrcmap, CONFIG_SYS_MAXARGS, 1, do_starfive_set_img_rec_map,
	   "Set authentication status to recovery mapping",
	   setimgrcmap_help_text
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

U_BOOT_CMD(setkernelimgflg, CONFIG_SYS_MAXARGS, 1, do_starfive_set_kernel_image_flag,
	   "Set AP status kernel image flag",
	   setkernelimgflg_help_text
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

U_BOOT_CMD(parsecap, CONFIG_SYS_MAXARGS, 1, do_starfive_parse_capsule,
	   "Parse Update Capsule for writting to eMMC",
	   parsecap_help_text
);

U_BOOT_CMD(checksecboot, CONFIG_SYS_MAXARGS, 1, do_starfive_check_secure_boot,
	   "Check secure boot status",
	   checksecboot_help_text
);
