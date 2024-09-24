/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2015 Regents of the University of California
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 *
 * Taken from Linux arch/riscv/include/asm/sbi.h
 */

#ifndef _ASM_RISCV_SBI_H
#define _ASM_RISCV_SBI_H

#include <linux/types.h>

enum sbi_ext_id {
	SBI_EXT_0_1_SET_TIMER = 0x0,
	SBI_EXT_0_1_CONSOLE_PUTCHAR = 0x1,
	SBI_EXT_0_1_CONSOLE_GETCHAR = 0x2,
	SBI_EXT_0_1_CLEAR_IPI = 0x3,
	SBI_EXT_0_1_SEND_IPI = 0x4,
	SBI_EXT_0_1_REMOTE_FENCE_I = 0x5,
	SBI_EXT_0_1_REMOTE_SFENCE_VMA = 0x6,
	SBI_EXT_0_1_REMOTE_SFENCE_VMA_ASID = 0x7,
	SBI_EXT_0_1_SHUTDOWN = 0x8,
	SBI_EXT_BASE = 0x10,
	SBI_EXT_TIME = 0x54494D45,
	SBI_EXT_IPI = 0x735049,
	SBI_EXT_RFENCE = 0x52464E43,
	SBI_EXT_HSM = 0x48534D,
	SBI_EXT_SRST = 0x53525354,
	SBI_EXT_PMU = 0x504D55,
	SBI_EXT_DBCN = 0x4442434E,
	SBI_EXT_SUSP = 0x53555350,
	SBI_EXT_CPPC = 0x43505043,
	SBI_EXT_NACL = 0x4E41434C,
	SBI_EXT_STA = 0x535441,
	SBI_EXT_DBTR = 0x44425452,
	SBI_EXT_SSE = 0x535345,
	SBI_EXT_MPXY = 0x4D505859,
};

enum sbi_ext_base_fid {
	SBI_EXT_BASE_GET_SPEC_VERSION = 0,
	SBI_EXT_BASE_GET_IMP_ID,
	SBI_EXT_BASE_GET_IMP_VERSION,
	SBI_EXT_BASE_PROBE_EXT,
	SBI_EXT_BASE_GET_MVENDORID,
	SBI_EXT_BASE_GET_MARCHID,
	SBI_EXT_BASE_GET_MIMPID,
};

enum sbi_ext_time_fid {
	SBI_EXT_TIME_SET_TIMER = 0,
};

enum sbi_ext_ipi_fid {
	SBI_EXT_IPI_SEND_IPI = 0,
};

enum sbi_ext_rfence_fid {
	SBI_EXT_RFENCE_REMOTE_FENCE_I = 0,
	SBI_EXT_RFENCE_REMOTE_SFENCE_VMA,
	SBI_EXT_RFENCE_REMOTE_SFENCE_VMA_ASID,
	SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA_VMID,
	SBI_EXT_RFENCE_REMOTE_HFENCE_GVMA,
	SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA_ASID,
	SBI_EXT_RFENCE_REMOTE_HFENCE_VVMA,
};

enum sbi_ext_hsm_fid {
	SBI_EXT_HSM_HART_START = 0,
	SBI_EXT_HSM_HART_STOP,
	SBI_EXT_HSM_HART_STATUS,
	SBI_EXT_HSM_HART_SUSPEND,
};

enum sbi_hsm_hart_status {
	SBI_HSM_HART_STATUS_STARTED = 0,
	SBI_HSM_HART_STATUS_STOPPED,
	SBI_HSM_HART_STATUS_START_PENDING,
	SBI_HSM_HART_STATUS_STOP_PENDING,
	SBI_HSM_HART_STATUS_SUSPEND_PENDING,
	SBI_HSM_HART_STATUS_RESUME_PENDING,
};

enum sbi_ext_srst_fid {
	SBI_EXT_SRST_RESET = 0,
};

enum sbi_srst_reset_type {
	SBI_SRST_RESET_TYPE_SHUTDOWN = 0,
	SBI_SRST_RESET_TYPE_COLD_REBOOT,
	SBI_SRST_RESET_TYPE_WARM_REBOOT,
};

enum sbi_srst_reset_reason {
	SBI_SRST_RESET_REASON_NONE = 0,
	SBI_SRST_RESET_REASON_SYS_FAILURE,
};

enum sbi_ext_dbcn_fid {
	SBI_EXT_DBCN_CONSOLE_WRITE = 0,
	SBI_EXT_DBCN_CONSOLE_READ,
	SBI_EXT_DBCN_CONSOLE_WRITE_BYTE,
};

