//commit:06b6362e (HEAD -> b0.8.1_dv, origin/b0.8.1_dv)

#ifndef _SYS0_CRG_MACRO_H_
#define _SYS0_CRG_MACRO_H_

//#define SYS0_CRG_BASE_ADDR 0x0
#define CLK_APB_MAIN_SYS0_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x0U)
#define CLK_APB_OSC_SYS0_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x4U)
#define CLK_NCNOC0_600_CTRL_REG_ADDR                                 (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x8U)
#define CLK_DEBUG_200_CTRL_REG_ADDR                                  (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xCU)
#define CLK_DEBUG_200_ICG_BUF_CTRL_REG_ADDR                          (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x10U)
#define CLK_DEBUG_EC_DATA_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x14U)
#define CLK_DEBUG_50_DFT_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x18U)
#define CLK_APB_SIM_APB_ICG_BUF_CTRL_REG_ADDR                        (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x1CU)
#define CLK_DDR_600_CTRL_REG_ADDR                                    (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x20U)
#define CLK_DDR_AXI_MAIN_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x24U)
#define CLK_DDR_200_CTRL_REG_ADDR                                    (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x28U)
#define CLK_DDR_200_OSC_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x2CU)
#define CLK_BMCCPUSS_CNOC_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x30U)
#define CLK_BMCCPUSS_CNOC_OSC_CTRL_REG_ADDR                          (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x34U)
#define CLK_BMCCPUSS_CNOC_ICG_BUF_CTRL_REG_ADDR                      (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x38U)
#define CLK_DDR_PLL3_DIV_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x3CU)
#define CLK_DDR_PLL3_CTRL_REG_ADDR                                   (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x40U)
#define CLK_BMCPCIERP_600_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x44U)
#define CLK_BMCPCIERP_MAIN_CTRL_REG_ADDR                             (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x48U)
#define CLK_BMCPCIERP_100_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x4CU)
#define CLK_BMCPCIERP_CFG_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x50U)
#define CLK_BMCPCIERP_PHY_SCAN_400_DFT_CTRL_REG_ADDR                 (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x54U)
#define CLK_PCIE_REF_CML_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x58U)
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x5CU)
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x60U)
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x64U)
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x68U)
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x6CU)
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x70U)
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x74U)
#define CLK_U0_PCIE_REF_CML_CMOSIN_CTRL_REG_ADDR                     (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x78U)
#define CLK_HOSTSS0_100_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x7CU)
#define CLK_HOSTSS0_CFG_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x80U)
#define CLK_HOSTSS0_600_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x84U)
#define CLK_HOSTSS0_DATA_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x88U)
#define CLK_HOSTSS0_PHY_SCAN_400_CTRL_REG_ADDR                       (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x8CU)
#define DFT_GPIO_ESPI0_66_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x90U)
#define CLK_ESPI0_EXT_DFT_MUX_CTRL_REG_ADDR                          (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x94U)
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x98U)
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x9CU)
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_CTRL_REG_ADDR      (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xA0U)
#define CLK_BMCUSB_600_CTRL_REG_ADDR                                 (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xA4U)
#define CLK_BMCUSB_INIT_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xA8U)
#define CLK_BMCUSB_200_CTRL_REG_ADDR                                 (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xACU)
#define CLK_BMCUSB_TARG_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xB0U)
#define CLK_BMCUSB_SCANCLK_CTRL_REG_ADDR                             (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xB4U)
#define CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xB8U)
#define CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR                           (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xBCU)
#define CLK_BMCCPUSS_600_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xC0U)
#define CLK_BMCCPUSS_DATA_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xC4U)
#define CLK_BMCCPUSS_200_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xC8U)
#define CLK_BMCCPUSS_CFG_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xCCU)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xD0U)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xD4U)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xD8U)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xDCU)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xE0U)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xE4U)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xE8U)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xECU)
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_CTRL_REG_ADDR (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xF0U)
#define CLK_VCE_600_CTRL_REG_ADDR                                    (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xF4U)
#define CLK_VCE_INIT_CTRL_REG_ADDR                                   (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xF8U)
#define CLK_VCE_100_CTRL_REG_ADDR                                    (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0xFCU)
#define CLK_VCE_TARG_CTRL_REG_ADDR                                   (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x100U)
#define CLK_BMCPER2_600_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x104U)
#define CLK_BMCPER2_INIT_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x108U)
#define CLK_BMCPER2_100_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x10CU)
#define CLK_BMCPER2_TARG_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x110U)
#define CLK_BMCPER2_400_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x114U)
#define CLK_BMCPER2_400_OSC_CTRL_REG_ADDR                            (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x118U)
#define CLK_BMCPER2_125_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x11CU)
#define CLK_BMCPER2_125_OSC_CTRL_REG_ADDR                            (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x120U)
#define CLK_NCNOC1_600_CTRL_REG_ADDR                                 (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x128U)
#define CLK_HOSTSS1_600_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x12CU)
#define CLK_HOSTSS1_DATA_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x130U)
#define CLK_HOSTSS1_PHY_SCAN_400_CTRL_REG_ADDR                       (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x134U)
#define CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_CTRL_REG_ADDR               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x138U)
#define CLK_VOUT_600_CTRL_REG_ADDR                                   (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x144U)
#define CLK_VOUT_INIT_CTRL_REG_ADDR                                  (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x148U)
#define CLK_VOUT_AUX_CTRL_REG_ADDR                                   (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x14CU)
#define CLK_VOUT_SCAN_800_DFT_CTRL_REG_ADDR                          (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x150U)
#define CLK_BMCPER3_600_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x154U)
#define CLK_BMCPER3_INIT_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x158U)
#define CLK_HOSTUSB_600_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x15CU)
#define CLK_HOSTUSB_INIT_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x160U)
#define CLK_HOSTUSBCMN_480_CTRL_REG_ADDR                             (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x164U)
#define CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR                         (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x168U)
#define CLK_SEC_600_CTRL_REG_ADDR                                    (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x16CU)
#define CLK_SEC_DATA_INIT_CTRL_REG_ADDR                              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x170U)
#define CLK_BMCPER1_600_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x174U)
#define CLK_BMCPER1_INIT_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x178U)
#define CLK_BMCPER1_400_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x17CU)
#define CLK_BMCPER1_400_OSC_CTRL_REG_ADDR                            (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x180U)
#define CLK_BMCPER1_800_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x184U)
#define CLK_BMCPER1_800_OSC_CTRL_REG_ADDR                            (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x188U)
#define CLK_BMCPER0_600_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x18CU)
#define CLK_BMCPER0_INIT_CTRL_REG_ADDR                               (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x190U)
#define CLK_BMCPER0_400_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x194U)
#define CLK_BMCPER0_400_OSC_CTRL_REG_ADDR                            (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x198U)
#define CLK_BMCPER0_800_CTRL_REG_ADDR                                (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x19CU)
#define CLK_BMCPER0_800_OSC_CTRL_REG_ADDR                            (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x1A0U)
#define CLK_GPU0_600_CTRL_REG_ADDR                                   (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x1A4U)
#define CLK_GPU0_INIT_CTRL_REG_ADDR                                  (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x1A8U)
#define CLK_GPU1_600_CTRL_REG_ADDR                                   (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x1ACU)
#define CLK_GPU1_INIT_CTRL_REG_ADDR                                  (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x1B0U)


#define SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x1B4U)

#define SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR              (U0_SYS0_CRG__ITG_BD_APBS__BASE_ADDR + 0x1B8U)


