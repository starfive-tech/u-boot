// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#include <common.h>
#include <dm.h>
#include <dm/uclass.h>
#include <dm/device.h>
#include <dm/device-internal.h>
#include <dm/device_compat.h>
#include <linux/errno.h>
#include "mailbox_rpmi_shmem.h"
#include <mailbox.h>
#include <rpmi/rpmi-srvgrp-uclass.h>
#include <asm/arch/rpmi-mpxy-sec.h>

static struct rpmi_service starfive_bmc_sec_rt_services[STARFIVE_SEC_SRV_MAX_COUNT] = {
{
	.id = SECBOOT_VERIFY_BMCFW,
	.min_tx_len = sizeof(struct secboot_verify_bmcfw_req),
	.max_tx_len = sizeof(struct secboot_verify_bmcfw_req),
	.min_rx_len = sizeof(struct secboot_verify_bmcfw_resp),
	.max_rx_len = sizeof(struct secboot_verify_bmcfw_resp),
},
{
	.id = SECBOOT_VERIFY_BIOSFW,
	.min_tx_len = sizeof(struct secboot_verify_biosfw_req),
	.max_tx_len = sizeof(struct secboot_verify_biosfw_req),
	.min_rx_len = sizeof(struct secboot_verify_biosfw_resp),
	.max_rx_len = sizeof(struct secboot_verify_biosfw_resp),
},
{
	.id = SECBOOT_GETBIOS_VERIFY_STATUS,
	.min_tx_len = sizeof(struct secboot_getbios_verify_status_req),
	.max_tx_len = sizeof(struct secboot_getbios_verify_status_req),
	.min_rx_len = sizeof(struct secboot_getbios_verify_status_resp),
	.max_rx_len = sizeof(struct secboot_getbios_verify_status_resp),
},
{
	.id = SECBOOT_GETBIOS_MUX_STATUS,
	.min_tx_len = sizeof(struct secboot_getbios_mux_status_req),
	.max_tx_len = sizeof(struct secboot_getbios_mux_status_req),
	.min_rx_len = sizeof(struct secboot_getbios_mux_status_resp),
	.max_rx_len = sizeof(struct secboot_getbios_mux_status_resp),
},
{
	.id = SECBOOT_GET_BOOT_STATUS,
	.min_tx_len = 0,
	.max_tx_len = 0,
	.min_rx_len = sizeof(struct secboot_get_boot_status_resp),
	.max_rx_len = sizeof(struct secboot_get_boot_status_resp),
},
{
	.id = FW_UPDATE_REQ,
	.min_tx_len = sizeof(struct fw_update_req_req),
	.max_tx_len = sizeof(struct fw_update_req_req),
	.min_rx_len = sizeof(struct fw_update_req_resp),
	.max_rx_len = sizeof(struct fw_update_req_resp),
},
{
	.id = GET_LAST_FW_UPDATE_STATUS,
	.min_tx_len = sizeof(struct get_last_fw_update_status_req),
	.max_tx_len = sizeof(struct get_last_fw_update_status_req),
	.min_rx_len = sizeof(struct get_last_fw_update_status_resp),
	.max_rx_len = sizeof(struct get_last_fw_update_status_resp),
},
{
	.id = GET_BMCFW_INFO,
	.min_tx_len = sizeof(struct get_bmcfw_info_req),
	.max_tx_len = sizeof(struct get_bmcfw_info_req),
	.min_rx_len = sizeof(struct get_bmcfw_info_resp),
	.max_rx_len = sizeof(struct get_bmcfw_info_resp),
},
{
	.id = GET_BIOSFW_INFO,
	.min_tx_len = sizeof(struct get_biosfw_info_req),
	.max_tx_len = sizeof(struct get_biosfw_info_req),
	.min_rx_len = sizeof(struct get_biosfw_info_resp),
	.max_rx_len = sizeof(struct get_biosfw_info_resp),
},
{
	.id = DICE_PROV_CERT0,
	.min_tx_len = sizeof(struct dice_prov_cert0_req),
	.max_tx_len = sizeof(struct dice_prov_cert0_req),
	.min_rx_len = sizeof(struct dice_prov_cert0_resp),
	.max_rx_len = sizeof(struct dice_prov_cert0_resp),
},
{
	.id = DICE_GET_CERT_N,
	.min_tx_len = sizeof(struct dice_get_cert_n_req),
	.max_tx_len = sizeof(struct dice_get_cert_n_req),
	.min_rx_len = sizeof(struct dice_get_cert_n_resp),
	.max_rx_len = sizeof(struct dice_get_cert_n_resp),
},
{
	.id = DICE_GET_CSR0,
	.min_tx_len = sizeof(struct dice_get_csr0_req),
	.max_tx_len = sizeof(struct dice_get_csr0_req),
	.min_rx_len = sizeof(struct dice_get_csr0_resp),
	.max_rx_len = sizeof(struct dice_get_csr0_resp),
},
{
	.id = OTP_GET_USER_REGION_SIZE,
	.min_tx_len = 0,
	.max_tx_len = 0,
	.min_rx_len = sizeof(struct otp_get_user_region_size_resp),
	.max_rx_len = sizeof(struct otp_get_user_region_size_resp),
},
{
	.id = OTP_USER_REGION_READ,
	.min_tx_len = sizeof(struct otp_user_region_read_req),
	.max_tx_len = sizeof(struct otp_user_region_read_req),
	.min_rx_len = sizeof(struct otp_user_region_read_resp),
	.max_rx_len = sizeof(struct otp_user_region_read_resp),
},
{
	.id = OTP_USER_REGION_WRITE,
	.min_tx_len = sizeof(struct otp_user_region_write_req),
	.max_tx_len = sizeof(struct otp_user_region_write_req),
	.min_rx_len = sizeof(struct otp_user_region_write_resp),
	.max_rx_len = sizeof(struct otp_user_region_write_resp),
},
};

