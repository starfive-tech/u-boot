/**
 ******************************************************************************
 * @copyright Copyright (c) 2020 StarFive Technology Co.,Ltd.
 * @file starfive-jhb100.h
 * @author StarFive SFT Team
 * @brief
 ******************************************************************************
 */

#ifndef _STARFIVE_JHB100_H
#define _STARFIVE_JHB100_H

#include <version.h>
#include <linux/sizes.h>

#ifdef CONFIG_SPL

#define CONFIG_SPL_STACK	(0x40100000 - GENERATED_GBL_DATA_SIZE)

#define STARFIVE_SPL_BOOT_LOAD_ADDR 0x48000000
#endif

#define CONFIG_SYS_CACHELINE_SIZE 64

/*
 * CPU and Board Configuration Options
 */

#define CONFIG_BOOTP_SEND_HOSTNAME
//#define CONFIG_BOOTP_SERVERIP

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size */
//#define CONFIG_SYS_BOOTM_LEN (32 << 20) /* 32MB */

/*
 * max number of command args
 */
#define CONFIG_SYS_MAXARGS	64

/*
 * Boot Argument Buffer Size
 */
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

#define CONFIG_NR_DRAM_BANKS	1

#define PHYS_SDRAM_0		0x40000000	/* SDRAM Bank #1 */
//#define PHYS_SDRAM_0_SIZE	0x80000000	/* 2 GB */
#define PHYS_SDRAM_0_SIZE	0x100000000	/* 4 GB */

#define CONFIG_SYS_SDRAM_BASE	(PHYS_SDRAM_0)

/*
 * Ethernet
 */
#ifdef CONFIG_CMD_NET
#define CONFIG_DW_ALTDESCRIPTOR
//#define CONFIG_PHY_ADDR		0
#define DWC_NET_PHYADDR		0
//#define CONFIG_ARP_TIMEOUT	0x5000
#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.152.100
#define CONFIG_SERVERIP		192.168.152.30
#define CONFIG_GATEWAYIP	192.168.152.1
#endif

#define CONFIG_RAMDISK_ADDR 0x70000000

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define JHB100_BOOTENV	\
	"bootenv=uEnv.txt\0"	\
	"boot_dev_s=mmc\0"	\
	"spibootconfig=tftpcompboot\0"	\
	"mmcbootconfig=mmcramfitboot\0"	\
	"fitbootfile=kernel.itb\0"	\
	"bootfile=Image\0"	\
	"fdtfile=jhb100-fpga.dtb\0"	\
	"ramdiskfile=rootfs.cpio\0"	\
	"mmcpart=2\0"

