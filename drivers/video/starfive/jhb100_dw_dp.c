// SPDX-License-Identifier: GPL-2.0+
/*
 * StarFive JHB100 DWC DisplayPort Transmitter Driver
 *
 * Copyright (c) 2026 StarFive Technology Co., Ltd.
 */

#include <asm/io.h>
#include <asm/unaligned.h>
#include <div64.h>
#include <display.h>
#include <dm.h>
#include <dm/device_compat.h>
#include <edid.h>
#include <linux/bitfield.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/iopoll.h>
#include <linux/kernel.h>
#include <regmap.h>
#include <reset.h>
#include <syscon.h>
#include <video_starfive.h>

#include "jhb100_dw_dp.h"

#define DC_SYSCON_SYSREG_AUX_PWR	0x00
#define DC_SYSCON_SYSREG_CTRL		0x04
#define DC_SYSCON_SYSREG_COLOR		0x08
#define VOUT_SYSCON_CRG_PHY_CTRL	0x10c

#define DP_READ(p, r)		readl((p)->dp + (r))
#define DP_WRITE(p, r, v)	writel((v), (p)->dp + (r))

#define DYNSW_READ(base, r)	readl((base) + (r))
#define DYNSW_WRITE(base, r, v)	writel((v), (base) + (r))

/* If you use regmap for syscon, keep these macros. Otherwise delete them. */
#define VOUT_SYSCON_READ(p, r, v)  regmap_read((p)->vout_syscon, (r), &(v))
#define VOUT_SYSCON_WRITE(p, r, v) regmap_write((p)->vout_syscon, (r), (v))
#define DC_SYSCON_READ(p, r, v)    regmap_read((p)->dc_syscon, (r), &(v))
#define DC_SYSCON_WRITE(p, r, v)   regmap_write((p)->dc_syscon, (r), (v))

struct dw_dp {
	void __iomem *dp;
	void __iomem *dynsw;
	struct regmap *vout_syscon;
	struct regmap *dc_syscon;
	struct reset_ctl_bulk resets;

	struct dw_dp_link link;
	struct dw_dp_video video;

	u32 max_link_rate;
	u32 max_lane_count;
	u8 v_sync_polarity;
	u8 h_sync_polarity;

	u8 dc_id;

	struct connector_state conn_state;
};

static void to_byte_array(u32 value, u8 *arr)
{
	memcpy(arr, &value, sizeof(value));
}

static int dp_edid_read(struct dw_dp *priv, u8 *edid_data, int len)
{
	u32 tmp = 0;
	int cnt = 0;

	DP_WRITE(priv, DPTX_AUX_CMD, 0x40003000);
	while ((DP_READ(priv, DPTX_GENERAL_INTERRUPT) & 0x00000002) == 0)
		mdelay(10);

	tmp = DP_READ(priv, DPTX_AUX_STATUS);
	while (((tmp >> 16) & 0x1) == 0x1) {
		tmp = DP_READ(priv, DPTX_AUX_STATUS);
		mdelay(10);
	}

	DP_WRITE(priv, DPTX_AUX_CMD, 0x40005000);
	while ((DP_READ(priv, DPTX_GENERAL_INTERRUPT) & 0x00000002) == 0)
		mdelay(10);

	tmp = DP_READ(priv, DPTX_AUX_STATUS);
	while (((tmp >> 16) & 0x1) == 0x1) {
		tmp = DP_READ(priv, DPTX_AUX_STATUS);
		mdelay(10);
	}

	for (int i = 0; i < 8 && cnt < len; i++) {
		tmp = 0;
		DP_WRITE(priv, DPTX_AUX_CMD, 0x5000500f);
		while ((tmp & 0x2) == 0) {
			tmp = DP_READ(priv, DPTX_GENERAL_INTERRUPT);
			mdelay(10);
		}

		tmp = DP_READ(priv, DPTX_AUX_STATUS);
		while (((tmp >> 16) & 0x1) == 0x1) {
			tmp = DP_READ(priv, DPTX_AUX_STATUS);
			mdelay(10);
		}

		for (int j = 0; j < 4; j++) {
			tmp = DP_READ(priv, DPTX_AUX_DATA0 + j * 4);
			to_byte_array(tmp, edid_data + cnt);
			cnt += 4;
		}
	}

	return 0;
}

static int dw_dp_aux_read_data(struct dw_dp *priv, u8 *buffer, size_t size)
{
	size_t i, j;

	for (i = 0; i < DIV_ROUND_UP(size, 4); i++) {
		size_t num = min_t(size_t, size - i * 4, 4);
		u32 value;

		value = DP_READ(priv, DPTX_AUX_DATA0 + i * 4);

		for (j = 0; j < num; j++)
			buffer[i * 4 + j] = value >> (j * 8);
	}

	return size;
}

static int dw_dp_aux_write_data(struct dw_dp *priv, const u8 *buffer, size_t size)
{
	size_t i, j;

	for (i = 0; i < DIV_ROUND_UP(size, 4); i++) {
		size_t num = min_t(size_t, size - i * 4, 4);
		u32 value = 0;

		for (j = 0; j < num; j++)
			value |= buffer[i * 4 + j] << (j * 8);

		DP_WRITE(priv, DPTX_AUX_DATA0 + i * 4, value);
	}

	return size;
}

static int dp_aux_cmd_exec(struct dw_dp *priv, u32 aux_cmd, u32 *aux_reply)
{
	u32 status;
	int ret;

	/* Send AUX command */
	DP_WRITE(priv, DPTX_AUX_CMD, aux_cmd);

	/* Wait for AUX reply interrupt */
	ret = readl_poll_timeout(priv->dp + DPTX_GENERAL_INTERRUPT,
				 status,
				 status & AUX_REPLY_EVENT,
				 200000);
	if (ret) {
		printf("timeout waiting for AUX reply\n");
		return -ETIMEDOUT;
	}

	/* Clear AUX reply interrupt */
	DP_WRITE(priv, DPTX_GENERAL_INTERRUPT, AUX_REPLY_EVENT);

	if (aux_reply) {
		*aux_reply = DP_READ(priv, AUX_STATUS);

		/* Wait until AUX engine becomes idle */
		ret = readl_poll_timeout(priv->dp + AUX_STATUS,
					 *aux_reply,
					 ((*aux_reply >> 16) & 0x1) == 0,
					 200000);
		if (ret) {
			printf("timeout waiting AUX idle\n");
			return -ETIMEDOUT;
		}
	}

	return 0;
}

static ssize_t dw_dp_aux_transfer(struct dw_dp *priv,
				  struct drm_dp_aux_msg *msg)
{
	u32 value;
	ssize_t ret = 0;

	switch (msg->request) {
	case DP_AUX_NATIVE_WRITE:
		ret = dw_dp_aux_write_data(priv, msg->buffer, msg->size);
		if (ret < 0)
			return ret;
		break;
	case DP_AUX_NATIVE_READ:
		break;
	default:
		return -EINVAL;
	}

	if (msg->size > 0)
		value = FIELD_PREP(AUX_LEN_REQ, msg->size - 1);

	value |= FIELD_PREP(AUX_CMD_TYPE, msg->request);
	value |= FIELD_PREP(AUX_ADDR, msg->address);

	dp_aux_cmd_exec(priv, value, &value);
	/* Read AUX reply status */
	value = DP_READ(priv, AUX_STATUS);
	msg->reply = FIELD_GET(AUX_STATUS, value);

	if (msg->size > 0 && msg->reply == DP_AUX_NATIVE_REPLY_ACK) {
		if (msg->request & DP_AUX_NATIVE_READ) {
			ret = dw_dp_aux_read_data(priv, msg->buffer, msg->size);
			if (ret < 0)
				return ret;
		}
	}

	return ret;
}

