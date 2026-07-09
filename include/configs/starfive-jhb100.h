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

#ifdef CONFIG_STARFIVE_JHB100_SFC_NONE
#error "JHB100 SFC partition mechanism not selected: choose \
	CONFIG_STARFIVE_JHB100_SFC_AGT or CONFIG_STARFIVE_JHB100_SFC_AB"
#endif

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
#define CONFIG_SERVERIP		192.168.152.85
#define CONFIG_GATEWAYIP	192.168.152.1
#define CONFIG_U_BOOT_ITB	"u-boot.itb"
#endif

/**
 * Environment variables holding default load addresses
 */
#define LOAD_COMP_ADDR			__stringify(0x47000000)
#define ENV_LOAD_ADDR			__stringify(0x4fdbe000)
#define FDT_ADDR_R			__stringify(0x6bf00000)
#define RAMDISK_ADDR_R			__stringify(0x6c000000)
#define KERNEL_COMP_ADDR_R		__stringify(0x73000000)
#define KERNEL_ADDR_R			__stringify(0x75000000)
#define KERNEL_COMP_SIZE		__stringify(0x1000000)
#define KERNEL_FIT_LOAD_SIZE		__stringify(0x1000000)
#define KERNEL_FIT_COMP_LOAD_SIZE	__stringify(0x1000000)
#define RAMDISK_SIZE			__stringify(0x7000000)

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

#define JHB100_BOOTENV_COMMON	\
	"bootdev=uart\0"	\
	"bootenv=uEnv.txt\0"	\
	"bootmstatsfc=fail\0"	\
	"fdtmodify=no\0"	\
	"fitfile=kernel.itb\0"	\
	"bootfile=Image\0"	\
	"fdtfile=jhb100.dtb\0"	\
	"ramdiskfile=rootfs.cpio\0"	\
	"updcapfile=capsule.cap\0"

#ifdef CONFIG_MMC
#define JHB100_BOOTENV_MMC	\
	"mmcpart=1\0"
#else
#define JHB100_BOOTENV_MMC
#endif

#if defined(CONFIG_MMC) || defined(CONFIG_SCSI)
#define JHB100_BOOTENV_STORAGE_FIT	\
	"fitbootfile=/boot/kernel.itb\0"	\
	"fitbootrecfile=/boot/kernel-recovery.itb\0"
#else
#define JHB100_BOOTENV_STORAGE_FIT
#endif

#ifdef CONFIG_SCSI
#define JHB100_BOOTENV_UFS	\
	"lun_l=d\0"
#else
#define JHB100_BOOTENV_UFS
#endif

#define JHB100_KERNEL_BOOTENV_COMMON	\
	"set_bootargs_root_ram="		\
		"affixbootargs root=/dev/ram0\0"	\
	"loadfitimagetftp=tftpboot ${loadaddr} /${fitfile}\0"	\
	"loadcompfitimagetftp=tftpboot ${kernel_comp_addr_r} /${fitfile}.gz\0"	\
	"loadimagetftp=tftpboot ${loadaddr} /${bootfile}\0"	\
	"loadcompimagetftp=tftpboot ${kernel_addr_r} /${bootfile}.gz\0"	\
	"loadfdttftp=tftpboot ${fdt_addr_r} ${fdtfile}\0"	\
	"loadramdisktftp=tftpboot ${ramdisk_addr_r} ${ramdiskfile}\0"	\
	"loadupdcaptftp=tftpboot ${loadaddr} /${updcapfile}\0"	\
	"bootmfit=bootm ${loadaddr};\0"	\
	"ramboot=booti ${loadaddr} ${ramdisk_addr_r}:${ramdisk_size} ${fdt_addr_r};\0"	\
	"noramboot=booti ${loadaddr} - ${fdt_addr_r};\0"	\
	"gzramboot=booti ${kernel_addr_r} ${ramdisk_addr_r}:${ramdisk_size} ${fdt_addr_r};\0"	\
	"gznoramboot=booti ${kernel_addr_r} - ${fdt_addr_r};\0"	\
	"uncompfitimage=unzip ${kernel_comp_addr_r} ${loadaddr}\0"	\
	"auth_pre_os_bootm="	\
		"if authbm ${loadaddr}; then "	\
			"echo Initiate Pre OS Boot Notify ...; "	\
			"preosbootnotify;"	\
			"echo Boot OS ...; "	\
			"bootm ${loadaddr};"	\
		"fi;\0"	\
	"auth_and_bootm="	\
		"if authbm ${loadaddr}; then "	\
			"bootm ${loadaddr};"	\
		"fi;\0"	\
	"tftpgzramboot="	\
		"run loadcompimagetftp;"	\
		"run loadfdttftp;"	\
		"run loadramdisktftp; run gzramboot;\0"	\
	"tftpramboot="	\
		"run loadimagetftp;"	\
		"run loadfdttftp;"	\
		"run loadramdisktftp; run ramboot;\0"

