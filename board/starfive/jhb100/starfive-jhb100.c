/* SPDX-License-Identifier: GPL-2.0+ */
/**
  ******************************************************************************
  * @file  jhb100.c
  * @author  StarFive Technology
  * @version  V1.0
  * @date  25/04/2024
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
  * COPYRIGHT 2024 Shanghai StarFive Technology Co., Ltd.
  */

#include <asm/arch/boot_env.h>
#include <asm/arch/boot_fdt.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/boot_mapping.h>
#include <asm/arch/starfive_reset.h>
#include <asm/arch/bootcmd_restore.h>
#include <dm/ofnode.h>
#include <env.h>
#include <env_internal.h>
#include <init.h>
#include <linux/delay.h>
#include <spl.h>
#include <common.h>
#include <fdt_support.h>

static int env_changed_id;

int board_init(void)
{
	/* Required to perform early initialization
	*  in order to start watchdog successfully
	*/
	arch_early_init_r();

	return 0;
}

enum env_location env_get_location(enum env_operation op, int prio)
{
	int boot_mode = GET_BOOT_SRC;

	if (prio) {
		debug("Could not find persistent storage\n");
		return ENVL_UNKNOWN;
	}

	switch (boot_mode) {
	case BOOT_SRC_SFC:
		debug("Boot source: SPI flash\n");
		if (IS_ENABLED(CONFIG_ENV_IS_IN_SPI_FLASH))
			return ENVL_SPI_FLASH;
		break;
	case BOOT_SRC_EMMC:
		debug("Boot source: eMMC\n");
		if (IS_ENABLED(CONFIG_ENV_IS_IN_FAT))
			return ENVL_FAT;
		if (IS_ENABLED(CONFIG_ENV_IS_IN_MMC))
			return ENVL_MMC;
		break;
	case BOOT_SRC_UFS:
		debug("Boot source: UFS\n");
		if (IS_ENABLED(CONFIG_ENV_IS_IN_FAT))
			return ENVL_FAT;
		if (IS_ENABLED(CONFIG_ENV_IS_IN_MMC))
			return ENVL_MMC;
		break;
	default:
		printf("Could not find persistent storage for environment\n");
		break;
	}

	/* Define this based on priority of the persistent storage to choose, for now
	 * we choose SPI flash > MMC > FAT
	 */
	if (IS_ENABLED(CONFIG_ENV_IS_IN_SPI_FLASH))
		return ENVL_SPI_FLASH;
	if (IS_ENABLED(CONFIG_ENV_IS_IN_FAT))
		return ENVL_FAT;
	if (IS_ENABLED(CONFIG_ENV_IS_IN_MMC))
		return ENVL_MMC;

	/* If CONFIG_ENV_IS_NOWHERE is enabled and no other config is enabled,
	 * this function falls back to here
	 */
	return ENVL_NOWHERE;
}

static int update_partition_reg(void *fdt, int flash_off,
				const char *label, uint32_t offset, uint32_t size)
{
	int partitions_off, part_off;
	const char *prop;
	int len;

	partitions_off = fdt_subnode_offset(fdt, flash_off, "partitions");
	if (partitions_off < 0)
		return partitions_off;

	fdt_for_each_subnode(part_off, fdt, partitions_off) {
		prop = fdt_getprop(fdt, part_off, "label", &len);
		if (prop && strcmp(prop, label) == 0) {
			uint32_t reg[2];
			reg[0] = cpu_to_fdt32(offset);
			reg[1] = cpu_to_fdt32(size);
			printf("  -> Updating '%s' reg = <%#x %#x>\n",
			       label, offset, size);
			return fdt_setprop(fdt, part_off, "reg", reg, sizeof(reg));
		}
	}

	printf("  !! Partition '%s' not found\n", label);
	return -ENOENT;
}