#define CLK_APB_MAIN_SYS0_DIV_SHIFT                                  0
#define CLK_APB_MAIN_SYS0_DIV_MASK                                   0xFU
#define CLK_APB_OSC_SYS0_SW_SHIFT                                    24
#define CLK_APB_OSC_SYS0_SW_MASK                                     0x1000000U
#define CLK_APB_OSC_SYS0_SW_CLK_OSC_DATA                             0
#define CLK_APB_OSC_SYS0_SW_CLK_APB_MAIN_SYS0_DATA                   1
#define CLK_NCNOC0_600_DIV_SHIFT                                     0
#define CLK_NCNOC0_600_DIV_MASK                                      0x7U
#define CLK_DEBUG_200_DIV_SHIFT                                      0
#define CLK_DEBUG_200_DIV_MASK                                       0x7U
#define CLK_DEBUG_200_ICG_BUF_ENABLE_DATA                            1
#define CLK_DEBUG_200_ICG_BUF_DISABLE_DATA                           0
#define CLK_DEBUG_200_ICG_BUF_EN_SHIFT                               31
#define CLK_DEBUG_200_ICG_BUF_EN_MASK                                0x80000000U
#define CLK_DEBUG_EC_DATA_DIV_SHIFT                                  0
#define CLK_DEBUG_EC_DATA_DIV_MASK                                   0x7U
#define CLK_DEBUG_50_DFT_DIV_SHIFT                                   0
#define CLK_DEBUG_50_DFT_DIV_MASK                                    0x3U
#define CLK_APB_SIM_APB_ICG_BUF_ENABLE_DATA                          1
#define CLK_APB_SIM_APB_ICG_BUF_DISABLE_DATA                         0
#define CLK_APB_SIM_APB_ICG_BUF_EN_SHIFT                             31
#define CLK_APB_SIM_APB_ICG_BUF_EN_MASK                              0x80000000U
#define CLK_DDR_600_DIV_SHIFT                                        0
#define CLK_DDR_600_DIV_MASK                                         0x7U
#define CLK_DDR_AXI_MAIN_SW_SHIFT                                    24
#define CLK_DDR_AXI_MAIN_SW_MASK                                     0x1000000U
#define CLK_DDR_AXI_MAIN_SW_CLK_OSC_DATA                             0
#define CLK_DDR_AXI_MAIN_SW_CLK_DDR_600_DATA                         1
#define CLK_DDR_200_DIV_SHIFT                                        0
#define CLK_DDR_200_DIV_MASK                                         0xFU
#define CLK_DDR_200_OSC_SW_SHIFT                                     24
#define CLK_DDR_200_OSC_SW_MASK                                      0x1000000U
#define CLK_DDR_200_OSC_SW_CLK_OSC_DATA                              0
#define CLK_DDR_200_OSC_SW_CLK_DDR_200_DATA                          1
#define CLK_BMCCPUSS_CNOC_DIV_SHIFT                                  0
#define CLK_BMCCPUSS_CNOC_DIV_MASK                                   0x7U
#define CLK_BMCCPUSS_CNOC_OSC_SW_SHIFT                               24
#define CLK_BMCCPUSS_CNOC_OSC_SW_MASK                                0x1000000U
#define CLK_BMCCPUSS_CNOC_OSC_SW_CLK_OSC_DATA                        0
#define CLK_BMCCPUSS_CNOC_OSC_SW_CLK_BMCCPUSS_CNOC_DATA              1
#define CLK_BMCCPUSS_CNOC_ICG_BUF_ENABLE_DATA                        1
#define CLK_BMCCPUSS_CNOC_ICG_BUF_DISABLE_DATA                       0
#define CLK_BMCCPUSS_CNOC_ICG_BUF_EN_SHIFT                           31
#define CLK_BMCCPUSS_CNOC_ICG_BUF_EN_MASK                            0x80000000U
#define CLK_DDR_PLL3_DIV_DIV_SHIFT                                   0
#define CLK_DDR_PLL3_DIV_DIV_MASK                                    0xFU
#define CLK_DDR_PLL3_SW_SHIFT                                        24
#define CLK_DDR_PLL3_SW_MASK                                         0x1000000U
#define CLK_DDR_PLL3_SW_CLK_OSC_DATA                                 0
#define CLK_DDR_PLL3_SW_CLK_DDR_PLL3_DIV_DATA                        1
#define CLK_BMCPCIERP_600_DIV_SHIFT                                  0
#define CLK_BMCPCIERP_600_DIV_MASK                                   0x7U
#define CLK_BMCPCIERP_MAIN_SW_SHIFT                                  24
#define CLK_BMCPCIERP_MAIN_SW_MASK                                   0x1000000U
#define CLK_BMCPCIERP_MAIN_SW_CLK_OSC_DATA                           0
#define CLK_BMCPCIERP_MAIN_SW_CLK_BMCPCIERP_600_DATA                 1
#define CLK_BMCPCIERP_100_DIV_SHIFT                                  0
#define CLK_BMCPCIERP_100_DIV_MASK                                   0xFU
#define CLK_BMCPCIERP_CFG_SW_SHIFT                                   24
#define CLK_BMCPCIERP_CFG_SW_MASK                                    0x1000000U
#define CLK_BMCPCIERP_CFG_SW_CLK_OSC_DATA                            0
#define CLK_BMCPCIERP_CFG_SW_CLK_BMCPCIERP_100_DATA                  1
#define CLK_BMCPCIERP_PHY_SCAN_400_DFT_DIV_SHIFT                     0
#define CLK_BMCPCIERP_PHY_SCAN_400_DFT_DIV_MASK                      0x7U
#define CLK_PCIE_REF_CML_DIV_SHIFT                                   0
#define CLK_PCIE_REF_CML_DIV_MASK                                    0x1FU
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_ENABLE_DATA   1
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_DISABLE_DATA  0
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_SHIFT      31
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_MASK       0x80000000U
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_ENABLE_DATA 1
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_DISABLE_DATA 0
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_SHIFT 31
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_ENABLE_DATA 1
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_DISABLE_DATA 0
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_SHIFT 31
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_ENABLE_DATA 1
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_DISABLE_DATA 0
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_SHIFT 31
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_ENABLE_DATA 1
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_DISABLE_DATA 0
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT 31
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_ENABLE_DATA 1
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_DISABLE_DATA 0
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT 31
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_ENABLE_DATA   1
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_DISABLE_DATA  0
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_SHIFT      31
#define CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_MASK       0x80000000U
#define CLK_U0_PCIE_REF_CML_CMOSIN_ENABLE_DATA                       1
#define CLK_U0_PCIE_REF_CML_CMOSIN_DISABLE_DATA                      0
#define CLK_U0_PCIE_REF_CML_CMOSIN_EN_SHIFT                          31
#define CLK_U0_PCIE_REF_CML_CMOSIN_EN_MASK                           0x80000000U
#define CLK_HOSTSS0_100_DIV_SHIFT                                    0
#define CLK_HOSTSS0_100_DIV_MASK                                     0xFU
#define CLK_HOSTSS0_CFG_SW_SHIFT                                     24
#define CLK_HOSTSS0_CFG_SW_MASK                                      0x1000000U
#define CLK_HOSTSS0_CFG_SW_CLK_OSC_DATA                              0
#define CLK_HOSTSS0_CFG_SW_CLK_HOSTSS0_100_DATA                      1
#define CLK_HOSTSS0_600_DIV_SHIFT                                    0
#define CLK_HOSTSS0_600_DIV_MASK                                     0x7U
#define CLK_HOSTSS0_DATA_SW_SHIFT                                    24
#define CLK_HOSTSS0_DATA_SW_MASK                                     0x1000000U
#define CLK_HOSTSS0_DATA_SW_CLK_OSC_DATA                             0
#define CLK_HOSTSS0_DATA_SW_CLK_HOSTSS0_600_DATA                     1
#define CLK_HOSTSS0_PHY_SCAN_400_DIV_SHIFT                           0
#define CLK_HOSTSS0_PHY_SCAN_400_DIV_MASK                            0x7U
#define DFT_GPIO_ESPI0_66_DIV_SHIFT                                  0
#define DFT_GPIO_ESPI0_66_DIV_MASK                                   0xFU
#define CLK_ESPI0_EXT_DFT_MUX_SW_SHIFT                               24
#define CLK_ESPI0_EXT_DFT_MUX_SW_MASK                                0x1000000U
#define CLK_ESPI0_EXT_DFT_MUX_SW_CLK_ESPI0_EXT_DATA                  0
#define CLK_ESPI0_EXT_DFT_MUX_SW_DFT_GPIO_ESPI0_66_DATA              1
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_ENABLE_DATA 1
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_DISABLE_DATA 0
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT 31
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK 0x80000000U
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_ENABLE_DATA 1
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_DISABLE_DATA 0
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT 31
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK 0x80000000U
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_ENABLE_DATA        1
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_DISABLE_DATA       0
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_SHIFT           31
#define CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_MASK            0x80000000U
#define CLK_BMCUSB_600_DIV_SHIFT                                     0
#define CLK_BMCUSB_600_DIV_MASK                                      0x7U
#define CLK_BMCUSB_INIT_SW_SHIFT                                     24
#define CLK_BMCUSB_INIT_SW_MASK                                      0x1000000U
#define CLK_BMCUSB_INIT_SW_CLK_OSC_DATA                              0
#define CLK_BMCUSB_INIT_SW_CLK_BMCUSB_600_DATA                       1
#define CLK_BMCUSB_200_DIV_SHIFT                                     0
#define CLK_BMCUSB_200_DIV_MASK                                      0x7U
#define CLK_BMCUSB_TARG_SW_SHIFT                                     24
#define CLK_BMCUSB_TARG_SW_MASK                                      0x1000000U
#define CLK_BMCUSB_TARG_SW_CLK_OSC_DATA                              0
#define CLK_BMCUSB_TARG_SW_CLK_BMCUSB_200_DATA                       1
#define CLK_BMCUSB_SCANCLK_DIV_SHIFT                                 0
#define CLK_BMCUSB_SCANCLK_DIV_MASK                                  0x7U
#define CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_MASK 0x80000000U
#define CLK_BMCCPUSS_SYS_OSC_ENABLE_DATA                             1
#define CLK_BMCCPUSS_SYS_OSC_DISABLE_DATA                            0
#define CLK_BMCCPUSS_SYS_OSC_EN_SHIFT                                31
#define CLK_BMCCPUSS_SYS_OSC_EN_MASK                                 0x80000000U
#define CLK_BMCCPUSS_SYS_OSC_SW_SHIFT                                24
#define CLK_BMCCPUSS_SYS_OSC_SW_MASK                                 0x1000000U
#define CLK_BMCCPUSS_SYS_OSC_SW_CLK_OSC_DATA                         0
#define CLK_BMCCPUSS_SYS_OSC_SW_CLK_BMCCPUSS_SYS_DATA                1
#define CLK_BMCCPUSS_600_ENABLE_DATA                                 1
#define CLK_BMCCPUSS_600_DISABLE_DATA                                0
#define CLK_BMCCPUSS_600_EN_SHIFT                                    31
#define CLK_BMCCPUSS_600_EN_MASK                                     0x80000000U
#define CLK_BMCCPUSS_600_DIV_SHIFT                                   0
#define CLK_BMCCPUSS_600_DIV_MASK                                    0x7U
#define CLK_BMCCPUSS_DATA_SW_SHIFT                                   24
#define CLK_BMCCPUSS_DATA_SW_MASK                                    0x1000000U
#define CLK_BMCCPUSS_DATA_SW_CLK_OSC_DATA                            0
#define CLK_BMCCPUSS_DATA_SW_CLK_BMCCPUSS_600_DATA                   1
#define CLK_BMCCPUSS_200_ENABLE_DATA                                 1
#define CLK_BMCCPUSS_200_DISABLE_DATA                                0
#define CLK_BMCCPUSS_200_EN_SHIFT                                    31
#define CLK_BMCCPUSS_200_EN_MASK                                     0x80000000U
#define CLK_BMCCPUSS_200_DIV_SHIFT                                   0
#define CLK_BMCCPUSS_200_DIV_MASK                                    0x7U
#define CLK_BMCCPUSS_CFG_SW_SHIFT                                    24
#define CLK_BMCCPUSS_CFG_SW_MASK                                     0x1000000U
#define CLK_BMCCPUSS_CFG_SW_CLK_OSC_DATA                             0
#define CLK_BMCCPUSS_CFG_SW_CLK_BMCCPUSS_200_DATA                    1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_MASK 0x80000000U
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_ENABLE_DATA 1
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_DISABLE_DATA 0
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_SHIFT 31
#define CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_MASK 0x80000000U
#define CLK_VCE_600_DIV_SHIFT                                        0
#define CLK_VCE_600_DIV_MASK                                         0xFU
#define CLK_VCE_INIT_SW_SHIFT                                        24
#define CLK_VCE_INIT_SW_MASK                                         0x1000000U
#define CLK_VCE_INIT_SW_CLK_OSC_DATA                                 0
#define CLK_VCE_INIT_SW_CLK_VCE_600_DATA                             1
#define CLK_VCE_100_DIV_SHIFT                                        0
#define CLK_VCE_100_DIV_MASK                                         0xFU
#define CLK_VCE_TARG_SW_SHIFT                                        24
#define CLK_VCE_TARG_SW_MASK                                         0x1000000U
#define CLK_VCE_TARG_SW_CLK_OSC_DATA                                 0
#define CLK_VCE_TARG_SW_CLK_VCE_100_DATA                             1
#define CLK_BMCPER2_600_DIV_SHIFT                                    0
#define CLK_BMCPER2_600_DIV_MASK                                     0x7U
#define CLK_BMCPER2_INIT_SW_SHIFT                                    24
#define CLK_BMCPER2_INIT_SW_MASK                                     0x1000000U
#define CLK_BMCPER2_INIT_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER2_INIT_SW_CLK_BMCPER2_600_DATA                     1
#define CLK_BMCPER2_100_DIV_SHIFT                                    0
#define CLK_BMCPER2_100_DIV_MASK                                     0xFU
#define CLK_BMCPER2_TARG_SW_SHIFT                                    24
#define CLK_BMCPER2_TARG_SW_MASK                                     0x1000000U
#define CLK_BMCPER2_TARG_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER2_TARG_SW_CLK_BMCPER2_100_DATA                     1
#define CLK_BMCPER2_400_DIV_SHIFT                                    0
#define CLK_BMCPER2_400_DIV_MASK                                     0xFU
#define CLK_BMCPER2_400_OSC_SW_SHIFT                                 24
#define CLK_BMCPER2_400_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER2_400_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER2_400_OSC_SW_CLK_BMCPER2_400_DATA                  1
#define CLK_BMCPER2_125_DIV_SHIFT                                    0
#define CLK_BMCPER2_125_DIV_MASK                                     0xFU
#define CLK_BMCPER2_125_OSC_SW_SHIFT                                 24
#define CLK_BMCPER2_125_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER2_125_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER2_125_OSC_SW_CLK_BMCPER2_125_DATA                  1
#define CLK_NCNOC1_600_DIV_SHIFT                                     0
#define CLK_NCNOC1_600_DIV_MASK                                      0x7U
#define CLK_HOSTSS1_600_DIV_SHIFT                                    0
#define CLK_HOSTSS1_600_DIV_MASK                                     0x7U
#define CLK_HOSTSS1_DATA_SW_SHIFT                                    24
#define CLK_HOSTSS1_DATA_SW_MASK                                     0x1000000U
#define CLK_HOSTSS1_DATA_SW_CLK_OSC_DATA                             0
#define CLK_HOSTSS1_DATA_SW_CLK_HOSTSS1_600_DATA                     1
#define CLK_HOSTSS1_PHY_SCAN_400_DIV_SHIFT                           0
#define CLK_HOSTSS1_PHY_SCAN_400_DIV_MASK                            0x7U
#define CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_ENABLE_DATA                 1
#define CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_DISABLE_DATA                0
#define CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_SHIFT                    31
#define CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_MASK                     0x80000000U
#define CLK_VOUT_600_DIV_SHIFT                                       0
#define CLK_VOUT_600_DIV_MASK                                        0x7U
#define CLK_VOUT_INIT_SW_SHIFT                                       24
#define CLK_VOUT_INIT_SW_MASK                                        0x1000000U
#define CLK_VOUT_INIT_SW_CLK_OSC_DATA                                0
#define CLK_VOUT_INIT_SW_CLK_VOUT_600_DATA                           1
#define CLK_VOUT_AUX_DIV_SHIFT                                       0
#define CLK_VOUT_AUX_DIV_MASK                                        0xFFU
#define CLK_VOUT_SCAN_800_DFT_DIV_SHIFT                              0
#define CLK_VOUT_SCAN_800_DFT_DIV_MASK                               0x3U
#define CLK_BMCPER3_600_DIV_SHIFT                                    0
#define CLK_BMCPER3_600_DIV_MASK                                     0x7U
#define CLK_BMCPER3_INIT_SW_SHIFT                                    24
#define CLK_BMCPER3_INIT_SW_MASK                                     0x1000000U
#define CLK_BMCPER3_INIT_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER3_INIT_SW_CLK_BMCPER3_600_DATA                     1
#define CLK_HOSTUSB_600_DIV_SHIFT                                    0
#define CLK_HOSTUSB_600_DIV_MASK                                     0x7U
#define CLK_HOSTUSB_INIT_SW_SHIFT                                    24
#define CLK_HOSTUSB_INIT_SW_MASK                                     0x1000000U
#define CLK_HOSTUSB_INIT_SW_CLK_OSC_DATA                             0
#define CLK_HOSTUSB_INIT_SW_CLK_HOSTUSB_600_DATA                     1
#define CLK_HOSTUSBCMN_480_DIV_SHIFT                                 0
#define CLK_HOSTUSBCMN_480_DIV_MASK                                  0x7U
#define CLK_HOSTUSBCMN_480_OSC_SW_SHIFT                              24
#define CLK_HOSTUSBCMN_480_OSC_SW_MASK                               0x1000000U
#define CLK_HOSTUSBCMN_480_OSC_SW_CLK_OSC_DATA                       0
#define CLK_HOSTUSBCMN_480_OSC_SW_CLK_HOSTUSBCMN_480_DATA            1
#define CLK_SEC_600_DIV_SHIFT                                        0
#define CLK_SEC_600_DIV_MASK                                         0x7U
#define CLK_SEC_DATA_INIT_SW_SHIFT                                   24
#define CLK_SEC_DATA_INIT_SW_MASK                                    0x1000000U
#define CLK_SEC_DATA_INIT_SW_CLK_OSC_DATA                            0
#define CLK_SEC_DATA_INIT_SW_CLK_SEC_600_DATA                        1
#define CLK_BMCPER1_600_DIV_SHIFT                                    0
#define CLK_BMCPER1_600_DIV_MASK                                     0x7U
#define CLK_BMCPER1_INIT_SW_SHIFT                                    24
#define CLK_BMCPER1_INIT_SW_MASK                                     0x1000000U
#define CLK_BMCPER1_INIT_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER1_INIT_SW_CLK_BMCPER1_600_DATA                     1
#define CLK_BMCPER1_400_DIV_SHIFT                                    0
#define CLK_BMCPER1_400_DIV_MASK                                     0xFU
#define CLK_BMCPER1_400_OSC_SW_SHIFT                                 24
#define CLK_BMCPER1_400_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER1_400_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER1_400_OSC_SW_CLK_BMCPER1_400_DATA                  1
#define CLK_BMCPER1_800_DIV_SHIFT                                    0
#define CLK_BMCPER1_800_DIV_MASK                                     0x7U
#define CLK_BMCPER1_800_OSC_SW_SHIFT                                 24
#define CLK_BMCPER1_800_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER1_800_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER1_800_OSC_SW_CLK_BMCPER1_800_DATA                  1
#define CLK_BMCPER0_600_DIV_SHIFT                                    0
#define CLK_BMCPER0_600_DIV_MASK                                     0x7U
#define CLK_BMCPER0_INIT_SW_SHIFT                                    24
#define CLK_BMCPER0_INIT_SW_MASK                                     0x1000000U
#define CLK_BMCPER0_INIT_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER0_INIT_SW_CLK_BMCPER0_600_DATA                     1
#define CLK_BMCPER0_400_DIV_SHIFT                                    0
#define CLK_BMCPER0_400_DIV_MASK                                     0xFU
#define CLK_BMCPER0_400_OSC_SW_SHIFT                                 24
#define CLK_BMCPER0_400_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER0_400_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER0_400_OSC_SW_CLK_BMCPER0_400_DATA                  1
#define CLK_BMCPER0_800_DIV_SHIFT                                    0
#define CLK_BMCPER0_800_DIV_MASK                                     0xFU
#define CLK_BMCPER0_800_OSC_SW_SHIFT                                 24
#define CLK_BMCPER0_800_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER0_800_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER0_800_OSC_SW_CLK_BMCPER0_800_DATA                  1
#define CLK_GPU0_600_DIV_SHIFT                                       0
#define CLK_GPU0_600_DIV_MASK                                        0xFU
#define CLK_GPU0_INIT_SW_SHIFT                                       24
#define CLK_GPU0_INIT_SW_MASK                                        0x1000000U
#define CLK_GPU0_INIT_SW_CLK_OSC_DATA                                0
#define CLK_GPU0_INIT_SW_CLK_GPU0_600_DATA                           1
#define CLK_GPU1_600_DIV_SHIFT                                       0
#define CLK_GPU1_600_DIV_MASK                                        0xFU
#define CLK_GPU1_INIT_SW_SHIFT                                       24
#define CLK_GPU1_INIT_SW_MASK                                        0x1000000U
#define CLK_GPU1_INIT_SW_CLK_OSC_DATA                                0
#define CLK_GPU1_INIT_SW_CLK_GPU1_600_DATA                           1




