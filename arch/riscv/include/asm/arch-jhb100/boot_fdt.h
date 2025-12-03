/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_FDT_H
#define _BOOT_FDT_H

int jhb100_fdt_fixup(void *blob);
int jhb100_scp_buffer_parser(void *blob);
int jhb100_set_mmbi_iopmp_memrange(void *blob);

#endif /* _BOOT_FDT_H */
