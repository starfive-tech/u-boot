
// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2022 Starfive, Inc.
 * Author:	yanhong <yanhong.wang@starfivetech.com>
 *
 */

#include "starfive_ddr.h"

#define G_SPEED_2133	1

#define OFFSET_SEL	0x80000000

static struct ddr_reg_clrset ddr_start_data[] = {
	{(OFFSET_SEL | 89),  	0xffffff00,  	0x00000051},
	{(OFFSET_SEL | 78),  	0xfffffcff,  	0x0},
	{(OFFSET_SEL | 345),  	0xffffff00,  	0x00000051},
	{(OFFSET_SEL | 334), 	0xfffffcff, 	0x0},
	{(OFFSET_SEL | 601), 	0xffffff00, 	0x00000051},
	{(OFFSET_SEL | 590), 	0xfffffcff, 	0x0},
	{(OFFSET_SEL | 857), 	0xffffff00, 	0x00000051},
	{(OFFSET_SEL | 846), 	0xfffffcff, 	0x0},
	{(OFFSET_SEL | 1793), 	0xfffffeff, 	0x0},
	{(OFFSET_SEL | 1793), 	0xfffcffff, 	0x0},
	{(OFFSET_SEL | 125), 	0xfff0ffff, 	0x00010000},
	{(OFFSET_SEL | 102), 	0xfffffffc, 	0x00000001},
	{(OFFSET_SEL | 105), 	0xffffffe0, 	0x00000001},
	{(OFFSET_SEL | 92), 	0xfffffffe, 	0x00000001},
	{(OFFSET_SEL | 94), 	0xffffe0ff, 	0x00000200},
	{(OFFSET_SEL | 96), 	0xfffff0ff, 	0x00000400},
	{(OFFSET_SEL | 89), 	0xffffff00, 	0x00000051},
	{(OFFSET_SEL | 381), 	0xfff0ffff, 	0x00010000},
	{(OFFSET_SEL | 358), 	0xfffffffc, 	0x00000001},
	{(OFFSET_SEL | 361), 	0xffffffe0, 	0x00000001},
	{(OFFSET_SEL | 348), 	0xfffffffe, 	0x00000001},
	{(OFFSET_SEL | 350), 	0xffffe0ff, 	0x00000200},
	{(OFFSET_SEL | 352),  	0xfffff0ff,	0x00000400},
	{(OFFSET_SEL | 345), 	0xffffff00,	0x00000051},
	{(OFFSET_SEL | 637), 	0xfff0ffff,	0x00010000},
	{(OFFSET_SEL | 614), 	0xfffffffc,	0x00000001},
	{(OFFSET_SEL | 617), 	0xffffffe0,	0x00000001},
	{(OFFSET_SEL | 604), 	0xfffffffe,	0x00000001},
	{(OFFSET_SEL | 606), 	0xffffe0ff,	0x00000200},
	{(OFFSET_SEL | 608), 	0xfffff0ff,	0x00000400},
	{(OFFSET_SEL | 601), 	0xffffff00,	0x00000051},
	{(OFFSET_SEL | 893), 	0xfff0ffff,	0x00010000},
	{(OFFSET_SEL | 870), 	0xfffffffc,	0x00000001},
	{(OFFSET_SEL | 873), 	0xffffffe0,	0x00000001},
	{(OFFSET_SEL | 860), 	0xfffffffe,	0x00000001},
	{(OFFSET_SEL | 862), 	0xffffe0ff,	0x00000200},
	{(OFFSET_SEL | 864), 	0xfffff0ff,	0x00000400},
	{(OFFSET_SEL | 857), 	0xffffff00,	0x00000051},
	{(OFFSET_SEL | 1895), 	0xffffe000,	0x00001342},
	{(OFFSET_SEL | 1835), 	0xfffff0ff,	0x00000200},
	{(OFFSET_SEL | 1793), 	0xfffffeff,	0x00000100},
	{62, 	0xfffffeff,	0x0},
	{66, 	0xfffffeff,	0x0},
	{166, 	0xffffff80,	0x00000001},
	{62, 	0xfff0ffff,	0x00010000},
	{62, 	0xf0ffffff,	0x01000000},
	{166, 	0xffff80ff,	0x00000100},
	{179, 	0xff80ffff,	0x00010000},
	{67, 	0xffe0ffff,	0x00010000},
	{67, 	0xe0ffffff,	0x01000000},
	{179, 	0x80ffffff,	0x01000000},
	{166, 	0xff80ffff,	0x00010000},
	{62, 	0xfff0ffff,	0x00010000},
	{62, 	0xf0ffffff,	0x01000000},
	{166, 	0x80ffffff,	0x01000000},
	{182, 	0xff80ffff,	0x00010000},
	{67, 	0xffe0ffff,	0x00010000},
	{67,	0xe0ffffff,	0x01000000},
	{182, 	0x80ffffff,	0x01000000},
	{167, 	0xffffff80,	0x00000017},
	{62, 	0xfff0ffff,	0x00010000},
	{62, 	0xf0ffffff,	0x01000000},
	{167, 	0xffff80ff,	0x00001700},
	{185, 	0xff80ffff,	0x00200000},
	{67, 	0xffe0ffff,	0x00010000},
	{67, 	0xe0ffffff,	0x01000000},
	{185, 	0x80ffffff,	0x20000000},
	{10, 	0xffffffe0,	0x00000002},
	{0, 	0xfffffffe,	0x00000001},
#ifdef G_DDR_SIMULATION
	{(OFFSET_SEL | 1860),	0x80ffffff,	0x01000000},
#endif
	{247,	0xffffffff,	0x00000008},
	{249,	0xffffffff,	0x00000800},
	{252,	0xffffffff,	0x00000008},
	{254,	0xffffffff,	0x00000800},
	{281,	0xffffffff,	0x33000000},
	{305,	0xffffffff,	0x33000000},
	{329,	0xffffffff,	0x33000000},
	{353,	0xffffffff,	0x33000000},
	{289,	0xffffffff,	0x66000000},
	{313,	0xffffffff,	0x66000000},
	{337,	0xffffffff,	0x66000000},
	{361,	0xffffffff,	0x66000000},
	{282,	0xffffffff,	0x00160000},
	{306,	0xffffffff,	0x00160000},
	{330,	0xffffffff,	0x00160000},
	{354,	0xffffffff,	0x00160000},
	{290,	0xffffffff,	0x00160000},
	{314,	0xffffffff,	0x00160000},
	{338,	0xffffffff,	0x00160000},
	{362,	0xffffffff,	0x00160000},
	{282,	0xffffff00,	0x17},
	{306,	0xffffff00,	0x17},
	{330,	0xffffff00,	0x17},
	{354,	0xffffff00,	0x17},
	{290,	0xffffff00,	0x17},
	{314,	0xffffff00,	0x17},
	{338,	0xffffff00,	0x17},
	{362,	0xffffff00,	0x17},
	{282,	0xffff00ff,	0x2000},
	{306,	0xffff00ff,	0x2000},
	{330,	0xffff00ff,	0x2000},
	{354,	0xffff00ff,	0x2000},
	{290,	0xffff00ff,	0x2000},
	{314,	0xffff00ff,	0x2000},
	{338,	0xffff00ff,	0x2000},
	{362,	0xffff00ff,	0x2000},
	{(OFFSET_SEL | 65), 	0xffffffff,	0x00000100},
	{(OFFSET_SEL | 321),	0xffffffff,	0x00000100},
	{(OFFSET_SEL | 577),	0xffffffff,	0x00000100},
	{(OFFSET_SEL | 833),	0xffffffff,	0x00000100},
};