#define RSTN_U0_SYS0_SYSCON_PRESETN_SHIFT                            0
#define RSTN_U0_SYS0_SYSCON_PRESETN_MASK                             (0x1 << 0)
#define RSTN_U0_SYS0_SYSCON_PRESETN_ASSERT                           1
#define RSTN_U0_SYS0_SYSCON_PRESETN_CLEAR                            0
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_SHIFT                         1
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_MASK                          (0x1 << 1)
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_ASSERT                        1
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_CLEAR                         0
#define RSTN_U0_SYS0_IOMUX_PRESETN_SHIFT                             2
#define RSTN_U0_SYS0_IOMUX_PRESETN_MASK                              (0x1 << 2)
#define RSTN_U0_SYS0_IOMUX_PRESETN_ASSERT                            1
#define RSTN_U0_SYS0_IOMUX_PRESETN_CLEAR                             0
#define RSTN_U0_SYS0H_IOMUX_PRESETN_SHIFT                            3
#define RSTN_U0_SYS0H_IOMUX_PRESETN_MASK                             (0x1 << 3)
#define RSTN_U0_SYS0H_IOMUX_PRESETN_ASSERT                           1
#define RSTN_U0_SYS0H_IOMUX_PRESETN_CLEAR                            0
#define MAIN_RSTN_PCU_BMCCPU_SHIFT                                   4
#define MAIN_RSTN_PCU_BMCCPU_MASK                                    (0x1 << 4)
#define MAIN_RSTN_PCU_BMCCPU_ASSERT                                  1
#define MAIN_RSTN_PCU_BMCCPU_CLEAR                                   0
#define MAIN_RSTN_PCU_BMCPCIERP_SHIFT                                5
#define MAIN_RSTN_PCU_BMCPCIERP_MASK                                 (0x1 << 5)
#define MAIN_RSTN_PCU_BMCPCIERP_ASSERT                               1
#define MAIN_RSTN_PCU_BMCPCIERP_CLEAR                                0
#define MAIN_RSTN_PCU_HOSTSS0_SHIFT                                  6
#define MAIN_RSTN_PCU_HOSTSS0_MASK                                   (0x1 << 6)
#define MAIN_RSTN_PCU_HOSTSS0_ASSERT                                 1
#define MAIN_RSTN_PCU_HOSTSS0_CLEAR                                  0
#define RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_SHIFT                       7
#define RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_MASK                        (0x1 << 7)
#define RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_ASSERT                      1
#define RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_CLEAR                       0
#define RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_SHIFT             8
#define RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_MASK              (0x1 << 8)
#define RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_ASSERT            1
#define RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_CLEAR             0
#define RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_SHIFT                9
#define RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_MASK                 (0x1 << 9)
#define RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_ASSERT               1
#define RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_CLEAR                0
#define MAIN_RSTN_EC_SHIFT                                           10
#define MAIN_RSTN_EC_MASK                                            (0x1 << 10)
#define MAIN_RSTN_EC_ASSERT                                          1
#define MAIN_RSTN_EC_CLEAR                                           0
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_SHIFT 11
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_MASK (0x1 << 11)
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_ASSERT 1
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_CLEAR 0
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_SHIFT 12
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_MASK (0x1 << 12)
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_ASSERT 1
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_CLEAR 0
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_SHIFT 13
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_MASK (0x1 << 13)
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_ASSERT 1
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_CLEAR 0
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_SHIFT 14
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_MASK (0x1 << 14)
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_ASSERT 1
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_CLEAR 0
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_SHIFT 15
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_MASK (0x1 << 15)
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_ASSERT 1
#define RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_CLEAR 0
#define RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_SHIFT  16
#define RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_MASK   (0x1 << 16)
#define RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_ASSERT 1
#define RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_CLEAR  0
#define RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_SHIFT      17
#define RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_MASK       (0x1 << 17)
#define RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_ASSERT     1
#define RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_CLEAR      0
#define RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_SHIFT      18
#define RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_MASK       (0x1 << 18)
#define RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_ASSERT     1
#define RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_CLEAR      0
#define RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_SHIFT       19
#define RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_MASK        (0x1 << 19)
#define RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_ASSERT      1
#define RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_CLEAR       0

