/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2018 Microsemi Corporation.
 * Padmarao Begari, Microsemi Corporation <padmarao.begari@microsemi.com>
 * Copyright (C) 2018 SiFive Inc
 * Troy Benjegerdes, <troy.benjegerdes@sifive.com>
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#include <version.h>
#include <linux/sizes.h>

#ifdef CONFIG_SPL

#define CONFIG_SPL_MAX_SIZE		0x00100000
#define CONFIG_SPL_BSS_START_ADDR	0x85000000
#define CONFIG_SPL_BSS_MAX_SIZE		0x00100000
#define CONFIG_SYS_SPL_MALLOC_START	(CONFIG_SPL_BSS_START_ADDR + \
					 CONFIG_SPL_BSS_MAX_SIZE)
#define CONFIG_SYS_SPL_MALLOC_SIZE	0x00100000

#define CONFIG_SPL_STACK		(0x08000000 + 0x001D0000 - \
					 GENERATED_GBL_DATA_SIZE)

#endif

#define CONFIG_SYS_CACHELINE_SIZE	64

/*
 * CPU and Board Configuration Options
 */
#define CONFIG_BOOTP_SERVERIP

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_CBSIZE		1024	/* Console I/O Buffer Size */
#define CONFIG_SYS_BOOTM_LEN		(64 << 20) /* 64MB */

/*
 * Print Buffer Size
 */
#define CONFIG_SYS_PBSIZE	\
			(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)

/*
 * max number of command args
 */
#define CONFIG_SYS_MAXARGS		16

/*
 * Boot Argument Buffer Size
 */
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE

#define PHYS_SDRAM_0			0x80000000	/* SDRAM Bank #1 */
//#define PHYS_SDRAM_0_SIZE		0x80000000	/* 2 GB */
#define PHYS_SDRAM_0_SIZE		0x200000000	/* 8 GB */
#define CONFIG_SYS_SDRAM_BASE		(PHYS_SDRAM_0)

/* Init Stack Pointer */
#define CONFIG_SYS_INIT_SP_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_2M)

//#define CONFIG_SYS_LOAD_ADDR		0xa0000000
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + SZ_2M)
#define CONFIG_STANDALONE_LOAD_ADDR	(CONFIG_SYS_SDRAM_BASE + SZ_2M)

#define SIFIVE_BASE_ETHERNET		0x10020000	//GMAC
#define SIFIVE_BASE_GPIO	 	0x10060000

#define SIFIVE_BASE_SPI			0xA3100000
#define CONFIG_SYS_SPI_BASE		SIFIVE_BASE_SPI
#define CONFIG_SYS_SPI_CLK		(CONFIG_SYS_CLK_FREQ / 2)
#define CONFIG_ENV_SPI_MAX_HZ		25000000

#define CONFIG_BOOTFILE			"vmlinuz"

/*mac addr offset in otp*/
#define STARFIVE_OTP_MAC_OFFSET		0x28

/*
 * Ethernet
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_DW_ALTDESCRIPTOR
#define CONFIG_ARP_TIMEOUT		0x5000
#define CONFIG_NETMASK			255.255.255.0
#define CONFIG_IPADDR			192.168.120.200
#endif

/* HACK these should have '#if defined (stuff) around them like zynqp*/
#define BOOT_TARGET_DEVICES(func)	func(DHCP, dhcp, na) \
					func(MMC, mmc, 0)

#include <config_distro_bootcmd.h>

#include <environment/distro/sf.h>

#define TYPE_GUID_LOADER1		"5B193300-FC78-40CD-8002-E86C45580B47"
#define TYPE_GUID_LOADER2		"2E54B353-1271-4842-806F-E436D6AF6985"
#define TYPE_GUID_SYSTEM		"0FC63DAF-8483-4772-8E79-3D69D8477DE4"

#define PARTS_DEFAULT \
	"name=loader1,start=17K,size=1M,type=${type_guid_gpt_loader1};" \
	"name=loader2,size=4MB,type=${type_guid_gpt_loader2};" \
	"name=system,size=-,bootable,type=${type_guid_gpt_system};"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"kernel_addr_r=0x84000000\0" \
	"fdt_addr_r=0x88000000\0" \
	"scriptaddr=0x88100000\0" \
	"script_offset_f=0x1fff000\0" \
	"script_size_f=0x1000\0" \
	"pxefile_addr_r=0x88200000\0" \
	"ramdisk_addr_r=0x88300000\0" \
	"kernel_comp_addr_r=0x90000000\0" \
	"kernel_comp_size=0x10000000\0" \
	"type_guid_gpt_loader1=" TYPE_GUID_LOADER1 "\0" \
	"type_guid_gpt_loader2=" TYPE_GUID_LOADER2 "\0" \
	"type_guid_gpt_system=" TYPE_GUID_SYSTEM "\0" \
	"partitions=" PARTS_DEFAULT "\0" \
	BOOTENV \
	BOOTENV_SF

#define CONFIG_SYS_MAX_FLASH_SECT		0
#define CONFIG_SYS_MAX_FLASH_BANKS		0


#define CONFIG_SYS_BAUDRATE_TABLE		{9600,19200,38400,57600,115200,230400,460800,921600}
#define CONFIG_SYS_LOADS_BAUD_CHANGE		1	/* allow baudrate change */

/* 6.25MHz RTC clock, SiFive FU740 Manual ?? */
#define CONFIG_SYS_HZ_CLOCK			6250000

/*
+ * QSPI support
+ */
#ifdef CONFIG_OF_CONTROL			/* QSPI is controlled via DT */
#define CONFIG_CQSPI_REF_CLK			(250000000)
#endif
#define __io

#endif /* __CONFIG_H */
