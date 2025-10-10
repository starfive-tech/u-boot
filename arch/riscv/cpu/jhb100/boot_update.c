// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: WeiSheng Ch'ng <weisheng.chng@starfivetech.com>
 */

#include <common.h>
#include <mailbox.h>
#include <dm/uclass.h>
#include <dm/device.h>
#include <dm/device-internal.h>
#include <u-boot/crc.h>
#include <malloc.h>
#include <asm/arch/secure_vab.h>
#include <hang.h>
#include <misc.h>
#include <asm/io.h>
#include <asm/sbi.h>
#include <asm/arch/ap_core.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/boot_fallback.h>
#include <rand.h>

#define CAP_PARSE_SUCCESS	0
#define CAP_PARSE_ERROR		1

/* Max size of capsule should be no more than allocated GPP size of 400 MB */
#define UPD_CAP_MAX_SIZE	0x19000000

u32 starfive_jhb100_parse_capsule(u32 *rofs_blk_size, u32 *rofs_size,
				  u32 *rofs_offs, u32 load_addr)
{
	/* Only simple check performed by AP */
	printf("Parsing update capsule loaded to address 0x%x\n", load_addr);
	struct bif_image_hdr *hdr = (struct bif_image_hdr *)(uintptr_t)load_addr;

	/* Check Magic */
	if (hdr->bif_magic != BIF_MAGIC_NUM) {
		printf("[ERROR]: hdr->bif_magic = %x\n", hdr->bif_magic);
		return CAP_PARSE_ERROR;
	}

	/* Check Image size properties */
	if ((!hdr->img_len) || (!hdr->img_off)) {
		printf("[ERROR]: hdr->img_len = %x\n", hdr->img_len);
		printf("[ERROR]: hdr->img_off = %x\n", hdr->img_off);
		return CAP_PARSE_ERROR;
	}

	if ((hdr->img_off + hdr->img_len) > UPD_CAP_MAX_SIZE) {
		printf("[ERROR]: hdr->img_off + hdr->img_len = %x\n",
		       hdr->img_off + hdr->img_len);
		return CAP_PARSE_ERROR;
	}

	/* Check sig and mft properties */
	if ((!hdr->sign_off) || (!hdr->mft_off)) {
		printf("[ERROR]: hdr->sign_off = %x\n", hdr->sign_off);
		printf("[ERROR]: hdr->mft_off = %x\n", hdr->mft_off);
		return CAP_PARSE_ERROR;
	}

	/* Check custom data properties */
	if ((hdr->custom_data_off + hdr->custom_data_len) > UPD_CAP_MAX_SIZE) {
		printf("[ERROR]: hdr->custom_data_off + hdr->custom_data_len = %x\n",
		       hdr->custom_data_off + hdr->custom_data_len);
		return CAP_PARSE_ERROR;
	}

	struct capsule_cmf *cmf = (struct capsule_cmf *)((u8 *)hdr + hdr->custom_data_off);

	/* Check Magic */
	if (cmf->magic != CMF_MAGIC_NUM) {
		printf("[ERROR]: cmf->magic = %x\n", cmf->magic);
		return CAP_PARSE_ERROR;
	}

	struct capsule_cap *cap = (struct capsule_cap *)((u8 *)cmf + sizeof(struct capsule_cmf));

	/* Check Magic */
	if (cap->magic != CAP_MAGIC_NUM) {
		printf("[ERROR]: cap->magic = %x\n", cap->magic);
		return CAP_PARSE_ERROR;
	}

	if ((cap->storage_type != CAP_STORAGE_TYPE_EMMC) &&
	    (cap->storage_type != CAP_STORAGE_TYPE_UFS) &&
	    (cap->storage_type != CAP_STORAGE_TYPE_SFC)) {
		printf("[ERROR]: cap->storage_type = %x\n", cap->storage_type);
		return CAP_PARSE_ERROR;
	}

	if (cap->count > CAPSULE_COMPONENT_MAX_COUNT) {
		printf("[ERROR]: cap->count = %x\n", cap->count);
		return CAP_PARSE_ERROR;
	}

	int comp_idx;

	for (comp_idx = 0; comp_idx < cap->count; comp_idx++) {
		int idx = comp_idx / CAPSULE_COMPS_PER_REG;
		int offs = (comp_idx % CAPSULE_COMPS_PER_REG) * 8;

		if (BIF_IMG_TYPE_ROFS == ((cap->img_type_maps[idx] >> offs) & 0xff)) {
			goto extract_capsule;
		}
	}

	printf("[ERROR]: Unknown Image Type\n");
	return CAP_PARSE_ERROR;

extract_capsule:
	struct capsule_comp_attrs *comp_attr = (struct capsule_comp_attrs *)
					       ((u8 *)cap + sizeof(struct capsule_cap));

	comp_attr += comp_idx;
	struct bif_image_hdr *rofs_hdr = (struct bif_image_hdr *)((u8 *)cmf +
					 (comp_attr->off_cap));

	/* Check Magic */
	if (rofs_hdr->bif_magic != BIF_MAGIC_NUM) {
		printf("[ERROR]: rofs_hdr->bif_magic = %x\n", rofs_hdr->bif_magic);
		return CAP_PARSE_ERROR;
	}

	/* Check Image size properties */
	if ((!rofs_hdr->img_len) || (!rofs_hdr->img_off)) {
		printf("[ERROR]: rofs_hdr->img_len = %x\n", rofs_hdr->img_len);
		printf("[ERROR]: rofs_hdr->img_off = %x\n", rofs_hdr->img_off);
		return CAP_PARSE_ERROR;
	}

	if ((rofs_hdr->img_off + rofs_hdr->img_len) > UPD_CAP_MAX_SIZE) {
		printf("[ERROR]: rofs_hdr->img_off + rofs_hdr->img_len = %x\n",
		       rofs_hdr->img_off + rofs_hdr->img_len);
		return CAP_PARSE_ERROR;
	}

#ifdef CONFIG_STARFIVE_JHB100_SECURE_VAB_AUTH
	/* Check sig and mft properties */
	if ((!rofs_hdr->sign_off) || (!rofs_hdr->mft_off)) {
		printf("[ERROR]: rofs_hdr->sign_off = %x\n", rofs_hdr->sign_off);
		printf("[ERROR]: rofs_hdr->mft_off = %x\n", rofs_hdr->mft_off);
		return CAP_PARSE_ERROR;
	}
#endif

	*rofs_blk_size = (rofs_hdr->img_len % MMC_BLK_SIZE) ?
			 ((rofs_hdr->img_len / MMC_BLK_SIZE) + 1) :
			 (rofs_hdr->img_len / MMC_BLK_SIZE);

	*rofs_size = (rofs_hdr->img_len + SFC_PAGE_SIZE - 1) & ~(SFC_PAGE_SIZE - 1);
	*rofs_offs = hdr->custom_data_off + comp_attr->off_cap + load_addr + BIF_HDR_LENGTH;
#ifdef CONFIG_STARFIVE_JHB100_SECURE_VAB_AUTH
	*rofs_offs = *rofs_offs + BIF_MFT_LENGTH + BIF_SIG_LENGTH;
#endif

	printf("[SUCCESS]: rofs_blk_size = 0x%x\n", *rofs_blk_size);
	printf("[SUCCESS]: rofs_size = 0x%x\n", *rofs_size);
	printf("[SUCCESS]: rofs_offs in memory is 0x%x\n", *rofs_offs);

	return CAP_PARSE_SUCCESS;
}
