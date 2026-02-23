/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * StarFive JHB100 Display and Video Driver Cmd Header
 *
 * Copyright (c) 2026 StarFive Technology Co., Ltd.
 */

#ifndef __VIDEO_STARFIVE_H__
#define __VIDEO_STARFIVE_H__

enum force_timing {
	FORCE_640_480_60HZ = 1,
	FORCE_720_400_85HZ,
	FORCE_800_600_60HZ,
	FORCE_1024_768_60HZ,
	FORCE_1152_864_75HZ,
	FORCE_1280_720_60HZ,
	FORCE_1280_768_60HZ,
	FORCE_1280_960_60HZ,
	FORCE_1280_1024_60HZ,
	FORCE_1440_900_60HZ,
	FORCE_1600_900_60HZ,
	FORCE_1600_1200_60HZ,
	FORCE_1920_1080_60HZ,
	FORCE_1920_1200_60HZ,
	FORCE_2048_1080_60HZ,
	FORCE_TIMING_NONE,
};

enum force_timing video_jhb100_get_timing(void);
u8 video_jhb100_get_dc_dev_id(void);

#endif /* __VIDEO_STARFIVE_H__ */