#define JHB100_KERNEL_BOOTENV	\
	"importbootenv="	\
		"echo Importing environment variables from uEnv.txt ...; "	\
		"env import -t $envloadaddr $filesize\0" \
	"loadbootenv="	\
		"if fatload mmc ${mmcdev}:${mmcpart} ${envloadaddr} ${bootenv}; then "	\
			"echo Loaded environment from ${bootenv}; "	\
			"run importbootenv; "	\
		"fi;\0"	\
	"loadimagefat=fatload mmc ${mmcdev}:${mmcpart} ${kernel_addr_r} /${bootfile}\0"	\
	"loadfitimagefat=fatload mmc ${mmcdev}:${mmcpart} ${kernel_addr_r} /${fitbootfile}\0"	\
	"loadfdtfat=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr_r} /${fdtfile}\0"	\
	"loadramdiskfat=fatload mmc ${mmcdev}:${mmcpart} ${ramdisk_addr_r} /${ramdiskfile}\0"	\
	"loadfitimagespiprim=sf read ${loadaddr} ${kernel_fit_spi_prim_off} ${kernel_fit_load_size}\0"	\
	"loadfitimagespisec=sf read ${loadaddr} ${kernel_fit_spi_sec_off} ${kernel_fit_load_size}\0"	\
	"loadcompfitimagespiprim=sf read ${kernel_comp_addr_r} ${kernel_fit_spi_prim_off} ${kernel_fit_comp_load_size}\0"	\
	"loadcompfitimagespisec=sf read ${kernel_comp_addr_r} ${kernel_fit_spi_sec_off} ${kernel_fit_comp_load_size}\0"	\
	"loadfitimagetftp=tftpboot ${loadaddr} /${fitbootfile}\0"	\
	"loadcompfitimagetftp=tftpboot ${kernel_comp_addr_r} /${fitbootfile}.gz\0"	\
	"loadimagetftp=tftpboot ${loadaddr} /${bootfile}\0"	\
	"loadcompimagetftp=tftpboot ${kernel_addr_r} /${bootfile}.gz\0"	\
	"loadfdttftp=tftpboot ${fdt_addr_r} ${fdtfile}\0"	\
	"loadramdisktftp=tftpboot ${ramdisk_addr_r} ${ramdiskfile}\0"	\
	"bootmfit=bootm ${loadaddr};\0"	\
	"ramboot=booti ${loadaddr} ${ramdisk_addr_r}:${ramdisk_size} ${fdt_addr_r};\0"	\
	"noramboot=booti ${loadaddr} - ${fdt_addr_r};\0"	\
	"gzramboot=booti ${kernel_addr_r} ${ramdisk_addr_r}:${ramdisk_size} ${fdt_addr_r};\0"	\
	"gznoramboot=booti ${kernel_addr_r} - ${fdt_addr_r};\0"	\
	"uncompfitimage=unzip ${kernel_comp_addr_r} ${loadaddr} ${kernel_fit_load_size};\0"	\
	"tftpgzramboot="	\
		"run loadcompimagetftp;"	\
		"run loadfdttftp;"	\
		"run loadramdisktftp; run gzramboot;\0"	\
	"tftpramboot="	\
		"run loadimagetftp;"	\
		"run loadfdttftp;"	\
		"run loadramdisktftp; run ramboot;\0"	\
	"mmcramfitboot="	\
		"run loadfitimagefat;"	\
		"run bootmfit;\0"	\
	"mmcboot="	\
		"run loadimagefat;"	\
		"run loadfdtfat;"	\
		"run noramboot;\0"	\
	"mmcramboot="	\
		"run loadimagefat;"	\
		"run loadfdtfat;"	\
		"if run loadramdiskfat; then "	\
			"echo ramdisk detected; "	\
			"run ramboot; "	\
		"else "	\
			"run noramboot; "	\
		"fi; \0"	\
	"spi_test_and_boot="	\
		"if sf probe; then "	\
			"echo Try booting from SPI ...; "	\
			"run ${spibootconfig};"	\
		"fi;\0"	\
	"mmc_test_and_boot="	\
		"if mmc dev ${mmcdev}; then "	\
			"echo Try booting from MMC${mmcdev} ...; "	\
			"run ${mmcbootconfig};"	\
		"fi;\0"	\
	"spi_scan_and_run="	\
		"if 0; then "	\
			"echo SPI device detected!; "	\
			"run spi_test_and_boot;"	\
		"else "	\
			"echo ERROR: SPI device not detected!; "	\
			"echo Try booting from MMC${mmcdev} ...; "	\
			"run mmc_test_and_boot;"	\
		"fi; \0"	\
	"mmc_scan_and_run="	\
		"if mmc dev ${mmcdev}; mmc rescan; then "	\
			"echo MMC device ${mmcdev} detected!; "	\
			"run mmc_test_and_boot;"	\
		"else "	\
			"echo ERROR: MMC device ${mmcdev} not detected!; "	\
		"fi; \0"	\
	"kernel_bootenv_mmc="	\
		"if test ${bootdev} = spi; then "	\
			"run spi_scan_and_run;"	\
		"fi; "	\
		"if test ${bootdev} = mmc1; then "	\
			"run mmc_scan_and_run;"	\
		"fi; "	\
		"if test ${bootdev} = mmc2; then "	\
			"run mmc_scan_and_run;"	\
		"fi; \0"	\
	"kernel_boot_env="	\
		"echo Trying to boot kernel ...;"	\
		"for boot_dev in ${boot_dev_s}; do "	\
			"run kernel_bootenv_${boot_dev}; "	\
		"done; \0"	\
	"kernel_auth_boot_spi="	\
		"echo Checking FIT image in SPI flash ...;"	\
		"if checkimgrcmap 1; then "	\
			"sf probe;"	\
			"if sf probe 0:1; then "	\
				"echo Trying to load SPI Primary FIT image ...; "	\
				"run loadfitimagespiprim;"	\
				"echo Authenticating SPI Primary FIT image ...; "	\
				"if authbm ${loadaddr}; then "	\
					"bootm ${loadaddr};"	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo SPI Primary FIT image failed authentication ...;"	\
		"if checkimgrcmap 2; then "	\
			"if sf probe 0:1; then "	\
				"echo Trying to load SPI Secondary FIT image ...; "	\
				"run loadfitimagespisec;"	\
				"echo Authenticating SPI Secondary FIT image ...; "	\
				"if authbm ${loadaddr}; then "	\
					"bootm ${loadaddr};"	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo SPI Secondary FIT image failed authentication ...;\0"	\
	"kernel_comp_auth_boot_spi="	\
		"echo Checking compressed FIT image in SPI flash ...;"	\
		"if checkimgrcmap 1; then "	\
			"echo Trying to load SPI Primary FIT image ...; "	\
			"sf probe;"	\
			"if sf probe 0:1; then "	\
				"run loadcompfitimagespiprim;"	\
				"echo Uncompressing FIT image ...; "	\
				"run uncompfitimage;"	\
				"echo Authenticating SPI Primary FIT image ...; "	\
				"if authbm ${loadaddr}; then "	\
					"bootm ${loadaddr};"	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo SPI Primary FIT image failed authentication ...;"	\
		"if checkimgrcmap 2; then "	\
			"echo Trying to load SPI Secondary FIT image ...; "	\
			"if sf probe 0:1; then "	\
				"run loadcompfitimagespisec;"	\
				"echo Uncompressing FIT image ...; "	\
				"run uncompfitimage;"	\
				"echo Authenticating SPI Secondary FIT image ...; "	\
				"if authbm ${loadaddr}; then "	\
					"bootm ${loadaddr};"	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo SPI Secondary FIT image failed authentication ...;\0"

