// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */
#ifndef __STARFIVE_SEC_SPEC_H
#define __STARFIVE_SEC_SPEC_H

static const struct request_spec request_specs[] = {
	{
		.request_id = 1,
		.request_name = "secboot_verify_bmcfw",
		.param_count = 4,
		.param_names = {"flags", "addr_low", "addr_high", "size"},
		.resp_count = 2,
		.resp_names = {"status", "img_len"},
		.resp_size = 8,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 2,
		.request_name = "secboot_verify_biosfw",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 3,
		.request_name = "secboot_get_bios_verify_status",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 2,
		.resp_names = {"status", "verify_status"},
		.resp_size = 8,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 4,
		.request_name = "secboot_get_bmcfw_boot_status",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 2,
		.resp_names = {"status", "boot_status"},
		.resp_size = 8,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 5,
		.request_name = "update_bmcfw_req",
		.param_count = 4,
		.param_names = {"flags", "addr_low", "addr_high", "size"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 6,
		.request_name = "update_biosfw_req",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 7,
		.request_name = "get_bmcfw_update_info",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 20,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 8,
		.request_name = "get_biosfw_update_info",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 20,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 9,
		.request_name = "get_biosfw_info",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 36,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 10,
		.request_name = "dice_get_cert_n",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 2,
		.resp_names = {"status", "cert_len"},
		.resp_size = 4096,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 11,
		.request_name = "otp_get_user_region_size",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 3,
		.resp_names = {"status", "otp1_size", "otp2_size"},
		.resp_size = 12,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 12,
		.request_name = "otp_user_region_read",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 68,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 13,
		.request_name = "otp_user_region_write",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 1
	},
	{
		.request_id = 14,
		.request_name = "otp_get_zeroize_status",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 2,
		.resp_names = {"status", "zeroize_status"},
		.resp_size = 8,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 15,
		.request_name = "set_logbuf",
		.param_count = 4,
		.param_names = {"flags", "addr_low", "addr_high", "buf_size"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 16,
		.request_name = "get_logbuf",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 4,
		.resp_names = {"status", "addr_low", "addr_high", "buf_size"},
		.resp_size = 16,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 17,
		.request_name = "set_next_boot_param",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 18,
		.request_name = "get_dram_info",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 20,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 19,
		.request_name = "biosfw_factory_reset",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 20,
		.request_name = "get_system_event",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 2,
		.resp_names = {"status", "event_len"},
		.resp_size = 40,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 21,
		.request_name = "get_system_status",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 20,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 22,
		.request_name = "pre_os_boot_notify",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 23,
		.request_name = "os_boot_notify",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 24,
		.request_name = "secboot_verify_rofs",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 0,
		.has_external_data = 0
	},
	{
		.request_id = 513,
		.request_name = "dice_prov_cert0",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 1,
		.has_external_data = 1
	},
	{
		.request_id = 514,
		.request_name = "dice_uds_rehash",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status", "uds_rehash_bitmap"},
		.resp_size = 8,
		.need_auth = 1,
		.has_external_data = 0
	},
	{
		.request_id = 515,
		.request_name = "set_sec_mode",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 1,
		.has_external_data = 0
	},
	{
		.request_id = 516,
		.request_name = "key_prov",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 1,
		.has_external_data = 1
	},
	{
		.request_id = 517,
		.request_name = "key_revoke",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 1,
		.has_external_data = 0
	},
	{
		.request_id = 518,
		.request_name = "otp_zeroize",
		.param_count = 1,
		.param_names = {"flags"},
		.resp_count = 1,
		.resp_names = {"status"},
		.resp_size = 4,
		.need_auth = 1,
		.has_external_data = 0
	}
};
#endif
