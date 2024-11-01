// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 Starfive Technology International <www.starfivetech.com>
 *
 */

#ifndef _SECURE_VAB_H_
#define _SECURE_VAB_H_

#include <linux/sizes.h>
#include <linux/stddef.h>
#include <linux/bitops.h>

#define BITS_PER_WORD		32
#define NUM_WORD(n)		((n) / BITS_PER_WORD)
#define BUF256_WORD_32_NUM	NUM_WORD(256)

/*
 * BIF_V1
 */
#define BIF_MAGIC_NUM			0x00464942
#define BIF_VERSION_1			1
#define BIF_NV_COUNTER_LEN		16
#define BIF_MAX_AES_KEY_NUM		3
#define BIF_MAX_EC_PUBKEY_NUM		8

/*
 * Image Flags
 */
#define BIF_IS_ENCRYPTED		BIT(0)
#define BIF_IS_ANTI_ROLLBACK_ON		BIT(1)
#define BIF_IS_SECONDARY		BIT(2)
#define BIF_SECURE_BOOT_EN		BIT(3)

/*
 * Key revocation
 */
#define BIF_AES_KEY_REVOCATION(v)	(((v) >> 24) & (0x7))
#define BIF_PUKT2_KEYS_REVOCATION(v)	(((v) >> 16) & (0xff))
#define BIF_PUKT1_KEYS_REVOCATION(v)	(((v) >> 8) & (0xff))
#define BIF_PUKT0_KEYS_REVOCATION(v)	(((v) >> 0) & (0xff))

struct ecc_public_key {
	unsigned int x[BUF256_WORD_32_NUM];
	unsigned int y[BUF256_WORD_32_NUM];
};

struct ecc_parameters {
	unsigned int ptr_p[BUF256_WORD_32_NUM];
	unsigned int ptr_a[BUF256_WORD_32_NUM];
	unsigned int ptr_b[BUF256_WORD_32_NUM];
	unsigned int ptr_Gx[BUF256_WORD_32_NUM];
	unsigned int ptr_Gy[BUF256_WORD_32_NUM];
	unsigned int ptr_n[BUF256_WORD_32_NUM];
	unsigned int reserved[16];
};

struct sec_image_head {
	u32 magic_num;			/* 0x0, Boot Image Header Magic Number (0x00464942) */
	u32 bif_version;		/* 0x4, Boot Image Header Version */
	u32 entry_point_l;		/* 0x8, Low 32bits, "Data" shall be loaded and excuted */
	u32 entry_point_h;		/* 0xC, High 32bits, "Data" shall be loaded and excuted */
	u32 nv_counter[4];		/* 0x10, 128-bit Anti-Rollback Counter */
	u32 otp_nv_counter_off;		/* 0x20, Index of the Platform Non-Volatile (NV) Counter
					 *       reside in Secure OTP
					 */
	u8 otp_img_aes_key_idx;		/* 0x24, Firmware AES encryption key index (Kfw_x) */
	u8 otp_pubkey_table_idx;	/* 0x25, range 0~2, for ec_pubkey_table validation against
					 *       HASH in Secure OTP
					 */
	u8 reserved0[2];
	u32 ec_pubkey_table_off;	/* 0x28, Offset to "EC-256 Public Key" */
	u8 ec_pubkey_count;		/* 0x2C, The number of ec_pubkeys in the table */
	u8 ec_pubkey_select;		/* 0x2D, [0, ec_pubkey_count - 1] */
	u8 reserved1[2];
	u32 sign_off;			/* 0x30, Offset to "Signature" */
	u32 sign_len;			/* 0x34, Length of "Signature" */
	u32 img_off;			/* 0x38, Offset to "Image" */
	u32 img_len;			/* 0x3C, Length of "Image" */
	u32 img_crc32;			/* 0x40, CRC32 of data */
	u32 img_flags;			/* 0x44, Multiple flags:
					 *       [0] - AES encrypted
					 *       [1] - anti-rollback on
					 *       [2] - Secondary Flag
					 *       [3] - Secure boot enable
					 *       [31:4] - TBD
					 */
	u32 keys_revocation;		/* 0x48, Revocation for ec and aes keys, 1 to revoke
					 *       relevant key
					 *      [31:27] - reserved
					 *      [26:24] - AES keys revocation
					 *      [23:16] - ec_pubkey_table #2 keys revocation
					 *      [15:8] - ec_pubkey_table #1 keys revocation
					 *      [7:0] - ec_pubkey_table #0 keys revocation
					 */
	u8 reserved2[4];
	u8 aes_iv[16];			 /* 0x50, Seed of the AES-256 IV */
	struct ecc_parameters ec_params; /* 0x60, EC-256 curve parameters: */
	u32 ekek[BUF256_WORD_32_NUM];	 /* 0x160, Encrypted Key Encryption Key */
	u32 edek[BUF256_WORD_32_NUM];	 /* 0x180, Encrypted Data Encryption Key */
};
#endif /* _SECURE_VAB_H_ */
