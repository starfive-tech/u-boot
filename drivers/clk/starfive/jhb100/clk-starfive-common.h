/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2024 StarFive Technology Co., Ltd.
 * Author:	ZhiWei Lim <zhiwei.lim@starfivetech.com>
 */

 #include <dm.h>
 #include <dm/device.h>
 #include <dm/devres.h>
 #include <dm/lists.h>
 #include "clk.h"

struct clk *starfive_clk_fixed_factor(const char *name, const char *parent_name,
				      unsigned int mult, unsigned int div);
unsigned long starfive_clk_id_trans(enum clk_type_t type, unsigned long id);
void starfive_clk_init(void __iomem *reg, enum clk_type_t type,
		       const struct clk_info *init_data,
		       unsigned long init_data_size);
int jhb100_clk_bind(struct udevice *dev);
int jhb100_clk_check_parent(const struct driver *parent_drv);
