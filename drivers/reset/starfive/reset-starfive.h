/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright 2024 StarFive, Inc <zhiwei.lim@starfivetech.com>
 *
 * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING
 * CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER
 * FOR THEM TO SAVE TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE
 * FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY
 * CLAIMS ARISING FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE
 * BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION
 * WITH THEIR PRODUCTS.
 */

extern const struct reset_ops starfive_reset_ops;

/*
 * struct starfive_reset_priv - private data for Starfive reset driver
 */
struct starfive_reset_priv {
	void __iomem *reg;
	struct starfive_reset_info *starfive_reset_info;
};

struct starfive_reset_info {
	u32 nr_resets;
	u32 assert_offset;
	u32 status_offset;
};
