// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */

#include <dm/uclass.h>
#include <dm/device.h>
#include <hang.h>
#include <misc.h>
#include <asm/io.h>
#include <asm/sbi.h>
#include <asm/arch/ap_core.h>
#include <asm/arch/secure_vab.h>
#include <asm/arch/mpxy-sec.h>
#include <linux/bitops.h>
#include <dm/device-internal.h>
#include <rpmi/rpmi-srvgrp-uclass.h>
#include <common.h>
#include <mailbox.h>

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
	struct secboot_verify_bmcfw secboot;

	secboot.req.fw_address_high = ((u64)payld & ADDR_HIGH_MASK) >> BITS_PER_WORD;
	secboot.req.fw_address_low = (u64)payld & ADDR_LOW_MASK;
	secboot.req.size = *p_size;

#ifndef CONFIG_SPL_BUILD
	/** Sends MPXY message */
	struct udevice *mpxy_sec_dev;

	ret = uclass_get_device_by_driver(UCLASS_MISC, DM_DRIVER_GET(jhb100_sbi_mpxy_sec),
					  &mpxy_sec_dev);
	if (ret) {
		printf("Failed to probe StarFive JHB100 Sec MPXY driver\n");
		return ret;
	}

	ret = misc_ioctl(mpxy_sec_dev, SECBOOT_VERIFY_BMCFW, &secboot);
#else
	/** Create SHMEM */
	struct udevice *rpmi_mbox_shmem_dev;

	ret = uclass_get_device_by_driver(UCLASS_MAILBOX, DM_DRIVER_GET(rpmi_mbox_shmem),
					  &rpmi_mbox_shmem_dev);
	if (ret) {
		printf("Failed to probe RPMI shmem driver\n");
		return ret;
	}

	struct udevice *rpmi_sec_dev;
	/** Sends RPMI message */
	ret = uclass_get_device_by_driver(UCLASS_RPMI_SRV_GRP,
					  DM_DRIVER_GET(rpmi_srv_grp_starfive_bmc_sec_rt),
					  &rpmi_sec_dev);
	if (ret) {
		printf("Failed to probe StarFive JHB100 Sec RPMI Driver\n");
		return ret;
	}

	ret = rpmi_process_msg(rpmi_sec_dev, SECBOOT_VERIFY_BMCFW, &secboot);
#endif
	if (ret) {
		printf("Image verification failed\n");
		return ret;
	}

	struct bif_image_hdr *hdr = (struct bif_image_hdr *)*p_image;
	/* Point to image offset and image size */
	*p_image = (u8 *)hdr + hdr->img_off;
	*p_size = secboot.resp.img_len;

	return 0;
}
