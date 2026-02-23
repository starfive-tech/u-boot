/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * StarFive JHB100 DC8000 Minimal Display and Framebuffer Driver Header
 *
 * Copyright (c) 2026 StarFive Technology Co., Ltd.
 */

#ifndef __JHB100_DC8000_H__
#define __JHB100_DC8000_H__

#include <fdtdec.h>
#include <linux/types.h>
#include <linux/bitops.h>
#include <linux/media-bus-format.h>

/* ------------------------------------------------------------------------- */
/* DC Identification                                                         */
/* ------------------------------------------------------------------------- */
#define DC_HW_REVISION_REG	0x0024
#define DC_HW_CHIP_CID_REG	0x0030

/* ------------------------------------------------------------------------- */
/* Framebuffer (Primary)                                                     */
/* ------------------------------------------------------------------------- */
#define DC_FRAMEBUFFER_ADDRESS			0x1400
#define DC_FRAMEBUFFER_STRIDE			0x1408
#define DC_FRAMEBUFFER_CONFIG			0x1518
#define DC_FRAMEBUFFER_SCALE_CONFIG		0x1520
#define DC_FRAMEBUFFER_BG_COLOR			0x1528
#define DC_FRAMEBUFFER_U_ADDRESS		0x1530
#define DC_FRAMEBUFFER_V_ADDRESS		0x1538
#define DC_FRAMEBUFFER_COLOR_KEY		0x1508
#define DC_FRAMEBUFFER_COLOR_KEY_HIGH		0x1510

#define DC_FRAMEBUFFER_U_STRIDE			0x1800
#define DC_FRAMEBUFFER_V_STRIDE			0x1808
#define DC_FRAMEBUFFER_SIZE			0x1810
#define DC_FRAMEBUFFER_COLOR_TABLE_INDEX	0x1818
#define DC_FRAMEBUFFER_COLOR_TABLE_DATA		0x1820
#define DC_FRAMEBUFFER_SCALE_FACTOR_X		0x1828
#define DC_FRAMEBUFFER_SCALE_FACTOR_Y		0x1830

#define DC_FRAMEBUFFER_H_FILTER_COEF_INDEX	0x1838
#define DC_FRAMEBUFFER_H_FILTER_COEF_DATA	0x1A00
#define DC_FRAMEBUFFER_V_FILTER_COEF_INDEX	0x1A08
#define DC_FRAMEBUFFER_V_FILTER_COEF_DATA	0x1A10
#define DC_FRAMEBUFFER_CLEAR_VALUE		0x1A18
#define DC_FRAMEBUFFER_INIT_OFFSET		0x1A20

#define DC_FRAMEBUFFER_DEGAMMA_INDEX		0x1D88
#define DC_FRAMEBUFFER_DEGAMMA_DATA		0x1D90
#define DC_FRAMEBUFFER_DEGAMMA_EX_DATA		0x1D98

#define DC_FRAMEBUFFER_YUVTORGB_COEF0		0x1DA0
#define DC_FRAMEBUFFER_YUVTORGB_COEF1		0x1DA8
#define DC_FRAMEBUFFER_YUVTORGB_COEF2		0x1DB0
#define DC_FRAMEBUFFER_YUVTORGB_COEF3		0x1DB8
#define DC_FRAMEBUFFER_YUVTORGB_COEF4		0x1E00
#define DC_FRAMEBUFFER_YUVTORGB_COEFD0		0x1E08
#define DC_FRAMEBUFFER_YUVTORGB_COEFD1		0x1E10
#define DC_FRAMEBUFFER_YUVTORGB_COEFD2		0x1E18

#define DC_FRAMEBUFFER_RGBTORGB_COEF0		0x1E20
#define DC_FRAMEBUFFER_RGBTORGB_COEF1		0x1E28
#define DC_FRAMEBUFFER_RGBTORGB_COEF2		0x1E30
#define DC_FRAMEBUFFER_RGBTORGB_COEF3		0x1E38
#define DC_FRAMEBUFFER_RGBTORGB_COEF4		0x1E40

#define DC_FRAMEBUFFER_Y_CLAMP_BOUND		0x1E88
#define DC_FRAMEBUFFER_UV_CLAMP_BOUND		0x1E90

#define DC_FRAMEBUFFER_CONFIG_EX		0x1CC0
#define DC_FRAMEBUFFER_WATERMARK0		0x1CE8

