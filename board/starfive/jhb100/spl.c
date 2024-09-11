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
#include <asm/arch/saif_init.h>

#define OUTPUT_ENABLE   0
#define INPUT_ENABLE    1

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

void plat_sfc_init(void)
{
	// sfc0
	u0_dwc_ssi_sfc_enable();
}

void plat_uart_init(void)
{
	// console UART4 (N25f)
	SET_PADCFG_PAD_GPIO_A34_IE(1);
	SET_PADCFG_PAD_GPIO_A35_IE(0);
	SET_U0_SYS2_IOMUX_FUNC10_SEL(1);
	SET_U0_SYS2_IOMUX_FUNC11_SEL(1);

	SET_U0_DW_APB_UART_UART4_RX_SEL(4);
	SET_U0_DW_APB_UART_UART4_TX_SEL(4);

	// console UART5 (Merak)
	SET_PADCFG_PAD_GPIO_A36_IE(1);
	SET_PADCFG_PAD_GPIO_A37_IE(0);
	SET_U0_SYS2_IOMUX_FUNC12_SEL(1);
	SET_U0_SYS2_IOMUX_FUNC13_SEL(1);

	SET_U0_DW_APB_UART_UART5_RX_SEL(5);
	SET_U0_DW_APB_UART_UART5_TX_SEL(5);
}

void starfive_wdt_reset(void)
{

}

void rtc_reset(void)
{

}

void starfive_timer_reset(void)
{

}

void flexnoc_reset(void)
{

}

void plat_gmac_init(void)
{
	/* Reference from baremetal soc_platform/lib/platform/drivers/dw_gmac.c */
	/* Reference from baremetal soc_platform/lib/platform/chip_macro/0_5_1/include/platform/drivers/gpio.h */
	/* Reference from baremetal soc_platform/lib/platform/drivers/phy */

	/* Set IOMUX */
	SET_U0_BMCPERIPH0_GPIO_IOMUX_FUNC24_SEL(2); //gpio_func_sel(GPIO_B24, 2);	// MDC
	SET_U0_BMCPERIPH0_GPIO_IOMUX_FUNC25_SEL(2); //gpio_func_sel(GPIO_B25, 2);	// MDIO
	SET_U0_BMCPERIPH2_IOMUX_FUNC24_SEL(0);      //gpio_func_sel(GPIO_D24, 0);	// RESETN
	SET_U0_BMCPERIPH2_IOMUX_FUNC25_SEL(2);      //gpio_func_sel(GPIO_D25, 2);	// TXEN
	SET_U0_BMCPERIPH2_IOMUX_FUNC43_SEL(1);      //gpio_func_sel(GPIO_D43, 1);	// TXCLK
	SET_U0_BMCPERIPH2_IOMUX_FUNC27_SEL(2);      //gpio_func_sel(GPIO_D27, 2);	// TXD0
	SET_U0_BMCPERIPH2_IOMUX_FUNC28_SEL(2);      //gpio_func_sel(GPIO_D28, 2);	// TXD1
	SET_U0_BMCPERIPH2_IOMUX_FUNC30_SEL(2);      //gpio_func_sel(GPIO_D30, 2);	// TXD2
	SET_U0_BMCPERIPH2_IOMUX_FUNC31_SEL(2);      //gpio_func_sel(GPIO_D31, 2);	// TXD3
	SET_U0_BMCPERIPH2_IOMUX_FUNC37_SEL(1);      //gpio_func_sel(GPIO_D37, 1);	// RXCLK
	SET_U0_BMCPERIPH2_IOMUX_FUNC38_SEL(1);      //gpio_func_sel(GPIO_D38, 1);	// RXDV
	SET_U0_BMCPERIPH2_IOMUX_FUNC39_SEL(1);      //gpio_func_sel(GPIO_D39, 1);	// RXD0
	SET_U0_BMCPERIPH2_IOMUX_FUNC40_SEL(1);      //gpio_func_sel(GPIO_D40, 1);	// RXD1
	SET_U0_BMCPERIPH2_IOMUX_FUNC41_SEL(1);      //gpio_func_sel(GPIO_D41, 1);	// RXD2
	SET_U0_BMCPERIPH2_IOMUX_FUNC42_SEL(1);      //gpio_func_sel(GPIO_D42, 1);	// RXD3

	/* Reset phy - active low */
	#define GPIO_OUT  0
	#define GPIO_IN   1
	#define GPIO_LOW  0
	#define GPIO_HIGH 1

	SET_U0_BMCPERIPH2_IOMUX_FMUX_OEN24_SEL(GPIO_OUT); //GPIO_D24
	SET_U0_BMCPERIPH2_IOMUX_FMUX_O24_SEL(GPIO_HIGH);
	udelay(15000);
	SET_U0_BMCPERIPH2_IOMUX_FMUX_O24_SEL(GPIO_LOW);
	udelay(15000);
	SET_U0_BMCPERIPH2_IOMUX_FMUX_O24_SEL(GPIO_HIGH);
	udelay(15000);
}

void gmac_reset(void)
{
	/* Set clk & Assert reset */
	u0_dwc_ether_rmiiandrgmii_disable_patch();

	/* dwc_eth_qos_gmac_interface_set */
	SET_U0_DWC_ETHER_RMIIANDRGMII_PHY_INTF_SEL_I(1); //sys_con
	_SET_CLOCK_POLARITY_STATUS_CLK_BMCPERIPH2_GMAC2_RX_125_N_(1);

	/* Set clk & Deassert reset */
	u0_dwc_ether_rmiiandrgmii_enable_patch();

	/* dwc_eth_qos_gmac_clk_set */
	/* baremetal: do nothing for bitfile 041 */
}

void sd_reset(void)
{

}

void emmc_reset(void)
{

}

void xspi_reset(void)
{

}

void smbus_reset(void)
{

}

void pwm_reset(void)
{

}

void spi_reset(void)
{

}

void can_reset(void)
{

}

void sec_reset(void)
{

}

void otp_reset(void)
{

}

void board_init_f(ulong dummy)
{
	int ret;

	ret = spl_early_init();
	if (ret)
		panic("spl_early_init() failed: %d\n", ret);

	preloader_console_init();

	riscv_cpu_setup();

	/* Initialize peripherals reset here */
	plat_sfc_init();
	plat_uart_init();
	//flexnoc_reset();
	//starfive_wdt_reset();
	//starfive_timer_reset();
	plat_gmac_init();
	gmac_reset();
	//sd_reset();
	//u0_tvsensor_wrapper_enable();
	//smbus_reset();
	//pwm_reset();
	//spi_reset();
	//xspi_reset();
	//rtc_reset();
	//can_reset();
	//sec_reset();
	//otp_reset();

	ret = spl_board_init_f();
	if (ret) {
		printf("spl_board_init_f init failed: %d\n", ret);
		return;
	}
}
