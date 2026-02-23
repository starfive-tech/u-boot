/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * StarFive JHB100 DWC DisplayPort Transmitter Driver Header
 *
 * Copyright (c) 2026 StarFive Technology Co., Ltd.
 */

#ifndef __JHB100_DW_DP_H__
#define __JHB100_DW_DP_H__

#include <reset.h>

#include <linux/types.h>
#include <linux/bitops.h>
#include <linux/bitfield.h>
#include <linux/media-bus-format.h>

/* ------------------------------------------------------------------------- */
/* DRM/DP minimal definitions (only what the driver uses)                    */
/* ------------------------------------------------------------------------- */
#define DRM_COLOR_FORMAT_RGB444		BIT(0)
#define DRM_COLOR_FORMAT_YCRCB444	BIT(1)
#define DRM_COLOR_FORMAT_YCRCB422	BIT(2)
#define DRM_COLOR_FORMAT_YCRCB420	BIT(3)

/* Mode flags (keep if your driver consumes these flags) */
#define DRM_MODE_FLAG_PHSYNC		BIT(0)
#define DRM_MODE_FLAG_NHSYNC		BIT(1)
#define DRM_MODE_FLAG_PVSYNC		BIT(2)
#define DRM_MODE_FLAG_NVSYNC		BIT(3)
#define DRM_MODE_FLAG_INTERLACE		BIT(4)
#define DRM_MODE_FLAG_DBLSCAN		BIT(5)
#define DRM_MODE_FLAG_CSYNC		BIT(6)
#define DRM_MODE_FLAG_PCSYNC		BIT(7)
#define DRM_MODE_FLAG_NCSYNC		BIT(8)
#define DRM_MODE_FLAG_HSKEW		BIT(9)
#define DRM_MODE_FLAG_DBLCLK		BIT(12)
#define DRM_MODE_FLAG_CLKDIV2		BIT(13)

/* ------------------------------------------------------------------------- */
/* DPTX Video Mapping IDs (Synopsys video_mapping field)                     */
/* ------------------------------------------------------------------------- */
enum dw_dp_video_mapping {
	DPTX_VM_RGB_6BIT,
	DPTX_VM_RGB_8BIT,
	DPTX_VM_RGB_10BIT,
	DPTX_VM_RGB_12BIT,
	DPTX_VM_RGB_16BIT,
	DPTX_VM_YCBCR444_8BIT,
	DPTX_VM_YCBCR444_10BIT,
	DPTX_VM_YCBCR444_12BIT,
	DPTX_VM_YCBCR444_16BIT,
	DPTX_VM_YCBCR422_8BIT,
	DPTX_VM_YCBCR422_10BIT,
	DPTX_VM_YCBCR422_12BIT,
	DPTX_VM_YCBCR422_16BIT,
	DPTX_VM_YCBCR420_8BIT,
	DPTX_VM_YCBCR420_10BIT,
	DPTX_VM_YCBCR420_12BIT,
	DPTX_VM_YCBCR420_16BIT,
};

struct drm_dp_aux_msg {
	u32 address;
	u8 request;
	u8 reply;
	void *buffer;
	size_t size;
};

struct dw_dp_output_format {
	u32 bus_format;		/* MEDIA_BUS_FMT_* */
	u32 color_format;	/* DRM_COLOR_FORMAT_* bitmask */
	u8 video_mapping;	/* enum dw_dp_video_mapping */
	u8 bpc;			/* bits per component */
	u8 bpp;			/* bits per pixel */
};