static struct ddr_reg_clrset ddr_start_data1[] = {
#ifdef G_SPEED_3200
	{96, 	0xff00ffff,	0x00180000},
	{352,	0xff00ffff,	0x00180000},
	{608,	0xff00ffff,	0x00180000},
	{864,	0xff00ffff,	0x00180000},
#elif defined G_SPEED_2666
	{96, 	0xff00ffff,	0x00140000},
	{352,	0xff00ffff,	0x00140000},
	{608,	0xff00ffff,	0x00140000},
	{864,	0xff00ffff,	0x00140000},
#elif defined G_SPEED_2133
	{96, 	0xff00ffff,	0x00120000},
	{352,	0xff00ffff,	0x00120000},
	{608,	0xff00ffff,	0x00120000},
	{864,	0xff00ffff,	0x00120000},
#endif
	{33,  	0xffffff00,	0x0040},
	{289, 	0xffffff00,	0x0040},
	{545, 	0xffffff00,	0x0040},
	{801, 	0xffffff00,	0x0040},
	{1038,	0xfcffffff,	0x03000000},
	{1294,	0xfcffffff,	0x03000000},
	{1550,	0xfcffffff,	0x03000000},
	{83,  	0xffc0ffff,	0x70000},
	{339, 	0xffc0ffff,	0x70000},
	{595, 	0xffc0ffff,	0x70000},
	{851, 	0xffc0ffff,	0x70000},
	{1062,	0xf800ffff,	0x70000},
	{1318,	0xf800ffff,	0x70000},
	{1574,	0xf800ffff,	0x70000},
	{1892,	0xfffc0000,	0x15547},
	{1893,	0xfffc0000,	0x7},
	{1852,	0xffffe000,	0x07a},
	{1853,	0xffffffff,	0x0100},
	{1822,	0xffffffff,	0xFF},
	{1896,	0xfffffc00,	0x03d5},
	{91,  	0xfc00ffff,	0x03d50000},
	{347, 	0xfc00ffff,	0x03d50000},
	{603, 	0xfc00ffff,	0x03d50000},
	{859, 	0xfc00ffff,	0x03d50000},
};

static struct ddr_reg_set ddr_start_data2[] = {