/* Helper to rename by offset */
static int rename_partition_by_offset(void *fdt, int flash_off,
                                      uint32_t match_off,
                                      const char *new_label)
{
	int partitions_off, part_off;
	const fdt32_t *reg;
	int len;

	partitions_off = fdt_subnode_offset(fdt, flash_off, "partitions");
	if (partitions_off < 0) {
		return partitions_off;
	}

	fdt_for_each_subnode(part_off, fdt, partitions_off) {
		reg = fdt_getprop(fdt, part_off, "reg", &len);
		if (reg && len >= 8) {
			uint32_t off = fdt32_to_cpu(reg[0]);
			if (off == match_off) {
				const char *old = fdt_getprop(fdt, part_off, "label", NULL);
				printf("  -> Renaming partition at offset %#x: '%s' -> '%s'\n",
				       off, old ? old : "(none)", new_label);
				return fdt_setprop_string(fdt, part_off, "label", new_label);
			}
		}
	}

	printf("  !! No partition found at offset %#x for rename to '%s'\n", match_off, new_label);
	return -ENOENT;
}

int jhb100_fdt_sfc_fixup(void *fdt)
{
	int sfc0_off, flash0_off, flash1_off, partitions_off;
	int part_off;
	int ret;

	/* Make sure we can modify the FDT (expand if needed) */
	ret = fdt_open_into(fdt, fdt, fdt_totalsize(fdt) + 8192);
	if (ret) {
		printf("Failed to expand FDT: %s\n", fdt_strerror(ret));
		return ret;
	}

	/* Get sfc0 node, try under soc/ */
	sfc0_off = fdt_path_offset(fdt, "/sfc0");
	if (sfc0_off < 0)
		sfc0_off = fdt_path_offset(fdt, "/soc/bus_nioc/spi@18000000");
	if (sfc0_off < 0) {
		printf("sfc0 node not found\n");
		return sfc0_off;
	}

	/* Locate flash@0 and flash@1 */
	flash0_off = fdt_subnode_offset(fdt, sfc0_off, "flash@0");
	flash1_off = fdt_subnode_offset(fdt, sfc0_off, "flash@1");

	uint32_t part_size = starfive_get_sfc_part_size(PT_TEMP, IMG_TYPE_KERNEL);
	uint32_t kernel_fit_active_off =
		starfive_get_partition_offset(BOOT_SRC_SFC,
					      PT_ACTIVE,
					      IMG_TYPE_KERNEL);
	uint32_t rootfs_active_off = kernel_fit_active_off + SIXTEEN_MB;
	uint32_t kernel_fit_golden_off =
		starfive_get_partition_offset(BOOT_SRC_SFC,
					      PT_GOLDEN,
					      IMG_TYPE_KERNEL);
	uint32_t rootfs_golden_off = kernel_fit_golden_off + SIXTEEN_MB;
	uint32_t kernel_fit_temp_off =
		starfive_get_partition_offset(BOOT_SRC_SFC,
					      PT_TEMP,
					      IMG_TYPE_KERNEL);
	uint32_t rootfs_temp_off = kernel_fit_temp_off + SIXTEEN_MB;

	uint32_t kernel_fit_size = SIXTEEN_MB;
	uint32_t rootfs_size = part_size - SIXTEEN_MB;

	uint32_t a_t_kernel_off;
	uint32_t a_t_rofs_off;
	uint32_t g_kernel_off;
	uint32_t g_rofs_off;

	if (kernel_fit_active_off == kernel_fit_temp_off) {
		a_t_kernel_off = kernel_fit_active_off;
		a_t_rofs_off = rootfs_active_off;
		g_kernel_off = kernel_fit_golden_off;
		g_rofs_off = rootfs_golden_off;
	} else if (kernel_fit_active_off == kernel_fit_golden_off) {
		a_t_kernel_off = kernel_fit_active_off;
		a_t_rofs_off = rootfs_active_off;
		g_kernel_off = kernel_fit_temp_off;
		g_rofs_off = rootfs_temp_off;
	} else {
		a_t_kernel_off = kernel_fit_temp_off;
		a_t_rofs_off = rootfs_temp_off;
		g_kernel_off = kernel_fit_active_off;
		g_rofs_off = rootfs_active_off;
	}

	/* Update labels based on CS and offset */
	int cs_active = starfive_get_sfc_cs(PT_ACTIVE, IMG_TYPE_KERNEL);
	int cs_golden = starfive_get_sfc_cs(PT_GOLDEN, IMG_TYPE_KERNEL);
	int cs_temp   = starfive_get_sfc_cs(PT_TEMP, IMG_TYPE_KERNEL);

	/* === Case 1: Dual flash mode === */
	if ((starfive_get_sfc_cs(PT_ACTIVE, IMG_TYPE_KERNEL) == CONFIG_SF_CS1) ||
	    (starfive_get_sfc_cs(PT_GOLDEN, IMG_TYPE_KERNEL) == CONFIG_SF_CS1) ||
	    (starfive_get_sfc_cs(PT_TEMP, IMG_TYPE_KERNEL) == CONFIG_SF_CS1)) {
		printf("Detected dual flash mode, keeping both flashes.\n");

		/* flash@0 updates */
		update_partition_reg(fdt, flash0_off,
				     "User Data Area",
				     CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE,
				     part_size - CONFIG_ENV_SIZE);
		update_partition_reg(fdt, flash0_off,
				     "Kernel FIT Active (compressed)",
				     a_t_kernel_off, kernel_fit_size);
		update_partition_reg(fdt, flash0_off,
				     "RootFS Active",
				     a_t_rofs_off, rootfs_size);

		/* flash@1 updates */
		if (flash1_off >= 0) {
			update_partition_reg(fdt, flash1_off,
					     "Kernel FIT Golden (compressed)",
					     g_kernel_off, kernel_fit_size);
			update_partition_reg(fdt, flash1_off,
					     "RootFS Golden",
					     g_rofs_off, rootfs_size);
			update_partition_reg(fdt, flash1_off,
					     "Kernel FIT Temp (compressed)",
					     a_t_kernel_off, kernel_fit_size);
			update_partition_reg(fdt, flash1_off,
					     "RootFS Temp",
					     a_t_rofs_off, rootfs_size);
		} else {
			printf("Warning: flash@1 not found, skipping golden/temp partitions.\n");
		}

		flash0_off = fdt_subnode_offset(fdt, sfc0_off, "flash@0");
		/* flash@0 label updates */
		if (flash0_off >= 0) {
			if (cs_active == CONFIG_SF_DEFAULT_CS) {
				rename_partition_by_offset(fdt, flash0_off, kernel_fit_active_off,
					"Kernel FIT Active (compressed)");
				rename_partition_by_offset(fdt, flash0_off, rootfs_active_off,
					"RootFS Active");
			}
			if (cs_golden == CONFIG_SF_DEFAULT_CS) {
				rename_partition_by_offset(fdt, flash0_off, kernel_fit_golden_off,
					"Kernel FIT Golden (compressed)");
				rename_partition_by_offset(fdt, flash0_off, rootfs_golden_off,
					"RootFS Golden");
			}
			if (cs_temp == CONFIG_SF_DEFAULT_CS) {
				rename_partition_by_offset(fdt, flash0_off, kernel_fit_temp_off,
					"Kernel FIT Temp (compressed)");
				rename_partition_by_offset(fdt, flash0_off, rootfs_temp_off,
					"RootFS Temp");
			}
		}

		flash1_off = fdt_subnode_offset(fdt, sfc0_off, "flash@1");
		/* flash@1 label updates */
		if (flash1_off >= 0) {
			if (cs_active == CONFIG_SF_CS1) {
				rename_partition_by_offset(fdt, flash1_off, kernel_fit_active_off,
					"Kernel FIT Active (compressed)");
				rename_partition_by_offset(fdt, flash1_off, rootfs_active_off,
					"RootFS Active");
			}
			if (cs_golden == CONFIG_SF_CS1) {
				rename_partition_by_offset(fdt, flash1_off, kernel_fit_golden_off,
					"Kernel FIT Golden (compressed)");
				rename_partition_by_offset(fdt, flash1_off, rootfs_golden_off,
					"RootFS Golden");
			}
			if (cs_temp == CONFIG_SF_CS1) {
				rename_partition_by_offset(fdt, flash1_off, kernel_fit_temp_off,
					"Kernel FIT Temp (compressed)");
				rename_partition_by_offset(fdt, flash1_off, rootfs_temp_off,
					"RootFS Temp");
			}
		}

		printf("Partition labels updated based on flash offset and CS (dual flash mode).\n");
		printf("Dual-flash partitions updated successfully.\n");
		return 0;
	}

	/* === Case 2: Single flash mode === */
	printf("Detected single flash mode, converting to single flash layout.\n");

	/* Remove flash@1 if present */
	if (flash1_off >= 0) {
		ret = fdt_del_node(fdt, flash1_off);
		if (ret) {
			printf("Failed to remove flash@1: %s\n", fdt_strerror(ret));
			return ret;
		}
		printf("Removed flash@1 node.\n");
	}

	/* Remove old partitions under flash@0 */
	partitions_off = fdt_subnode_offset(fdt, flash0_off, "partitions");
	if (partitions_off >= 0) {
		fdt_del_node(fdt, partitions_off);
		printf("Removed old partitions.\n");
	}

	/* Rebuild partitions */
	partitions_off = fdt_add_subnode(fdt, flash0_off, "partitions");
	fdt_setprop_string(fdt, partitions_off, "compatible", "fixed-partitions");
	fdt_setprop_u32(fdt, partitions_off, "#address-cells", 1);
	fdt_setprop_u32(fdt, partitions_off, "#size-cells", 1);

	uint32_t current_offset = 0;

	#define ADD_AUTO_PART_WITH_OFFSET(label, size, offset) do { \
		char name[32]; \
		sprintf(name, "partition@%x", offset); \
		part_off = fdt_add_subnode(fdt, partitions_off, name); \
		fdt_setprop_string(fdt, part_off, "label", label); \
		uint32_t reg[2]; \
		reg[0] = cpu_to_fdt32(offset); \
		reg[1] = cpu_to_fdt32(size); \
		fdt_setprop(fdt, part_off, "reg", reg, sizeof(reg)); \
	} while (0)

	/* Define partitions in logical order */
	struct {
		const char *label;
		uint32_t size;
		uint32_t offset;
	} parts[] = {
		{ "Boot Info Active",			0x010000 },
		{ "L0 Firmware Active",			0x080000 },
		{ "L1 Firmware Active",			0x080000 },
		{ "U-Boot SPL Active",			0x080000 },
		{ "U-Boot FIT Active",			0x260000 },
		{ "SFC I2C filter cfg Active",		0x010000 },
		{ "U-Boot Environment",			0x290000 },
		{ "Boot Info Temp",			0x010000 },
		{ "L0 Firmware Temp",			0x080000 },
		{ "L1 Firmware Temp",			0x080000 },
		{ "U-Boot SPL Temp",			0x080000 },
		{ "U-Boot FIT Temp",			0x260000 },
		{ "SFC I2C filter cfg Temp",		0x080000 },
		{ "Kernel FIT Active (compressed)",	kernel_fit_size },
		{ "RootFS Active",			rootfs_size },
		{ "Kernel FIT Temp (compressed)",	kernel_fit_size },
		{ "RootFS Temp",			rootfs_size },
		{ "User Data Area",			0x400000 },
	};

	/* Step 1: Precompute offsets in forward order */
	for (int i = 0; i < (int)(sizeof(parts)/sizeof(parts[0])); i++) {
		parts[i].offset = current_offset;
		current_offset += parts[i].size;
	}

	/* Step 2: Add partitions to FDT in reverse order */
	for (int i = (sizeof(parts)/sizeof(parts[0])) - 1; i >= 0; i--) {
		ADD_AUTO_PART_WITH_OFFSET(parts[i].label, parts[i].size, parts[i].offset);
	}