#ifdef CONFIG_CMD_SF
#ifdef CONFIG_STARFIVE_JHB100_SFC_AGT
#define JHB100_KERNEL_BOOTENV_SFC_LAYOUT	\
	"auth_boot_kernel_fit_sfc="	\
		"echo Checking kernel FIT image in SPI flash ...;"	\
		"if checkimgrcmap 5; then "	\
			"setimgrcmap 5; "	\
			"getimginfo 5; "	\
			"run set_bootargs_root_ram;"	\
			"if sf probe 0:${cs_num}; then "	\
				"echo Authenticating SFC Active FIT image ...; "	\
				"if authbimgstorage 5; then "	\
					"run process_load_image_sfc_act;"	\
				"fi; "	\
				"if test ${bootmstatsfc} = try; then "	\
					"echo FIT binary authentication failed ...; "	\
					"echo Trying to authenticate FIT payload components instead ...; "	\
					"run process_load_image_sfc_act;"	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid SFC Active FIT image ...;"	\
		"echo Checking for SFC Golden image location in flash chip ...;"	\
		"if checkimgrcmap 6; then "	\
			"setimgrcmap 6; "	\
			"getimginfo 6; "	\
			"run set_bootargs_root_ram;"	\
			"if sf probe 0:${cs_num}; then "	\
				"echo Authenticating SFC Golden FIT image ...; "	\
				"if authbimgstorage 6; then "	\
					"run process_load_image_sfc_gol;"	\
				"fi; "	\
				"if test ${bootmstatsfc} = try; then "	\
					"echo FIT binary authentication failed ...; "	\
					"echo Trying to authenticate FIT payload components instead ...; "	\
					"run process_load_image_sfc_gol;"	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid SFC Golden FIT image ...; \0"	\
	"parse_write_agt_upd_cap_sfc="	\
		"if parsecap ${loadaddr}; then "	\
			"sf probe 0:${sfc_temp_cs}; "	\
			"echo Writing parsed update capsule to SFC temp partition ...; "	\
			"run sfc_write_cap_temp;"	\
			"sf probe 0:${sfc_gol_cs}; "	\
			"echo Writing parsed update capsule to SFC golden partition ...; "	\
			"run sfc_write_cap_gol;"	\
			"sf probe 0:${sfc_act_cs}; "	\
			"echo Writing parsed update capsule to SFC active partition ...; "	\
			"run sfc_write_cap_act;"	\
			"echo Writing complete ...; "	\
		"fi; \0"
#else /* AB (active/backup) partition layout */
#define JHB100_KERNEL_BOOTENV_SFC_LAYOUT	\
	"auth_boot_kernel_fit_sfc="	\
		"echo Checking kernel FIT image in SPI flash ...;"	\
		"if checkimgrcmap 5; then "	\
			"setimgrcmap 5; "	\
			"getimginfo 5; "	\
			"run set_bootargs_root_ram;"	\
			"if sf probe 0:${cs_num}; then "	\
				"echo Authenticating SFC Active FIT image ...; "	\
				"if authbimgstorage 5; then "	\
					"run process_load_image_sfc_act;"	\
				"fi; "	\
				"if test ${bootmstatsfc} = try; then "	\
					"echo FIT binary authentication failed ...; "	\
					"echo Trying to authenticate FIT payload components instead ...; "	\
					"run process_load_image_sfc_act;"	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid SFC Active FIT image ...; \0" \
	"parse_write_ab_upd_cap_sfc="	\
		"if parsecap ${loadaddr}; then "	\
			"sf probe 0:${sfc_gol_cs}; "	\
			"echo Writing parsed update capsule to SFC backup partition ...; "	\
			"run sfc_write_cap_gol;"	\
			"sf probe 0:${sfc_act_cs}; "	\
			"echo Writing parsed update capsule to SFC active partition ...; "	\
			"run sfc_write_cap_act;"	\
			"echo Writing complete ...; "	\
		"fi; \0"