static const struct dw_dp_output_format dw_dp_possible_output_fmts[] = {
	{ MEDIA_BUS_FMT_RGB101010_1X30, DRM_COLOR_FORMAT_RGB444,
	  DPTX_VM_RGB_10BIT, 10, 30 },
	{ MEDIA_BUS_FMT_RGB888_1X24, DRM_COLOR_FORMAT_RGB444,
	  DPTX_VM_RGB_8BIT, 8, 24 },
	{ MEDIA_BUS_FMT_YUV10_1X30, DRM_COLOR_FORMAT_YCRCB444,
	  DPTX_VM_YCBCR444_10BIT, 10, 30 },
	{ MEDIA_BUS_FMT_YUV8_1X24, DRM_COLOR_FORMAT_YCRCB444,
	  DPTX_VM_YCBCR444_8BIT, 8, 24 },
	{ MEDIA_BUS_FMT_YUYV10_1X20, DRM_COLOR_FORMAT_YCRCB422,
	  DPTX_VM_YCBCR422_10BIT, 10, 20 },
	{ MEDIA_BUS_FMT_YUYV8_1X16, DRM_COLOR_FORMAT_YCRCB422,
	  DPTX_VM_YCBCR422_8BIT, 8, 16 },
	{ MEDIA_BUS_FMT_UYYVYY10_0_5X30, DRM_COLOR_FORMAT_YCRCB420,
	  DPTX_VM_YCBCR420_10BIT, 10, 15 },
	{ MEDIA_BUS_FMT_UYYVYY8_0_5X24, DRM_COLOR_FORMAT_YCRCB420,
	  DPTX_VM_YCBCR420_8BIT, 8, 12 },
	{ MEDIA_BUS_FMT_RGB666_1X24_CPADHI, DRM_COLOR_FORMAT_RGB444,
	  DPTX_VM_RGB_6BIT, 6, 18 },
};

/* ------------------------------------------------------------------------- */
/* DPTX register offsets + bitfields                                         */
/* ------------------------------------------------------------------------- */
#define DPTX_VERSION_NUMBER			0x0000

#define DPTX_CCTL				0x0200
#define  FORCE_HPD				BIT(4)
#define  DEFAULT_FAST_LINK_TRAIN_EN		BIT(2)
#define  ENHANCE_FRAMING_EN			BIT(1)
#define  SCRAMBLE_DIS				BIT(0)

#define DPTX_SOFT_RESET_CTRL			0x0204
#define  VIDEO_RESET				BIT(5)
#define  AUX_RESET				BIT(4)
#define  AUDIO_SAMPLER_RESET			BIT(3)
#define  PHY_SOFT_RESET				BIT(1)
#define  CONTROLLER_RESET			BIT(0)

#define DPTX_VSAMPLE_CTRL			0x0300
#define  PIXEL_MODE_SELECT			GENMASK(22, 21)
#define  VIDEO_MAPPING				GENMASK(20, 16)
#define  VIDEO_STREAM_ENABLE			BIT(5)

#define DPTX_VINPUT_POLARITY_CTRL		0x030c
#define  DE_IN_POLARITY				BIT(2)
#define  HSYNC_IN_POLARITY			BIT(1)
#define  VSYNC_IN_POLARITY			BIT(0)

#define DPTX_VIDEO_CONFIG1			0x0310
#define  HACTIVE				GENMASK(31, 16)
#define  HBLANK					GENMASK(15, 2)
#define  I_P					BIT(1)
#define  R_V_BLANK_IN_OSC			BIT(0)

#define DPTX_VIDEO_CONFIG2			0x0314
#define  VBLANK					GENMASK(31, 16)
#define  VACTIVE				GENMASK(15, 0)

#define DPTX_VIDEO_CONFIG3			0x0318
#define  H_SYNC_WIDTH				GENMASK(31, 16)
#define  H_FRONT_PORCH				GENMASK(15, 0)

#define DPTX_VIDEO_CONFIG4			0x031c
#define  V_SYNC_WIDTH				GENMASK(31, 16)
#define  V_FRONT_PORCH				GENMASK(15, 0)

#define DPTX_VIDEO_CONFIG5			0x0320
#define  INIT_THRESHOLD_HI			GENMASK(22, 21)
#define  AVERAGE_BYTES_PER_TU_FRAC		GENMASK(19, 16)
#define  INIT_THRESHOLD				GENMASK(13, 7)
#define  AVERAGE_BYTES_PER_TU			GENMASK(6, 0)

#define DPTX_VIDEO_MSA1				0x0324
#define  VSTART					GENMASK(31, 16)
#define  HSTART					GENMASK(15, 0)

#define DPTX_VIDEO_MSA2				0x0328
#define  MISC0					GENMASK(31, 24)

#define DPTX_VIDEO_MSA3				0x032c
#define  MISC1					GENMASK(31, 24)

#define DPTX_VIDEO_HBLANK_INTERVAL		0x0330
#define  HBLANK_INTERVAL_EN			BIT(16)
#define  HBLANK_INTERVAL			GENMASK(15, 0)

#define DPTX_MVID_CONFIG1			0x0338
#define DPTX_MVID_CONFIG2			0x033c