#undef ADD_AUTO_PART_WITH_OFFSET
	printf("Single-flash partitions rebuilt successfully.\n");

	/* Update labels for single flash */
	flash0_off = fdt_subnode_offset(fdt, sfc0_off, "flash@0");

	if (flash0_off >= 0) {
		if (cs_active == CONFIG_SF_DEFAULT_CS) {
			rename_partition_by_offset(fdt, flash0_off, kernel_fit_active_off,
				"Kernel FIT Active (compressed)");
			rename_partition_by_offset(fdt, flash0_off, rootfs_active_off,
				"RootFS Active");
		}
		if (cs_temp == CONFIG_SF_DEFAULT_CS) {
			rename_partition_by_offset(fdt, flash0_off, kernel_fit_temp_off,
				"Kernel FIT Temp (compressed)");
			rename_partition_by_offset(fdt, flash0_off, rootfs_temp_off,
				"RootFS Temp");
		}
	}

	printf("Single-flash partition labels updated based on offset and CS.\n");
	return 0;
}

void check_fdtmodify(void *blob)
{
	const char *fdtmodify;

	fdtmodify = env_get("fdtmodify");

	if (fdtmodify && strcmp(fdtmodify, "yes") == 0) {
		printf("fdtmodify = yes, modifying device tree\n");
		jhb100_fdt_sfc_fixup(blob);
	}
}

