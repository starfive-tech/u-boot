// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2024 StarFive Technology Co., Ltd.
 */

#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_src.h>
#include <linux/bitops.h>
#include <dm.h>
#include <log.h>
#include <spl.h>

/* Storing register mapping in data segment for now */
static FB_REC_MAP_BIT_POS primary_bit_pos;
static FB_REC_MAP_BIT_POS secondary_bit_pos;
static int fb_rec_map;

/* Get partition type where caller boots from */
FB_REC_MAP_BIT_POS starfive_get_part(FB_REC_MAP_TYPE p_type)
{
	return (p_type == PRIMARY) ? primary_bit_pos : secondary_bit_pos;
}

/* Retrieve register mapping */
int starfive_get_fb_rec_map(void)
{
	return fb_rec_map;
}

/* Write to register mapping */
void starfive_set_fb_rec_map(int val)
{
	fb_rec_map = val;
}

/* Custom safe simplified set bit */
void starfive_set_bit(int *reg_map, int bit_pos)
{
	int val = *reg_map;

	val |= bit_pos;
	*reg_map = val;
}

/* Custom safe simplified clear bit */
void starfive_clear_bit(int *reg_map, int bit_pos)
{
	int val = *reg_map;

	val &= ~bit_pos;
	*reg_map = val;
}

/* Call this with SET and CLEAR after authentication and before jumping */
/* If authentication failed, SET immediately before next authentication */
/* In early phase when called by board_boot_order(), if index is more than 0,
 * need to SET bit accordingly.
 * For example, if index is 1, primary partition of the mapping must be set.
 */
int starfive_fb_rec_map_handler(int *reg_map, FB_REC_MAP_BIT_POS first_part_bit,
		FB_REC_MAP_BIT_POS last_part_bit, FB_REC_MAP_STATE reg_map_msk, FB_REC_MAP action)
{
	/* Handle misuse of function */
	if (first_part_bit > last_part_bit)
		return 0;

	int first_bit_pos = (reg_map_msk << first_part_bit);
	int last_bit_pos = (reg_map_msk << last_part_bit);

	/* Clear if set */
	if (action == CLEAR) {
		int bit_pos = last_bit_pos;

		while (bit_pos >= first_bit_pos) {
			if (bit_pos & *reg_map) {
				starfive_clear_bit(reg_map, bit_pos);
				return bit_pos;
			}
			bit_pos >>= 1;
		}
	} else {
		int bit_pos = first_bit_pos;

		while (bit_pos <= last_bit_pos)	{
			if (!(bit_pos & *reg_map)) {
				/* Set if unset, check if unset */
				if (action == SET) {
					primary_bit_pos = first_part_bit;
					secondary_bit_pos = last_part_bit;
					starfive_set_bit(reg_map, bit_pos);
				}
				return bit_pos;
			}
			bit_pos <<= 1;
		}
	}
	return 0;
}
