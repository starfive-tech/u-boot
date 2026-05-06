// SPDX-License-Identifier: GPL-2.0+
/*
 * StarFive JHB100 DC8000 Minimal Display and Framebuffer Driver
 *
 * Copyright (c) 2026 StarFive Technology Co., Ltd.
 */

#include <asm/cache.h>
#include <asm/global_data.h>
#include <asm/io.h>
#include <clk.h>
#include <cpu_func.h>
#include <display.h>
#include <dm.h>
#include <dm/ofnode.h>
#include <div64.h>
#include <fdtdec.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/ioport.h>
#include <mapmem.h>
#include <regmap.h>
#include <reset.h>
#include <syscon.h>
#include <video.h>
#include <video_starfive.h>

#include "jhb100_dc8000.h"

DECLARE_GLOBAL_DATA_PTR;

#define JHB100_MAX_XRES		2048
#define JHB100_MAX_YRES		1080
#define JHB100_BPP_BYTES	4
#define JHB100_FB_ALIGN		0x100000

struct jhb100_dc8000_priv {
	struct clk_bulk clks;
	struct reset_ctl reset;
	struct dc_hw hw;
	bool first_frame;
	bool force_output;
	bool pipe_sync;
	struct display_timing *forced_timing;
	struct dc_hw_display  *dc;
	struct dc_hw_fb       *fb;
};

struct dc_hw_funcs {
	void (*gamma)(struct jhb100_dc8000_priv *priv);
	void (*plane)(struct jhb100_dc8000_priv *priv);
	void (*display)(struct jhb100_dc8000_priv *priv, struct dc_hw_display *display);
};

static inline int dc_get_read_index(struct dc_hw *hw, u32 reg)
{
	int i;

	for (i = 0; i < READ_REG_COUNT; i++) {
		if (hw->read_block[i].reg == reg)
			return i;
	}
	return i;
}

static inline u32 dc_read(struct dc_hw *hw, u32 reg)
{
	u32 value = readl(hw->dc_base + reg);

	if (hw->read_block) {
		int i = dc_get_read_index(hw, reg);

		if (i < READ_REG_COUNT) {
			value &= ~BIT(0);
			value |= hw->read_block[i].value & BIT(0);
		}
	}

	return value;
}

static inline void dc_write(struct dc_hw *hw, u32 reg, u32 value)
{
	writel(value, hw->dc_base + reg);

	if (hw->read_block) {
		int i = dc_get_read_index(hw, reg);

		if (i < READ_REG_COUNT)
			hw->read_block[i].value = value;
	}
}

static void dc_set_clear(struct jhb100_dc8000_priv *priv, u32 reg,
			 u32 set, u32 clear)
{
	u32 val = dc_read(&priv->hw, reg);

	val &= ~clear;
	val |= set;
	dc_write(&priv->hw, reg, val);
}

static void gamma_commit(struct jhb100_dc8000_priv *priv)
{
	u16 i;
	u32 value;

	if (priv->hw.gamma.dirty) {
		if (priv->hw.gamma.enable) {
			dc_write(&priv->hw, DC_DISPLAY_GAMMA_INDEX, 0x00);
			for (i = 0; i < GAMMA_SIZE; i++) {
				value = priv->hw.gamma.gamma[i][2] |
					(priv->hw.gamma.gamma[i][1] << 10) |
					(priv->hw.gamma.gamma[i][0] << 20);
				dc_write(&priv->hw, DC_DISPLAY_GAMMA_DATA, value);
			}

			dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, BIT(2), 0);
		} else {
			dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, 0, BIT(2));
		}
		priv->hw.gamma.dirty = false;
	}
}

static void gamma_ex_commit(struct jhb100_dc8000_priv *priv)
{
	u16 i;
	u32 value;

	if (priv->hw.gamma.dirty) {
		if (priv->hw.gamma.enable) {
			dc_write(&priv->hw, DC_DISPLAY_GAMMA_EX_INDEX, 0x00);
			for (i = 0; i < GAMMA_EX_SIZE; i++) {
				value = priv->hw.gamma.gamma[i][2] |
					(priv->hw.gamma.gamma[i][1] << 12);
				dc_write(&priv->hw, DC_DISPLAY_GAMMA_EX_DATA, value);
				dc_write(&priv->hw, DC_DISPLAY_GAMMA_EX_ONE_DATA,
					 priv->hw.gamma.gamma[i][0]);
			}
			dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, BIT(2), 0);
		} else {
			dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, 0, BIT(2));
		}
		priv->hw.gamma.dirty = false;
	}
}