int ft_board_setup(void *blob, struct bd_info *bd)
{
#ifdef CONFIG_STARFIVE_JHB100_QUERY_DDR_INFO
	jhb100_fdt_fixup(blob);
#endif
	check_fdtmodify(blob);
	jhb100_set_mmbi_iopmp_memrange(blob);

	return 0;
}

#ifdef CONFIG_BOARD_LATE_INIT
static void env_get_boot_dev(void)
{
	switch (jhb100_get_boot_device()) {
	case BOOT_DEVICE_SPI:
		env_set("bootdev", "spi");
		break;
	case BOOT_DEVICE_MMC1:
		env_set("mmcdev", "0");
		env_set("bootdev", "mmc1");
		break;
	case BOOT_DEVICE_UFS:
		env_set("bootdev", "ufs");
		break;
	case BOOT_DEVICE_UART:
		env_set("bootdev", "uart");
		break;
	case BOOT_DEVICE_RAM:
		env_set("bootdev", "ram");
		break;
	default:
		env_set("bootdev", "uart");
		break;
	}
}

static int env_get_spi_flash_offs(void)
{
	ofnode node, sbnode0, sbnode1;
	u32 reg[2];

	/* Find flash 0 if available */
	node = ofnode_by_compatible(ofnode_null(), "jedec,spi-nor");
	if (!ofnode_valid(node))
		return log_msg_ret("Cannot find SPI flash 0\n", -ENOENT);

	sbnode0 = ofnode_find_subnode(node, "partitions");
	if (!ofnode_valid(sbnode0))
		return log_msg_ret("Cannot find partition node", -EPERM);

	sbnode1 = ofnode_find_subnode(sbnode0, "partition@8");
	if (!ofnode_valid(sbnode1))
		return log_msg_ret("Cannot find kernel primary node", -EPERM);

	env_set("kernel_fit_spi_prim_off", "0x4200000");
	if (!ofnode_read_u32_array(sbnode1, "reg", reg, 2))
		env_set_hex("kernel_fit_spi_prim_off", (ulong)reg[0]);

	/* Find flash 1 if available */
	node = ofnode_by_compatible(node, "jedec,spi-nor");
	if (!ofnode_valid(node))
		return log_msg_ret("Cannot find SPI flash 1\n", -ENOENT);

	sbnode0 = ofnode_find_subnode(node, "partitions");
	if (!ofnode_valid(sbnode0))
		return log_msg_ret("Cannot find partition node", -EPERM);

	sbnode1 = ofnode_find_subnode(sbnode0, "partition@6");
	if (!ofnode_valid(sbnode1))
		return log_msg_ret("Cannot find kernel secondary node", -EPERM);

	env_set("kernel_fit_spi_sec_off", "0x400000");
	if (!ofnode_read_u32_array(sbnode1, "reg", reg, 2))
		env_set_hex("kernel_fit_spi_sec_off", (ulong)reg[0]);

	return 0;
}

