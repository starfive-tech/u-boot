// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	Wei Sheng Ch'ng <weisheng.chng@starfivetech.com>
 *
 */
#include <common.h>
#include <dm.h>
#include <wdt.h>
#include <clk.h>
#include <dm/device_compat.h>
#include <linux/io.h>
#include <reset.h>

struct starfive_wdt_jhb100_priv {
	void __iomem *base;
	u64 freq;
	struct udevice *dev;
	struct clk *core_clk;
	struct clk *apb_clk;
	u32 count;
};

/* Watchdog timeout range */
#define STARFIVE_JHB100_WDT_MINCNT_MS		1
#define STARFIVE_JHB100_WDT_MAXCNT_MS		4294967295 /* 0xFFFFFFFF */
#define STARFIVE_JHB100_WDT_DEFAULT_MS		15000
#define STARFIVE_JHB100_WDT_RST_PULSE_WIDTH	100

#define STARFIVE_JHB100_WDT_RESTART_MAGIC_NUM	0x2BA8 /* MAGIC NUMBER to restart count */
#define STARFIVE_JHB100_WDT_WR_LOCK_SECURE_NUM	0xE19C /* MAGIC NUMBER to unlock write access */

/* JHB100 Watchdog register offset */
#define STARFIVE_JHB100_WDT_CTRL		0x000	/* RW: Watchdog control register */
#define STARFIVE_JHB100_WDT_RST_PULSE		0x004	/* RW: Reset pulse width register */
#define STARFIVE_JHB100_WDT_INT_TIMEOUT		0x008	/* RW: Interrupt timeout register */
#define STARFIVE_JHB100_WDT_RST_TIMEOUT		0x00C	/* RW: Reset timeout register */
#define STARFIVE_JHB100_WDT_COUNT		0x010	/* RO: Current wdt count register */
#define STARFIVE_JHB100_WDT_RESTART		0x014	/* WO: Restart wdt register */
#define STARFIVE_JHB100_WDT_WRITE_LOCK		0x018	/* WO: Write access unlock register */
#define STARFIVE_JHB100_WDT_INTERRUPT		0x01C	/* W1C: Clear interrupt if set */
#define STARFIVE_JHB100_WDT_STATUS		0x020	/* RO: Check write access status */

/* Bit config for wdt control register */
#define STARFIVE_JHB100_WDT_CTRL_WDT_ENABLE		BIT(0)
#define STARFIVE_JHB100_WDT_CTRL_SINGLE_STAGE_MODE	BIT(1)
#define STARFIVE_JHB100_WDT_CTRL_INT_ENABLE		BIT(2)
#define STARFIVE_JHB100_WDT_CTRL_INT_ACT_HIGH_POLARITY	BIT(3)
#define STARFIVE_JHB100_WDT_CTRL_RST_ENABLE		BIT(4)
#define STARFIVE_JHB100_WDT_CTRL_RST_ACT_HIGH_POLARITY	BIT(5)
#define STARFIVE_JHB100_WDT_CTRL_RST_LEVEL_TRIG_MODE	BIT(6)

/* Bit config for wdt interrupt register */
#define STARFIVE_JHB100_WDT_INTERRUPT_ACTIVE		BIT(0)

/* Bit config for wdt write access register */
#define STARFIVE_JHB100_WDT_STATUS_LOCKED		BIT(0)

#define STARFIVE_JHB100_WDT_INTERRUPT_TIMEOUT		0
#define STARFIVE_JHB100_WDT_RESET_TIMEOUT		1

/**
 * starfive_wdt_jhb100_is_locked - Check if write access to register is locked.
 *
 * @priv: Private data
 *
 * Read the first bit content of wrlock reg
 *
 * Return: locked - 1, unlocked - 0.
 */
static int starfive_wdt_jhb100_is_locked(struct starfive_wdt_jhb100_priv *priv)
{
	u32 val;

	val = readl(priv->base + STARFIVE_JHB100_WDT_STATUS);

	return !!(val & STARFIVE_JHB100_WDT_STATUS_LOCKED);
}

