//RTL tag v0.5.1


#ifndef _SYS1_CRG_MACRO_H_
#define _SYS1_CRG_MACRO_H_

//#define SYS1_CRG_BASE_ADDR 0x0
#define CLK_APB_MAIN_SYS1_CTRL_REG_ADDR                              (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x0U)
#define CLK_APB_OSC_SYS1_CTRL_REG_ADDR                               (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x4U)
#define CLK_NCNOC1_600_CTRL_REG_ADDR                                 (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x8U)
#define CLK_NCNOC1_200_CTRL_REG_ADDR                                 (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0xCU)
#define CLK_U0_BCU_PCLK_CTRL_REG_ADDR                                (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x10U)
#define CLK_U0_NCNOC_SYSTOP_CLK_BCU_CTRL_REG_ADDR                    (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x14U)
#define CLK_U0_BCU_DFT_BISR_CLK_CTRL_REG_ADDR                        (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x18U)
#define CLK_HOSTSS1_100_CTRL_REG_ADDR                                (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x1CU)
#define CLK_HOSTSS1_CFG_CTRL_REG_ADDR                                (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x20U)
#define CLK_HOSTSS1_600_CTRL_REG_ADDR                                (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x24U)
#define CLK_HOSTSS1_DATA_CTRL_REG_ADDR                               (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x28U)
#define CLK_HOSTSS1_PHY_SCAN_200_CTRL_REG_ADDR                       (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x2CU)
#define CLK_HOSTSS1_PHY_SCAN_500_CTRL_REG_ADDR                       (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x30U)
#define CLK_HOSTSS1_REF_CML_CTRL_REG_ADDR                            (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x34U)
#define CLK_GPU0_600_CTRL_REG_ADDR                                   (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x38U)
#define CLK_GPU0_INIT_CTRL_REG_ADDR                                  (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x3CU)
#define CLK_GPU0_100_CTRL_REG_ADDR                                   (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x40U)
#define CLK_GPU0_TARG_CTRL_REG_ADDR                                  (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x44U)
#define CLK_GPU1_600_CTRL_REG_ADDR                                   (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x48U)
#define CLK_GPU1_INIT_CTRL_REG_ADDR                                  (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x4CU)
#define CLK_GPU1_100_CTRL_REG_ADDR                                   (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x50U)
#define CLK_GPU1_TARG_CTRL_REG_ADDR                                  (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x54U)
#define CLK_VOUT_600_CTRL_REG_ADDR                                   (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x58U)
#define CLK_VOUT_INIT_CTRL_REG_ADDR                                  (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x5CU)
#define CLK_VOUT_100_CTRL_REG_ADDR                                   (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x60U)
#define CLK_VOUT_TARG_CTRL_REG_ADDR                                  (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x64U)
#define CLK_VOUT_AUX_CTRL_REG_ADDR                                   (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x68U)
#define CLK_VOUT_SCAN_1000_CTRL_REG_ADDR                             (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x6CU)
#define CLK_VOUT_SCAN_800_CTRL_REG_ADDR                              (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x70U)
#define CLK_BMCPER3_600_CTRL_REG_ADDR                                (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x74U)
#define CLK_BMCPER3_INIT_CTRL_REG_ADDR                               (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x78U)
#define CLK_BMCPER3_100_CTRL_REG_ADDR                                (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x7CU)
#define CLK_BMCPER3_TARG_CTRL_REG_ADDR                               (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x80U)
#define CLK_BMCPER3_125_CTRL_REG_ADDR                                (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x84U)
#define CLK_BMCPER3_125_OSC_CTRL_REG_ADDR                            (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x88U)


#define MAIN_ICG_EN_BCU_CTRL_REG_ADDR                                (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x8CU)


#define SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR              (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x90U)

#define SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR              (U0_SYS1_CRG__ITG_BD_APBS__BASE_ADDR + 0x94U)