enum sbi_ext_mpxy_fid {
	SBI_EXT_MPXY_GET_SHMEM_SIZE = 0,
	SBI_EXT_MPXY_SET_SHMEM,
	SBI_EXT_MPXY_GET_CHANNEL_IDS,
	SBI_EXT_MPXY_READ_ATTRS,
	SBI_EXT_MPXY_WRITE_ATTRS,
	SBI_EXT_MPXY_SEND_MSG_WITH_RESP,
	SBI_EXT_MPXY_SEND_MSG_NO_RESP,
	SBI_EXT_MPXY_GET_NOTIFICATION_EVENTS,
};

enum sbi_mpxy_attr_id {
	/* Standard channel attributes managed by MPXY framework */
	SBI_MPXY_ATTR_MSG_PROT_ID		= 0x00000000,
	SBI_MPXY_ATTR_MSG_PROT_VER		= 0x00000001,
	SBI_MPXY_ATTR_MSG_MAX_LEN		= 0x00000002,
	SBI_MPXY_ATTR_MSG_SEND_TIMEOUT		= 0x00000003,
	SBI_MPXY_ATTR_MSG_COMPLETION_TIMEOUT	= 0x00000004,
	SBI_MPXY_ATTR_CHANNEL_CAPABILITY	= 0x00000005,
	SBI_MPXY_ATTR_SSE_EVENT_ID		= 0x00000006,
	SBI_MPXY_ATTR_MSI_CONTROL		= 0x00000007,
	SBI_MPXY_ATTR_MSI_ADDR_LO		= 0x00000008,
	SBI_MPXY_ATTR_MSI_ADDR_HI		= 0x00000009,
	SBI_MPXY_ATTR_MSI_DATA			= 0x0000000A,
	SBI_MPXY_ATTR_EVENTS_STATE_CONTROL	= 0x0000000B,
	SBI_MPXY_ATTR_STD_ATTR_MAX_IDX,
	/* Message protocol specific attributes, managed by
	 * message protocol driver
	 */
	SBI_MPXY_ATTR_MSGPROTO_ATTR_START	= 0x80000000,
	SBI_MPXY_ATTR_MSGPROTO_ATTR_END		= 0xffffffff
};

enum sbi_mpxy_msgproto_id {
	SBI_MPXY_MSGPROTO_RPMI_ID = 0x0,
};

struct sbi_mpxy_msi_info {
	u32 msi_addr_lo;
	u32 msi_addr_hi;
	u32 msi_data;
};

/**
 * Channel attributes.
 * NOTE: The sequence of attribute fields are as per the
 * defined sequence in the attribute table in spec(or as
 * per the enum sbi_mpxy_attr_id).
 */
struct sbi_mpxy_channel_attrs {
	/* Message protocol ID */
	u32 msg_proto_id;
	/* Message protocol Version */
	u32 msg_proto_version;
	/* Message protocol maximum message length */
	u32 msg_max_len;
	/* Message protocol message send timeout in microseconds */
	u32 msg_send_timeout;
	/* Bit array for channel capabilities */
	u32 capability;
	/* MSI enable/disable control knob */
	u32 msi_control;
	/* Channel MSI info */
	struct sbi_mpxy_msi_info msi_info;
	/* SSE Event Id */
	u32 sse_event_id;
	/* Events State Control */
	u32 eventsstate_ctrl;
};

#ifdef CONFIG_SBI_V01
#define SBI_EXT_SET_TIMER		SBI_EXT_0_1_SET_TIMER
#define SBI_FID_SET_TIMER		0
#define SBI_EXT_SEND_IPI		SBI_EXT_0_1_SEND_IPI
#define SBI_FID_SEND_IPI		0
#define SBI_EXT_REMOTE_FENCE_I		SBI_EXT_0_1_REMOTE_FENCE_I
#define SBI_FID_REMOTE_FENCE_I		0
#define SBI_EXT_REMOTE_SFENCE_VMA	SBI_EXT_0_1_REMOTE_SFENCE_VMA
#define SBI_FID_REMOTE_SFENCE_VMA	0
#define SBI_EXT_REMOTE_SFENCE_VMA_ASID	SBI_EXT_0_1_REMOTE_SFENCE_VMA_ASID
#define SBI_FID_REMOTE_SFENCE_VMA_ASID	0
#else
#define SBI_EXT_SET_TIMER		SBI_EXT_TIME
#define SBI_FID_SET_TIMER		SBI_EXT_TIME_SET_TIMER
#define SBI_EXT_SEND_IPI		SBI_EXT_IPI
#define SBI_FID_SEND_IPI		SBI_EXT_IPI_SEND_IPI
#define SBI_EXT_REMOTE_FENCE_I		SBI_EXT_RFENCE
#define SBI_FID_REMOTE_FENCE_I		SBI_EXT_RFENCE_REMOTE_FENCE_I
#define SBI_EXT_REMOTE_SFENCE_VMA	SBI_EXT_RFENCE
#define SBI_FID_REMOTE_SFENCE_VMA	SBI_EXT_RFENCE_REMOTE_SFENCE_VMA
#define SBI_EXT_REMOTE_SFENCE_VMA_ASID	SBI_EXT_RFENCE
#define SBI_FID_REMOTE_SFENCE_VMA_ASID	SBI_EXT_RFENCE_REMOTE_SFENCE_VMA_ASID
#define SBI_EXT_VENDOR_START		0x09000000
#define SBI_EXT_VENDOR_END		0x09FFFFFF
#endif