static int drm_dp_dpcd_access(struct dw_dp *priv, u8 request,
			      unsigned int offset, void *buffer, size_t size)
{
	struct drm_dp_aux_msg msg;
	unsigned int retry, native_reply;
	int err = 0, ret = 0;

	memset(&msg, 0, sizeof(msg));
	msg.address = offset;
	msg.request = request;
	msg.buffer = buffer;
	msg.size = size;

	/*
	 * The specification doesn't give any recommendation on how often to
	 * retry native transactions. We used to retry 7 times like for
	 * aux i2c transactions but real world devices this wasn't
	 * sufficient, bump to 32 which makes Dell 4k monitors happier.
	 */
	for (retry = 0; retry < 32; retry++) {
		if (ret != 0 && ret != -ETIMEDOUT)
			udelay(500);

		ret = dw_dp_aux_transfer(priv, &msg);
		if (ret >= 0) {
			native_reply = msg.reply & DP_AUX_NATIVE_REPLY_MASK;
			if (native_reply == DP_AUX_NATIVE_REPLY_ACK) {
				if (ret == size)
					goto out;

				ret = -EPROTO;
			} else {
				ret = -EIO;
			}
		}

		/*
		 * We want the error we return to be the error we received on
		 * the first transaction, since we may get a different error the
		 * next time we retry
		 */
		if (!err)
			err = ret;
	}

	printf("Aux too many retries, giving up. First error: %d\n", err);
	ret = err;

out:
	return ret;
}

static ssize_t drm_dp_dpcd_read(struct dw_dp *priv, unsigned int offset,
				void *buffer, size_t size)
{
	int ret;

	ret = drm_dp_dpcd_access(priv, DP_AUX_NATIVE_READ, DP_DPCD_REV,
				 buffer, 1);
	if (ret != 1)
		goto out;

	ret = drm_dp_dpcd_access(priv, DP_AUX_NATIVE_READ, offset,
				 buffer, size);

out:
	return ret;
}

static inline ssize_t drm_dp_dpcd_readb(struct dw_dp *priv,
					unsigned int offset, u8 *valuep)
{
	return drm_dp_dpcd_read(priv, offset, valuep, 1);
}

static ssize_t drm_dp_dpcd_write(struct dw_dp *priv, unsigned int offset,
				 void *buffer, size_t size)
{
	int ret;

	ret = drm_dp_dpcd_access(priv, DP_AUX_NATIVE_WRITE, offset,
				 buffer, size);

	return ret;
}

static inline ssize_t drm_dp_dpcd_writeb(struct dw_dp *priv,
					 unsigned int offset, u8 value)
{
	return drm_dp_dpcd_write(priv, offset, &value, 1);
}

static inline void dw_dp_update_bits(struct dw_dp *priv, u32 reg, u32 mask, u32 val)
{
	u32 tmp = DP_READ(priv, reg);

	tmp = (tmp & ~mask) | (val & mask);
	DP_WRITE(priv, reg, tmp);
}

static int dw_dp_read_edid(struct udevice *dev, u8 *buf, int buf_size)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct connector_state *conn_state = &priv->conn_state;

	if (buf_size > EDID_SIZE)
		buf_size = EDID_SIZE;

	dp_edid_read(priv, conn_state->edid, EDID_SIZE);
	memcpy(buf, conn_state->edid, buf_size);

	return buf_size;
}

static void dw_dp_hpd_init(struct dw_dp *priv)
{
	/* Enable all HPD interrupts */
	dw_dp_update_bits(priv, DPTX_HPD_INTERRUPT_ENABLE,
			  HPD_UNPLUG_EN | HPD_PLUG_EN | HPD_IRQ_EN,
			  FIELD_PREP(HPD_UNPLUG_EN, 1) |
			  FIELD_PREP(HPD_PLUG_EN, 1) |
			  FIELD_PREP(HPD_IRQ_EN, 1));

	/* Enable all top-level interrupts */
	dw_dp_update_bits(priv, DPTX_GENERAL_INTERRUPT_ENABLE,
			  HPD_EVENT_EN, FIELD_PREP(HPD_EVENT_EN, 1));
}

static void dw_dp_aux_init(struct dw_dp *priv)
{
	dw_dp_update_bits(priv, DPTX_SOFT_RESET_CTRL, AUX_RESET,
			  FIELD_PREP(AUX_RESET, 1));
	udelay(10);
	dw_dp_update_bits(priv, DPTX_SOFT_RESET_CTRL, AUX_RESET,
			  FIELD_PREP(AUX_RESET, 0));

	dw_dp_update_bits(priv, DPTX_GENERAL_INTERRUPT_ENABLE,
			  AUX_REPLY_EVENT_EN,
			  FIELD_PREP(AUX_REPLY_EVENT_EN, 1));
}

static void dw_dp_init(struct dw_dp *priv)
{
	dw_dp_update_bits(priv, DPTX_SOFT_RESET_CTRL, CONTROLLER_RESET,
			  FIELD_PREP(CONTROLLER_RESET, 1));
	udelay(10);
	dw_dp_update_bits(priv, DPTX_SOFT_RESET_CTRL, CONTROLLER_RESET,
			  FIELD_PREP(CONTROLLER_RESET, 0));

	dw_dp_update_bits(priv, DPTX_SOFT_RESET_CTRL, PHY_SOFT_RESET,
			  FIELD_PREP(PHY_SOFT_RESET, 1));
	udelay(10);
	dw_dp_update_bits(priv, DPTX_SOFT_RESET_CTRL, PHY_SOFT_RESET,
			  FIELD_PREP(PHY_SOFT_RESET, 0));

	/* Disable default fast treaining */
	dw_dp_update_bits(priv, DPTX_CCTL, DEFAULT_FAST_LINK_TRAIN_EN,
			  FIELD_PREP(DEFAULT_FAST_LINK_TRAIN_EN, 0));

	dw_dp_hpd_init(priv);
	dw_dp_aux_init(priv);
}

static void dw_dp_connector_init(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);

	reset_assert_bulk(&priv->resets);
	udelay(20);
	reset_deassert_bulk(&priv->resets);

	dw_dp_init(priv);

	/* Config RGB888 color depth */
	DC_SYSCON_WRITE(priv, DC_SYSCON_SYSREG_COLOR, 0xa0);
	/* AUX Power ON */
	DC_SYSCON_WRITE(priv, DC_SYSCON_SYSREG_AUX_PWR, 0x01);

	/* PHY Initialization */
	VOUT_SYSCON_WRITE(priv, VOUT_SYSCON_CRG_PHY_CTRL, 0x00000c00);
	mdelay(100);
	VOUT_SYSCON_WRITE(priv, VOUT_SYSCON_CRG_PHY_CTRL, 0x00000800);
	VOUT_SYSCON_WRITE(priv, VOUT_SYSCON_CRG_PHY_CTRL, 0x00000000);

	DC_SYSCON_WRITE(priv, DC_SYSCON_SYSREG_CTRL, 0x00020004);
}

static int dw_dp_link_power_up(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct dw_dp_link *link = &priv->link;
	u8 value;
	int ret;

	if (link->revision < 0x11)
		return 0;

	ret = drm_dp_dpcd_readb(priv, DP_SET_POWER, &value);
	if (ret < 0)
		return ret;

	value &= ~DP_SET_POWER_MASK;
	value |= DP_SET_POWER_D0;

	ret = drm_dp_dpcd_writeb(priv, DP_SET_POWER, value);
	if (ret < 0)
		return ret;

	/* Give some time for link power up */
	udelay(1000);

	return 0;
}

static void dw_dp_link_train_init(struct drm_dp_link_train *train)
{
	struct drm_dp_link_train_set *request = &train->request;
	struct drm_dp_link_train_set *adjust = &train->adjust;
	unsigned int i;

	for (i = 0; i < 4; i++) {
		request->voltage_swing[i] = 0;
		adjust->voltage_swing[i] = 0;

		request->pre_emphasis[i] = 0;
		adjust->pre_emphasis[i] = 0;
	}

	train->clock_recovered = false;
	train->channel_equalized = false;
}

