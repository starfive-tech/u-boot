/*
 * StarFive JH7100 Serial Port driver
 * This driver ported from NS16550 Serial Port driver:
 * drivers/serial/ns16550.c
 * (which is originally from linux source (arch/powerpc/boot/ns16550.c))
 *
 * Modified for StarFive JH7100 SoC by
 * Wei Fu <wefu@redhat.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 */
#include <common.h>
#include <clk.h>
#include <debug_uart.h>
#include <dm.h>
#include <errno.h>
#include <fdtdec.h>
#include <log.h>
#include <watchdog.h>
#include <asm/io.h>
#include <linux/compiler.h>
#include <serial.h>
#include <linux/err.h>

#define UART_REG(x) u32 x
typedef struct uart_starfive {
	UART_REG(rbr);		/* 0 */
	UART_REG(ier);		/* 1 */
	UART_REG(fcr);		/* 2 */
	UART_REG(lcr);		/* 3 */
	UART_REG(mcr);		/* 4 */
	UART_REG(lsr);		/* 5 */
	UART_REG(msr);		/* 6 */
	UART_REG(spr);		/* 7 */
} uart_starfive_t;

struct starfive_uart_platdata {
	unsigned long clock;
	struct uart_starfive *regs;
};

#define thr rbr
#define iir fcr
#define dll rbr
#define dlh ier

DECLARE_GLOBAL_DATA_PTR;

/* TXCTRL register */
#define UART_TXEN		0x1
#define UART_TXWM(x)		(((x) & 0xffff) << 16)

/* RXCTRL register */
#define UART_RXEN		0x1
#define UART_RXWM(x)		(((x) & 0xffff) << 16)

/* IP register */
#define UART_IP_TXWM		0x1
#define UART_IP_RXWM		0x2

#define UART_TXFIFO_FULL	0x80000000
#define UART_RXFIFO_EMPTY	0x80000000

#define  SER_RBR		0x00
#define  SER_THR		0x00
#define  SER_DLL		0x00
#define  SER_DLH		0x04
#define  SER_IER		0x04
#define  SER_IIR		0x08
#define  SER_FCR		0x08
#define  SER_LCR		0x0C
#define  SER_MCR		0x10
#define  SER_LSR		0x14
#define  SER_MSR		0x18
#define  SER_SCR		0x1C

//UART_LCR bit define
#define LCR_WORD_LEN5		(0 << 0)
#define LCR_WORD_LEN6		BIT(0)
#define LCR_WORD_LEN7		(2 << 0)
#define LCR_WORD_LEN8		(3 << 0)
#define LCR_STOP_1BIT		(0 << 2)
#define LCR_STOP_2BIT		BIT(2)
#define LCR_PE			BIT(3)
#define LCR_EPS			BIT(4)
#define LCR_SP			BIT(5)
#define LCR_BC			BIT(6)
#define LCR_DLAB		BIT(7)

//IER, interrupt enable reg
#define IER_ERBFI		BIT(0)  //rx interrupt enable
#define IER_ETBEI		BIT(1)  //tx interrupt enable
#define IER_ELSI		BIT(2)
#define IER_EDSSI		BIT(3)
#define IER_PTIME		BIT(7)

//IIR, interrupt identify reg
#define INTR_ID_RLSI		0x06
#define INTR_ID_DATAVL		0x04
#define INTR_ID_TIMEOUT		0x0C
#define INTR_ID_THR		0x02

//FCR
#define RCVR_TRIG_1C		(0x00 << 0x06) //1 char
#define RCVR_TRIG_QFL		(0x01 << 0x06) //1/4 FIFO
#define RCVR_TRIG_HFL		(0x02 << 0x06) //1/2 FIFO
#define RCVR_TRIG_LTF		(0x03 << 0x06) //2 less than full