static void plane_commit(struct jhb100_dc8000_priv *priv)
{
	struct dc_hw_plane *plane;
	const struct dc_hw_plane_reg *reg;
	u16 i;

	for (i = 0; i < PLANE_NUM; i++) {
		if (i == PRIMARY_PLANE) {
			plane = &priv->hw.primary;
			reg = &dc_plane_reg[0];
		} else if (i == OVERLAY_PLANE) {
			plane = &priv->hw.overlay.plane;
			reg = &dc_plane_reg[1];
		} else {
			continue;
		}

		if (plane->fb.dirty) {
			if (plane->fb.enable) {
				dc_write(&priv->hw, DC_FRAMEBUFFER_WATERMARK0, 0x2);
				dc_write(&priv->hw, reg->y_address,
					 plane->fb.y_address);
				dc_write(&priv->hw, reg->u_address,
					 plane->fb.u_address);
				dc_write(&priv->hw, reg->v_address,
					 plane->fb.v_address);
				dc_write(&priv->hw, reg->y_stride,
					 plane->fb.y_stride);
				dc_write(&priv->hw, reg->u_stride,
					 plane->fb.u_stride);
				dc_write(&priv->hw, reg->v_stride,
					 plane->fb.v_stride);
				dc_write(&priv->hw, reg->size,
					 plane->fb.width |
					     (plane->fb.height << 15));
			}
			if (i == PRIMARY_PLANE)
				dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG,
					     (plane->fb.format << 26) |
						 (plane->fb.uv_swizzle << 25) |
						 (plane->fb.swizzle << 23) |
						 (plane->fb.tile_mode << 17) |
						 (plane->fb.yuv_color_space << 14) |
						 (plane->fb.rotation << 11) |
						 plane->fb.enable,
					     (0x1F << 26) |
						 BIT(25) |
						 (0x03 << 23) |
						 (0x1F << 17) |
						 (0x07 << 14) |
						 (0x07 << 11) |
						 BIT(0));
			else
				dc_set_clear(priv, DC_OVERLAY_CONFIG,
					     (plane->fb.format << 16) |
						 (plane->fb.uv_swizzle << 15) |
						 (plane->fb.swizzle << 13) |
						 (plane->fb.tile_mode << 8) |
						 (plane->fb.yuv_color_space << 5) |
						 (plane->fb.rotation << 2) |
						 (plane->fb.enable << 24),
					     (0x1F << 16) |
						 BIT(15) |
						 (0x03 << 13) |
						 (0x1F << 8) |
						 (0x07 << 5) |
						 (0x07 << 2) |
						 BIT(24));
			plane->fb.dirty = false;
		}

		if (plane->scale.dirty) {
			if (plane->scale.enable) {
				dc_write(&priv->hw, reg->scale_factor_x,
					 plane->scale.scale_factor_x);
				dc_write(&priv->hw, reg->scale_factor_y,
					 plane->scale.scale_factor_y);
				if (i == PRIMARY_PLANE)
					dc_set_clear(priv,
						     DC_FRAMEBUFFER_CONFIG,
						     BIT(22), 0);
				else
					dc_set_clear(priv,
						     DC_OVERLAY_SCALE_CONFIG,
						     BIT(8), 0);
			} else {
				if (i == PRIMARY_PLANE)
					dc_set_clear(priv,
						     DC_FRAMEBUFFER_CONFIG,
						     0, BIT(22));
				else
					dc_set_clear(priv,
						     DC_OVERLAY_SCALE_CONFIG,
						     0, BIT(8));
			}
			plane->scale.dirty = false;
		}
	}
}

static bool is_rgb(enum dc_hw_color_format format)
{
	switch (format) {
	case FORMAT_X4R4G4B4:
	case FORMAT_A4R4G4B4:
	case FORMAT_X1R5G5B5:
	case FORMAT_A1R5G5B5:
	case FORMAT_R5G6B5:
	case FORMAT_X8R8G8B8:
	case FORMAT_A8R8G8B8:
	case FORMAT_A2R10G10B10:
		return true;
	default:
		return false;
	}
}

static void load_yuv_to_rgb(struct dc_hw *hw, const struct dc_hw_plane_reg *reg,
			    const s32 *table)
{
	dc_write(hw, reg->yuv_to_rgb_coef0, (0xFFFF & table[0]) | (table[1] << 16));
	dc_write(hw, reg->yuv_to_rgb_coef1, (0xFFFF & table[2]) | (table[3] << 16));
	dc_write(hw, reg->yuv_to_rgb_coef2, (0xFFFF & table[4]) | (table[5] << 16));
	dc_write(hw, reg->yuv_to_rgb_coef3, (0xFFFF & table[6]) | (table[7] << 16));
	dc_write(hw, reg->yuv_to_rgb_coef4, table[8]);
	dc_write(hw, reg->yuv_to_rgb_coef_d0, table[9]);
	dc_write(hw, reg->yuv_to_rgb_coef_d1, table[10]);
	dc_write(hw, reg->yuv_to_rgb_coef_d2, table[11]);
	dc_write(hw, reg->y_clamp_bound, table[12] | (table[13] << 16));
	dc_write(hw, reg->uv_clamp_bound, table[14] | (table[15] << 16));
}