static void dw_dp_phy_xmit_enable(struct dw_dp *priv, u32 lanes)
{
	u32 xmit_enable;

	switch (lanes) {
	case 4:
	case 2:
	case 1:
		xmit_enable = GENMASK(lanes - 1, 0);
		break;
	case 0:
	default:
		xmit_enable = 0;
		break;
	}

	dw_dp_update_bits(priv, DPTX_PHYIF_CTRL, XMIT_ENABLE,
			  FIELD_PREP(XMIT_ENABLE, xmit_enable));
}

static u8 drm_dp_link_rate_to_bw_code(int link_rate)
{
	/* Spec says link_bw = link_rate / 0.27Gbps */
	return link_rate / 27000;
}

static int dw_dp_link_configure(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct dw_dp_link *link = &priv->link;
	u8 buf[2];
	int ret, phy_rate;
	u32 reg;

	dw_dp_update_bits(priv, DPTX_PHYIF_CTRL, PHY_LANES,
			  FIELD_PREP(PHY_LANES, link->lanes / 2));

	switch (link->rate) {
	case 810000:
		phy_rate = DPTX_PHYRATE_HBR3;
		break;
	case 540000:
		phy_rate = DPTX_PHYRATE_HBR2;
		break;
	case 270000:
		phy_rate = DPTX_PHYRATE_HBR;
		break;
	case 162000:
	default:
		phy_rate = DPTX_PHYRATE_RBR;
		break;
	}
	dw_dp_update_bits(priv, DPTX_PHYIF_CTRL, PHY_RATE,
			  FIELD_PREP(PHY_RATE, phy_rate));

	reg = FIELD_PREP(POWER_DOWN_CTRL_LANE2_3, 3) |
		FIELD_PREP(POWER_DOWN_CTRL_LANE1, 3) |
		PER_LANE_PWRDOWN_CTRL_EN;
	DP_WRITE(priv, DPTX_PHYIF_PWRDOWN_CTRL, reg);

	do {
		mdelay(2);
		ret = DP_READ(priv, DPTX_PHYIF_CTRL);
	} while ((ret & (3 << 12)) != 0);

	dw_dp_phy_xmit_enable(priv, link->lanes);

	buf[0] = drm_dp_link_rate_to_bw_code(link->rate);
	buf[1] = link->lanes;

	if (link->caps.enhanced_framing) {
		buf[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
		dw_dp_update_bits(priv, DPTX_CCTL, ENHANCE_FRAMING_EN,
				  FIELD_PREP(ENHANCE_FRAMING_EN, 1));
	} else {
		dw_dp_update_bits(priv, DPTX_CCTL, ENHANCE_FRAMING_EN,
				  FIELD_PREP(ENHANCE_FRAMING_EN, 0));
	}

	ret = drm_dp_dpcd_write(priv, DP_LINK_BW_SET, buf, sizeof(buf));
	if (ret < 0)
		return ret;

	buf[0] = link->caps.ssc ? DP_SPREAD_AMP_0_5 : 0;
	buf[1] = link->caps.channel_coding ? DP_SET_ANSI_8B10B : 0;

	ret = drm_dp_dpcd_write(priv, DP_DOWNSPREAD_CTRL, buf,
				sizeof(buf));
	if (ret < 0)
		return ret;

	return 0;
}

static void dw_dp_phy_set_pattern(struct dw_dp *priv, u32 pattern)
{
	dw_dp_update_bits(priv, DPTX_PHYIF_CTRL, TPS_SEL,
			  FIELD_PREP(TPS_SEL, pattern));
}

static int dw_dp_link_train_set_pattern(struct dw_dp *priv, u32 pattern)
{
	u8 buf = 0;
	int ret;

	switch (pattern) {
	case DP_TRAINING_PATTERN_DISABLE:
		dw_dp_phy_set_pattern(priv, DPTX_PHY_PATTERN_NONE);
		break;
	case DP_TRAINING_PATTERN_1:
		dw_dp_phy_set_pattern(priv, DPTX_PHY_PATTERN_TPS_1);
		break;
	case DP_TRAINING_PATTERN_2:
		dw_dp_phy_set_pattern(priv, DPTX_PHY_PATTERN_TPS_2);
		break;
	case DP_TRAINING_PATTERN_3:
		dw_dp_phy_set_pattern(priv, DPTX_PHY_PATTERN_TPS_3);
		break;
	case DP_TRAINING_PATTERN_4:
		dw_dp_phy_set_pattern(priv, DPTX_PHY_PATTERN_TPS_4);
		break;
	default:
		return -EINVAL;
	}

	ret = drm_dp_dpcd_writeb(priv, DP_TRAINING_PATTERN_SET,
				 buf | pattern);
	if (ret < 0)
		return ret;

	return 0;
}

static int drm_dp_dpcd_read_link_status(struct dw_dp *priv,
					u8 status[DP_LINK_STATUS_SIZE])
{
	return drm_dp_dpcd_read(priv, DP_LANE0_1_STATUS, status,
				DP_LINK_STATUS_SIZE);
}

static u8 dp_link_status(const u8 link_status[DP_LINK_STATUS_SIZE], int r)
{
	return link_status[r - DP_LANE0_1_STATUS];
}

static u8 dp_get_lane_status(const u8 link_status[DP_LINK_STATUS_SIZE],
			     int lane)
{
	int i = DP_LANE0_1_STATUS + (lane >> 1);
	int s = (lane & 1) * 4;
	u8 l = dp_link_status(link_status, i);

	return (l >> s) & 0xf;
}

static bool drm_dp_clock_recovery_ok(const u8 link_status[DP_LINK_STATUS_SIZE],
				     int lane_count)
{
	int lane;
	u8 lane_status;

	for (lane = 0; lane < lane_count; lane++) {
		lane_status = dp_get_lane_status(link_status, lane);
		if ((lane_status & DP_LANE_CR_DONE) == 0)
			return false;
	}
	return true;
}

static u8
drm_dp_get_adjust_request_voltage(const u8 link_status[DP_LINK_STATUS_SIZE],
				  int lane)
{
	int i = DP_ADJUST_REQUEST_LANE0_1 + (lane >> 1);
	int s = ((lane & 1) ?
		 DP_ADJUST_VOLTAGE_SWING_LANE1_SHIFT :
		 DP_ADJUST_VOLTAGE_SWING_LANE0_SHIFT);
	u8 l = dp_link_status(link_status, i);

	return ((l >> s) & 0x3) << DP_TRAIN_VOLTAGE_SWING_SHIFT;
}

static u8
drm_dp_get_adjust_request_pre_emphasis(const u8 link_status[DP_LINK_STATUS_SIZE],
				       int lane)
{
	int i = DP_ADJUST_REQUEST_LANE0_1 + (lane >> 1);
	int s = ((lane & 1) ?
		 DP_ADJUST_PRE_EMPHASIS_LANE1_SHIFT :
		 DP_ADJUST_PRE_EMPHASIS_LANE0_SHIFT);
	u8 l = dp_link_status(link_status, i);

	return ((l >> s) & 0x3) << DP_TRAIN_PRE_EMPHASIS_SHIFT;
}

static void dw_dp_link_get_adjustments(struct dw_dp_link *link,
				       u8 status[DP_LINK_STATUS_SIZE])
{
	struct drm_dp_link_train_set *adjust = &link->train.adjust;
	unsigned int i;

	for (i = 0; i < link->lanes; i++) {
		adjust->voltage_swing[i] =
			drm_dp_get_adjust_request_voltage(status, i) >>
				DP_TRAIN_VOLTAGE_SWING_SHIFT;

		adjust->pre_emphasis[i] =
			drm_dp_get_adjust_request_pre_emphasis(status, i) >>
				DP_TRAIN_PRE_EMPHASIS_SHIFT;
	}
}

static void dw_dp_link_train_adjust(struct drm_dp_link_train *train)
{
	struct drm_dp_link_train_set *request = &train->request;
	struct drm_dp_link_train_set *adjust = &train->adjust;
	unsigned int i;

	for (i = 0; i < 4; i++)
		request->voltage_swing[i] = adjust->voltage_swing[i];

	for (i = 0; i < 4; i++)
		request->pre_emphasis[i] = adjust->pre_emphasis[i];
}

static int dw_dp_link_train_update_vs_emph(struct dw_dp *priv)
{
	struct dw_dp_link *link = &priv->link;
	struct drm_dp_link_train_set *request = &link->train.request;
	unsigned int lanes = link->lanes, *vs, *pe;
	u8 buf[4];
	int i, ret;

	vs = request->voltage_swing;
	pe = request->pre_emphasis;

	for (i = 0; i < lanes; i++)
		buf[i] = (vs[i] << DP_TRAIN_VOLTAGE_SWING_SHIFT) |
			 (pe[i] << DP_TRAIN_PRE_EMPHASIS_SHIFT);
	ret = drm_dp_dpcd_write(priv, DP_TRAINING_LANE0_SET, buf, lanes);
	if (ret < 0)
		return ret;

	return 0;
}

static void drm_dp_link_train_clock_recovery_delay(const u8 *dpcd)
{
	int rd_interval = dpcd[DP_TRAINING_AUX_RD_INTERVAL] &
			  DP_TRAINING_AUX_RD_MASK;

	if (rd_interval > 4)
		printf("AUX interval %d, out of range (max 4)\n", rd_interval);

	if (rd_interval == 0 || dpcd[DP_DPCD_REV] >= DP_DPCD_REV_14)
		udelay(100);
	else
		mdelay(rd_interval * 4);
}

static int dw_dp_link_clock_recovery(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct dw_dp_link *link = &priv->link;
	u8 status[DP_LINK_STATUS_SIZE];
	unsigned int tries = 0;
	int ret;

	ret = dw_dp_link_train_set_pattern(priv, DP_TRAINING_PATTERN_1);
	if (ret)
		return ret;

	for (;;) {
		ret = dw_dp_link_train_update_vs_emph(priv);
		if (ret)
			return ret;
		drm_dp_link_train_clock_recovery_delay(link->dpcd);

		ret = drm_dp_dpcd_read_link_status(priv, status);
		if (ret < 0) {
			dev_err(dev, "failed to read link status: %d\n",
				ret);
			return ret;
		}

		if (drm_dp_clock_recovery_ok(status, link->lanes)) {
			link->train.clock_recovered = true;
			break;
		}

		dw_dp_link_get_adjustments(link, status);

		if (link->train.request.voltage_swing[0] ==
		    link->train.adjust.voltage_swing[0])
			tries++;
		else
			tries = 0;

		if (tries == 5)
			break;

		dw_dp_link_train_adjust(&link->train);
	}

	return 0;
}

static bool dw_dp_bandwidth_ok(const struct drm_display_mode *mode, u32 bpp,
			       unsigned int lanes, unsigned int rate)
{
	u32 max_bw, req_bw;

	req_bw = mode->clock * bpp / 8;
	max_bw = lanes * rate;
	if (req_bw > max_bw)
		return false;

	return true;
}

static int dw_dp_link_downgrade(struct dw_dp *priv)
{
	struct dw_dp_link *link = &priv->link;
	struct dw_dp_video *video = &priv->video;

	switch (link->rate) {
	case 162000:
		return -EINVAL;
	case 270000:
		link->rate = 162000;
		break;
	case 540000:
		link->rate = 270000;
		break;
	case 810000:
		link->rate = 540000;
		break;
	}

	if (!dw_dp_bandwidth_ok(&video->mode, video->bpp, link->lanes,
				link->rate))
		return -E2BIG;

	return 0;
}

static bool
drm_dp_channel_eq_ok(const u8 link_status[DP_LINK_STATUS_SIZE], int lane_count)
{
	u8 lane_align;
	u8 lane_status;
	int lane;

	lane_align = dp_link_status(link_status,
				    DP_LANE_ALIGN_STATUS_UPDATED);
	if ((lane_align & DP_INTERLANE_ALIGN_DONE) == 0)
		return false;
	for (lane = 0; lane < lane_count; lane++) {
		lane_status = dp_get_lane_status(link_status, lane);
		if ((lane_status & DP_CHANNEL_EQ_BITS) != DP_CHANNEL_EQ_BITS)
			return false;
	}
	return true;
}

static void drm_dp_link_train_channel_eq_delay(const u8 *dpcd)
{
	int rd_interval = dpcd[DP_TRAINING_AUX_RD_INTERVAL] &
			  DP_TRAINING_AUX_RD_MASK;

	if (rd_interval > 4)
		printf("AUX interval %d, out of range (max 4)\n", rd_interval);

	if (rd_interval == 0)
		udelay(400);
	else
		mdelay(rd_interval * 4);
}

static int dw_dp_link_channel_equalization(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct dw_dp_link *link = &priv->link;
	u8 status[DP_LINK_STATUS_SIZE], pattern;
	unsigned int tries;
	int ret;

	if (link->caps.tps4_supported)
		pattern = DP_TRAINING_PATTERN_4;
	else if (link->caps.tps3_supported)
		pattern = DP_TRAINING_PATTERN_3;
	else
		pattern = DP_TRAINING_PATTERN_2;
	ret = dw_dp_link_train_set_pattern(priv, pattern);
	if (ret)
		return ret;

	for (tries = 1; tries < 5; tries++) {
		ret = dw_dp_link_train_update_vs_emph(priv);
		if (ret)
			return ret;

		drm_dp_link_train_channel_eq_delay(link->dpcd);

		ret = drm_dp_dpcd_read_link_status(priv, status);
		if (ret < 0)
			return ret;

		if (!drm_dp_clock_recovery_ok(status, link->lanes)) {
			dev_err(dev, "clock recovery lost while eq\n");
			link->train.clock_recovered = false;
			break;
		}

		if (drm_dp_channel_eq_ok(status, link->lanes)) {
			link->train.channel_equalized = true;
			break;
		}

		dw_dp_link_get_adjustments(link, status);
		dw_dp_link_train_adjust(&link->train);
	}

	return 0;
}

static int dw_dp_link_train(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct dw_dp_link *link = &priv->link;
	int ret;

retry:
	dw_dp_link_train_init(&link->train);

	printf("Training link: %u lane%s at %u MHz\n",
	       link->lanes, (link->lanes > 1) ? "s" : "", link->rate / 100);

	ret = dw_dp_link_configure(dev);

	if (ret < 0) {
		dev_err(dev, "Failed to configure DP link: %d\n", ret);
		return ret;
	}

	ret = dw_dp_link_clock_recovery(dev);
	if (ret < 0) {
		dev_err(dev, "Clock recovery failed: %d\n", ret);
		goto out;
	}

	if (!link->train.clock_recovered) {
		dev_err(dev, "Clock recovery failed, downgrading link\n");

		ret = dw_dp_link_downgrade(priv);
		if (ret < 0)
			goto out;
		else
			goto retry;
	}

	printf("Clock recovery succeeded\n");

	ret = dw_dp_link_channel_equalization(dev);
	if (ret < 0) {
		dev_err(dev, "Channel equalization failed: %d\n", ret);
		goto out;
	}

	if (!link->train.channel_equalized) {
		dev_err(dev,
			"Channel equalization failed, downgrading link\n");

		ret = dw_dp_link_downgrade(priv);
		if (ret < 0)
			goto out;
		else
			goto retry;
	}

	printf("Channel equalization succeeded\n");

out:
	dw_dp_link_train_set_pattern(priv, DP_TRAINING_PATTERN_DISABLE);
	return ret;
}

static int dw_dp_link_enable(struct udevice *dev)
{
	int ret;

	ret = dw_dp_link_power_up(dev);
	if (ret < 0)
		return ret;

	ret = dw_dp_link_train(dev);
	if (ret < 0) {
		dev_err(dev, "link training failed: %d\n", ret);
		return ret;
	}

	return 0;
}

static int dw_dp_video_set_pixel_mode(struct dw_dp *priv, u8 pixel_mode)
{
	switch (pixel_mode) {
	case DPTX_MP_SINGLE_PIXEL:
	case DPTX_MP_DUAL_PIXEL:
	case DPTX_MP_QUAD_PIXEL:
		break;
	default:
		return -EINVAL;
	}

	dw_dp_update_bits(priv, DPTX_VSAMPLE_CTRL, PIXEL_MODE_SELECT,
			  FIELD_PREP(PIXEL_MODE_SELECT, pixel_mode));
	return 0;
}

static int dw_dp_video_set_msa(struct dw_dp *priv, u8 color_format, u8 bpc,
			       u16 vstart, u16 hstart)
{
	struct dw_dp_link *link = &priv->link;
	u16 misc = 0;

	if (link->vsc_sdp_extension_for_colorimetry_supported)
		misc |= DP_MSA_MISC_COLOR_VSC_SDP;

	switch (color_format) {
	case DRM_COLOR_FORMAT_RGB444:
		misc |= DP_MSA_MISC_COLOR_RGB;
		break;
	case DRM_COLOR_FORMAT_YCRCB444:
		misc |= DP_MSA_MISC_COLOR_YCBCR_444_BT709;
		break;
	case DRM_COLOR_FORMAT_YCRCB422:
		misc |= DP_MSA_MISC_COLOR_YCBCR_422_BT709;
		break;
	case DRM_COLOR_FORMAT_YCRCB420:
		break;
	default:
		return -EINVAL;
	}

	switch (bpc) {
	case 6:
		misc |= DP_MSA_MISC_6_BPC;
		break;
	case 8:
		misc |= DP_MSA_MISC_8_BPC;
		break;
	case 10:
		misc |= DP_MSA_MISC_10_BPC;
		break;
	case 12:
		misc |= DP_MSA_MISC_12_BPC;
		break;
	case 16:
		misc |= DP_MSA_MISC_16_BPC;
		break;
	default:
		return -EINVAL;
	}

	DP_WRITE(priv, DPTX_VIDEO_MSA1,
		 FIELD_PREP(VSTART, vstart) | FIELD_PREP(HSTART, hstart));
	DP_WRITE(priv, DPTX_VIDEO_MSA2, FIELD_PREP(MISC0, misc));
	DP_WRITE(priv, DPTX_VIDEO_MSA3, FIELD_PREP(MISC1, misc >> 8));

	return 0;
}

static bool drm_dp_channel_coding_supported(const u8 *dpcd)
{
	return dpcd[DP_MAIN_LINK_CHANNEL_CODING] & DP_CAP_ANSI_8B10B;
}

static void dw_dp_vsc_sdp_pack(const struct drm_dp_vsc_sdp *vsc,
			       struct dw_dp_sdp *sdp)
{
	sdp->header.HB0 = 0;
	sdp->header.HB1 = DP_SDP_VSC;
	sdp->header.HB2 = vsc->revision;
	sdp->header.HB3 = vsc->length;

	sdp->db[16] = (vsc->pixelformat & 0xf) << 4;
	sdp->db[16] |= vsc->colorimetry & 0xf;

	switch (vsc->bpc) {
	case 8:
		sdp->db[17] = 0x1;
		break;
	case 10:
		sdp->db[17] = 0x2;
		break;
	case 12:
		sdp->db[17] = 0x3;
		break;
	case 16:
		sdp->db[17] = 0x4;
		break;
	case 6:
	default:
		break;
	}

	if (vsc->dynamic_range == DP_DYNAMIC_RANGE_CTA)
		sdp->db[17] |= 0x80;

	sdp->db[18] = vsc->content_type & 0x7;

	sdp->flags |= DPTX_SDP_VERTICAL_INTERVAL;
}

static int dw_dp_send_sdp(struct dw_dp *priv, struct dw_dp_sdp *sdp)
{
	const u8 *payload = sdp->db;
	u32 reg;
	int i, nr = 0;

	reg = DPTX_SDP_REGISTER_BANK + nr * 9 * 4;

	/* SDP header */
	DP_WRITE(priv, reg, get_unaligned_le32(&sdp->header));

	/* SDP data payload */
	for (i = 1; i < 9; i++, payload += 4)
		DP_WRITE(priv, reg + i * 4,
			 FIELD_PREP(SDP_REGS, get_unaligned_le32(payload)));

	if (sdp->flags & DPTX_SDP_VERTICAL_INTERVAL)
		dw_dp_update_bits(priv, DPTX_SDP_VERTICAL_CTRL,
				  EN_VERTICAL_SDP << nr,
				    EN_VERTICAL_SDP << nr);

	if (sdp->flags & DPTX_SDP_HORIZONTAL_INTERVAL)
		dw_dp_update_bits(priv, DPTX_SDP_HORIZONTAL_CTRL,
				  EN_HORIZONTAL_SDP << nr,
				    EN_HORIZONTAL_SDP << nr);

	return 0;
}

static int dw_dp_send_vsc_sdp(struct dw_dp *priv)
{
	struct dw_dp_video *video = &priv->video;
	struct drm_dp_vsc_sdp vsc = {};
	struct dw_dp_sdp sdp = {};

	vsc.revision = 0x5;
	vsc.length = 0x13;

	switch (video->color_format) {
	case DRM_COLOR_FORMAT_YCRCB444:
		vsc.pixelformat = DP_PIXELFORMAT_YUV444;
		break;
	case DRM_COLOR_FORMAT_YCRCB420:
		vsc.pixelformat = DP_PIXELFORMAT_YUV420;
		break;
	case DRM_COLOR_FORMAT_YCRCB422:
		vsc.pixelformat = DP_PIXELFORMAT_YUV422;
		break;
	case DRM_COLOR_FORMAT_RGB444:
	default:
		vsc.pixelformat = DP_PIXELFORMAT_RGB;
		break;
	}

	if (video->color_format == DRM_COLOR_FORMAT_RGB444)
		vsc.colorimetry = DP_COLORIMETRY_DEFAULT;
	else
		vsc.colorimetry = DP_COLORIMETRY_BT709_YCC;

	vsc.bpc = video->bpc;
	vsc.dynamic_range = DP_DYNAMIC_RANGE_CTA;
	vsc.content_type = DP_CONTENT_TYPE_NOT_DEFINED;

	dw_dp_vsc_sdp_pack(&vsc, &sdp);

	return dw_dp_send_sdp(priv, &sdp);
}

static int dw_dp_video_enable(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct dw_dp_video *video = &priv->video;
	struct dw_dp_link *link = &priv->link;
	struct drm_display_mode *mode = &video->mode;
	u8 color_format = video->color_format;
	u8 bpc = video->bpc;
	u8 pixel_mode = video->pixel_mode;
	u8 bpp = video->bpp, init_threshold;
	u32 hactive, hblank, h_sync_width, h_front_porch;
	u32 vactive, vblank, v_sync_width, v_front_porch;
	u32 vstart = mode->vtotal - mode->vsync_start;
	u32 hstart = mode->htotal - mode->hsync_start;
	u32 peak_stream_bandwidth, link_bandwidth;
	u32 average_bytes_per_tu, average_bytes_per_tu_frac;
	u32 ts, hblank_interval;
	u32 value;
	int ret;

	ret = dw_dp_video_set_pixel_mode(priv, pixel_mode);
	if (ret)
		return ret;

	ret = dw_dp_video_set_msa(priv, color_format, bpc, vstart, hstart);
	if (ret)
		return ret;

	dw_dp_update_bits(priv, DPTX_VSAMPLE_CTRL, VIDEO_MAPPING,
			  FIELD_PREP(VIDEO_MAPPING, video->video_mapping));

	/* Configure DPTX_VINPUT_POLARITY_CTRL register */
	value = 0;
	if (mode->flags & DRM_MODE_FLAG_PHSYNC)
		value |= FIELD_PREP(HSYNC_IN_POLARITY, 1);
	if (mode->flags & DRM_MODE_FLAG_PVSYNC)
		value |= FIELD_PREP(VSYNC_IN_POLARITY, 1);
	DP_WRITE(priv, DPTX_VINPUT_POLARITY_CTRL, value);

	/* Configure DPTX_VIDEO_CONFIG1 register */
	hactive = mode->hdisplay;
	hblank = mode->htotal - mode->hdisplay;
	value = FIELD_PREP(HACTIVE, hactive) | FIELD_PREP(HBLANK, hblank);
	if (mode->flags & DRM_MODE_FLAG_INTERLACE)
		value |= FIELD_PREP(I_P, 1);
	DP_WRITE(priv, DPTX_VIDEO_CONFIG1, value);

	/* Configure DPTX_VIDEO_CONFIG2 register */
	vblank = mode->vtotal - mode->vdisplay;
	vactive = mode->vdisplay;
	DP_WRITE(priv, DPTX_VIDEO_CONFIG2,
		 FIELD_PREP(VBLANK, vblank) | FIELD_PREP(VACTIVE, vactive));

	/* Configure DPTX_VIDEO_CONFIG3 register */
	h_sync_width = mode->hsync_end - mode->hsync_start;
	h_front_porch = mode->hsync_start - mode->hdisplay;
	DP_WRITE(priv, DPTX_VIDEO_CONFIG3,
		 FIELD_PREP(H_SYNC_WIDTH, h_sync_width) |
		      FIELD_PREP(H_FRONT_PORCH, h_front_porch));

	/* Configure DPTX_VIDEO_CONFIG4 register */
	v_sync_width = mode->vsync_end - mode->vsync_start;
	v_front_porch = mode->vsync_start - mode->vdisplay;
	DP_WRITE(priv, DPTX_VIDEO_CONFIG4,
		 FIELD_PREP(V_SYNC_WIDTH, v_sync_width) |
		      FIELD_PREP(V_FRONT_PORCH, v_front_porch));

	peak_stream_bandwidth = mode->clock * bpp / 8;
	link_bandwidth = (link->rate / 1000) * link->lanes;
	ts = peak_stream_bandwidth * 64 / link_bandwidth;
	average_bytes_per_tu = ts / 1000;
	average_bytes_per_tu_frac = ts / 100 - average_bytes_per_tu * 10;
	if (pixel_mode == DPTX_MP_SINGLE_PIXEL) {
		if (average_bytes_per_tu < 6)
			init_threshold = 32;
		else if (hblank <= 80 &&
			 color_format != DRM_COLOR_FORMAT_YCRCB420)
			init_threshold = 12;
		else if (hblank <= 40 &&
			 color_format == DRM_COLOR_FORMAT_YCRCB420)
			init_threshold = 3;
		else
			init_threshold = 16;
	} else {
		u32 t1 = 0, t2 = 0, t3 = 0;

		switch (bpc) {
		case 6:
			t1 = (4 * 1000 / 9) * link->lanes;
			break;
		case 8:
			if (color_format == DRM_COLOR_FORMAT_YCRCB422) {
				t1 = (1000 / 2) * link->lanes;
			} else {
				if (pixel_mode == DPTX_MP_DUAL_PIXEL)
					t1 = (1000 / 3) * link->lanes;
				else
					t1 = (3000 / 16) * link->lanes;
			}
			break;
		case 10:
			if (color_format == DRM_COLOR_FORMAT_YCRCB422)
				t1 = (2000 / 5) * link->lanes;
			else
				t1 = (4000 / 15) * link->lanes;
			break;
		case 12:
			if (color_format == DRM_COLOR_FORMAT_YCRCB422) {
				if (pixel_mode == DPTX_MP_DUAL_PIXEL)
					t1 = (1000 / 6) * link->lanes;
				else
					t1 = (1000 / 3) * link->lanes;
			} else {
				t1 = (2000 / 9) * link->lanes;
			}
			break;
		case 16:
			if (color_format != DRM_COLOR_FORMAT_YCRCB422 &&
			    pixel_mode == DPTX_MP_DUAL_PIXEL)
				t1 = (1000 / 6) * link->lanes;
			else
				t1 = (1000 / 4) * link->lanes;
			break;
		default:
			return -EINVAL;
		}

		if (color_format == DRM_COLOR_FORMAT_YCRCB420)
			t2 = (link->rate / 4) * 1000 / (mode->clock / 2);
		else
			t2 = (link->rate / 4) * 1000 / mode->clock;

		if (average_bytes_per_tu_frac)
			t3 = average_bytes_per_tu + 1;
		else
			t3 = average_bytes_per_tu;
		init_threshold = t1 * t2 * t3 / (1000 * 1000);
		if (init_threshold <= 16 || average_bytes_per_tu < 10)
			init_threshold = 40;
	}

	debug("DP TU calc: init_threshold=%d avg_bytes_per_tu=%d.%02u lanes=%u rate=%uMHz pclk=%ukHz fmt=%s\n",
	      init_threshold,
	      average_bytes_per_tu,
	      average_bytes_per_tu_frac,
	      link->lanes,
	      link->rate / 1000,
	      mode->clock,
	      color_format == DRM_COLOR_FORMAT_YCRCB420 ? "YCbCr420" : "RGB/YUV444");

	DP_WRITE(priv, DPTX_VIDEO_CONFIG5,
		 FIELD_PREP(INIT_THRESHOLD_HI, init_threshold >> 6) |
		      FIELD_PREP(AVERAGE_BYTES_PER_TU_FRAC,
				 average_bytes_per_tu_frac) |
		      FIELD_PREP(INIT_THRESHOLD, init_threshold) |
		      FIELD_PREP(AVERAGE_BYTES_PER_TU, average_bytes_per_tu));

	/* Configure DPTX_VIDEO_HBLANK_INTERVAL register */
	hblank_interval = hblank * (link->rate / 4) / mode->clock;
	DP_WRITE(priv, DPTX_VIDEO_HBLANK_INTERVAL,
		 FIELD_PREP(HBLANK_INTERVAL_EN, 1) |
		      FIELD_PREP(HBLANK_INTERVAL, hblank_interval));

	/* Video stream enable */
	dw_dp_update_bits(priv, DPTX_VSAMPLE_CTRL, VIDEO_STREAM_ENABLE,
			  FIELD_PREP(VIDEO_STREAM_ENABLE, 1));

	if (link->vsc_sdp_extension_for_colorimetry_supported)
		dw_dp_send_vsc_sdp(priv);

	return 0;
}

static inline int sft_ds_config(void __iomem *ds_base, int dc_id,
				int pclk_ena, int dat_ena,
				bool vs_high, bool hs_high)
{
	u32 csr = 0;
	unsigned int timeout = 300;

	if (!ds_base)
		return -EINVAL;

	csr |= pclk_ena << PIXCLK_ENA_SHIFT;
	csr |= dc_id    << PIXCLK_SW_SHIFT;
	if (dat_ena)
		csr |= (dc_id + 1) << DATMUX_CTRL_SHIFT;
	csr |= (!vs_high) << VS_POL_SEL_SHIFT;
	csr |= (!hs_high) << HS_POL_SEL_SHIFT;

	DYNSW_WRITE(ds_base, VOUT_DYNSW_INTR_ENA, 0);
	DYNSW_WRITE(ds_base, VOUT_DYNSW_CSR, csr);

	/* Poll for switch done/data off */
	while (timeout--) {
		u32 stat = DYNSW_READ(ds_base, VOUT_DYNSW_INTR_CLEAR);

		if (stat & SW_DONE_INTR) {
			DYNSW_WRITE(ds_base, VOUT_DYNSW_INTR_CLEAR,
				    SW_DONE_INTR_CLEAR);
			return 0;
		}
		if (stat & DATA_OFF_INTR) {
			DYNSW_WRITE(ds_base, VOUT_DYNSW_INTR_CLEAR,
				    DATA_OFF_INTR_CLEAR);
			return 0;
		}
		mdelay(1);
	}

	return -ETIMEDOUT;
}

static int dw_dp_connector_enable(struct udevice *dev, u8 dc_id)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct connector_state *conn_state = &priv->conn_state;
	struct drm_display_mode *mode = &conn_state->mode;
	struct dw_dp_video *video = &priv->video;
	int ret;

	memcpy(&video->mode, mode, sizeof(video->mode));

	ret = dw_dp_link_enable(dev);
	if (ret < 0) {
		printf("failed to enable link: %d\n", ret);
		return ret;
	}

	ret = dw_dp_video_enable(dev);
	if (ret < 0) {
		printf("failed to enable video: %d\n", ret);
		return ret;
	}

	sft_ds_config(priv->dynsw, dc_id, 1, 1,
		      priv->v_sync_polarity, priv->h_sync_polarity);

	return 0;
}