#endif

#define JHB100_KERNEL_BOOTENV_SFC	\
	"loadfitimagespiact=sf read ${loadaddr} ${sfc_kernel_act_part_offs} ${kernel_fit_load_size}\0"	\
	"loadfitimagespigol=sf read ${loadaddr} ${sfc_kernel_gol_part_offs} ${kernel_fit_load_size}\0"	\
	"loadcompfitimagespiact=sf read ${kernel_comp_addr_r} ${sfc_kernel_act_part_offs} ${kernel_fit_load_size}\0"	\
	"loadcompfitimagespigol=sf read ${kernel_comp_addr_r} ${sfc_kernel_gol_part_offs} ${kernel_fit_load_size}\0"	\
	"loadfitimagespiprim=sf read ${loadaddr} ${kernel_fit_spi_prim_off} ${kernel_fit_load_size}\0"	\
	"loadfitimagespisec=sf read ${loadaddr} ${kernel_fit_spi_sec_off} ${kernel_fit_load_size}\0"	\
	"auth_bootm_sfc_act="	\
		"if authbm ${loadaddr}; then "	\
			"setkernelimgflg 1;"	\
			"echo Initiate Pre OS Boot Notify ...; "	\
			"preosbootnotify 0;"	\
			"echo Boot OS ...; "	\
			"bootm ${loadaddr};"	\
		"fi;\0"	\
	"auth_bootm_sfc_gol="	\
		"if authbm ${loadaddr}; then "	\
			"setkernelimgflg 2;"	\
			"echo Initiate Pre OS Boot Notify ...; "	\
			"preosbootnotify 1;"	\
			"echo Boot OS ...; "	\
			"bootm ${loadaddr};"	\
		"fi;\0"	\
	"sfc_write_cap_act="	\
		"sf update ${rofs_offs} ${sfc_act_part_offs} ${rofs_size};"	\
		"sf update ${loadaddr} ${sfc_part_last_8mb_act} ${8mb_size};\0"	\
	"sfc_write_cap_gol="	\
		"sf update ${rofs_offs} ${sfc_gol_part_offs} ${rofs_size};"	\
		"sf update ${loadaddr} ${sfc_part_last_8mb_gol} ${8mb_size};\0"	\
	"sfc_write_cap_temp="	\
		"sf update ${rofs_offs} ${sfc_temp_part_offs} ${rofs_size};"	\
		"sf update ${loadaddr} ${sfc_part_last_8mb_temp} ${8mb_size};\0"	\
	"parse_write_act_upd_cap_sfc="	\
		"if parsecap ${loadaddr}; then "	\
			"if sf probe 0:${sfc_act_cs}; then "	\
				"echo Writing parsed update capsule to SFC active partition ...; "	\
				"run sfc_write_cap_act;"	\
				"echo Writing complete ...; "	\
			"fi; "	\
		"fi; \0"	\
	"parse_write_gol_upd_cap_sfc="	\
		"if parsecap ${loadaddr}; then "	\
			"if sf probe 0:${sfc_gol_cs}; then "	\
				"echo Writing parsed update capsule to SFC golden partition ...; "	\
				"run sfc_write_cap_gol;"	\
				"echo Writing complete ...; "	\
			"fi; "	\
		"fi; \0"	\
	"parse_write_temp_upd_cap_sfc="	\
		"if parsecap ${loadaddr}; then "	\
			"if sf probe 0:${sfc_temp_cs}; then "	\
				"echo Writing parsed update capsule to SFC temp partition ...; "	\
				"run sfc_write_cap_temp;"	\
				"echo Writing complete ...; "	\
			"fi; "	\
		"fi; \0"	\
	"process_load_image_sfc_act="	\
		"echo Trying to load SPI Active FIT image ...; "	\
		"run loadcompfitimagespiact; "	\
		"echo Uncompressing FIT image ...; "	\
		"run uncompfitimage;"	\
		"run auth_bootm_sfc_act;"	\
		"echo FIT image may not be compressed, trying again ...; "	\
		"run loadfitimagespiact; "	\
		"run auth_bootm_sfc_act;"	\
		"setenv bootmstatsfc fail; \0"	\
	"process_load_image_sfc_gol="	\
		"echo Trying to load SPI Golden FIT image ...; "	\
		"run loadcompfitimagespigol; "	\
		"echo Uncompressing FIT image ...; "	\
		"run uncompfitimage;"	\
		"run auth_bootm_sfc_gol;"	\
		"echo FIT image may not be compressed, trying again ...; "	\
		"run loadfitimagespigol; "	\
		"run auth_bootm_sfc_gol;"	\
		"setenv bootmstatsfc fail; \0"	\
	JHB100_KERNEL_BOOTENV_SFC_LAYOUT
