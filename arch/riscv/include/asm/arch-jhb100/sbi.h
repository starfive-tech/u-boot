// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 Starfive Technology International <www.starfivetech.com>
 *
 */

#ifndef _STARFIVE_SBI_H
#define _STARFIVE_SBI_H

/* Sync from OpenSBI */
enum sbi_ext_starfive_jhb100_fid {
	SBI_EXT_STARFIVE_JHB100_SET_SFC_ADDR_MODE,
	SBI_EXT_STARFIVE_JHB100_DOMAIN_RESET,
	SBI_EXT_STARFIVE_JHB100_FID_MAX,
};

int sbi_set_sfc_addr_mode(unsigned long sfc_num, unsigned long value);

#endif