static bool dw_dp_detect(struct dw_dp *priv)
{
	u32 value;

	value = DP_READ(priv, DPTX_HPD_STATUS);
	if (FIELD_GET(HPD_STATE, value) == DP_SOURCE_STATE_PLUG) {
		DP_WRITE(priv, DPTX_HPD_STATUS, HPD_HOT_PLUG);
		printf("DP cable connected.\n");
		return true;
	}

	return false;
}

static int drm_dp_bw_code_to_link_rate(u8 link_bw)
{
	/* Spec says link_rate = link_bw * 0.27Gbps */
	return link_bw * 27000;
}

static inline int
drm_dp_max_link_rate(const u8 *dpcd)
{
	return drm_dp_bw_code_to_link_rate(dpcd[DP_MAX_LINK_RATE]);
}

static inline u8
drm_dp_max_lane_count(const u8 *dpcd)
{
	return dpcd[DP_MAX_LANE_COUNT] & DP_MAX_LANE_COUNT_MASK;
}

static inline bool
drm_dp_enhanced_frame_cap(const u8 *dpcd)
{
	return dpcd[DP_DPCD_REV] >= 0x11 &&
		(dpcd[DP_MAX_LANE_COUNT] & DP_ENHANCED_FRAME_CAP);
}

static inline bool
drm_dp_tps3_supported(const u8 *dpcd)
{
	return dpcd[DP_DPCD_REV] >= 0x12 &&
		dpcd[DP_MAX_LANE_COUNT] & DP_TPS3_SUPPORTED;
}

