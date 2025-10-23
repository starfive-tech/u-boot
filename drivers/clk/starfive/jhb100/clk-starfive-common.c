// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	ZhiWei Lim <zhiwei.lim@starfivetech.com>
 *
 */

 #include "clk-starfive-common.h"
 #include <linux/clk-provider.h>
 #include <dt-bindings/clock/starfive,jhb100-crg.h>

DECLARE_GLOBAL_DATA_PTR;

static struct clk *starfive_clk_mux(void __iomem *reg, const char *name, unsigned int offset,
				    u8 width, const char * const *parent_names, u8 num_parents)
{
	return clk_register_mux(NULL, name, parent_names, num_parents, 0, reg + offset,
				STARFIVE_CLK_MUX_SHIFT, width, 0);
}

static struct clk *starfive_clk_gate(void __iomem *reg, const char *name, const char *parent_name,
				     unsigned int offset)
{
	return clk_register_gate(NULL, name, parent_name, 0, reg + offset,
				 STARFIVE_CLK_ENABLE_SHIFT, 0, NULL);
}

static struct clk *starfive_clk_inv(void __iomem *reg, const char *name, const char *parent_name,
				    unsigned int offset)
{
	return clk_register_gate(NULL, name, parent_name, 0, reg + offset,
				STARFIVE_CLK_INVERT_SHIFT, 0, NULL);
}

static struct clk *starfive_clk_divider(void __iomem *reg, const char *name,
					const char *parent_name, unsigned int offset, u8 width)
{
	return clk_register_divider(NULL, name, parent_name, 0, reg + offset, 0, width,
				    CLK_DIVIDER_ONE_BASED);
}

struct clk *starfive_clk_fixed_factor(const char *name, const char *parent_name,
				      unsigned int mult, unsigned int div)
{
	return clk_register_fixed_factor(NULL, name, parent_name, 0, mult, div);
}

static struct clk *starfive_clk_composite(void __iomem *reg, const char *name,
					  const char * const *parent_names,
					  unsigned int num_parents, unsigned int offset,
					  unsigned int mux_width, unsigned int gate_width,
					  unsigned int div_width)
{
	struct clk *clk = ERR_PTR(-ENOMEM);
	struct clk_divider *div = NULL;
	struct clk_gate *gate = NULL;
	struct clk_mux *mux = NULL;
	int mask_arry[4] = {0x1, 0x3, 0x7, 0xF};
	int mask;

	if (mux_width) {
		if (mux_width > 4)
			goto fail;
		else
			mask = mask_arry[mux_width - 1];

		mux = kzalloc(sizeof(*mux), GFP_KERNEL);
		if (!mux)
			goto fail;

		mux->reg = reg + offset;
		mux->mask = mask;
		mux->shift = STARFIVE_CLK_MUX_SHIFT;
		mux->num_parents = num_parents;
		mux->flags = 0;
		mux->parent_names = parent_names;
	}

	if (gate_width) {
		gate = kzalloc(sizeof(*gate), GFP_KERNEL);

		if (!gate)
			goto fail;

		gate->reg = reg + offset;
		gate->bit_idx = gate_width;
		gate->flags = 0;
	}

	if (div_width) {
		div = kzalloc(sizeof(*div), GFP_KERNEL);
		if (!div)
			goto fail;

		div->reg = reg + offset;
		div->shift = STARFIVE_CLK_DIV_SHIFT;
		div->width = div_width;
		div->flags = CLK_DIVIDER_ONE_BASED;
		div->table = NULL;
	}

	clk = clk_register_composite(NULL, name, parent_names, num_parents, &mux->clk,
				     &clk_mux_ops, &div->clk, &clk_divider_ops,
				     &gate->clk, &clk_gate_ops, 0);

	if (IS_ERR(clk))
		goto fail;

	return clk;

fail:
	kfree(gate);
	kfree(div);
	kfree(mux);
	return ERR_CAST(clk);
}

static struct clk *starfive_clk_fix_parent_composite(void __iomem *reg, const char *name,
						     const char *parent_names, unsigned int offset,
						     unsigned int mux_width,
						     unsigned int gate_width,
						     unsigned int div_width)
{
	const char * const *parents;

	parents = &parent_names;

	return starfive_clk_composite(reg, name, parents, 1, offset,
				      mux_width, gate_width, div_width);
}

static struct clk *starfive_clk_fixed_rate(const char *name)
{
	const fdt32_t *prop;
	char node[150];
	int offset, len;
	u32 freq;

	snprintf(node, sizeof(node), "/%s", name);