#define TXEM_TRIG_EMT		(0x00 << 0x04) //FIFO empty
#define TXEM_TRIG_2C		(0x00 << 0x04) //2 char
#define TXEM_TRIG_QFL		(0x02 << 0x04) //1/4 FIFO
#define TXEM_TRIG_HFL		(0x03 << 0x04) //1/2 FIFO

#define DMA_MOD1		(0x01 << 0x03)
#define DMA_MOD0		(0x00 << 0x03)
#define TXFIFO_RST		BIT(2)
#define RXFIFO_RST		BIT(1)
#define FIFO_ENA		BIT(0)

//LSR
#define DATA_RDY		BIT(0) //at least one byte available
#define RCV_OVERUN		BIT(1)
#define ERR_PARITY		BIT(2)
#define ERR_FRAMING		BIT(3)
#define ID_BREAK		BIT(4) //break interrupt bit
#define ID_THRE			BIT(5) //in FIFO THRE mode, it is the xmit fifo full flag !!!
#define ID_TEMPT		BIT(6)
#define ERR_RPE			BIT(7)

/* MCR */
#define MCR_DTR		 	BIT(0) /* dtr output */
#define MCR_RTS		 	BIT(1) /* rts output */
#define MCR_OUT1		BIT(2) /* output #1 */
#define MCR_OUT2		BIT(3) /* output #2 */
#define MCR_LOOP		BIT(4) /* loop back */
#define MCR_AFCE		BIT(5) /* auto flow control enable */

static void _ser_clrrxtmo(struct uart_starfive *regs)
{
	u32 reg32_val;

	while(1) {
		reg32_val = readl(&regs->iir);
		if((reg32_val & INTR_ID_TIMEOUT) != INTR_ID_TIMEOUT)
			break;
		reg32_val = readl(&regs->rbr);
	}
}

/* Set up the baud rate in gd struct */
static void _starfive_serial_setbrg(struct uart_starfive *regs,
				  unsigned long clock, unsigned long baud)
{
	u64 baud_value = ((clock / baud) >> 4);

	writel((baud_value & 0xFF), &regs->dll);
	writel(((baud_value >> 8) & 0xFF), &regs->dlh);
}

static void _starfive_serial_init(struct uart_starfive *regs)
{
	u32  datab, stopb, par, mcr;

	u8 databits = 8;
	u8 stopbits = 1;
	u8 parity = 0;
	u8 flow_ctl = 0;

	if (databits >= 5 && databits <= 8)
		datab = (databits - 5);
	else
		return;

	if (stopbits == 1)
		stopb = LCR_STOP_1BIT;
	else if (stopbits == 2)
		stopb = LCR_STOP_2BIT;
	else
		return;

	par = (parity == 0) ? 0 : (parity == 1) ? LCR_PE : (LCR_PE | LCR_EPS);

	writel(LCR_DLAB, &regs->lcr);
	writel(datab | stopb | par, &regs->lcr);

	//enable fifo and reset fifo, 1-byte int trig!
	writel((RCVR_TRIG_1C | TXEM_TRIG_EMT | TXFIFO_RST | RXFIFO_RST |
		FIFO_ENA), &regs->fcr);

	mcr = (flow_ctl == 0) ? 0 : MCR_RTS | MCR_AFCE;
	writel(mcr, &regs->mcr);

	//dis the ser interrupt
	writel(0, &regs->ier);

	_ser_clrrxtmo(regs);
}

static int _starfive_serial_putc(struct uart_starfive *regs, const char c)
{
	if (readl(&regs->lsr) & ID_TEMPT) {
		writel(c, &regs->thr);
		return 0;
	}
	return -EAGAIN;
}

static int _starfive_serial_getc(struct uart_starfive *regs)
{
	/* Wait here until the the FIFO is not full */
	if (readl(&regs->lsr) & DATA_RDY)
		return readl(&regs->rbr);

	return -EAGAIN;
}