static inline bool
drm_dp_tps4_supported(const u8 *dpcd)
{
	return dpcd[DP_DPCD_REV] >= 0x14 &&
		dpcd[DP_MAX_DOWNSPREAD] & DP_TPS4_SUPPORTED;
}

static int drm_dp_read_extended_dpcd_caps(struct dw_dp *priv,
					  u8 *dpcd)
{
	u32 dpcd_ext[6];
	int ret;

	/*
	 * Prior to DP1.3 the bit represented by
	 * DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT was reserved.
	 * If it is set DP_DPCD_REV at 0000h could be at a value less than
	 * the true capability of the panel. The only way to check is to
	 * then compare 0000h and 2200h.
	 */
	if (!(dpcd[DP_TRAINING_AUX_RD_INTERVAL] &
	      DP_EXTENDED_RECEIVER_CAP_FIELD_PRESENT))
		return 0;

	ret = drm_dp_dpcd_read(priv, DP_DP13_DPCD_REV, &dpcd_ext,
			       sizeof(dpcd_ext));
	if (ret < 0)
		return ret;
	if (ret != sizeof(dpcd_ext))
		return -EIO;

	if (dpcd[DP_DPCD_REV] > dpcd_ext[DP_DPCD_REV]) {
		printf("Extended DPCD rev less than base DPCD rev (%d > %d)\n",
		       dpcd[DP_DPCD_REV], dpcd_ext[DP_DPCD_REV]);
		return 0;
	}

	if (!memcmp(dpcd, dpcd_ext, sizeof(dpcd_ext)))
		return 0;

	debug("Base DPCD: %*ph\n",
	      DP_RECEIVER_CAP_SIZE, dpcd);

	memcpy(dpcd, dpcd_ext, sizeof(dpcd_ext));

	return 0;
}

