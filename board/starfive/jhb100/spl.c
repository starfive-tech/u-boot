/**
  ******************************************************************************
  * @file  spl.c
  * @author  StarFive Technology
  * @version  V1.0
  * @date  25/04/2022
  * @brief
  ******************************************************************************
  * @copy
  *
  * THE PRESENT SOFTWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STARFIVE SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH SOFTWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * COPYRIGHT 2022 Shanghai StarFive Technology Co., Ltd.
  */
#include <common.h>
#include <init.h>
#include <spl.h>
#include <log.h>
#include <linux/delay.h>
#include <image.h>
#include <asm/csr.h>
#include <asm/arch/boot_src.h>
#include <asm/arch/boot_fallback.h>
#include <asm/arch/boot_mapping.h>
#include <asm/arch/boot_pti.h>
#include <asm/arch/spl.h>
#include <asm/arch/starfive_pcu.h>

/* CPUSS_SECURE_CRG */
#define JHB100_CPUSS_SECURE_CRG_ADDR		0x14142000UL
#define JHB100_MAIN_ICG_EN_INT_CTRL_OFFSET	0x60
#define JHB100_MAIN_CLK_ENABLE			BIT(31)

/* PER2CRG */
#define JHB100_PER2CRG_ADDR			0x11bc0000UL
#define JHB100_PER2CRG_MAIN_ICG_EN_ADC0_OFFSET	0x10c
#define JHB100_PER2CRG_MAIN_ICG_EN_ADC1_OFFSET	0x110
#define JHB100_PER2CRG_RESET_ASSERT0_OFFSET	0x11c
#define JHB100_RSTN_ADC				GENMASK(11, 14)

/* PRODUCT_ID */
#define JHB100_PRODUCT_ID_ADDR			0x13010038UL
#define JHB100_MASK_REV_NUM			GENMASK(3, 0)
#define JHB100_REV_NUM_A			0x0
#define JHB100_REV_NUM_A_ECO			0x1
#define JHB100_REV_NUM_B			0x4

u32 jhb100_get_product_rev_num(void)
{
	return (readl((void *)JHB100_PRODUCT_ID_ADDR) & JHB100_MASK_REV_NUM);
}

u32 spl_mmc_boot_mode(struct mmc *mmc, const u32 boot_device)
{
#if defined(CONFIG_SUPPORT_EMMC_BOOT)
	return MMCSD_MODE_EMMCBOOT;
#elif defined(CONFIG_SPL_FS_FAT) || defined(CONFIG_SPL_FS_EXT4)
	return MMCSD_MODE_FS;
#else
	return MMCSD_MODE_RAW;
#endif
}

unsigned long spl_mmc_get_uboot_raw_sector(struct mmc *mmc,
					   unsigned long raw_sect)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int part = PT_TEMP;
	int fb_rec_mmc = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_rec_mmc,
						   BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
						   BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
						   FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
						   CHECK);

	if (!map_stat) {
		part = PT_GOLDEN;
	} else if (map_stat == (FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK
				<< BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS)) {
		part = PT_ACTIVE;
	}
	return starfive_get_partition_offset(BOOT_SRC_EMMC,
					     part,
					     IMG_TYPE_UBOOT_PROPER);
}

int spl_mmc_emmc_boot_partition(struct mmc *mmc)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	int part;
#ifdef CONFIG_SYS_MMCSD_RAW_MODE_EMMC_BOOT_PARTITION
	part = CONFIG_SYS_MMCSD_RAW_MODE_EMMC_BOOT_PARTITION;
	int fb_rec_mmc = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_rec_mmc,
						   BOOT_SRC_PART_EMMC_PRIMARY_BIT_POS,
						   BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS,
						   FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
						   CHECK);
	if (!map_stat) {
		part = 2;
	} else if (map_stat == (FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK
				<< BOOT_SRC_PART_EMMC_SECONDARY_BIT_POS)) {
		part = 1;
	}
#else
	/*
	 * We need to check what the partition is configured to.
	 * 1 and 2 match up to boot0 / boot1 and 7 is user data
	 * which is the first physical partition (0).
	 */
	part = EXT_CSD_EXTRACT_BOOT_PART(mmc->part_config);
	if (part == 7)
		part = 0;
#endif
	return part;
}

unsigned int spl_spi_get_uboot_offs(struct spi_flash *flash)
{
	if (IS_ENABLED(CONFIG_JHB100_UPD_RCV_TEST_TRACE))
		printf("fn(): %s\n", __func__);
	/* Check auth or boot status of image */
	int fb_rec_spi = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_rec_spi,
				BOOT_SRC_PART_SPI_PRIMARY_BIT_POS,
				BOOT_SRC_PART_SPI_SECONDARY_BIT_POS,
				FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
				CHECK);
	if (!map_stat) {
		printf("Loading SFC Golden image...\n");
		return starfive_get_partition_offset(BOOT_SRC_SFC,
						     PT_GOLDEN,
						     IMG_TYPE_UBOOT_PROPER);
	} else if (map_stat == (FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK
				<< BOOT_SRC_PART_SPI_SECONDARY_BIT_POS)) {
		printf("Loading SFC Active image...\n");
		return starfive_get_partition_offset(BOOT_SRC_SFC,
						     PT_ACTIVE,
						     IMG_TYPE_UBOOT_PROPER);
	}
	return CONFIG_SYS_SPI_U_BOOT_OFFS;
}