static int starfive_serial_setbrg(struct udevice *dev, int baudrate)
{
	int ret;
	u32 clock = 0;
	struct clk clk;
	struct starfive_uart_platdata *platdata = dev_get_plat(dev);

	ret = clk_get_by_index(dev, 0, &clk);
	if (IS_ERR_VALUE(ret)) {
		debug("StarFive UART failed to get clock\n");
		ret = dev_read_u32(dev, "clock-frequency", &clock);
		if (IS_ERR_VALUE(ret)) {
			debug("StarFive UART clock not defined\n");
			return 0;
		}
	} else {
		clock = clk_get_rate(&clk);
		if (IS_ERR_VALUE(clock)) {
			debug("StarFive UART clock get rate failed\n");
			return 0;
		}
	}
	platdata->clock = clock;
	_starfive_serial_setbrg(platdata->regs, platdata->clock, baudrate);

	return 0;
}

static int starfive_serial_probe(struct udevice *dev)
{
	struct starfive_uart_platdata *platdata = dev_get_plat(dev);

	/* No need to reinitialize the UART after relocation */
	if (gd->flags & GD_FLG_RELOC)
		return 0;

	_starfive_serial_init(platdata->regs);

	return 0;
}

static int starfive_serial_getc(struct udevice *dev)
{
	int c;
	struct starfive_uart_platdata *platdata = dev_get_plat(dev);
	struct uart_starfive *regs = platdata->regs;

	while ((c = _starfive_serial_getc(regs)) == -EAGAIN) ;

	return c;
}

static int starfive_serial_putc(struct udevice *dev, const char ch)
{
	int rc;
	struct starfive_uart_platdata *platdata = dev_get_plat(dev);

	while ((rc = _starfive_serial_putc(platdata->regs, ch)) == -EAGAIN) ;

	return rc;
}


static int starfive_serial_pending(struct udevice *dev, bool input)
{
	struct starfive_uart_platdata *platdata = dev_get_plat(dev);
	struct uart_starfive *regs = platdata->regs;

	if (input)
		return (readl(&regs->lsr) & DATA_RDY) ? 1 : 0;
	else
		return (readl(&regs->lsr) & ID_THRE) ? 0 : 1;
}

static int starfive_serial_of_to_plat(struct udevice *dev)
{
	struct starfive_uart_platdata *platdata = dev_get_plat(dev);

	platdata->regs = (struct uart_starfive *)dev_read_addr(dev);
	if (IS_ERR(platdata->regs))
		return PTR_ERR(platdata->regs);

	return 0;
}

static const struct dm_serial_ops starfive_serial_ops = {
	.putc = starfive_serial_putc,
	.getc = starfive_serial_getc,
	.pending = starfive_serial_pending,
	.setbrg = starfive_serial_setbrg,
};

static const struct udevice_id starfive_serial_ids[] = {
	{ .compatible = "starfive,uart0" },
	{ }
};

U_BOOT_DRIVER(serial_starfive) = {
	.name	= "serial_starfive",
	.id	= UCLASS_SERIAL,
	.of_match = starfive_serial_ids,
	.of_to_plat = starfive_serial_of_to_plat,
	.plat_auto = sizeof(struct starfive_uart_platdata),
	.probe = starfive_serial_probe,
	.ops	= &starfive_serial_ops,
};

#ifdef CONFIG_DEBUG_UART_STARFIVE
static inline void _debug_uart_init(void)
{
	struct uart_starfive *regs =
			(struct uart_starfive *)CONFIG_DEBUG_UART_BASE;

	_starfive_serial_setbrg(regs, CONFIG_DEBUG_UART_CLOCK,
			      CONFIG_BAUDRATE);
	_starfive_serial_init(regs);
}

static inline void _debug_uart_putc(int ch)
{
	struct uart_starfive *regs =
			(struct uart_starfive *)CONFIG_DEBUG_UART_BASE;

	while (_starfive_serial_putc(regs, ch) == -EAGAIN)
		WATCHDOG_RESET();
}

DEBUG_UART_FUNCS
#endif