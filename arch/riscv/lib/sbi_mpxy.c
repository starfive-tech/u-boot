// SPDX-License-Identifier: GPL-2.0-only
/*
 * RISC-V RPMI Proxy (MPXY) Helper functions
 *
 * Copyright (C) 2024 Starfive Technology International <www.starfivetech.com>
 *
 * Taken from Linux arch/riscv/kernel/mpxy-sbi.c
 */

#include <asm/sbi.h>
#include <linux/errno.h>
#include <malloc.h>

int sbi_mpxy_setup_shmem(u64 *buffer)
{
	struct sbiret sret;

	/**
	 * U-Boot setup of shmem is done in mpxy OVERWRITE mode.
	 * flags[1:0] = 00b
	 **/
	sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_SET_SHMEM,
			 (unsigned long)buffer, 0, 0, 0, 0, 0);
	if (sret.error) {
		free(buffer);
		return sret.error;
	}

	return 0;
}

int sbi_mpxy_read_attrs(u64 *buffer, u32 channelid, u32 base_attrid, u32 attr_count,
			void *attrs_buf)
{
	struct sbiret sret;

	if (!attr_count || !attrs_buf)
		return -EINVAL;

	sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_READ_ATTRS,
			 channelid, base_attrid, attr_count, 0, 0, 0);
	if (!sret.error)
		memcpy(attrs_buf, buffer, attr_count * sizeof(u32));

	return sret.error;
}

int sbi_mpxy_write_attrs(u64 *buffer, u32 channelid, u32 base_attrid, u32 attr_count,
			 void *attrs_buf)
{
	struct sbiret sret;

	if (!attr_count || !attrs_buf)
		return -EINVAL;

	memcpy(buffer, attrs_buf, attr_count * sizeof(u32));

	sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_WRITE_ATTRS,
			 channelid, base_attrid, attr_count, 0, 0, 0);

	return sret.error;
}

int sbi_mpxy_send_message_withresp(u64 *buffer, u32 channelid, u32 msgid,
				   void *tx, u64 tx_msglen,
				   void *rx, u64 *rx_msglen)
{
	struct sbiret sret;

	/**
	 * Message protocols allowed to have no data in
	 * messages
	 */
	if (tx_msglen)
		memcpy(buffer, tx, tx_msglen);

	sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_SEND_MSG_WITH_RESP,
			 channelid, msgid, tx_msglen, 0, 0, 0);

	if (rx && !sret.error) {
		memcpy(rx, buffer, sret.value);
		if (rx_msglen)
			*rx_msglen = sret.value;
	}

	return sret.error;
}

int sbi_mpxy_send_message_noresp(u64 *buffer, u32 channelid, u32 msgid,
				 void *tx, unsigned long tx_msglen)
{
	struct sbiret sret;

	/**
	 * Message protocols allowed to have no data in
	 * messages.
	 */
	if (tx_msglen)
		memcpy(buffer, tx, tx_msglen);

	sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_SEND_MSG_NO_RESP,
			 channelid, msgid, tx_msglen, 0, 0, 0);

	return sret.error;
}

int sbi_mpxy_get_notifications(u64 *buffer, u32 channelid, void *rx, u64 *rx_msglen)
{
	struct sbiret sret;

	if (!rx)
		return -EINVAL;

	sret = sbi_ecall(SBI_EXT_MPXY, SBI_EXT_MPXY_GET_NOTIFICATION_EVENTS,
			 channelid, 0, 0, 0, 0, 0);
	if (!sret.error) {
		memcpy(rx, buffer, sret.value);
		if (rx_msglen)
			*rx_msglen = sret.value;
	}

	return sret.error;
}
