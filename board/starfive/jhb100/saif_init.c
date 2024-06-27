#include <asm/arch/saif_init.h>

void u0_dwc_ssi_sfc_enable(void){
  //clk_u0_dwc_ssi_sfc_ssi_clk:['clk_u0_dwc_ssi_sfc_ssi_clk', 'clk_u0_dwc_ssi_sfc_ssi_clk_icg', 'clk_bmcperiph1_200_div_sfc0', 'clk_bmcperiph1_200_divN0', 'clk_bmcperiph1_200_divN0_div', 'clk_bmcperiph1_400', 'clk_dom_bmcperiph1_clk_bmcperiph1_400'],dst:['u0_dwc_ssi_sfc.ssi_clk']
  //default:_DIVIDE_CLOCK_CLK_BMCPERIPH1_200_DIVN0_(2);
  _ENABLE_CLOCK_CLK_U0_DWC_SSI_SFC_SSI_CLK_;
  //clk_u0_dwc_ssi_sfc_hclk:['clk_u0_dwc_ssi_sfc_hclk', 'clk_u0_dwc_ssi_sfc_hclk_icg', 'clk_bmcperiph1_200_ahb_sfc0', 'clk_bmcperiph1_200', 'clk_dom_bmcperiph1_clk_bmcperiph1_200'],dst:['u0_dwc_ssi_sfc.hclk']
  _ENABLE_CLOCK_CLK_U0_DWC_SSI_SFC_HCLK_;

  //rstn_u0_dwc_ssi_sfc_ssi_rst_n:['rstn_u0_dwc_ssi_sfc_ssi_rst_n'],dst:['u0_dwc_ssi_sfc.ssi_rst_n']
  _CLEAR_RESET_RSTGEN_RSTN_U0_DWC_SSI_SFC_SSI_RST_N_;
  //rstn_u0_dwc_ssi_sfc_hresetn:['rstn_u0_dwc_ssi_sfc_hresetn'],dst:['u0_dwc_ssi_sfc.hresetn']
  _CLEAR_RESET_RSTGEN_RSTN_U0_DWC_SSI_SFC_HRESETN_;
}

void u0_dwc_ether_rmiiandrgmii_enable_patch(void){ /* Get from baremetal - different from bitfile 014 */
		_ENABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_TX_I_;
		_ENABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_RX_I_;
		_ENABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_CSR_I_;
		_ENABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_RMII_I_;
		_ENABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_TX_180_I_;
		_ENABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_RX_180_I_;
		_ENABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_PTP_REF_I_;
		_ENABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_ACLK_I_;
		_CLEAR_RESET_RSTGEN_MAIN_RSTN_GMAC2_;
		// _CLEAR_RESET_RSTGEN_RSTN_U0_DWC_ETHER_RMIIANDRGMII_ARESETN_I_;
}

void u0_dwc_ether_rmiiandrgmii_disable_patch(void){ /* Get from baremetal - different from bitfile 014 */
	_ASSERT_RESET_RSTGEN_MAIN_RSTN_GMAC2_;
  // _ASSERT_RESET_RSTGEN_RSTN_U0_DWC_ETHER_RMIIANDRGMII_ARESETN_I_;
	_DISABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_TX_I_;
	_DISABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_RX_I_;
	_DISABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_CSR_I_;
	_DISABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_RMII_I_;
	_DISABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_TX_180_I_;
	_DISABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_RX_180_I_;
	_DISABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_CLK_PTP_REF_I_;
	_DISABLE_CLOCK_CLK_U0_DWC_ETHER_RMIIANDRGMII_ACLK_I_;
}