#else
#define JHB100_KERNEL_BOOTENV_SFC
#endif

#ifdef CONFIG_MMC
#define JHB100_KERNEL_BOOTENV_MMC	\
	"set_bootargs_root_storage_mmc="		\
		"affixbootargs root=/dev/mmcblk0gp${blk_num}\0"	\
	"importbootenv="	\
		"echo Importing environment variables from uEnv.txt ...; "	\
		"env import -t $envloadaddr $filesize\0" \
	"loadbootenv="	\
		"if fatload mmc ${mmcdev}:${mmcpart} ${envloadaddr} ${bootenv}; then "	\
			"echo Loaded environment from ${bootenv}; "	\
			"run importbootenv; "	\
		"fi;\0"	\
	"loademmcimgext4="	\
		"ext4load mmc 0:0 ${loadaddr} /boot/${bootfile};"	\
		"ext4load mmc 0:0 ${ramdisk_addr_r} /boot/${ramdiskfile};"	\
		"ext4load mmc 0:0 ${fdt_addr_r} /boot/${fdtfile};\0"	\
	"loademmcfitimgext4=ext4load mmc 0:0 ${loadaddr} ${fitbootfile}\0"	\
	"loadimagefat=fatload mmc ${mmcdev}:${mmcpart} ${kernel_addr_r} /${bootfile}\0"	\
	"loadfdtfat=fatload mmc ${mmcdev}:${mmcpart} ${fdt_addr_r} /${fdtfile}\0"	\
	"loadramdiskfat=fatload mmc ${mmcdev}:${mmcpart} ${ramdisk_addr_r} /${ramdiskfile}\0"	\
	"loadfitimagefatprim=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${fitbootfile}\0"	\
	"loadfitimagefatsec=fatload mmc ${mmcdev}:${mmcpart} ${loadaddr} ${fitbootrecfile}\0"	\
	"loadcompfitimagefatprim=fatload mmc ${mmcdev}:${mmcpart} ${kernel_comp_addr_r} ${fitbootfile}.gz\0"	\
	"loadcompfitimagefatsec=fatload mmc ${mmcdev}:${mmcpart} ${kernel_comp_addr_r} ${fitbootrecfile}.gz\0"	\
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
	"emmc_write_cap="	\
		"mmc write ${rofs_offs} 0x0 ${rofs_blk_size};"	\
		"mmc write ${loadaddr} ${cap_bif_hdr_offs} ${rofs_blk_offs};\0"	\
	"parse_write_temp_upd_cap_emmc="	\
		"if parsecap ${loadaddr}; then "	\
			"mmc list;"	\
			"if mmc dev 0; then "	\
				"if mmc wp-gp-type 0 ${emmc_temp_partition}; then "	\
					"mmc wp-temp 0 ${emmc_temp_partition} 0; "	\
				"fi; "	\
				"getemmcgppsz; "	\
				"mmc partconf 0 0 0 ${emmc_temp_partition}; "	\
				"echo Writing parsed update capsule to eMMC temp partition ...; "	\
				"run emmc_write_cap;"	\
				"if checksecboot; then "	\
					"mmc wp-temp 0 ${emmc_temp_partition} 1; "	\
				"fi; "	\
				"echo Writing complete ...; "	\
			"fi; "	\
		"fi; \0"	\
	"parse_write_agt_upd_cap_emmc="	\
		"if parsecap ${loadaddr}; then "	\
			"mmc list;"	\
			"if mmc dev 0; then "	\
				"if mmc wp-gp-type 0 ${emmc_temp_partition}; then "	\
					"mmc wp-temp 0 ${emmc_temp_partition} 0; "	\
				"fi; "	\
				"getemmcgppsz; "	\
				"mmc partconf 0 0 0 ${emmc_temp_partition}; "	\
				"echo Writing parsed update capsule to eMMC temp partition ...; "	\
				"run emmc_write_cap;"	\
				"if checksecboot; then "	\
					"mmc wp-temp 0 ${emmc_temp_partition} 1; "	\
				"fi; "	\
				"mmc partconf 0 0 0 ${emmc_gol_partition}; "	\
				"echo Writing parsed update capsule to eMMC golden partition ...; "	\
				"run emmc_write_cap;"	\
				"mmc partconf 0 0 0 ${emmc_act_partition}; "	\
				"echo Writing parsed update capsule to eMMC active partition ...; "	\
				"run emmc_write_cap;"	\
				"echo Writing complete ...; "	\
			"fi; "	\
		"fi; \0"	\
	"auth_boot_kernel_emmc="	\
		"echo Checking kernel image in eMMC GPP partition...;"	\
		"if checkimgrcmap 1; then "	\
			"setimgrcmap 1; "	\
			"getimginfo 1; "	\
			"run set_bootargs_root_storage_mmc;"	\
			"mmc list;"	\
			"if mmc dev 0; then "	\
				"mmc partconf 0 0 0 ${emmc_kernel_act_part_num}; "	\
				"echo Authenticating eMMC Active image ...; "	\
				"if authbimgstorage 1; then "	\
					"echo Trying to load eMMC Active image ...; "	\
					"mmc dev 0;"	\
					"mmc partconf 0 0 0 ${emmc_kernel_act_part_num}; "	\
					"if run loademmcimgext4; then "	\
						"echo Initiate Pre OS Boot Notify ...; "	\
						"preosbootnotify 0;"	\
						"echo Boot OS ...; "	\
						"run ramboot;"	\
					"fi; "	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid eMMC Active image ...;"	\
		"if checkimgrcmap 2; then "	\
			"setimgrcmap 2; "	\
			"getimginfo 2; "	\
			"run set_bootargs_root_storage_mmc;"	\
			"mmc list;"	\
			"if mmc dev 0; then "	\
				"mmc partconf 0 0 0 ${emmc_kernel_gol_part_num}; "	\
				"echo Authenticating eMMC Golden image ...; "	\
				"if authbimgstorage 2; then "	\
					"echo Trying to load eMMC Golden image ...; "	\
					"mmc dev 0;"	\
					"mmc partconf 0 0 0 ${emmc_kernel_gol_part_num}; "	\
					"if run loademmcimgext4; then "	\
						"echo Initiate Pre OS Boot Notify ...; "	\
						"preosbootnotify 1;"	\
						"echo Boot OS ...; "	\
						"run set_bootargs_root_storage_mmc;"	\
						"run ramboot;"	\
					"fi; "	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid eMMC Golden image ...;\0"	\
	"auth_boot_kernel_fit_emmc="	\
		"echo Checking kernel FIT image in eMMC GPP partition...;"	\
		"if checkimgrcmap 1; then "	\
			"setimgrcmap 1; "	\
			"getimginfo 1; "	\
			"run set_bootargs_root_storage_mmc;"	\
			"mmc list;"	\
			"if mmc dev 0; then "	\
				"echo Authenticating eMMC Active image ...; "	\
				"if authbimgstorage 1; then "	\
					"echo Trying to load eMMC Active image ...; "	\
					"mmc dev 0;"	\
					"mmc partconf 0 0 0 ${emmc_kernel_act_part_num}; "	\
					"if run loademmcfitimgext4; then "	\
						"echo Initiate Pre OS Boot Notify ...; "	\
						"preosbootnotify 0;"	\
						"mmc dev 0;"	\
						"echo Boot OS ...; "	\
						"run bootmfit;"	\
					"fi; "	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid eMMC Active image ...;"	\
		"if checkimgrcmap 2; then "	\
			"setimgrcmap 2; "	\
			"getimginfo 2; "	\
			"run set_bootargs_root_storage_mmc;"	\
			"mmc list;"	\
			"if mmc dev 0; then "	\
				"echo Authenticating eMMC Golden image ...; "	\
				"if authbimgstorage 2; then "	\
					"echo Trying to load eMMC Golden image ...; "	\
					"mmc dev 0;"	\
					"mmc partconf 0 0 0 ${emmc_kernel_gol_part_num}; "	\
					"if run loademmcfitimgext4; then "	\
						"echo Initiate Pre OS Boot Notify ...; "	\
						"preosbootnotify 1;"	\
						"mmc dev 0;"	\
						"echo Boot OS ...; "	\
						"run bootmfit;"	\
					"fi; "	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid eMMC Golden image ...;\0"
