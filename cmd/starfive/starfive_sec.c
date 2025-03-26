// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

 #include <common.h>
 #include <stdio.h>
 #include <command.h>
 #include <malloc.h>
 #include <u-boot/crc.h>
 #include <env.h>
 #include <dm.h>
 #include <misc.h>
 #include <linux/types.h>
 #include <asm/arch/rpmi-mpxy-sec.h>
 #include <linux/string.h>
 #include <linux/errno.h>
 #include <mailbox.h>
 #include <rpmi/rpmi-srvgrp-uclass.h>
 #include "starfive_sec_spec.h"
 #include <linux/bitfield.h>
 #include <linux/delay.h>
 #include <linux/compat.h>

#define CRC32_SIZE	4
#define CACHE_ALIGN	CONFIG_SYS_CACHELINE_SIZE
void flush_dcache_range(unsigned long start, unsigned long end);
void invalidate_dcache_range(unsigned long start, unsigned long end);

const struct request_spec *get_request_spec_by_id(u32 request_id)
{
	for (int i = 0; i < ARRAY_SIZE(request_specs); i++) {
		if (request_specs[i].request_id == request_id)
			return &request_specs[i];
	}
	return NULL;
}

static u32 calc_data_buf_size(struct request_buf header)
{
	u32 alloc_size = max(header.resp_size, header.auth_msg_size);

	return sizeof(struct request_buf) + header.req_size + ALIGN(alloc_size, 4) +
		      ALIGN(header.external_buf_size, 4) + CRC32_SIZE;
}

/**
 * This function returns an allocated memory region buffer based on the req_spec
 * The caller of this function is expected to free the buffer
 */
static char *prepare_data_buf(const struct request_spec *req_spec, void *tx_params, void *auth_data,
			      u32 auth_size, void *ext_data, u32 ext_size, u32 *data_buf_size)
{
	if (req_spec->need_auth && !auth_size) {
		printf("Error: Missing auth file\n");
		return NULL;
	}

	if (req_spec->has_external_data && !ext_size) {
		printf("Error: Missing ext file\n");
		return NULL;
	}

	/** Create header based on spec */
	struct request_buf header = {
		.request_id = req_spec->request_id,
		.req_size = req_spec->param_count * sizeof(u32),
		.resp_size = req_spec->resp_size,
		.external_buf_size = (req_spec->has_external_data ? ext_size : 0),
		.auth_msg_size = (req_spec->need_auth ? auth_size : 0),
	};

	/** Calculate buffer size */
	u32 buf_size = *data_buf_size = calc_data_buf_size(header);
	char *data_buf = memalign(CACHE_ALIGN, buf_size);

	if (!data_buf)
		return NULL;

	memset(data_buf, 0, buf_size);

	/** Copy header to data_buf */
	memcpy(data_buf, &header, sizeof(struct request_buf));

	size_t offset = sizeof(struct request_buf);
	/** Parse tx_params */
	memcpy(data_buf + offset, tx_params, header.req_size);
	offset += header.req_size;

	/** Parse auth data if exist*/
	if (auth_size > 0)
		memcpy(data_buf + offset, auth_data, header.auth_msg_size);

	/** Offset shift to the larger size */
	offset += max(header.resp_size, header.auth_msg_size);
	/** Parse ext data if exist */
	if (ext_size > 0)
		memcpy(data_buf + offset, ext_data, ext_size);

	/** Calculate CRC32 */
	*(u32 *)(data_buf + buf_size - CRC32_SIZE) = crc32(0, data_buf, sizeof(struct request_buf) +
									header.req_size);
	return data_buf;
}