#define DPTX_SDP_VERTICAL_CTRL			0x0500
#define  EN_VERTICAL_SDP			BIT(2)
#define  EN_AUDIO_STREAM_SDP			BIT(1)
#define  EN_AUDIO_TIMESTAMP_SDP			BIT(0)

#define DPTX_SDP_HORIZONTAL_CTRL		0x0504
#define  EN_HORIZONTAL_SDP			BIT(2)

#define DPTX_SDP_REGISTER_BANK			0x0600
#define  SDP_REGS				GENMASK(31, 0)

#define DPTX_PHYIF_CTRL				0x0a00
#define  PHY_WIDTH				BIT(25)
#define  PHY_POWERDOWN				GENMASK(20, 17)
#define  SSC_DIS				BIT(16)
#define  PHY_BUSY				GENMASK(15, 12)
#define  XMIT_ENABLE				GENMASK(11, 8)
#define  PHY_LANES				GENMASK(7, 6)
#define  PHY_RATE				GENMASK(5, 4)
#define  TPS_SEL				GENMASK(3, 0)

#define DPTX_PHY_TX_EQ				0x0a04

#define DPTX_PHYIF_PWRDOWN_CTRL			0x0a18
#define  PHY_LANE_CTRL_SYNC			BIT(17)
#define  PER_LANE_PWRDOWN_CTRL_EN		BIT(16)
#define  POWER_DOWN_CTRL_LANE2_3		GENMASK(13, 12)
#define  POWER_DOWN_CTRL_LANE1			GENMASK(9, 8)
#define  POWER_DOWN_CTRL_LANE0			GENMASK(5, 4)

#define DPTX_AUX_CMD				0x0b00
#define  AUX_CMD_TYPE				GENMASK(31, 28)
#define  AUX_ADDR				GENMASK(27, 8)
#define  I2C_ADDR_ONLY				BIT(4)
#define  AUX_LEN_REQ				GENMASK(3, 0)

#define DPTX_AUX_STATUS				0x0b04
#define  AUX_TIMEOUT				BIT(17)
#define  AUX_BYTES_READ				GENMASK(23, 19)
#define  AUX_STATUS				GENMASK(7, 4)

#define DPTX_AUX_DATA0				0x0b08
#define DPTX_AUX_DATA1				0x0b0c
#define DPTX_AUX_DATA2				0x0b10
#define DPTX_AUX_DATA3				0x0b14

#define DPTX_GENERAL_INTERRUPT			0x0d00
#define  VIDEO_FIFO_OVERFLOW_STREAM0		BIT(6)
#define  AUDIO_FIFO_OVERFLOW_STREAM0		BIT(5)
#define  SDP_EVENT_STREAM0			BIT(4)
#define  AUX_CMD_INVALID			BIT(3)
#define  AUX_REPLY_EVENT			BIT(1)
#define  HPD_EVENT				BIT(0)

#define DPTX_GENERAL_INTERRUPT_ENABLE		0x0d04
#define  AUX_REPLY_EVENT_EN			BIT(1)
#define  HPD_EVENT_EN				BIT(0)

#define DPTX_HPD_STATUS				0x0d08
#define  HPD_STATE				GENMASK(11, 9)
#define  HPD_STATUS				BIT(8)
#define  HPD_HOT_UNPLUG				BIT(2)
#define  HPD_HOT_PLUG				BIT(1)
#define  HPD_IRQ				BIT(0)

#define DPTX_HPD_INTERRUPT_ENABLE		0x0d0c
#define  HPD_UNPLUG_ERR_EN			BIT(3)
#define  HPD_UNPLUG_EN				BIT(2)
#define  HPD_PLUG_EN				BIT(1)
#define  HPD_IRQ_EN				BIT(0)

/* ------------------------------------------------------------------------- */
/* DPCD registers (minimal set for link training / power / status)           */
/* ------------------------------------------------------------------------- */
#define DP_DPCD_REV				0x000
#define  DP_DPCD_REV_14				0x14

#define DP_MAX_LINK_RATE			0x001
#define DP_MAX_LANE_COUNT			0x002
#define  DP_MAX_LANE_COUNT_MASK			0x1f

#define DP_MAX_DOWNSPREAD			0x003
#define  DP_MAX_DOWNSPREAD_0_5			BIT(0)
#define  DP_NO_AUX_HANDSHAKE_LINK_TRAINING	BIT(6)

