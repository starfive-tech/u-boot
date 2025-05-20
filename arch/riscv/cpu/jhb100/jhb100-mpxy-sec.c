// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#include <common.h>
#include <dm.h>
#include <linux/compat.h>
#include <misc.h>
#include <asm/arch/rpmi-mpxy-sec.h>
#include <asm/rpmi.h>
#include <asm/sbi.h>
#include <asm-generic/ioctl.h>
#include <malloc.h>
#include <memalign.h>

struct jhb100_mpxy_priv {
	struct udevice *dev;
	void *shmem_buf;
	u32 shmem_size;
	bool active;
	u32 channel_id;
};

#define ATTR_COUNT(t, f)			((t) - (f) + 1)
#define FIRMWARE_MPXY_REQ_RESP(type) \
	struct type *type = (struct type *)arg; \
	if (sbi_mpxy_send_message_withresp(mpxy->shmem_buf, mpxy->channel_id, cmd, &type->req, \
					   sizeof(struct type##_req), \
					   &type->resp, &rxmsg_len)) \
		return -EACCES; \
	return type->resp.status

#define FIRMWARE_MPXY_RESP(type) \
	struct type *type = (struct type *)arg; \
	if (sbi_mpxy_send_message_withresp(mpxy->shmem_buf, mpxy->channel_id, cmd, 0, 0, \
					   &type, &rxmsg_len)) \
		return -EACCES; \
	return type->resp.status

static int jhb100_mpxy_sec_ioctl(struct udevice *dev, unsigned long cmd, void *arg)
{
	u64 rxmsg_len;
	struct jhb100_mpxy_priv *mpxy = dev_get_priv(dev);

	switch (cmd) {
	case RPMI_JHB100_SECURE_COMMAND:
		FIRMWARE_MPXY_REQ_RESP(rpmi_secure);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int jhb100_mpxy_sec_probe(struct udevice *dev)
{
	if (sbi_get_spec_version() < sbi_mk_version(1, 0) ||
	    sbi_probe_extension(SBI_EXT_MPXY) <= 0) {
		printf("sbi mpxy extension is not present\n");
		return -ENODEV;
	}

	int ret;
	u32 attr_count, *attr_buf, version;
	struct ofnode_phandle_args args;
	struct jhb100_mpxy_priv *mpxy = dev_get_priv(dev);

	if (!mpxy)
		return -ENOMEM;
	mpxy->dev = dev;
	ret = dev_read_phandle_with_args(dev,
					 "mboxes", "#mbox-cells", 0, 0, &args);
	if (ret) {
		printf("missing mboxes phandle\n");
		return ret;
	}

	if (args.args_count < 1) {
		printf("mboxes args missing channel-id\n");
		return -EINVAL;
	}

	/** Initiate MPXY MBOX transport */
	mpxy->channel_id = args.args[0];
	mpxy->shmem_buf = memalign(PAGE_SIZE, PAGE_SIZE);
	mpxy->shmem_size = PAGE_SIZE;

	ret = sbi_mpxy_setup_shmem(mpxy->shmem_buf);
	if (ret) {
		printf("Failed to set SHMEM\n");
		return -EINVAL;
	}

	mpxy->active = true;
	attr_count = ATTR_COUNT(SBI_MPXY_ATTR_MSG_SEND_TIMEOUT,
				SBI_MPXY_ATTR_MSG_PROT_ID);
	attr_buf = calloc(1, sizeof(u32) * attr_count);
	if (!attr_buf)
		return -ENOMEM;

	ret = sbi_mpxy_read_attrs(mpxy->shmem_buf, mpxy->channel_id, SBI_MPXY_ATTR_MSG_PROT_ID,
				  attr_count, attr_buf);
	if (ret) {
		printf("mpxy channel not available: %d\n", ret);
		goto fail_free_buff;
	}

	if (attr_buf[0] != SBI_MPXY_MSGPROTO_RPMI_ID) {
		printf("channel-%u: msgproto mismatch, expect:%u, found:%u\n", mpxy->channel_id,
			SBI_MPXY_MSGPROTO_RPMI_ID, attr_buf[0]);
		goto fail_free_buff;
	}

	version = RPMI_MSGPROTO_VERSION(RPMI_MAJOR_VER, RPMI_MINOR_VER);
	if (attr_buf[1] != version) {
		printf("channel-%u: msgproto version mismatch, expect:%u, found:%u\n",
			mpxy->channel_id, version, attr_buf[1]);
		goto fail_free_buff;
	}

	ret = sbi_mpxy_read_attrs(mpxy->shmem_buf, mpxy->channel_id,
				  SBI_MPXY_ATTR_MSGPROTO_ATTR_START, 1, attr_buf);
	if (ret) {
		printf("channel-%u: read attributes - %d\n", mpxy->channel_id, ret);
		goto fail_free_buff;
	}

	if (attr_buf[0] != RPMI_SRVGRP_VENDOR_SECURE) {
		printf("channel-%u ServiceGroup match failed, expected %x, found %x\n",
			mpxy->channel_id, RPMI_SRVGRP_VENDOR_SECURE, attr_buf[0]);
		goto fail_free_buff;
	}

	free(attr_buf);

	return 0;

fail_free_buff:
	free(attr_buf);
	return -EPROBE_DEFER;
}

static int jhb100_mpxy_sec_remove(struct udevice *dev)
{
	struct jhb100_mpxy_priv *mpxy = dev_get_priv(dev);

	if (!mpxy)
		return -ENOMEM;

	free(mpxy);

	return 0;
}

static const struct misc_ops jhb100_mpxy_sec_ops = {
	.ioctl = jhb100_mpxy_sec_ioctl,
};

static const struct udevice_id jhb100_mpxy_sec_ids[] = {
	{ .compatible = "riscv,rpmi-starfive-secure" },
	{}
};

U_BOOT_DRIVER(jhb100_sbi_mpxy_sec) = {
	.name		= "jhb100-sbi-mpxy-sec",
	.id		= UCLASS_MISC,
	.of_match	= jhb100_mpxy_sec_ids,
	.priv_auto	= sizeof(struct jhb100_mpxy_priv),
	.ops		= &jhb100_mpxy_sec_ops,
	.probe		= jhb100_mpxy_sec_probe,
	.remove		= jhb100_mpxy_sec_remove,
};