/* ------------------------------------------------------------------------- */
/* Overlay                                                                   */
/* ------------------------------------------------------------------------- */
#define DC_OVERLAY_CONFIG		0x1540
#define DC_OVERLAY_BLEND_CONFIG		0x1580
#define DC_OVERLAY_ADDRESS		0x15C0
#define DC_OVERLAY_STRIDE		0x1600
#define DC_OVERLAY_TOP_LEFT		0x1640
#define DC_OVERLAY_BOTTOM_RIGHT		0x1680
#define DC_OVERLAY_SRC_GLOBAL_COLOR	0x16C0
#define DC_OVERLAY_DST_GLOBAL_COLOR	0x1700
#define DC_OVERLAY_COLOR_KEY		0x1740
#define DC_OVERLAY_COLOR_KEY_HIGH	0x1780

#define DC_OVERLAY_SIZE			0x17C0
#define DC_OVERLAY_U_ADDRESS		0x1840
#define DC_OVERLAY_V_ADDRESS		0x1880
#define DC_OVERLAY_U_STRIDE		0x18C0
#define DC_OVERLAY_V_STRIDE		0x1900
#define DC_OVERLAY_CLEAR_VALUE		0x1940
#define DC_OVERLAY_COLOR_TABLE_INDEX	0x1980
#define DC_OVERLAY_COLOR_TABLE_DATA	0x19C0

#define DC_OVERLAY_INIT_OFFSET		0x1BC0
#define DC_OVERLAY_SCALE_CONFIG		0x1C00
#define DC_OVERLAY_SCALE_FACTOR_X	0x1A40
#define DC_OVERLAY_SCALE_FACTOR_Y	0x1A80

#define DC_OVERLAY_H_FILTER_COEF_INDEX	0x1AC0
#define DC_OVERLAY_H_FILTER_COEF_DATA	0x1B00
#define DC_OVERLAY_V_FILTER_COEF_INDEX	0x1B40
#define DC_OVERLAY_V_FILTER_COEF_DATA	0x1B80

#define DC_OVERLAY_YUVTORGB_COEF0	0x1EC0
#define DC_OVERLAY_YUVTORGB_COEF1	0x1F00
#define DC_OVERLAY_YUVTORGB_COEF2	0x1F40
#define DC_OVERLAY_YUVTORGB_COEF3	0x1F80
#define DC_OVERLAY_YUVTORGB_COEF4	0x1FC0
#define DC_OVERLAY_YUVTORGB_COEFD0	0x2000
#define DC_OVERLAY_YUVTORGB_COEFD1	0x2040
#define DC_OVERLAY_YUVTORGB_COEFD2	0x2080

#define DC_OVERLAY_RGBTORGB_COEF0	0x20C0
#define DC_OVERLAY_RGBTORGB_COEF1	0x2100
#define DC_OVERLAY_RGBTORGB_COEF2	0x2140
#define DC_OVERLAY_RGBTORGB_COEF3	0x2180
#define DC_OVERLAY_RGBTORGB_COEF4	0x21C0

#define DC_OVERLAY_DEGAMMA_INDEX	0x2200
#define DC_OVERLAY_DEGAMMA_DATA		0x2240
#define DC_OVERLAY_DEGAMMA_EX_DATA	0x2280
#define DC_OVERLAY_Y_CLAMP_BOUND	0x22C0
#define DC_OVERLAY_UV_CLAMP_BOUND	0x2300

/* ------------------------------------------------------------------------- */
/* Cursor                                                                    */
/* ------------------------------------------------------------------------- */
#define DC_CURSOR_CONFIG	0x1468
#define DC_CURSOR_ADDRESS	0x146C
#define DC_CURSOR_LOCATION	0x1470
#define DC_CURSOR_BACKGROUND	0x1474
#define DC_CURSOR_FOREGROUND	0x1478
#define DC_CURSOR_CLK_GATING	0x1484

/* ------------------------------------------------------------------------- */
/* Display timing / general                                                  */
/* ------------------------------------------------------------------------- */
#define DC_DISPLAY_DITHER_CONFIG	0x1410
#define DC_DISPLAY_PANEL_CONFIG		0x1418
#define DC_DISPLAY_DITHER_TABLE_LOW	0x1420
#define DC_DISPLAY_DITHER_TABLE_HIGH	0x1428
#define DC_DISPLAY_H			0x1430
#define DC_DISPLAY_H_SYNC		0x1438
#define DC_DISPLAY_V			0x1440
#define DC_DISPLAY_V_SYNC		0x1448
#define DC_DISPLAY_CURRENT_LOCATION	0x1450
#define DC_DISPLAY_GAMMA_INDEX		0x1458
#define DC_DISPLAY_GAMMA_DATA		0x1460
#define DC_DISPLAY_INT			0x147C
#define DC_DISPLAY_INT_ENABLE		0x1480
#define DC_DISPLAY_DBI_CONFIG		0x1488
#define DC_DISPLAY_GENERAL_CONFIG	0x14B0
#define DC_DISPLAY_DPI_CONFIG		0x14B8
#define DC_DISPLAY_DEBUG_COUNTER_SELECT	0x14D0
#define DC_DISPLAY_DEBUG_COUNTER_VALUE	0x14D8
#define DC_DISPLAY_DP_CONFIG		0x1CD0
#define DC_DISPLAY_GAMMA_EX_INDEX	0x1CF0
#define DC_DISPLAY_GAMMA_EX_DATA	0x1CF8
#define DC_DISPLAY_GAMMA_EX_ONE_DATA	0x1D80

