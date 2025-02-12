// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 StarFive Technology Co., Ltd.
 * Author:	ZhiWei Lim <zhiwei.lim@starfivetech.com>
 *
 */

#include <clk.h>
#include <clk-uclass.h>
#include <linux/math64.h>
#include <dm.h>
#include <pwm.h>
#include <linux/io.h>
#include <linux/bitfield.h>

/* max channel of pwm */
#define MAX_PWM				8

/* Bit for PWM clock */
#define BIT_PWM_CLOCK_EN		31

/* Bit for clock gen soft reset */
#define BIT_CLK_GEN_SOFT_RESET		13

#define NS_1				1000000000U

/* Access PTC register (cntr hrc lrc and ctrl), need to replace PWM_BASE_ADDR */
#define REG_PTC_BASE_ADDR_SUB(base, N) ({ \
	int _n = (N); \
	(base) + ((_n > 3) ? ((_n - 4) * 0x10 + (1 << 15)) : (_n * 0x10)); \
})

#define REG_PTC_RPTC_CNTR(base, N)	(REG_PTC_BASE_ADDR_SUB(base, N))
#define REG_PTC_RPTC_HRC(base, N)	(REG_PTC_BASE_ADDR_SUB(base, N) + 0x4)
#define REG_PTC_RPTC_LRC(base, N)	(REG_PTC_BASE_ADDR_SUB(base, N) + 0x8)
#define REG_PTC_RPTC_CTRL(base, N)	(REG_PTC_BASE_ADDR_SUB(base, N) + 0xC)

struct starfive_pwm_regs {
	unsigned long cntr;
	unsigned long hrc;
	unsigned long lrc;
	unsigned long ctrl;
};

struct starfive_pwm_data {
	struct starfive_pwm_regs regs;
};

struct starfive_pwm_priv {
	void __iomem *regs;
	ulong freq;
	bool enabled;
	struct starfive_pwm_data *data;
};

static int starfive_pwm_set_config(struct udevice *dev, uint channel,
				   uint period_ns, uint duty_ns)
{
	struct starfive_pwm_priv *priv = dev_get_priv(dev);
	struct starfive_pwm_regs *reg_addr = &priv->data->regs;
	u32 pwm_clk_ns = 0;
	u32 data_hrc = 0;
	u32 data_lrc = 0;
	u32 period_data = 0;
	u32 duty_data = 0;
	u32 val = 0;

	debug("%s: ch: %d\n", __func__, channel);
	debug("LRC from reg: %u\nHRC from reg: %u\n",
	      ioread32(REG_PTC_RPTC_LRC(priv->regs, channel)),
	      ioread32(REG_PTC_RPTC_HRC(priv->regs, channel)));
	debug("period_ns: %u\n", period_ns);
	debug("duty_ns: %u\n", duty_ns);
	debug("enabled: %d\n", priv->enabled);

	/* how many ns does apb clock elapse */
	pwm_clk_ns = NS_1 / priv->freq;

	debug("pwm_clk_ns: %u\n", pwm_clk_ns);

	/* duty_cycle should be less than or equal to period */
	if (duty_ns > period_ns)
		return -EINVAL;

	period_data = div_u64(period_ns, pwm_clk_ns);

	if (!priv->enabled)
		/* if disabled, just set duty_data to 0, which means low level always */
		duty_data = 0;
	else
		/* calculate duty count */
		duty_data = div_u64(duty_ns, pwm_clk_ns);

	debug("period_data: %u, duty_data: %u\n",
	      period_data, duty_data);

	data_lrc = period_data;

	data_hrc = duty_data;

	/* set hrc */
	reg_addr = REG_PTC_RPTC_HRC(priv->regs, channel);
	iowrite32(data_hrc, reg_addr);

	debug("%s: reg_addr:%p, data:%u\n",
	      __func__, reg_addr,
	      ioread32(REG_PTC_RPTC_HRC(priv->regs, channel)));

	/* set lrc */
	reg_addr = REG_PTC_RPTC_LRC(priv->regs, channel);
	iowrite32(data_lrc, reg_addr);

	debug("%s: reg_addr:%p, data:%u\n",
	      __func__, reg_addr,
	      ioread32(REG_PTC_RPTC_LRC(priv->regs, channel)));

	/* clear REG_RPTC_CNTR after setting period & duty_cycle */
	reg_addr = REG_PTC_RPTC_CNTR(priv->regs, channel);
	iowrite32(0, reg_addr);

	/* enable PWM output driver */
	/* bit 0 = (EN) to start RPTC_CNTR */
	/* bit 1 = (ECLK) use ptc_ecgt to increment RPTC_CNTR */
	/* bit 3 = (OE) enable PWM output driver */
	reg_addr = REG_PTC_RPTC_CTRL(priv->regs, channel);

	val = readl(REG_PTC_RPTC_CTRL(priv->regs, channel));
	val |= BIT(0) | BIT(1) | BIT(3);

	writel(val, reg_addr);

	return 0;
};

static int starfive_pwm_set_enable(struct udevice *dev, uint channel, bool enable)
{
	struct starfive_pwm_priv *priv = dev_get_priv(dev);
	struct starfive_pwm_regs *reg_addr = &priv->data->regs;
	u32 val = 0;

	val = readl(priv->regs);

	if (enable) {
		val |= BIT(channel);
		priv->enabled = 1;
	} else {
		val &= ~BIT(channel);
		priv->enabled = 0;

		/* disable PWM output driver */
		reg_addr = REG_PTC_RPTC_CTRL(priv->regs, channel);

		val = readl(REG_PTC_RPTC_CTRL(priv->regs, channel));
		val &= ~BIT(3);

		writel(val, reg_addr);
	}

	debug("Enabled: %d\n", priv->enabled);
	writel(val, priv->regs);

	return 0;
};

static int starfive_pwm_of_to_plat(struct udevice *dev)
{
	struct starfive_pwm_priv *priv = dev_get_priv(dev);

	priv->regs = dev_read_addr_ptr(dev);

	return 0;
}

static int starfive_pwm_probe(struct udevice *dev)
{
	struct starfive_pwm_priv *priv = dev_get_priv(dev);
	struct clk clk;
	int ret = 0;

	ret = clk_get_by_index(dev, 0, &clk);
	if (ret < 0) {
		debug("%s get clock fail!\n", __func__);
		return -EINVAL;
	}

	priv->freq = clk_get_rate(&clk);
	debug("Clock frequency: %ld\n", priv->freq);

	priv->data = (struct starfive_pwm_data *)dev_get_driver_data(dev);

	return 0;
};

static const struct pwm_ops starfive_pwm_ops = {
	.set_config	= starfive_pwm_set_config,
	.set_enable	= starfive_pwm_set_enable,
};

static const struct starfive_pwm_data pwm_data = {
	.regs = {
		.cntr = 0x00,
		.hrc = 0x04,
		.lrc = 0x08,
		.ctrl = 0x0C,
	},
};

static const struct udevice_id starfive_pwm_ids[] = {
	{ .compatible = "starfive,jhb100-pwm", .data = (ulong)&pwm_data},
	{ }
};

U_BOOT_DRIVER(pwm_starfive) = {
	.name	= "pwm_starfive",
	.id	= UCLASS_PWM,
	.of_match = starfive_pwm_ids,
	.ops	= &starfive_pwm_ops,
	.of_to_plat	= starfive_pwm_of_to_plat,
	.probe		= starfive_pwm_probe,
	.priv_auto	= sizeof(struct starfive_pwm_priv),
};
