// SPDX-License-Identifier: GPL-2.0+
/*
 * JHB100 Video Display Test Command
 *
 * Copyright (c) 2026 StarFive Technology Co., Ltd.
 */

#include <command.h>
#include <display.h>
#include <dm.h>
#include <dm/device-internal.h>
#include <dm/uclass-internal.h>
#include <edid.h>
#include <linux/errno.h>
#include <video.h>
#include <video_starfive.h>

static enum force_timing req_timing = FORCE_TIMING_NONE;
static enum force_timing req_timing_prev = FORCE_TIMING_NONE;
static u8 dc_dev_id;
static u8 dc_dev_id_prev;
struct mode_info {
	const char *name;
	u32 hactive;
	u32 vactive;
	u32 refresh;
};

static const struct mode_info mode_table[] = {
	{ "640x480@60",   640,  480,  60 },
	{ "720x400@85",   720,  400,  85 },
	{ "800x600@60",   800,  600,  60 },
	{ "1024x768@60",  1024,  768,  60 },
	{ "1152x864@75",  1152,  864,  75 },
	{ "1280x720@60",  1280,  720,  60 },
	{ "1280x768@60",  1280,  768,  60 },
	{ "1280x960@60",  1280,  960,  60 },
	{ "1280x1024@60", 1280, 1024,  60 },
	{ "1440x900@60",  1440,  900,  60 },
	{ "1600x900@60",  1600,  900,  60 },
	{ "1600x1200@60", 1600, 1200,  60 },
	{ "1920x1080@60", 1920, 1080,  60 },
	{ "1920x1200@60", 1920, 1200,  60 },
	{ "2048x1080@60", 2048, 1080,  60 },
};

enum force_timing video_jhb100_get_timing(void)
{
	return req_timing;
}

u8 video_jhb100_get_dc_dev_id(void)
{
	return dc_dev_id;
}

static int dp_read_and_print_edid(struct udevice *disp_dev)
{
	struct dm_display_ops *ops = display_get_ops(disp_dev);
	u8 buf[EDID_SIZE];

	if (!ops || !ops->read_edid) {
		printf("EDID read not supported by display device\n");
		return -ENOTSUPP;
	}

	ops->read_edid(disp_dev, buf, sizeof(buf));
	edid_print_info((struct edid1_info *)buf);

	return 0;
}

static int do_jhb100_dp(struct cmd_tbl *cmdtp, int flag, int argc,
			char *const argv[])
{
	struct udevice *video_dev = NULL;
	struct udevice *disp_dev = NULL;
	const char *cmd;
	ulong ctrl = 0;
	ulong mode_id;
	char *endp;
	int ret;

	if (argc < 2)
		return CMD_RET_USAGE;

	/*
	 * Supported forms:
	 *   dp <ctrl> mode <1-15>
	 *   dp <ctrl> edid
	 */
	if (argc < 3)
		return CMD_RET_USAGE;

	ctrl = simple_strtoul(argv[1], &endp, 10);
	if (*argv[1] == '\0' || (endp && *endp != '\0'))
		return CMD_RET_USAGE;
	cmd = argv[2];

	if (ctrl > 1)
		return CMD_RET_USAGE;

	if (!strcmp(cmd, "edid") || !strcmp(cmd, "EDID")) {
		ret = uclass_get_device(UCLASS_DISPLAY, 0, &disp_dev);
		if (ret) {
			printf("Failed to get display controller %d (%d)\n",
			       0, ret);
			return CMD_RET_FAILURE;
		}
		ret = dp_read_and_print_edid(disp_dev);
		if (ret) {
			printf("EDID read failed (%d)\n", ret);
			return CMD_RET_FAILURE;
		}
		return CMD_RET_SUCCESS;
	}

	if (!strcmp(cmd, "mode")) {
		if (argc != 4)
			return CMD_RET_USAGE;

		mode_id = simple_strtoul(argv[3], &endp, 10);
		if (!mode_id || (endp && *endp != '\0'))
			return CMD_RET_USAGE;
	} else {
		return CMD_RET_USAGE;
	}

	if (mode_id < 1 || mode_id > ARRAY_SIZE(mode_table))
		return CMD_RET_USAGE;

	req_timing = mode_id - 1;
	dc_dev_id = ctrl;

	/* Re-probe display/video if timing changed */
	if (req_timing_prev != req_timing) {
		if (!uclass_find_device_by_seq(UCLASS_DISPLAY, 0, &disp_dev) && disp_dev) {
			if (device_active(disp_dev))
				device_remove(disp_dev, DM_REMOVE_NORMAL);
		}

		if (!uclass_find_device_by_seq(UCLASS_VIDEO, dc_dev_id, &video_dev) && video_dev) {
			if (device_active(video_dev))
				device_remove(video_dev, DM_REMOVE_NORMAL);
		}
	}

	/* Re-probe display/video if device controller changed */
	if (dc_dev_id_prev != dc_dev_id) {
		if (!uclass_find_device_by_seq(UCLASS_DISPLAY, 0, &disp_dev) && disp_dev) {
			if (device_active(disp_dev))
				device_remove(disp_dev, DM_REMOVE_NORMAL);
		}

		if (!uclass_find_device_by_seq(UCLASS_VIDEO,
					       dc_dev_id_prev, &video_dev) && video_dev) {
			if (device_active(video_dev))
				device_remove(video_dev, DM_REMOVE_NORMAL);
		}
	}

	req_timing_prev = req_timing;
	dc_dev_id_prev = dc_dev_id;

	if (mode_id <= ARRAY_SIZE(mode_table)) {
		const struct mode_info *m = &mode_table[mode_id - 1];

		printf("Using fixed mode %lu: %s (%ux%u @ %uHz)\n",
		       mode_id, m->name, m->hactive, m->vactive, m->refresh);
	}

	ret = uclass_get_device(UCLASS_VIDEO, dc_dev_id, &video_dev);
	if (ret) {
		printf("Failed to get video controller %u (%d)\n",
		       dc_dev_id, ret);
		return CMD_RET_FAILURE;
	}

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(dp, 4, 0, do_jhb100_dp,
	   "JHB100 DP test command",
	   "<dev> mode <1-15>\n"
	   "dp <dev> edid\n"
	   "  <dev>: 0 or 1\n"
	   "    1: 640x480@60    2: 720x400@85    3: 800x600@60\n"
	   "    4: 1024x768@60   5: 1152x864@75   6: 1280x720@60\n"
	   "    7: 1280x768@60   8: 1280x960@60   9: 1280x1024@60\n"
	   "   10: 1440x900@60  11: 1600x900@60  12: 1600x1200@60\n"
	   "   13: 1920x1080@60 14: 1920x1200@60 15: 2048x1080@60"
);