#define DC_DISPLAY_RGBTOYUV_COEF0	0x1E48
#define DC_DISPLAY_RGBTOYUV_COEF1	0x1E50
#define DC_DISPLAY_RGBTOYUV_COEF2	0x1E58
#define DC_DISPLAY_RGBTOYUV_COEF3	0x1E60
#define DC_DISPLAY_RGBTOYUV_COEF4	0x1E68
#define DC_DISPLAY_RGBTOYUV_COEFD0	0x1E70
#define DC_DISPLAY_RGBTOYUV_COEFD1	0x1E78
#define DC_DISPLAY_RGBTOYUV_COEFD2	0x1E80

#define DC_DISPLAY_DITHERTABLE_LOW	0x7B48F3C0
#define DC_DISPLAY_DITHERTABLE_HIGH	0x596AD1E2

/* ------------------------------------------------------------------------- */
/* HW constants / tables                                                     */
/* ------------------------------------------------------------------------- */
#define GAMMA_SIZE	256
#define GAMMA_EX_SIZE	300
#define DEGAMMA_SIZE	260

#define RGB_TO_RGB_TABLE_SIZE	9
#define YUV_TO_RGB_TABLE_SIZE	16
#define RGB_TO_YUV_TABLE_SIZE	12

#define MAIN_ICG_EN_U0_DC8000		0xF4
#define MAIN_ICG_EN_U0_DC8000_SENSOR	0xF8

#define HORIZONTAL_COEF	0
#define VERTICAL_COEF	1

enum dc_hw_chip_rev {
	DC_REV_5551,
	DC_REV_5551_306,
	DC_REV_5701_303,
	DC_REV_5701_309,
};

enum dc_hw_plane_id {
	PRIMARY_PLANE,
	CURSOR_PLANE,
	OVERLAY_PLANE,
	PLANE_NUM
};

enum dc_hw_color_format {
	FORMAT_X4R4G4B4,
	FORMAT_A4R4G4B4,
	FORMAT_X1R5G5B5,
	FORMAT_A1R5G5B5,
	FORMAT_R5G6B5,
	FORMAT_X8R8G8B8,
	FORMAT_A8R8G8B8,
	FORMAT_YUY2,
	FORMAT_UYVY,
	FORMAT_INDEX8,
	FORMAT_MONOCHROME,
	FORMAT_YV12 = 0xf,
	FORMAT_A8,
	FORMAT_NV12,
	FORMAT_NV16,
	FORMAT_RG16,
	FORMAT_R8,
	FORMAT_NV12_10BIT,
	FORMAT_A2R10G10B10,
	FORMAT_NV16_10BIT,
	FORMAT_INDEX1,
	FORMAT_INDEX2,
	FORMAT_INDEX4,
	FORMAT_P010,
	FORMAT_YUV444,
};

enum dc_hw_yuv_color_space {
	COLOR_SPACE_601 = 0,
	COLOR_SPACE_709 = 1,
	COLOR_SPACE_2020 = 3,
};

enum dc_hw_blend_mode {
	BLEND_PREMULTI,
	BLEND_COVERAGE,
	BLEND_PIXEL_NONE,
};

struct dc_hw_plane_reg {
	u32 y_address;
	u32 u_address;
	u32 v_address;
	u32 y_stride;
	u32 u_stride;
	u32 v_stride;
	u32 size;
	u32 scale_factor_x;
	u32 scale_factor_y;
	u32 h_filter_coef_index;
	u32 h_filter_coef_data;
	u32 v_filter_coef_index;
	u32 v_filter_coef_data;
	u32 init_offset;
	u32 color_key;
	u32 color_key_high;
	u32 clear_value;
	u32 color_table_index;
	u32 color_table_data;
	u32 scale_config;
	u32 degamma_index;
	u32 degamma_data;
	u32 degamma_ex_data;
	u32 yuv_to_rgb_coef0;
	u32 yuv_to_rgb_coef1;
	u32 yuv_to_rgb_coef2;
	u32 yuv_to_rgb_coef3;
	u32 yuv_to_rgb_coef4;
	u32 yuv_to_rgb_coef_d0;
	u32 yuv_to_rgb_coef_d1;
	u32 yuv_to_rgb_coef_d2;
	u32 y_clamp_bound;
	u32 uv_clamp_bound;
	u32 rgb_to_rgb_coef0;
	u32 rgb_to_rgb_coef1;
	u32 rgb_to_rgb_coef2;
	u32 rgb_to_rgb_coef3;
	u32 rgb_to_rgb_coef5;
};

