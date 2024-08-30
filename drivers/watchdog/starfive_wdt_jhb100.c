// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright 2022 StarFive, Inc <yuinyee.chew@starfivetech.com>
 *
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING
 * CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER
 * FOR THEM TO SAVE TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE
 * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY
 * CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE
 * BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION
 * WITH THEIR PRODUCTS.
 */

#include <common.h>
#include <dm.h>
#include <wdt.h>
#include <clk.h>
#include <dm/device_compat.h>
#include <linux/io.h>
#include <reset.h>

struct starfive_wdt_priv {
	void __iomem *base;
	u64 freq;
	struct udevice *dev;
	struct clk *core_clk;
	struct clk *apb_clk;
	u32 count;
};

/* General define*/
#define STARFIVE_WDT_ENABLE			0x1

/* Watchdog timeout range */
#define STARFIVE_WDT_MINCNT_MS		1
#define STARFIVE_WDT_MAXCNT_MS		4294967295 /* 0xFFFFFFFF */
#define STARFIVE_WDT_DEFAULT_MS		15000

/* Register shift bit */
#define STARFIVE_WDT_INT_EN_SHIFT	0
#define STARFIVE_WDT_RESEN_SHIFT	1
#define STARFIVE_WDT_EN_SHIFT		0

/* Register unlock key */
#define STARFIVE_WDT_UNLOCK_KEY		0x1ACCE551

/* Register mask */
#define WDOG_LOCKED_MASK			BIT(0)
#define WDOG_ENABLED_MASK			BIT(0)

/* JHB100 Watchdog register offset */
#define STARFIVE_WDT_WDOGLOAD		0x000	/* RW: Watchdog load register */
#define STARFIVE_WDT_WDOGVALUE		0x004	/* RO: The current value for the watchdog counter */
#define STARFIVE_WDT_WDOGCONTROL	0x008	/* RW: [0]: reset enable;  [1]: int enable/wdt enable/reload counter; [31:2]: res */
#define STARFIVE_WDT_WDOGINTCLR		0x00C	/* WO: clear intterupt && reload the counter */
#define STARFIVE_WDT_WDOGRIS		0x010	/* RO: Raw interrupt status from the counter */
#define STARFIVE_WDT_WDOGIMS		0x014	/* RO: Enabled interrupt status from the counter */
#define STARFIVE_WDT_WDOGLOCK		0xC00	/* RO: Enable write access to all other registers by writing 0x1ACCE551 */
#define STARFIVE_WDT_WDOGITCR		0xF00	/* RW: When set HIGH, places the Watchdog into integraeion test mode */
#define STARFIVE_WDT_WDOGITOP		0xF04	/* WO: [0] Integration Test WDOGRES, [1] Integration Test WDOGINT value */

/**
 * starfive_wdt_is_locked - Check if write access to register is locked.
 *
 * @priv: Private data
 *
 * Read the first bit content of WdogLock reg
 *
 * Return: locked - 1, unlocked - 0.
 */
static int starfive_wdt_is_locked(struct starfive_wdt_priv *priv)
{
	u32 val;

	val = readl(priv->base + STARFIVE_WDT_WDOGLOCK);
	return !!(val & WDOG_LOCKED_MASK);
}

/**
 * starfive_wdt_unlock - Unlock wdt register for write access.
 *
 * @priv: Private data
 *
 * Write unlock to WdogLock reg if the register is locked
 *
 * Return: N/A
 */
static void starfive_wdt_unlock(struct starfive_wdt_priv *priv)
{
	if (starfive_wdt_is_locked(priv))
		writel(STARFIVE_WDT_UNLOCK_KEY, priv->base + STARFIVE_WDT_WDOGLOCK);
}

/**
 * starfive_wdt_lock - Lock wdt register to prevent write access.
 *
 * @priv: Private data
 *
 * Write lock to WdogLock reg if the register is not locked
 *
 * Return: N/A
 */