static void load_degamma_table(struct dc_hw *hw,
			       const struct dc_hw_plane_reg *reg,
			       const u16 *table)
{
	u16 i;
	u32 value;

	for (i = 0; i < DEGAMMA_SIZE; i++) {
		dc_write(hw, reg->degamma_index, i);
		value = table[i] | (table[i] << 16);
		dc_write(hw, reg->degamma_data, value);
		dc_write(hw, reg->degamma_ex_data, table[i]);
	}
}

static void plane_ex_commit(struct jhb100_dc8000_priv *priv)
{
	struct dc_hw_plane *plane;
	const struct dc_hw_plane_reg *reg;
	u16 i;

	for (i = 0; i < PLANE_NUM; i++) {
		if (i == PRIMARY_PLANE) {
			plane = &priv->hw.primary;
			reg = &dc_plane_reg[0];
		} else if (i == OVERLAY_PLANE) {
			plane = &priv->hw.overlay.plane;
			reg = &dc_plane_reg[1];
		} else {
			continue;
		}

		if (plane->fb.dirty) {
			if (is_rgb(plane->fb.format)) {
				if (i == PRIMARY_PLANE)
					dc_set_clear(priv,
						     DC_FRAMEBUFFER_CONFIG_EX,
						     BIT(6), BIT(8));
				else
					dc_set_clear(priv,
						     DC_OVERLAY_CONFIG,
						     BIT(29), BIT(30));
			} else {
				if (i == PRIMARY_PLANE)
					dc_set_clear(priv,
						     DC_FRAMEBUFFER_CONFIG_EX,
						     BIT(8), BIT(6));
				else
					dc_set_clear(priv,
						     DC_OVERLAY_CONFIG,
						     BIT(30), BIT(29));
				switch (plane->fb.yuv_color_space) {
				case COLOR_SPACE_601:
					load_yuv_to_rgb(&priv->hw, reg, YUV601_2RGB);
					break;
				case COLOR_SPACE_709:
					load_yuv_to_rgb(&priv->hw, reg, YUV709_2RGB);
					break;
				case COLOR_SPACE_2020:
					load_yuv_to_rgb(&priv->hw, reg, YUV2020_2RGB);
					break;
				default:
					break;
				}
			}
		}
		if (plane->degamma.dirty) {
			switch (plane->degamma.mode) {
			case VS_DEGAMMA_DISABLE:
				if (i == PRIMARY_PLANE)
					dc_set_clear(priv,
						     DC_FRAMEBUFFER_CONFIG_EX,
						     0, BIT(5));
				else
					dc_set_clear(priv,
						     DC_OVERLAY_CONFIG,
						     0, BIT(28));
				break;
			case VS_DEGAMMA_BT709:
				load_degamma_table(&priv->hw, reg, DEGAMMA_709);
				if (i == PRIMARY_PLANE)
					dc_set_clear(priv,
						     DC_FRAMEBUFFER_CONFIG_EX,
						     BIT(5), 0);
				else
					dc_set_clear(priv,
						     DC_OVERLAY_CONFIG,
						     BIT(28), 0);
				break;
			case VS_DEGAMMA_BT2020:
				load_degamma_table(&priv->hw, reg, DEGAMMA_2020);
				if (i == PRIMARY_PLANE)
					dc_set_clear(priv,
						     DC_FRAMEBUFFER_CONFIG_EX,
						     BIT(5), 0);
				else
					dc_set_clear(priv,
						     DC_OVERLAY_CONFIG,
						     BIT(28), 0);
				break;
			default:
				break;
			}
			plane->degamma.dirty = false;
		}
	}
	plane_commit(priv);
}

static void setup_display(struct jhb100_dc8000_priv *priv,
			  struct dc_hw_display *display)
{
	u32 dpi_cfg;

	switch (display->bus_format) {
	case MEDIA_BUS_FMT_RGB565_1X16:
		dpi_cfg = 0;
		break;
	case MEDIA_BUS_FMT_RGB666_1X18:
		dpi_cfg = 3;
		break;
	case MEDIA_BUS_FMT_RGB666_1X24_CPADHI:
		dpi_cfg = 4;
		break;
	case MEDIA_BUS_FMT_RGB888_1X24:
		dpi_cfg = 5;
		break;
	case MEDIA_BUS_FMT_RGB101010_1X30:
		dpi_cfg = 6;
		break;
	default:
		dpi_cfg = 5;
		break;
	}
	dc_write(&priv->hw, DC_DISPLAY_DPI_CONFIG, dpi_cfg);

	dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, 0, BIT(4));

	dc_write(&priv->hw, DC_DISPLAY_H, priv->hw.display.h_active |
		 (priv->hw.display.h_total << 16));
	dc_write(&priv->hw, DC_DISPLAY_H_SYNC,
		 priv->hw.display.h_sync_start |
		 (priv->hw.display.h_sync_end << 15) |
		 (priv->hw.display.h_sync_polarity ? 0 : BIT(31)) |
		 BIT(30));
	dc_write(&priv->hw, DC_DISPLAY_V, priv->hw.display.v_active |
		 (priv->hw.display.v_total << 16));
	dc_write(&priv->hw, DC_DISPLAY_V_SYNC,
		 priv->hw.display.v_sync_start |
		 (priv->hw.display.v_sync_end << 15) |
		 (priv->hw.display.v_sync_polarity ? 0 : BIT(31)) |
		 BIT(30));

	if (priv->pipe_sync) {
		switch (display->sync_mode) {
		case VS_SINGLE_DC:
			dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG_EX,
				     0, BIT(3) | BIT(4));
			break;
		case VS_MULTI_DC_PRIMARY:
			dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG_EX,
				     BIT(3) | BIT(4), 0);
			break;
		case VS_MULTI_DC_SECONDARY:
			dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG_EX,
				     BIT(3), BIT(4));
			break;
		default:
			break;
		}
	}

	dc_write(&priv->hw, DC_DISPLAY_DITHER_CONFIG, 0);
	dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, BIT(4), 0);
}

static void setup_display_ex(struct jhb100_dc8000_priv *priv,
			     struct dc_hw_display *display)
{
	u32 dp_cfg;
	bool is_yuv = false;

	switch (display->bus_format) {
	case MEDIA_BUS_FMT_RGB565_1X16:
		dp_cfg = 0;
		break;
	case MEDIA_BUS_FMT_RGB666_1X18:
		dp_cfg = 1;
		break;
	case MEDIA_BUS_FMT_RGB888_1X24:
		dp_cfg = 2;
		break;
	case MEDIA_BUS_FMT_RGB101010_1X30:
		dp_cfg = 3;
		break;
	case MEDIA_BUS_FMT_UYYVYY8_0_5X24:
		dp_cfg = 0;
		is_yuv = true;
		break;
	case MEDIA_BUS_FMT_UYVY8_1X16:
		dp_cfg = 2 << 4;
		is_yuv = true;
		break;
	case MEDIA_BUS_FMT_YUV8_1X24:
		dp_cfg = 4 << 4;
		is_yuv = true;
		break;
	case MEDIA_BUS_FMT_UYYVYY10_0_5X30:
		dp_cfg = 6 << 4;
		is_yuv = true;
		break;
	case MEDIA_BUS_FMT_UYVY10_1X20:
		dp_cfg = 8 << 4;
		is_yuv = true;
		break;
	case MEDIA_BUS_FMT_YUV10_1X30:
		dp_cfg = 10 << 4;
		is_yuv = true;
		break;
	default:
		dp_cfg = 2;
		break;
	}
	if (is_yuv)
		dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG_EX, BIT(7), 0);
	else
		dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG_EX, 0, BIT(7));
	dc_write(&priv->hw, DC_DISPLAY_DP_CONFIG, dp_cfg | BIT(3));

	setup_display(priv, display);
}

static const struct dc_hw_funcs hw_func[] = {
	{
		.gamma = gamma_commit,
		.plane = plane_commit,
		.display = setup_display,
	},
	{
		.gamma = gamma_commit,
		.plane = plane_commit,
		.display = setup_display,
	},
	{
		.gamma = gamma_ex_commit,
		.plane = plane_ex_commit,
		.display = setup_display_ex,
	},
	{
		.gamma = gamma_ex_commit,
		.plane = plane_ex_commit,
		.display = setup_display_ex,
	},
};

static inline u32 hi_read(struct dc_hw *hw, u32 reg)
{
	return readl(hw->dc_base + reg);
}

static void load_default_filter(struct dc_hw *hw,
				const struct dc_hw_plane_reg *reg)
{
	u8 i;

	dc_write(hw, reg->scale_config, 0x33);
	dc_write(hw, reg->init_offset, 0x80008000);
	dc_write(hw, reg->h_filter_coef_index, 0x00);
	for (i = 0; i < coef_table[HORIZONTAL_COEF].size; i++)
		dc_write(hw, reg->h_filter_coef_data,
			 coef_table[HORIZONTAL_COEF].data[i]);

	dc_write(hw, reg->v_filter_coef_index, 0x00);
	for (i = 0; i < coef_table[VERTICAL_COEF].size; i++)
		dc_write(hw, reg->v_filter_coef_data,
			 coef_table[VERTICAL_COEF].data[i]);
}

