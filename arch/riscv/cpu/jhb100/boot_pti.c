// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */

#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/rpmi-mpxy-sec.h>
#include <linux/bitops.h>
#include <dm.h>
#include <log.h>
#include <rand.h>
#include <spl.h>

#define GET_SPEC(id, spec)	\
	const struct request_spec *(spec) = get_request_spec_by_id(id); \
	if (!spec) { \
		printf("Error: Invalid request_id\n"); \
		return -EINVAL; \
	}

#define GET_BMCFW_INFO(op, part_type, boot_src, img_type, resp_data)	\
	GET_SPEC(GET_BMCFW_INFO, spec); \
	u32 resp_data[spec->resp_size / sizeof(u32)]; \
	memset(resp_data, 0, spec->resp_size); \
	u32 flags = (op) | \
		    (part_type) << GET_BMCFW_INFO_PARTITION_TYPE_SHIFT | \
		    (boot_src) << GET_BMCFW_INFO_BOOT_SRC_REQ_SHIFT | \
		    (img_type) << GET_BMCFW_INFO_IMG_TYPE_SHIFT; \
	int ret = starfive_sec_rx_tx(spec, &flags, resp_data, NULL, 0, NULL, 0, false); \
	if (ret) \
		return ret; \
	if (resp_data[0]) \
		return resp_data[0]

int starfive_get_partition_num(int boot_src, int part_type, int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	switch (boot_src) {
	case BOOT_SRC_SFC:
		break;
	case BOOT_SRC_EMMC: {
		/* Send RPMI/MPXY message via mailbox */
		GET_BMCFW_INFO(GET_CURRENT_PARTITION, part_type, boot_src, img_type, resp_data);

		return emmc_partition_map[resp_data[1] & GET_BMCFW_INFO_EMMC_UFS_PARTITION_MASK];
	}
	default:
		printf("Unknown boot source\n");
	}

	return -EINVAL;
}

int starfive_get_partition_offset(int boot_src, int part_type, int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	switch (boot_src) {
	case BOOT_SRC_SFC:
	case BOOT_SRC_EMMC: {
		/* Send RPMI/MPXY message via mailbox */
		GET_BMCFW_INFO(GET_CURRENT_PARTITION, part_type, boot_src, img_type, resp_data);

		return boot_src == BOOT_SRC_EMMC ? resp_data[2] / MMC_BLK_SIZE : resp_data[2];
	}
	default:
		printf("Unknown boot source\n");
	}

	return -EINVAL;
}

int starfive_get_sfc_cs_line_num(void)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE)) {
		printf("fn(): %s\n", __func__);
		if (IS_ENABLED(CONFIG_RANDOMIZED_TEST_PATTERN)) {
			int a = rand();
			int b = rand();

			if (a < b)
				return 2;
			return 1;
		}
	}

	/** If CS1 is present, Golden partition is stored in CS1 */
	if (starfive_get_sfc_cs(PT_GOLDEN, IMG_TYPE_UBOOT_PROPER) == 1)
		return 2;

	return 1;
}

int starfive_get_sfc_cs(int part_type, int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);

	if (part_type >= PT_TYPE_MAX || img_type >= IMG_TYPE_MAX)
		return -EINVAL;

	/* Send RPMI/MPXY message via mailbox */
	GET_BMCFW_INFO(GET_CURRENT_PARTITION, part_type, BOOT_SRC_SFC, img_type, resp_data);

	return (resp_data[1] & GET_BMCFW_INFO_SFC_CS_NUM_MASK) >> GET_BMCFW_INFO_SFC_CS_NUM_SHIFT;
}

int starfive_req_img_auth_storage(int boot_src, int part_type, int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);

	if (part_type >= PT_TYPE_MAX)
		return -EINVAL;
#ifdef CONFIG_STARFIVE_JHB100_SECURE_VAB_AUTH
	/* Send MPXY message via mailbox */
	GET_SPEC(SECBOOT_VERIFY_ROFS, spec);

	u32 resp_data[spec->resp_size / sizeof(u32)];

	memset(resp_data, 0, spec->resp_size);

	u32 flags = part_type |
		    boot_src << SECBOOT_VERIFY_ROFS_BOOT_SRC_REQ_SHIFT;

	int ret = starfive_sec_rx_tx(spec, &flags, resp_data, NULL, 0, NULL, 0, false);

	if (ret)
		return ret;

	return resp_data[0];
#else
	return 0;
#endif
}

// TODO: Remove this. Not required anymore
int starfive_req_img_auth_memory(int boot_src, int part_type, int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	// TODO: RPMI service to authenticate image loaded to memory
	return 0;
}

int starfive_pre_os_boot_notify(int part_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);

	/* Send MPXY message via mailbox to get partition */
	GET_SPEC(PRE_OS_BOOT_NOTIFY, spec);

	u32 resp_data[spec->resp_size / sizeof(u32)];

	memset(resp_data, 0, spec->resp_size);
	int ret = starfive_sec_rx_tx(spec, &part_type, resp_data, NULL, 0, NULL, 0, false);

	if (ret)
		return ret;

	return resp_data[0];
}

void starfive_set_boot_ctrl_reg(int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	writel(img_type, (void *)BOOT_CTRL_REG_ADDR);
}

void starfive_set_boot_stat_reg(int boot_src, int part_type, int img_type)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	// TODO: Sync with FW
}
