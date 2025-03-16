// SPDX-License-Identifier: GPL-2.0
/*
 * StarFive IO Voltage Domain Driver
 *
 * Ported from linux drivers/soc/starfive/iodomain/io-domain-jhb100.c
 */

#include <dm.h>
#include <dm/device_compat.h>
#include <asm/io.h>

#define IODOMAIN_MAX_NUM	5

/* vsel register values */
enum starfive_reg_value {
	JHB100_VREF_3_3V,	/* 00 = 3.3V */
	JHB100_VREF_2_5V,	/* 01 = 2.5V */
	JHB100_VREF_1_8V,	/* 1X = 1.2V or 1.8V */
};

/* vsel voltage range */
enum starfive_vsel_range {
	JHB100_VREF_VDD1833,	/* 1.8V and 3.3V */
	JHB100_VREF_VDD182533,	/* 1.8V, 2.5V and 3.3V */
};

struct starfive_iodomain_data {
	int vsel_reg_num;
	int vsel_range;
	const char *vsel_names[IODOMAIN_MAX_NUM];
};

static const struct starfive_iodomain_data jhb100_soc_data_sys2 = {
	.vsel_reg_num = 4,
	.vsel_range = JHB100_VREF_VDD1833,
	.vsel_names = {
		"gpiow-vsel",
		"gpiow-vsel",
		NULL,
		NULL,
		NULL,
	},
};

static const struct starfive_iodomain_data jhb100_soc_data_bmcperiph0 = {
	.vsel_reg_num = 5,
	.vsel_range = JHB100_VREF_VDD1833,
	.vsel_names = {
		NULL,
		"gpioe-i3c0-vsel",
		"gpioe-i3c1-vsel",
		"gpioe-i3c2-vsel",
		"gpioe-i3c4-vsel",
	},
};

static const struct starfive_iodomain_data jhb100_soc_data_bmcperiph1 = {
	.vsel_reg_num = 5,
	.vsel_range = JHB100_VREF_VDD1833,
	.vsel_names = {
		"gpioe-spi-vsel",
		"gpioe-qspi0-vsel",
		"gpioe-qspi1-vsel",
		"gpioe-qspi2-vsel",
		NULL,
	},
};

static const struct starfive_iodomain_data jhb100_soc_data_bmcperiph2 = {
	.vsel_reg_num = 1,
	.vsel_range = JHB100_VREF_VDD182533,
	.vsel_names = {
		"gpionw-vsel",
		NULL,
		NULL,
		NULL,
		NULL,
	},
};

static const struct starfive_iodomain_data jhb100_soc_data_bmcperiph3 = {
	.vsel_reg_num = 1,
	.vsel_range = JHB100_VREF_VDD182533,
	.vsel_names = {
		"gpios-vsel",
		NULL,
		NULL,
		NULL,
		NULL,
	},
};

static const struct udevice_id starfive_iodomain_ids[] = {
	{
		.compatible = "starfive,jhb100-sys-pinctrl-systop-sys2",
		.data = (ulong)&jhb100_soc_data_sys2,
	},
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph0",
		.data = (ulong)&jhb100_soc_data_bmcperiph0,
	},
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph1",
		.data = (ulong)&jhb100_soc_data_bmcperiph1,
	},
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph2",
		.data = (ulong)&jhb100_soc_data_bmcperiph2,
	},
	{
		.compatible = "starfive,jhb100-sys-pinctrl-bmcperiph3",
		.data = (ulong)&jhb100_soc_data_bmcperiph3,
	},
	{ }
};

static int starfive_iodomain_bind(struct udevice *dev)
{
	dev_or_flags(dev, DM_FLAG_PROBE_AFTER_BIND);

	return 0;
}

static struct starfive_iodomain_data *jhb100_iodomain_get_cfg(const char *compat)
{
	for (int i = 0; i < ARRAY_SIZE(starfive_iodomain_ids); i++) {
		if (!strcmp(compat, starfive_iodomain_ids[i].compatible))
			return (struct starfive_iodomain_data *)starfive_iodomain_ids[i].data;
	}

	return NULL;
}

static int starfive_iodomain_probe(struct udevice *dev)
{
	struct starfive_iodomain_data *soc_data;
	const char *compat;
	void __iomem *reg;
	int val;

	reg = (void __iomem *)dev_read_addr_index(dev, 0);
	if (IS_ERR(reg))
		return PTR_ERR(reg);

	compat = ofnode_get_property(dev_ofnode(dev), "compatible", NULL);
	if (!compat)
		return -EINVAL;

	soc_data = jhb100_iodomain_get_cfg(compat);
	if (!soc_data)
		return -EINVAL;

	for (int i = 0; i < soc_data->vsel_reg_num; i++) {
		const char *supply_name = soc_data->vsel_names[i];

		if (!supply_name)
			continue;

		/* Read voltage reference from device tree */
		val = dev_read_u32_default(dev, supply_name, JHB100_VREF_3_3V);

		if (val < JHB100_VREF_3_3V || val > JHB100_VREF_1_8V)
			return -EINVAL;

		/* Ensure 2.5V is not selected for VDD1833 range */
		if (soc_data->vsel_range == JHB100_VREF_VDD1833 && val == JHB100_VREF_2_5V)
			return -EINVAL;

		/* Write voltage reference to register */
		writel(val, reg + (i * 4));
	}

	return 0;
}

U_BOOT_DRIVER(starfive_io_domain) = {
	.name = "starfive_io_domain",
	.id = UCLASS_NOP,
	.of_match = starfive_iodomain_ids,
	.probe = starfive_iodomain_probe,
	.bind = starfive_iodomain_bind,
};