static void load_rgb_to_rgb(struct dc_hw *hw, const struct dc_hw_plane_reg *reg,
			    const u16 *table)
{
	dc_write(hw, reg->rgb_to_rgb_coef0, table[0] | (table[1] << 16));
	dc_write(hw, reg->rgb_to_rgb_coef1, table[2] | (table[3] << 16));
	dc_write(hw, reg->rgb_to_rgb_coef2, table[4] | (table[5] << 16));
	dc_write(hw, reg->rgb_to_rgb_coef3, table[6] | (table[7] << 16));
	dc_write(hw, reg->rgb_to_rgb_coef5, table[8]);
}

static void load_rgb_to_yuv(struct dc_hw *hw, const s16 *table)
{
	dc_write(hw, DC_DISPLAY_RGBTOYUV_COEF0, table[0] | (table[1] << 16));
	dc_write(hw, DC_DISPLAY_RGBTOYUV_COEF1, table[2] | (table[3] << 16));
	dc_write(hw, DC_DISPLAY_RGBTOYUV_COEF2, table[4] | (table[5] << 16));
	dc_write(hw, DC_DISPLAY_RGBTOYUV_COEF3, table[6] | (table[7] << 16));
	dc_write(hw, DC_DISPLAY_RGBTOYUV_COEF4, table[8]);
	dc_write(hw, DC_DISPLAY_RGBTOYUV_COEFD0, table[9]);
	dc_write(hw, DC_DISPLAY_RGBTOYUV_COEFD1, table[10]);
	dc_write(hw, DC_DISPLAY_RGBTOYUV_COEFD2, table[11]);
}

static int dc_hw_init(struct jhb100_dc8000_priv *priv)
{
	u8 i;
	struct dc_hw *hw = &priv->hw;
	u32 revision = hi_read(hw, DC_HW_REVISION_REG);
	u32 cid = hi_read(hw, DC_HW_CHIP_CID_REG);

	printf("DC8000 Revision: 0x%x, Chip ID: 0x%x\n", revision, cid);
	if (!revision) {
		printf("DC8000 revision is 0x0, read fail\n");
		return -ENXIO;
	}

	switch (revision) {
	case 0x5551:
		hw->rev = (cid < 0x306) ? DC_REV_5551 : DC_REV_5551_306;
		priv->pipe_sync = false;
		break;
	case 0x5701:
		hw->rev = (cid < 0x309) ? DC_REV_5701_303 : DC_REV_5701_309;
		priv->pipe_sync = (hw->rev == DC_REV_5701_303) ? false : true;
		break;
	default:
		return -ENXIO;
	}

	if (hw->rev == DC_REV_5551) {
		hw->read_block =
		    malloc(sizeof(struct dc_hw_read) * READ_REG_COUNT);
		if (!hw->read_block)
			return -ENOMEM;
		for (i = 0; i < READ_REG_COUNT; i++)
			hw->read_block[i].reg = dc_read_reg_list[i];
	}

	hw->func = (struct dc_hw_funcs *)&hw_func[hw->rev];

	for (i = 0; i < plane_reg_table.size; i++) {
		const struct dc_hw_plane_reg *data = &plane_reg_table.data[i];

		load_default_filter(hw, data);

		if (hw->rev == DC_REV_5701_303 || hw->rev == DC_REV_5701_309)
			load_rgb_to_rgb(hw, data, RGB2RGB);
	}

	if (hw->rev == DC_REV_5701_303)
		load_rgb_to_yuv(hw, RGB2YUV);

	dc_write(hw, DC_CURSOR_BACKGROUND, 0x00FFFFFF);
	if (dc_read(hw, DC_CURSOR_BACKGROUND) != 0x00FFFFFF) {
		printf("dc_read(hw, DC_CURSOR_BACKGROUND) val is: 0x%x\n, not 0xFFFFFF",
		       dc_read(hw, DC_CURSOR_BACKGROUND));
		return -EINVAL;
	}
	dc_write(hw, DC_CURSOR_FOREGROUND, 0x00AAAAAA);
	if (dc_read(hw, DC_CURSOR_FOREGROUND) != 0x00AAAAAA) {
		printf("dc_read(hw, DC_CURSOR_FOREGROUND) val is: 0x%x\n, not 0xAAAAAA",
		       dc_read(hw, DC_CURSOR_FOREGROUND));
		return -EINVAL;
	}
	dc_write(hw, DC_DISPLAY_PANEL_CONFIG, 0x111);
	if (dc_read(hw, DC_DISPLAY_PANEL_CONFIG) != 0x111) {
		printf("dc_read(hw, DC_DISPLAY_PANEL_CONFIG) val is: 0x%x\n, not 0x111",
		       dc_read(hw, DC_DISPLAY_PANEL_CONFIG));
		return -EINVAL;
	}

	return 0;
}