static int drm_dp_read_dpcd_caps(struct dw_dp *priv,
				 u8 *dpcd)
{
	int ret;

	ret = drm_dp_dpcd_read(priv, DP_DPCD_REV, (u32 *)dpcd, DP_RECEIVER_CAP_SIZE);
	if (ret < 0)
		return ret;
	if (ret != DP_RECEIVER_CAP_SIZE || dpcd[DP_DPCD_REV] == 0)
		return -EIO;

	ret = drm_dp_read_extended_dpcd_caps(priv, dpcd);
	if (ret < 0)
		return ret;

	return ret;
}

static int dw_dp_link_probe(struct dw_dp *priv)
{
	struct dw_dp_link *link = &priv->link;
	u8 dpcd;
	int ret;

	drm_dp_dpcd_writeb(priv, DP_MSTM_CTRL, 0);
	ret = drm_dp_read_dpcd_caps(priv, link->dpcd);
	if (ret < 0)
		return ret;

	ret = drm_dp_dpcd_readb(priv, DP_DPRX_FEATURE_ENUMERATION_LIST,
				&dpcd);
	if (ret < 0)
		return ret;

	link->vsc_sdp_extension_for_colorimetry_supported =
		!!(dpcd & DP_VSC_SDP_EXT_FOR_COLORIMETRY_SUPPORTED);

	link->revision = link->dpcd[DP_DPCD_REV];
	link->rate = min_t(u32, priv->max_link_rate, drm_dp_max_link_rate(link->dpcd));
	link->lanes = min_t(u8, priv->max_lane_count, drm_dp_max_lane_count(link->dpcd));

	link->caps.enhanced_framing = drm_dp_enhanced_frame_cap(link->dpcd);
	link->caps.tps3_supported = drm_dp_tps3_supported(link->dpcd);
	link->caps.tps4_supported = drm_dp_tps4_supported(link->dpcd);
	link->caps.channel_coding = drm_dp_channel_coding_supported(link->dpcd);
	link->caps.ssc = !!(link->dpcd[DP_MAX_DOWNSPREAD] &
			    DP_MAX_DOWNSPREAD_0_5);

	return 0;
}