/**
 * starfive_wdt_jhb100_unlock - Unlock wdt register for write access.
 *
 * @priv: Private data
 *
 * Write unlock to wrlock reg if the register is locked
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_unlock(struct starfive_wdt_jhb100_priv *priv)
{
	if (starfive_wdt_jhb100_is_locked(priv))
		writel(STARFIVE_JHB100_WDT_WR_LOCK_SECURE_NUM,
		       priv->base + STARFIVE_JHB100_WDT_WRITE_LOCK);
}

/**
 * starfive_wdt_jhb100_lock - Lock wdt register to prevent write access.
 *
 * @priv: Private data
 *
 * Write lock to wrlock reg if the register is not locked
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_lock(struct starfive_wdt_jhb100_priv *priv)
{
	if (!starfive_wdt_jhb100_is_locked(priv))
		writel(STARFIVE_JHB100_WDT_WR_LOCK_SECURE_NUM,
		       priv->base + STARFIVE_JHB100_WDT_WRITE_LOCK);
}

/**
 * starfive_wdt_jhb100_set_reg_mask - Set corresponding bit.
 *
 * @priv: Private data
 * @off: Register offset
 * @bitmask: Bit to set
 *
 * Return: N/A
 */
static inline void starfive_wdt_jhb100_set_reg_mask(struct starfive_wdt_jhb100_priv *priv,
						    u32 off, u32 bitmask)
{
	u32 val;

	starfive_wdt_jhb100_unlock(priv);
	val = readl(priv->base + off);
	val |= bitmask;
	writel(val, priv->base + off);
	starfive_wdt_jhb100_lock(priv);
}

/**
 * starfive_wdt_jhb100_clear_reg_mask - Clear corresponding bit.
 *
 * @priv: Private data
 * @off: Register offset
 * @bitmask: Bit to set
 *
 * Return: N/A
 */
static inline void starfive_wdt_jhb100_clear_reg_mask(struct starfive_wdt_jhb100_priv *priv,
						      u32 off, u32 bitmask)
{
	u32 val;

	starfive_wdt_jhb100_unlock(priv);
	val = readl(priv->base + off);
	val &= ~(bitmask);
	writel(val, priv->base + off);
	starfive_wdt_jhb100_lock(priv);
}

/**
 * starfive_wdt_jhb100_is_enabled - Check if watchdog is enbaled.
 *
 * @priv: Private data
 *
 * Read wdt ctrl reg to determine if watchdog has been enabled
 *
 * Return: enable - 1, disable - 0
 */
static int starfive_wdt_jhb100_is_enabled(struct starfive_wdt_jhb100_priv *priv)
{
	u32 val;

	val = readl(priv->base + STARFIVE_JHB100_WDT_CTRL);
	return !!(val & STARFIVE_JHB100_WDT_CTRL_WDT_ENABLE);
}

/**
 * starfive_wdt_jhb100_disable - Disable watchdog timer.
 *
 * @priv: Private data
 *
 * Stop countdown of watchdog timer
 *
 * Return: N/A
 */
static inline void starfive_wdt_jhb100_disable(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_clear_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL,
					   STARFIVE_JHB100_WDT_CTRL_WDT_ENABLE);
}

/**
 * starfive_wdt_jhb100_enable - Enable watchdog timer.
 *
 * @priv: Private data
 *
 * Start countdown of watchdog timer
 *
 * Return: N/A
 */
static inline void starfive_wdt_jhb100_enable(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL,
					 STARFIVE_JHB100_WDT_CTRL_WDT_ENABLE);
}

