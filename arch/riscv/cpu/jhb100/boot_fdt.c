/* SPDX-License-Identifier: GPL-2.0+ */
/**
  ******************************************************************************
  * @file  boot_fdt.c
  * @author  WeiSheng Ch'ng <weisheng.chng@starfivetech.com>
  * @version  V1.0
  * @date  15/08/2024
  * @brief
  ******************************************************************************
  * @copy
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 2025 Shanghai StarFive Technology Co., Ltd.
  */

#include <dm/ofnode.h>
#include <asm/arch/rpmi-mpxy-sec.h>

#define DRAM_AP_BASE_ADDR	0x40000000
#define DRAM_512_MB_SIZE	0x20000000

#define GET_SPEC_FOR_DDR(id, spec)	\
	const struct request_spec *(spec) = get_request_spec_by_id(id); \
	if (!spec) { \
		printf("Error: Invalid request_id\n"); \
		return -EINVAL; \
	}

int jhb100_fdt_fixup(void *blob)
{
	int node;
	fdt32_t reg[4];
	reg[0] = cpu_to_fdt32(0x00000000);
	reg[1] = cpu_to_fdt32(DRAM_AP_BASE_ADDR);

	GET_SPEC_FOR_DDR(GET_DRAM_INFO, spec);
	u32 resp_data[spec->resp_size / sizeof(u32)];
	u32 flg_bitmap = GET_DRAM_INFO_DRAM_SIZE_FLAG;

	memset(resp_data, 0, spec->resp_size);
	node = fdt_path_offset(blob, "/memory");
	if (node < 0)
		return 0;

	/* Send RPMI/MPXY message via mailbox */
	if (starfive_sec_rx_tx(spec, &flg_bitmap, resp_data, NULL, 0, NULL, 0, false)) {
		printf("WARNING: can't query DDR size\n");
		goto warning_log;
	}

	if (resp_data[0]) {
		printf("WARNING: DDR size query respond failed\n");
		goto warning_log;
	}

	reg[2] = cpu_to_fdt32((resp_data[2] & GET_DRAM_INFO_LOW_32BIT_ADDR_MASK));
	reg[3] = cpu_to_fdt32((resp_data[1] & GET_DRAM_INFO_LOW_32BIT_ADDR_MASK));
	/* If returned DDR size is invalid, retain whatever set in DTB */
	if ((!reg[2]) && (reg[3] < cpu_to_fdt32(DRAM_512_MB_SIZE))) {
		printf("WARNING: Invalid DDR size query returned, retain DTB config\n");
		goto warning_log;
	}

	node = fdt_setprop(blob, node, "reg", reg, sizeof(reg));
	if (node < 0)
		goto warning_log;

	return 0;
warning_log:
	printf("WARNING: can't set %s from node %s\n", "reg", "memory");	
	return 0;
}