#define DP_MAIN_LINK_CHANNEL_CODING		0x006
#define  DP_CAP_ANSI_8B10B			BIT(0)

#define DP_TRAINING_AUX_RD_INTERVAL		0x00e
#define DP_TRAINING_AUX_RD_MASK			0x7f
#define DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT	BIT(7) /* DP 1.3 */

#define DP_LINK_BW_SET				0x100
#define DP_LANE_COUNT_SET			0x101
#define  DP_LANE_COUNT_ENHANCED_FRAME_EN	BIT(7)

#define DP_TRAINING_PATTERN_SET			0x102
#define  DP_TRAINING_PATTERN_DISABLE		0
#define  DP_TRAINING_PATTERN_1			1
#define  DP_TRAINING_PATTERN_2			2
#define  DP_TRAINING_PATTERN_3			3
#define  DP_TRAINING_PATTERN_4			7 /* DP 1.4 */

#define DP_TRAINING_LANE0_SET			0x103

#define DP_DOWNSPREAD_CTRL			0x107
#define  DP_SPREAD_AMP_0_5			BIT(4)

#define DP_MSTM_CTRL				0x111 /* 1.2 */
#define  DP_MST_EN				BIT(0)
#define  DP_UP_REQ_EN				BIT(1)
#define  DP_UPSTREAM_IS_SRC			BIT(2)

#define DP_MAIN_LINK_CHANNEL_CODING_SET		0x108
#define  DP_SET_ANSI_8B10B			BIT(0)

#define DP_LANE0_1_STATUS			0x202
#define DP_LANE_ALIGN_STATUS_UPDATED		0x204
#define  DP_INTERLANE_ALIGN_DONE		BIT(0)

#define DP_ADJUST_REQUEST_LANE0_1		0x206
#define DP_ADJUST_REQUEST_LANE2_3		0x207

#define DP_SET_POWER				0x600
#define  DP_SET_POWER_D0			0x1
#define  DP_SET_POWER_D3			0x2
#define  DP_SET_POWER_MASK			0x3

#define DP_RECEIVER_CAP_SIZE			0x0f
#define DP_LINK_STATUS_SIZE			6

#define DP_TPS3_SUPPORTED			BIT(6)
#define DP_TPS4_SUPPORTED			BIT(7)
#define DP_ENHANCED_FRAME_CAP			BIT(7)

#define DP_AUX_NATIVE_WRITE			0x8
#define DP_AUX_NATIVE_READ			0x9

#define DP_AUX_NATIVE_REPLY_ACK			(0x0 << 0)
#define DP_AUX_NATIVE_REPLY_NACK		(0x1 << 0)
#define DP_AUX_NATIVE_REPLY_DEFER		(0x2 << 0)
#define DP_AUX_NATIVE_REPLY_MASK		(0x3 << 0)

#define DP_TRAIN_VOLTAGE_SWING_SHIFT		0
#define DP_TRAIN_PRE_EMPHASIS_SHIFT		3

#define DP_ADJUST_VOLTAGE_SWING_LANE0_SHIFT	0
#define DP_ADJUST_PRE_EMPHASIS_LANE0_SHIFT	2
#define DP_ADJUST_VOLTAGE_SWING_LANE1_SHIFT	4
#define DP_ADJUST_PRE_EMPHASIS_LANE1_SHIFT	6

#define DP_SDP_VSC				0x07 /* DP 1.2 */
#define DP_DP13_DPCD_REV			0x2200

#define DP_LANE_CR_DONE				BIT(0)
#define DP_LANE_CHANNEL_EQ_DONE			BIT(1)
#define DP_LANE_SYMBOL_LOCKED			BIT(2)
#define DP_CHANNEL_EQ_BITS			(DP_LANE_CR_DONE | \
						 DP_LANE_CHANNEL_EQ_DONE | \
						 DP_LANE_SYMBOL_LOCKED)

#define _DP_MSA_MISC_COLOR(misc1_7, misc0_21, misc0_3, misc0_4) \
	((misc1_7) << 15 | (misc0_4) << 4 | (misc0_3) << 3 | ((misc0_21) << 1))
