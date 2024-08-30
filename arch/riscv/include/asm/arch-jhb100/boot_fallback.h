/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_FALLBACK_H
#define _BOOT_FALLBACK_H

void starfive_board_boot_order(u32 *spl_boot_list);
void starfive_fallback_handler(void);

#endif /* _BOOT_FALLBACK_H */