#define SBI_SPEC_VERSION_MAJOR_SHIFT	24
#define SBI_SPEC_VERSION_MAJOR_MASK	0x7f
#define SBI_SPEC_VERSION_MINOR_MASK	0xffffff

/* SBI return error codes */
#define SBI_SUCCESS			0
#define SBI_ERR_FAILURE			-1
#define SBI_ERR_NOT_SUPPORTED		-2
#define SBI_ERR_INVALID_PARAM		-3
#define SBI_ERR_DENIED			-4
#define SBI_ERR_INVALID_ADDRESS		-5
#define SBI_ERR_NO_SHMEM		-9
#define SBI_ERR_INVALID_STATE		-10
#define SBI_ERR_BAD_RANGE		-11
#define SBI_ERR_NOT_IMPLEMENTED		-12
#define SBI_ERR_TIMEOUT			-13
#define SBI_ERR_IO			-14
struct sbiret {
	long error;
	long value;
};

struct sbiret sbi_ecall(int ext, int fid, unsigned long arg0,
			unsigned long arg1, unsigned long arg2,
			unsigned long arg3, unsigned long arg4,
			unsigned long arg5);

#ifdef CONFIG_SBI_V01
void sbi_console_putchar(int ch);
int sbi_console_getchar(void);
void sbi_clear_ipi(void);
void sbi_shutdown(void);
void sbi_send_ipi(const unsigned long *hart_mask);
void sbi_remote_fence_i(const unsigned long *hart_mask);
void sbi_remote_sfence_vma(const unsigned long *hart_mask,
			   unsigned long start,
			   unsigned long size);
void sbi_remote_sfence_vma_asid(const unsigned long *hart_mask,
				unsigned long start,
				unsigned long size,
				unsigned long asid);
#endif

/* Make SBI version */
static inline unsigned long sbi_mk_version(unsigned long major,
					   unsigned long minor)
{
	return ((major & SBI_SPEC_VERSION_MAJOR_MASK) <<
		SBI_SPEC_VERSION_MAJOR_SHIFT) | minor;
}

void sbi_set_timer(uint64_t stime_value);
long sbi_get_spec_version(void);
int sbi_get_impl_id(void);
int sbi_get_impl_version(long *version);
int sbi_probe_extension(int ext);
int sbi_get_mvendorid(long *mvendorid);
int sbi_get_marchid(long *marchid);
int sbi_get_mimpid(long *mimpid);
void sbi_srst_reset(unsigned long type, unsigned long reason);
int sbi_dbcn_write_byte(unsigned char ch);
unsigned long sbi_get_vendor_extid(void);

#ifdef CONFIG_SBI_MPXY
int sbi_mpxy_setup_shmem(u64 *buffer);
int sbi_mpxy_read_attrs(u64 *buffer, u32 channelid, u32 base_attrid, u32 attr_count,
			void *attrs_buf);
int sbi_mpxy_write_attrs(u64 *buffer, u32 channelid, u32 base_attrid, u32 attr_count,
			 void *attrs_buf);
int sbi_mpxy_send_message_withresp(u64 *buffer, u32 channelid, u32 msgid,
				   void *tx, u64 tx_msglen,
				   void *rx, u64 *rx_msglen);
int sbi_mpxy_send_message_noresp(u64 *buffer, u32 channelid, u32 msgid,
				 void *tx, unsigned long tx_msglen);
int sbi_mpxy_get_notifications(u64 *buffer, u32 channelid, void *rx, u64 *rx_msglen);
#endif
#endif