#define CLK_APB_MAIN_SYS1_DIV_SHIFT                                  0
#define CLK_APB_MAIN_SYS1_DIV_MASK                                   0xFU
#define CLK_APB_OSC_SYS1_SW_SHIFT                                    24
#define CLK_APB_OSC_SYS1_SW_MASK                                     0x1000000U
#define CLK_APB_OSC_SYS1_SW_CLK_OSC_DATA                             0
#define CLK_APB_OSC_SYS1_SW_CLK_APB_MAIN_SYS1_DATA                   1
#define CLK_NCNOC1_600_DIV_SHIFT                                     0
#define CLK_NCNOC1_600_DIV_MASK                                      0x7U
#define CLK_NCNOC1_200_DIV_SHIFT                                     0
#define CLK_NCNOC1_200_DIV_MASK                                      0x7U
#define CLK_U0_BCU_PCLK_ENABLE_DATA                                  1
#define CLK_U0_BCU_PCLK_DISABLE_DATA                                 0
#define CLK_U0_BCU_PCLK_EN_SHIFT                                     31
#define CLK_U0_BCU_PCLK_EN_MASK                                      0x80000000U
#define CLK_U0_NCNOC_SYSTOP_CLK_BCU_ENABLE_DATA                      1
#define CLK_U0_NCNOC_SYSTOP_CLK_BCU_DISABLE_DATA                     0
#define CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_SHIFT                         31
#define CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_MASK                          0x80000000U
#define CLK_U0_BCU_DFT_BISR_CLK_ENABLE_DATA                          1
#define CLK_U0_BCU_DFT_BISR_CLK_DISABLE_DATA                         0
#define CLK_U0_BCU_DFT_BISR_CLK_EN_SHIFT                             31
#define CLK_U0_BCU_DFT_BISR_CLK_EN_MASK                              0x80000000U
#define CLK_HOSTSS1_100_ENABLE_DATA                                  1
#define CLK_HOSTSS1_100_DISABLE_DATA                                 0
#define CLK_HOSTSS1_100_EN_SHIFT                                     31
#define CLK_HOSTSS1_100_EN_MASK                                      0x80000000U
#define CLK_HOSTSS1_100_DIV_SHIFT                                    0
#define CLK_HOSTSS1_100_DIV_MASK                                     0xFU
#define CLK_HOSTSS1_CFG_SW_SHIFT                                     24
#define CLK_HOSTSS1_CFG_SW_MASK                                      0x1000000U
#define CLK_HOSTSS1_CFG_SW_CLK_OSC_DATA                              0
#define CLK_HOSTSS1_CFG_SW_CLK_HOSTSS1_100_DATA                      1
#define CLK_HOSTSS1_600_ENABLE_DATA                                  1
#define CLK_HOSTSS1_600_DISABLE_DATA                                 0
#define CLK_HOSTSS1_600_EN_SHIFT                                     31
#define CLK_HOSTSS1_600_EN_MASK                                      0x80000000U
#define CLK_HOSTSS1_600_DIV_SHIFT                                    0
#define CLK_HOSTSS1_600_DIV_MASK                                     0x7U
#define CLK_HOSTSS1_DATA_SW_SHIFT                                    24
#define CLK_HOSTSS1_DATA_SW_MASK                                     0x1000000U
#define CLK_HOSTSS1_DATA_SW_CLK_OSC_DATA                             0
#define CLK_HOSTSS1_DATA_SW_CLK_HOSTSS1_600_DATA                     1
#define CLK_HOSTSS1_PHY_SCAN_200_ENABLE_DATA                         1
#define CLK_HOSTSS1_PHY_SCAN_200_DISABLE_DATA                        0
#define CLK_HOSTSS1_PHY_SCAN_200_EN_SHIFT                            31
#define CLK_HOSTSS1_PHY_SCAN_200_EN_MASK                             0x80000000U
#define CLK_HOSTSS1_PHY_SCAN_200_DIV_SHIFT                           0
#define CLK_HOSTSS1_PHY_SCAN_200_DIV_MASK                            0x7U
#define CLK_HOSTSS1_PHY_SCAN_500_ENABLE_DATA                         1
#define CLK_HOSTSS1_PHY_SCAN_500_DISABLE_DATA                        0
#define CLK_HOSTSS1_PHY_SCAN_500_EN_SHIFT                            31
#define CLK_HOSTSS1_PHY_SCAN_500_EN_MASK                             0x80000000U
#define CLK_HOSTSS1_PHY_SCAN_500_DIV_SHIFT                           0
#define CLK_HOSTSS1_PHY_SCAN_500_DIV_MASK                            0x3U
#define CLK_HOSTSS1_REF_CML_DIV_SHIFT                                0
#define CLK_HOSTSS1_REF_CML_DIV_MASK                                 0xFU
#define CLK_GPU0_600_ENABLE_DATA                                     1
#define CLK_GPU0_600_DISABLE_DATA                                    0
#define CLK_GPU0_600_EN_SHIFT                                        31
#define CLK_GPU0_600_EN_MASK                                         0x80000000U
#define CLK_GPU0_600_DIV_SHIFT                                       0
#define CLK_GPU0_600_DIV_MASK                                        0x7U
#define CLK_GPU0_INIT_SW_SHIFT                                       24
#define CLK_GPU0_INIT_SW_MASK                                        0x1000000U
#define CLK_GPU0_INIT_SW_CLK_OSC_DATA                                0
#define CLK_GPU0_INIT_SW_CLK_GPU0_600_DATA                           1
#define CLK_GPU0_100_ENABLE_DATA                                     1
#define CLK_GPU0_100_DISABLE_DATA                                    0
#define CLK_GPU0_100_EN_SHIFT                                        31
#define CLK_GPU0_100_EN_MASK                                         0x80000000U
#define CLK_GPU0_100_DIV_SHIFT                                       0
#define CLK_GPU0_100_DIV_MASK                                        0xFU
#define CLK_GPU0_TARG_SW_SHIFT                                       24
#define CLK_GPU0_TARG_SW_MASK                                        0x1000000U
#define CLK_GPU0_TARG_SW_CLK_OSC_DATA                                0
#define CLK_GPU0_TARG_SW_CLK_GPU0_100_DATA                           1
#define CLK_GPU1_600_ENABLE_DATA                                     1
#define CLK_GPU1_600_DISABLE_DATA                                    0
#define CLK_GPU1_600_EN_SHIFT                                        31
#define CLK_GPU1_600_EN_MASK                                         0x80000000U
#define CLK_GPU1_600_DIV_SHIFT                                       0
#define CLK_GPU1_600_DIV_MASK                                        0x7U
#define CLK_GPU1_INIT_SW_SHIFT                                       24
#define CLK_GPU1_INIT_SW_MASK                                        0x1000000U
#define CLK_GPU1_INIT_SW_CLK_OSC_DATA                                0
#define CLK_GPU1_INIT_SW_CLK_GPU1_600_DATA                           1
#define CLK_GPU1_100_ENABLE_DATA                                     1
#define CLK_GPU1_100_DISABLE_DATA                                    0
#define CLK_GPU1_100_EN_SHIFT                                        31
#define CLK_GPU1_100_EN_MASK                                         0x80000000U
#define CLK_GPU1_100_DIV_SHIFT                                       0
#define CLK_GPU1_100_DIV_MASK                                        0xFU
#define CLK_GPU1_TARG_SW_SHIFT                                       24
#define CLK_GPU1_TARG_SW_MASK                                        0x1000000U
#define CLK_GPU1_TARG_SW_CLK_OSC_DATA                                0
#define CLK_GPU1_TARG_SW_CLK_GPU1_100_DATA                           1
#define CLK_VOUT_600_ENABLE_DATA                                     1
#define CLK_VOUT_600_DISABLE_DATA                                    0
#define CLK_VOUT_600_EN_SHIFT                                        31
#define CLK_VOUT_600_EN_MASK                                         0x80000000U
#define CLK_VOUT_600_DIV_SHIFT                                       0
#define CLK_VOUT_600_DIV_MASK                                        0x7U
#define CLK_VOUT_INIT_SW_SHIFT                                       24
#define CLK_VOUT_INIT_SW_MASK                                        0x1000000U
#define CLK_VOUT_INIT_SW_CLK_OSC_DATA                                0
#define CLK_VOUT_INIT_SW_CLK_VOUT_600_DATA                           1
#define CLK_VOUT_100_ENABLE_DATA                                     1
#define CLK_VOUT_100_DISABLE_DATA                                    0
#define CLK_VOUT_100_EN_SHIFT                                        31
#define CLK_VOUT_100_EN_MASK                                         0x80000000U
#define CLK_VOUT_100_DIV_SHIFT                                       0
#define CLK_VOUT_100_DIV_MASK                                        0xFU
#define CLK_VOUT_TARG_SW_SHIFT                                       24
#define CLK_VOUT_TARG_SW_MASK                                        0x1000000U
#define CLK_VOUT_TARG_SW_CLK_OSC_DATA                                0
#define CLK_VOUT_TARG_SW_CLK_VOUT_100_DATA                           1
#define CLK_VOUT_AUX_DIV_SHIFT                                       0
#define CLK_VOUT_AUX_DIV_MASK                                        0xFFU
#define CLK_VOUT_SCAN_1000_ENABLE_DATA                               1
#define CLK_VOUT_SCAN_1000_DISABLE_DATA                              0
#define CLK_VOUT_SCAN_1000_EN_SHIFT                                  31
#define CLK_VOUT_SCAN_1000_EN_MASK                                   0x80000000U
#define CLK_VOUT_SCAN_800_ENABLE_DATA                                1
#define CLK_VOUT_SCAN_800_DISABLE_DATA                               0
#define CLK_VOUT_SCAN_800_EN_SHIFT                                   31
#define CLK_VOUT_SCAN_800_EN_MASK                                    0x80000000U
#define CLK_VOUT_SCAN_800_DIV_SHIFT                                  0
#define CLK_VOUT_SCAN_800_DIV_MASK                                   0x3U
#define CLK_BMCPER3_600_ENABLE_DATA                                  1
#define CLK_BMCPER3_600_DISABLE_DATA                                 0
#define CLK_BMCPER3_600_EN_SHIFT                                     31
#define CLK_BMCPER3_600_EN_MASK                                      0x80000000U
#define CLK_BMCPER3_600_DIV_SHIFT                                    0
#define CLK_BMCPER3_600_DIV_MASK                                     0x7U
#define CLK_BMCPER3_INIT_SW_SHIFT                                    24
#define CLK_BMCPER3_INIT_SW_MASK                                     0x1000000U
#define CLK_BMCPER3_INIT_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER3_INIT_SW_CLK_BMCPER3_600_DATA                     1
#define CLK_BMCPER3_100_ENABLE_DATA                                  1
#define CLK_BMCPER3_100_DISABLE_DATA                                 0
#define CLK_BMCPER3_100_EN_SHIFT                                     31
#define CLK_BMCPER3_100_EN_MASK                                      0x80000000U
#define CLK_BMCPER3_100_DIV_SHIFT                                    0
#define CLK_BMCPER3_100_DIV_MASK                                     0xFU
#define CLK_BMCPER3_TARG_SW_SHIFT                                    24
#define CLK_BMCPER3_TARG_SW_MASK                                     0x1000000U
#define CLK_BMCPER3_TARG_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER3_TARG_SW_CLK_BMCPER3_100_DATA                     1
#define CLK_BMCPER3_125_ENABLE_DATA                                  1
#define CLK_BMCPER3_125_DISABLE_DATA                                 0
#define CLK_BMCPER3_125_EN_SHIFT                                     31
#define CLK_BMCPER3_125_EN_MASK                                      0x80000000U
#define CLK_BMCPER3_125_DIV_SHIFT                                    0
#define CLK_BMCPER3_125_DIV_MASK                                     0xFU
#define CLK_BMCPER3_125_OSC_SW_SHIFT                                 24
#define CLK_BMCPER3_125_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER3_125_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER3_125_OSC_SW_CLK_BMCPER3_125_DATA                  1

#define MAIN_ICG_EN_BCU_ENABLE_DATA                                  1
#define MAIN_ICG_EN_BCU_DISABLE_DATA                                 0
#define MAIN_ICG_EN_BCU_EN_SHIFT                                     31
#define MAIN_ICG_EN_BCU_EN_MASK                                      0x80000000U



