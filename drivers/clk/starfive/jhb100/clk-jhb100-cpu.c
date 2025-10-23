// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 StarFive Technology Co., Ltd.
 *
 */

 #include "clk.h"
 #include "clk-starfive-common.h"
 #include <dt-bindings/clock/starfive,jhb100-crg.h>
 #include <linux/clk-provider.h>

static struct clk_info cpucrg_clk_info[] = {
	{ JHB100_CPUCLK_MAIN_ICG_EN_CPUSS_HEARTBEAT,	"main_icg_en_cpuss_heartbeat",
		"osc",		NULL,	CLK_GATE,	0 },
};

static int jhb100_cpucrg_probe(struct udevice *dev)
{
	void __iomem *reg = (void __iomem *)dev_read_addr_ptr(dev);

	starfive_clk_init(reg, cpu, cpucrg_clk_info, ARRAY_SIZE(cpucrg_clk_info));

	return 0;
}

JHB100_CLK_OF_XLATE(cpu);

JHB100_CLK_OPS(cpu);

static const struct udevice_id jhb100_cpucrg_match[] = {
	{ .compatible = "starfive,jhb100-cpucrg" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(cpucrg) = {
	.name = "clk-starfive-jhb100-cpu",
	.id = UCLASS_CLK,
	.of_match = jhb100_cpucrg_match,
	.probe = jhb100_cpucrg_probe,
	.ops = &jhb100_cpu_clk_ops,
	.bind = jhb100_clk_bind,
	.flags = DM_FLAG_PRE_RELOC,
};
