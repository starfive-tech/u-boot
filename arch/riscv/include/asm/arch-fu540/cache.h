/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2020 SiFive, Inc.
 *
 * Authors:
 *   Pragnesh Patel <pragnesh.patel@sifve.com>
 */

#ifndef _CACHE_SIFIVE_H
#define _CACHE_SIFIVE_H

int cache_enable_ways(void);
u32 cache_enable_ways_debug(u32 ways_input);

#endif /* _CACHE_SIFIVE_H */