#define DP_MSA_MISC_COLOR_VSC_SDP		BIT(14)
#define DP_MSA_MISC_COLOR_RGB			_DP_MSA_MISC_COLOR(0, 0, 0, 0)
#define DP_MSA_MISC_COLOR_YCBCR_422_BT709	_DP_MSA_MISC_COLOR(0, 1, 1, 1)
#define DP_MSA_MISC_COLOR_YCBCR_444_BT709	_DP_MSA_MISC_COLOR(0, 2, 1, 1)

#define DP_MSA_MISC_6_BPC			(0 << 5)
#define DP_MSA_MISC_8_BPC			BIT(5)
#define DP_MSA_MISC_10_BPC			(2 << 5)
#define DP_MSA_MISC_12_BPC			(3 << 5)
#define DP_MSA_MISC_16_BPC			(4 << 5)

#define DP_DPRX_FEATURE_ENUMERATION_LIST	0x2210 /* DP 1.3 */
#define  DP_GTC_CAP				BIT(0) /* DP 1.3 */
#define  DP_SST_SPLIT_SDP_CAP			BIT(1) /* DP 1.4 */
#define  DP_AV_SYNC_CAP				BIT(2) /* DP 1.3 */
#define  DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORTED	BIT(3) /* DP 1.3 */
#define  DP_VSC_EXT_VESA_SDP_SUPPORTED		BIT(4) /* DP 1.4 */
#define  DP_VSC_EXT_VESA_SDP_CHAINING_SUPPORTED	BIT(5) /* DP 1.4 */
#define  DP_VSC_EXT_CEA_SDP_SUPPORTED		BIT(6) /* DP 1.4 */
#define  DP_VSC_EXT_CEA_SDP_CHAINING_SUPPORTED	BIT(7) /* DP 1.4 */

#define PIXCLK_ENA_SHIFT			0x0
#define PIXCLK_SW_SHIFT				0x1
#define DATMUX_CTRL_SHIFT			0x2
#define VS_POL_SEL_SHIFT			0x4
#define HS_POL_SEL_SHIFT			0x5

#define VOUT_DYNSW_VERSION			0x0000
#define VOUT_DYNSW_CSR				0x0004
#define VOUT_DYNSW_INTR_ENA			0x0008
#define VOUT_DYNSW_INTR_FORCE			0x000c
#define VOUT_DYNSW_INTR_CLEAR			0x0010
#define VOUT_DYNSW_DC_WDOG_TIME_CFG		0x0014

#define SW_DONE_INTR_CLEAR			BIT(0)
#define DATA_OFF_INTR_CLEAR			BIT(1)
#define SW_DONE_INTR				BIT(0)
#define DATA_OFF_INTR				BIT(1)

/* ------------------------------------------------------------------------- */
/* Pixel mode                                                                */
/* ------------------------------------------------------------------------- */
enum dw_dp_pixel_mode {
	DPTX_MP_SINGLE_PIXEL,
	DPTX_MP_DUAL_PIXEL,
	DPTX_MP_QUAD_PIXEL,
};

enum dw_dp_phyrate {
	DPTX_PHYRATE_RBR,
	DPTX_PHYRATE_HBR,
	DPTX_PHYRATE_HBR2,
	DPTX_PHYRATE_HBR3,
};

enum dw_dp_phypattern {
	DPTX_PHY_PATTERN_NONE,
	DPTX_PHY_PATTERN_TPS_1,
	DPTX_PHY_PATTERN_TPS_2,
	DPTX_PHY_PATTERN_TPS_3,
	DPTX_PHY_PATTERN_TPS_4,
	DPTX_PHY_PATTERN_SERM,
	DPTX_PHY_PATTERN_PBRS7,
	DPTX_PHY_PATTERN_CUSTOM_80BIT,
	DPTX_PHY_PATTERN_CP2520_1,
	DPTX_PHY_PATTERN_CP2520_2,
};

/* ------------------------------------------------------------------------- */
/* SDP / VSC                                                                 */
/* ------------------------------------------------------------------------- */
enum dp_pixelformat {
	DP_PIXELFORMAT_RGB = 0,
	DP_PIXELFORMAT_YUV444 = 0x1,
	DP_PIXELFORMAT_YUV422 = 0x2,
	DP_PIXELFORMAT_YUV420 = 0x3,
	DP_PIXELFORMAT_Y_ONLY = 0x4,
	DP_PIXELFORMAT_RAW = 0x5,
	DP_PIXELFORMAT_RESERVED = 0x6,
};

