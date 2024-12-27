// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#include <linux/types.h>
#include <linux/compat.h>
#include <mailbox.h>

/*
 * RPMI SERVICEGROUPS AND SERVICES
 */

/** RPMI ServiceGroups IDs */
enum rpmi_servicegroup_id {
	RPMI_SRVGRP_ID_MIN = 0,
	RPMI_SRVGRP_BASE = 0x0001,
	RPMI_SRVGRP_SYSTEM_RESET = 0x0002,
	RPMI_SRVGRP_SYSTEM_SUSPEND = 0x0003,
	RPMI_SRVGRP_HSM = 0x0004,
	RPMI_SRVGRP_CPPC = 0x0005,
	RPMI_SRVGRP_VOLTAGE = 0x0006,
	RPMI_SRVGRP_CLOCK = 0x0007,
	RPMI_SRVGRP_DEVICE_POWER = 0x0008,
	RPMI_SRVGRP_PERFORMANCE = 0x0009,
	RPMI_SRVGRP_ID_MAX_COUNT,

	/* Reserved range for service groups */
	RPMI_SRVGRP_RESERVE_START = RPMI_SRVGRP_ID_MAX_COUNT,
	RPMI_SRVGRP_RESERVE_END = 0x7FFF,

	/* Vendor/Implementation-specific service groups range */
	RPMI_SRVGRP_VENDOR_START = 0x8000,
	RPMI_SRVGRP_VENDOR_END = 0xFFFF,
};

/** RPMI Base ServiceGroup Service IDs */
enum rpmi_base_service_id {
	RPMI_BASE_SRV_ENABLE_NOTIFICATION = 0x01,
	RPMI_BASE_SRV_GET_IMPLEMENTATION_VERSION = 0x02,
	RPMI_BASE_SRV_GET_IMPLEMENTATION_IDN = 0x03,
	RPMI_BASE_SRV_GET_SPEC_VERSION = 0x04,
	RPMI_BASE_SRV_GET_PLATFORM_INFO = 0x05,
	RPMI_BASE_SRV_PROBE_SERVICE_GROUP = 0x06,
	RPMI_BASE_SRV_GET_ATTRIBUTES = 0x07,
	RPMI_BASE_SRV_SET_MSI = 0x08,
};

#define RPMI_BASE_FLAGS_F0_PRIVILEGE		BIT(2)
#define RPMI_BASE_FLAGS_F0_EV_NOTIFY		BIT(1)
#define RPMI_BASE_FLAGS_F0_MSI_EN		(1U)

enum rpmi_base_context_priv_level {
	RPMI_BASE_CONTEXT_PRIV_S_MODE,
	RPMI_BASE_CONTEXT_PRIV_M_MODE,
};

struct rpmi_base_get_attributes_resp {
	s32 status_code;
	u32 f0;
	u32 f1;
	u32 f2;
	u32 f3;
};

/**
 * RISC-V privilege levels associated with
 * RPMI context and service groups
 */
enum rpmi_privilege_level {
	RPMI_PRIVILEGE_S_MODE = 0,
	RPMI_PRIVILEGE_M_MODE = 1,
	RPMI_PRIVILEGE_LEVEL_MAX_IDX,
};

#define RPMI_PRIVILEGE_S_MODE_MASK	BIT(RPMI_PRIVILEGE_S_MODE)
#define RPMI_PRIVILEGE_M_MODE_MASK	BIT(RPMI_PRIVILEGE_M_MODE)

/**************** RPMI Transport Structures and Macros ***********/
#define RPMI_SLOT_SIZE_MIN			(64)
/** Queue layout */
#define RPMI_QUEUE_HEAD_SLOT		0
#define RPMI_QUEUE_TAIL_SLOT		1
#define RPMI_QUEUE_HEADER_SLOTS		2
#define GET_SERVICEGROUP_ID(msg)		\
({						\
	struct rpmi_message *mbuf = msg;	\
	le16_to_cpu(mbuf->header.servicegroup_id);\
})

#define GET_SERVICE_ID(msg)			\
({						\
	struct rpmi_message *mbuf = msg;	\
	mbuf->header.service_id;		\
})

#define GET_FLAGS(msg)				\
({						\
	struct rpmi_message *mbuf = msg;	\
	mbuf->header.flags;			\
})

