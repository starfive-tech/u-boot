// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */
#include <linux/types.h>

uint32_t itg_get_reg(uint32_t addr, uint32_t shift, uint32_t mask);
void itg_set_reg(uint32_t addr, uint32_t data, uint32_t shift, uint32_t mask);
void itg_assert_rst(uint32_t addr, uint32_t addr_status, uint32_t mask);
void itg_clear_rst(uint32_t addr, uint32_t addr_status, uint32_t mask);
