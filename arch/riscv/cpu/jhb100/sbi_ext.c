// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2024 Starfive Technology International <www.starfivetech.com>
 */

#include <asm/arch/sbi.h>
#include <asm/sbi.h>

int sbi_set_sfc_addr_mode(unsigned long sfc_num, unsigned long value)
{
	struct sbiret sbi_ret;

	sbi_ret = sbi_ecall(sbi_get_vendor_extid(),
			    SBI_EXT_STARFIVE_JHB100_SET_SFC_ADDR_MODE,
			    sfc_num, value, 0, 0, 0, 0);
	if (sbi_ret.error)
		return sbi_ret.error;

	return 0;
}