static void dump_data_buf(const struct request_spec *req_spec, char *buf, char *resp_buf,
			  u32 buf_size)
{
	struct request_buf *data_buf = (struct request_buf *)buf;

	printf("Request ID: 0x%08x\n", data_buf->request_id);
	printf("Request Size: 0x%08x\n", data_buf->req_size);
	printf("Response Size: 0x%08x\n", data_buf->resp_size);
	printf("External Buffer Size: 0x%08x\n", data_buf->external_buf_size);
	printf("Auth Message Size: 0x%08x\n", data_buf->auth_msg_size);

	for (int i = 0; i < req_spec->param_count; i++)
		printf("Param[%d] (%s): 0x%08x\n", i, req_spec->param_names[i], data_buf->param[i]);

	for (int i = 0; i < req_spec->resp_count; i++)
		printf("Resp[%d] (%s): 0x%08x\n", i, req_spec->resp_names[i], ((u32 *)resp_buf)[i]);

	u32 crc_received = *(u32 *)((char *)data_buf + buf_size - CRC32_SIZE);
		printf("CRC Received: 0x%08x\n", crc_received);
}

int starfive_sec_rx_tx(const struct request_spec *req_spec, void *tx_params, void *rx,
		       void *auth_data, size_t auth_size, void *ext_data, size_t ext_size,
		       bool dump_buf)
{
	int ret = 0;
	u32 buf_size;
	struct rpmi_secure sec;
	char *data_buf = prepare_data_buf(req_spec,
					  tx_params,
					  auth_data,
					  auth_size,
					  ext_data,
					  ext_size,
					  &buf_size);
	if (!data_buf) {
		printf("Error: Memory allocation failed\n");
		return CMD_RET_FAILURE;
	}

	/** Sending message via MPXY/RPMI protocol */
	sec.req.addr = (u64)data_buf;
	struct request_buf *buf = (struct request_buf *)data_buf;
	char *resp_buf = data_buf + sizeof(struct request_buf) + buf->req_size;
#ifdef CONFIG_SPL_BUILD
	struct udevice *rpmi_srv_grp_starfive_bmc_sec_rt_dev;
	struct udevice *rpmi_mbox_shmem_dev;

	ret = uclass_get_device_by_driver(UCLASS_MAILBOX, DM_DRIVER_GET(rpmi_mbox_shmem),
					  &rpmi_mbox_shmem_dev);
	if (ret) {
		printf("FAIL to call RPMI_SHMEM_DRIVER!!\n");
		goto cleanup_ret;
	}

	ret = uclass_get_device_by_driver(UCLASS_RPMI_SRV_GRP,
					  DM_DRIVER_GET(rpmi_srv_grp_starfive_bmc_sec_rt),
					  &rpmi_srv_grp_starfive_bmc_sec_rt_dev);
	if (ret) {
		printf("FAIL to call rpmi_srv_grp_starfive_bmc_sec_rt!!\n");
		goto cleanup_ret;
	}
#else
	struct udevice *mpxy_sec_dev;

	ret = uclass_get_device_by_driver(UCLASS_MISC, DM_DRIVER_GET(jhb100_sbi_mpxy_sec),
					  &mpxy_sec_dev);

	if (ret) {
		printf("Failed to probe StarFive JHB100 Sec MPXY driver\n");
		goto cleanup_ret;
	}
#endif
	flush_dcache_range((u64)data_buf, (u64)(data_buf + buf_size));
#ifdef CONFIG_SPL_BUILD
	ret = rpmi_process_msg(rpmi_srv_grp_starfive_bmc_sec_rt_dev, RPMI_JHB100_SECURE_COMMAND,
			       &sec);
	if (ret) {
		printf("RPMI failed with error: %d\n", ret);
		goto cleanup_ret;
	}
#else
	ret = misc_ioctl(mpxy_sec_dev, RPMI_JHB100_SECURE_COMMAND, &sec);
	if (ret) {
		printf("IOCTL failed with error: %d\n", ret);
		goto cleanup_ret;
	}
#endif
	invalidate_dcache_range((u64)data_buf, (u64)(data_buf + buf_size));
	if (rx)
		memcpy(rx, resp_buf, req_spec->resp_size);

	if (dump_buf) {
		dump_data_buf(req_spec, data_buf, resp_buf, buf_size);
		printf("Response received\n");
	}

	free(data_buf);
	return CMD_RET_SUCCESS;

cleanup_ret:
	free(data_buf);
	return CMD_RET_FAILURE;
}