static void dc_hw_setup_display(struct jhb100_dc8000_priv *priv, struct dc_hw_display *display)
{
	memcpy(&priv->hw.display, display, sizeof(*display));
	priv->hw.func->display(priv, display);
}

static bool dc_hw_flip_in_progress(struct dc_hw *hw)
{
	return dc_read(hw, DC_FRAMEBUFFER_CONFIG) & BIT(6);
}

static void dc_hw_enable_shadow_register(struct jhb100_dc8000_priv *priv, bool enable)
{
	if (enable)
		dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, 0, BIT(3));
	else
		dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, BIT(3), 0);
}

static void dc_hw_commit(struct jhb100_dc8000_priv *priv)
{
	priv->hw.func->gamma(priv);
	priv->hw.func->plane(priv);

	if (priv->hw.overlay.pos.dirty) {
		dc_write(&priv->hw, DC_OVERLAY_TOP_LEFT,
			 priv->hw.overlay.pos.start_x |
			 (priv->hw.overlay.pos.start_y << 15));
		dc_write(&priv->hw, DC_OVERLAY_BOTTOM_RIGHT,
			 priv->hw.overlay.pos.end_x |
			 (priv->hw.overlay.pos.end_y << 15));
		priv->hw.overlay.pos.dirty = false;
	}

	if (priv->hw.overlay.blend.dirty) {
		dc_write(&priv->hw, DC_OVERLAY_SRC_GLOBAL_COLOR,
			 priv->hw.overlay.blend.alpha << 24);
		dc_write(&priv->hw, DC_OVERLAY_DST_GLOBAL_COLOR,
			 priv->hw.overlay.blend.alpha << 24);
		switch (priv->hw.overlay.blend.blend_mode) {
		case BLEND_PREMULTI:
			dc_write(&priv->hw, DC_OVERLAY_BLEND_CONFIG, 0x3450);
			break;
		case BLEND_COVERAGE:
			dc_write(&priv->hw, DC_OVERLAY_BLEND_CONFIG, 0x3950);
			break;
		case BLEND_PIXEL_NONE:
			dc_write(&priv->hw, DC_OVERLAY_BLEND_CONFIG, 0x3548);
			break;
		default:
			break;
		}
		priv->hw.overlay.blend.dirty = false;
	}
}

static void vs_dc_commit(struct jhb100_dc8000_priv *priv)
{
	if (!priv->first_frame) {
		if (dc_hw_flip_in_progress(&priv->hw))
			udelay(100);

		dc_hw_enable_shadow_register(priv, false);
	}

	dc_hw_commit(priv);

	if (priv->first_frame)
		priv->first_frame = false;

	dc_hw_enable_shadow_register(priv, true);
}

static void dc_hw_update_plane(struct dc_hw *hw, enum dc_hw_plane_id id,
			       struct dc_hw_fb *fb, struct dc_hw_scale *scale)
{
	struct dc_hw_plane *plane = NULL;

	if (id == PRIMARY_PLANE)
		plane = &hw->primary;
	else if (id == OVERLAY_PLANE)
		plane = &hw->overlay.plane;

	if (plane) {
		if (fb) {
			if (!fb->enable)
				plane->fb.enable = false;
			else
				memcpy(&plane->fb, fb,
				       sizeof(*fb) - sizeof(fb->dirty));
			plane->fb.dirty = true;
		}
		if (scale) {
			memcpy(&plane->scale, scale,
			       sizeof(*scale) - sizeof(scale->dirty));
			plane->scale.dirty = true;
		}
	}
}

static void vs_update_primary_plane(struct jhb100_dc8000_priv *priv,
				    struct dc_hw_fb *fb,
				    struct dc_hw_scale *scale)
{
	dc_hw_update_plane(&priv->hw, PRIMARY_PLANE, fb, scale);
}

static struct dc_hw_scale no_scale = {
	.enable = 0,
};

static inline void update_bits32(void __iomem *base,
				 u32 off, u32 mask, u32 val_shifted)
{
	clrsetbits_le32(base + off, mask, val_shifted & mask);
}

