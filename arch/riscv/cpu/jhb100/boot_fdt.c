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
#include <asm/arch/sbi.h>
#include <asm/arch/rpmi-mpxy-sec.h>
#include <asm/rpmi.h>
#include <linux/kernel.h>

#define DRAM_AP_BASE_ADDR	0x40000000
#define DRAM_512_MB_SIZE	0x20000000

#define GET_SPEC_ID(id, spec)	\
	const struct request_spec *(spec) = get_request_spec_by_id(id); \
	if (!spec) { \
		printf("Error: Invalid request_id\n"); \
		return -EINVAL; \
	}

#ifndef CONFIG_SPL_BUILD
#define MAX_MMBI	4

struct mmbi_info {
	const char *compatible;
	u32 id;
	fdt_addr_t addr;
	fdt_size_t size;
};

static struct mmbi_info mmbi_list[MAX_MMBI] = {
	{.compatible = "starfive,jhb100-mmbi-espi", .id = 0},
	{.compatible = "starfive,jhb100-mmbi-espi", .id = 1},
	{.compatible = "starfive,jhb100-mmbi-pcie", .id = 0},
	{.compatible = "starfive,jhb100-mmbi-pcie", .id = 1},
};
#endif

int jhb100_fdt_fixup(void *blob)
{
	int node;
	fdt32_t reg[4];
	reg[0] = cpu_to_fdt32(0x00000000);
	reg[1] = cpu_to_fdt32(DRAM_AP_BASE_ADDR);

	GET_SPEC_ID(GET_DRAM_INFO, spec);
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

#ifdef CONFIG_SPL_BUILD
static int jhb100_parse_reserved_mem(void *fdt, const char *alias, fdt_addr_t *addr,
				     fdt_size_t *size)
{
	const char *path;
	int node;

	if (!addr || !size)
		return -EINVAL;

	path = fdt_get_alias(fdt, alias);
	if (!path)
		return -ENOENT;

	/* Find node through path */
	node = fdt_path_offset(fdt, path);
	if (node < 0) {
		printf("Node for alias '%s' (%s) not found: %d\n",
		       alias, path, node);
		return node;
	}

	/* Read reg property with parent address-cells support */
	fdt_addr_t tmp_addr;
	fdt_size_t tmp_size;

	tmp_addr = fdtdec_get_addr_size_auto_parent(fdt, 0, node, "reg", 0, &tmp_size, false);

	if (tmp_addr == FDT_ADDR_T_NONE) {
		printf("Failed to parse 'reg' for alias '%s'\n", alias);
		return -ENOENT;
	}

	*addr = tmp_addr;
	*size = tmp_size;

	return 0;
}

int jhb100_scp_buffer_parser(void *blob)
{
	int ret;
	fdt_size_t size;
	fdt_addr_t addr;

	ret = jhb100_parse_reserved_mem(blob, "scp_buffer_cache", &addr, &size);
	if (ret)
		return ret;

	GET_SPEC_ID(ASSIGN_MEM_BLOCK, spec);
	u32 resp_data[spec->resp_count];

	memset(resp_data, 0, sizeof(u32) * spec->resp_count);

	u32 req_data[spec->param_count];

	req_data[0] = 0; /* flag */
	req_data[1] = (u64)addr & ADDR_LOW_MASK; /* addr_low */
	req_data[2] = ((u64)addr & ADDR_HIGH_MASK) >> BITS_PER_WORD; /* addr_high */
	req_data[3] = (u32)size; /* size */

	ret = starfive_sec_rx_tx(spec, req_data, resp_data, NULL, 0, NULL, 0, false);
	if (ret)
		return ret;

	if (resp_data[0]) {
		if (resp_data[0] != RPMI_ERR_ALREADY)
			printf("Failed, error: %d\n", resp_data[0]);
	}

	return resp_data[0];
}
#endif

#ifndef CONFIG_SPL_BUILD
static int fdt_find_node_by_compat_and_id(const void *fdt,
					  const char *compat,
					  const char *id_prop,
					  int target_id,
					  int *out_node,
					  u32 *instance_num,
					  u32 *instance_size,
					  u32 *src_addr_offset)
{
	int node = -1;

	if (!fdt || !compat || !id_prop)
		return -EINVAL;

	while ((node = fdt_node_offset_by_compatible(fdt, node, compat)) >= 0) {
		int len;
		const u8 *id = fdt_getprop(fdt, node, id_prop, &len);

		if (!id || len < 1)
			continue;

		if (id[0] != target_id)
			continue;

		if (out_node)
			*out_node = node;

		if (instance_num)
			*instance_num =
				fdtdec_get_uint(fdt, node, "mmbi-instance-num", 0);

		if (instance_size)
			*instance_size =
				fdtdec_get_uint(fdt, node, "mmbi-instance-size", 0);

		if (src_addr_offset)
			*src_addr_offset =
				fdtdec_get_uint(fdt, node, "mmbi-src-addr-offset", 0);

		return 0;
	}

	return -ENODEV;
}

static int parse_mmbi_list(void *fdt)
{
	int ret = 0;

	for (int i = 0; i < MAX_MMBI; i++) {
		int node;
		u32 instance_num = 0, instance_size = 0, src_addr_offset = 0;

		ret = fdt_find_node_by_compat_and_id(fdt,
						     mmbi_list[i].compatible,
						     "mmbi-id",
						     mmbi_list[i].id,
						     &node,
						     &instance_num,
						     &instance_size,
						     &src_addr_offset);
		if (ret)
			goto fail_return;

		int mem_node = fdtdec_lookup_phandle(fdt, node, "memory-region");

		if (mem_node < 0) {
			ret = mem_node;
			goto fail_return;
		}

		fdt_addr_t addr;
		fdt_size_t unused;

		addr = fdtdec_get_addr_size_auto_parent(fdt, 0, mem_node, "reg", 0, &unused, false);

		/* Compute addr range = addr + src_addr_offset */
		mmbi_list[i].addr = addr + src_addr_offset;

		/* Compute size = instance_num * instance_size / 2 */
		mmbi_list[i].size =
			((fdt_size_t)instance_num * instance_size) / 2;
	}

fail_return:
	return ret;
}

void jhb100_set_mmbi_iopmp_memrange(void *blob)
{
	if (parse_mmbi_list(blob))
		return;

	for (int i = 0; i < MAX_MMBI; i++)
		sbi_set_iopmp_host_readonly_memrange(mmbi_list[i].addr, mmbi_list[i].size);

	sbi_set_iopmp_lock();
}
#endif