#ifndef CONFIG_SPL_BUILD
static const struct request_spec *get_request_spec_by_name(const char *request_name)
{
	for (int i = 0; i < ARRAY_SIZE(request_specs); i++) {
		if (strcmp(request_specs[i].request_name, request_name) == 0)
			return &request_specs[i];
	}

	return NULL;
}

static void display_available_requests(void)
{
	printf("\nAvailable Requests:\n");
	for (int i = 0; i < ARRAY_SIZE(request_specs); i++)
		printf("- %s\n", request_specs[i].request_name);
}

static void display_help(void)
{
	printf("BMC Secure Service Tool Usage:\n");
	printf("bmc_sst <request_name> [parameters...] [auth_data] [ext_data]\n\n");

	printf("General options:\n");
	printf("  help                     Show this help message\n");
	printf("  list                     List available requests\n");
	printf("  show <request>           Show details for a specific request\n\n");

	printf("Request parameters:\n");
	printf("  For requests requiring authentication:\n");
	printf("    auth=<addr>,<size>     Authentication data info\n");
	printf("  For requests with external data:\n");
	printf("    ext=<addr>,<size>      External data info\n\n");

	printf("Detailed Request Table:\n");
	int col_widths[] = {28, 6, 8, 40};

	printf(" ");
	for (int i = 0; i < ARRAY_SIZE(col_widths); i++) {
		for (int j = 0; j < col_widths[i]; j++)
			printf("-");
		printf(i == 3 ? "\n" : "-+-");
	}

	printf("%-26s | %-4s | %-6s | %-38s\n",
	       "Request Name", "Auth", "Ext", "Parameters");
	printf(" ");
	for (int i = 0; i < ARRAY_SIZE(col_widths); i++) {
		for (int j = 0; j < col_widths[i]; j++)
			printf("-");
		printf(i == 3 ? "\n" : "-+-");
	}

	for (int i = 0; i < ARRAY_SIZE(request_specs); i++) {
		char params[40] = {0};

		for (int j = 0; j < request_specs[i].param_count; j++) {
			if (j > 0)
				strncat(params, " ", sizeof(params) - strlen(params) - 1);
			strncat(params, request_specs[i].param_names[j],
				sizeof(params) - strlen(params) - 1);
		}

		printf("%-26s | %-4s | %-6s | %-38s\n",
		       request_specs[i].request_name,
		       request_specs[i].need_auth ? "Yes" : "No",
		       request_specs[i].has_external_data ? "Yes" : "No",
		       params);
	}

	printf(" ");
	for (int i = 0; i < ARRAY_SIZE(col_widths); i++) {
		for (int j = 0; j < col_widths[i]; j++)
			printf("-");
		printf(i == 3 ? "\n" : "-+-");
	}
}

static void show_request_details(const char *request_name)
{
	const struct request_spec *req_spec = get_request_spec_by_name(request_name);

	if (!req_spec) {
		printf("Error: Unknown request name %s\n", request_name);
		return;
	}

	printf("\nDetails for request: %s\n", request_name);
	printf("Parameters (%d):\n", req_spec->param_count);
	for (int i = 0; i < req_spec->param_count; i++)
		printf("  %d: %s\n", i + 1, req_spec->param_names[i]);

	printf("Authentication required: %s\n", req_spec->need_auth ? "Yes" : "No");
	printf("External data required: %s\n", req_spec->has_external_data ? "Yes" : "No");
}

static int parse_auth_ext_param(const char *param, void **addr, u32 *size)
{
	*addr = (void *)hextoul(param, (char **)&param);

	if (*param != ',')
		return -EINVAL;
	param++;

	*size = dectoul(param, NULL);

	return 0;
}