static int cfg_vout_clk(struct udevice *dev, u32 id, uint32_t pclk_hz)
{
	void __iomem *syscon, *crg;
	u64 div_pll, pll_clk, fvco;
	u64 fbdiv, frac;
	u64 rem, rem_scaled, tmp;
	u32 ph;
	ofnode n;
	ofnode osc = ofnode_path("/osc");
	u32 osc_freq = 0;

	if (!dev || !pclk_hz)
		return -EINVAL;

	ph = dev_read_u32_default(dev, "starfive,syscon", 0);
	if (!ph)
		return -EINVAL;

	n = ofnode_get_by_phandle(ph);
	if (!ofnode_valid(n))
		return -EINVAL;

	syscon = (void __iomem *)ofnode_get_addr(n);
	if (syscon == (void __iomem *)FDT_ADDR_T_NONE)
		return -EINVAL;

	ph = dev_read_u32_default(dev, "starfive,crg", 0);
	if (!ph)
		return -EINVAL;

	n = ofnode_get_by_phandle(ph);
	if (!ofnode_valid(n))
		return -EINVAL;

	crg = (void __iomem *)ofnode_get_addr(n);
	if (crg == (void __iomem *)FDT_ADDR_T_NONE)
		return -EINVAL;

	if (ofnode_valid(osc))
		osc_freq = ofnode_read_u32_default(osc, "clock-frequency", 0);

	if (!osc_freq)
		return -EINVAL;

	div_pll = (pclk_hz > 74250000U) ? 1 : 4;
	pll_clk = (u64)pclk_hz * div_pll;
	fvco    = pll_clk * 16;

	/* fbdiv = fvco / osc_freq, rem = fvco % osc_freq */
	tmp = fvco;
	fbdiv = tmp;
	do_div(fbdiv, osc_freq);

	rem = fvco - fbdiv * osc_freq;
	rem_scaled = rem << 24;
	rem_scaled += (osc_freq / 2);
	frac = rem_scaled;
	do_div(frac, osc_freq);

	if (frac > 0xFFFFFFULL) {
		frac = 0;
		fbdiv += 1;
	}

	if (id == 0) {
		update_bits32(crg, 0x40, GENMASK(2, 0),
			      (u32)(div_pll << 0));
		update_bits32(syscon, 0x18, GENMASK(13, 2),
			      (u32)(fbdiv << 2));
		update_bits32(syscon, 0x1c, GENMASK(23, 0),
			      (u32)(frac << 0));
	} else {
		update_bits32(crg, 0x44, GENMASK(2, 0),
			      (u32)(div_pll << 0));
		update_bits32(syscon, 0x24, GENMASK(13, 2),
			      (u32)(fbdiv << 2));
		update_bits32(syscon, 0x28, GENMASK(23, 0),
			      (u32)(frac << 0));
	}

	mdelay(100);

	return 0;
}

static int dc_setup_fb_and_display(struct dc_hw_fb *fb,
				   struct dc_hw_display *dc,
				   const struct display_timing *timing,
				   struct video_uc_plat *plat)
{
	int hactive, hfp, hbp, hsync;
	int vactive, vfp, vbp, vsync;

	if (!fb || !dc || !timing || !plat)
		return -EINVAL;

	hactive = timing->hactive.typ;
	hfp     = timing->hfront_porch.typ;
	hbp     = timing->hback_porch.typ;
	hsync   = timing->hsync_len.typ;

	vactive = timing->vactive.typ;
	vfp     = timing->vfront_porch.typ;
	vbp     = timing->vback_porch.typ;
	vsync   = timing->vsync_len.typ;

	memset(dc, 0, sizeof(*dc));
	memset(fb, 0, sizeof(*fb));

	fb->width = hactive;
	fb->height = vactive;
	fb->y_address       = plat->base;
	fb->u_address       = 0x0;
	fb->v_address       = 0x0;
	fb->y_stride        = ALIGN(fb->width * 4, 128);
	fb->u_stride        = 0;
	fb->v_stride        = 0;
	fb->format          = FORMAT_A8R8G8B8;
	fb->tile_mode       = 0;
	fb->rotation        = 0;
	fb->yuv_color_space = 0;
	fb->swizzle         = 0;
	fb->uv_swizzle      = 0;
	fb->enable          = 1;
	fb->dirty           = 1;

	dc->h_active     = hactive;
	dc->h_sync_start = hactive + hfp;
	dc->h_sync_end   = hactive + hfp + hsync;
	dc->h_total      = hactive + hfp + hsync + hbp;
	dc->v_active     = vactive;
	dc->v_sync_start = vactive + vfp;
	dc->v_sync_end   = vactive + vfp + vsync;
	dc->v_total      = vactive + vfp + vsync + vbp;
	dc->frame_rate   = (timing->pixelclock.typ) /
			   (dc->h_total * dc->v_total);

	dc->h_sync_polarity = (timing->flags & DISPLAY_FLAGS_HSYNC_HIGH)
			       ? 1 : 0;
	dc->v_sync_polarity = (timing->flags & DISPLAY_FLAGS_VSYNC_HIGH)
			       ? 1 : 0;

	dc->bus_format      = MEDIA_BUS_FMT_RGB888_1X24;
	dc->sync_mode       = VS_SINGLE_DC;

	return 0;
}

