// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2021-2023 StarFive Technology Co., Ltd.
 *
 */

#include <dm/uclass.h>
#include <dm/device.h>
#include <hang.h>
#include <misc.h>
#include <asm/io.h>
#include <asm/sbi.h>
#include <asm/arch/ap_core.h>
#include <asm/arch/saif_init.h>
#include <asm/arch/secure_vab.h>

void board_fit_image_post_process(const void *fit, int node, void **p_image,
				  size_t *p_size)
{
	/* TODO: BIF authentication should be placed here */
#ifndef CONFIG_SPL_BUILD
	/* Important that FDT is modified after authentication */
	/* Assign new pointer to retain wherever pointed by p_image  */
	void *payld = *p_image;

	/* Check CPU nodes */
	int cpus_offset, tmp, idx;

	cpus_offset = fdt_path_offset(payld, "/cpus");
	if (cpus_offset < 0)
		return;

	for (tmp = fdt_first_subnode(payld, cpus_offset), idx = 0;
	     tmp >= 0;
	     tmp = fdt_next_subnode(payld, tmp)) {
		const char *compat;
		compat = fdt_getprop(payld, tmp,
				     "compatible", NULL);
		if (!compat)
			continue;
		/* Add status properties if not present */
		if (strcmp(compat, "starfive,dubhe-70") == 0)
		{
			if (GET_SOC_OTP_AP_CORE_STAT(idx))
				fdt_setprop_string(payld, tmp,
						   "status", "disabled");
			idx++;
		}

		/* We know we have 4 AP cores, this break save processing time */
		if (idx > 3)
			break;
	}
#endif
}
