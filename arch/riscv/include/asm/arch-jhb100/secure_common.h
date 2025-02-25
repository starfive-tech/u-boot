// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2025 Starfive Technology International <www.starfivetech.com>
 *
 * Author: Genevieve Chan <genevieve.chan@starfivetech.com>
 */
#ifndef _SECURE_COMMOH_H_
#define _SECURE_COMMON_H_

/**
 * Invoke a secure API on device that can be used to perform verification on a
 * secure blob by authenticaing and optionally decrypting it. The operation
 * depends on how the header file was first embedded into the blob during the
 * signing/encryption step when the secure blob was first created
 */
u32 starfive_jhb100_vendor_authentication(void **p_image, size_t *p_size);

/**
 * Invoke an API to point to the blob actual address and size post authentication
 */
void starfive_adjust_image(void **p_image, size_t *p_size);

#endif /* _SECURE_COMMON_H */
