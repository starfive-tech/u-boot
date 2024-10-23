// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#ifndef __STARFIVE_MPXY_SEC_H
#define __STARFIVE_MPXY_SEC_H

enum jhb100_firmware {
	SECBOOT_VERIFY_BMCFW = 0x1,
	SECBOOT_VERIFY_BIOSFW,
	SECBOOT_GETBIOS_VERIFY_STATUS,
	SECBOOT_GETBIOS_MUX_STATUS,
	SECBOOT_GET_BOOT_STATUS,
	FW_UPDATE_REQ,
	GET_LAST_FW_UPDATE_STATUS,
	GET_BMCFW_INFO,
	GET_BIOSFW_INFO,
	DICE_PROV_CERT0,
	DICE_GET_CERT_N,
	DICE_GET_CSR0,
	OTP_GET_USER_REGION_SIZE,
	OTP_USER_REGION_READ,
	OTP_USER_REGION_WRITE
};

struct secboot_verify_bmcfw_req {
	u32 fw_address_low;
	u32 fw_address_high;
	u32 size;
};

struct secboot_verify_bmcfw_resp {
	u32 status;
};

struct secboot_verify_bmcfw {
	struct secboot_verify_bmcfw_req req;
	struct secboot_verify_bmcfw_resp resp;
};

struct secboot_verify_biosfw_req {
	u32 biosfw_address_low;
	u32 biosfw_address_high;
	u32 biosfw_mem_size;
};

struct secboot_verify_biosfw_resp {
	u32 status;
};

struct secboot_verify_biosfw {
	struct secboot_verify_biosfw_req req;
	struct secboot_verify_biosfw_resp resp;
};

union secboot_getbios_verify_status_flag {
	u32 v;
	struct {
		u32 chip_select	: 2;
#define CS0	0
#define CS1	1
#define CS2	2
		u32 node_select	: 2;
#define NODE_0	0
#define NODE_1	1
		u32 reserved	: 28;
	};
};

struct secboot_getbios_verify_status_req {
	union secboot_getbios_verify_status_flag flag;
};

struct secboot_getbios_verify_status_resp {
	u32 status;
};

struct secboot_getbios_verify_status {
	struct secboot_getbios_verify_status_req req;
	struct secboot_getbios_verify_status_resp resp;
};

union secboot_getbios_mux_status_flag {
	u32 v;
	struct {
		u32 node_select	: 2;
#define NODE_0	0
#define NODE_1	1
		u32 reserved	: 30;
	};
};

struct secboot_getbios_mux_status_req {
	union secboot_getbios_mux_status_flag flag;
};

union mux_status {
	u32 v;
	struct {
		u32 cs0		: 1;
		u32 cs1		: 1;
		u32 cs2		: 1;
#define BMC_CONTROL	0
#define HOST_CONTROL	1
		u32 reserved	: 29;
	};
};

struct secboot_getbios_mux_status_resp {
	u32 status;
	union mux_status mux_status;
};

struct secboot_getbios_mux_status {
	struct secboot_getbios_mux_status_req req;
	struct secboot_getbios_mux_status_resp resp;
};

union boot_status {
	u32 v;
	struct {
		u32 bmc_os_loc		: 2;
		u32 opensbi_uboot_loc	: 2;
		u32 spl_loc		: 2;
		u32 l1_fw_loc		: 2;
		u32 l0_fw_loc		: 2;
#define ACTIVE		0
#define RECOVERY	1
#define GOLDEN		2
		u32 boot_source		: 2;
#define UART		0
#define SPI_FLASH	1
#define EMMC		2
#define UFS		3
		u32 reserved		: 20;
	};
};

struct secboot_get_boot_status_resp {
	u32 status;
	union boot_status boot_status;
};

union fw_update_config {
	u32 v;
	struct {
		u32 fw_img_type	: 2;
#define BMC_FW	0
#define BIOS_FW	1
		u32 target_loc	: 2;
		u32 source_loc	: 2;
#define UPDATE_FROM_STAGING 0
#define UPDATE_FROM_GOLDEN 1
		u32 media_type	: 2;
		u32 reserved	: 24;
	};
};

struct fw_update_req_req {
	union fw_update_config fw_update_config;
	u32 fw_source_offset;
};

struct fw_update_req_resp {
	u32 status;
};

struct fw_update_req {
	struct fw_update_req_req req;
	struct fw_update_req_resp resp;
};

union get_last_fw_update_status_flag {
	u32 v;
	struct {
		u32 fw_img_type	: 2;
		u32 reserved	: 30;
	};
};

struct get_last_fw_update_status_req {
	union get_last_fw_update_status_flag flag;
};

union fw_update_status {
	u32 v;
	struct {
		u32 fw_img_type	: 2;
		u32 target_loc	: 2;
		u32 source_loc	: 2;
		u32 media_type	: 2;
		u32 reserved	: 24;
	};
};

struct get_last_fw_update_status_resp {
	u32 status;
	union fw_update_status fw_update_status;
};

struct get_last_fw_update_status {
	struct get_last_fw_update_status_req req;
	struct get_last_fw_update_status_resp resp;
};

union get_boot_info_flag {
	u32 v;
	struct {
		u32 fw_loc	: 2;
		u32 reserved	: 30;
	};
};

struct get_bmcfw_info_req {
	union get_boot_info_flag flag;
};

struct get_bmcfw_info_resp {
	u32 status;
	u32 l0_fw_ver;
	u32 l1_fw_ver;
	u32 spl_fw_ver;
	u32 opensbi_fw_ver;
	u32 uboot_fw_ver;
	u32 bmc_os_ver;
};

struct get_bmcfw_info {
	struct get_bmcfw_info_req req;
	struct get_bmcfw_info_resp resp;
};

struct get_biosfw_info_req {
	union get_boot_info_flag flag;
};

struct get_biosfw_info_resp {
	u32 status;
	u32 bios_fw_ver;
};

struct get_biosfw_info {
	struct get_biosfw_info_req req;
	struct get_biosfw_info_resp resp;
};

struct dice_prov_cert0_req {
	u32 cert0_add_low;
	u32 cert1_add_high;
	u32 cert0_size;
};

struct dice_prov_cert0_resp {
	u32 status;
};

struct dice_prov_cert0 {
	struct dice_prov_cert0_req req;
	struct dice_prov_cert0_resp resp;
};

struct dice_get_cert_n_req {
	u32 certificate_index;
	u32 certn_address_low;
	u32 certn_address_high;
	u32 certn_size;
};

struct dice_get_cert_n_resp {
	u32 status;
};

struct dice_get_cert_n {
	struct dice_get_cert_n_req req;
	struct dice_get_cert_n_resp resp;
};

struct dice_get_csr0_req {
	u32 csr0_address_low;
	u32 csr0_address_high;
	u32 csr0_size;
};

struct dice_get_csr0_resp {
	u32 status;
};

struct dice_get_csr0 {
	struct dice_get_csr0_req req;
	struct dice_get_csr0_resp resp;
};

struct otp_get_user_region_size_resp {
	u32 status;
	u32 fields_num;
};

struct otp_user_region_read_req {
	u32 otp_field_index;
};

struct otp_user_region_read_resp {
	u32 status;
	u32 data32;
};

struct otp_user_region_read {
	struct otp_user_region_read_req req;
	struct otp_user_region_read_resp resp;
};

struct otp_user_region_write_req {
	u32 otp_field_index;
	u32 data32;
};

struct otp_user_region_write_resp {
	u32 status;
};

struct otp_user_region_write {
	struct otp_user_region_write_req req;
	struct otp_user_region_write_resp resp;
};
#endif
