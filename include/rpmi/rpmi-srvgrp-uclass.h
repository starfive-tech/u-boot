// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

struct rpmi_chan_priv {
	struct mbox_chan *chan;
	struct rpmi_srv_grp_priv *group;
};

struct rpmi_service {
	/** ID of the service */
	u8 id;
	/** Minimum data length for handling request */
	u32 min_tx_len;
	u32 max_tx_len;
	u32 min_rx_len;
	u32 max_rx_len;
};

/** RPMI service group instance */
struct rpmi_srv_grp_priv {
	/** Name of the service group */
	const char *name;
	/** ID of the service group */
	u16 servicegroup_id;
	/** Maximum service ID of the service group */
	u16 max_service_id;
	/** Service group version */
	u32 servicegroup_version;
	/**
	 * RISC-V privilagel level bitmap where this group
	 * is allowed to be accessible. enum rpmi_privilege_level
	 * values represents the bit positions which if are
	 * set, the access to that privilegel level is enabled
	 */
	u32 privilege_level_bitmap;
	/** Array of services indexed by service ID */
	struct rpmi_service *services;
	/** Lock to synchronize service group access (optional) */
	void *lock;
};

int rpmi_process_msg(struct udevice *dev, u16 service_id, void *data);
struct rpmi_service *find_rpmi_srvid(struct udevice *dev, u32 service_id);

struct rpmi_srvgrp_ops {
	int (*rpmi_process_msg)(struct udevice *dev, u16 service_id, void *data);
};