#define RPMI_REQ_RESP(type) \
	; \
	struct type *type = (struct type *)data; \
	return starfive_bmc_sec_rt_trans(dev, service_id, &type->req, sizeof(struct type##_req), \
					 &type->resp, &rxmsg_len)

#define RPMI_RESP(type) \
	; \
	struct type *type = (struct type *)data; \
	return starfive_bmc_sec_rt_trans(dev, service_id, 0, 0, \
					 &type, &rxmsg_len)

static int rpmi_tx_rx(struct mbox_chan *chan, u16 servicegroup_id, u16 service_id, void *tx,
		      u64 tx_msglen, void *rx, u64 rx_msglen, u64 *out_len)
{
	struct rpmi_message *msg = calloc(1, sizeof(*msg) +
					 (tx_msglen > rx_msglen ? tx_msglen : rx_msglen));
	int ret = 0;

	msg->header.servicegroup_id = cpu_to_le16(servicegroup_id);
	msg->header.service_id = service_id;
	msg->header.flags = rx ? RPMI_MSG_NORMAL_REQUEST : RPMI_MSG_POSTED_REQUEST;
	msg->header.datalen = tx_msglen;
	msg->header.token = cpu_to_le16(MSG_TOKEN);
	memcpy(msg->data, tx, tx_msglen);
	ret = mbox_send(chan, msg);
	if (ret) {
		printf("Failed to send message\n");
		free(msg);
		return -EINVAL;
	}

	if (rx) {
		msg->header.datalen = rx_msglen;

		ret = mbox_recv(chan, msg, RPMI_DEF_RX_TIMEOUT_US);
		if (ret) {
			printf("Failed to receive message\n");
			free(msg);
			return -EINVAL;
		}

		*out_len = (u64)msg->header.datalen;
		memcpy(rx, msg->data, *out_len);

		free(msg);
		return ((u32 *)rx)[0];
	}

	free(msg);
	return 0;
}

static int starfive_bmc_sec_rt_trans(struct udevice *dev, u16 service_id, void *tx, u64 tx_msglen,
				     void *rx, u64 *out_len)
{
	struct rpmi_service *srv = find_rpmi_srvid(dev, service_id);

	if (!srv)
		return -EINVAL;

	struct rpmi_chan_priv *chan_priv = dev_get_priv(dev);

	if (!chan_priv) {
		dev_err(dev, "No priv data found\n");
		return -EINVAL;
	}

	struct rpmi_srv_grp_priv *group = chan_priv->group;

	if (!group) {
		dev_err(dev, "Service group not registered\n");
		return -ENODEV;
	}

	if (tx_msglen < srv->min_tx_len || tx_msglen > srv->max_tx_len)
		return -EINVAL;

	return rpmi_tx_rx(chan_priv->chan,
			  group->servicegroup_id,
			  service_id,
			  tx,
			  tx_msglen,
			  rx,
			  srv->max_rx_len,
			  out_len);
}

static int starfive_bmc_sec_rt_process_msg(struct udevice *dev, u16 service_id, void *data)
{
	u64 rxmsg_len;
	struct rpmi_chan_priv *chan_priv = dev_get_priv(dev);

	if (!chan_priv) {
		dev_err(dev, "No priv data found\n");
		return -EINVAL;
	}

	struct rpmi_srv_grp_priv *group = chan_priv->group;

	if (!group) {
		dev_err(dev, "Service group not registered\n");
		return -ENODEV;
	}

	if (service_id > group->max_service_id)
		return -EINVAL;

	switch (service_id) {
	case SECBOOT_VERIFY_BMCFW:
		RPMI_REQ_RESP(secboot_verify_bmcfw);
		break;
	case SECBOOT_VERIFY_BIOSFW:
		RPMI_REQ_RESP(secboot_verify_biosfw);
		break;
	case SECBOOT_GETBIOS_VERIFY_STATUS:
		RPMI_REQ_RESP(secboot_getbios_verify_status);
		break;
	case SECBOOT_GETBIOS_MUX_STATUS:
		RPMI_REQ_RESP(secboot_getbios_mux_status);
		break;
	case SECBOOT_GET_BOOT_STATUS:
		RPMI_RESP(secboot_get_boot_status_resp);
		break;
	case FW_UPDATE_REQ:
		RPMI_REQ_RESP(fw_update_req);
		break;
	case GET_LAST_FW_UPDATE_STATUS:
		RPMI_REQ_RESP(get_last_fw_update_status);
		break;
	case GET_BMCFW_INFO:
		RPMI_REQ_RESP(get_bmcfw_info);
		break;
	case GET_BIOSFW_INFO:
		RPMI_REQ_RESP(get_biosfw_info);
		break;
	case DICE_PROV_CERT0:
		RPMI_REQ_RESP(dice_prov_cert0);
		break;
	case DICE_GET_CERT_N:
		RPMI_REQ_RESP(dice_get_cert_n);
		break;
	case DICE_GET_CSR0:
		RPMI_REQ_RESP(dice_get_csr0);
		break;
	case OTP_GET_USER_REGION_SIZE:
		RPMI_RESP(otp_get_user_region_size_resp);
		break;
	case OTP_USER_REGION_READ:
		RPMI_REQ_RESP(otp_user_region_read);
		break;
	case OTP_USER_REGION_WRITE:
		RPMI_REQ_RESP(otp_user_region_write);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int rpmi_get_base_privilege_level(struct udevice *dev)
{
	int ret;
	struct rpmi_base_get_attributes_resp resp;
	u64 *out_len = NULL;

	struct rpmi_chan_priv *chan_priv = dev_get_priv(dev);

	if (!chan_priv) {
		dev_err(dev, "No priv data found\n");
		return -EINVAL;
	}

	ret = rpmi_tx_rx(chan_priv->chan,
			 RPMI_SRVGRP_BASE,
			 RPMI_BASE_SRV_GET_ATTRIBUTES,
			 0,
			 0,
			 &resp,
			 sizeof(resp),
			 out_len);

	if (!out_len)
		return -EINVAL;

	if (resp.status_code)
		return resp.status_code;

	return (resp.f0 & RPMI_BASE_FLAGS_F0_PRIVILEGE);
}

static int rpmi_get_base_version(struct udevice *dev)
{
	int ret;
	u32 val[2];
	u64 *out_len = NULL;

	struct rpmi_chan_priv *chan_priv = dev_get_priv(dev);

	if (!chan_priv) {
		dev_err(dev, "No priv data found\n");
		return -EINVAL;
	}

	ret = rpmi_tx_rx(chan_priv->chan,
			 RPMI_SRVGRP_BASE,
			 RPMI_BASE_SRV_GET_SPEC_VERSION,
			 0,
			 0,
			 val,
			 sizeof(val),
			 out_len);
	if (ret)
		return ret;

	if (val[0])
		return val[0];

	return val[1];
}

static int starfive_bmc_sec_rt_probe(struct udevice *dev)
{
	struct rpmi_chan_priv *chan_dev = dev_get_priv(dev);
	int ret;

	if (!chan_dev)
		return -ENOMEM;

	chan_dev->chan = calloc(1, sizeof(*chan_dev->chan));
	if (!chan_dev->chan)
		return -ENOMEM;

	/** Request channel */
	ret = mbox_get_by_index(dev, 0, chan_dev->chan);
	if (ret) {
		free(chan_dev->chan);
		return -ENOTSUPP;
	}

	chan_dev->group = calloc(1, sizeof(*chan_dev->group));
	if (!chan_dev->group) {
		free(chan_dev->chan);
		return -ENOMEM;
	}

	struct rpmi_srv_grp_priv *group = chan_dev->group;

	group->name = "starfive_bmc_sec_rt";
	group->servicegroup_id = RPMI_SRVGRP_VENDOR_START;
	group->servicegroup_version = rpmi_get_base_version(dev);
	/* Allowed for both M-mode and S-mode RPMI context */
	group->privilege_level_bitmap = rpmi_get_base_privilege_level(dev);
	group->max_service_id = STARFIVE_SEC_SRV_MAX_COUNT;
	group->services = starfive_bmc_sec_rt_services;

	return 0;
}

static int starfive_bmc_sec_rt_remove(struct udevice *dev)
{
	struct rpmi_chan_priv *chan_priv = dev_get_priv(dev);

	if (!chan_priv) {
		dev_err(dev, "No priv data found\n");
		return -EINVAL;
	}

	free(chan_priv->chan);
	free(chan_priv->group);

	return 0;
}

static const struct rpmi_srvgrp_ops starfive_bmc_sec_rt_ops = {
	.rpmi_process_msg = starfive_bmc_sec_rt_process_msg,
};

static const struct udevice_id rpmi_service_group_starfive_bmc_sec_rt_ids[] = {
	{ .compatible = "riscv,rpmi-jhb100-sec" },
	{ }
};

U_BOOT_DRIVER(rpmi_srv_grp_starfive_bmc_sec_rt) = {
	.id		= UCLASS_RPMI_SRV_GRP,
	.name		= "rpmi_srv_grp_starfive_bmc_sec_rt",
	.priv_auto	= sizeof(struct rpmi_chan_priv),
	.probe		= starfive_bmc_sec_rt_probe,
	.remove		= starfive_bmc_sec_rt_remove,
	.ops		= &starfive_bmc_sec_rt_ops,
	.of_match	= rpmi_service_group_starfive_bmc_sec_rt_ids,
};
