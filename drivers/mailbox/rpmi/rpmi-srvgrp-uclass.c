// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#include <linux/types.h>
#include <common.h>
#include <dm.h>
#include <dm/device_compat.h>
#include <rpmi/rpmi-srvgrp-uclass.h>

int rpmi_process_msg(struct udevice *dev, u16 service_id, void *data)
{
	struct rpmi_srvgrp_ops *ops = (struct rpmi_srvgrp_ops *)device_get_ops(dev);

	if (!ops->rpmi_process_msg)
		return -ENOSYS;

	return ops->rpmi_process_msg(dev, service_id, data);
}

struct rpmi_service *find_rpmi_srvid(struct udevice *dev, u32 service_id)
{
	struct rpmi_chan_priv *chan_priv = dev_get_priv(dev);

	if (!chan_priv) {
		dev_err(dev, "No priv data found\n");
		return NULL;
	}

	struct rpmi_srv_grp_priv *group = chan_priv->group;

	if (!group) {
		dev_err(dev, "Service group not registered\n");
		return NULL;
	}

	struct rpmi_service *srv = group->services;
	int sid;

	for (sid = 0; srv[sid].id < group->max_service_id; sid++) {
		if (srv[sid].id == (u8)service_id)
			return &srv[sid];
	}

	return NULL;
}

UCLASS_DRIVER(rpmi_svc_grp) = {
	.id		= UCLASS_RPMI_SRV_GRP,
	.name		= "rpmi_srv_grp",
};