/* TODO: The values of kernel_addr_r, fdt_addr, and ramdisk_addr_r will be confirmed
 * after discussion with the Linux team
 */
#define CFG_EXTRA_ENV_SETTINGS			\
	"bootfile=Image\0"	\
	"fdtfile=jhb100-fpga.dtb\0"	\
	"fdt_high=0xffffffffffffffff\0"			\
	"initrd_high=0xffffffffffffffff\0"		\
	"envloadaddr=0x44000000\0"	\
	"kernel_addr_r=0xc0000000\0"			\
	"kernel_comp_addr_r=0x44000000\0"		\
	"kernel_comp_size=0x2000000\0"			\
	"kernel_fit_load_size=0x2000000\0"		\
	"kernel_fit_comp_load_size=0xa00000\0"		\
	"fdt_addr_r=0x46000000\0"			\
	"load_comp_addr=0x47000000\0"	\
	"ramdisk_size=0x4000000\0"			\
	"loadaddr=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0" \
	"ramdisk_addr_r=" __stringify(CONFIG_RAMDISK_ADDR) "\0"	\
	"ipaddr=" __stringify(CONFIG_IPADDR) "\0"	\
	"netmask=" __stringify(CONFIG_NETMASK) "\0"	\
	"serverip=" __stringify(CONFIG_SERVERIP) "\0"	\
	"gatewayip=" __stringify(CONFIG_GATEWAYIP) "\0"	\
	JHB100_BOOTENV	\
	JHB100_KERNEL_BOOTENV

#endif /* _STARFIVE_JHB100_H */