static void starfive_wdt_lock(struct starfive_wdt_priv *priv)
{
	if (!starfive_wdt_is_locked(priv))
		writel(~STARFIVE_WDT_UNLOCK_KEY, priv->base + STARFIVE_WDT_WDOGLOCK);
}

/**
 * starfive_wdt_is_enabled - Check is watchdog is enbaled.
 *
 * @priv: Private data
 *
 * Read WdogControl reg to determine if watchdog has been enabled
 *
 * Return: enable - 1, disable - 0
 */
static int starfive_wdt_is_enabled(struct starfive_wdt_priv *priv)
{
	u32 val;

	val = readl(priv->base + STARFIVE_WDT_WDOGCONTROL);
	return !!(val & WDOG_ENABLED_MASK);
}

/**
 * starfive_wdt_set_count - Check is watchdog is enabled.
 *
 * @priv: Private data
 * @val: New value to be set into watchdog timer
 *
 * Set watchdog timer with a new value by writing to WdogLoad reg
 *
 * Return: N/A
 */
static inline void starfive_wdt_set_count(struct starfive_wdt_priv *priv, u32 val)
{
	starfive_wdt_unlock(priv);
	writel(val, priv->base + STARFIVE_WDT_WDOGLOAD);
	starfive_wdt_lock(priv);
}

/**
 * starfive_wdt_disable - Disable watchdog timer count.
 *
 * @priv: Private data
 *
 * Stop decrement in watchdog timer
 *
 * Return: N/A
 */
static inline void starfive_wdt_disable(struct starfive_wdt_priv *priv)
{
	u32 val;

	starfive_wdt_unlock(priv);
	val = readl(priv->base + STARFIVE_WDT_WDOGCONTROL);
	val &= ~(STARFIVE_WDT_ENABLE << STARFIVE_WDT_EN_SHIFT);
	writel(val, priv->base + STARFIVE_WDT_WDOGCONTROL);
	starfive_wdt_lock(priv);
}

/**
 * starfive_wdt_enable - Enable watchdog timer count.
 *
 * @priv: Private data
 *
 * Start decrement in watchdog timer
 *
 * Return: N/A
 */
static inline void starfive_wdt_enable(struct starfive_wdt_priv *priv)
{
	u32 val;

	starfive_wdt_unlock(priv);
	val = readl(priv->base + STARFIVE_WDT_WDOGCONTROL);
	val |= STARFIVE_WDT_ENABLE << STARFIVE_WDT_EN_SHIFT;
	writel(val, priv->base + STARFIVE_WDT_WDOGCONTROL);
	starfive_wdt_lock(priv);
}

/**
 * starfive_wdt_disable_reset - Disable watchdog reset.
 *
 * @priv: Private data
 *
 * Disable watchdog reset despite counter expired
 *
 * Return: N/A
 */
static void starfive_wdt_disable_reset(struct starfive_wdt_priv *priv)
{
	u32 val;

	starfive_wdt_unlock(priv);
	val = readl(priv->base + STARFIVE_WDT_WDOGCONTROL);
	val &= ~(STARFIVE_WDT_ENABLE << STARFIVE_WDT_RESEN_SHIFT);
	writel(val, priv->base + STARFIVE_WDT_WDOGCONTROL);
	starfive_wdt_lock(priv);
}

/**
 * starfive_wdt_enable_reset - Enable watchdog reset.
 *
 * @priv: Private data
 *
 * Enable watchdog reset after counter expired
 *
 * Return: N/A
 */
static void starfive_wdt_enable_reset(struct starfive_wdt_priv *priv)
{
	u32 val;

	starfive_wdt_unlock(priv);
	val = readl(priv->base + STARFIVE_WDT_WDOGCONTROL);
	val |= STARFIVE_WDT_ENABLE << STARFIVE_WDT_RESEN_SHIFT;
	writel(val, priv->base + STARFIVE_WDT_WDOGCONTROL);
	starfive_wdt_lock(priv);
}

