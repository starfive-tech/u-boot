/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#ifndef _BOOTCMD_RESTORE_H
#define _BOOTCMD_RESTORE_H

void restore_deep_bootcmd(void);
void restore_bootcmd_utils(void);
void restore_bootcmd_sfc(void);
void restore_bootcmd_emmc(void);
void jhb100_env_check_version(void);

#endif /* _BOOTCMD_RESTORE_H */