static int jhb100_dc8000_bind(struct udevice *dev)
{
	struct video_uc_plat *plat = dev_get_uclass_plat(dev);

	/* Go for the maximum supported resolution */
	plat->size = ALIGN(JHB100_MAX_XRES * VNBYTES(VIDEO_BPP32), 128) *
			JHB100_MAX_YRES;
	plat->align = JHB100_FB_ALIGN;

	return 0;
}

static int jhb100_dc8000_probe(struct udevice *dev)
{
	struct jhb100_dc8000_priv *priv = dev_get_priv(dev);
	struct dc_hw          *hw       = &priv->hw;
	struct video_uc_plat  *plat     = dev_get_uclass_plat(dev);
	struct video_priv     *uc_priv  = dev_get_uclass_priv(dev);
	struct udevice        *disp_dev = NULL;
	struct display_timing  timing;
	enum force_timing      req_timing;
	u32 dc_id, alloc_x, alloc_y;
	int err;

	err = clk_get_bulk(dev, &priv->clks);
	if (err < 0)
		return err;

	err = reset_get_by_index(dev, 0, &priv->reset);
	if (err)
		return err;

	err = clk_enable_bulk(&priv->clks);
	if (err)
		return err;

	err = reset_deassert(&priv->reset);
	if (err)
		return err;

	priv->dc = malloc(sizeof(struct dc_hw_display));
	if (!priv->dc)
		goto err_dc8000_probe;
	priv->fb = malloc(sizeof(struct dc_hw_fb));
	if (!priv->fb)
		goto err_dc8000_probe;

	dc_id = dev_read_u32_default(dev, "dc-id", 0);

	memset(hw, 0, sizeof(*hw));
	hw->dc_base = dev_read_addr_ptr(dev);
	if (!hw->dc_base) {
		err = -EINVAL;
		goto err_dc8000_probe;
	}

	err = uclass_get_device(UCLASS_DISPLAY, 0, &disp_dev);
	if (err) {
		printf("Failed to get display controller 0 (%d)\n", err);
		goto err_dc8000_probe;
	}

	req_timing = video_jhb100_get_timing();
	if (req_timing == FORCE_TIMING_NONE) {
		err = display_read_timing(disp_dev, &timing);
		if (err) {
			printf("EDID Read timing failure\n");
			goto err_dc8000_probe;
		}
	} else {
		timing = timing_default[req_timing];
	}

	/* Configure PLL clock according to timing */
	cfg_vout_clk(dev, dc_id, timing.pixelclock.typ);

	/* Configure frame buffer and display controller */
	err = dc_setup_fb_and_display(priv->fb, priv->dc, &timing, plat);
	if (err)
		goto err_dc8000_probe;

	err = dc_hw_init(priv);
	if (err)
		goto err_dc8000_probe;

	/* Configure plane */
	vs_update_primary_plane(priv, priv->fb, &no_scale);
	vs_dc_commit(priv);

	/* Enable Display Controller */
	dc_hw_setup_display(priv, priv->dc);

	/* Enable Display Port */
	display_enable(disp_dev, VNBITS(uc_priv->bpix), &timing);

	/* Enable cache flush in post probe */
	video_set_flush_dcache(dev, true);

	/* Populate uclass priv */
	uc_priv->xsize = timing.hactive.typ;
	uc_priv->ysize = timing.vactive.typ;
	uc_priv->bpix = VIDEO_BPP32;
	uc_priv->rot = 0;

	alloc_x = timing.hactive.typ;
	alloc_y = timing.vactive.typ;

	return 0;

err_dc8000_probe:
	if (priv->fb)
		free(priv->fb);
	if (priv->dc)
		free(priv->dc);
	reset_assert(&priv->reset);
	clk_disable_bulk(&priv->clks);
	clk_release_bulk(&priv->clks);
	return err;
}

static int jhb100_dc8000_remove(struct udevice *dev)
{
	struct jhb100_dc8000_priv *priv = dev_get_priv(dev);

	dc_set_clear(priv, DC_FRAMEBUFFER_CONFIG, 0, BIT(4) | BIT(0));

	free(priv->dc);
	free(priv->fb);
	free(priv->hw.read_block);
	reset_assert(&priv->reset);
	clk_release_bulk(&priv->clks);

	return 0;
}

static const struct udevice_id jhb100_dc8000_ids[] = {
	{ .compatible = "starfive,jhb100-dc8000" },
	{ }
};

U_BOOT_DRIVER(jhb100_dc8000) = {
	.name = "jhb100_dc8000",
	.id = UCLASS_VIDEO,
	.of_match = jhb100_dc8000_ids,
	.bind = jhb100_dc8000_bind,
	.probe = jhb100_dc8000_probe,
	.remove = jhb100_dc8000_remove,
	.priv_auto = sizeof(struct jhb100_dc8000_priv),
};