struct dc_hw_fb {
	u32 y_address;
	u32 u_address;
	u32 v_address;
	u16 y_stride;
	u16 u_stride;
	u16 v_stride;
	u16 width;
	u16 height;
	u8 format;
	u8 tile_mode;
	u8 rotation;
	u8 yuv_color_space;
	u8 swizzle;
	u8 uv_swizzle;
	bool enable;
	bool dirty;
};

struct dc_hw_scale {
	u32 scale_factor_x;
	u32 scale_factor_y;
	bool enable;
	bool dirty;
};

struct dc_hw_position {
	u16 start_x;
	u16 start_y;
	u16 end_x;
	u16 end_y;
	bool dirty;
};

struct dc_hw_blend {
	u8 alpha;
	u8 blend_mode;
	bool dirty;
};

enum drm_vs_sync_dc_mode {
	VS_SINGLE_DC = 0,
	VS_MULTI_DC_PRIMARY = 1,
	VS_MULTI_DC_SECONDARY = 2,
};

struct dc_hw_display {
	u32 bus_format;
	u16 h_active;
	u16 h_total;
	u16 h_sync_start;
	u16 h_sync_end;
	u16 v_active;
	u16 v_total;
	u16 v_sync_start;
	u16 v_sync_end;
	enum drm_vs_sync_dc_mode sync_mode;
	bool h_sync_polarity;
	bool v_sync_polarity;
	u32 frame_rate;
};

struct dc_hw_gamma {
	u16 gamma[GAMMA_EX_SIZE][3];
	bool enable;
	bool dirty;
};

struct dc_hw_degamma {
	u16 degamma[DEGAMMA_SIZE][3];
	u32 mode;
	bool dirty;
};

struct dc_hw_plane {
	struct dc_hw_fb fb;
	struct dc_hw_scale scale;
	struct dc_hw_degamma degamma;
};

struct dc_hw_overlay {
	struct dc_hw_plane plane;
	struct dc_hw_position pos;
	struct dc_hw_blend blend;
};

struct dc_hw_read {
	u32 reg;
	u32 value;
};

struct dc_hw {
	enum dc_hw_chip_rev rev;
	void *dc_base;
	struct dc_hw_read *read_block;
	struct dc_hw_display display;
	struct dc_hw_gamma gamma;
	struct dc_hw_plane primary;
	struct dc_hw_overlay overlay;
	struct dc_hw_funcs *func;
};

enum drm_vs_degamma_mode {
	VS_DEGAMMA_DISABLE = 0,
	VS_DEGAMMA_BT709 = 1,
	VS_DEGAMMA_BT2020 = 2,
};

static const u32 dc_read_reg_list[] = {
	DC_FRAMEBUFFER_CONFIG,
	DC_OVERLAY_CONFIG,
	DC_OVERLAY_SCALE_CONFIG,
};

#define READ_REG_COUNT ARRAY_SIZE(dc_read_reg_list)

struct coef_table {
	const u32 *data;
	size_t size;
};

struct reg_table {
	const struct dc_hw_plane_reg *data;
	size_t size;
};

extern const u32 hor_kernel[];
extern const u32 ver_kernel[];

extern const u16 RGB2RGB[RGB_TO_RGB_TABLE_SIZE];

extern const s32 YUV601_2RGB[YUV_TO_RGB_TABLE_SIZE];
extern const s32 YUV709_2RGB[YUV_TO_RGB_TABLE_SIZE];
extern const s32 YUV2020_2RGB[YUV_TO_RGB_TABLE_SIZE];

extern const s16 RGB2YUV[RGB_TO_YUV_TABLE_SIZE];

extern const u16 DEGAMMA_709[DEGAMMA_SIZE];
extern const u16 DEGAMMA_2020[DEGAMMA_SIZE];

extern const struct dc_hw_plane_reg dc_plane_reg[];
extern const struct display_timing timing_default[];
extern const struct coef_table coef_table[];
extern const struct reg_table plane_reg_table;

#endif /* __JHB100_DC8000_H__ */
