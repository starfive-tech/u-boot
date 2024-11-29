// SPDX-License-Identifier: (GPL-2.0 OR MIT)
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#include <dm.h>
#include <env.h>
#include <fdt_support.h>
#include <linux/libfdt.h>

#if IS_ENABLED(CONFIG_MISC_INIT_R)
bool is_dma_coherent(int node)
{
	const void *fdt = gd->fdt_blob;

	return fdt_get_property(fdt, node, "dma-coherent", NULL) != NULL;
}

int misc_init_r(void)
{
	const void *fdt = gd->fdt_blob;
	const char *compatible = NULL;
	int node, nodeoffset;

	node = fdt_path_offset(fdt, "/soc");
	if (node < 0) {
		printf("Failed to find device node: %d\n", node);
		return node;
	}

	static const char * const compatibles[] = {
		"starfive,dubhe-70",
		"starfive,dubhe-80",
		"starfive,dubhe-83",
		"starfive,dubhe-90"
	};

	for (int i = 0; i < ARRAY_SIZE(compatibles); i++) {
		nodeoffset = fdt_node_offset_by_compatible(fdt, -1, compatibles[i]);
		if (nodeoffset >= 0) {
			compatible = compatibles[i];
			break;
		}
	}

	if (nodeoffset < 0) {
		printf("No compatible node found.\n");
		return nodeoffset;
	}

	if (strcmp(compatible, "starfive,dubhe-90") == 0) {
		env_set("dubhe_plat", "dubhe-90");
	} else if (strcmp(compatible, "starfive,dubhe-83") == 0) {
		env_set("dubhe_plat", "dubhe-83");
	} else if (strcmp(compatible, "starfive,dubhe-80") == 0) {
		env_set("dubhe_plat", "dubhe-80");
	} else if (strcmp(compatible, "starfive,dubhe-70") == 0) {
		if (is_dma_coherent(node))
			env_set("dubhe_plat", "dubhe-70s");
		else
			env_set("dubhe_plat", "dubhe-70a");
	} else {
		printf("No compatible node found.\n");
		return -1;
	}

	return 0;
}
#endif

int board_init(void)
{
	return 0;
}