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
	u32 mft_off;            // 0x24 Offset to Key Manifest
	u8 reserved_0[472];
};
#endif /* _SECURE_VAB_H_ */
