// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#include <common.h>
#include <clk.h>
#include <dm.h>
#include <log.h>
#include <mailbox-uclass.h>
#include <malloc.h>
#include <dm/device_compat.h>
#include <linux/bitops.h>
#include <linux/compat.h>
#include <mailbox.h>
#include <asm/atomic.h>
#include <linux/types.h>
#include <linux/byteorder/little_endian.h>
#include <linux/delay.h>
#include <linux/iopoll.h>
#include "mailbox_rpmi_shmem.h"
#include <dm/ofnode_decl.h>
#include <dm/lists.h>

struct rpmi_mbox_priv {
	struct rpmi_shmem_mbox_controller *mctl;
};

static bool __smq_queue_full(struct smq_queue_ctx *qctx)
{
	return ((le32_to_cpu(*qctx->tailptr) + 1) % qctx->num_slots ==
			le32_to_cpu(*qctx->headptr)) ? true : false;
}

static bool __smq_queue_empty(struct smq_queue_ctx *qctx)
{
	return (le32_to_cpu(*qctx->headptr) ==
		le32_to_cpu(*qctx->tailptr)) ? true : false;
}

static int rpmi_shmem_mbox_tx(struct mbox_chan *chan, const void *data)
{
	struct smq_queue_ctx *qctx;
	u32 i, tailidx;
	void *dst, *src;

	struct rpmi_mbox_priv *mbox_dev = dev_get_priv(chan->dev);

	if (!mbox_dev) {
		dev_err(chan->dev, "No priv data found\n");
		return -ENODEV;
	}

	struct rpmi_shmem_mbox_controller *mctl = mbox_dev->mctl;
	struct rpmi_message *msg = (struct rpmi_message *)data;
	struct rpmi_message_header header = msg->header;

	qctx = &mctl->queue_ctx_tbl[RPMI_QUEUE_IDX_A2P_REQ];

	if (__smq_queue_full(qctx))
		return -ENOMEM;

	/* Tx sanity checks */
	if (header.datalen > (mctl->slot_size - sizeof(struct rpmi_message_header)))
		return -EINVAL;

	tailidx = le32_to_cpu(*qctx->tailptr);

	/* Write header into the slot */
	dst = (char *)qctx->buffer + (tailidx * mctl->slot_size);
	memcpy(dst, &header, sizeof(header));
	dst += sizeof(header);

	/* Write data into the slot */
	if (header.datalen) {
		src = msg->data;
		for (i = 0; i < (header.datalen / sizeof(u32)); i++)
			((u32 *)dst)[i] = cpu_to_le32(((u32 *)src)[i]);
	}

	/** Update tail index */
	*qctx->tailptr = cpu_to_le32(tailidx + 1) % qctx->num_slots;

	writel(cpu_to_le32(1), &mctl->mb_regs->db_reg);

	return 0;
}

