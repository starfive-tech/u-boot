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

#include <ufs.h>

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

		} else if (!strcmp(argv[1], "update")) {
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

			if (ufs_update_lu(ufs_dev, lun, size, attr)) {
				printf("LUN update failure\n");
				return CMD_RET_FAILURE;
			}

			return CMD_RET_SUCCESS;

		} else if (!strcmp(argv[1], "remove")) {
			if (argc == 3) {
				if (do_ufs_get_device(&ufs_dev, 0))
					return CMD_RET_FAILURE;
				dev = dectoul(argv[2], NULL);
				return ufs_remove_lu(ufs_dev, dev);
			}
		}
	}

	return CMD_RET_USAGE;
}

U_BOOT_CMD(ufs, 6, 1, do_ufs,
	"UFS sub-system",
	"init [dev]  - init UFS subsystem\n"
	"ufs list  - list existing Logical Units\n"
	"ufs create <lun> <size> <attr>  - create a logical unit\n"
	"   Size 1 == 4MB\n"
	"   Attribute[0:1] - 0: Not bootable, 1:Boot LU A, 2: Boot LU B\n"
	"ufs update <lun> <size> <attr>  - create a logical unit\n"
	"   Size 1 == 4MB\n"
	"   Attribute[0:1] - 0: Not bootable, 1:Boot LU A, 2: Boot LU B\n"
	"ufs remove <lun>  - remove a logical unit\n"
	"ATTENTION: create, update, and remove will reset data in all LUNs\n"
);