#else
#define JHB100_KERNEL_BOOTENV_MMC
#endif

#ifdef CONFIG_SCSI
#define JHB100_KERNEL_BOOTENV_UFS	\
	"set_bootargs_root_storage_ufs="		\
		"affixbootargs root=/dev/sd${lun_l}\0"	\
	"loadufsactfitimgext4=ext4load scsi ${ufs_kernel_act_part_num}:0 ${loadaddr} ${fitbootfile}\0"	\
	"loadufsgolfitimgext4=ext4load scsi ${ufs_kernel_gol_part_num}:0 ${loadaddr} ${fitbootfile}\0"	\
	"ufs_write_cap="	\
		"scsi write ${rofs_offs} 0x0 ${rofs_ufs_blk_size};"	\
		"scsi write ${loadaddr} ${cap_bif_hdr_ufs_offs} ${rofs_ufs_blk_offs};\0"	\
	"parse_write_temp_upd_cap_ufs="	\
		"if parsecap ${loadaddr}; then "	\
			"if scsi scan; then "	\
				"getufsgppsz; "	\
				"scsi device ${ufs_temp_partition}; "	\
				"echo Writing parsed update capsule to UFS temp partition ...; "	\
				"run ufs_write_cap;"	\
				"echo Writing complete ...; "	\
			"fi; "	\
		"fi; \0"	\
	"parse_write_agt_upd_cap_ufs="	\
		"if parsecap ${loadaddr}; then "	\
			"if scsi scan; then "	\
				"getufsgppsz; "	\
				"scsi device ${ufs_temp_partition}; "	\
				"echo Writing parsed update capsule to UFS temp partition ...; "	\
				"run ufs_write_cap;"	\
				"scsi device ${ufs_gol_partition}; "	\
				"echo Writing parsed update capsule to UFS golden partition ...; "	\
				"run ufs_write_cap;"	\
				"scsi device ${ufs_act_partition}; "	\
				"echo Writing parsed update capsule to UFS active partition ...; "	\
				"run ufs_write_cap;"	\
				"echo Writing complete ...; "	\
			"fi; "	\
		"fi; \0"	\
	"auth_boot_kernel_fit_ufs="	\
		"echo Checking kernel FIT image in UFS LUN GPP partition...;"	\
		"if checkimgrcmap 3; then "	\
			"setimgrcmap 3; "	\
			"getimginfo 3; "	\
			"run set_bootargs_root_storage_ufs;"	\
			"if scsi scan; then "	\
				"scsi device ${ufs_kernel_act_part_num}; "	\
				"echo Authenticating UFS Active image ...; "	\
				"if authbimgstorage 3; then "	\
					"echo Trying to load UFS Active image ...; "	\
					"scsi device ${ufs_kernel_act_part_num}; "	\
					"if run loadufsactfitimgext4; then "	\
						"echo Initiate Pre OS Boot Notify ...; "	\
						"preosbootnotify 0;"	\
						"echo Boot OS ...; "	\
						"run bootmfit;"	\
					"fi; "	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid UFS Active image ...;"	\
		"if checkimgrcmap 4; then "	\
			"setimgrcmap 4; "	\
			"getimginfo 4; "	\
			"run set_bootargs_root_storage_ufs;"	\
			"if scsi scan; then "	\
				"scsi device ${ufs_kernel_gol_part_num}; "	\
				"echo Authenticating UFS Golden image ...; "	\
				"if authbimgstorage 4; then "	\
					"echo Trying to load UFS Golden image ...; "	\
					"scsi device ${ufs_kernel_gol_part_num}; "	\
					"if run loadufsgolfitimgext4; then "	\
						"echo Initiate Pre OS Boot Notify ...; "	\
						"preosbootnotify 1;"	\
						"echo Boot OS ...; "	\
						"run bootmfit;"	\
					"fi; "	\
				"fi; "	\
			"fi; "	\
		"fi;"	\
		"echo Found invalid UFS Golden image ...;\0"
