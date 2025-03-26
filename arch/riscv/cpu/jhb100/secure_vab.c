// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

 #include <common.h>
 #include <mailbox.h>
 #include <dm/uclass.h>
 #include <dm/device.h>
 #include <dm/device-internal.h>
 #include <rpmi/rpmi-srvgrp-uclass.h>
 #include <asm/arch/rpmi-mpxy-sec.h>
 #include <u-boot/crc.h>
 #include <malloc.h>
 #include <asm/arch/secure_vab.h>

#define ADDR_HIGH_MASK	(GENMASK(63, 32))
#define ADDR_LOW_MASK	(GENMASK(31, 0))

u32 starfive_jhb100_vendor_authentication(void **p_image, size_t *p_size)
{
	int ret = 0;

	void *payld = *p_image;
	/**
	 * Send RPMI/MPXY message via mailbox to request secure
	 * core to validate image
	 */
	const struct request_spec *spec = get_request_spec_by_id(SECBOOT_VERIFY_BMCFW);

	if (!spec) {
		printf("Error: Invalid request_id\n");
		return -EINVAL;
	}

	u32 resp_data[spec->resp_count];

	memset(resp_data, 0, sizeof(u32) * spec->resp_count);

	u32 req_data[spec->param_count];

	req_data[0] = 0; /* flag */
	req_data[1] = (u64)payld & ADDR_LOW_MASK; /* addr_low */
	req_data[2] = ((u64)payld & ADDR_HIGH_MASK) >> BITS_PER_WORD; /* addr_high */
	req_data[3] = *p_size; /* size */

	ret = starfive_sec_rx_tx(spec, req_data, resp_data, NULL, 0, NULL, 0, false);
	if (ret) {
		return ret;
	}

	if (resp_data[0]) {
		printf("Image verification failed, error: %d\n", resp_data[0]);
		return resp_data[0];
	}

	struct bif_image_hdr *hdr = (struct bif_image_hdr *)*p_image;
	/* Point to image offset and image size */
	*p_image = (u8 *)hdr + hdr->img_off;
	/* Get image's actual length from secure service's response */
	*p_size = resp_data[1];

	return 0;
}