#define RSTN_U0_SYS1_SYSCON_PRESETN_SHIFT                            0
#define RSTN_U0_SYS1_SYSCON_PRESETN_MASK                             (0x1 << 0)
#define RSTN_U0_SYS1_SYSCON_PRESETN_ASSERT                           1
#define RSTN_U0_SYS1_SYSCON_PRESETN_CLEAR                            0
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_SHIFT                         1
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_MASK                          (0x1 << 1)
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_ASSERT                        1
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_CLEAR                         0
#define MAIN_RSTN_SYS1_IOMUX_SHIFT                                   2
#define MAIN_RSTN_SYS1_IOMUX_MASK                                    (0x1 << 2)
#define MAIN_RSTN_SYS1_IOMUX_ASSERT                                  1
#define MAIN_RSTN_SYS1_IOMUX_CLEAR                                   0
#define RSTN_U0_BCU_PRST_SHIFT                                       3
#define RSTN_U0_BCU_PRST_MASK                                        (0x1 << 3)
#define RSTN_U0_BCU_PRST_ASSERT                                      1
#define RSTN_U0_BCU_PRST_CLEAR                                       0
#define RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_SHIFT                          4
#define RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_MASK                           (0x1 << 4)
#define RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_ASSERT                         1
#define RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_CLEAR                          0
#define RSTN_U0_BCU_DFT_BISR_RST_SHIFT                               5
#define RSTN_U0_BCU_DFT_BISR_RST_MASK                                (0x1 << 5)
#define RSTN_U0_BCU_DFT_BISR_RST_ASSERT                              1
#define RSTN_U0_BCU_DFT_BISR_RST_CLEAR                               0
#define RSTN_U0_PCU_CORE_RST_SHIFT                                   6
#define RSTN_U0_PCU_CORE_RST_MASK                                    (0x1 << 6)
#define RSTN_U0_PCU_CORE_RST_ASSERT                                  1
#define RSTN_U0_PCU_CORE_RST_CLEAR                                   0
#define RSTN_U0_PCU_APB_RST_SHIFT                                    7
#define RSTN_U0_PCU_APB_RST_MASK                                     (0x1 << 7)
#define RSTN_U0_PCU_APB_RST_ASSERT                                   1
#define RSTN_U0_PCU_APB_RST_CLEAR                                    0
#define RSTN_U1_PCU_CORE_RST_SHIFT                                   8
#define RSTN_U1_PCU_CORE_RST_MASK                                    (0x1 << 8)
#define RSTN_U1_PCU_CORE_RST_ASSERT                                  1
#define RSTN_U1_PCU_CORE_RST_CLEAR                                   0
#define RSTN_U1_PCU_APB_RST_SHIFT                                    9
#define RSTN_U1_PCU_APB_RST_MASK                                     (0x1 << 9)
#define RSTN_U1_PCU_APB_RST_ASSERT                                   1
#define RSTN_U1_PCU_APB_RST_CLEAR                                    0
#define RSTN_U2_PCU_CORE_RST_SHIFT                                   10
#define RSTN_U2_PCU_CORE_RST_MASK                                    (0x1 << 10)
#define RSTN_U2_PCU_CORE_RST_ASSERT                                  1
#define RSTN_U2_PCU_CORE_RST_CLEAR                                   0
#define RSTN_U2_PCU_APB_RST_SHIFT                                    11
#define RSTN_U2_PCU_APB_RST_MASK                                     (0x1 << 11)
#define RSTN_U2_PCU_APB_RST_ASSERT                                   1
#define RSTN_U2_PCU_APB_RST_CLEAR                                    0
#define RSTN_U3_PCU_CORE_RST_SHIFT                                   12
#define RSTN_U3_PCU_CORE_RST_MASK                                    (0x1 << 12)
#define RSTN_U3_PCU_CORE_RST_ASSERT                                  1
#define RSTN_U3_PCU_CORE_RST_CLEAR                                   0
#define RSTN_U3_PCU_APB_RST_SHIFT                                    13
#define RSTN_U3_PCU_APB_RST_MASK                                     (0x1 << 13)
#define RSTN_U3_PCU_APB_RST_ASSERT                                   1
#define RSTN_U3_PCU_APB_RST_CLEAR                                    0
#define RSTN_U9_PCU_CORE_RST_SHIFT                                   14
#define RSTN_U9_PCU_CORE_RST_MASK                                    (0x1 << 14)
#define RSTN_U9_PCU_CORE_RST_ASSERT                                  1
#define RSTN_U9_PCU_CORE_RST_CLEAR                                   0
#define RSTN_U9_PCU_APB_RST_SHIFT                                    15
#define RSTN_U9_PCU_APB_RST_MASK                                     (0x1 << 15)
#define RSTN_U9_PCU_APB_RST_ASSERT                                   1
#define RSTN_U9_PCU_APB_RST_CLEAR                                    0