#else
#define JHB100_KERNEL_BOOTENV_UFS
#endif

#ifdef CONFIG_CMD_SF
#define JHB100_KERNEL_AUTOBOOT_SFC	\
		"if test ${bootdev} = spi; then "	\
			"run auth_boot_kernel_fit_sfc;"	\
		"fi; "
#else
#define JHB100_KERNEL_AUTOBOOT_SFC
#endif

#ifdef CONFIG_MMC
#define JHB100_KERNEL_AUTOBOOT_MMC	\
		"if test ${bootdev} = mmc1; then "	\
			"run auth_boot_kernel_fit_emmc;"	\
		"fi; "
#else
#define JHB100_KERNEL_AUTOBOOT_MMC
#endif

#ifdef CONFIG_SCSI
#define JHB100_KERNEL_AUTOBOOT_UFS	\
		"if test ${bootdev} = ufs; then "	\
			"run auth_boot_kernel_fit_ufs;"	\
		"fi; "
#else
#define JHB100_KERNEL_AUTOBOOT_UFS
#endif

#define JHB100_KERNEL_BOOTENV_AUTOBOOT	\
	"kernel_autoboot="	\
		JHB100_KERNEL_AUTOBOOT_SFC	\
		JHB100_KERNEL_AUTOBOOT_MMC	\
		JHB100_KERNEL_AUTOBOOT_UFS	\
		"if test ${bootdev} = uart; then "	\
			"echo Detected boot source is UART, please load kernel image...;"	\
		"fi; \0"