static int do_bmc_sst(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	const struct request_spec *req_spec = NULL;
	u32 auth_size = 0;
	void *auth_data = NULL;
	char *ext_data = NULL;
	u32 ext_size = 0;
	int ret = 0;
	int param_index = 0;
	int optional_args = 0;

	if (argc < 2) {
		printf("Error: No request specified\n");
		display_help();
		return CMD_RET_USAGE;
	}

	/* Handle help/list/show commands */
	if (strcmp(argv[1], "help") == 0) {
		display_help();
		return CMD_RET_SUCCESS;
	}
	if (strcmp(argv[1], "list") == 0) {
		display_available_requests();
		return CMD_RET_SUCCESS;
	}
	if (strcmp(argv[1], "show") == 0) {
		if (argc < 3) {
			printf("Error: No request name specified for show command\n");
			return CMD_RET_USAGE;
		}
		show_request_details(argv[2]);
		return CMD_RET_SUCCESS;
	}

	/* Get request specification */
	req_spec = get_request_spec_by_name(argv[1]);
	if (!req_spec) {
		printf("Error: Unknown request name %s\n", argv[1]);
		return CMD_RET_FAILURE;
	}

	/* First pass to count optional args (auth=, ext=) */
	for (int i = 2; i < argc; i++) {
		if (strncmp(argv[i], "auth=", 5) == 0 || strncmp(argv[i], "ext=", 4) == 0)
			optional_args++;
	}

	/* Check required parameter count matches */
	/* Subtract command, request, and optional args */
	int provided_params = argc - 2 - optional_args;

	if (provided_params < req_spec->param_count) {
		printf("Error: Insufficient arguments for %s\n", req_spec->request_name);
		printf("Expected %d parameters, got %d\n", req_spec->param_count, provided_params);
		return CMD_RET_USAGE;
	}

	/* Allocate and parse required parameters */
	char *endptr;
	u32 req_data[req_spec->param_count];

	for (param_index = 0; param_index < req_spec->param_count; param_index++) {
		req_data[param_index] = hextoul(argv[param_index + 2], &endptr);

		if (*endptr != '\0') {
			printf("Error: Invalid hex value '%s' for parameter %s\n",
			       argv[param_index + 2], req_spec->param_names[param_index]);
			return CMD_RET_USAGE;
		}
	}

	/* Parse optional auth and ext parameters */
	for (int i = 2 + req_spec->param_count; i < argc; i++) {
		if (strncmp(argv[i], "auth=", 5) == 0) {
			if (!req_spec->need_auth) {
				printf("Warning: Authentication data provided but not required for this request\n");
				continue;
			}
			if (parse_auth_ext_param(argv[i] + 5, &auth_data, &auth_size) != 0)
				return CMD_RET_USAGE;
		} else if (strncmp(argv[i], "ext=", 4) == 0) {
			if (!req_spec->has_external_data) {
				printf("Warning: External data provided but not required for this request\n");
				continue;
			}
			if (parse_auth_ext_param(argv[i] + 4, (void **)&ext_data, &ext_size) != 0)
				return CMD_RET_USAGE;
		} else {
			printf("Error: Unknown parameter %s\n", argv[i]);
			return CMD_RET_USAGE;
		}
	}

	/* Validate required optionals */
	if (req_spec->need_auth && (!auth_data || auth_size == 0)) {
		printf("Error: Authentication required but no auth data provided\n");
		return CMD_RET_USAGE;
	}

	if (req_spec->has_external_data && (!ext_data || ext_size == 0)) {
		printf("Error: External data required but none provided\n");
		return CMD_RET_USAGE;
	}

	/* Execute request */
	printf("Submitting request %s...\n", req_spec->request_name);
	ret = starfive_sec_rx_tx(req_spec, req_data, NULL, auth_data,
				 auth_size, ext_data, ext_size, true);

	return ret ? CMD_RET_FAILURE : CMD_RET_SUCCESS;
}

U_BOOT_CMD(bmc_sst, CONFIG_SYS_MAXARGS, 1, do_bmc_sst,
	   "StarFive BMC Secure Service Tool",
	   "bmc_sst <request> [params...] [auth=<addr>,<size>] [ext=<addr>,<size>]\n"
	   "bmc_sst help - Show detailed help\n"
	   "bmc_sst list - List available requests\n"
	   "bmc_sst show <request> - Show details for a request"
);
#endif