static int dw_dp_connector_detect(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	int status, tries, ret;

	for (tries = 0; tries < 200; tries++) {
		status = dw_dp_detect(priv);
		if (status)
			break;
		mdelay(2);
	}

	ret = dw_dp_link_probe(priv);
	if (ret)
		printf("failed to probe DP link: %d\n", ret);

	return status;
}

static int dw_dp_connector_get_timing(struct udevice *dev,
				      const struct display_timing *timing)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct connector_state *conn_state = &priv->conn_state;
	struct drm_display_mode *mode = &conn_state->mode;
	u32 bus_fmt;

	int hactive = timing->hactive.typ;
	int hfp     = timing->hfront_porch.typ;
	int hbp     = timing->hback_porch.typ;
	int hsync   = timing->hsync_len.typ;

	int vactive = timing->vactive.typ;
	int vfp     = timing->vfront_porch.typ;
	int vbp     = timing->vback_porch.typ;
	int vsync   = timing->vsync_len.typ;

	/* pixelclock in Hz -> kHz */
	mode->clock = (int)(timing->pixelclock.typ / 1000);

	mode->hdisplay    = hactive;
	mode->hsync_start = hactive + hfp;
	mode->hsync_end   = hactive + hfp + hsync;
	mode->htotal      = hactive + hfp + hsync + hbp;

	mode->vdisplay    = vactive;
	mode->vsync_start = vactive + vfp;
	mode->vsync_end   = vactive + vfp + vsync;
	mode->vtotal      = vactive + vfp + vsync + vbp;

	if (mode->htotal && mode->vtotal && mode->clock) {
		mode->vrefresh = (mode->clock * 1000) /
					(mode->htotal * mode->vtotal);
	} else {
		mode->vrefresh = 0;
	}

	mode->vscan = 0;

	mode->flags = 0;
	if (timing->flags & DISPLAY_FLAGS_HSYNC_HIGH)
		mode->flags |= DRM_MODE_FLAG_PHSYNC;
	else
		mode->flags |= DRM_MODE_FLAG_NHSYNC;

	if (timing->flags & DISPLAY_FLAGS_VSYNC_HIGH)
		mode->flags |= DRM_MODE_FLAG_PVSYNC;
	else
		mode->flags |= DRM_MODE_FLAG_NVSYNC;

	if (timing->flags & DISPLAY_FLAGS_INTERLACED)
		mode->flags |= DRM_MODE_FLAG_INTERLACE;

	bus_fmt = 1;
	conn_state->bus_format = dw_dp_possible_output_fmts[bus_fmt].bus_format;

	return 0;
}

