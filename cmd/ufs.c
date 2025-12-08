// SPDX-License-Identifier: GPL-2.0+
/**
 * ufs.c - UFS specific U-Boot commands
 *
 * Copyright (C) 2019 Texas Instruments Incorporated - https://www.ti.com
 *
 */
#include <common.h>
#include <command.h>
#include <ufs.h>
#include <dm.h>
#include <console.h>

#include <ufs.h>

static int confirm_key_prog(void)
{
	puts("Warning: Programming authentication key can be done only once !\n"
	     "         Use this command only if you are sure of what you are doing,\n"
	     "Really perform the key programming? <y/N> ");
	if (confirm_yesno())
		return 1;

	puts("Authentication key programming aborted\n");
	return 0;
}

static int do_ufs_get_device(struct udevice **dev, u8 index)
{
	int ret;

	ret = uclass_get_device(UCLASS_UFS, index, dev);
	if (ret)
		return CMD_RET_SUCCESS;

	ret = ufs_probe_dev(index);
	if (ret)
		return CMD_RET_FAILURE;

	return uclass_get_device(UCLASS_UFS, index, dev);
}

static int do_ufs(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	int dev, ret;
	struct udevice *ufs_dev;

	if (argc >= 2) {
		if (!strcmp(argv[1], "init")) {
			if (argc == 3) {
				dev = dectoul(argv[2], NULL);
				ret = ufs_probe_dev(dev);
				if (ret)
					return CMD_RET_FAILURE;
			} else {
				ufs_probe();
			}

			return CMD_RET_SUCCESS;

		} else if (!strcmp(argv[1], "list")) {
			if (do_ufs_get_device(&ufs_dev, 0))
				return CMD_RET_FAILURE;

			ufs_list_lus(ufs_dev);

			return CMD_RET_SUCCESS;

		} else if (!strcmp(argv[1], "create")) {
			if (argc < 5)
				return CMD_RET_USAGE;

			u8 lun = dectoul(argv[2], NULL);
			u32 size = dectoul(argv[3], NULL);
			u32 attr = dectoul(argv[4], NULL);

			if (!size) {
				printf("Size cannot be 0!\n");
				return CMD_RET_FAILURE;
			}

			if (do_ufs_get_device(&ufs_dev, 0))
				return CMD_RET_FAILURE;

			if (ufs_create_lu(ufs_dev, lun, size, attr)) {
				printf("LUN create failure\n");
				return CMD_RET_FAILURE;
			}

			return CMD_RET_SUCCESS;

		} else if (!strcmp(argv[1], "rpmb")) {
			if (!strcmp(argv[2], "create")) {
				if (argc != 5)
					return CMD_RET_USAGE;

				u8 region = dectoul(argv[3], NULL);
				u32 size = dectoul(argv[4], NULL);

				if (region < 1 || region > 3) {
					printf("Region should be between 1 and 3\n");
					return CMD_RET_FAILURE;
				}

				if (!size) {
					printf("Size cannot be 0!\n");
					return CMD_RET_FAILURE;
				}

				if (do_ufs_get_device(&ufs_dev, 0))
					return CMD_RET_FAILURE;

				if (ufs_create_rpmb_lu(ufs_dev, region, size)) {
					printf("RPMB LUN create failure\n");
					return CMD_RET_FAILURE;
				}

				return CMD_RET_SUCCESS;
			}  else if (!strcmp(argv[2], "remove")) {
				if (argc != 4)
					return CMD_RET_USAGE;

				u8 region = dectoul(argv[3], NULL);

				if (do_ufs_get_device(&ufs_dev, 0))
					return CMD_RET_FAILURE;

				if (ufs_remove_rpmb_lu(ufs_dev, region)) {
					printf("RPMB LUN remove failure\n");
					return CMD_RET_FAILURE;
				}

				return CMD_RET_SUCCESS;
			} else if (!strcmp(argv[2], "read")) {

				if (argc < 7)
					return CMD_RET_USAGE;

				u8 region = dectoul(argv[3], NULL);
				void* addr = (void *)dectoul(argv[4], NULL);
				u32 blk = dectoul(argv[5], NULL);
				u32 cnt = dectoul(argv[6], NULL);
				void *key_addr = (void *)dectoul(argv[7], NULL);

				if (do_ufs_get_device(&ufs_dev, 0))
					return CMD_RET_FAILURE;

				if (ufs_rpmb_read(ufs_dev, region, addr, blk, cnt, key_addr)) {
					return CMD_RET_FAILURE;
				}

				return CMD_RET_SUCCESS;
			} else if (!strcmp(argv[2], "write")) {
				if (argc != 8)
					return CMD_RET_USAGE;

				u8 region = dectoul(argv[3], NULL);
				void* addr = (void *)dectoul(argv[4], NULL);
				u32 blk = dectoul(argv[5], NULL);
				u32 cnt = dectoul(argv[6], NULL);
				void *key_addr = (void *)dectoul(argv[7], NULL);

				if (do_ufs_get_device(&ufs_dev, 0))
					return CMD_RET_FAILURE;

				if (ufs_rpmb_write(ufs_dev, region, addr, blk, cnt, key_addr)) {
				return CMD_RET_FAILURE;
			}

			return CMD_RET_SUCCESS;
			} else if (!strcmp(argv[2], "key")) {
				if (argc != 5)
					return CMD_RET_USAGE;

				u8 region = dectoul(argv[3], NULL);
				void *key_addr = (void *)hextoul(argv[4], NULL);

				if (do_ufs_get_device(&ufs_dev, 0))
					return CMD_RET_FAILURE;

				if (!confirm_key_prog())
					return CMD_RET_FAILURE;
				if (ufs_write_rpmb_key(ufs_dev, region, key_addr)) {
					printf("ERROR - Key already programmed ?\n");
					return CMD_RET_FAILURE;
				}

				printf("RPMB Region %d key programmed successfully!\n", region);
				return CMD_RET_SUCCESS;
			}
		}
	}

	return CMD_RET_USAGE;
}

U_BOOT_CMD(ufs, 8, 1, do_ufs,
	"UFS sub-system",
	"init [dev]  - init UFS subsystem\n"
	"ufs list  - list existing Logical Units\n"
	"ufs create <lun> <blksize> <attr>  - create a logical unit\n"
	"   1 blksize equal 4MB\n"
	"   Attribute[0:1] - 0: Not bootable, 1:Boot LU A, 2: Boot LU B\n\n"

	"ufs rpmb key <region> <address of auth-key> - program the RPMB authentication key "
	"ufs rpmb create <region> <blksize>  - create a RPMB region [1-3]\n"
	"   1 blksize equal 128KB\n"
	"ufs rpmb remove <region>  - remove a RPMB region [1-3]\n"
	"ufs rpmb read <region> <addr> <blk#> <cnt> [address of auth-key] - read from UFS RPMB to memory\n"
	"ufs rpmb write <region> <addr> <blk#> <cnt> <address of auth-key>  - read from UFS RPMB to memory\n\n"

	"ATTENTION: create, update, and remove will reset data in all LUNs\n"
);
