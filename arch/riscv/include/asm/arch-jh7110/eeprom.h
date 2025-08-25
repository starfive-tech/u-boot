/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2021 StarFive Technology Co., Ltd.
 *
 * Author: Jianlong Huang <jianlong.huang@starfivetech.com>
 */

#ifndef _ASM_RISCV_EEPROM_H
#define _ASM_RISCV_EEPROM_H

const char *get_product_id_from_eeprom(void);
int get_vf2_board_type(void);
unsigned long get_mmc_size_from_eeprom(void);
u8 get_pcb_revision_from_eeprom(void);
int get_data_from_eeprom(int offset, int len, unsigned char *data);

#endif /* _ASM_RISCV_EEPROM_H */