static int rpmi_shmem_mbox_rx(struct mbox_chan *chan, void *data)
{
	struct smq_queue_ctx *qctx;
	u32 i, tmp, pos, msgidn, headidx, tailidx, rx_datalen;
	void *dst, *src;
	struct rpmi_message *msg;

	struct rpmi_mbox_priv *mbox_dev = dev_get_priv(chan->dev);

	if (!mbox_dev) {
		dev_err(chan->dev, "No priv data found\n");
		return -ENODEV;
	}

	struct rpmi_shmem_mbox_controller *mctl = mbox_dev->mctl;
	struct rpmi_message *args = (struct rpmi_message *)data;

	/* Rx */
	qctx = &mctl->queue_ctx_tbl[RPMI_QUEUE_IDX_P2A_ACK];

	if (__smq_queue_empty(qctx))
		return -ENODATA;

	/* Rx sanity checks */
	if (args->header.datalen > (mctl->slot_size - sizeof(struct rpmi_message_header)))
		return -EINVAL;

	headidx = *qctx->headptr;
	tailidx = *qctx->tailptr;
	msgidn = MAKE_MESSAGE_ID(args->header.servicegroup_id,
				 args->header.service_id,
				 args->header.flags);

	/* Find the Rx message with matching token */
	pos = headidx;
	while (pos != tailidx) {
		src = (void *)qctx->buffer + (pos * mctl->slot_size);
		if ((GET_MESSAGE_ID(src) == msgidn) || (GET_TOKEN(src) == args->header.token)) {
			break;
		}
		pos = (pos + 1) % qctx->num_slots;
	}
	if (pos == tailidx)
		return -ENODATA;

	/* If Rx message is not first message then make it first message */
	if (pos != headidx) {
		src = (void *)qctx->buffer + (pos * mctl->slot_size);
		dst = (void *)qctx->buffer + (headidx * mctl->slot_size);
		for (i = 0; i < mctl->slot_size / sizeof(u32); i++) {
			tmp = ((u32 *)dst)[i];
			((u32 *)dst)[i] = ((u32 *)src)[i];
			((u32 *)src)[i] = tmp;
		}
	}
	msg = (void *)qctx->buffer + (headidx * mctl->slot_size);

	/* Extract data from the first message */
	args->header.datalen = rx_datalen = GET_DLEN(msg);
	src = (void *)msg + sizeof(struct rpmi_message_header);
	dst = args->data;
	for (i = 0; i < (rx_datalen / sizeof(u32)); i++)
		((u32 *)dst)[i] = le32_to_cpu(((u32 *)src)[i]);

	/* Update the head/read index */
	*qctx->headptr = cpu_to_le32(headidx + 1) % qctx->num_slots;

	return 0;
}

static int rpmi_shmem_mbox_request_chan(struct mbox_chan *chan)
{
	/* Service group id not defined or in reserved range is invalid */
	if ((chan->id >= RPMI_SRVGRP_ID_MAX_COUNT && chan->id <= RPMI_SRVGRP_RESERVE_END) ||
	    chan->id > RPMI_SRVGRP_VENDOR_END)
		return -EINVAL;

	return 0;
}

static int rpmi_shmem_simple_xlate(struct mbox_chan *chan, struct ofnode_phandle_args *pargs)
{
	if (pargs->args_count < 1)
		return -EINVAL;

	chan->id = pargs->args[0];

	return 0;
}

static int rpmi_shmem_transport_init(struct udevice *dev, struct rpmi_shmem_mbox_controller *mctl)
{
	int count, len, ret, qid;
	u64 reg_addr, reg_size;
	struct smq_queue_ctx *qctx;

	/* get queue slot size in bytes */
	ret = dev_read_u32(dev, "riscv,slot-size", &len);
	if (ret) {
		dev_dbg(dev, "Missing riscv,slot-size\n");
		return -EINVAL;
	}

	mctl->slot_size = len;
	if (mctl->slot_size < RPMI_SLOT_SIZE_MIN) {
		dev_dbg(dev, "%s: slot_size < mimnum required message size\n", __func__);
		mctl->slot_size = RPMI_SLOT_SIZE_MIN;
	}

	/*
	 * queue names count is taken as the number of queues
	 * supported which make it mandatory to provide the
	 * name of the queue.
	 */
	count = dev_read_string_count(dev, "reg-names");
	if (count < 0 ||
	    count > (RPMI_QUEUE_IDX_MAX_COUNT + RPMI_REG_IDX_MAX_COUNT))
		return -EINVAL;
	mctl->queue_count = count - RPMI_REG_IDX_MAX_COUNT;

	/* parse all queues and populate queues context structure */
	for (qid = 0; qid < mctl->queue_count; qid++) {
		qctx = &mctl->queue_ctx_tbl[qid];

		/* get each queue share-memory base address and size*/
		reg_addr = dev_read_addr_size_index(dev, qid, &reg_size);
		if (reg_addr < 0 || !reg_size)
			return -ENOENT;
		/* calculate number of slots in each queue */
		qctx->num_slots =
			(reg_size - (mctl->slot_size * RPMI_QUEUE_HEADER_SLOTS)) / mctl->slot_size;

		/* setup queue pointers */
		qctx->headptr = ((void *)(unsigned long)reg_addr) +
				RPMI_QUEUE_HEAD_SLOT * mctl->slot_size;
		qctx->tailptr = ((void *)(unsigned long)reg_addr) +
				RPMI_QUEUE_TAIL_SLOT * mctl->slot_size;
		qctx->buffer = ((void *)(unsigned long)reg_addr) +
				RPMI_QUEUE_HEADER_SLOTS * mctl->slot_size;

		memset((void *)qctx->headptr, 0, qctx->num_slots * mctl->slot_size);
		memset((void *)qctx->tailptr, 0, qctx->num_slots * mctl->slot_size);
		memset((void *)qctx->buffer, 0, qctx->num_slots * mctl->slot_size);

		/* store the index as queue_id */
		qctx->queue_id = qid;
		spin_lock_init(qctx->queue_lock);
	}

	/* fetch doorbell register address*/
	reg_addr = dev_read_addr_size_index(dev, qid, &reg_size);
	mctl->mb_regs = (void *)(unsigned long)reg_addr;

	return 0;
}

