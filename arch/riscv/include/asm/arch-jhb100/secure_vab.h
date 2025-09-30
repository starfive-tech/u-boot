// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#ifndef _SECURE_VAB_H_
#define _SECURE_VAB_H_

#include <linux/sizes.h>
#include <linux/stddef.h>
#include <linux/bitops.h>

#define CAPSULE_COMPONENT_MAX_COUNT	(32)
#define CAPSULE_COMPS_PER_REG		(4)
#define BIF_HDR_LENGTH			0x200
#define BIF_MFT_LENGTH			0xE00
#define BIF_SIG_LENGTH			0x200
#define CAP_STORAGE_TYPE_EMMC		0x01
#define CAP_STORAGE_TYPE_UFS		0x02
#define CAP_STORAGE_TYPE_SFC		0x03

#define BIF_IMG_TYPE_L0			0x0
#define BIF_IMG_TYPE_L1			0x1
#define BIF_IMG_TYPE_SPL		0x2
#define BIF_IMG_TYPE_OPENSBI		0x3
#define BIF_IMG_TYPE_UBOOT_PROP		0x4
#define BIF_IMG_TYPE_UBOOT_DTB		0x5
#define BIF_IMG_TYPE_LINUX_KERNEL	0x6
#define BIF_IMG_TYPE_LINUX_KERNEL_DTB	0x7
#define BIF_IMG_TYPE_ROFS		0x8
#define BIF_IMG_TYPE_FILTER_CONFIG	0x9
#define BIF_IMG_TYPE_RAW_IMG		0xA
#define BIF_IMG_TYPE_CAPSULE		0xFE

struct bif_image_hdr {
	u32 bif_magic;		// 0x0 BIF Magic Number. ("BIF\0", 0x42494600)
#define BIF_MAGIC_NUM					(0x00464942)
	u32 version;		// 0x4 Version:
				//   [22:16] Image version
				//   [15:8] Image Type
				//   [7:0] spec version = 0x02
#define GET_BIF_IMAGE_VERSION(val)			(((val) >> 16) & 0x7F)
#define GET_BIF_SPEC_VERSION(val)			(((val) >> 0) & 0xFF)
#define   SUPPORTED_BIF_SPEC_VERSION			(0x2)
	u32 iflags;             // 0x8 Image Control Flags:
				//   [31] Image Data Encryption enabled
				//   (0-unencrypted, 1-encrypted by key_mft.DEK)
#define IMAGE_IS_ENCRYPTED				BIT(31)
	u32 entry_point_l;
	u32 entry_point_h;
	u32 img_crc32;		// 0x14 CRC32 of image data
	u32 img_len;
	u32 img_off;
	u32 sign_off;		// 0x20 Offset to Signature of this hdr + image data
	u32 mft_off;		// 0x24 Offset to Key Manifest
	u32 custom_data_len;
	u32 custom_data_off;
	u8 reserved_0[464];
};