static void env_get_spi_cs(void)
{
	env_set_hex("cs_num", (ulong)CONFIG_SF_DEFAULT_CS);
}

static void env_get_spi_flash_config(void)
{
	env_get_spi_flash_offs();
	env_get_spi_cs();
}

void env_add_bootarg_reset_event(void)
{
	env_filter_add_bootarg(starfive_get_reset_event, "reset_event=", NULL);
	env_changed_id = env_get_id();
}

/* We do critical boot command restoration here in the case user save
 * and then load their custom environment from persistent storages.
 * This will not override any additional custom environments added by user,
 * instead append critical boot command on top of it.
 * However, this overrides critical boot command if added by user.
 */
void env_restore_bootcmd(void)
{
	restore_bootcmd_utils();

	if (IS_ENABLED(CONFIG_ENV_IS_IN_SPI_FLASH))
		restore_bootcmd_sfc();
	if (IS_ENABLED(CONFIG_ENV_IS_IN_FAT))
		restore_bootcmd_emmc();

	env_changed_id = env_get_id();
}

void uboot_starfive_fb_rec_map_handler(void)
{
	int boot_mode = GET_BOOT_SRC;
	int fb_map_reg = starfive_get_fb_rec_map();

	switch (boot_mode) {
	case BOOT_SRC_SFC:
		starfive_fb_rec_map_handler(&fb_map_reg,
					    BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
					    BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
					    FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					    CLEAR);
		break;
	case BOOT_SRC_EMMC:
		starfive_fb_rec_map_handler(&fb_map_reg,
					    BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
					    BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
					    FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					    CLEAR);
		break;
	case BOOT_SRC_UFS:
		starfive_fb_rec_map_handler(&fb_map_reg,
					    BOOT_SRC_PART_UFS_PRIMARY_BIT_POS,
					    BOOT_SRC_PART_UFS_SECONDARY_BIT_POS,
					    FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
					    CLEAR);
		break;
	default:
		return;
	}

	starfive_set_fb_rec_map(fb_map_reg);
}

int board_late_init(void)
{
	env_get_boot_dev();
	env_get_spi_flash_config();
	env_restore_bootcmd();
	/* Add or replace reset_event argument to bootargs */
	env_add_bootarg_reset_event();

	uboot_starfive_fb_rec_map_handler();

	return 0;
}

#ifndef CONFIG_SPL_BUILD
static int last_stage_init(void)
{
	int env_id = env_get_id();
	int boot_mode = GET_BOOT_SRC;

	/* Update only when the environment has changed */
	if (env_changed_id != env_id) {
		env_changed_id = env_id;
		env_save();
	}

	starfive_set_ap_sts_boot_src(BOOTSTG_KERNEL, boot_mode);
	starfive_clear_ap_sts_retry_cnt(BOOTSTG_U_BOOT_SPL);
	starfive_clear_ap_sts_retry_cnt(BOOTSTG_U_BOOT_PROPER);
	starfive_clear_ap_sts_error(BOOTSTG_U_BOOT_SPL);
	starfive_clear_ap_sts_error(BOOTSTG_U_BOOT_PROPER);

	return 0;
}
EVENT_SPY_SIMPLE(EVT_LAST_STAGE_INIT, last_stage_init);
#endif

#endif