#define _DIVIDE_CLOCK_CLK_APB_MAIN_SYS0_(div) 			itg_set_reg(CLK_APB_MAIN_SYS0_CTRL_REG_ADDR, div, CLK_APB_MAIN_SYS0_DIV_SHIFT, CLK_APB_MAIN_SYS0_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_APB_MAIN_SYS0_ 		itg_get_reg(CLK_APB_MAIN_SYS0_CTRL_REG_ADDR, CLK_APB_MAIN_SYS0_DIV_SHIFT, CLK_APB_MAIN_SYS0_DIV_MASK)
#define _SWITCH_CLOCK_CLK_APB_OSC_SYS0_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_APB_OSC_SYS0_CTRL_REG_ADDR, CLK_APB_OSC_SYS0_SW_CLK_OSC_DATA, CLK_APB_OSC_SYS0_SW_SHIFT, CLK_APB_OSC_SYS0_SW_MASK)
#define _SWITCH_CLOCK_CLK_APB_OSC_SYS0_SOURCE_CLK_APB_MAIN_SYS0_ 	itg_set_reg(CLK_APB_OSC_SYS0_CTRL_REG_ADDR, CLK_APB_OSC_SYS0_SW_CLK_APB_MAIN_SYS0_DATA, CLK_APB_OSC_SYS0_SW_SHIFT, CLK_APB_OSC_SYS0_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_APB_OSC_SYS0_ 		itg_get_reg(CLK_APB_OSC_SYS0_CTRL_REG_ADDR, CLK_APB_OSC_SYS0_SW_SHIFT, CLK_APB_OSC_SYS0_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_APB_OSC_SYS0_(x) 		itg_set_reg(CLK_APB_OSC_SYS0_CTRL_REG_ADDR, x, CLK_APB_OSC_SYS0_SW_SHIFT, CLK_APB_OSC_SYS0_SW_MASK)
#define _DIVIDE_CLOCK_CLK_NCNOC0_600_(div) 			itg_set_reg(CLK_NCNOC0_600_CTRL_REG_ADDR, div, CLK_NCNOC0_600_DIV_SHIFT, CLK_NCNOC0_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_NCNOC0_600_ 		itg_get_reg(CLK_NCNOC0_600_CTRL_REG_ADDR, CLK_NCNOC0_600_DIV_SHIFT, CLK_NCNOC0_600_DIV_MASK)
#define _DIVIDE_CLOCK_CLK_DEBUG_200_(div) 			itg_set_reg(CLK_DEBUG_200_CTRL_REG_ADDR, div, CLK_DEBUG_200_DIV_SHIFT, CLK_DEBUG_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_DEBUG_200_ 		itg_get_reg(CLK_DEBUG_200_CTRL_REG_ADDR, CLK_DEBUG_200_DIV_SHIFT, CLK_DEBUG_200_DIV_MASK)
#define _ENABLE_CLOCK_CLK_DEBUG_200_ICG_BUF_ 			itg_set_reg(CLK_DEBUG_200_ICG_BUF_CTRL_REG_ADDR, CLK_DEBUG_200_ICG_BUF_ENABLE_DATA, CLK_DEBUG_200_ICG_BUF_EN_SHIFT, CLK_DEBUG_200_ICG_BUF_EN_MASK)
#define _DISABLE_CLOCK_CLK_DEBUG_200_ICG_BUF_ 			itg_set_reg(CLK_DEBUG_200_ICG_BUF_CTRL_REG_ADDR, CLK_DEBUG_200_ICG_BUF_DISABLE_DATA, CLK_DEBUG_200_ICG_BUF_EN_SHIFT, CLK_DEBUG_200_ICG_BUF_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_DEBUG_200_ICG_BUF_ 		itg_get_reg(CLK_DEBUG_200_ICG_BUF_CTRL_REG_ADDR, CLK_DEBUG_200_ICG_BUF_EN_SHIFT, CLK_DEBUG_200_ICG_BUF_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_DEBUG_200_ICG_BUF_(x) 		itg_set_reg(CLK_DEBUG_200_ICG_BUF_CTRL_REG_ADDR, x, CLK_DEBUG_200_ICG_BUF_EN_SHIFT, CLK_DEBUG_200_ICG_BUF_EN_MASK)
#define _DIVIDE_CLOCK_CLK_DEBUG_EC_DATA_(div) 			itg_set_reg(CLK_DEBUG_EC_DATA_CTRL_REG_ADDR, div, CLK_DEBUG_EC_DATA_DIV_SHIFT, CLK_DEBUG_EC_DATA_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_DEBUG_EC_DATA_ 		itg_get_reg(CLK_DEBUG_EC_DATA_CTRL_REG_ADDR, CLK_DEBUG_EC_DATA_DIV_SHIFT, CLK_DEBUG_EC_DATA_DIV_MASK)
#define _DIVIDE_CLOCK_CLK_DEBUG_50_DFT_(div) 			itg_set_reg(CLK_DEBUG_50_DFT_CTRL_REG_ADDR, div, CLK_DEBUG_50_DFT_DIV_SHIFT, CLK_DEBUG_50_DFT_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_DEBUG_50_DFT_ 		itg_get_reg(CLK_DEBUG_50_DFT_CTRL_REG_ADDR, CLK_DEBUG_50_DFT_DIV_SHIFT, CLK_DEBUG_50_DFT_DIV_MASK)
#define _ENABLE_CLOCK_CLK_APB_SIM_APB_ICG_BUF_ 			itg_set_reg(CLK_APB_SIM_APB_ICG_BUF_CTRL_REG_ADDR, CLK_APB_SIM_APB_ICG_BUF_ENABLE_DATA, CLK_APB_SIM_APB_ICG_BUF_EN_SHIFT, CLK_APB_SIM_APB_ICG_BUF_EN_MASK)
#define _DISABLE_CLOCK_CLK_APB_SIM_APB_ICG_BUF_ 			itg_set_reg(CLK_APB_SIM_APB_ICG_BUF_CTRL_REG_ADDR, CLK_APB_SIM_APB_ICG_BUF_DISABLE_DATA, CLK_APB_SIM_APB_ICG_BUF_EN_SHIFT, CLK_APB_SIM_APB_ICG_BUF_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_APB_SIM_APB_ICG_BUF_ 		itg_get_reg(CLK_APB_SIM_APB_ICG_BUF_CTRL_REG_ADDR, CLK_APB_SIM_APB_ICG_BUF_EN_SHIFT, CLK_APB_SIM_APB_ICG_BUF_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_APB_SIM_APB_ICG_BUF_(x) 		itg_set_reg(CLK_APB_SIM_APB_ICG_BUF_CTRL_REG_ADDR, x, CLK_APB_SIM_APB_ICG_BUF_EN_SHIFT, CLK_APB_SIM_APB_ICG_BUF_EN_MASK)
#define _DIVIDE_CLOCK_CLK_DDR_600_(div) 			itg_set_reg(CLK_DDR_600_CTRL_REG_ADDR, div, CLK_DDR_600_DIV_SHIFT, CLK_DDR_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_DDR_600_ 		itg_get_reg(CLK_DDR_600_CTRL_REG_ADDR, CLK_DDR_600_DIV_SHIFT, CLK_DDR_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_DDR_AXI_MAIN_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_DDR_AXI_MAIN_CTRL_REG_ADDR, CLK_DDR_AXI_MAIN_SW_CLK_OSC_DATA, CLK_DDR_AXI_MAIN_SW_SHIFT, CLK_DDR_AXI_MAIN_SW_MASK)
#define _SWITCH_CLOCK_CLK_DDR_AXI_MAIN_SOURCE_CLK_DDR_600_ 	itg_set_reg(CLK_DDR_AXI_MAIN_CTRL_REG_ADDR, CLK_DDR_AXI_MAIN_SW_CLK_DDR_600_DATA, CLK_DDR_AXI_MAIN_SW_SHIFT, CLK_DDR_AXI_MAIN_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_DDR_AXI_MAIN_ 		itg_get_reg(CLK_DDR_AXI_MAIN_CTRL_REG_ADDR, CLK_DDR_AXI_MAIN_SW_SHIFT, CLK_DDR_AXI_MAIN_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_DDR_AXI_MAIN_(x) 		itg_set_reg(CLK_DDR_AXI_MAIN_CTRL_REG_ADDR, x, CLK_DDR_AXI_MAIN_SW_SHIFT, CLK_DDR_AXI_MAIN_SW_MASK)
#define _DIVIDE_CLOCK_CLK_DDR_200_(div) 			itg_set_reg(CLK_DDR_200_CTRL_REG_ADDR, div, CLK_DDR_200_DIV_SHIFT, CLK_DDR_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_DDR_200_ 		itg_get_reg(CLK_DDR_200_CTRL_REG_ADDR, CLK_DDR_200_DIV_SHIFT, CLK_DDR_200_DIV_MASK)
#define _SWITCH_CLOCK_CLK_DDR_200_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_DDR_200_OSC_CTRL_REG_ADDR, CLK_DDR_200_OSC_SW_CLK_OSC_DATA, CLK_DDR_200_OSC_SW_SHIFT, CLK_DDR_200_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_DDR_200_OSC_SOURCE_CLK_DDR_200_ 	itg_set_reg(CLK_DDR_200_OSC_CTRL_REG_ADDR, CLK_DDR_200_OSC_SW_CLK_DDR_200_DATA, CLK_DDR_200_OSC_SW_SHIFT, CLK_DDR_200_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_DDR_200_OSC_ 		itg_get_reg(CLK_DDR_200_OSC_CTRL_REG_ADDR, CLK_DDR_200_OSC_SW_SHIFT, CLK_DDR_200_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_DDR_200_OSC_(x) 		itg_set_reg(CLK_DDR_200_OSC_CTRL_REG_ADDR, x, CLK_DDR_200_OSC_SW_SHIFT, CLK_DDR_200_OSC_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCCPUSS_CNOC_(div) 			itg_set_reg(CLK_BMCCPUSS_CNOC_CTRL_REG_ADDR, div, CLK_BMCCPUSS_CNOC_DIV_SHIFT, CLK_BMCCPUSS_CNOC_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCCPUSS_CNOC_ 		itg_get_reg(CLK_BMCCPUSS_CNOC_CTRL_REG_ADDR, CLK_BMCCPUSS_CNOC_DIV_SHIFT, CLK_BMCCPUSS_CNOC_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCCPUSS_CNOC_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCCPUSS_CNOC_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_CNOC_OSC_SW_CLK_OSC_DATA, CLK_BMCCPUSS_CNOC_OSC_SW_SHIFT, CLK_BMCCPUSS_CNOC_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCCPUSS_CNOC_OSC_SOURCE_CLK_BMCCPUSS_CNOC_ 	itg_set_reg(CLK_BMCCPUSS_CNOC_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_CNOC_OSC_SW_CLK_BMCCPUSS_CNOC_DATA, CLK_BMCCPUSS_CNOC_OSC_SW_SHIFT, CLK_BMCCPUSS_CNOC_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCCPUSS_CNOC_OSC_ 		itg_get_reg(CLK_BMCCPUSS_CNOC_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_CNOC_OSC_SW_SHIFT, CLK_BMCCPUSS_CNOC_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCCPUSS_CNOC_OSC_(x) 		itg_set_reg(CLK_BMCCPUSS_CNOC_OSC_CTRL_REG_ADDR, x, CLK_BMCCPUSS_CNOC_OSC_SW_SHIFT, CLK_BMCCPUSS_CNOC_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCCPUSS_CNOC_ICG_BUF_ 			itg_set_reg(CLK_BMCCPUSS_CNOC_ICG_BUF_CTRL_REG_ADDR, CLK_BMCCPUSS_CNOC_ICG_BUF_ENABLE_DATA, CLK_BMCCPUSS_CNOC_ICG_BUF_EN_SHIFT, CLK_BMCCPUSS_CNOC_ICG_BUF_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCCPUSS_CNOC_ICG_BUF_ 			itg_set_reg(CLK_BMCCPUSS_CNOC_ICG_BUF_CTRL_REG_ADDR, CLK_BMCCPUSS_CNOC_ICG_BUF_DISABLE_DATA, CLK_BMCCPUSS_CNOC_ICG_BUF_EN_SHIFT, CLK_BMCCPUSS_CNOC_ICG_BUF_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCCPUSS_CNOC_ICG_BUF_ 		itg_get_reg(CLK_BMCCPUSS_CNOC_ICG_BUF_CTRL_REG_ADDR, CLK_BMCCPUSS_CNOC_ICG_BUF_EN_SHIFT, CLK_BMCCPUSS_CNOC_ICG_BUF_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCCPUSS_CNOC_ICG_BUF_(x) 		itg_set_reg(CLK_BMCCPUSS_CNOC_ICG_BUF_CTRL_REG_ADDR, x, CLK_BMCCPUSS_CNOC_ICG_BUF_EN_SHIFT, CLK_BMCCPUSS_CNOC_ICG_BUF_EN_MASK)
#define _DIVIDE_CLOCK_CLK_DDR_PLL3_DIV_(div) 			itg_set_reg(CLK_DDR_PLL3_DIV_CTRL_REG_ADDR, div, CLK_DDR_PLL3_DIV_DIV_SHIFT, CLK_DDR_PLL3_DIV_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_DDR_PLL3_DIV_ 		itg_get_reg(CLK_DDR_PLL3_DIV_CTRL_REG_ADDR, CLK_DDR_PLL3_DIV_DIV_SHIFT, CLK_DDR_PLL3_DIV_DIV_MASK)
#define _SWITCH_CLOCK_CLK_DDR_PLL3_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_DDR_PLL3_CTRL_REG_ADDR, CLK_DDR_PLL3_SW_CLK_OSC_DATA, CLK_DDR_PLL3_SW_SHIFT, CLK_DDR_PLL3_SW_MASK)
#define _SWITCH_CLOCK_CLK_DDR_PLL3_SOURCE_CLK_DDR_PLL3_DIV_ 	itg_set_reg(CLK_DDR_PLL3_CTRL_REG_ADDR, CLK_DDR_PLL3_SW_CLK_DDR_PLL3_DIV_DATA, CLK_DDR_PLL3_SW_SHIFT, CLK_DDR_PLL3_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_DDR_PLL3_ 		itg_get_reg(CLK_DDR_PLL3_CTRL_REG_ADDR, CLK_DDR_PLL3_SW_SHIFT, CLK_DDR_PLL3_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_DDR_PLL3_(x) 		itg_set_reg(CLK_DDR_PLL3_CTRL_REG_ADDR, x, CLK_DDR_PLL3_SW_SHIFT, CLK_DDR_PLL3_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPCIERP_600_(div) 			itg_set_reg(CLK_BMCPCIERP_600_CTRL_REG_ADDR, div, CLK_BMCPCIERP_600_DIV_SHIFT, CLK_BMCPCIERP_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPCIERP_600_ 		itg_get_reg(CLK_BMCPCIERP_600_CTRL_REG_ADDR, CLK_BMCPCIERP_600_DIV_SHIFT, CLK_BMCPCIERP_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPCIERP_MAIN_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPCIERP_MAIN_CTRL_REG_ADDR, CLK_BMCPCIERP_MAIN_SW_CLK_OSC_DATA, CLK_BMCPCIERP_MAIN_SW_SHIFT, CLK_BMCPCIERP_MAIN_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPCIERP_MAIN_SOURCE_CLK_BMCPCIERP_600_ 	itg_set_reg(CLK_BMCPCIERP_MAIN_CTRL_REG_ADDR, CLK_BMCPCIERP_MAIN_SW_CLK_BMCPCIERP_600_DATA, CLK_BMCPCIERP_MAIN_SW_SHIFT, CLK_BMCPCIERP_MAIN_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPCIERP_MAIN_ 		itg_get_reg(CLK_BMCPCIERP_MAIN_CTRL_REG_ADDR, CLK_BMCPCIERP_MAIN_SW_SHIFT, CLK_BMCPCIERP_MAIN_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPCIERP_MAIN_(x) 		itg_set_reg(CLK_BMCPCIERP_MAIN_CTRL_REG_ADDR, x, CLK_BMCPCIERP_MAIN_SW_SHIFT, CLK_BMCPCIERP_MAIN_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPCIERP_100_(div) 			itg_set_reg(CLK_BMCPCIERP_100_CTRL_REG_ADDR, div, CLK_BMCPCIERP_100_DIV_SHIFT, CLK_BMCPCIERP_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPCIERP_100_ 		itg_get_reg(CLK_BMCPCIERP_100_CTRL_REG_ADDR, CLK_BMCPCIERP_100_DIV_SHIFT, CLK_BMCPCIERP_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPCIERP_CFG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPCIERP_CFG_CTRL_REG_ADDR, CLK_BMCPCIERP_CFG_SW_CLK_OSC_DATA, CLK_BMCPCIERP_CFG_SW_SHIFT, CLK_BMCPCIERP_CFG_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPCIERP_CFG_SOURCE_CLK_BMCPCIERP_100_ 	itg_set_reg(CLK_BMCPCIERP_CFG_CTRL_REG_ADDR, CLK_BMCPCIERP_CFG_SW_CLK_BMCPCIERP_100_DATA, CLK_BMCPCIERP_CFG_SW_SHIFT, CLK_BMCPCIERP_CFG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPCIERP_CFG_ 		itg_get_reg(CLK_BMCPCIERP_CFG_CTRL_REG_ADDR, CLK_BMCPCIERP_CFG_SW_SHIFT, CLK_BMCPCIERP_CFG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPCIERP_CFG_(x) 		itg_set_reg(CLK_BMCPCIERP_CFG_CTRL_REG_ADDR, x, CLK_BMCPCIERP_CFG_SW_SHIFT, CLK_BMCPCIERP_CFG_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPCIERP_PHY_SCAN_400_DFT_(div) 			itg_set_reg(CLK_BMCPCIERP_PHY_SCAN_400_DFT_CTRL_REG_ADDR, div, CLK_BMCPCIERP_PHY_SCAN_400_DFT_DIV_SHIFT, CLK_BMCPCIERP_PHY_SCAN_400_DFT_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPCIERP_PHY_SCAN_400_DFT_ 		itg_get_reg(CLK_BMCPCIERP_PHY_SCAN_400_DFT_CTRL_REG_ADDR, CLK_BMCPCIERP_PHY_SCAN_400_DFT_DIV_SHIFT, CLK_BMCPCIERP_PHY_SCAN_400_DFT_DIV_MASK)
#define _DIVIDE_CLOCK_CLK_PCIE_REF_CML_(div) 			itg_set_reg(CLK_PCIE_REF_CML_CTRL_REG_ADDR, div, CLK_PCIE_REF_CML_DIV_SHIFT, CLK_PCIE_REF_CML_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_PCIE_REF_CML_ 		itg_get_reg(CLK_PCIE_REF_CML_CTRL_REG_ADDR, CLK_PCIE_REF_CML_DIV_SHIFT, CLK_PCIE_REF_CML_DIV_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_ENABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_DISABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_ 		itg_get_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_(x) 		itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_OSC_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_ENABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_DISABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_ 		itg_get_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_(x) 		itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_DATA_INIT_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_ENABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_DISABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_ 		itg_get_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_(x) 		itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_CFG_INIT_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_ENABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_DISABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_ 		itg_get_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_(x) 		itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_NCNOC_TARG_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_ENABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_DISABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_ 		itg_get_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_(x) 		itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_ENABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_DISABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_ 		itg_get_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_(x) 		itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_ENABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_ 			itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_DISABLE_DATA, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_ 		itg_get_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_CTRL_REG_ADDR, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_(x) 		itg_set_reg(CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_SHIFT, CLK_U0_DOM_BMCPCIERP_CLK_DOM_BMCPCIERP_CLK_PCU_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_PCIE_REF_CML_CMOSIN_ 			itg_set_reg(CLK_U0_PCIE_REF_CML_CMOSIN_CTRL_REG_ADDR, CLK_U0_PCIE_REF_CML_CMOSIN_ENABLE_DATA, CLK_U0_PCIE_REF_CML_CMOSIN_EN_SHIFT, CLK_U0_PCIE_REF_CML_CMOSIN_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_PCIE_REF_CML_CMOSIN_ 			itg_set_reg(CLK_U0_PCIE_REF_CML_CMOSIN_CTRL_REG_ADDR, CLK_U0_PCIE_REF_CML_CMOSIN_DISABLE_DATA, CLK_U0_PCIE_REF_CML_CMOSIN_EN_SHIFT, CLK_U0_PCIE_REF_CML_CMOSIN_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_PCIE_REF_CML_CMOSIN_ 		itg_get_reg(CLK_U0_PCIE_REF_CML_CMOSIN_CTRL_REG_ADDR, CLK_U0_PCIE_REF_CML_CMOSIN_EN_SHIFT, CLK_U0_PCIE_REF_CML_CMOSIN_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_PCIE_REF_CML_CMOSIN_(x) 		itg_set_reg(CLK_U0_PCIE_REF_CML_CMOSIN_CTRL_REG_ADDR, x, CLK_U0_PCIE_REF_CML_CMOSIN_EN_SHIFT, CLK_U0_PCIE_REF_CML_CMOSIN_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS0_100_(div) 			itg_set_reg(CLK_HOSTSS0_100_CTRL_REG_ADDR, div, CLK_HOSTSS0_100_DIV_SHIFT, CLK_HOSTSS0_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS0_100_ 		itg_get_reg(CLK_HOSTSS0_100_CTRL_REG_ADDR, CLK_HOSTSS0_100_DIV_SHIFT, CLK_HOSTSS0_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS0_CFG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTSS0_CFG_CTRL_REG_ADDR, CLK_HOSTSS0_CFG_SW_CLK_OSC_DATA, CLK_HOSTSS0_CFG_SW_SHIFT, CLK_HOSTSS0_CFG_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS0_CFG_SOURCE_CLK_HOSTSS0_100_ 	itg_set_reg(CLK_HOSTSS0_CFG_CTRL_REG_ADDR, CLK_HOSTSS0_CFG_SW_CLK_HOSTSS0_100_DATA, CLK_HOSTSS0_CFG_SW_SHIFT, CLK_HOSTSS0_CFG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTSS0_CFG_ 		itg_get_reg(CLK_HOSTSS0_CFG_CTRL_REG_ADDR, CLK_HOSTSS0_CFG_SW_SHIFT, CLK_HOSTSS0_CFG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTSS0_CFG_(x) 		itg_set_reg(CLK_HOSTSS0_CFG_CTRL_REG_ADDR, x, CLK_HOSTSS0_CFG_SW_SHIFT, CLK_HOSTSS0_CFG_SW_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS0_600_(div) 			itg_set_reg(CLK_HOSTSS0_600_CTRL_REG_ADDR, div, CLK_HOSTSS0_600_DIV_SHIFT, CLK_HOSTSS0_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS0_600_ 		itg_get_reg(CLK_HOSTSS0_600_CTRL_REG_ADDR, CLK_HOSTSS0_600_DIV_SHIFT, CLK_HOSTSS0_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS0_DATA_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTSS0_DATA_CTRL_REG_ADDR, CLK_HOSTSS0_DATA_SW_CLK_OSC_DATA, CLK_HOSTSS0_DATA_SW_SHIFT, CLK_HOSTSS0_DATA_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS0_DATA_SOURCE_CLK_HOSTSS0_600_ 	itg_set_reg(CLK_HOSTSS0_DATA_CTRL_REG_ADDR, CLK_HOSTSS0_DATA_SW_CLK_HOSTSS0_600_DATA, CLK_HOSTSS0_DATA_SW_SHIFT, CLK_HOSTSS0_DATA_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTSS0_DATA_ 		itg_get_reg(CLK_HOSTSS0_DATA_CTRL_REG_ADDR, CLK_HOSTSS0_DATA_SW_SHIFT, CLK_HOSTSS0_DATA_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTSS0_DATA_(x) 		itg_set_reg(CLK_HOSTSS0_DATA_CTRL_REG_ADDR, x, CLK_HOSTSS0_DATA_SW_SHIFT, CLK_HOSTSS0_DATA_SW_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS0_PHY_SCAN_400_(div) 			itg_set_reg(CLK_HOSTSS0_PHY_SCAN_400_CTRL_REG_ADDR, div, CLK_HOSTSS0_PHY_SCAN_400_DIV_SHIFT, CLK_HOSTSS0_PHY_SCAN_400_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS0_PHY_SCAN_400_ 		itg_get_reg(CLK_HOSTSS0_PHY_SCAN_400_CTRL_REG_ADDR, CLK_HOSTSS0_PHY_SCAN_400_DIV_SHIFT, CLK_HOSTSS0_PHY_SCAN_400_DIV_MASK)
#define _DIVIDE_CLOCK_DFT_GPIO_ESPI0_66_(div) 			itg_set_reg(DFT_GPIO_ESPI0_66_CTRL_REG_ADDR, div, DFT_GPIO_ESPI0_66_DIV_SHIFT, DFT_GPIO_ESPI0_66_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_DFT_GPIO_ESPI0_66_ 		itg_get_reg(DFT_GPIO_ESPI0_66_CTRL_REG_ADDR, DFT_GPIO_ESPI0_66_DIV_SHIFT, DFT_GPIO_ESPI0_66_DIV_MASK)
#define _SWITCH_CLOCK_CLK_ESPI0_EXT_DFT_MUX_SOURCE_CLK_ESPI0_EXT_ 	itg_set_reg(CLK_ESPI0_EXT_DFT_MUX_CTRL_REG_ADDR, CLK_ESPI0_EXT_DFT_MUX_SW_CLK_ESPI0_EXT_DATA, CLK_ESPI0_EXT_DFT_MUX_SW_SHIFT, CLK_ESPI0_EXT_DFT_MUX_SW_MASK)
#define _SWITCH_CLOCK_CLK_ESPI0_EXT_DFT_MUX_SOURCE_DFT_GPIO_ESPI0_66_ 	itg_set_reg(CLK_ESPI0_EXT_DFT_MUX_CTRL_REG_ADDR, CLK_ESPI0_EXT_DFT_MUX_SW_DFT_GPIO_ESPI0_66_DATA, CLK_ESPI0_EXT_DFT_MUX_SW_SHIFT, CLK_ESPI0_EXT_DFT_MUX_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_ESPI0_EXT_DFT_MUX_ 		itg_get_reg(CLK_ESPI0_EXT_DFT_MUX_CTRL_REG_ADDR, CLK_ESPI0_EXT_DFT_MUX_SW_SHIFT, CLK_ESPI0_EXT_DFT_MUX_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_ESPI0_EXT_DFT_MUX_(x) 		itg_set_reg(CLK_ESPI0_EXT_DFT_MUX_CTRL_REG_ADDR, x, CLK_ESPI0_EXT_DFT_MUX_SW_SHIFT, CLK_ESPI0_EXT_DFT_MUX_SW_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_ 			itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_ENABLE_DATA, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_ 			itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_DISABLE_DATA, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_ 		itg_get_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_(x) 		itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_CTRL_REG_ADDR, x, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_400_DFT_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_ 			itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_ENABLE_DATA, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_ 			itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_DISABLE_DATA, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_ 		itg_get_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_(x) 		itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_CTRL_REG_ADDR, x, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_PCIE_PHY_SCAN_1000_DFT_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_ 			itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_ENABLE_DATA, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_ 			itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_DISABLE_DATA, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_ 		itg_get_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_CTRL_REG_ADDR, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_(x) 		itg_set_reg(CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_CTRL_REG_ADDR, x, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_SHIFT, CLK_U0_DOM_HOSTSS_CLK_DOM_HOSTSS_CLK_ESPI_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCUSB_600_(div) 			itg_set_reg(CLK_BMCUSB_600_CTRL_REG_ADDR, div, CLK_BMCUSB_600_DIV_SHIFT, CLK_BMCUSB_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCUSB_600_ 		itg_get_reg(CLK_BMCUSB_600_CTRL_REG_ADDR, CLK_BMCUSB_600_DIV_SHIFT, CLK_BMCUSB_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCUSB_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCUSB_INIT_CTRL_REG_ADDR, CLK_BMCUSB_INIT_SW_CLK_OSC_DATA, CLK_BMCUSB_INIT_SW_SHIFT, CLK_BMCUSB_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCUSB_INIT_SOURCE_CLK_BMCUSB_600_ 	itg_set_reg(CLK_BMCUSB_INIT_CTRL_REG_ADDR, CLK_BMCUSB_INIT_SW_CLK_BMCUSB_600_DATA, CLK_BMCUSB_INIT_SW_SHIFT, CLK_BMCUSB_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCUSB_INIT_ 		itg_get_reg(CLK_BMCUSB_INIT_CTRL_REG_ADDR, CLK_BMCUSB_INIT_SW_SHIFT, CLK_BMCUSB_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCUSB_INIT_(x) 		itg_set_reg(CLK_BMCUSB_INIT_CTRL_REG_ADDR, x, CLK_BMCUSB_INIT_SW_SHIFT, CLK_BMCUSB_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCUSB_200_(div) 			itg_set_reg(CLK_BMCUSB_200_CTRL_REG_ADDR, div, CLK_BMCUSB_200_DIV_SHIFT, CLK_BMCUSB_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCUSB_200_ 		itg_get_reg(CLK_BMCUSB_200_CTRL_REG_ADDR, CLK_BMCUSB_200_DIV_SHIFT, CLK_BMCUSB_200_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCUSB_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCUSB_TARG_CTRL_REG_ADDR, CLK_BMCUSB_TARG_SW_CLK_OSC_DATA, CLK_BMCUSB_TARG_SW_SHIFT, CLK_BMCUSB_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCUSB_TARG_SOURCE_CLK_BMCUSB_200_ 	itg_set_reg(CLK_BMCUSB_TARG_CTRL_REG_ADDR, CLK_BMCUSB_TARG_SW_CLK_BMCUSB_200_DATA, CLK_BMCUSB_TARG_SW_SHIFT, CLK_BMCUSB_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCUSB_TARG_ 		itg_get_reg(CLK_BMCUSB_TARG_CTRL_REG_ADDR, CLK_BMCUSB_TARG_SW_SHIFT, CLK_BMCUSB_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCUSB_TARG_(x) 		itg_set_reg(CLK_BMCUSB_TARG_CTRL_REG_ADDR, x, CLK_BMCUSB_TARG_SW_SHIFT, CLK_BMCUSB_TARG_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCUSB_SCANCLK_(div) 			itg_set_reg(CLK_BMCUSB_SCANCLK_CTRL_REG_ADDR, div, CLK_BMCUSB_SCANCLK_DIV_SHIFT, CLK_BMCUSB_SCANCLK_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCUSB_SCANCLK_ 		itg_get_reg(CLK_BMCUSB_SCANCLK_CTRL_REG_ADDR, CLK_BMCUSB_SCANCLK_DIV_SHIFT, CLK_BMCUSB_SCANCLK_DIV_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_ 			itg_set_reg(CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_ENABLE_DATA, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_SHIFT, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_ 			itg_set_reg(CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_DISABLE_DATA, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_SHIFT, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_ 		itg_get_reg(CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_SHIFT, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_SHIFT, CLK_U0_DOM_BMCUSB_CLK_DOM_BMCUSB_BMCUSB_480M_SCANCLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_BMCCPUSS_SYS_OSC_ 			itg_set_reg(CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_SYS_OSC_ENABLE_DATA, CLK_BMCCPUSS_SYS_OSC_EN_SHIFT, CLK_BMCCPUSS_SYS_OSC_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCCPUSS_SYS_OSC_ 			itg_set_reg(CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_SYS_OSC_DISABLE_DATA, CLK_BMCCPUSS_SYS_OSC_EN_SHIFT, CLK_BMCCPUSS_SYS_OSC_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCCPUSS_SYS_OSC_ 		itg_get_reg(CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_SYS_OSC_EN_SHIFT, CLK_BMCCPUSS_SYS_OSC_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCCPUSS_SYS_OSC_(x) 		itg_set_reg(CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR, x, CLK_BMCCPUSS_SYS_OSC_EN_SHIFT, CLK_BMCCPUSS_SYS_OSC_EN_MASK)
#define _SWITCH_CLOCK_CLK_BMCCPUSS_SYS_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_SYS_OSC_SW_CLK_OSC_DATA, CLK_BMCCPUSS_SYS_OSC_SW_SHIFT, CLK_BMCCPUSS_SYS_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCCPUSS_SYS_OSC_SOURCE_CLK_BMCCPUSS_SYS_ 	itg_set_reg(CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_SYS_OSC_SW_CLK_BMCCPUSS_SYS_DATA, CLK_BMCCPUSS_SYS_OSC_SW_SHIFT, CLK_BMCCPUSS_SYS_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCCPUSS_SYS_OSC_ 		itg_get_reg(CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR, CLK_BMCCPUSS_SYS_OSC_SW_SHIFT, CLK_BMCCPUSS_SYS_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCCPUSS_SYS_OSC_(x) 		itg_set_reg(CLK_BMCCPUSS_SYS_OSC_CTRL_REG_ADDR, x, CLK_BMCCPUSS_SYS_OSC_SW_SHIFT, CLK_BMCCPUSS_SYS_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCCPUSS_600_ 			itg_set_reg(CLK_BMCCPUSS_600_CTRL_REG_ADDR, CLK_BMCCPUSS_600_ENABLE_DATA, CLK_BMCCPUSS_600_EN_SHIFT, CLK_BMCCPUSS_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCCPUSS_600_ 			itg_set_reg(CLK_BMCCPUSS_600_CTRL_REG_ADDR, CLK_BMCCPUSS_600_DISABLE_DATA, CLK_BMCCPUSS_600_EN_SHIFT, CLK_BMCCPUSS_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCCPUSS_600_ 		itg_get_reg(CLK_BMCCPUSS_600_CTRL_REG_ADDR, CLK_BMCCPUSS_600_EN_SHIFT, CLK_BMCCPUSS_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCCPUSS_600_(x) 		itg_set_reg(CLK_BMCCPUSS_600_CTRL_REG_ADDR, x, CLK_BMCCPUSS_600_EN_SHIFT, CLK_BMCCPUSS_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCCPUSS_600_(div) 			itg_set_reg(CLK_BMCCPUSS_600_CTRL_REG_ADDR, div, CLK_BMCCPUSS_600_DIV_SHIFT, CLK_BMCCPUSS_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCCPUSS_600_ 		itg_get_reg(CLK_BMCCPUSS_600_CTRL_REG_ADDR, CLK_BMCCPUSS_600_DIV_SHIFT, CLK_BMCCPUSS_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCCPUSS_DATA_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCCPUSS_DATA_CTRL_REG_ADDR, CLK_BMCCPUSS_DATA_SW_CLK_OSC_DATA, CLK_BMCCPUSS_DATA_SW_SHIFT, CLK_BMCCPUSS_DATA_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCCPUSS_DATA_SOURCE_CLK_BMCCPUSS_600_ 	itg_set_reg(CLK_BMCCPUSS_DATA_CTRL_REG_ADDR, CLK_BMCCPUSS_DATA_SW_CLK_BMCCPUSS_600_DATA, CLK_BMCCPUSS_DATA_SW_SHIFT, CLK_BMCCPUSS_DATA_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCCPUSS_DATA_ 		itg_get_reg(CLK_BMCCPUSS_DATA_CTRL_REG_ADDR, CLK_BMCCPUSS_DATA_SW_SHIFT, CLK_BMCCPUSS_DATA_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCCPUSS_DATA_(x) 		itg_set_reg(CLK_BMCCPUSS_DATA_CTRL_REG_ADDR, x, CLK_BMCCPUSS_DATA_SW_SHIFT, CLK_BMCCPUSS_DATA_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCCPUSS_200_ 			itg_set_reg(CLK_BMCCPUSS_200_CTRL_REG_ADDR, CLK_BMCCPUSS_200_ENABLE_DATA, CLK_BMCCPUSS_200_EN_SHIFT, CLK_BMCCPUSS_200_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCCPUSS_200_ 			itg_set_reg(CLK_BMCCPUSS_200_CTRL_REG_ADDR, CLK_BMCCPUSS_200_DISABLE_DATA, CLK_BMCCPUSS_200_EN_SHIFT, CLK_BMCCPUSS_200_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCCPUSS_200_ 		itg_get_reg(CLK_BMCCPUSS_200_CTRL_REG_ADDR, CLK_BMCCPUSS_200_EN_SHIFT, CLK_BMCCPUSS_200_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCCPUSS_200_(x) 		itg_set_reg(CLK_BMCCPUSS_200_CTRL_REG_ADDR, x, CLK_BMCCPUSS_200_EN_SHIFT, CLK_BMCCPUSS_200_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCCPUSS_200_(div) 			itg_set_reg(CLK_BMCCPUSS_200_CTRL_REG_ADDR, div, CLK_BMCCPUSS_200_DIV_SHIFT, CLK_BMCCPUSS_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCCPUSS_200_ 		itg_get_reg(CLK_BMCCPUSS_200_CTRL_REG_ADDR, CLK_BMCCPUSS_200_DIV_SHIFT, CLK_BMCCPUSS_200_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCCPUSS_CFG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCCPUSS_CFG_CTRL_REG_ADDR, CLK_BMCCPUSS_CFG_SW_CLK_OSC_DATA, CLK_BMCCPUSS_CFG_SW_SHIFT, CLK_BMCCPUSS_CFG_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCCPUSS_CFG_SOURCE_CLK_BMCCPUSS_200_ 	itg_set_reg(CLK_BMCCPUSS_CFG_CTRL_REG_ADDR, CLK_BMCCPUSS_CFG_SW_CLK_BMCCPUSS_200_DATA, CLK_BMCCPUSS_CFG_SW_SHIFT, CLK_BMCCPUSS_CFG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCCPUSS_CFG_ 		itg_get_reg(CLK_BMCCPUSS_CFG_CTRL_REG_ADDR, CLK_BMCCPUSS_CFG_SW_SHIFT, CLK_BMCCPUSS_CFG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCCPUSS_CFG_(x) 		itg_set_reg(CLK_BMCCPUSS_CFG_CTRL_REG_ADDR, x, CLK_BMCCPUSS_CFG_SW_SHIFT, CLK_BMCCPUSS_CFG_SW_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_SYS_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_OSC_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_INIT_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_CFG_TARG_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_CNOC_FP_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_NCNOC_DATA_TARG_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_UST_CLK_UDB_IP_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_ENABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_ 			itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_DISABLE_DATA, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_ 		itg_get_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_CTRL_REG_ADDR, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_(x) 		itg_set_reg(CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_CTRL_REG_ADDR, x, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_SHIFT, CLK_U0_DOM_BMCCPUSS_CLK_DOM_BMCCPUSS_BMCCPUSS_JTAG_TCK_XBAR_EN_MASK)
#define _DIVIDE_CLOCK_CLK_VCE_600_(div) 			itg_set_reg(CLK_VCE_600_CTRL_REG_ADDR, div, CLK_VCE_600_DIV_SHIFT, CLK_VCE_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VCE_600_ 		itg_get_reg(CLK_VCE_600_CTRL_REG_ADDR, CLK_VCE_600_DIV_SHIFT, CLK_VCE_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_VCE_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_VCE_INIT_CTRL_REG_ADDR, CLK_VCE_INIT_SW_CLK_OSC_DATA, CLK_VCE_INIT_SW_SHIFT, CLK_VCE_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_VCE_INIT_SOURCE_CLK_VCE_600_ 	itg_set_reg(CLK_VCE_INIT_CTRL_REG_ADDR, CLK_VCE_INIT_SW_CLK_VCE_600_DATA, CLK_VCE_INIT_SW_SHIFT, CLK_VCE_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_VCE_INIT_ 		itg_get_reg(CLK_VCE_INIT_CTRL_REG_ADDR, CLK_VCE_INIT_SW_SHIFT, CLK_VCE_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_VCE_INIT_(x) 		itg_set_reg(CLK_VCE_INIT_CTRL_REG_ADDR, x, CLK_VCE_INIT_SW_SHIFT, CLK_VCE_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_VCE_100_(div) 			itg_set_reg(CLK_VCE_100_CTRL_REG_ADDR, div, CLK_VCE_100_DIV_SHIFT, CLK_VCE_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VCE_100_ 		itg_get_reg(CLK_VCE_100_CTRL_REG_ADDR, CLK_VCE_100_DIV_SHIFT, CLK_VCE_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_VCE_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_VCE_TARG_CTRL_REG_ADDR, CLK_VCE_TARG_SW_CLK_OSC_DATA, CLK_VCE_TARG_SW_SHIFT, CLK_VCE_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_VCE_TARG_SOURCE_CLK_VCE_100_ 	itg_set_reg(CLK_VCE_TARG_CTRL_REG_ADDR, CLK_VCE_TARG_SW_CLK_VCE_100_DATA, CLK_VCE_TARG_SW_SHIFT, CLK_VCE_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_VCE_TARG_ 		itg_get_reg(CLK_VCE_TARG_CTRL_REG_ADDR, CLK_VCE_TARG_SW_SHIFT, CLK_VCE_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_VCE_TARG_(x) 		itg_set_reg(CLK_VCE_TARG_CTRL_REG_ADDR, x, CLK_VCE_TARG_SW_SHIFT, CLK_VCE_TARG_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER2_600_(div) 			itg_set_reg(CLK_BMCPER2_600_CTRL_REG_ADDR, div, CLK_BMCPER2_600_DIV_SHIFT, CLK_BMCPER2_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER2_600_ 		itg_get_reg(CLK_BMCPER2_600_CTRL_REG_ADDR, CLK_BMCPER2_600_DIV_SHIFT, CLK_BMCPER2_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER2_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER2_INIT_CTRL_REG_ADDR, CLK_BMCPER2_INIT_SW_CLK_OSC_DATA, CLK_BMCPER2_INIT_SW_SHIFT, CLK_BMCPER2_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER2_INIT_SOURCE_CLK_BMCPER2_600_ 	itg_set_reg(CLK_BMCPER2_INIT_CTRL_REG_ADDR, CLK_BMCPER2_INIT_SW_CLK_BMCPER2_600_DATA, CLK_BMCPER2_INIT_SW_SHIFT, CLK_BMCPER2_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER2_INIT_ 		itg_get_reg(CLK_BMCPER2_INIT_CTRL_REG_ADDR, CLK_BMCPER2_INIT_SW_SHIFT, CLK_BMCPER2_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER2_INIT_(x) 		itg_set_reg(CLK_BMCPER2_INIT_CTRL_REG_ADDR, x, CLK_BMCPER2_INIT_SW_SHIFT, CLK_BMCPER2_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER2_100_(div) 			itg_set_reg(CLK_BMCPER2_100_CTRL_REG_ADDR, div, CLK_BMCPER2_100_DIV_SHIFT, CLK_BMCPER2_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER2_100_ 		itg_get_reg(CLK_BMCPER2_100_CTRL_REG_ADDR, CLK_BMCPER2_100_DIV_SHIFT, CLK_BMCPER2_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER2_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER2_TARG_CTRL_REG_ADDR, CLK_BMCPER2_TARG_SW_CLK_OSC_DATA, CLK_BMCPER2_TARG_SW_SHIFT, CLK_BMCPER2_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER2_TARG_SOURCE_CLK_BMCPER2_100_ 	itg_set_reg(CLK_BMCPER2_TARG_CTRL_REG_ADDR, CLK_BMCPER2_TARG_SW_CLK_BMCPER2_100_DATA, CLK_BMCPER2_TARG_SW_SHIFT, CLK_BMCPER2_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER2_TARG_ 		itg_get_reg(CLK_BMCPER2_TARG_CTRL_REG_ADDR, CLK_BMCPER2_TARG_SW_SHIFT, CLK_BMCPER2_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER2_TARG_(x) 		itg_set_reg(CLK_BMCPER2_TARG_CTRL_REG_ADDR, x, CLK_BMCPER2_TARG_SW_SHIFT, CLK_BMCPER2_TARG_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER2_400_(div) 			itg_set_reg(CLK_BMCPER2_400_CTRL_REG_ADDR, div, CLK_BMCPER2_400_DIV_SHIFT, CLK_BMCPER2_400_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER2_400_ 		itg_get_reg(CLK_BMCPER2_400_CTRL_REG_ADDR, CLK_BMCPER2_400_DIV_SHIFT, CLK_BMCPER2_400_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER2_400_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER2_400_OSC_CTRL_REG_ADDR, CLK_BMCPER2_400_OSC_SW_CLK_OSC_DATA, CLK_BMCPER2_400_OSC_SW_SHIFT, CLK_BMCPER2_400_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER2_400_OSC_SOURCE_CLK_BMCPER2_400_ 	itg_set_reg(CLK_BMCPER2_400_OSC_CTRL_REG_ADDR, CLK_BMCPER2_400_OSC_SW_CLK_BMCPER2_400_DATA, CLK_BMCPER2_400_OSC_SW_SHIFT, CLK_BMCPER2_400_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER2_400_OSC_ 		itg_get_reg(CLK_BMCPER2_400_OSC_CTRL_REG_ADDR, CLK_BMCPER2_400_OSC_SW_SHIFT, CLK_BMCPER2_400_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER2_400_OSC_(x) 		itg_set_reg(CLK_BMCPER2_400_OSC_CTRL_REG_ADDR, x, CLK_BMCPER2_400_OSC_SW_SHIFT, CLK_BMCPER2_400_OSC_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER2_125_(div) 			itg_set_reg(CLK_BMCPER2_125_CTRL_REG_ADDR, div, CLK_BMCPER2_125_DIV_SHIFT, CLK_BMCPER2_125_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER2_125_ 		itg_get_reg(CLK_BMCPER2_125_CTRL_REG_ADDR, CLK_BMCPER2_125_DIV_SHIFT, CLK_BMCPER2_125_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER2_125_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER2_125_OSC_CTRL_REG_ADDR, CLK_BMCPER2_125_OSC_SW_CLK_OSC_DATA, CLK_BMCPER2_125_OSC_SW_SHIFT, CLK_BMCPER2_125_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER2_125_OSC_SOURCE_CLK_BMCPER2_125_ 	itg_set_reg(CLK_BMCPER2_125_OSC_CTRL_REG_ADDR, CLK_BMCPER2_125_OSC_SW_CLK_BMCPER2_125_DATA, CLK_BMCPER2_125_OSC_SW_SHIFT, CLK_BMCPER2_125_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER2_125_OSC_ 		itg_get_reg(CLK_BMCPER2_125_OSC_CTRL_REG_ADDR, CLK_BMCPER2_125_OSC_SW_SHIFT, CLK_BMCPER2_125_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER2_125_OSC_(x) 		itg_set_reg(CLK_BMCPER2_125_OSC_CTRL_REG_ADDR, x, CLK_BMCPER2_125_OSC_SW_SHIFT, CLK_BMCPER2_125_OSC_SW_MASK)
#define _DIVIDE_CLOCK_CLK_NCNOC1_600_(div) 			itg_set_reg(CLK_NCNOC1_600_CTRL_REG_ADDR, div, CLK_NCNOC1_600_DIV_SHIFT, CLK_NCNOC1_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_NCNOC1_600_ 		itg_get_reg(CLK_NCNOC1_600_CTRL_REG_ADDR, CLK_NCNOC1_600_DIV_SHIFT, CLK_NCNOC1_600_DIV_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS1_600_(div) 			itg_set_reg(CLK_HOSTSS1_600_CTRL_REG_ADDR, div, CLK_HOSTSS1_600_DIV_SHIFT, CLK_HOSTSS1_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS1_600_ 		itg_get_reg(CLK_HOSTSS1_600_CTRL_REG_ADDR, CLK_HOSTSS1_600_DIV_SHIFT, CLK_HOSTSS1_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS1_DATA_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTSS1_DATA_CTRL_REG_ADDR, CLK_HOSTSS1_DATA_SW_CLK_OSC_DATA, CLK_HOSTSS1_DATA_SW_SHIFT, CLK_HOSTSS1_DATA_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS1_DATA_SOURCE_CLK_HOSTSS1_600_ 	itg_set_reg(CLK_HOSTSS1_DATA_CTRL_REG_ADDR, CLK_HOSTSS1_DATA_SW_CLK_HOSTSS1_600_DATA, CLK_HOSTSS1_DATA_SW_SHIFT, CLK_HOSTSS1_DATA_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTSS1_DATA_ 		itg_get_reg(CLK_HOSTSS1_DATA_CTRL_REG_ADDR, CLK_HOSTSS1_DATA_SW_SHIFT, CLK_HOSTSS1_DATA_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTSS1_DATA_(x) 		itg_set_reg(CLK_HOSTSS1_DATA_CTRL_REG_ADDR, x, CLK_HOSTSS1_DATA_SW_SHIFT, CLK_HOSTSS1_DATA_SW_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS1_PHY_SCAN_400_(div) 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_400_CTRL_REG_ADDR, div, CLK_HOSTSS1_PHY_SCAN_400_DIV_SHIFT, CLK_HOSTSS1_PHY_SCAN_400_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS1_PHY_SCAN_400_ 		itg_get_reg(CLK_HOSTSS1_PHY_SCAN_400_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_400_DIV_SHIFT, CLK_HOSTSS1_PHY_SCAN_400_DIV_MASK)
#define _ENABLE_CLOCK_CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_ 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_ENABLE_DATA, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_ 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_DISABLE_DATA, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_ 		itg_get_reg(CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_(x) 		itg_set_reg(CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_CTRL_REG_ADDR, x, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_400_ICG_BUF_EN_MASK)
#define _DIVIDE_CLOCK_CLK_VOUT_600_(div) 			itg_set_reg(CLK_VOUT_600_CTRL_REG_ADDR, div, CLK_VOUT_600_DIV_SHIFT, CLK_VOUT_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VOUT_600_ 		itg_get_reg(CLK_VOUT_600_CTRL_REG_ADDR, CLK_VOUT_600_DIV_SHIFT, CLK_VOUT_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_VOUT_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_VOUT_INIT_CTRL_REG_ADDR, CLK_VOUT_INIT_SW_CLK_OSC_DATA, CLK_VOUT_INIT_SW_SHIFT, CLK_VOUT_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_VOUT_INIT_SOURCE_CLK_VOUT_600_ 	itg_set_reg(CLK_VOUT_INIT_CTRL_REG_ADDR, CLK_VOUT_INIT_SW_CLK_VOUT_600_DATA, CLK_VOUT_INIT_SW_SHIFT, CLK_VOUT_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_VOUT_INIT_ 		itg_get_reg(CLK_VOUT_INIT_CTRL_REG_ADDR, CLK_VOUT_INIT_SW_SHIFT, CLK_VOUT_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_VOUT_INIT_(x) 		itg_set_reg(CLK_VOUT_INIT_CTRL_REG_ADDR, x, CLK_VOUT_INIT_SW_SHIFT, CLK_VOUT_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_VOUT_AUX_(div) 			itg_set_reg(CLK_VOUT_AUX_CTRL_REG_ADDR, div, CLK_VOUT_AUX_DIV_SHIFT, CLK_VOUT_AUX_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VOUT_AUX_ 		itg_get_reg(CLK_VOUT_AUX_CTRL_REG_ADDR, CLK_VOUT_AUX_DIV_SHIFT, CLK_VOUT_AUX_DIV_MASK)
#define _DIVIDE_CLOCK_CLK_VOUT_SCAN_800_DFT_(div) 			itg_set_reg(CLK_VOUT_SCAN_800_DFT_CTRL_REG_ADDR, div, CLK_VOUT_SCAN_800_DFT_DIV_SHIFT, CLK_VOUT_SCAN_800_DFT_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VOUT_SCAN_800_DFT_ 		itg_get_reg(CLK_VOUT_SCAN_800_DFT_CTRL_REG_ADDR, CLK_VOUT_SCAN_800_DFT_DIV_SHIFT, CLK_VOUT_SCAN_800_DFT_DIV_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER3_600_(div) 			itg_set_reg(CLK_BMCPER3_600_CTRL_REG_ADDR, div, CLK_BMCPER3_600_DIV_SHIFT, CLK_BMCPER3_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER3_600_ 		itg_get_reg(CLK_BMCPER3_600_CTRL_REG_ADDR, CLK_BMCPER3_600_DIV_SHIFT, CLK_BMCPER3_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER3_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER3_INIT_CTRL_REG_ADDR, CLK_BMCPER3_INIT_SW_CLK_OSC_DATA, CLK_BMCPER3_INIT_SW_SHIFT, CLK_BMCPER3_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER3_INIT_SOURCE_CLK_BMCPER3_600_ 	itg_set_reg(CLK_BMCPER3_INIT_CTRL_REG_ADDR, CLK_BMCPER3_INIT_SW_CLK_BMCPER3_600_DATA, CLK_BMCPER3_INIT_SW_SHIFT, CLK_BMCPER3_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER3_INIT_ 		itg_get_reg(CLK_BMCPER3_INIT_CTRL_REG_ADDR, CLK_BMCPER3_INIT_SW_SHIFT, CLK_BMCPER3_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER3_INIT_(x) 		itg_set_reg(CLK_BMCPER3_INIT_CTRL_REG_ADDR, x, CLK_BMCPER3_INIT_SW_SHIFT, CLK_BMCPER3_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTUSB_600_(div) 			itg_set_reg(CLK_HOSTUSB_600_CTRL_REG_ADDR, div, CLK_HOSTUSB_600_DIV_SHIFT, CLK_HOSTUSB_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTUSB_600_ 		itg_get_reg(CLK_HOSTUSB_600_CTRL_REG_ADDR, CLK_HOSTUSB_600_DIV_SHIFT, CLK_HOSTUSB_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSB_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTUSB_INIT_CTRL_REG_ADDR, CLK_HOSTUSB_INIT_SW_CLK_OSC_DATA, CLK_HOSTUSB_INIT_SW_SHIFT, CLK_HOSTUSB_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSB_INIT_SOURCE_CLK_HOSTUSB_600_ 	itg_set_reg(CLK_HOSTUSB_INIT_CTRL_REG_ADDR, CLK_HOSTUSB_INIT_SW_CLK_HOSTUSB_600_DATA, CLK_HOSTUSB_INIT_SW_SHIFT, CLK_HOSTUSB_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTUSB_INIT_ 		itg_get_reg(CLK_HOSTUSB_INIT_CTRL_REG_ADDR, CLK_HOSTUSB_INIT_SW_SHIFT, CLK_HOSTUSB_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTUSB_INIT_(x) 		itg_set_reg(CLK_HOSTUSB_INIT_CTRL_REG_ADDR, x, CLK_HOSTUSB_INIT_SW_SHIFT, CLK_HOSTUSB_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTUSBCMN_480_(div) 			itg_set_reg(CLK_HOSTUSBCMN_480_CTRL_REG_ADDR, div, CLK_HOSTUSBCMN_480_DIV_SHIFT, CLK_HOSTUSBCMN_480_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTUSBCMN_480_ 		itg_get_reg(CLK_HOSTUSBCMN_480_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_DIV_SHIFT, CLK_HOSTUSBCMN_480_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSBCMN_480_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_OSC_SW_CLK_OSC_DATA, CLK_HOSTUSBCMN_480_OSC_SW_SHIFT, CLK_HOSTUSBCMN_480_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSBCMN_480_OSC_SOURCE_CLK_HOSTUSBCMN_480_ 	itg_set_reg(CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_OSC_SW_CLK_HOSTUSBCMN_480_DATA, CLK_HOSTUSBCMN_480_OSC_SW_SHIFT, CLK_HOSTUSBCMN_480_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTUSBCMN_480_OSC_ 		itg_get_reg(CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_OSC_SW_SHIFT, CLK_HOSTUSBCMN_480_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTUSBCMN_480_OSC_(x) 		itg_set_reg(CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR, x, CLK_HOSTUSBCMN_480_OSC_SW_SHIFT, CLK_HOSTUSBCMN_480_OSC_SW_MASK)
#define _DIVIDE_CLOCK_CLK_SEC_600_(div) 			itg_set_reg(CLK_SEC_600_CTRL_REG_ADDR, div, CLK_SEC_600_DIV_SHIFT, CLK_SEC_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_SEC_600_ 		itg_get_reg(CLK_SEC_600_CTRL_REG_ADDR, CLK_SEC_600_DIV_SHIFT, CLK_SEC_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_SEC_DATA_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_SEC_DATA_INIT_CTRL_REG_ADDR, CLK_SEC_DATA_INIT_SW_CLK_OSC_DATA, CLK_SEC_DATA_INIT_SW_SHIFT, CLK_SEC_DATA_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_SEC_DATA_INIT_SOURCE_CLK_SEC_600_ 	itg_set_reg(CLK_SEC_DATA_INIT_CTRL_REG_ADDR, CLK_SEC_DATA_INIT_SW_CLK_SEC_600_DATA, CLK_SEC_DATA_INIT_SW_SHIFT, CLK_SEC_DATA_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_SEC_DATA_INIT_ 		itg_get_reg(CLK_SEC_DATA_INIT_CTRL_REG_ADDR, CLK_SEC_DATA_INIT_SW_SHIFT, CLK_SEC_DATA_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_SEC_DATA_INIT_(x) 		itg_set_reg(CLK_SEC_DATA_INIT_CTRL_REG_ADDR, x, CLK_SEC_DATA_INIT_SW_SHIFT, CLK_SEC_DATA_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_600_(div) 			itg_set_reg(CLK_BMCPER1_600_CTRL_REG_ADDR, div, CLK_BMCPER1_600_DIV_SHIFT, CLK_BMCPER1_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_600_ 		itg_get_reg(CLK_BMCPER1_600_CTRL_REG_ADDR, CLK_BMCPER1_600_DIV_SHIFT, CLK_BMCPER1_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER1_INIT_CTRL_REG_ADDR, CLK_BMCPER1_INIT_SW_CLK_OSC_DATA, CLK_BMCPER1_INIT_SW_SHIFT, CLK_BMCPER1_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_INIT_SOURCE_CLK_BMCPER1_600_ 	itg_set_reg(CLK_BMCPER1_INIT_CTRL_REG_ADDR, CLK_BMCPER1_INIT_SW_CLK_BMCPER1_600_DATA, CLK_BMCPER1_INIT_SW_SHIFT, CLK_BMCPER1_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_INIT_ 		itg_get_reg(CLK_BMCPER1_INIT_CTRL_REG_ADDR, CLK_BMCPER1_INIT_SW_SHIFT, CLK_BMCPER1_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_INIT_(x) 		itg_set_reg(CLK_BMCPER1_INIT_CTRL_REG_ADDR, x, CLK_BMCPER1_INIT_SW_SHIFT, CLK_BMCPER1_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_400_(div) 			itg_set_reg(CLK_BMCPER1_400_CTRL_REG_ADDR, div, CLK_BMCPER1_400_DIV_SHIFT, CLK_BMCPER1_400_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_400_ 		itg_get_reg(CLK_BMCPER1_400_CTRL_REG_ADDR, CLK_BMCPER1_400_DIV_SHIFT, CLK_BMCPER1_400_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_400_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER1_400_OSC_CTRL_REG_ADDR, CLK_BMCPER1_400_OSC_SW_CLK_OSC_DATA, CLK_BMCPER1_400_OSC_SW_SHIFT, CLK_BMCPER1_400_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_400_OSC_SOURCE_CLK_BMCPER1_400_ 	itg_set_reg(CLK_BMCPER1_400_OSC_CTRL_REG_ADDR, CLK_BMCPER1_400_OSC_SW_CLK_BMCPER1_400_DATA, CLK_BMCPER1_400_OSC_SW_SHIFT, CLK_BMCPER1_400_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_400_OSC_ 		itg_get_reg(CLK_BMCPER1_400_OSC_CTRL_REG_ADDR, CLK_BMCPER1_400_OSC_SW_SHIFT, CLK_BMCPER1_400_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_400_OSC_(x) 		itg_set_reg(CLK_BMCPER1_400_OSC_CTRL_REG_ADDR, x, CLK_BMCPER1_400_OSC_SW_SHIFT, CLK_BMCPER1_400_OSC_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_800_(div) 			itg_set_reg(CLK_BMCPER1_800_CTRL_REG_ADDR, div, CLK_BMCPER1_800_DIV_SHIFT, CLK_BMCPER1_800_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_800_ 		itg_get_reg(CLK_BMCPER1_800_CTRL_REG_ADDR, CLK_BMCPER1_800_DIV_SHIFT, CLK_BMCPER1_800_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_800_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER1_800_OSC_CTRL_REG_ADDR, CLK_BMCPER1_800_OSC_SW_CLK_OSC_DATA, CLK_BMCPER1_800_OSC_SW_SHIFT, CLK_BMCPER1_800_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_800_OSC_SOURCE_CLK_BMCPER1_800_ 	itg_set_reg(CLK_BMCPER1_800_OSC_CTRL_REG_ADDR, CLK_BMCPER1_800_OSC_SW_CLK_BMCPER1_800_DATA, CLK_BMCPER1_800_OSC_SW_SHIFT, CLK_BMCPER1_800_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_800_OSC_ 		itg_get_reg(CLK_BMCPER1_800_OSC_CTRL_REG_ADDR, CLK_BMCPER1_800_OSC_SW_SHIFT, CLK_BMCPER1_800_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_800_OSC_(x) 		itg_set_reg(CLK_BMCPER1_800_OSC_CTRL_REG_ADDR, x, CLK_BMCPER1_800_OSC_SW_SHIFT, CLK_BMCPER1_800_OSC_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER0_600_(div) 			itg_set_reg(CLK_BMCPER0_600_CTRL_REG_ADDR, div, CLK_BMCPER0_600_DIV_SHIFT, CLK_BMCPER0_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER0_600_ 		itg_get_reg(CLK_BMCPER0_600_CTRL_REG_ADDR, CLK_BMCPER0_600_DIV_SHIFT, CLK_BMCPER0_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER0_INIT_CTRL_REG_ADDR, CLK_BMCPER0_INIT_SW_CLK_OSC_DATA, CLK_BMCPER0_INIT_SW_SHIFT, CLK_BMCPER0_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_INIT_SOURCE_CLK_BMCPER0_600_ 	itg_set_reg(CLK_BMCPER0_INIT_CTRL_REG_ADDR, CLK_BMCPER0_INIT_SW_CLK_BMCPER0_600_DATA, CLK_BMCPER0_INIT_SW_SHIFT, CLK_BMCPER0_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_INIT_ 		itg_get_reg(CLK_BMCPER0_INIT_CTRL_REG_ADDR, CLK_BMCPER0_INIT_SW_SHIFT, CLK_BMCPER0_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_INIT_(x) 		itg_set_reg(CLK_BMCPER0_INIT_CTRL_REG_ADDR, x, CLK_BMCPER0_INIT_SW_SHIFT, CLK_BMCPER0_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER0_400_(div) 			itg_set_reg(CLK_BMCPER0_400_CTRL_REG_ADDR, div, CLK_BMCPER0_400_DIV_SHIFT, CLK_BMCPER0_400_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER0_400_ 		itg_get_reg(CLK_BMCPER0_400_CTRL_REG_ADDR, CLK_BMCPER0_400_DIV_SHIFT, CLK_BMCPER0_400_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_400_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER0_400_OSC_CTRL_REG_ADDR, CLK_BMCPER0_400_OSC_SW_CLK_OSC_DATA, CLK_BMCPER0_400_OSC_SW_SHIFT, CLK_BMCPER0_400_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_400_OSC_SOURCE_CLK_BMCPER0_400_ 	itg_set_reg(CLK_BMCPER0_400_OSC_CTRL_REG_ADDR, CLK_BMCPER0_400_OSC_SW_CLK_BMCPER0_400_DATA, CLK_BMCPER0_400_OSC_SW_SHIFT, CLK_BMCPER0_400_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_400_OSC_ 		itg_get_reg(CLK_BMCPER0_400_OSC_CTRL_REG_ADDR, CLK_BMCPER0_400_OSC_SW_SHIFT, CLK_BMCPER0_400_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_400_OSC_(x) 		itg_set_reg(CLK_BMCPER0_400_OSC_CTRL_REG_ADDR, x, CLK_BMCPER0_400_OSC_SW_SHIFT, CLK_BMCPER0_400_OSC_SW_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER0_800_(div) 			itg_set_reg(CLK_BMCPER0_800_CTRL_REG_ADDR, div, CLK_BMCPER0_800_DIV_SHIFT, CLK_BMCPER0_800_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER0_800_ 		itg_get_reg(CLK_BMCPER0_800_CTRL_REG_ADDR, CLK_BMCPER0_800_DIV_SHIFT, CLK_BMCPER0_800_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_800_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER0_800_OSC_CTRL_REG_ADDR, CLK_BMCPER0_800_OSC_SW_CLK_OSC_DATA, CLK_BMCPER0_800_OSC_SW_SHIFT, CLK_BMCPER0_800_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_800_OSC_SOURCE_CLK_BMCPER0_800_ 	itg_set_reg(CLK_BMCPER0_800_OSC_CTRL_REG_ADDR, CLK_BMCPER0_800_OSC_SW_CLK_BMCPER0_800_DATA, CLK_BMCPER0_800_OSC_SW_SHIFT, CLK_BMCPER0_800_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_800_OSC_ 		itg_get_reg(CLK_BMCPER0_800_OSC_CTRL_REG_ADDR, CLK_BMCPER0_800_OSC_SW_SHIFT, CLK_BMCPER0_800_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_800_OSC_(x) 		itg_set_reg(CLK_BMCPER0_800_OSC_CTRL_REG_ADDR, x, CLK_BMCPER0_800_OSC_SW_SHIFT, CLK_BMCPER0_800_OSC_SW_MASK)
#define _DIVIDE_CLOCK_CLK_GPU0_600_(div) 			itg_set_reg(CLK_GPU0_600_CTRL_REG_ADDR, div, CLK_GPU0_600_DIV_SHIFT, CLK_GPU0_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_GPU0_600_ 		itg_get_reg(CLK_GPU0_600_CTRL_REG_ADDR, CLK_GPU0_600_DIV_SHIFT, CLK_GPU0_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_GPU0_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_GPU0_INIT_CTRL_REG_ADDR, CLK_GPU0_INIT_SW_CLK_OSC_DATA, CLK_GPU0_INIT_SW_SHIFT, CLK_GPU0_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_GPU0_INIT_SOURCE_CLK_GPU0_600_ 	itg_set_reg(CLK_GPU0_INIT_CTRL_REG_ADDR, CLK_GPU0_INIT_SW_CLK_GPU0_600_DATA, CLK_GPU0_INIT_SW_SHIFT, CLK_GPU0_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_GPU0_INIT_ 		itg_get_reg(CLK_GPU0_INIT_CTRL_REG_ADDR, CLK_GPU0_INIT_SW_SHIFT, CLK_GPU0_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_GPU0_INIT_(x) 		itg_set_reg(CLK_GPU0_INIT_CTRL_REG_ADDR, x, CLK_GPU0_INIT_SW_SHIFT, CLK_GPU0_INIT_SW_MASK)
#define _DIVIDE_CLOCK_CLK_GPU1_600_(div) 			itg_set_reg(CLK_GPU1_600_CTRL_REG_ADDR, div, CLK_GPU1_600_DIV_SHIFT, CLK_GPU1_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_GPU1_600_ 		itg_get_reg(CLK_GPU1_600_CTRL_REG_ADDR, CLK_GPU1_600_DIV_SHIFT, CLK_GPU1_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_GPU1_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_GPU1_INIT_CTRL_REG_ADDR, CLK_GPU1_INIT_SW_CLK_OSC_DATA, CLK_GPU1_INIT_SW_SHIFT, CLK_GPU1_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_GPU1_INIT_SOURCE_CLK_GPU1_600_ 	itg_set_reg(CLK_GPU1_INIT_CTRL_REG_ADDR, CLK_GPU1_INIT_SW_CLK_GPU1_600_DATA, CLK_GPU1_INIT_SW_SHIFT, CLK_GPU1_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_GPU1_INIT_ 		itg_get_reg(CLK_GPU1_INIT_CTRL_REG_ADDR, CLK_GPU1_INIT_SW_SHIFT, CLK_GPU1_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_GPU1_INIT_(x) 		itg_set_reg(CLK_GPU1_INIT_CTRL_REG_ADDR, x, CLK_GPU1_INIT_SW_SHIFT, CLK_GPU1_INIT_SW_MASK)