/**
 * starfive_wdt_jhb100_enable_interrupt - Enable watchdog interrupt.
 *
 * @priv: Private data
 *
 * Enable watchdog interrupt assert after first stage expiration
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_enable_interrupt(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL,
					 STARFIVE_JHB100_WDT_CTRL_INT_ENABLE);
}

/**
 * starfive_wdt_jhb100_set_act_high_intr_polarity - Select Active high polarity ofr intr.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_set_act_high_intr_polarity(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL,
					 STARFIVE_JHB100_WDT_CTRL_INT_ACT_HIGH_POLARITY);
}

/**
 * starfive_wdt_jhb100_enable_reset - Enable watchdog reset.
 *
 * @priv: Private data
 *
 * Enable watchdog reset after second stage expiration
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_enable_reset(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL,
					 STARFIVE_JHB100_WDT_CTRL_RST_ENABLE);
}

/**
 * starfive_wdt_jhb100_set_act_high_rst_polarity - Set Active High for reset polarity.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_set_act_high_rst_polarity(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL,
					 STARFIVE_JHB100_WDT_CTRL_RST_ACT_HIGH_POLARITY);
}

/**
 * starfive_wdt_jhb100_set_pulse_rst_trig_mode - Select pulse reset triggering mode.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_set_pulse_rst_trig_mode(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_clear_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL,
					   STARFIVE_JHB100_WDT_CTRL_RST_LEVEL_TRIG_MODE);
}

/**
 * starfive_wdt_jhb100_set_rst_pulse_width - Set reset pulse width.
 *
 * @priv: Private data
 * @val: Reset pulse width
 *
 * Return: N/A
 */
static inline void starfive_wdt_jhb100_set_rst_pulse_width(struct starfive_wdt_jhb100_priv
							   *priv, u32 val)
{
	starfive_wdt_jhb100_unlock(priv);
	writel(val, priv->base + STARFIVE_JHB100_WDT_RST_PULSE);
	starfive_wdt_jhb100_lock(priv);
}

/**
 * starfive_wdt_jhb100_set_intr_timeout - Set timeout period for interrupt assertion.
 *
 * @priv: Private data
 * @val: Timeout period for interrupt assertion
 *
 * Return: N/A
 */
static inline void starfive_wdt_jhb100_set_intr_timeout(struct starfive_wdt_jhb100_priv *priv,
							u32 val)
{
	starfive_wdt_jhb100_unlock(priv);
	writel(val, priv->base + STARFIVE_JHB100_WDT_INT_TIMEOUT);
	starfive_wdt_jhb100_lock(priv);
}

/**
 * starfive_wdt_jhb100_set_rst_timeout - Set timeout period for reset assertion.
 *
 * @priv: Private data
 * @val: Timeout period for reset assertion
 *
 * Return: N/A
 */
static inline void starfive_wdt_jhb100_set_rst_timeout(struct starfive_wdt_jhb100_priv *priv,
						       u32 val)
{
	starfive_wdt_jhb100_unlock(priv);
	writel(val, priv->base + STARFIVE_JHB100_WDT_RST_TIMEOUT);
	starfive_wdt_jhb100_lock(priv);
}

/**
 * starfive_wdt_jhb100_set_restart - Restart countdown of watchdog.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static inline void starfive_wdt_jhb100_set_restart(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_unlock(priv);
	writel(STARFIVE_JHB100_WDT_RESTART_MAGIC_NUM,
	       priv->base + STARFIVE_JHB100_WDT_RESTART);
	starfive_wdt_jhb100_lock(priv);
}

#if 0
/**
 * starfive_wdt_jhb100_sel_two_stage_timeout - Select two stage timeout mode.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_sel_two_stage_timeout(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_clear_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_SINGLE_STAGE_MODE);
}

/**
 * starfive_wdt_jhb100_clear_wdt_intr - Clear wdt interrupt.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_clear_wdt_intr(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_INTERRUPT, STARFIVE_JHB100_WDT_INTERRUPT_ACTIVE);
}

/**
 * starfive_wdt_jhb100_get_count - Check current count of wdt.
 *
 * @priv: Private data
 *
 * Return: Count.
 */
static u32 starfive_wdt_jhb100_get_count(struct starfive_wdt_jhb100_priv *priv)
{
	u32 val;

	val = readl(priv->base + STARFIVE_JHB100_WDT_COUNT);
	return val;
}