enum dp_colorimetry {
	DP_COLORIMETRY_DEFAULT = 0,
	DP_COLORIMETRY_RGB_WIDE_FIXED = 0x1,
	DP_COLORIMETRY_BT709_YCC = 0x1,
	DP_COLORIMETRY_RGB_WIDE_FLOAT = 0x2,
	DP_COLORIMETRY_XVYCC_601 = 0x2,
	DP_COLORIMETRY_OPRGB = 0x3,
	DP_COLORIMETRY_XVYCC_709 = 0x3,
	DP_COLORIMETRY_DCI_P3_RGB = 0x4,
	DP_COLORIMETRY_SYCC_601 = 0x4,
	DP_COLORIMETRY_RGB_CUSTOM = 0x5,
	DP_COLORIMETRY_OPYCC_601 = 0x5,
	DP_COLORIMETRY_BT2020_RGB = 0x6,
	DP_COLORIMETRY_BT2020_CYCC = 0x6,
	DP_COLORIMETRY_BT2020_YCC = 0x7,
};

enum dp_dynamic_range {
	DP_DYNAMIC_RANGE_VESA = 0,
	DP_DYNAMIC_RANGE_CTA = 1,
};

enum dp_content_type {
	DP_CONTENT_TYPE_NOT_DEFINED = 0x00,
	DP_CONTENT_TYPE_GRAPHICS = 0x01,
	DP_CONTENT_TYPE_PHOTO = 0x02,
	DP_CONTENT_TYPE_VIDEO = 0x03,
	DP_CONTENT_TYPE_GAME = 0x04,
};

enum {
	DPTX_SDP_VERTICAL_INTERVAL = BIT(0),
	DPTX_SDP_HORIZONTAL_INTERVAL = BIT(1),
};

enum {
	DP_SOURCE_STATE_IDLE,
	DP_SOURCE_STATE_UNPLUG,
	DP_SOURCE_STATE_HPD_TIMEOUT = 4,
	DP_SOURCE_STATE_PLUG = 7,
};

struct dp_sdp_header {
	u8 HB0;
	u8 HB1;
	u8 HB2;
	u8 HB3;
};

struct dw_dp_sdp {
	struct dp_sdp_header header;
	u8 db[32];
	unsigned long flags;
};

struct drm_dp_vsc_sdp {
	u8 sdp_type;
	u8 revision;
	u8 length;
	enum dp_pixelformat pixelformat;
	enum dp_colorimetry colorimetry;
	int bpc;
	enum dp_dynamic_range dynamic_range;
	enum dp_content_type content_type;
};

/* ------------------------------------------------------------------------- */
/* Link / mode structs (minimal)                                             */
/* ------------------------------------------------------------------------- */
struct drm_display_mode {
	int clock; /* kHz */
	int hdisplay;
	int hsync_start;
	int hsync_end;
	int htotal;
	int vdisplay;
	int vsync_start;
	int vsync_end;
	int vtotal;
	int vrefresh;
	int vscan;
	u32 flags;
	int picture_aspect_ratio;
	int hskew;
	u32 type;
	bool invalid;
};

struct drm_dp_link_caps {
	bool enhanced_framing;
	bool tps3_supported;
	bool tps4_supported;
	bool channel_coding;
	bool ssc;
};

struct drm_dp_link_train_set {
	u32 voltage_swing[4];
	u32 pre_emphasis[4];
};

struct drm_dp_link_train {
	struct drm_dp_link_train_set request;
	struct drm_dp_link_train_set adjust;
	bool clock_recovered;
	bool channel_equalized;
};

struct dw_dp_link {
	u8 dpcd[DP_RECEIVER_CAP_SIZE];
	u8 revision;
	u32 rate;
	u32 lanes;
	struct drm_dp_link_caps caps;
	struct drm_dp_link_train train;
	u8 sink_count;
	u8 vsc_sdp_extension_for_colorimetry_supported;
};

struct dw_dp_video {
	struct drm_display_mode mode;
	u32 bus_format;
	u8 video_mapping;
	u8 pixel_mode;
	u8 color_format;
	u8 bpc;
	u8 bpp;
};

struct connector_state {
	struct drm_display_mode mode;
	u8 edid[128];
	int bus_format;
};

#endif /* __JHB100_DW_DP_H__ */