	{1912,	0xcc3bfc7},
	{1913,	0xff8f},
	{1914,	0x33f07ff},
	{1915,	0xc3c37ff},
	{1916,	0x1fffff10},
	{1917,	0x230070},
	{1918,	0x3ff7ffff},
	{1919,	0xe10},
	{1920,	0x1fffffff},
	{1921,	0x188411},
	{1922,	0x1fffffff},
	{1923,	0x180400},
	{1924,	0x1fffffff},
	{1925,	0x180400},
	{1926,	0x1fffffcf},
	{1927,	0x188400},
	{1928,	0x1fffffff},
	{1929,	0x4188411},
	{1837,	0x24410},
	{1840,	0x24410},
	{1842,	0x2ffff},
};

static struct ddr_reg_clrset ddr_start_data3[] = {
	{76,	0xff0000f8,	0x00ff8f07},
	{332,	0xff0000f8,	0x00ff8f07},
	{588,	0xff0000f8,	0x00ff8f07},
	{844,	0xff0000f8,	0x00ff8f07},
	{77,	0xffff0000,	0xff8f},
	{333,	0xffff0000,	0xff8f},
	{589,	0xffff0000,	0xff8f},
	{845,	0xffff0000,	0xff8f},
	{1062,	0xffffff00,	0xff},
	{1318,	0xffffff00,	0xff},
	{1574,	0xffffff00,	0xff},
	{1028,	0xffffffff,	0x1000000},
	{1284,	0xffffffff,	0x1000000},
	{1540,	0xffffffff,	0x1000000},
};

static struct ddr_reg_clrset ddr_start_data4[] = {
	{130,	0x0000ffff,	0xffff0000},
	{386,	0x0000ffff,	0xffff0000},
	{642,	0x0000ffff,	0xffff0000},
	{898,	0x0000ffff,	0xffff0000},
	{131,	0xfffffff0,	0xf},
	{387,	0xfffffff0,	0xf},
	{643,	0xfffffff0,	0xf},
	{899,	0xfffffff0,	0xf},
	{29,	0xc0ffffff,	0x10000000},
	{285,	0xc0ffffff,	0x10000000},
	{541,	0xc0ffffff,	0x10000000},
	{797,	0xc0ffffff,	0x10000000},
	{30,	0xffffffff,	0x00080000},
	{286,	0xffffffff,	0x00080000},
	{542,	0xffffffff,	0x00080000},
	{798,	0xffffffff,	0x00080000},
	{31,	0xffffffc0,	0x00000010},
	{287,	0xffffffc0,	0x00000010},
	{543,	0xffffffc0,	0x00000010},
	{799,	0xffffffc0,	0x00000010},
	{1071,	0xfffffff0,	0x00000008},
	{1327,	0xfffffff0,	0x00000008},
	{1583,	0xfffffff0,	0x00000008},
	{1808,	0xfffffff0,	0x00000008},
	{1896,	0xfff0ffff,	0x00080000},
};

void ddr_phy_start(u32 *phyreg)
{
	u32 i, len;
	u32 *addr, *reg;
	u32 offset;

	reg = phyreg + 4096;

	len = sizeof(ddr_start_data)/sizeof(struct ddr_reg_clrset);
	for (i = 0; i < len; i++) {
		if (ddr_start_data[i].offset & OFFSET_SEL) {
			offset = ddr_start_data[i].offset & (~OFFSET_SEL);
			addr = reg;
		} else {
			offset = ddr_start_data[i].offset;
			addr = phyreg + 2048;
		}
		DDR_REG_TRIGGER((addr + offset), ddr_start_data[i].mask,
			ddr_start_data[i].val);
	}

	out_le32(reg + 96, in_le32(reg + 96) + 0x300);
	out_le32(reg + 352, in_le32(reg + 352) + 0x300);
	out_le32(reg + 608, in_le32(reg + 608) + 0x300);
	out_le32(reg + 864, in_le32(reg + 864) + 0x300);

	len = sizeof(ddr_start_data1)/sizeof(struct ddr_reg_clrset);
	for (i = 0; i < len; i++)
		DDR_REG_TRIGGER((reg + ddr_start_data1[i].offset),
			ddr_start_data1[i].mask,
			ddr_start_data1[i].val);

	len = sizeof(ddr_start_data2)/sizeof(struct ddr_reg_set);
	for (i = 0; i < len; i++)
		out_le32((reg + ddr_start_data2[i].offset),
			ddr_start_data2[i].val);

	len = sizeof(ddr_start_data3)/sizeof(struct ddr_reg_clrset);
	for (i = 0; i < len; i++)
		DDR_REG_TRIGGER((reg + ddr_start_data3[i].offset),
			ddr_start_data3[i].mask,
			ddr_start_data3[i].val);

	out_le32((reg + 1848), 0x3cf07f8);
	out_le32((reg + 1849), 0x3f);
	out_le32((reg + 1850), 0x1fffff);
	out_le32((reg + 1851), 0x060000);

	len = sizeof(ddr_start_data4)/sizeof(struct ddr_reg_clrset);
	for (i = 0; i < len; i++)
		DDR_REG_TRIGGER((reg + ddr_start_data4[i].offset),
			ddr_start_data4[i].mask,
			ddr_start_data4[i].val);

	out_le32(phyreg, 0x01);
}