/**
 * starfive_wdt_jhb100_set_pulse_rst_trig_mode - Set pulse reset triggering mode.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_set_pulse_rst_trig_mode(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_clear_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_RST_LEVEL_TRIG_MODE);
}

/**
 * starfive_wdt_jhb100_set_act_high_rst_polarity - Set Active High for reset polarity.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_set_act_high_rst_polarity(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_RST_ACT_HIGH_POLARITY);
}

/**
 * starfive_wdt_jhb100_set_act_low_rst_polarity - Set Active low for reset polarity.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_set_act_low_rst_polarity(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_clear_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_RST_ACT_HIGH_POLARITY);
}

/**
 * starfive_wdt_jhb100_set_level_rst_trig_mode - Select Level reset triggering mode.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_set_level_rst_trig_mode(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_RST_LEVEL_TRIG_MODE);
}

/**
 * starfive_wdt_jhb100_disable_reset - Disable watchdog reset.
 *
 * @priv: Private data
 *
 * Disable watchdog reset.
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_disable_reset(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_clear_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_RST_ENABLE);
}

/**
 * starfive_wdt_jhb100_enable_reset - Enable watchdog reset.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_enable_reset(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_RST_ENABLE);
}

/**
 * starfive_wdt_jhb100_set_act_low_intr_polarity - Set active low interrupt polarity.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_set_act_low_intr_polarity(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_clear_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_INT_ACT_HIGH_POLARITY);
}

/**
 * starfive_wdt_jhb100_disable_interrupt - Disable watchdog first stage interrupt.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_jhb100_disable_interrupt(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_clear_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL, STARFIVE_JHB100_WDT_CTRL_INT_ENABLE);
}
#endif
/**
 * starfive_wdt_sel_single_stage_timeout - Select single stage timeout.
 *
 * @priv: Private data
 *
 * Return: N/A
 */
static void starfive_wdt_sel_single_stage_timeout(struct starfive_wdt_jhb100_priv *priv)
{
	starfive_wdt_jhb100_set_reg_mask(priv, STARFIVE_JHB100_WDT_CTRL,
					 STARFIVE_JHB100_WDT_CTRL_SINGLE_STAGE_MODE);
}

/**
 * starfive_wdt_jhb100_enable_clock - Enable watchdog clock
 *
 * @priv: Private data
 *
 * Return: Success - 0, Fail - error enum
 */
static int starfive_wdt_jhb100_enable_clock(struct starfive_wdt_jhb100_priv *priv)
{
	int ret = 0;

	priv->apb_clk = devm_clk_get(priv->dev, "apb");
	if (!IS_ERR(priv->apb_clk)) {
		ret = clk_prepare_enable(priv->apb_clk);
		if (ret)
			dev_warn(priv->dev, "enable apb_clk error.\n");
	}

	priv->core_clk = devm_clk_get(priv->dev, "core");
	if (!IS_ERR(priv->core_clk)) {
		ret = clk_prepare_enable(priv->core_clk);
		if (ret)
			dev_warn(priv->dev, "enable core_clk error.\n");
	}

	return ret;
}

/**
 * starfive_wdt_jhb100_get_clock_rate - Get clock frequency
 *
 * @priv: Private data
 *
 * Get frequency from dts if declared, else, get from internal clock
 *
 * Return: Success - 0, Fail - error enum
 */
static int starfive_wdt_jhb100_get_clock_rate(struct starfive_wdt_jhb100_priv *priv)
{
	u32 freq = 0;

	/* Next we try to get clock-frequency from dts.*/
	freq = dev_read_u32_default(priv->dev, "clock-frequency", 0);
	if (freq) {
		priv->freq = (u64)freq;
		return 0;
	}
	dev_dbg(priv->dev, "get rate failed, undefined clock-frequency in dts.\n");

	if (!IS_ERR(priv->core_clk)) {
		priv->freq = clk_get_rate(priv->core_clk);
		return 0;
	}
	dev_err(priv->dev, "get clock-frequency failed\n");

	return -ENOENT;
}

/**
 * starfive_wdt_jhb100_max_timeout - Get max frequency based on clock frequency
 *
 * @freq: CLock frequency used
 *
 * Get maximum timeout on the clock frqeuency used
 *
 * Return: Maximum timeout value in milliseconds
 */