#define GET_MESSAGE_ID(msg)			\
({						\
	struct rpmi_message *mbuf = msg;	\
	((u32)mbuf->header.flags << (RPMI_MSG_FLAGS_OFFSET * 8)) | \
	((u32)mbuf->header.service_id << (RPMI_MSG_SERVICE_ID_OFFSET * 8)) | \
	((u32)le16_to_cpu(mbuf->header.servicegroup_id)); \
})
/** ServiceGroup ID field byte offset */
#define RPMI_MSG_SERVICEGROUP_ID_OFFSET		(0x0)
#define RPMI_MSG_SERVICE_ID_OFFSET		(0x2)
#define RPMI_MSG_FLAGS_OFFSET			(0x3)

#define MAKE_MESSAGE_ID(__group_id, __service_id, __flags)	\
({						\
	u32 __ret = 0;				\
	__ret |= (u32)(__group_id) << (RPMI_MSG_SERVICEGROUP_ID_OFFSET * 8); \
	__ret |= (u32)(__service_id) << (RPMI_MSG_SERVICE_ID_OFFSET * 8); \
	__ret |= (u32)(__flags) << (RPMI_MSG_FLAGS_OFFSET * 8); \
	__ret;					\
})

#define GET_DLEN(msg)				\
({						\
	struct rpmi_message *mbuf = msg;	\
	le16_to_cpu(mbuf->header.datalen);	\
})

#define GET_TOKEN(msg)				\
({						\
	struct rpmi_message *mbuf = msg;	\
	le16_to_cpu(mbuf->header.token);	\
})

#define GET_MESSAGE_TYPE(msg)						\
({									\
	u8 flags = *((uint8_t *)(msg) + RPMI_MSG_FLAGS_OFFSET);	\
	((flags & RPMI_MSG_FLAGS_TYPE) >> RPMI_MSG_FLAGS_TYPE_POS));	\
})

enum rpmi_queue_type {
	RPMI_QUEUE_TYPE_REQ = 0,
	RPMI_QUEUE_TYPE_ACK = 1,
};

enum rpmi_queue_idx {
	RPMI_QUEUE_IDX_A2P_REQ = 0,
	RPMI_QUEUE_IDX_P2A_ACK = 1,
	RPMI_QUEUE_IDX_P2A_REQ = 2,
	RPMI_QUEUE_IDX_A2P_ACK = 3,
	RPMI_QUEUE_IDX_MAX_COUNT,
};

enum rpmi_reg_idx {
	RPMI_REG_IDX_DB_REG = 0, /* Doorbell register */
	RPMI_REG_IDX_MAX_COUNT,
};

/** Mailbox registers */
struct rpmi_mb_regs {
	/* doorbell from AP -> PuC*/
	volatile __le32 db_reg;
} __packed;

/** Single Queue Context Structure */
struct smq_queue_ctx {
	u32 queue_id;
	u32 num_slots;
	spinlock_t queue_lock;
	/* Type of queue - REQ or ACK */
	enum rpmi_queue_type queue_type;
	/* Pointers to the queue shared memory */
	volatile __le32 *headptr;
	volatile __le32 *tailptr;
	volatile u8 *buffer;
};

struct rpmi_shmem_mbox_controller {
	/* Driver specific members */
	u32 slot_size;
	u32 queue_count;
	struct rpmi_mb_regs *mb_regs;
	struct smq_queue_ctx queue_ctx_tbl[RPMI_QUEUE_IDX_MAX_COUNT];
	struct mbox_chan *base_chan;
	u32 impl_version;
	u32 impl_id;
	u32 spec_version;
	u32 plat_info_len;
	char *plat_info;
	struct {
		u8 f0_priv_level;
		bool f0_ev_notif_en;
		bool f0_msi_en;
	} base_flags;
};

/** RPMI Messages Types */
enum rpmi_message_type {
	/* Normal request backed with ack */
	RPMI_MSG_NORMAL_REQUEST = 0x0,
	/* Request without any ack */
	RPMI_MSG_POSTED_REQUEST = 0x1,
	/* Acknowledgment for normal request message */
	RPMI_MSG_ACKNOWLDGEMENT = 0x2,
	/* Notification message */
	RPMI_MSG_NOTIFICATION = 0x3,
};

/** RPMI Message Header */
struct rpmi_message_header {
	__le16 servicegroup_id;
	u8 service_id;
	u8 flags;
	__le16 datalen;
	__le16 token;
};

struct rpmi_message {
	struct rpmi_message_header header;
	u8 data[0];
} __packed;

#define MSG_TOKEN		0xDEAD
#define RX_TIMEOUT_S(x)		((x) * 1000000)
#define RPMI_DEF_RX_TIMEOUT_US	RX_TIMEOUT_S(15)