struct key_mft {
	u32 mft_magic;		// 0x0 Key Manifest Magic Number. ("MFT\0", 0x4d465400)
#define MFT_MAGIC_NUM		(0x0054464d)
	u32 version;		// 0x4 Version:
				//   [7:0] spec version = 0x02
#define GET_MFT_SPEC_VERSION(val)			(((val) >> 0) & 0xFF)
#define   SUPPORTED_MFT_SPEC_VERSION			(0x2)
	u32 sflags;		// 0x8 Sign Control Flags:
				//   [29:28] Device Public Key Type (0-ECDSA384, 1-SM2, 2-RSA4096)
				//   [25:24] Device Public Key Table ID (11b reserved)
				//   [21:20] Device Public Key Table Key Count - 1 (0 base)
				//   [17:16] Device Public Key ID
				//   [9:8] Image Public Key Type (0-ECDSA384, 1-SM2, 2-RSA4096)
				//   [6:0] Image Public Key ID
#define GET_DEVICE_PUBLIC_KEY_TYPE(val)			(((val) >> 28) & 0x3)
#define   DEVICE_PUBLIC_KEY_ECDSA384			(0x0)
#define   DEVICE_PUBLIC_KEY_SM2				(0x1)
#define   DEVICE_PUBLIC_KEY_RSA4096			(0x2)
#define GET_DEVICE_PUBLIC_KEY_TABLE_ID(val)		(((val) >> 24) & 0x3)
#define   MAX_DEVICE_PUBLIC_KEY_TABLE_NUM		(0x3)
#define GET_DEVICE_PUBLIC_KEY_TABLE_KEY_COUNT(val)	((((val) >> 20) & 0x3) + 1)
#define GET_DEVICE_PUBLIC_KEY_ID(val)			(((val) >> 16) & 0x3)
#define GET_IMAGE_PUBLIC_KEY_TYPE(val)			(((val) >> 8) & 0x3)
#define   IMAGE_PUBLIC_KEY_TYPE_ECDSA384		(0x0)
#define   IMAGE_PUBLIC_KEY_TYPE_SM2			(0x1)
#define   IMAGE_PUBLIC_KEY_TYPE_RSA4096			(0x2)
#define GET_IMAGE_PUBLIC_KEY_ID(val)			(((val) >> 0) & 0x7F)
	u32 eflags;		// 0xC Encryption Control Flags:
				//   [29:28] Encryption Type (0-AES-256-CBC, 1-SM4-CBC)
				//   [25:24] Encryption Key ID (FWkey, 10b 11b reserved)
#define GET_ENCRYPTION_TYPE(val)			(((val) >> 28) & 0x3)
#define   ENCRYPTION_TYPE_AES256			(0x0)
#define   ENCRYPTION_TYPE_SM4				(0x1)
#define GET_ENCRYPTION_KEY_ID(val)			(((val) >> 24) & 0x3)
#define   MAX_ENCRYPTION_KEY_NUM			(0x2)
	u32 img_ver_revoke_loc; // 0x10 OTP addr of Image version revocation
	u8 reserved_0[204];
	u8 iza[32];		// 0xE0 Za of Image Signer, for SM2 only
	u8 reserved_1[32];
	u8 dza[32];		// 0x120 Za of Device Signer, for SM2 only
	u8 reserved_2[32];
	u8 iv[16];
	u8 reserved_3[16];
	u8 ekek[32];		// 0x180 Encrypted Key Encryption Key (by FWkey, no padding)
	u8 reserved_4[32];
	u8 edek[32];		// 0x1C0 Encrypted Data Encryption Key (by KEK, no padding)
	u8 reserved_5[32];
	u8 eipk[512];		// 0x200 Encrypted Image Public Key (by DEK, no padding)
#define MAX_IMAGE_PUBLIC_KEY_SIZE			(0x200)
	u8 edpkt[2048];		// 0x400 Encrypted Device Public Key Table (by DEK, no padding)
#define DEVICE_PUBLIC_KEY_ENTRY_SIZE			(0x200)
};

struct capsule_comp_attrs {
	u32 off_cap;
	u32 off_storage;
	u32 size;
};

struct capsule_cap {
	u32 magic;
#define CAP_MAGIC_NUM	(0x00504143)
	u32 len;
	u8 desc[64];
	u32 storage_type;
	u32 image_sfc_cs;
	u32 count;
	u32 img_type_maps[CAPSULE_COMPONENT_MAX_COUNT / CAPSULE_COMPS_PER_REG];
};

struct capsule_rpt {
	u32 magic;
#define RPT_MAGIC_NUM	(0x00545052)
	u32 len;
	u32 enc_rev_bit_msk;
	u32 pkh_rev_bit_msk;
	u32 pkid_rev_bit_msk;
	u32 pkh_img_key_rev_bit_msk[4 * 3];
	u32 svn_rev_attrs[CAPSULE_COMPONENT_MAX_COUNT];
	u8 rsvd[148];
};

struct capsule_cmf {
	u32 magic;
#define CMF_MAGIC_NUM	(0x00464D43)
	u32 version;
	u32 cflag;
	u32 body_len;
};

struct capsule_info {
	struct bif_image_hdr hdr;
	struct key_mft mft;
	struct capsule_cmf cmf;
	struct capsule_cap cap;
	struct capsule_comp_attrs attrs[CAPSULE_COMPONENT_MAX_COUNT];
	struct capsule_rpt rpt;
	u8 cus_sig[512];	// custom data signature
	u8 cap_sig[512];	// capsule signature
	u8 mft_sig[512];

	u32 part_capsule_off;
};

u32 starfive_jhb100_parse_capsule(u32 *rofs_blk_size, u32 *rofs_size,
				  u32 *rofs_offs, u32 load_add);

#endif /* _SECURE_VAB_H_ */
