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
#include <asm/arch/spl.h>
#include <asm/arch/starfive_pcu.h>
#include <asm/arch/saif_init.h>

/* I2C filter */
#define JHB100_I2C0_FILTER_ADDR		0x14080000UL
#define JHB100_I2C_FILTER_OFFSET	0x1000
#define JHB100_I2C_FILTER_MAX_NUM	16

/* CPUSS_SECURE_CRG */
#define JHB100_CPUSS_SECURE_CRG_ADDR		0x14142000UL
#define JHB100_MAIN_ICG_EN_INT_CTRL_OFFSET	0x60
#define JHB100_MAIN_CLK_ENABLE			BIT(31)

/* PER2_SYSREG */
#define JHB100_PER2_SYSREG_ADDR			0x11bc1000UL
#define JHB100_ETHER_RMIIRGMII_CONTROL0_OFFSET	0x0
#define JHB100_ETHER_RGMII_ENABLE		BIT(8)

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

	starfive_fb_rec_map_handler(&fb_map_reg,
		starfive_get_part(PRIMARY),
		starfive_get_part(SECONDARY),
		FB_RCV_SPL_SET_UBOOT_PROP_CLEAR_MSK,
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

void jhb100_smbus_filter_disable(void)
{
	/* Disable smbus filter for all I2C filters */
	for (unsigned int i = 0; i < JHB100_I2C_FILTER_MAX_NUM; i++) {
		void *addr = (void *)(JHB100_I2C0_FILTER_ADDR + (i * JHB100_I2C_FILTER_OFFSET));
		writel(0x00, addr);
	}
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

	/* Select to use RGMII as PHY interface */
	addr = (void *)(JHB100_PER2_SYSREG_ADDR + JHB100_ETHER_RMIIRGMII_CONTROL0_OFFSET);

	val = readl(addr);
	val &= ~(0xF << 8);
	val |= JHB100_ETHER_RGMII_ENABLE;

	writel(val, addr);
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

void board_init_f(ulong dummy)
{
	int ret;

	ret = spl_early_init();
	if (ret)
		panic("spl_early_init() failed: %d\n", ret);

	preloader_console_init();

	riscv_cpu_setup();

	jhb100_smbus_filter_disable();

	jhb100_plat_init();

	subsys_init();

	ret = spl_board_init_f();
	if (ret) {
		printf("spl_board_init_f init failed: %d\n", ret);
		return;
	}
}
