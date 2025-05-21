// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#ifndef __STARFIVE_RPMI_MPXY_SEC_H
#define __STARFIVE_RPMI_MPXY_SEC_H

#define BITS_PER_WORD		32
#define NUM_WORD(n)		((n) / BITS_PER_WORD)
#define BUF256_WORD_32_NUM	NUM_WORD(256)
#define ADDR_HIGH_MASK		(GENMASK(63, 32))
#define ADDR_LOW_MASK		(GENMASK(31, 0))
#define CRC32_SIZE		4
#define MAX_REQ_RESP_COUNT	8

struct __attribute__((aligned(4))) request_buf {
	u32 request_id;
	u32 req_size;
	u32 resp_size;
	u32 external_buf_size;
	u32 auth_msg_size;
	u32 param[];
};

struct request_spec {
	u32 request_id;
	const char *request_name;
	int param_count;
	const char *param_names[MAX_REQ_RESP_COUNT];
	u32 resp_size;
	const char *resp_names[MAX_REQ_RESP_COUNT];
	u32 resp_count;
	int need_auth;
	int has_external_data;
};

enum jhb100_sec_srv_id {
	RPMI_JHB100_SECURE_COMMAND = 0x1,
	JHB100_SEC_SRV_ID_MAX_COUNT
};

struct rpmi_secure_req {
	u64 addr;
};

struct rpmi_secure_resp {
	s32 status;
};

struct rpmi_secure {
	struct rpmi_secure_req req;
	struct rpmi_secure_resp resp;
};

enum jhb100_firmware {
	SECBOOT_VERIFY_BMCFW = 1,
	SECBOOT_VERIFY_BIOSFW,
	SECBOOT_GET_BIOS_VERIFY_STATUS,
	SECBOOT_GET_BMCFW_BOOT_STATUS,
	FW_UPDATE_BMCFW_REQ,
	FW_UPDATE_BIOSFW_REQ,
	GET_BMCFW_UPDATE_INFO,
	GET_BIOSFW_UPDATE_INFO,
	GET_BIOSFW_INFO,
	DICE_GET_CERT_N,
	DICE_GET_CSR0,
	OTP_GET_USER_REGION_SIZE,
	OTP_USER_REGION_READ,
	OTP_USER_REGION_WRITE,
	SET_LOGBUF,
	GET_LOGBUF,
	SET_NEXT_BOOT_MODE,
	GET_DRAM_INFO,
	SET_DRAM_CFG,
	DICE_PROV_CERT0 = 513,
	DICE_UDS_REHASH,
	SET_SEC_MODE,
	KEY_PROV,
	KEY_REVOKE,
	OTP_ZEROIZE,
};

const struct request_spec *get_request_spec_by_id(u32 request_id);
int starfive_sec_rx_tx(const struct request_spec *req_spec, void *tx_params, void *rx,
		       void *auth_data, size_t auth_size, void *ext_data, size_t ext_size,
		       bool dump_buf);
int run_bmc_sst_cmd(const char *cmd, void *resp);

#endif