#define _DIVIDE_CLOCK_CLK_APB_MAIN_SYS1_(div) 			itg_set_reg(CLK_APB_MAIN_SYS1_CTRL_REG_ADDR, div, CLK_APB_MAIN_SYS1_DIV_SHIFT, CLK_APB_MAIN_SYS1_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_APB_MAIN_SYS1_ 		itg_get_reg(CLK_APB_MAIN_SYS1_CTRL_REG_ADDR, CLK_APB_MAIN_SYS1_DIV_SHIFT, CLK_APB_MAIN_SYS1_DIV_MASK)
#define _SWITCH_CLOCK_CLK_APB_OSC_SYS1_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_APB_OSC_SYS1_CTRL_REG_ADDR, CLK_APB_OSC_SYS1_SW_CLK_OSC_DATA, CLK_APB_OSC_SYS1_SW_SHIFT, CLK_APB_OSC_SYS1_SW_MASK)
#define _SWITCH_CLOCK_CLK_APB_OSC_SYS1_SOURCE_CLK_APB_MAIN_SYS1_ 	itg_set_reg(CLK_APB_OSC_SYS1_CTRL_REG_ADDR, CLK_APB_OSC_SYS1_SW_CLK_APB_MAIN_SYS1_DATA, CLK_APB_OSC_SYS1_SW_SHIFT, CLK_APB_OSC_SYS1_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_APB_OSC_SYS1_ 		itg_get_reg(CLK_APB_OSC_SYS1_CTRL_REG_ADDR, CLK_APB_OSC_SYS1_SW_SHIFT, CLK_APB_OSC_SYS1_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_APB_OSC_SYS1_(x) 		itg_set_reg(CLK_APB_OSC_SYS1_CTRL_REG_ADDR, x, CLK_APB_OSC_SYS1_SW_SHIFT, CLK_APB_OSC_SYS1_SW_MASK)
#define _DIVIDE_CLOCK_CLK_NCNOC1_600_(div) 			itg_set_reg(CLK_NCNOC1_600_CTRL_REG_ADDR, div, CLK_NCNOC1_600_DIV_SHIFT, CLK_NCNOC1_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_NCNOC1_600_ 		itg_get_reg(CLK_NCNOC1_600_CTRL_REG_ADDR, CLK_NCNOC1_600_DIV_SHIFT, CLK_NCNOC1_600_DIV_MASK)
#define _DIVIDE_CLOCK_CLK_NCNOC1_200_(div) 			itg_set_reg(CLK_NCNOC1_200_CTRL_REG_ADDR, div, CLK_NCNOC1_200_DIV_SHIFT, CLK_NCNOC1_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_NCNOC1_200_ 		itg_get_reg(CLK_NCNOC1_200_CTRL_REG_ADDR, CLK_NCNOC1_200_DIV_SHIFT, CLK_NCNOC1_200_DIV_MASK)
#define _ENABLE_CLOCK_CLK_U0_BCU_PCLK_ 			itg_set_reg(CLK_U0_BCU_PCLK_CTRL_REG_ADDR, CLK_U0_BCU_PCLK_ENABLE_DATA, CLK_U0_BCU_PCLK_EN_SHIFT, CLK_U0_BCU_PCLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_BCU_PCLK_ 			itg_set_reg(CLK_U0_BCU_PCLK_CTRL_REG_ADDR, CLK_U0_BCU_PCLK_DISABLE_DATA, CLK_U0_BCU_PCLK_EN_SHIFT, CLK_U0_BCU_PCLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_BCU_PCLK_ 		itg_get_reg(CLK_U0_BCU_PCLK_CTRL_REG_ADDR, CLK_U0_BCU_PCLK_EN_SHIFT, CLK_U0_BCU_PCLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_BCU_PCLK_(x) 		itg_set_reg(CLK_U0_BCU_PCLK_CTRL_REG_ADDR, x, CLK_U0_BCU_PCLK_EN_SHIFT, CLK_U0_BCU_PCLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_NCNOC_SYSTOP_CLK_BCU_ 			itg_set_reg(CLK_U0_NCNOC_SYSTOP_CLK_BCU_CTRL_REG_ADDR, CLK_U0_NCNOC_SYSTOP_CLK_BCU_ENABLE_DATA, CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_SHIFT, CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_NCNOC_SYSTOP_CLK_BCU_ 			itg_set_reg(CLK_U0_NCNOC_SYSTOP_CLK_BCU_CTRL_REG_ADDR, CLK_U0_NCNOC_SYSTOP_CLK_BCU_DISABLE_DATA, CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_SHIFT, CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_NCNOC_SYSTOP_CLK_BCU_ 		itg_get_reg(CLK_U0_NCNOC_SYSTOP_CLK_BCU_CTRL_REG_ADDR, CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_SHIFT, CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_NCNOC_SYSTOP_CLK_BCU_(x) 		itg_set_reg(CLK_U0_NCNOC_SYSTOP_CLK_BCU_CTRL_REG_ADDR, x, CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_SHIFT, CLK_U0_NCNOC_SYSTOP_CLK_BCU_EN_MASK)
#define _ENABLE_CLOCK_CLK_U0_BCU_DFT_BISR_CLK_ 			itg_set_reg(CLK_U0_BCU_DFT_BISR_CLK_CTRL_REG_ADDR, CLK_U0_BCU_DFT_BISR_CLK_ENABLE_DATA, CLK_U0_BCU_DFT_BISR_CLK_EN_SHIFT, CLK_U0_BCU_DFT_BISR_CLK_EN_MASK)
#define _DISABLE_CLOCK_CLK_U0_BCU_DFT_BISR_CLK_ 			itg_set_reg(CLK_U0_BCU_DFT_BISR_CLK_CTRL_REG_ADDR, CLK_U0_BCU_DFT_BISR_CLK_DISABLE_DATA, CLK_U0_BCU_DFT_BISR_CLK_EN_SHIFT, CLK_U0_BCU_DFT_BISR_CLK_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_U0_BCU_DFT_BISR_CLK_ 		itg_get_reg(CLK_U0_BCU_DFT_BISR_CLK_CTRL_REG_ADDR, CLK_U0_BCU_DFT_BISR_CLK_EN_SHIFT, CLK_U0_BCU_DFT_BISR_CLK_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_U0_BCU_DFT_BISR_CLK_(x) 		itg_set_reg(CLK_U0_BCU_DFT_BISR_CLK_CTRL_REG_ADDR, x, CLK_U0_BCU_DFT_BISR_CLK_EN_SHIFT, CLK_U0_BCU_DFT_BISR_CLK_EN_MASK)
#define _ENABLE_CLOCK_CLK_HOSTSS1_100_ 			itg_set_reg(CLK_HOSTSS1_100_CTRL_REG_ADDR, CLK_HOSTSS1_100_ENABLE_DATA, CLK_HOSTSS1_100_EN_SHIFT, CLK_HOSTSS1_100_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTSS1_100_ 			itg_set_reg(CLK_HOSTSS1_100_CTRL_REG_ADDR, CLK_HOSTSS1_100_DISABLE_DATA, CLK_HOSTSS1_100_EN_SHIFT, CLK_HOSTSS1_100_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_100_ 		itg_get_reg(CLK_HOSTSS1_100_CTRL_REG_ADDR, CLK_HOSTSS1_100_EN_SHIFT, CLK_HOSTSS1_100_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_100_(x) 		itg_set_reg(CLK_HOSTSS1_100_CTRL_REG_ADDR, x, CLK_HOSTSS1_100_EN_SHIFT, CLK_HOSTSS1_100_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS1_100_(div) 			itg_set_reg(CLK_HOSTSS1_100_CTRL_REG_ADDR, div, CLK_HOSTSS1_100_DIV_SHIFT, CLK_HOSTSS1_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS1_100_ 		itg_get_reg(CLK_HOSTSS1_100_CTRL_REG_ADDR, CLK_HOSTSS1_100_DIV_SHIFT, CLK_HOSTSS1_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS1_CFG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTSS1_CFG_CTRL_REG_ADDR, CLK_HOSTSS1_CFG_SW_CLK_OSC_DATA, CLK_HOSTSS1_CFG_SW_SHIFT, CLK_HOSTSS1_CFG_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS1_CFG_SOURCE_CLK_HOSTSS1_100_ 	itg_set_reg(CLK_HOSTSS1_CFG_CTRL_REG_ADDR, CLK_HOSTSS1_CFG_SW_CLK_HOSTSS1_100_DATA, CLK_HOSTSS1_CFG_SW_SHIFT, CLK_HOSTSS1_CFG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTSS1_CFG_ 		itg_get_reg(CLK_HOSTSS1_CFG_CTRL_REG_ADDR, CLK_HOSTSS1_CFG_SW_SHIFT, CLK_HOSTSS1_CFG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTSS1_CFG_(x) 		itg_set_reg(CLK_HOSTSS1_CFG_CTRL_REG_ADDR, x, CLK_HOSTSS1_CFG_SW_SHIFT, CLK_HOSTSS1_CFG_SW_MASK)
#define _ENABLE_CLOCK_CLK_HOSTSS1_600_ 			itg_set_reg(CLK_HOSTSS1_600_CTRL_REG_ADDR, CLK_HOSTSS1_600_ENABLE_DATA, CLK_HOSTSS1_600_EN_SHIFT, CLK_HOSTSS1_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTSS1_600_ 			itg_set_reg(CLK_HOSTSS1_600_CTRL_REG_ADDR, CLK_HOSTSS1_600_DISABLE_DATA, CLK_HOSTSS1_600_EN_SHIFT, CLK_HOSTSS1_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_600_ 		itg_get_reg(CLK_HOSTSS1_600_CTRL_REG_ADDR, CLK_HOSTSS1_600_EN_SHIFT, CLK_HOSTSS1_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_600_(x) 		itg_set_reg(CLK_HOSTSS1_600_CTRL_REG_ADDR, x, CLK_HOSTSS1_600_EN_SHIFT, CLK_HOSTSS1_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS1_600_(div) 			itg_set_reg(CLK_HOSTSS1_600_CTRL_REG_ADDR, div, CLK_HOSTSS1_600_DIV_SHIFT, CLK_HOSTSS1_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS1_600_ 		itg_get_reg(CLK_HOSTSS1_600_CTRL_REG_ADDR, CLK_HOSTSS1_600_DIV_SHIFT, CLK_HOSTSS1_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS1_DATA_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTSS1_DATA_CTRL_REG_ADDR, CLK_HOSTSS1_DATA_SW_CLK_OSC_DATA, CLK_HOSTSS1_DATA_SW_SHIFT, CLK_HOSTSS1_DATA_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTSS1_DATA_SOURCE_CLK_HOSTSS1_600_ 	itg_set_reg(CLK_HOSTSS1_DATA_CTRL_REG_ADDR, CLK_HOSTSS1_DATA_SW_CLK_HOSTSS1_600_DATA, CLK_HOSTSS1_DATA_SW_SHIFT, CLK_HOSTSS1_DATA_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTSS1_DATA_ 		itg_get_reg(CLK_HOSTSS1_DATA_CTRL_REG_ADDR, CLK_HOSTSS1_DATA_SW_SHIFT, CLK_HOSTSS1_DATA_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTSS1_DATA_(x) 		itg_set_reg(CLK_HOSTSS1_DATA_CTRL_REG_ADDR, x, CLK_HOSTSS1_DATA_SW_SHIFT, CLK_HOSTSS1_DATA_SW_MASK)
#define _ENABLE_CLOCK_CLK_HOSTSS1_PHY_SCAN_200_ 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_200_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_200_ENABLE_DATA, CLK_HOSTSS1_PHY_SCAN_200_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_200_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTSS1_PHY_SCAN_200_ 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_200_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_200_DISABLE_DATA, CLK_HOSTSS1_PHY_SCAN_200_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_200_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_PHY_SCAN_200_ 		itg_get_reg(CLK_HOSTSS1_PHY_SCAN_200_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_200_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_200_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_PHY_SCAN_200_(x) 		itg_set_reg(CLK_HOSTSS1_PHY_SCAN_200_CTRL_REG_ADDR, x, CLK_HOSTSS1_PHY_SCAN_200_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_200_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS1_PHY_SCAN_200_(div) 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_200_CTRL_REG_ADDR, div, CLK_HOSTSS1_PHY_SCAN_200_DIV_SHIFT, CLK_HOSTSS1_PHY_SCAN_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS1_PHY_SCAN_200_ 		itg_get_reg(CLK_HOSTSS1_PHY_SCAN_200_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_200_DIV_SHIFT, CLK_HOSTSS1_PHY_SCAN_200_DIV_MASK)
#define _ENABLE_CLOCK_CLK_HOSTSS1_PHY_SCAN_500_ 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_500_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_500_ENABLE_DATA, CLK_HOSTSS1_PHY_SCAN_500_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_500_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTSS1_PHY_SCAN_500_ 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_500_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_500_DISABLE_DATA, CLK_HOSTSS1_PHY_SCAN_500_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_500_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_PHY_SCAN_500_ 		itg_get_reg(CLK_HOSTSS1_PHY_SCAN_500_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_500_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_500_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTSS1_PHY_SCAN_500_(x) 		itg_set_reg(CLK_HOSTSS1_PHY_SCAN_500_CTRL_REG_ADDR, x, CLK_HOSTSS1_PHY_SCAN_500_EN_SHIFT, CLK_HOSTSS1_PHY_SCAN_500_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS1_PHY_SCAN_500_(div) 			itg_set_reg(CLK_HOSTSS1_PHY_SCAN_500_CTRL_REG_ADDR, div, CLK_HOSTSS1_PHY_SCAN_500_DIV_SHIFT, CLK_HOSTSS1_PHY_SCAN_500_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS1_PHY_SCAN_500_ 		itg_get_reg(CLK_HOSTSS1_PHY_SCAN_500_CTRL_REG_ADDR, CLK_HOSTSS1_PHY_SCAN_500_DIV_SHIFT, CLK_HOSTSS1_PHY_SCAN_500_DIV_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTSS1_REF_CML_(div) 			itg_set_reg(CLK_HOSTSS1_REF_CML_CTRL_REG_ADDR, div, CLK_HOSTSS1_REF_CML_DIV_SHIFT, CLK_HOSTSS1_REF_CML_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTSS1_REF_CML_ 		itg_get_reg(CLK_HOSTSS1_REF_CML_CTRL_REG_ADDR, CLK_HOSTSS1_REF_CML_DIV_SHIFT, CLK_HOSTSS1_REF_CML_DIV_MASK)
#define _ENABLE_CLOCK_CLK_GPU0_600_ 			itg_set_reg(CLK_GPU0_600_CTRL_REG_ADDR, CLK_GPU0_600_ENABLE_DATA, CLK_GPU0_600_EN_SHIFT, CLK_GPU0_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_GPU0_600_ 			itg_set_reg(CLK_GPU0_600_CTRL_REG_ADDR, CLK_GPU0_600_DISABLE_DATA, CLK_GPU0_600_EN_SHIFT, CLK_GPU0_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_GPU0_600_ 		itg_get_reg(CLK_GPU0_600_CTRL_REG_ADDR, CLK_GPU0_600_EN_SHIFT, CLK_GPU0_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_GPU0_600_(x) 		itg_set_reg(CLK_GPU0_600_CTRL_REG_ADDR, x, CLK_GPU0_600_EN_SHIFT, CLK_GPU0_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_GPU0_600_(div) 			itg_set_reg(CLK_GPU0_600_CTRL_REG_ADDR, div, CLK_GPU0_600_DIV_SHIFT, CLK_GPU0_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_GPU0_600_ 		itg_get_reg(CLK_GPU0_600_CTRL_REG_ADDR, CLK_GPU0_600_DIV_SHIFT, CLK_GPU0_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_GPU0_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_GPU0_INIT_CTRL_REG_ADDR, CLK_GPU0_INIT_SW_CLK_OSC_DATA, CLK_GPU0_INIT_SW_SHIFT, CLK_GPU0_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_GPU0_INIT_SOURCE_CLK_GPU0_600_ 	itg_set_reg(CLK_GPU0_INIT_CTRL_REG_ADDR, CLK_GPU0_INIT_SW_CLK_GPU0_600_DATA, CLK_GPU0_INIT_SW_SHIFT, CLK_GPU0_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_GPU0_INIT_ 		itg_get_reg(CLK_GPU0_INIT_CTRL_REG_ADDR, CLK_GPU0_INIT_SW_SHIFT, CLK_GPU0_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_GPU0_INIT_(x) 		itg_set_reg(CLK_GPU0_INIT_CTRL_REG_ADDR, x, CLK_GPU0_INIT_SW_SHIFT, CLK_GPU0_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_GPU0_100_ 			itg_set_reg(CLK_GPU0_100_CTRL_REG_ADDR, CLK_GPU0_100_ENABLE_DATA, CLK_GPU0_100_EN_SHIFT, CLK_GPU0_100_EN_MASK)
#define _DISABLE_CLOCK_CLK_GPU0_100_ 			itg_set_reg(CLK_GPU0_100_CTRL_REG_ADDR, CLK_GPU0_100_DISABLE_DATA, CLK_GPU0_100_EN_SHIFT, CLK_GPU0_100_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_GPU0_100_ 		itg_get_reg(CLK_GPU0_100_CTRL_REG_ADDR, CLK_GPU0_100_EN_SHIFT, CLK_GPU0_100_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_GPU0_100_(x) 		itg_set_reg(CLK_GPU0_100_CTRL_REG_ADDR, x, CLK_GPU0_100_EN_SHIFT, CLK_GPU0_100_EN_MASK)
#define _DIVIDE_CLOCK_CLK_GPU0_100_(div) 			itg_set_reg(CLK_GPU0_100_CTRL_REG_ADDR, div, CLK_GPU0_100_DIV_SHIFT, CLK_GPU0_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_GPU0_100_ 		itg_get_reg(CLK_GPU0_100_CTRL_REG_ADDR, CLK_GPU0_100_DIV_SHIFT, CLK_GPU0_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_GPU0_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_GPU0_TARG_CTRL_REG_ADDR, CLK_GPU0_TARG_SW_CLK_OSC_DATA, CLK_GPU0_TARG_SW_SHIFT, CLK_GPU0_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_GPU0_TARG_SOURCE_CLK_GPU0_100_ 	itg_set_reg(CLK_GPU0_TARG_CTRL_REG_ADDR, CLK_GPU0_TARG_SW_CLK_GPU0_100_DATA, CLK_GPU0_TARG_SW_SHIFT, CLK_GPU0_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_GPU0_TARG_ 		itg_get_reg(CLK_GPU0_TARG_CTRL_REG_ADDR, CLK_GPU0_TARG_SW_SHIFT, CLK_GPU0_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_GPU0_TARG_(x) 		itg_set_reg(CLK_GPU0_TARG_CTRL_REG_ADDR, x, CLK_GPU0_TARG_SW_SHIFT, CLK_GPU0_TARG_SW_MASK)
#define _ENABLE_CLOCK_CLK_GPU1_600_ 			itg_set_reg(CLK_GPU1_600_CTRL_REG_ADDR, CLK_GPU1_600_ENABLE_DATA, CLK_GPU1_600_EN_SHIFT, CLK_GPU1_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_GPU1_600_ 			itg_set_reg(CLK_GPU1_600_CTRL_REG_ADDR, CLK_GPU1_600_DISABLE_DATA, CLK_GPU1_600_EN_SHIFT, CLK_GPU1_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_GPU1_600_ 		itg_get_reg(CLK_GPU1_600_CTRL_REG_ADDR, CLK_GPU1_600_EN_SHIFT, CLK_GPU1_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_GPU1_600_(x) 		itg_set_reg(CLK_GPU1_600_CTRL_REG_ADDR, x, CLK_GPU1_600_EN_SHIFT, CLK_GPU1_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_GPU1_600_(div) 			itg_set_reg(CLK_GPU1_600_CTRL_REG_ADDR, div, CLK_GPU1_600_DIV_SHIFT, CLK_GPU1_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_GPU1_600_ 		itg_get_reg(CLK_GPU1_600_CTRL_REG_ADDR, CLK_GPU1_600_DIV_SHIFT, CLK_GPU1_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_GPU1_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_GPU1_INIT_CTRL_REG_ADDR, CLK_GPU1_INIT_SW_CLK_OSC_DATA, CLK_GPU1_INIT_SW_SHIFT, CLK_GPU1_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_GPU1_INIT_SOURCE_CLK_GPU1_600_ 	itg_set_reg(CLK_GPU1_INIT_CTRL_REG_ADDR, CLK_GPU1_INIT_SW_CLK_GPU1_600_DATA, CLK_GPU1_INIT_SW_SHIFT, CLK_GPU1_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_GPU1_INIT_ 		itg_get_reg(CLK_GPU1_INIT_CTRL_REG_ADDR, CLK_GPU1_INIT_SW_SHIFT, CLK_GPU1_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_GPU1_INIT_(x) 		itg_set_reg(CLK_GPU1_INIT_CTRL_REG_ADDR, x, CLK_GPU1_INIT_SW_SHIFT, CLK_GPU1_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_GPU1_100_ 			itg_set_reg(CLK_GPU1_100_CTRL_REG_ADDR, CLK_GPU1_100_ENABLE_DATA, CLK_GPU1_100_EN_SHIFT, CLK_GPU1_100_EN_MASK)
#define _DISABLE_CLOCK_CLK_GPU1_100_ 			itg_set_reg(CLK_GPU1_100_CTRL_REG_ADDR, CLK_GPU1_100_DISABLE_DATA, CLK_GPU1_100_EN_SHIFT, CLK_GPU1_100_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_GPU1_100_ 		itg_get_reg(CLK_GPU1_100_CTRL_REG_ADDR, CLK_GPU1_100_EN_SHIFT, CLK_GPU1_100_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_GPU1_100_(x) 		itg_set_reg(CLK_GPU1_100_CTRL_REG_ADDR, x, CLK_GPU1_100_EN_SHIFT, CLK_GPU1_100_EN_MASK)
#define _DIVIDE_CLOCK_CLK_GPU1_100_(div) 			itg_set_reg(CLK_GPU1_100_CTRL_REG_ADDR, div, CLK_GPU1_100_DIV_SHIFT, CLK_GPU1_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_GPU1_100_ 		itg_get_reg(CLK_GPU1_100_CTRL_REG_ADDR, CLK_GPU1_100_DIV_SHIFT, CLK_GPU1_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_GPU1_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_GPU1_TARG_CTRL_REG_ADDR, CLK_GPU1_TARG_SW_CLK_OSC_DATA, CLK_GPU1_TARG_SW_SHIFT, CLK_GPU1_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_GPU1_TARG_SOURCE_CLK_GPU1_100_ 	itg_set_reg(CLK_GPU1_TARG_CTRL_REG_ADDR, CLK_GPU1_TARG_SW_CLK_GPU1_100_DATA, CLK_GPU1_TARG_SW_SHIFT, CLK_GPU1_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_GPU1_TARG_ 		itg_get_reg(CLK_GPU1_TARG_CTRL_REG_ADDR, CLK_GPU1_TARG_SW_SHIFT, CLK_GPU1_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_GPU1_TARG_(x) 		itg_set_reg(CLK_GPU1_TARG_CTRL_REG_ADDR, x, CLK_GPU1_TARG_SW_SHIFT, CLK_GPU1_TARG_SW_MASK)
#define _ENABLE_CLOCK_CLK_VOUT_600_ 			itg_set_reg(CLK_VOUT_600_CTRL_REG_ADDR, CLK_VOUT_600_ENABLE_DATA, CLK_VOUT_600_EN_SHIFT, CLK_VOUT_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_VOUT_600_ 			itg_set_reg(CLK_VOUT_600_CTRL_REG_ADDR, CLK_VOUT_600_DISABLE_DATA, CLK_VOUT_600_EN_SHIFT, CLK_VOUT_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_VOUT_600_ 		itg_get_reg(CLK_VOUT_600_CTRL_REG_ADDR, CLK_VOUT_600_EN_SHIFT, CLK_VOUT_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_VOUT_600_(x) 		itg_set_reg(CLK_VOUT_600_CTRL_REG_ADDR, x, CLK_VOUT_600_EN_SHIFT, CLK_VOUT_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_VOUT_600_(div) 			itg_set_reg(CLK_VOUT_600_CTRL_REG_ADDR, div, CLK_VOUT_600_DIV_SHIFT, CLK_VOUT_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VOUT_600_ 		itg_get_reg(CLK_VOUT_600_CTRL_REG_ADDR, CLK_VOUT_600_DIV_SHIFT, CLK_VOUT_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_VOUT_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_VOUT_INIT_CTRL_REG_ADDR, CLK_VOUT_INIT_SW_CLK_OSC_DATA, CLK_VOUT_INIT_SW_SHIFT, CLK_VOUT_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_VOUT_INIT_SOURCE_CLK_VOUT_600_ 	itg_set_reg(CLK_VOUT_INIT_CTRL_REG_ADDR, CLK_VOUT_INIT_SW_CLK_VOUT_600_DATA, CLK_VOUT_INIT_SW_SHIFT, CLK_VOUT_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_VOUT_INIT_ 		itg_get_reg(CLK_VOUT_INIT_CTRL_REG_ADDR, CLK_VOUT_INIT_SW_SHIFT, CLK_VOUT_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_VOUT_INIT_(x) 		itg_set_reg(CLK_VOUT_INIT_CTRL_REG_ADDR, x, CLK_VOUT_INIT_SW_SHIFT, CLK_VOUT_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_VOUT_100_ 			itg_set_reg(CLK_VOUT_100_CTRL_REG_ADDR, CLK_VOUT_100_ENABLE_DATA, CLK_VOUT_100_EN_SHIFT, CLK_VOUT_100_EN_MASK)
#define _DISABLE_CLOCK_CLK_VOUT_100_ 			itg_set_reg(CLK_VOUT_100_CTRL_REG_ADDR, CLK_VOUT_100_DISABLE_DATA, CLK_VOUT_100_EN_SHIFT, CLK_VOUT_100_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_VOUT_100_ 		itg_get_reg(CLK_VOUT_100_CTRL_REG_ADDR, CLK_VOUT_100_EN_SHIFT, CLK_VOUT_100_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_VOUT_100_(x) 		itg_set_reg(CLK_VOUT_100_CTRL_REG_ADDR, x, CLK_VOUT_100_EN_SHIFT, CLK_VOUT_100_EN_MASK)
#define _DIVIDE_CLOCK_CLK_VOUT_100_(div) 			itg_set_reg(CLK_VOUT_100_CTRL_REG_ADDR, div, CLK_VOUT_100_DIV_SHIFT, CLK_VOUT_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VOUT_100_ 		itg_get_reg(CLK_VOUT_100_CTRL_REG_ADDR, CLK_VOUT_100_DIV_SHIFT, CLK_VOUT_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_VOUT_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_VOUT_TARG_CTRL_REG_ADDR, CLK_VOUT_TARG_SW_CLK_OSC_DATA, CLK_VOUT_TARG_SW_SHIFT, CLK_VOUT_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_VOUT_TARG_SOURCE_CLK_VOUT_100_ 	itg_set_reg(CLK_VOUT_TARG_CTRL_REG_ADDR, CLK_VOUT_TARG_SW_CLK_VOUT_100_DATA, CLK_VOUT_TARG_SW_SHIFT, CLK_VOUT_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_VOUT_TARG_ 		itg_get_reg(CLK_VOUT_TARG_CTRL_REG_ADDR, CLK_VOUT_TARG_SW_SHIFT, CLK_VOUT_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_VOUT_TARG_(x) 		itg_set_reg(CLK_VOUT_TARG_CTRL_REG_ADDR, x, CLK_VOUT_TARG_SW_SHIFT, CLK_VOUT_TARG_SW_MASK)
#define _DIVIDE_CLOCK_CLK_VOUT_AUX_(div) 			itg_set_reg(CLK_VOUT_AUX_CTRL_REG_ADDR, div, CLK_VOUT_AUX_DIV_SHIFT, CLK_VOUT_AUX_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VOUT_AUX_ 		itg_get_reg(CLK_VOUT_AUX_CTRL_REG_ADDR, CLK_VOUT_AUX_DIV_SHIFT, CLK_VOUT_AUX_DIV_MASK)
#define _ENABLE_CLOCK_CLK_VOUT_SCAN_1000_ 			itg_set_reg(CLK_VOUT_SCAN_1000_CTRL_REG_ADDR, CLK_VOUT_SCAN_1000_ENABLE_DATA, CLK_VOUT_SCAN_1000_EN_SHIFT, CLK_VOUT_SCAN_1000_EN_MASK)
#define _DISABLE_CLOCK_CLK_VOUT_SCAN_1000_ 			itg_set_reg(CLK_VOUT_SCAN_1000_CTRL_REG_ADDR, CLK_VOUT_SCAN_1000_DISABLE_DATA, CLK_VOUT_SCAN_1000_EN_SHIFT, CLK_VOUT_SCAN_1000_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_VOUT_SCAN_1000_ 		itg_get_reg(CLK_VOUT_SCAN_1000_CTRL_REG_ADDR, CLK_VOUT_SCAN_1000_EN_SHIFT, CLK_VOUT_SCAN_1000_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_VOUT_SCAN_1000_(x) 		itg_set_reg(CLK_VOUT_SCAN_1000_CTRL_REG_ADDR, x, CLK_VOUT_SCAN_1000_EN_SHIFT, CLK_VOUT_SCAN_1000_EN_MASK)
#define _ENABLE_CLOCK_CLK_VOUT_SCAN_800_ 			itg_set_reg(CLK_VOUT_SCAN_800_CTRL_REG_ADDR, CLK_VOUT_SCAN_800_ENABLE_DATA, CLK_VOUT_SCAN_800_EN_SHIFT, CLK_VOUT_SCAN_800_EN_MASK)
#define _DISABLE_CLOCK_CLK_VOUT_SCAN_800_ 			itg_set_reg(CLK_VOUT_SCAN_800_CTRL_REG_ADDR, CLK_VOUT_SCAN_800_DISABLE_DATA, CLK_VOUT_SCAN_800_EN_SHIFT, CLK_VOUT_SCAN_800_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_VOUT_SCAN_800_ 		itg_get_reg(CLK_VOUT_SCAN_800_CTRL_REG_ADDR, CLK_VOUT_SCAN_800_EN_SHIFT, CLK_VOUT_SCAN_800_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_VOUT_SCAN_800_(x) 		itg_set_reg(CLK_VOUT_SCAN_800_CTRL_REG_ADDR, x, CLK_VOUT_SCAN_800_EN_SHIFT, CLK_VOUT_SCAN_800_EN_MASK)
#define _DIVIDE_CLOCK_CLK_VOUT_SCAN_800_(div) 			itg_set_reg(CLK_VOUT_SCAN_800_CTRL_REG_ADDR, div, CLK_VOUT_SCAN_800_DIV_SHIFT, CLK_VOUT_SCAN_800_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_VOUT_SCAN_800_ 		itg_get_reg(CLK_VOUT_SCAN_800_CTRL_REG_ADDR, CLK_VOUT_SCAN_800_DIV_SHIFT, CLK_VOUT_SCAN_800_DIV_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER3_600_ 			itg_set_reg(CLK_BMCPER3_600_CTRL_REG_ADDR, CLK_BMCPER3_600_ENABLE_DATA, CLK_BMCPER3_600_EN_SHIFT, CLK_BMCPER3_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER3_600_ 			itg_set_reg(CLK_BMCPER3_600_CTRL_REG_ADDR, CLK_BMCPER3_600_DISABLE_DATA, CLK_BMCPER3_600_EN_SHIFT, CLK_BMCPER3_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER3_600_ 		itg_get_reg(CLK_BMCPER3_600_CTRL_REG_ADDR, CLK_BMCPER3_600_EN_SHIFT, CLK_BMCPER3_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER3_600_(x) 		itg_set_reg(CLK_BMCPER3_600_CTRL_REG_ADDR, x, CLK_BMCPER3_600_EN_SHIFT, CLK_BMCPER3_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER3_600_(div) 			itg_set_reg(CLK_BMCPER3_600_CTRL_REG_ADDR, div, CLK_BMCPER3_600_DIV_SHIFT, CLK_BMCPER3_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER3_600_ 		itg_get_reg(CLK_BMCPER3_600_CTRL_REG_ADDR, CLK_BMCPER3_600_DIV_SHIFT, CLK_BMCPER3_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER3_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER3_INIT_CTRL_REG_ADDR, CLK_BMCPER3_INIT_SW_CLK_OSC_DATA, CLK_BMCPER3_INIT_SW_SHIFT, CLK_BMCPER3_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER3_INIT_SOURCE_CLK_BMCPER3_600_ 	itg_set_reg(CLK_BMCPER3_INIT_CTRL_REG_ADDR, CLK_BMCPER3_INIT_SW_CLK_BMCPER3_600_DATA, CLK_BMCPER3_INIT_SW_SHIFT, CLK_BMCPER3_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER3_INIT_ 		itg_get_reg(CLK_BMCPER3_INIT_CTRL_REG_ADDR, CLK_BMCPER3_INIT_SW_SHIFT, CLK_BMCPER3_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER3_INIT_(x) 		itg_set_reg(CLK_BMCPER3_INIT_CTRL_REG_ADDR, x, CLK_BMCPER3_INIT_SW_SHIFT, CLK_BMCPER3_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER3_100_ 			itg_set_reg(CLK_BMCPER3_100_CTRL_REG_ADDR, CLK_BMCPER3_100_ENABLE_DATA, CLK_BMCPER3_100_EN_SHIFT, CLK_BMCPER3_100_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER3_100_ 			itg_set_reg(CLK_BMCPER3_100_CTRL_REG_ADDR, CLK_BMCPER3_100_DISABLE_DATA, CLK_BMCPER3_100_EN_SHIFT, CLK_BMCPER3_100_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER3_100_ 		itg_get_reg(CLK_BMCPER3_100_CTRL_REG_ADDR, CLK_BMCPER3_100_EN_SHIFT, CLK_BMCPER3_100_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER3_100_(x) 		itg_set_reg(CLK_BMCPER3_100_CTRL_REG_ADDR, x, CLK_BMCPER3_100_EN_SHIFT, CLK_BMCPER3_100_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER3_100_(div) 			itg_set_reg(CLK_BMCPER3_100_CTRL_REG_ADDR, div, CLK_BMCPER3_100_DIV_SHIFT, CLK_BMCPER3_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER3_100_ 		itg_get_reg(CLK_BMCPER3_100_CTRL_REG_ADDR, CLK_BMCPER3_100_DIV_SHIFT, CLK_BMCPER3_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER3_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER3_TARG_CTRL_REG_ADDR, CLK_BMCPER3_TARG_SW_CLK_OSC_DATA, CLK_BMCPER3_TARG_SW_SHIFT, CLK_BMCPER3_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER3_TARG_SOURCE_CLK_BMCPER3_100_ 	itg_set_reg(CLK_BMCPER3_TARG_CTRL_REG_ADDR, CLK_BMCPER3_TARG_SW_CLK_BMCPER3_100_DATA, CLK_BMCPER3_TARG_SW_SHIFT, CLK_BMCPER3_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER3_TARG_ 		itg_get_reg(CLK_BMCPER3_TARG_CTRL_REG_ADDR, CLK_BMCPER3_TARG_SW_SHIFT, CLK_BMCPER3_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER3_TARG_(x) 		itg_set_reg(CLK_BMCPER3_TARG_CTRL_REG_ADDR, x, CLK_BMCPER3_TARG_SW_SHIFT, CLK_BMCPER3_TARG_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER3_125_ 			itg_set_reg(CLK_BMCPER3_125_CTRL_REG_ADDR, CLK_BMCPER3_125_ENABLE_DATA, CLK_BMCPER3_125_EN_SHIFT, CLK_BMCPER3_125_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER3_125_ 			itg_set_reg(CLK_BMCPER3_125_CTRL_REG_ADDR, CLK_BMCPER3_125_DISABLE_DATA, CLK_BMCPER3_125_EN_SHIFT, CLK_BMCPER3_125_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER3_125_ 		itg_get_reg(CLK_BMCPER3_125_CTRL_REG_ADDR, CLK_BMCPER3_125_EN_SHIFT, CLK_BMCPER3_125_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER3_125_(x) 		itg_set_reg(CLK_BMCPER3_125_CTRL_REG_ADDR, x, CLK_BMCPER3_125_EN_SHIFT, CLK_BMCPER3_125_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER3_125_(div) 			itg_set_reg(CLK_BMCPER3_125_CTRL_REG_ADDR, div, CLK_BMCPER3_125_DIV_SHIFT, CLK_BMCPER3_125_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER3_125_ 		itg_get_reg(CLK_BMCPER3_125_CTRL_REG_ADDR, CLK_BMCPER3_125_DIV_SHIFT, CLK_BMCPER3_125_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER3_125_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER3_125_OSC_CTRL_REG_ADDR, CLK_BMCPER3_125_OSC_SW_CLK_OSC_DATA, CLK_BMCPER3_125_OSC_SW_SHIFT, CLK_BMCPER3_125_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER3_125_OSC_SOURCE_CLK_BMCPER3_125_ 	itg_set_reg(CLK_BMCPER3_125_OSC_CTRL_REG_ADDR, CLK_BMCPER3_125_OSC_SW_CLK_BMCPER3_125_DATA, CLK_BMCPER3_125_OSC_SW_SHIFT, CLK_BMCPER3_125_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER3_125_OSC_ 		itg_get_reg(CLK_BMCPER3_125_OSC_CTRL_REG_ADDR, CLK_BMCPER3_125_OSC_SW_SHIFT, CLK_BMCPER3_125_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER3_125_OSC_(x) 		itg_set_reg(CLK_BMCPER3_125_OSC_CTRL_REG_ADDR, x, CLK_BMCPER3_125_OSC_SW_SHIFT, CLK_BMCPER3_125_OSC_SW_MASK)