/**
 * starfive_wdt_enable_clock - Enable clock for watchdog
 *
 * @priv: Private data
 *
 * Enable watchdog reset after counter expired
 *
 * Return: Success - 0, Fail - error enum
 */
static int starfive_wdt_enable_clock(struct starfive_wdt_priv *priv)
{
	int ret = 0;

	priv->apb_clk = devm_clk_get(priv->dev, "apb");
	if (!IS_ERR(priv->apb_clk)) {
		ret = clk_prepare_enable(priv->apb_clk);
		if (ret)
			dev_warn(priv->dev, "enable core_clk error.\n");
	}

	priv->core_clk = devm_clk_get(priv->dev, "core");
	if (!IS_ERR(priv->core_clk)) {
		ret = clk_prepare_enable(priv->core_clk);
		if (ret)
			dev_warn(priv->dev, "enable apb_clk error.\n");
	}

	return ret;
}

/**
 * starfive_wdt_get_clock_rate - Get clock frequency
 *
 * @priv: Private data
 *
 * Get frequency from dts if declared, else, get from internal clock
 *
 * Return: Success - 0, Fail - error enum
 */
static int starfive_wdt_get_clock_rate(struct starfive_wdt_priv *priv)
{
	u32 freq = 0;

	/* Next we try to get clock-frequency from dts.*/
	freq = dev_read_u32_default(priv->dev, "clock-frequency", 0);
	if (freq) {
		priv->freq = (u64)freq;
		return 0;
	}
	dev_dbg(priv->dev, "get rate failed, need clock-frequency define in dts.\n");

	if (!IS_ERR(priv->core_clk)) {
		priv->freq = clk_get_rate(priv->core_clk);
		return 0;
	}
	dev_err(priv->dev, "get clock-frequency failed\n");

	return -ENOENT;
}

/**
 * starfive_wdt_max_timeout - Get max frequency based on clock frequency
 *
 * @freq: CLock frequency used
 *
 * Get maximum timeout on the clock frqeuency used
 *
 * Return: Maximum timeout value in milliseconds
 */
static unsigned int starfive_wdt_max_timeout(u64 freq)
{
	return (DIV_ROUND_UP(STARFIVE_WDT_MAXCNT_MS, freq) - 1) * 1000;
}

/**
 * starfive_wdt_set_timeout - Calculate and set count value to load reg
 *
 * @priv: Private data
 * @timeout: watchdog timeout value in milliseconds
 *
 * Calculate watchdog count value based on timeout value and clock
 * frequency. Use maximum count value defined in macro if count exceeds
 * max count. Write calculated count into WdogLoad reg.
 *
 * Return: Success 0, Fail - EINVAL
 */
static int starfive_wdt_set_timeout(struct starfive_wdt_priv *priv,
				    unsigned int timeout)
{
	unsigned long freq = priv->freq;
	unsigned int count;

	if (timeout < 1)
		return -EINVAL;

	count = (timeout * freq / 2) / 1000;

	if (count > STARFIVE_WDT_MAXCNT_MS) {
		dev_warn(priv->dev, "timeout %d too big,use the MAX-timeout set.\n",
				timeout);
		timeout = starfive_wdt_max_timeout(priv->freq);
		count = (timeout * freq) / 1000;
	}

	dev_info(priv->dev, "Heartbeat: timeout=%d ms, count/2=%d (%08x)\n",
		 timeout, count, count);

	starfive_wdt_set_count(priv, count);

	priv->count = count;

	return 0;
}

/**
 * starfive_wdt_probe - Probe watchdog device
 *
 * @dev: Watchdog device
 *
 * Get the base address of watchdog registers
 *
 * Return: Sucess - 0, Fail - EINVAL
 */
static int starfive_wdt_probe(struct udevice *dev)
{
	struct starfive_wdt_priv *priv = dev_get_priv(dev);

	priv->dev = dev;

	/* Get memory region */
	priv->base = dev_remap_addr(dev);
	if (!priv->base)
		return -EINVAL;

	return 0;
}