#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_SYS0_SYSCON_PRESETN_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0_SYSCON_PRESETN_SHIFT, RSTN_U0_SYS0_SYSCON_PRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_SYS0_SYSCON_PRESETN_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0_SYSCON_PRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_SYS0_SYSCON_PRESETN_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0_SYSCON_PRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_SHIFT, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR0_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_SYS0_IOMUX_PRESETN_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0_IOMUX_PRESETN_SHIFT, RSTN_U0_SYS0_IOMUX_PRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_SYS0_IOMUX_PRESETN_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0_IOMUX_PRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_SYS0_IOMUX_PRESETN_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0_IOMUX_PRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_SYS0H_IOMUX_PRESETN_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0H_IOMUX_PRESETN_SHIFT, RSTN_U0_SYS0H_IOMUX_PRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_SYS0H_IOMUX_PRESETN_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0H_IOMUX_PRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_SYS0H_IOMUX_PRESETN_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS0H_IOMUX_PRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_MAIN_RSTN_PCU_BMCCPU_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_BMCCPU_SHIFT, MAIN_RSTN_PCU_BMCCPU_MASK)
#define _ASSERT_RESET_RSTGEN_MAIN_RSTN_PCU_BMCCPU_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_BMCCPU_MASK)
#define _CLEAR_RESET_RSTGEN_MAIN_RSTN_PCU_BMCCPU_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_BMCCPU_MASK)
#define _READ_RESET_STATUS_RSTGEN_MAIN_RSTN_PCU_BMCPCIERP_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_BMCPCIERP_SHIFT, MAIN_RSTN_PCU_BMCPCIERP_MASK)
#define _ASSERT_RESET_RSTGEN_MAIN_RSTN_PCU_BMCPCIERP_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_BMCPCIERP_MASK)
#define _CLEAR_RESET_RSTGEN_MAIN_RSTN_PCU_BMCPCIERP_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_BMCPCIERP_MASK)
#define _READ_RESET_STATUS_RSTGEN_MAIN_RSTN_PCU_HOSTSS0_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_HOSTSS0_SHIFT, MAIN_RSTN_PCU_HOSTSS0_MASK)
#define _ASSERT_RESET_RSTGEN_MAIN_RSTN_PCU_HOSTSS0_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_HOSTSS0_MASK)
#define _CLEAR_RESET_RSTGEN_MAIN_RSTN_PCU_HOSTSS0_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_PCU_HOSTSS0_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_SHIFT, RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_RST_ADAPTOR_TIMEOUT_RSTN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_SHIFT, RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_MASK)
#define _ASSERT_RESET_RSTGEN_RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_MASK)
#define _CLEAR_RESET_RSTGEN_RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RST_U0_DEBUG_SUBSYS_RELEASE_UST_RST_UDB_IP_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_SHIFT, RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DEBUG_SUBSYS_RELEASE_TRNG_RST_N_MASK)
#define _READ_RESET_STATUS_RSTGEN_MAIN_RSTN_EC_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_EC_SHIFT, MAIN_RSTN_EC_MASK)
#define _ASSERT_RESET_RSTGEN_MAIN_RSTN_EC_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_EC_MASK)
#define _CLEAR_RESET_RSTGEN_MAIN_RSTN_EC_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_EC_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_SHIFT, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI1_RSTN_BUS_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_SHIFT, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI2_RSTN_BUS_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_SHIFT, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI3_RSTN_BUS_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_SHIFT, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI0_RSTN_BUS_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_SHIFT, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_AXI_RAS_RSTN_BUS_MASK)
#define _READ_RESET_STATUS_RSTGEN_RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_SHIFT, RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RST_U0_DOM_DDRSS_RSTN_DOM_DDRSS_DOM_DDRSS_UST_UDB_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_SHIFT, RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_BUS_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_SHIFT, RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCPCIERP_RSTN_DOM_BMCPCIERP_RSTN_CRG_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_ 	itg_get_reg(SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_SHIFT, RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_ 	itg_assert_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_ 	itg_clear_rst(SYS0_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS0_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_DOM_BMCCPUSS_RSTN_DOM_BMCCPUSS_RSTN_CORE_MASK)


#endif //_SYS0_CRG_MACRO_H_