static unsigned int starfive_wdt_jhb100_max_timeout(u64 freq)
{
	return (DIV_ROUND_UP(STARFIVE_JHB100_WDT_MAXCNT_MS, freq) - 1) * 1000;
}

/**
 * starfive_wdt_jhb100_set_timeout - Calculate and set count value to load reg
 *
 * @priv: Private data
 * @timeout: watchdog timeout value in milliseconds
 *
 * Calculate watchdog count value based on timeout value and clock
 * frequency. Use maximum count value defined in macro if count exceeds
 * max count. Write calculated count into interrupt register.
 *
 * Return: Success 0, Fail - EINVAL
 */
static int starfive_wdt_jhb100_set_timeout(struct starfive_wdt_jhb100_priv *priv,
					   unsigned int timeout, unsigned int wdt_mode)
{
	unsigned long freq = priv->freq;
	unsigned int count;

	if (timeout < 1)
		return -EINVAL;

	/* Calculate timeout for interrupt assertion as is, no need to be divided by half */
	count = (timeout * freq) / 1000;

	if (count > STARFIVE_JHB100_WDT_MAXCNT_MS) {
		dev_warn(priv->dev, "timeout %d too big,use the MAX-timeout set.\n",
				timeout);
		timeout = starfive_wdt_jhb100_max_timeout(priv->freq);
		count = (timeout * freq) / 1000;
	}

	dev_info(priv->dev, "Heartbeat: timeout=%d ms, count/2=%d (%08x)\n",
		 timeout, count, count);

	if (wdt_mode == STARFIVE_JHB100_WDT_RESET_TIMEOUT)
		starfive_wdt_jhb100_set_intr_timeout(priv, count);
	else if (wdt_mode == STARFIVE_JHB100_WDT_INTERRUPT_TIMEOUT)
		starfive_wdt_jhb100_set_rst_timeout(priv, count);

	priv->count = count;

	return 0;
}

/**
 * starfive_wdt_jhb100_probe - Probe watchdog device
 *
 * @dev: Watchdog device
 *
 * Get the base address of watchdog registers
 *
 * Return: Sucess - 0, Fail - EINVAL
 */
static int starfive_wdt_jhb100_probe(struct udevice *dev)
{
	int ret;
	struct udevice *clk_dev;

	ret = uclass_get_device_by_name(UCLASS_CLK, "clock-controller@13008000", &clk_dev);

	if (ret) {
		printf("clock device not found!\n");
		return -1;
	}

	struct starfive_wdt_jhb100_priv *priv = dev_get_priv(dev);

	priv->dev = dev;

	/* Get memory region */
	priv->base = dev_remap_addr(dev);
	if (!priv->base)
		return -EINVAL;

	return 0;
}

/**
 * starfive_wdt_jhb100_start - Start an instance of watchdog timer
 * TODO: Not automatically started yet until SCP is ready
 *
 * @dev: Watchdog device
 * @timeout: Timeout in ms
 * @flags: Configuration specific flags
 *
 * Enable internal clock and get the clock frequency.
 * Set timeout range to boundary value if exceed the boundary.
 * Watchdog timer configurations are enabled here,
 *
 * Return: Always 0
 */