#define _ENABLE_CLOCK_MAIN_ICG_EN_BCU_ 			itg_set_reg(MAIN_ICG_EN_BCU_CTRL_REG_ADDR, MAIN_ICG_EN_BCU_ENABLE_DATA, MAIN_ICG_EN_BCU_EN_SHIFT, MAIN_ICG_EN_BCU_EN_MASK)
#define _DISABLE_CLOCK_MAIN_ICG_EN_BCU_ 			itg_set_reg(MAIN_ICG_EN_BCU_CTRL_REG_ADDR, MAIN_ICG_EN_BCU_DISABLE_DATA, MAIN_ICG_EN_BCU_EN_SHIFT, MAIN_ICG_EN_BCU_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_MAIN_ICG_EN_BCU_ 		itg_get_reg(MAIN_ICG_EN_BCU_CTRL_REG_ADDR, MAIN_ICG_EN_BCU_EN_SHIFT, MAIN_ICG_EN_BCU_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_MAIN_ICG_EN_BCU_(x) 		itg_set_reg(MAIN_ICG_EN_BCU_CTRL_REG_ADDR, x, MAIN_ICG_EN_BCU_EN_SHIFT, MAIN_ICG_EN_BCU_EN_MASK)


#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_SYS1_SYSCON_PRESETN_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS1_SYSCON_PRESETN_SHIFT, RSTN_U0_SYS1_SYSCON_PRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_SYS1_SYSCON_PRESETN_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS1_SYSCON_PRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_SYS1_SYSCON_PRESETN_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS1_SYSCON_PRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_SHIFT, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR1_MASK)
#define _READ_RESET_STATUS_RSTGEN_MAIN_RSTN_SYS1_IOMUX_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_SYS1_IOMUX_SHIFT, MAIN_RSTN_SYS1_IOMUX_MASK)
#define _ASSERT_RESET_RSTGEN_MAIN_RSTN_SYS1_IOMUX_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_SYS1_IOMUX_MASK)
#define _CLEAR_RESET_RSTGEN_MAIN_RSTN_SYS1_IOMUX_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_SYS1_IOMUX_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_BCU_PRST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_BCU_PRST_SHIFT, RSTN_U0_BCU_PRST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_BCU_PRST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_BCU_PRST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_BCU_PRST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_BCU_PRST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_SHIFT, RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_BCU_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_BCU_DFT_BISR_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_BCU_DFT_BISR_RST_SHIFT, RSTN_U0_BCU_DFT_BISR_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_BCU_DFT_BISR_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_BCU_DFT_BISR_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_BCU_DFT_BISR_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_BCU_DFT_BISR_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_PCU_CORE_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_PCU_CORE_RST_SHIFT, RSTN_U0_PCU_CORE_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_PCU_CORE_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_PCU_CORE_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_PCU_CORE_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_PCU_CORE_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_PCU_APB_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_PCU_APB_RST_SHIFT, RSTN_U0_PCU_APB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_PCU_APB_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_PCU_APB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_PCU_APB_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_PCU_APB_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U1_PCU_CORE_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_PCU_CORE_RST_SHIFT, RSTN_U1_PCU_CORE_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U1_PCU_CORE_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_PCU_CORE_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U1_PCU_CORE_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_PCU_CORE_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U1_PCU_APB_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_PCU_APB_RST_SHIFT, RSTN_U1_PCU_APB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U1_PCU_APB_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_PCU_APB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U1_PCU_APB_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_PCU_APB_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U2_PCU_CORE_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U2_PCU_CORE_RST_SHIFT, RSTN_U2_PCU_CORE_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U2_PCU_CORE_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U2_PCU_CORE_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U2_PCU_CORE_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U2_PCU_CORE_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U2_PCU_APB_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U2_PCU_APB_RST_SHIFT, RSTN_U2_PCU_APB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U2_PCU_APB_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U2_PCU_APB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U2_PCU_APB_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U2_PCU_APB_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U3_PCU_CORE_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U3_PCU_CORE_RST_SHIFT, RSTN_U3_PCU_CORE_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U3_PCU_CORE_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U3_PCU_CORE_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U3_PCU_CORE_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U3_PCU_CORE_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U3_PCU_APB_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U3_PCU_APB_RST_SHIFT, RSTN_U3_PCU_APB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U3_PCU_APB_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U3_PCU_APB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U3_PCU_APB_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U3_PCU_APB_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U9_PCU_CORE_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U9_PCU_CORE_RST_SHIFT, RSTN_U9_PCU_CORE_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U9_PCU_CORE_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U9_PCU_CORE_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U9_PCU_CORE_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U9_PCU_CORE_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U9_PCU_APB_RST_ 	itg_get_reg(SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U9_PCU_APB_RST_SHIFT, RSTN_U9_PCU_APB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U9_PCU_APB_RST_ 	itg_assert_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U9_PCU_APB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U9_PCU_APB_RST_ 	itg_clear_rst(SYS1_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS1_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U9_PCU_APB_RST_MASK)


#endif //_SYS1_CRG_MACRO_H_
