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

#define OUTPUT_ENABLE   0
#define INPUT_ENABLE    1

/* I2C filter */
#define JHB100_I2C0_FILTER_ADDR		0x14080000
#define JHB100_I2C_FILTER_OFFSET	0x1000
#define JHB100_I2C_FILTER_MAX_NUM	16

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
	for (int i = 0; i < JHB100_I2C_FILTER_MAX_NUM; i++)
		writel(0x00, (void *)(JHB100_I2C0_FILTER_ADDR + (i * JHB100_I2C_FILTER_OFFSET)));
}

void starfive_wdt_init(void)
{
	/* TODO: Align with Linux and FW on wdt instances, for now enable all */
	starfive_wdt0_jhb100_enable();
	starfive_wdt1_jhb100_enable();
	starfive_wdt2_jhb100_enable();
	starfive_wdt3_jhb100_enable();
	starfive_wdt4_jhb100_enable();
}

void plat_gmac_init(void)
{
	#define GPIO_OUT  0
	#define GPIO_IN   1
	#define GPIO_LOW  0
	#define GPIO_HIGH 1

	/* Reference from baremetal soc_platform/lib/platform/drivers/dw_gmac.c */
	/* Reference from baremetal soc_platform/lib/platform/chip_macro/0_5_1/include/platform/drivers/gpio.h */
	/* Reference from baremetal soc_platform/lib/platform/drivers/phy */

	/* Set IOMUX */
	SET_U0_BMCPERIPH0_GPIO_IOMUX_FUNC24_SEL(2); //gpio_func_sel(GPIO_B24, 2);	// MDC
	SET_U0_BMCPERIPH0_GPIO_IOMUX_FUNC25_SEL(2); //gpio_func_sel(GPIO_B25, 2);	// MDIO
	SET_U0_BMCPERIPH2_IOMUX_FUNC18_SEL(0);      //gpio_func_sel(GPIO_D18, 0);	// RESETN
	SET_U0_BMCPERIPH2_IOMUX_FUNC19_SEL(1);      //gpio_func_sel(GPIO_D19, 1);	// RXCLK
	SET_U0_BMCPERIPH2_IOMUX_FUNC20_SEL(1);      //gpio_func_sel(GPIO_D20, 1);	// RXDV
	SET_U0_BMCPERIPH2_IOMUX_FUNC21_SEL(1);      //gpio_func_sel(GPIO_D21, 1);	// RXD0
	SET_U0_BMCPERIPH2_IOMUX_FUNC22_SEL(1);      //gpio_func_sel(GPIO_D22, 1);	// RXD1
	SET_U0_BMCPERIPH2_IOMUX_FUNC23_SEL(1);      //gpio_func_sel(GPIO_D23, 1);	// RXD2
	SET_U0_BMCPERIPH2_IOMUX_FUNC24_SEL(1);      //gpio_func_sel(GPIO_D24, 1);	// RXD3
	SET_U0_BMCPERIPH2_IOMUX_FUNC25_SEL(1);      //gpio_func_sel(GPIO_D25, 1);	// TXCLK
	SET_U0_BMCPERIPH2_IOMUX_FUNC26_SEL(1);      //gpio_func_sel(GPIO_D26, 1);	// TXEN
	SET_U0_BMCPERIPH2_IOMUX_FUNC27_SEL(1);      //gpio_func_sel(GPIO_D27, 1);	// TXD0
	SET_U0_BMCPERIPH2_IOMUX_FUNC28_SEL(1);      //gpio_func_sel(GPIO_D28, 1);	// TXD1
	SET_U0_BMCPERIPH2_IOMUX_FUNC29_SEL(1);      //gpio_func_sel(GPIO_D29, 1);	// TXD2
	SET_U0_BMCPERIPH2_IOMUX_FUNC30_SEL(1);      //gpio_func_sel(GPIO_D30, 1);	// TXD3

	/* Select to use RGMII as PHY interface */
	SET_U0_BMCPERIPH2_SYSREG__ITG_BD_APB_S_APB__BASE_ADDR_BMCPERIPH2_SYSREG_BMCPERIPH2_SYSREG_ITG_U0_DWC_ETHER_RMIIRGMII_CONTROL0_U0_DWC_ETHER_RMIIANDRGMII_PHY_INTF_SEL(0x1);


	SET_U0_BMCPERIPH2_IOMUX_FMUX_OEN18_SEL(GPIO_OUT); //GPIO_D18
	SET_U0_BMCPERIPH2_IOMUX_FMUX_O18_SEL(GPIO_HIGH);
	udelay(15000);
	SET_U0_BMCPERIPH2_IOMUX_FMUX_O18_SEL(GPIO_LOW);
	udelay(15000);
	SET_U0_BMCPERIPH2_IOMUX_FMUX_O18_SEL(GPIO_HIGH);
	udelay(15000);
}

void gmac_reset(void)
{
	/* Set clk & Assert reset */
	u0_dwc_ether_rmiiandrgmii_disable_patch();

	/* Set clk & Deassert reset */
	u0_dwc_ether_rmiiandrgmii_enable_patch();

	/* dwc_eth_qos_gmac_clk_set */
	/* baremetal: do nothing for bitfile 041 */
}

void subsys_init(void)
{
	/* PD_HOSTSIS_i0 */
	debug("before...static on..PD_HOSTSIS_i0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x2c)));

	starfive_pcu_set_pwr_mode(PD_HOSTSS_i0, PM_ON);

	debug("after...static on..PD_HOSTSIS_i0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U8_PCU__ITG_BD_APB__BASE_ADDR + 0x2c)));

#if 0
	/* PD_HOST0_USB */
	debug("before...static on..PD_HOSTSIS_i0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x2c)));

	starfive_pcu_set_pwr_mode(PD_HOST0_USB, PM_ON);

	debug("after...static on..PD_HOST0_USB..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U4_PCU__ITG_BD_APB__BASE_ADDR + 0x2c)));

	/* PD_DC0 */
	debug("before...static on..PD_DC0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x2c)));

	starfive_pcu_set_pwr_mode(PD_DC0, PM_ON);

	debug("after...static on..PD_DC0..\n");
	debug("PWR_POLICY_CAP....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x0)));
	debug("PCU_STATUS....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x4)));
	debug("PWR_POLICY_CTRL....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x8)));
	debug("PWR_REQ_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0xc)));
	debug("HARDWARE_EVENT_INDICATION....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x10)));
	debug("HARDWARE_EVENT_MASK....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x14)));
	debug("PWR_MODE_ENTRY_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x18)));
	debug("PWR_SWITCH_N_RETENTION_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x1c)));
	debug("DEVICE_CTRL_DELAY_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x20)));
	debug("INTR_STATUS....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x24)));
	debug("INTR_MASK....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x28)));
	debug("HARDWARE_EVENT_EDGE_DETECT_CFG....%x...\n", readl((const void *)(U2_PCU__ITG_BD_APB__BASE_ADDR + 0x2c)));
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

	/* Initialize peripherals reset here */
	starfive_wdt_init();
	plat_gmac_init();
	gmac_reset();
	subsys_init();

	ret = spl_board_init_f();
	if (ret) {
		printf("spl_board_init_f init failed: %d\n", ret);
		return;
	}
}