int spl_board_init_f(void)
{
	int ret;

	ret = spl_soc_init();
	if (ret) {
		debug("JHB100 SPL init failed: %d\n", ret);
		return ret;
	}

	return 0;
}

void spl_perform_fixups(struct spl_image_info *spl_image)
{
	int fb_map_reg = starfive_get_fb_rec_map();
	int map_stat = starfive_fb_rec_map_handler(&fb_map_reg,
						   starfive_get_part(PRIMARY),
						   starfive_get_part(SECONDARY),
						   FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
						   CHECK);
	starfive_set_ap_ctl_boot_stage(BOOTSTG_U_BOOT_PROPER, BOOTSTG_U_BOOT_PROPER);

	if (!map_stat) {
		starfive_set_ap_sts_image_flag(BOOTSTG_U_BOOT_PROPER, BA1_IMG);
	} else {
		starfive_set_ap_sts_image_flag(BOOTSTG_U_BOOT_PROPER, BA0_IMG);
	}
	starfive_fb_rec_map_handler(&fb_map_reg,
		starfive_get_part(PRIMARY),
		starfive_get_part(SECONDARY),
		FB_RCV_L1_FW_SET_SPL_CLEAR_MSK,
		CLEAR);
	starfive_set_fb_rec_map(fb_map_reg);
}

u32 spl_boot_device(void)
{
	return jhb100_get_boot_device();
}

void board_boot_order(u32 *spl_boot_list)
{
	starfive_board_boot_order(spl_boot_list);
}

struct legacy_img_hdr *spl_get_load_buffer(ssize_t offset, size_t size)
{
	return (struct legacy_img_hdr *)(STARFIVE_SPL_BOOT_LOAD_ADDR);
}

void jhb100_plat_init(void)
{
	void *addr;
	u32 val;

	/* CPUSS Secure CRG is now in PMP region. Enable main_icg clock during SPL init to ensure
	 * Linux can boot successfully to the console in emulator environment
	 */
	addr = (void *)(JHB100_CPUSS_SECURE_CRG_ADDR + JHB100_MAIN_ICG_EN_INT_CTRL_OFFSET);
	writel(JHB100_MAIN_CLK_ENABLE, addr);

	/* Bring ADC hardware block out of reset before ADC IO pads can be used as GPIO */
	addr = (void *)(JHB100_PER2CRG_ADDR + JHB100_PER2CRG_MAIN_ICG_EN_ADC0_OFFSET);
	writel(JHB100_MAIN_CLK_ENABLE, addr);	// Enable ADC0 CLK_GATE

	addr = (void *)(JHB100_PER2CRG_ADDR + JHB100_PER2CRG_MAIN_ICG_EN_ADC1_OFFSET);
	writel(JHB100_MAIN_CLK_ENABLE, addr);	// Enable ADC1 CLK_GATE

	addr = (void *)(JHB100_PER2CRG_ADDR + JHB100_PER2CRG_RESET_ASSERT0_OFFSET);

	val = readl(addr);
	val |= JHB100_RSTN_ADC;
	writel(val, addr);	// Assert reset

	val &= ~JHB100_RSTN_ADC;
	writel(val, addr);	// Deassert reset
}

void subsys_init(void)
{
	/* PD_HOSTSIS_i0 */
	debug("before...static on..PD_HOSTSIS_i0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x2c)));

	starfive_pcu_set_pwr_mode(PD_HOSTSS_i0, PM_ON);

	debug("after...static on..PD_HOSTSIS_i0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U8_PCU_BASE_ADDR + 0x2c)));

#if 0
	/* PD_HOST0_USB */
	debug("before...static on..PD_HOSTSIS_i0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x2c)));

	starfive_pcu_set_pwr_mode(PD_HOST0_USB, PM_ON);

	debug("after...static on..PD_HOST0_USB..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U4_PCU_BASE_ADDR + 0x2c)));

	/* PD_DC0 */
	debug("before...static on..PD_DC0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x2c)));

	starfive_pcu_set_pwr_mode(PD_DC0, PM_ON);

	debug("after...static on..PD_DC0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U2_PCU_BASE_ADDR + 0x2c)));
#endif
}

#if CONFIG_IS_ENABLED(SHOW_BOOT_PROGRESS)
/*
 * Meant to indicate any error, when forcefully hang.
 * In JHB100 security use case, meant to set the next-level bootstage
 * for SCP FW to intercept.
 */
void show_boot_progress(int progress)
{
#ifdef CONFIG_SPL_BUILD
	starfive_set_ap_ctl_boot_stage(BOOTSTG_U_BOOT_PROPER, BOOTSTG_U_BOOT_PROPER);
#else
	starfive_set_ap_ctl_boot_stage(BOOTSTG_KERNEL, BOOTSTG_KERNEL);
#endif
}
#endif

void board_init_f(ulong dummy)
{
	int ret;

	ret = spl_early_init();
	if (ret)
		panic("spl_early_init() failed: %d\n", ret);

	preloader_console_init();

	riscv_cpu_setup();

	jhb100_plat_init();

	subsys_init();

	ret = spl_board_init_f();
	if (ret) {
		printf("spl_board_init_f init failed: %d\n", ret);
		return;
	}
}