static int rpmi_shmem_mbox_probe(struct udevice *dev)
{
	struct rpmi_mbox_priv *mbox_dev = dev_get_priv(dev);
	struct rpmi_shmem_mbox_controller *mctl;
	u32 ret, addr;

	mctl = calloc(1, sizeof(*mctl));
	if (!mctl)
		return -ENOMEM;

	addr = dev_read_addr(dev);
	if (addr == FDT_ADDR_T_NONE)
		return -EINVAL;

	ret = rpmi_shmem_transport_init(dev, mctl);
	if (ret)
		return ret;

	mbox_dev->mctl = mctl;

	return 0;
}

static int rpmi_shmem_mbox_child_bind(struct udevice *dev)
{
	struct udevice *child;
	ofnode node;

	/** Iterate over child nodes and bind them */
	dev_for_each_subnode(node, dev) {
		const char *child_compatible;
		const char *child_name = ofnode_get_name(node);
		int ret = 0;
		int index = 0;

		while (!ofnode_read_string_index(node, "compatible", index++, &child_compatible)) {
			if (!strcmp(child_compatible, "riscv,rpmi-jhb100-sec"))
				break;
		}

		ret = device_bind_driver_to_node(dev, "rpmi_srv_grp_starfive_bmc_sec_rt",
						 child_name, node, &child);
		if (ret)
			return ret;
	}
	return 0;
}

static int rpmi_shmem_mbox_remove(struct udevice *dev)
{
	struct rpmi_mbox_priv *mbox_dev = dev_get_priv(dev);

	free(mbox_dev->mctl);

	return 0;
}

static const struct udevice_id rpmi_mbox_ids[] = {
	{ .compatible = "riscv,rpmi-shmem-mbox" },
	{ }
};

struct mbox_ops rpmi_mbox_shmem_ops = {
	.request = rpmi_shmem_mbox_request_chan,
	.send = rpmi_shmem_mbox_tx,
	.recv = rpmi_shmem_mbox_rx,
	.of_xlate = rpmi_shmem_simple_xlate,
};

U_BOOT_DRIVER(rpmi_mbox_shmem) = {
	.name		= "rpmi_mbox_shmem",
	.id		= UCLASS_MAILBOX,
	.of_match	= rpmi_mbox_ids,
	.probe		= rpmi_shmem_mbox_probe,
	.bind		= rpmi_shmem_mbox_child_bind,
	.remove		= rpmi_shmem_mbox_remove,
	.priv_auto	= sizeof(struct rpmi_mbox_priv),
	.ops		= &rpmi_mbox_shmem_ops,
};