/**
 * starfive_wdt_start - Start watchdog device
 *
 * @dev: Watchdog device
 *
 * Enable internal clock and get the clock frequency.
 * Set timeout range to boundary value is exceed the boundary.
 * Watchdog start count and reset is enable here.
 *
 * Return: Always 0
 */
static int starfive_wdt_start(struct udevice *dev, u64 timeout, ulong flags)
{
	struct starfive_wdt_priv *priv = dev_get_priv(dev);
	int ret;

	/* Enable clock */
	ret = starfive_wdt_enable_clock(priv);
	if (ret) {
		dev_warn(priv->dev, "get & enable clk err\n");
		return -1;
	}

	/* Get clock frequency */
	ret = starfive_wdt_get_clock_rate(priv);
	if (ret) {
		dev_warn(priv->dev, "get clk freq err\n");
		return -1;
	}

	/* WDT timeout range handling */
	timeout = max_t(u64, timeout, STARFIVE_WDT_MINCNT_MS);
	timeout = min_t(u64, timeout, starfive_wdt_max_timeout(priv->freq));

	/* Set timeout */
	ret = starfive_wdt_set_timeout(priv, timeout);
	if (ret) {
		dev_info(dev, "tmr_margin value out of range, default %d used\n",
				 STARFIVE_WDT_DEFAULT_MS);
		starfive_wdt_set_timeout(priv,
					 STARFIVE_WDT_DEFAULT_MS);
	}

	/* Enale wdt reset to trigger */
	starfive_wdt_enable_reset(priv);

	/* Enable wdt countdown */
	starfive_wdt_enable(priv);

	return 0;
}

/**
 * starfive_wdt_reset - Reset watchdog counter (i.e. pat the watchdog).
 *
 * @dev: Watchdog device
 *
 * When watchdog is enabled, reset the watchdog counter based on "count"
 * value saved in starfive_wdt_set_timeout() function
 *
 * Return: Always 0
 */
static int starfive_wdt_reset(struct udevice *dev)
{
	struct starfive_wdt_priv *priv = dev_get_priv(dev);

	if (starfive_wdt_is_enabled(priv))
		starfive_wdt_set_count(priv, priv->count);

	return 0;
}

/**
 * starfive_wdt_stop - Request watchdog to stop count
 *
 * @dev: Watchdog device
 *
 * Disable watchdog reset and stop watchdog count
 *
 * Return: Always 0
 */
static int starfive_wdt_stop(struct udevice *dev)
{
	struct starfive_wdt_priv *priv = dev_get_priv(dev);

	starfive_wdt_disable_reset(priv);
	starfive_wdt_disable(priv);

	return 0;
}

/**
 * starfive_wdt_expire_now - Request watchdog to expire immediately
 *
 * @dev: Watchdog device
 *
 * Set timer to minimum value, enable watchdog reset and enable
 * watchdog count.
 *
 * Return: Always 0
 */
static int starfive_wdt_expire_now(struct udevice *dev, ulong flags)
{
	struct starfive_wdt_priv *priv = dev_get_priv(dev);

	starfive_wdt_set_count(priv, 1);
	starfive_wdt_enable_reset(priv);
	starfive_wdt_enable(priv);

	return 0;
}

static const struct wdt_ops starfive_wdt_ops = {
	.start = starfive_wdt_start,
	.reset = starfive_wdt_reset,
	.stop = starfive_wdt_stop,
	.expire_now = starfive_wdt_expire_now,
};

static const struct udevice_id starfive_wdt_ids[] = {
	{	.compatible = "starfive,dskit-wdt",},
	{	.compatible = "starfive,jhb100-wdt",},
	{}
};

U_BOOT_DRIVER(starfive_wdt) = {
	.name = "starfive_wdt",
	.id = UCLASS_WDT,
	.of_match = starfive_wdt_ids,
	.probe = starfive_wdt_probe,
	.ops = &starfive_wdt_ops,
	.priv_auto	= sizeof(struct starfive_wdt_priv),
};