	offset = fdt_path_offset(gd->fdt_blob, node);
	if (offset < 0) {
		printf("FDT node '%s' not found\n", name);
		return ERR_PTR(-ENODEV);
	}

	prop = fdt_getprop(gd->fdt_blob, offset, "clock-frequency", &len);
	if (!prop || len != sizeof(fdt32_t)) {
		printf("clock-frequency not found or invalid in '%s'\n", name);
		return ERR_PTR(-EINVAL);
	}

	freq = fdt32_to_cpu(*prop);

	return clk_register_fixed_rate(NULL, name, freq);
}

unsigned long starfive_clk_id_trans(enum clk_type_t type, unsigned long id)
{
	switch (type) {
	case sys:
		return JHB100_SYS_ID_TRANS(id);
	case sys1:
		return JHB100_SYS1_ID_TRANS(id);
	case sys2:
		return JHB100_SYS2_ID_TRANS(id);
	case per0:
		return JHB100_PER0_ID_TRANS(id);
	case per1:
		return JHB100_PER1_ID_TRANS(id);
	case per2:
		return JHB100_PER2_ID_TRANS(id);
	case per3:
		return JHB100_PER3_ID_TRANS(id);
	case usb:
		return JHB100_USB_ID_TRANS(id);
	case cpu:
		return JHB100_CPU_ID_TRANS(id);
	default:
		debug("Invalid id: %lu\n", id);
		return 0;
	}
}

void starfive_clk_init(void __iomem *reg, enum clk_type_t type,
		       const struct clk_info *init_data, unsigned long init_data_size)
{
	for (unsigned long i = 0; i < init_data_size; i++) {
		switch (init_data[i].component) {
		case CLK_GATE:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_gate(reg, init_data[i].name,
						 init_data[i].parent_name,
						 OFFSET(init_data[i].id)));
			break;
		case CLK_INV:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_inv(reg, init_data[i].name,
						init_data[i].parent_name,
						OFFSET(init_data[i].id)));
			break;
		case CLK_MUX:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_mux(reg, init_data[i].name,
						OFFSET(init_data[i].id),
						1, init_data[i].parent_names,
						MAX_NUM_PARENTS));
			break;
		case CLK_DIVIDER:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_divider(reg, init_data[i].name,
						    init_data[i].parent_name,
						    OFFSET(init_data[i].id),
						    init_data[i].div_width));
			break;
		case CLK_MDIV:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_composite(reg, init_data[i].name,
						      init_data[i].parent_names,
						      MAX_NUM_PARENTS, OFFSET(init_data[i].id),
						      1, 0, init_data[i].div_width));
			break;
		case CLK_GDIV:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_fix_parent_composite(reg, init_data[i].name,
								 init_data[i].parent_name,
								 OFFSET(init_data[i].id), 0,
								 STARFIVE_CLK_ENABLE_SHIFT,
								 init_data[i].div_width));
			break;
		case CLK_IDIV:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_fix_parent_composite(reg, init_data[i].name,
								 init_data[i].parent_name,
								 OFFSET(init_data[i].id), 0,
								 STARFIVE_CLK_INVERT_SHIFT,
								 init_data[i].div_width));
			break;
		case CLK_GMUX:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_composite(reg, init_data[i].name,
						      init_data[i].parent_names, MAX_NUM_PARENTS,
						      OFFSET(init_data[i].id), 1,
						      STARFIVE_CLK_ENABLE_SHIFT, 0));
			break;
		case CLK_COMPOSITE:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_composite(reg, init_data[i].name,
						      init_data[i].parent_names, MAX_NUM_PARENTS,
						      OFFSET(init_data[i].id), 1,
						      STARFIVE_CLK_ENABLE_SHIFT,
						      init_data[i].div_width));
			break;
		case CLK_FIXED:
			clk_dm(starfive_clk_id_trans(type, init_data[i].id),
			       starfive_clk_fixed_rate(init_data[i].name));
			break;
		default:
			break;
		}
	}
}

int jhb100_clk_bind(struct udevice *dev)
{
	/* The reset driver does not have a device node, so bind it here */
	return device_bind_driver_to_node(dev, "starfive_reset", dev->name,
					  dev_ofnode(dev), NULL);
}

int jhb100_clk_check_parent(const struct driver *parent_drv)
{
	int ret;
	struct udevice *parent;

	ret = uclass_get_device_by_driver(UCLASS_CLK, parent_drv, &parent);

	return ret ? ret : (parent ? 0 : -ENOENT);
}