static int dw_dp_get_output_fmts_index(u32 bus_format)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(dw_dp_possible_output_fmts); i++) {
		const struct dw_dp_output_format *fmt = &dw_dp_possible_output_fmts[i];

		if (fmt->bus_format == bus_format)
			break;
	}

	if (i == ARRAY_SIZE(dw_dp_possible_output_fmts))
		return 1;

	return i;
}

static int dw_dp_connector_prepare(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	struct connector_state *conn_state = &priv->conn_state;
	struct dw_dp_video *video = &priv->video;
	int bus_fmt;

	bus_fmt = dw_dp_get_output_fmts_index(conn_state->bus_format);
	video->video_mapping = dw_dp_possible_output_fmts[bus_fmt].video_mapping;
	video->color_format = dw_dp_possible_output_fmts[bus_fmt].color_format;
	video->bus_format = dw_dp_possible_output_fmts[bus_fmt].bus_format;
	video->bpc = dw_dp_possible_output_fmts[bus_fmt].bpc;
	video->bpp = dw_dp_possible_output_fmts[bus_fmt].bpp;

	return 0;
}

static int dw_dp_enable(struct udevice *dev, int panel_bpp,
			const struct display_timing *timing)
{
	struct dw_dp *priv = dev_get_priv(dev);

	priv->dc_id = video_jhb100_get_dc_dev_id();
	priv->v_sync_polarity = (timing->flags & DISPLAY_FLAGS_HSYNC_HIGH) ? 1 : 0;
	priv->h_sync_polarity = (timing->flags & DISPLAY_FLAGS_VSYNC_HIGH) ? 1 : 0;

	dw_dp_connector_get_timing(dev, timing);

	sft_ds_config(priv->dynsw, priv->dc_id, 1, 0, priv->v_sync_polarity, priv->h_sync_polarity);
	dw_dp_connector_prepare(dev);
	dw_dp_connector_enable(dev, priv->dc_id);

	return 0;
}

static u32 dw_dp_parse_link_frequencies(struct udevice *dev)
{
	u64 frequency = 0;
	int ret;

	ret = dev_read_u64(dev, "link-frequencies", &frequency);
	if (ret) {
		dev_dbg(dev, "link-frequencies not found\n");
		return 0;
	}

	do_div(frequency, 10 * 1000); /* symbol rate kbytes */

	switch (frequency) {
	case 162000:
	case 270000:
	case 540000:
	case 810000:
		break;
	default:
		dev_err(dev, "invalid link frequency value: %llu\n", frequency);
		return 0;
	}

	return frequency;
}

static u32 dw_dp_parse_lane_count(struct udevice *dev)
{
	u32 lanes;
	int ret;

	ret = dev_read_u32(dev, "lane-count", &lanes);
	if (ret) {
		dev_dbg(dev, "lane-count not found\n");
		return 0;
	}

	switch (lanes) {
	case 1:
	case 2:
	case 4:
		break;
	default:
		dev_err(dev, "invalid lane-count value: %u\n", lanes);
		return 0;
	}

	return lanes;
}

static int dw_dp_parse_dt(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);

	priv->max_link_rate = dw_dp_parse_link_frequencies(dev);
	if (!priv->max_link_rate)
		priv->max_link_rate = 810000;

	priv->max_lane_count = dw_dp_parse_lane_count(dev);
	if (!priv->max_lane_count)
		priv->max_lane_count = 4;

	return 0;
}

static int dw_dp_probe(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);
	int ret;

	priv->dp = dev_read_addr_ptr(dev);
	if (!priv->dp)
		return -EINVAL;

	priv->dynsw = dev_remap_addr_name(dev, "dynsw");

	priv->vout_syscon = syscon_regmap_lookup_by_phandle(dev,
							    "vout-syscon");
	if (IS_ERR(priv->vout_syscon))
		return PTR_ERR(priv->vout_syscon);

	priv->dc_syscon = syscon_regmap_lookup_by_phandle(dev, "dc-syscon");

	ret = reset_get_bulk(dev, &priv->resets);
	if (ret)
		dev_err(dev, "Failed to get resetctl\n");

	ret = reset_deassert_bulk(&priv->resets);
	if (ret) {
		dev_err(dev, "Failed to deassert controller\n");
		return ret;
	}

	dw_dp_parse_dt(dev);

	/* Set for DDR Address higher than 32-bit */
	DC_SYSCON_WRITE(priv, 0x14, 0x800);
	DC_SYSCON_WRITE(priv, 0x18, 0x800);

	dw_dp_connector_init(dev);
	dw_dp_connector_detect(dev);

	return 0;
}

static int dw_dp_remove(struct udevice *dev)
{
	struct dw_dp *priv = dev_get_priv(dev);

	sft_ds_config(priv->dynsw, priv->dc_id, 1, 0,
		      priv->v_sync_polarity, priv->h_sync_polarity);
	mdelay(20);

	/* Video stream disable */
	dw_dp_update_bits(priv, DPTX_VSAMPLE_CTRL, VIDEO_STREAM_ENABLE,
			  FIELD_PREP(VIDEO_STREAM_ENABLE, 0));

	reset_assert_bulk(&priv->resets);

	return 0;
}

static const struct dm_display_ops dw_dp_ops = {
	.read_edid = dw_dp_read_edid,
	.enable = dw_dp_enable,
};

static const struct udevice_id dw_dp_ids[] = {
	{ .compatible = "starfive,jhb100-dp" },
	{ }
};

U_BOOT_DRIVER(dw_dp) = {
	.name = "jhb100_dw_dp",
	.id = UCLASS_DISPLAY,
	.of_match = dw_dp_ids,
	.ops = &dw_dp_ops,
	.probe = dw_dp_probe,
	.remove = dw_dp_remove,
	.priv_auto = sizeof(struct dw_dp),
};
