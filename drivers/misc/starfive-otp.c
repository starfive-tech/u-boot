/*
 *   Copyright 2021 StarFive, Inc
 *
 *   This program is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU General Public License
 *   as published by the Free Software Foundation, version 2.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 */

#include <common.h>
#include <dm/device.h>
#include <dm/read.h>
#include <linux/bitops.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <misc.h>

#include <asm/arch/global_reg.h>
#include <asm/arch/io.h>

#define BYTES_PER_FUSE		4

// otp reg offset
#define OTP_CFGR		0x00
#define OTPC_IER		0x04
#define OTPC_SRR		0x08
#define OTP_OPRR		0x0c
#define OTPC_CTLR		0x10
#define OTPC_ADDRR		0x14
#define OTPC_DINR		0x18
#define OTPC_DOUTR		0x1c

#define OTP_MEM_START		0x800
#define OTP_MEM_SIZE		0x800
#define OTP_EMPTY_CELL_VALUE	(0xffffffffUL)

// cfgr (offset 0x00)
#define OTP_CFGR_PRG_CNT_MASK	0xff
#define OTP_CFGR_PRG_CNT_SHIFT	0
#define OTP_CFGR_DIV_1US_MASK	0xff
#define OTP_CFGR_DIV_1US_SHIFT	8
#define OTP_CFGR_RD_CYC_MASK	0x0f
#define OTP_CFGR_RD_CYC_SHIFT	16

// ier (offset 0x04)
#define OTPC_IER_DONE_IE	BIT(0)
#define OTPC_IER_BUSY_OPR_IE	BIT(1)

// srr (offset 0x08)
#define OTPC_SRR_DONE		BIT(0)
#define OTPC_SRR_BUSY_OPR	BIT(1)
#define OTPC_SRR_INFO_RD_LOCK	BIT(29)
#define OTPC_SRR_INFO_WR_LOCK	BIT(30)
#define OTPC_SRR_BUSY		BIT(31)

// oprr (offset 0x0c)
#define OTP_OPRR_OPR_MASK	0x00000007
#define OTP_OPRR_OPR_SHIFT	0

#define OTP_OPR_STANDBY			0x0 // user mode
#define OTP_OPR_READ			0x1 // user mode
#define OTP_OPR_MARGIN_READ_PROG	0x2 // testing mode
#define OTP_OPR_MARGIN_READ_INIT	0x3 // testing mode
#define OTP_OPR_PROGRAM			0x4 // user mode
#define OTP_OPR_DEEP_STANDBY		0x5 // user mode
#define OTP_OPR_DEBUG			0x6 // user mode

// ctlr (offset 0x10, see EG512X32TH028CW01_v1.0.pdf "Pin Description")
#define OTPC_CTLR_PCE		BIT(0)
#define OTPC_CTLR_PTM_MASK	0x0000000e
#define OTPC_CTLR_PTM_SHIFT	1
#define OTPC_CTLR_PDSTB		BIT(4)
#define OTPC_CTLR_PTR		BIT(5)
#define OTPC_CTLR_PPROG		BIT(6)
#define OTPC_CTLR_PWE		BIT(7)
#define OTPC_CTLR_PCLK		BIT(8)

// addrr (offset 0x14)
#define OTPC_ADDRR_PA_MASK	0x000001ff
#define OTPC_ADDRR_PA_SHIFT	0

#define STARFIVE_OTP_GPIO	56	/*control power*/

struct starfive_otp_regs {
/* TODO: add otp ememory_eg512x32 registers define */
	uint32_t otp_cfg;	/* 0x00: timing Register.*/
	uint32_t otpc_ie;	/* 0x04: interrupt Enable Register.*/
	uint32_t otpc_sr;	/* 0x08: status Register.*/
	uint32_t otp_opr;	/* 0x0C: operation mode select Register.*/
	uint32_t otpc_ctl;	/* 0x10: otp control port*/
	uint32_t otpc_addr;	/* 0x14: otp pa port.*/
	uint32_t otpc_din;	/* 0x18: otp pdin port.*/
	uint32_t otpc_dout;	/* 0x1C: otp pdout.*/
};

struct starfive_otp_platdata {
	struct starfive_otp_regs __iomem *regs;
	u32 total_fuses;
};

static void gpio_direction_output(u32 gpio, u32 val)
{
	volatile uint32_t __iomem *addr = EZGPIO_FULLMUX_BASE_ADDR + 0x50 +
					  gpio * 8;

	MA_OUTW(addr, val);
	MA_OUTW(addr + 1, val);
}

static void gpio_set_value(u32 gpio, u32 val)
{
	volatile uint32_t __iomem *addr = EZGPIO_FULLMUX_BASE_ADDR + 0x50 +
					  gpio * 8;

	MA_OUTW(addr, val);
}

/*
 * offset and size are assumed aligned to the size of the fuses (32-bit).
 */
static int starfive_otp_read(struct udevice *dev, int offset,
			     void *buf, int size)
{
	struct starfive_otp_platdata *plat = dev_get_plat(dev);
	struct starfive_otp_regs *regs = (struct starfive_otp_regs *)plat->regs;
	int fuseidx = offset / BYTES_PER_FUSE;
	int fusecount = size / BYTES_PER_FUSE;
	u32 fusebuf[fusecount];
	u32 addr = (u32)regs;

	/* Check if offset and size are multiple of BYTES_PER_FUSE */
	if ((size % BYTES_PER_FUSE) || (offset % BYTES_PER_FUSE)) {
		printf("%s: size and offset must be multiple of 4.\n",
		       __func__);
		return -EINVAL;
	}

	/* check bounds */
	if (offset < 0 || size < 0)
		return -EINVAL;
	if (fuseidx >= plat->total_fuses)
		return -EINVAL;
	if ((fuseidx + fusecount) > plat->total_fuses)
		return -EINVAL;

	//otp power off and on
	gpio_direction_output(STARFIVE_OTP_GPIO, 0);
	mdelay(5);
	gpio_set_value(STARFIVE_OTP_GPIO, 1);
	mdelay(10);

	//otp set to read mode
	writel(OTP_OPR_READ, &regs->otp_opr);
	mdelay(5);

	/* read all requested fuses */
	for (unsigned int i = 0; i < fusecount; i++, fuseidx++) {
		/* read the value */
		fusebuf[i] = readl((volatile void __iomem *)
				   (addr + OTP_MEM_START +
				   fuseidx * BYTES_PER_FUSE));
	}

	//otp power off
	gpio_set_value(STARFIVE_OTP_GPIO, 0);
	mdelay(5);

	/* copy out */
	memcpy(buf, fusebuf, size);

	return size;
}

static int starfive_otp_ofdata_to_platdata(struct udevice *dev)
{
	struct starfive_otp_platdata *plat = dev_get_plat(dev);
	int ret;

	plat->regs = dev_read_addr_ptr(dev);

	ret = dev_read_u32(dev, "fuse-count", &plat->total_fuses);
	if (ret < 0) {
		pr_err("\"fuse-count\" not found\n");
		return ret;
	}
	return 0;
}

static const struct misc_ops starfive_otp_ops = {
	.read = starfive_otp_read,
};

static const struct udevice_id sifive_otp_ids[] = {
	{ .compatible = "starfive,fu740-otp" },
	{ }
};

U_BOOT_DRIVER(starfive_otp) = {
	.name = "starfive_otp",
	.id = UCLASS_MISC,
	.of_match = sifive_otp_ids,
	.of_to_plat = starfive_otp_ofdata_to_platdata,
	.plat_auto = sizeof(struct starfive_otp_platdata),
	.ops = &starfive_otp_ops,
};
