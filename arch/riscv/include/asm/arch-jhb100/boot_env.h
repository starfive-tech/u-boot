/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */
#ifndef _BOOT_ENV_H
#define _BOOT_ENV_H

void env_filter_add_bootarg(void (*str_fn)(char *ostr, char *istr),
			    char *key_str, char *val_str);

#endif /* _BOOT_ENV_H */