static int starfive_wdt_jhb100_start(struct udevice *dev, u64 timeout, ulong flags)
{
	struct starfive_wdt_jhb100_priv *priv = dev_get_priv(dev);
	int ret;

	/* Enable clock */
	ret = starfive_wdt_jhb100_enable_clock(priv);
	if (ret) {
		dev_warn(priv->dev, "get & enable clk err\n");
		return -1;
	}

	/* Get clock frequency */
	ret = starfive_wdt_jhb100_get_clock_rate(priv);
	if (ret) {
		dev_warn(priv->dev, "get clk freq err\n");
		return -1;
	}

	/* WDT timeout range handling */
	timeout = max_t(u64, timeout, STARFIVE_JHB100_WDT_MINCNT_MS);
	timeout = min_t(u64, timeout, starfive_wdt_jhb100_max_timeout(priv->freq));

	/* Set timeout */
	ret = starfive_wdt_jhb100_set_timeout(priv, timeout, STARFIVE_JHB100_WDT_RESET_TIMEOUT);
	if (ret) {
		dev_info(dev, "tmr_margin value out of range, default %d used\n",
				 STARFIVE_JHB100_WDT_DEFAULT_MS);

		starfive_wdt_jhb100_set_timeout(priv,
						STARFIVE_JHB100_WDT_DEFAULT_MS,
						STARFIVE_JHB100_WDT_RESET_TIMEOUT);
	}

	/* Enable single stage timeout mechanism from AP side */
	starfive_wdt_sel_single_stage_timeout(priv);

	/* Enable interrupt assertion in first stage */
	starfive_wdt_jhb100_enable_interrupt(priv);

	/* Enable active high interrupt polarity */
	starfive_wdt_jhb100_set_act_high_intr_polarity(priv);

	/* Enable reset for when intr to SCP not served */
	starfive_wdt_jhb100_enable_reset(priv);

	/* Enable active high reset polarity */
	starfive_wdt_jhb100_set_act_high_rst_polarity(priv);

	/* Set level reset triggering mode */
	starfive_wdt_jhb100_set_pulse_rst_trig_mode(priv);

	/* Set reset pulse width */
	starfive_wdt_jhb100_set_rst_pulse_width(priv, STARFIVE_JHB100_WDT_RST_PULSE_WIDTH);

	/* Enable wdt countdown */
	starfive_wdt_jhb100_enable(priv);

	return 0;
}

/**
 * starfive_wdt_jhb100_reset - Restart watchdog counter.
 *
 * @dev: Watchdog device
 *
 * When watchdog is enabled, reset the watchdog counter to the counter programmed
 *
 * Return: Always 0
 */
static int starfive_wdt_jhb100_reset(struct udevice *dev)
{
	struct starfive_wdt_jhb100_priv *priv = dev_get_priv(dev);

	if (starfive_wdt_jhb100_is_enabled(priv))
		starfive_wdt_jhb100_set_restart(priv);

	return 0;
}

/**
 * starfive_wdt_jhb100_stop - Request watchdog to stop count
 *
 * @dev: Watchdog device
 *
 * Disable watchdog countdown
 *
 * Return: Always 0
 */
static int starfive_wdt_jhb100_stop(struct udevice *dev)
{
	struct starfive_wdt_jhb100_priv *priv = dev_get_priv(dev);

	starfive_wdt_jhb100_disable(priv);

	return 0;
}

/**
 * starfive_wdt_jhb100_expire_now - Request watchdog to expire immediately
 *
 * @dev: Watchdog device
 *
 * Set timer to minimum value, enable watchdog reset and enable
 * watchdog count.
 *
 * Return: Always 0
 */
static int starfive_wdt_jhb100_expire_now(struct udevice *dev, ulong flags)
{
	struct starfive_wdt_jhb100_priv *priv = dev_get_priv(dev);

	starfive_wdt_jhb100_set_intr_timeout(priv, 1);
	starfive_wdt_jhb100_enable(priv);

	return 0;
}

static const struct wdt_ops starfive_wdt_jhb100_ops = {
	.start = starfive_wdt_jhb100_start,
	.reset = starfive_wdt_jhb100_reset,
	.stop = starfive_wdt_jhb100_stop,
	.expire_now = starfive_wdt_jhb100_expire_now,
};

static const struct udevice_id starfive_wdt_jhb100_ids[] = {
	{	.compatible = "starfive,jhb100-wdt",},
	{}
};

U_BOOT_DRIVER(starfive_wdt) = {
	.name = "starfive_wdt_jhb100",
	.id = UCLASS_WDT,
	.of_match = starfive_wdt_jhb100_ids,
	.probe = starfive_wdt_jhb100_probe,
	.ops = &starfive_wdt_jhb100_ops,
	.priv_auto	= sizeof(struct starfive_wdt_jhb100_priv),
};