#define CFG_EXTRA_ENV_SETTINGS						\
	"bootfile=Image\0"						\
	"fdtfile=jhb100.dtb\0"						\
	"fdt_high=0xffffffffffffffff\0"					\
	"initrd_high=0xffffffffffffffff\0"				\
	"envloadaddr=" ENV_LOAD_ADDR "\0" 				\
	"kernel_addr_r=" KERNEL_ADDR_R "\0"				\
	"kernel_comp_addr_r=" KERNEL_COMP_ADDR_R "\0"			\
	"kernel_comp_size=" KERNEL_COMP_SIZE "\0"			\
	"kernel_fit_load_size="KERNEL_FIT_LOAD_SIZE "\0"		\
	"kernel_fit_comp_load_size=" KERNEL_FIT_COMP_LOAD_SIZE "\0"	\
	"fdt_addr_r=" FDT_ADDR_R "\0"					\
	"load_comp_addr=" LOAD_COMP_ADDR "\0"				\
	"ramdisk_size=" RAMDISK_SIZE "\0"				\
	"loadaddr=" __stringify(CONFIG_SYS_LOAD_ADDR) "\0"		\
	"ramdisk_addr_r=" RAMDISK_ADDR_R "\0"				\
	"ipaddr=" __stringify(CONFIG_IPADDR) "\0"			\
	"netmask=" __stringify(CONFIG_NETMASK) "\0"			\
	"serverip=" __stringify(CONFIG_SERVERIP) "\0"			\
	"gatewayip=" __stringify(CONFIG_GATEWAYIP) "\0"			\
	JHB100_BOOTENV_COMMON						\
	JHB100_BOOTENV_MMC						\
	JHB100_BOOTENV_STORAGE_FIT					\
	JHB100_BOOTENV_UFS						\
	JHB100_KERNEL_BOOTENV_COMMON					\
	JHB100_KERNEL_BOOTENV_SFC					\
	JHB100_KERNEL_BOOTENV_MMC					\
	JHB100_KERNEL_BOOTENV_UFS					\
	JHB100_KERNEL_BOOTENV_AUTOBOOT

#endif /* _STARFIVE_JHB100_H */
