//RTL tag v0.5.1


#ifndef _SYS2_CRG_MACRO_H_
#define _SYS2_CRG_MACRO_H_

//#define SYS2_CRG_BASE_ADDR 0x0
#define CLK_APB_MAIN_SYS2_CTRL_REG_ADDR                              (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x0U)
#define CLK_APB_OSC_SYS2_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x4U)
#define CLK_JTAGM_200_CTRL_REG_ADDR                                  (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x8U)
#define CLK_JTAGM_100_CTRL_REG_ADDR                                  (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0xCU)
#define CLK_HOSTUSB_600_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x10U)
#define CLK_HOSTUSB_INIT_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x14U)
#define CLK_HOSTUSB_200_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x18U)
#define CLK_HOSTUSB_TARG_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x1CU)
#define CLK_HOSTUSB_100_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x20U)
#define CLK_HOSTUSBCMN_TARG_CTRL_REG_ADDR                            (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x24U)
#define CLK_HOSTUSBCMN_500_CTRL_REG_ADDR                             (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x28U)
#define CLK_HOSTUSBCMN_500_OSC_CTRL_REG_ADDR                         (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x2CU)
#define CLK_HOSTUSBCMN_480_CTRL_REG_ADDR                             (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x30U)
#define CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR                         (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x34U)
#define CLK_SEC_600_CTRL_REG_ADDR                                    (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x38U)
#define CLK_SEC_DATA_INIT_CTRL_REG_ADDR                              (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x3CU)
#define CLK_SEC_200_CTRL_REG_ADDR                                    (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x40U)
#define CLK_SEC_CFG_INIT_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x44U)
#define CLK_SEC_TARG_CTRL_REG_ADDR                                   (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x48U)
#define CLK_BMCPER1_600_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x4CU)
#define CLK_BMCPER1_INIT_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x50U)
#define CLK_BMCPER1_200_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x54U)
#define CLK_BMCPER1_TARG_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x58U)
#define CLK_BMCPER1_400_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x5CU)
#define CLK_BMCPER1_400_OSC_CTRL_REG_ADDR                            (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x60U)
#define CLK_UFS_REF_CTRL_REG_ADDR                                    (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x64U)
#define CLK_BMCPER1_250_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x68U)
#define CLK_BMCPER1_250_OSC_CTRL_REG_ADDR                            (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x6CU)
#define CLK_BMCPER1_143_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x70U)
#define CLK_BMCPER1_800_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x74U)
#define CLK_BMCPER1_800_OSC_CTRL_REG_ADDR                            (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x78U)
#define CLK_BMCPER0_600_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x7CU)
#define CLK_BMCPER0_INIT_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x80U)
#define CLK_BMCPER0_200_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x84U)
#define CLK_BMCPER0_TARG_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x88U)
#define CLK_BMCPER0_400_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x8CU)
#define CLK_BMCPER0_400_OSC_CTRL_REG_ADDR                            (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x90U)
#define CLK_BMCPER0_125_CTRL_REG_ADDR                                (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x94U)
#define CLK_BMCPER0_125_OSC_CTRL_REG_ADDR                            (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x98U)
#define CLK_BMCPER0_PLL6_CTRL_REG_ADDR                               (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0x9CU)


#define SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR              (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0xBCU)

#define SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR              (U0_SYS2_CRG__ITG_BD_APBS__BASE_ADDR + 0xC0U)


#define CLK_APB_MAIN_SYS2_DIV_SHIFT                                  0
#define CLK_APB_MAIN_SYS2_DIV_MASK                                   0xFU
#define CLK_APB_OSC_SYS2_SW_SHIFT                                    24
#define CLK_APB_OSC_SYS2_SW_MASK                                     0x1000000U
#define CLK_APB_OSC_SYS2_SW_CLK_OSC_DATA                             0
#define CLK_APB_OSC_SYS2_SW_CLK_APB_MAIN_SYS2_DATA                   1
#define CLK_JTAGM_200_ENABLE_DATA                                    1
#define CLK_JTAGM_200_DISABLE_DATA                                   0
#define CLK_JTAGM_200_EN_SHIFT                                       31
#define CLK_JTAGM_200_EN_MASK                                        0x80000000U
#define CLK_JTAGM_200_DIV_SHIFT                                      0
#define CLK_JTAGM_200_DIV_MASK                                       0x7U
#define CLK_JTAGM_100_ENABLE_DATA                                    1
#define CLK_JTAGM_100_DISABLE_DATA                                   0
#define CLK_JTAGM_100_EN_SHIFT                                       31
#define CLK_JTAGM_100_EN_MASK                                        0x80000000U
#define CLK_JTAGM_100_DIV_SHIFT                                      0
#define CLK_JTAGM_100_DIV_MASK                                       0xFU
#define CLK_HOSTUSB_600_ENABLE_DATA                                  1
#define CLK_HOSTUSB_600_DISABLE_DATA                                 0
#define CLK_HOSTUSB_600_EN_SHIFT                                     31
#define CLK_HOSTUSB_600_EN_MASK                                      0x80000000U
#define CLK_HOSTUSB_600_DIV_SHIFT                                    0
#define CLK_HOSTUSB_600_DIV_MASK                                     0x7U
#define CLK_HOSTUSB_INIT_SW_SHIFT                                    24
#define CLK_HOSTUSB_INIT_SW_MASK                                     0x1000000U
#define CLK_HOSTUSB_INIT_SW_CLK_OSC_DATA                             0
#define CLK_HOSTUSB_INIT_SW_CLK_HOSTUSB_600_DATA                     1
#define CLK_HOSTUSB_200_ENABLE_DATA                                  1
#define CLK_HOSTUSB_200_DISABLE_DATA                                 0
#define CLK_HOSTUSB_200_EN_SHIFT                                     31
#define CLK_HOSTUSB_200_EN_MASK                                      0x80000000U
#define CLK_HOSTUSB_200_DIV_SHIFT                                    0
#define CLK_HOSTUSB_200_DIV_MASK                                     0x7U
#define CLK_HOSTUSB_TARG_SW_SHIFT                                    24
#define CLK_HOSTUSB_TARG_SW_MASK                                     0x1000000U
#define CLK_HOSTUSB_TARG_SW_CLK_OSC_DATA                             0
#define CLK_HOSTUSB_TARG_SW_CLK_HOSTUSB_200_DATA                     1
#define CLK_HOSTUSB_100_ENABLE_DATA                                  1
#define CLK_HOSTUSB_100_DISABLE_DATA                                 0
#define CLK_HOSTUSB_100_EN_SHIFT                                     31
#define CLK_HOSTUSB_100_EN_MASK                                      0x80000000U
#define CLK_HOSTUSB_100_DIV_SHIFT                                    0
#define CLK_HOSTUSB_100_DIV_MASK                                     0xFU
#define CLK_HOSTUSBCMN_TARG_SW_SHIFT                                 24
#define CLK_HOSTUSBCMN_TARG_SW_MASK                                  0x1000000U
#define CLK_HOSTUSBCMN_TARG_SW_CLK_OSC_DATA                          0
#define CLK_HOSTUSBCMN_TARG_SW_CLK_HOSTUSB_100_DATA                  1
#define CLK_HOSTUSBCMN_500_ENABLE_DATA                               1
#define CLK_HOSTUSBCMN_500_DISABLE_DATA                              0
#define CLK_HOSTUSBCMN_500_EN_SHIFT                                  31
#define CLK_HOSTUSBCMN_500_EN_MASK                                   0x80000000U
#define CLK_HOSTUSBCMN_500_DIV_SHIFT                                 0
#define CLK_HOSTUSBCMN_500_DIV_MASK                                  0x7U
#define CLK_HOSTUSBCMN_500_OSC_SW_SHIFT                              24
#define CLK_HOSTUSBCMN_500_OSC_SW_MASK                               0x1000000U
#define CLK_HOSTUSBCMN_500_OSC_SW_CLK_OSC_DATA                       0
#define CLK_HOSTUSBCMN_500_OSC_SW_CLK_HOSTUSBCMN_500_DATA            1
#define CLK_HOSTUSBCMN_480_ENABLE_DATA                               1
#define CLK_HOSTUSBCMN_480_DISABLE_DATA                              0
#define CLK_HOSTUSBCMN_480_EN_SHIFT                                  31
#define CLK_HOSTUSBCMN_480_EN_MASK                                   0x80000000U
#define CLK_HOSTUSBCMN_480_DIV_SHIFT                                 0
#define CLK_HOSTUSBCMN_480_DIV_MASK                                  0x7U
#define CLK_HOSTUSBCMN_480_OSC_SW_SHIFT                              24
#define CLK_HOSTUSBCMN_480_OSC_SW_MASK                               0x1000000U
#define CLK_HOSTUSBCMN_480_OSC_SW_CLK_OSC_DATA                       0
#define CLK_HOSTUSBCMN_480_OSC_SW_CLK_HOSTUSBCMN_480_DATA            1
#define CLK_SEC_600_ENABLE_DATA                                      1
#define CLK_SEC_600_DISABLE_DATA                                     0
#define CLK_SEC_600_EN_SHIFT                                         31
#define CLK_SEC_600_EN_MASK                                          0x80000000U
#define CLK_SEC_600_DIV_SHIFT                                        0
#define CLK_SEC_600_DIV_MASK                                         0x7U
#define CLK_SEC_DATA_INIT_SW_SHIFT                                   24
#define CLK_SEC_DATA_INIT_SW_MASK                                    0x1000000U
#define CLK_SEC_DATA_INIT_SW_CLK_OSC_DATA                            0
#define CLK_SEC_DATA_INIT_SW_CLK_SEC_600_DATA                        1
#define CLK_SEC_200_ENABLE_DATA                                      1
#define CLK_SEC_200_DISABLE_DATA                                     0
#define CLK_SEC_200_EN_SHIFT                                         31
#define CLK_SEC_200_EN_MASK                                          0x80000000U
#define CLK_SEC_200_DIV_SHIFT                                        0
#define CLK_SEC_200_DIV_MASK                                         0x7U
#define CLK_SEC_CFG_INIT_SW_SHIFT                                    24
#define CLK_SEC_CFG_INIT_SW_MASK                                     0x1000000U
#define CLK_SEC_CFG_INIT_SW_CLK_OSC_DATA                             0
#define CLK_SEC_CFG_INIT_SW_CLK_SEC_200_DATA                         1
#define CLK_SEC_TARG_ENABLE_DATA                                     1
#define CLK_SEC_TARG_DISABLE_DATA                                    0
#define CLK_SEC_TARG_EN_SHIFT                                        31
#define CLK_SEC_TARG_EN_MASK                                         0x80000000U
#define CLK_SEC_TARG_SW_SHIFT                                        24
#define CLK_SEC_TARG_SW_MASK                                         0x1000000U
#define CLK_SEC_TARG_SW_CLK_OSC_DATA                                 0
#define CLK_SEC_TARG_SW_CLK_SEC_200_DATA                             1
#define CLK_SEC_TARG_DIV_SHIFT                                       0
#define CLK_SEC_TARG_DIV_MASK                                        0x7U
#define CLK_BMCPER1_600_ENABLE_DATA                                  1
#define CLK_BMCPER1_600_DISABLE_DATA                                 0
#define CLK_BMCPER1_600_EN_SHIFT                                     31
#define CLK_BMCPER1_600_EN_MASK                                      0x80000000U
#define CLK_BMCPER1_600_DIV_SHIFT                                    0
#define CLK_BMCPER1_600_DIV_MASK                                     0x7U
#define CLK_BMCPER1_INIT_SW_SHIFT                                    24
#define CLK_BMCPER1_INIT_SW_MASK                                     0x1000000U
#define CLK_BMCPER1_INIT_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER1_INIT_SW_CLK_BMCPER1_600_DATA                     1
#define CLK_BMCPER1_200_ENABLE_DATA                                  1
#define CLK_BMCPER1_200_DISABLE_DATA                                 0
#define CLK_BMCPER1_200_EN_SHIFT                                     31
#define CLK_BMCPER1_200_EN_MASK                                      0x80000000U
#define CLK_BMCPER1_200_DIV_SHIFT                                    0
#define CLK_BMCPER1_200_DIV_MASK                                     0x7U
#define CLK_BMCPER1_TARG_SW_SHIFT                                    24
#define CLK_BMCPER1_TARG_SW_MASK                                     0x1000000U
#define CLK_BMCPER1_TARG_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER1_TARG_SW_CLK_BMCPER1_200_DATA                     1
#define CLK_BMCPER1_400_ENABLE_DATA                                  1
#define CLK_BMCPER1_400_DISABLE_DATA                                 0
#define CLK_BMCPER1_400_EN_SHIFT                                     31
#define CLK_BMCPER1_400_EN_MASK                                      0x80000000U
#define CLK_BMCPER1_400_DIV_SHIFT                                    0
#define CLK_BMCPER1_400_DIV_MASK                                     0xFU
#define CLK_BMCPER1_400_OSC_SW_SHIFT                                 24
#define CLK_BMCPER1_400_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER1_400_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER1_400_OSC_SW_CLK_BMCPER1_400_DATA                  1
#define CLK_UFS_REF_ENABLE_DATA                                      1
#define CLK_UFS_REF_DISABLE_DATA                                     0
#define CLK_UFS_REF_EN_SHIFT                                         31
#define CLK_UFS_REF_EN_MASK                                          0x80000000U
#define CLK_UFS_REF_DIV_SHIFT                                        0
#define CLK_UFS_REF_DIV_MASK                                         0x1FU
#define CLK_BMCPER1_250_ENABLE_DATA                                  1
#define CLK_BMCPER1_250_DISABLE_DATA                                 0
#define CLK_BMCPER1_250_EN_SHIFT                                     31
#define CLK_BMCPER1_250_EN_MASK                                      0x80000000U
#define CLK_BMCPER1_250_DIV_SHIFT                                    0
#define CLK_BMCPER1_250_DIV_MASK                                     0x7U
#define CLK_BMCPER1_250_OSC_SW_SHIFT                                 24
#define CLK_BMCPER1_250_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER1_250_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER1_250_OSC_SW_CLK_BMCPER1_250_DATA                  1
#define CLK_BMCPER1_143_ENABLE_DATA                                  1
#define CLK_BMCPER1_143_DISABLE_DATA                                 0
#define CLK_BMCPER1_143_EN_SHIFT                                     31
#define CLK_BMCPER1_143_EN_MASK                                      0x80000000U
#define CLK_BMCPER1_143_DIV_SHIFT                                    0
#define CLK_BMCPER1_143_DIV_MASK                                     0xFU
#define CLK_BMCPER1_800_ENABLE_DATA                                  1
#define CLK_BMCPER1_800_DISABLE_DATA                                 0
#define CLK_BMCPER1_800_EN_SHIFT                                     31
#define CLK_BMCPER1_800_EN_MASK                                      0x80000000U
#define CLK_BMCPER1_800_DIV_SHIFT                                    0
#define CLK_BMCPER1_800_DIV_MASK                                     0x7U
#define CLK_BMCPER1_800_OSC_SW_SHIFT                                 24
#define CLK_BMCPER1_800_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER1_800_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER1_800_OSC_SW_CLK_BMCPER1_800_DATA                  1
#define CLK_BMCPER0_600_ENABLE_DATA                                  1
#define CLK_BMCPER0_600_DISABLE_DATA                                 0
#define CLK_BMCPER0_600_EN_SHIFT                                     31
#define CLK_BMCPER0_600_EN_MASK                                      0x80000000U
#define CLK_BMCPER0_600_DIV_SHIFT                                    0
#define CLK_BMCPER0_600_DIV_MASK                                     0x7U
#define CLK_BMCPER0_INIT_SW_SHIFT                                    24
#define CLK_BMCPER0_INIT_SW_MASK                                     0x1000000U
#define CLK_BMCPER0_INIT_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER0_INIT_SW_CLK_BMCPER0_600_DATA                     1
#define CLK_BMCPER0_200_ENABLE_DATA                                  1
#define CLK_BMCPER0_200_DISABLE_DATA                                 0
#define CLK_BMCPER0_200_EN_SHIFT                                     31
#define CLK_BMCPER0_200_EN_MASK                                      0x80000000U
#define CLK_BMCPER0_200_DIV_SHIFT                                    0
#define CLK_BMCPER0_200_DIV_MASK                                     0x7U
#define CLK_BMCPER0_TARG_SW_SHIFT                                    24
#define CLK_BMCPER0_TARG_SW_MASK                                     0x1000000U
#define CLK_BMCPER0_TARG_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER0_TARG_SW_CLK_BMCPER0_200_DATA                     1
#define CLK_BMCPER0_400_ENABLE_DATA                                  1
#define CLK_BMCPER0_400_DISABLE_DATA                                 0
#define CLK_BMCPER0_400_EN_SHIFT                                     31
#define CLK_BMCPER0_400_EN_MASK                                      0x80000000U
#define CLK_BMCPER0_400_DIV_SHIFT                                    0
#define CLK_BMCPER0_400_DIV_MASK                                     0xFU
#define CLK_BMCPER0_400_OSC_SW_SHIFT                                 24
#define CLK_BMCPER0_400_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER0_400_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER0_400_OSC_SW_CLK_BMCPER0_400_DATA                  1
#define CLK_BMCPER0_125_ENABLE_DATA                                  1
#define CLK_BMCPER0_125_DISABLE_DATA                                 0
#define CLK_BMCPER0_125_EN_SHIFT                                     31
#define CLK_BMCPER0_125_EN_MASK                                      0x80000000U
#define CLK_BMCPER0_125_DIV_SHIFT                                    0
#define CLK_BMCPER0_125_DIV_MASK                                     0xFU
#define CLK_BMCPER0_125_OSC_SW_SHIFT                                 24
#define CLK_BMCPER0_125_OSC_SW_MASK                                  0x1000000U
#define CLK_BMCPER0_125_OSC_SW_CLK_OSC_DATA                          0
#define CLK_BMCPER0_125_OSC_SW_CLK_BMCPER0_125_DATA                  1
#define CLK_BMCPER0_PLL6_ENABLE_DATA                                 1
#define CLK_BMCPER0_PLL6_DISABLE_DATA                                0
#define CLK_BMCPER0_PLL6_EN_SHIFT                                    31
#define CLK_BMCPER0_PLL6_EN_MASK                                     0x80000000U
#define CLK_BMCPER0_PLL6_SW_SHIFT                                    24
#define CLK_BMCPER0_PLL6_SW_MASK                                     0x1000000U
#define CLK_BMCPER0_PLL6_SW_CLK_OSC_DATA                             0
#define CLK_BMCPER0_PLL6_SW_CLK_PLL6_DATA                            1




#define RSTN_U0_SYS2_SYSCON_PRESETN_SHIFT                            0
#define RSTN_U0_SYS2_SYSCON_PRESETN_MASK                             (0x1 << 0)
#define RSTN_U0_SYS2_SYSCON_PRESETN_ASSERT                           1
#define RSTN_U0_SYS2_SYSCON_PRESETN_CLEAR                            0
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_SHIFT                         1
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_MASK                          (0x1 << 1)
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_ASSERT                        1
#define RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_CLEAR                         0
#define MAIN_RSTN_SYS2_IOMUX_SHIFT                                   2
#define MAIN_RSTN_SYS2_IOMUX_MASK                                    (0x1 << 2)
#define MAIN_RSTN_SYS2_IOMUX_ASSERT                                  1
#define MAIN_RSTN_SYS2_IOMUX_CLEAR                                   0
#define RSTN_U0_JTAG_MST_WRAP_HRESETN_SHIFT                          3
#define RSTN_U0_JTAG_MST_WRAP_HRESETN_MASK                           (0x1 << 3)
#define RSTN_U0_JTAG_MST_WRAP_HRESETN_ASSERT                         1
#define RSTN_U0_JTAG_MST_WRAP_HRESETN_CLEAR                          0
#define RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_SHIFT                      4
#define RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_MASK                       (0x1 << 4)
#define RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_ASSERT                     1
#define RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_CLEAR                      0
#define RSTN_U1_JTAG_MST_WRAP_HRESETN_SHIFT                          5
#define RSTN_U1_JTAG_MST_WRAP_HRESETN_MASK                           (0x1 << 5)
#define RSTN_U1_JTAG_MST_WRAP_HRESETN_ASSERT                         1
#define RSTN_U1_JTAG_MST_WRAP_HRESETN_CLEAR                          0
#define RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_SHIFT                      6
#define RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_MASK                       (0x1 << 6)
#define RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_ASSERT                     1
#define RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_CLEAR                      0
#define RSTN_U4_PCU_CORE_RST_SHIFT                                   7
#define RSTN_U4_PCU_CORE_RST_MASK                                    (0x1 << 7)
#define RSTN_U4_PCU_CORE_RST_ASSERT                                  1
#define RSTN_U4_PCU_CORE_RST_CLEAR                                   0
#define RSTN_U4_PCU_APB_RST_SHIFT                                    8
#define RSTN_U4_PCU_APB_RST_MASK                                     (0x1 << 8)
#define RSTN_U4_PCU_APB_RST_ASSERT                                   1
#define RSTN_U4_PCU_APB_RST_CLEAR                                    0
#define RSTN_U5_PCU_CORE_RST_SHIFT                                   9
#define RSTN_U5_PCU_CORE_RST_MASK                                    (0x1 << 9)
#define RSTN_U5_PCU_CORE_RST_ASSERT                                  1
#define RSTN_U5_PCU_CORE_RST_CLEAR                                   0
#define RSTN_U5_PCU_APB_RST_SHIFT                                    10
#define RSTN_U5_PCU_APB_RST_MASK                                     (0x1 << 10)
#define RSTN_U5_PCU_APB_RST_ASSERT                                   1
#define RSTN_U5_PCU_APB_RST_CLEAR                                    0
#define RSTN_U10_PCU_CORE_RST_SHIFT                                  11
#define RSTN_U10_PCU_CORE_RST_MASK                                   (0x1 << 11)
#define RSTN_U10_PCU_CORE_RST_ASSERT                                 1
#define RSTN_U10_PCU_CORE_RST_CLEAR                                  0
#define RSTN_U10_PCU_APB_RST_SHIFT                                   12
#define RSTN_U10_PCU_APB_RST_MASK                                    (0x1 << 12)
#define RSTN_U10_PCU_APB_RST_ASSERT                                  1
#define RSTN_U10_PCU_APB_RST_CLEAR                                   0

#define _DIVIDE_CLOCK_CLK_APB_MAIN_SYS2_(div) 			itg_set_reg(CLK_APB_MAIN_SYS2_CTRL_REG_ADDR, div, CLK_APB_MAIN_SYS2_DIV_SHIFT, CLK_APB_MAIN_SYS2_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_APB_MAIN_SYS2_ 		itg_get_reg(CLK_APB_MAIN_SYS2_CTRL_REG_ADDR, CLK_APB_MAIN_SYS2_DIV_SHIFT, CLK_APB_MAIN_SYS2_DIV_MASK)
#define _SWITCH_CLOCK_CLK_APB_OSC_SYS2_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_APB_OSC_SYS2_CTRL_REG_ADDR, CLK_APB_OSC_SYS2_SW_CLK_OSC_DATA, CLK_APB_OSC_SYS2_SW_SHIFT, CLK_APB_OSC_SYS2_SW_MASK)
#define _SWITCH_CLOCK_CLK_APB_OSC_SYS2_SOURCE_CLK_APB_MAIN_SYS2_ 	itg_set_reg(CLK_APB_OSC_SYS2_CTRL_REG_ADDR, CLK_APB_OSC_SYS2_SW_CLK_APB_MAIN_SYS2_DATA, CLK_APB_OSC_SYS2_SW_SHIFT, CLK_APB_OSC_SYS2_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_APB_OSC_SYS2_ 		itg_get_reg(CLK_APB_OSC_SYS2_CTRL_REG_ADDR, CLK_APB_OSC_SYS2_SW_SHIFT, CLK_APB_OSC_SYS2_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_APB_OSC_SYS2_(x) 		itg_set_reg(CLK_APB_OSC_SYS2_CTRL_REG_ADDR, x, CLK_APB_OSC_SYS2_SW_SHIFT, CLK_APB_OSC_SYS2_SW_MASK)
#define _ENABLE_CLOCK_CLK_JTAGM_200_ 			itg_set_reg(CLK_JTAGM_200_CTRL_REG_ADDR, CLK_JTAGM_200_ENABLE_DATA, CLK_JTAGM_200_EN_SHIFT, CLK_JTAGM_200_EN_MASK)
#define _DISABLE_CLOCK_CLK_JTAGM_200_ 			itg_set_reg(CLK_JTAGM_200_CTRL_REG_ADDR, CLK_JTAGM_200_DISABLE_DATA, CLK_JTAGM_200_EN_SHIFT, CLK_JTAGM_200_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_JTAGM_200_ 		itg_get_reg(CLK_JTAGM_200_CTRL_REG_ADDR, CLK_JTAGM_200_EN_SHIFT, CLK_JTAGM_200_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_JTAGM_200_(x) 		itg_set_reg(CLK_JTAGM_200_CTRL_REG_ADDR, x, CLK_JTAGM_200_EN_SHIFT, CLK_JTAGM_200_EN_MASK)
#define _DIVIDE_CLOCK_CLK_JTAGM_200_(div) 			itg_set_reg(CLK_JTAGM_200_CTRL_REG_ADDR, div, CLK_JTAGM_200_DIV_SHIFT, CLK_JTAGM_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_JTAGM_200_ 		itg_get_reg(CLK_JTAGM_200_CTRL_REG_ADDR, CLK_JTAGM_200_DIV_SHIFT, CLK_JTAGM_200_DIV_MASK)
#define _ENABLE_CLOCK_CLK_JTAGM_100_ 			itg_set_reg(CLK_JTAGM_100_CTRL_REG_ADDR, CLK_JTAGM_100_ENABLE_DATA, CLK_JTAGM_100_EN_SHIFT, CLK_JTAGM_100_EN_MASK)
#define _DISABLE_CLOCK_CLK_JTAGM_100_ 			itg_set_reg(CLK_JTAGM_100_CTRL_REG_ADDR, CLK_JTAGM_100_DISABLE_DATA, CLK_JTAGM_100_EN_SHIFT, CLK_JTAGM_100_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_JTAGM_100_ 		itg_get_reg(CLK_JTAGM_100_CTRL_REG_ADDR, CLK_JTAGM_100_EN_SHIFT, CLK_JTAGM_100_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_JTAGM_100_(x) 		itg_set_reg(CLK_JTAGM_100_CTRL_REG_ADDR, x, CLK_JTAGM_100_EN_SHIFT, CLK_JTAGM_100_EN_MASK)
#define _DIVIDE_CLOCK_CLK_JTAGM_100_(div) 			itg_set_reg(CLK_JTAGM_100_CTRL_REG_ADDR, div, CLK_JTAGM_100_DIV_SHIFT, CLK_JTAGM_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_JTAGM_100_ 		itg_get_reg(CLK_JTAGM_100_CTRL_REG_ADDR, CLK_JTAGM_100_DIV_SHIFT, CLK_JTAGM_100_DIV_MASK)
#define _ENABLE_CLOCK_CLK_HOSTUSB_600_ 			itg_set_reg(CLK_HOSTUSB_600_CTRL_REG_ADDR, CLK_HOSTUSB_600_ENABLE_DATA, CLK_HOSTUSB_600_EN_SHIFT, CLK_HOSTUSB_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTUSB_600_ 			itg_set_reg(CLK_HOSTUSB_600_CTRL_REG_ADDR, CLK_HOSTUSB_600_DISABLE_DATA, CLK_HOSTUSB_600_EN_SHIFT, CLK_HOSTUSB_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTUSB_600_ 		itg_get_reg(CLK_HOSTUSB_600_CTRL_REG_ADDR, CLK_HOSTUSB_600_EN_SHIFT, CLK_HOSTUSB_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTUSB_600_(x) 		itg_set_reg(CLK_HOSTUSB_600_CTRL_REG_ADDR, x, CLK_HOSTUSB_600_EN_SHIFT, CLK_HOSTUSB_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTUSB_600_(div) 			itg_set_reg(CLK_HOSTUSB_600_CTRL_REG_ADDR, div, CLK_HOSTUSB_600_DIV_SHIFT, CLK_HOSTUSB_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTUSB_600_ 		itg_get_reg(CLK_HOSTUSB_600_CTRL_REG_ADDR, CLK_HOSTUSB_600_DIV_SHIFT, CLK_HOSTUSB_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSB_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTUSB_INIT_CTRL_REG_ADDR, CLK_HOSTUSB_INIT_SW_CLK_OSC_DATA, CLK_HOSTUSB_INIT_SW_SHIFT, CLK_HOSTUSB_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSB_INIT_SOURCE_CLK_HOSTUSB_600_ 	itg_set_reg(CLK_HOSTUSB_INIT_CTRL_REG_ADDR, CLK_HOSTUSB_INIT_SW_CLK_HOSTUSB_600_DATA, CLK_HOSTUSB_INIT_SW_SHIFT, CLK_HOSTUSB_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTUSB_INIT_ 		itg_get_reg(CLK_HOSTUSB_INIT_CTRL_REG_ADDR, CLK_HOSTUSB_INIT_SW_SHIFT, CLK_HOSTUSB_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTUSB_INIT_(x) 		itg_set_reg(CLK_HOSTUSB_INIT_CTRL_REG_ADDR, x, CLK_HOSTUSB_INIT_SW_SHIFT, CLK_HOSTUSB_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_HOSTUSB_200_ 			itg_set_reg(CLK_HOSTUSB_200_CTRL_REG_ADDR, CLK_HOSTUSB_200_ENABLE_DATA, CLK_HOSTUSB_200_EN_SHIFT, CLK_HOSTUSB_200_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTUSB_200_ 			itg_set_reg(CLK_HOSTUSB_200_CTRL_REG_ADDR, CLK_HOSTUSB_200_DISABLE_DATA, CLK_HOSTUSB_200_EN_SHIFT, CLK_HOSTUSB_200_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTUSB_200_ 		itg_get_reg(CLK_HOSTUSB_200_CTRL_REG_ADDR, CLK_HOSTUSB_200_EN_SHIFT, CLK_HOSTUSB_200_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTUSB_200_(x) 		itg_set_reg(CLK_HOSTUSB_200_CTRL_REG_ADDR, x, CLK_HOSTUSB_200_EN_SHIFT, CLK_HOSTUSB_200_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTUSB_200_(div) 			itg_set_reg(CLK_HOSTUSB_200_CTRL_REG_ADDR, div, CLK_HOSTUSB_200_DIV_SHIFT, CLK_HOSTUSB_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTUSB_200_ 		itg_get_reg(CLK_HOSTUSB_200_CTRL_REG_ADDR, CLK_HOSTUSB_200_DIV_SHIFT, CLK_HOSTUSB_200_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSB_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTUSB_TARG_CTRL_REG_ADDR, CLK_HOSTUSB_TARG_SW_CLK_OSC_DATA, CLK_HOSTUSB_TARG_SW_SHIFT, CLK_HOSTUSB_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSB_TARG_SOURCE_CLK_HOSTUSB_200_ 	itg_set_reg(CLK_HOSTUSB_TARG_CTRL_REG_ADDR, CLK_HOSTUSB_TARG_SW_CLK_HOSTUSB_200_DATA, CLK_HOSTUSB_TARG_SW_SHIFT, CLK_HOSTUSB_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTUSB_TARG_ 		itg_get_reg(CLK_HOSTUSB_TARG_CTRL_REG_ADDR, CLK_HOSTUSB_TARG_SW_SHIFT, CLK_HOSTUSB_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTUSB_TARG_(x) 		itg_set_reg(CLK_HOSTUSB_TARG_CTRL_REG_ADDR, x, CLK_HOSTUSB_TARG_SW_SHIFT, CLK_HOSTUSB_TARG_SW_MASK)
#define _ENABLE_CLOCK_CLK_HOSTUSB_100_ 			itg_set_reg(CLK_HOSTUSB_100_CTRL_REG_ADDR, CLK_HOSTUSB_100_ENABLE_DATA, CLK_HOSTUSB_100_EN_SHIFT, CLK_HOSTUSB_100_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTUSB_100_ 			itg_set_reg(CLK_HOSTUSB_100_CTRL_REG_ADDR, CLK_HOSTUSB_100_DISABLE_DATA, CLK_HOSTUSB_100_EN_SHIFT, CLK_HOSTUSB_100_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTUSB_100_ 		itg_get_reg(CLK_HOSTUSB_100_CTRL_REG_ADDR, CLK_HOSTUSB_100_EN_SHIFT, CLK_HOSTUSB_100_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTUSB_100_(x) 		itg_set_reg(CLK_HOSTUSB_100_CTRL_REG_ADDR, x, CLK_HOSTUSB_100_EN_SHIFT, CLK_HOSTUSB_100_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTUSB_100_(div) 			itg_set_reg(CLK_HOSTUSB_100_CTRL_REG_ADDR, div, CLK_HOSTUSB_100_DIV_SHIFT, CLK_HOSTUSB_100_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTUSB_100_ 		itg_get_reg(CLK_HOSTUSB_100_CTRL_REG_ADDR, CLK_HOSTUSB_100_DIV_SHIFT, CLK_HOSTUSB_100_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSBCMN_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTUSBCMN_TARG_CTRL_REG_ADDR, CLK_HOSTUSBCMN_TARG_SW_CLK_OSC_DATA, CLK_HOSTUSBCMN_TARG_SW_SHIFT, CLK_HOSTUSBCMN_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSBCMN_TARG_SOURCE_CLK_HOSTUSB_100_ 	itg_set_reg(CLK_HOSTUSBCMN_TARG_CTRL_REG_ADDR, CLK_HOSTUSBCMN_TARG_SW_CLK_HOSTUSB_100_DATA, CLK_HOSTUSBCMN_TARG_SW_SHIFT, CLK_HOSTUSBCMN_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTUSBCMN_TARG_ 		itg_get_reg(CLK_HOSTUSBCMN_TARG_CTRL_REG_ADDR, CLK_HOSTUSBCMN_TARG_SW_SHIFT, CLK_HOSTUSBCMN_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTUSBCMN_TARG_(x) 		itg_set_reg(CLK_HOSTUSBCMN_TARG_CTRL_REG_ADDR, x, CLK_HOSTUSBCMN_TARG_SW_SHIFT, CLK_HOSTUSBCMN_TARG_SW_MASK)
#define _ENABLE_CLOCK_CLK_HOSTUSBCMN_500_ 			itg_set_reg(CLK_HOSTUSBCMN_500_CTRL_REG_ADDR, CLK_HOSTUSBCMN_500_ENABLE_DATA, CLK_HOSTUSBCMN_500_EN_SHIFT, CLK_HOSTUSBCMN_500_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTUSBCMN_500_ 			itg_set_reg(CLK_HOSTUSBCMN_500_CTRL_REG_ADDR, CLK_HOSTUSBCMN_500_DISABLE_DATA, CLK_HOSTUSBCMN_500_EN_SHIFT, CLK_HOSTUSBCMN_500_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTUSBCMN_500_ 		itg_get_reg(CLK_HOSTUSBCMN_500_CTRL_REG_ADDR, CLK_HOSTUSBCMN_500_EN_SHIFT, CLK_HOSTUSBCMN_500_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTUSBCMN_500_(x) 		itg_set_reg(CLK_HOSTUSBCMN_500_CTRL_REG_ADDR, x, CLK_HOSTUSBCMN_500_EN_SHIFT, CLK_HOSTUSBCMN_500_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTUSBCMN_500_(div) 			itg_set_reg(CLK_HOSTUSBCMN_500_CTRL_REG_ADDR, div, CLK_HOSTUSBCMN_500_DIV_SHIFT, CLK_HOSTUSBCMN_500_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTUSBCMN_500_ 		itg_get_reg(CLK_HOSTUSBCMN_500_CTRL_REG_ADDR, CLK_HOSTUSBCMN_500_DIV_SHIFT, CLK_HOSTUSBCMN_500_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSBCMN_500_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTUSBCMN_500_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_500_OSC_SW_CLK_OSC_DATA, CLK_HOSTUSBCMN_500_OSC_SW_SHIFT, CLK_HOSTUSBCMN_500_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSBCMN_500_OSC_SOURCE_CLK_HOSTUSBCMN_500_ 	itg_set_reg(CLK_HOSTUSBCMN_500_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_500_OSC_SW_CLK_HOSTUSBCMN_500_DATA, CLK_HOSTUSBCMN_500_OSC_SW_SHIFT, CLK_HOSTUSBCMN_500_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTUSBCMN_500_OSC_ 		itg_get_reg(CLK_HOSTUSBCMN_500_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_500_OSC_SW_SHIFT, CLK_HOSTUSBCMN_500_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTUSBCMN_500_OSC_(x) 		itg_set_reg(CLK_HOSTUSBCMN_500_OSC_CTRL_REG_ADDR, x, CLK_HOSTUSBCMN_500_OSC_SW_SHIFT, CLK_HOSTUSBCMN_500_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_HOSTUSBCMN_480_ 			itg_set_reg(CLK_HOSTUSBCMN_480_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_ENABLE_DATA, CLK_HOSTUSBCMN_480_EN_SHIFT, CLK_HOSTUSBCMN_480_EN_MASK)
#define _DISABLE_CLOCK_CLK_HOSTUSBCMN_480_ 			itg_set_reg(CLK_HOSTUSBCMN_480_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_DISABLE_DATA, CLK_HOSTUSBCMN_480_EN_SHIFT, CLK_HOSTUSBCMN_480_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_HOSTUSBCMN_480_ 		itg_get_reg(CLK_HOSTUSBCMN_480_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_EN_SHIFT, CLK_HOSTUSBCMN_480_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_HOSTUSBCMN_480_(x) 		itg_set_reg(CLK_HOSTUSBCMN_480_CTRL_REG_ADDR, x, CLK_HOSTUSBCMN_480_EN_SHIFT, CLK_HOSTUSBCMN_480_EN_MASK)
#define _DIVIDE_CLOCK_CLK_HOSTUSBCMN_480_(div) 			itg_set_reg(CLK_HOSTUSBCMN_480_CTRL_REG_ADDR, div, CLK_HOSTUSBCMN_480_DIV_SHIFT, CLK_HOSTUSBCMN_480_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_HOSTUSBCMN_480_ 		itg_get_reg(CLK_HOSTUSBCMN_480_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_DIV_SHIFT, CLK_HOSTUSBCMN_480_DIV_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSBCMN_480_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_OSC_SW_CLK_OSC_DATA, CLK_HOSTUSBCMN_480_OSC_SW_SHIFT, CLK_HOSTUSBCMN_480_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_HOSTUSBCMN_480_OSC_SOURCE_CLK_HOSTUSBCMN_480_ 	itg_set_reg(CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_OSC_SW_CLK_HOSTUSBCMN_480_DATA, CLK_HOSTUSBCMN_480_OSC_SW_SHIFT, CLK_HOSTUSBCMN_480_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_HOSTUSBCMN_480_OSC_ 		itg_get_reg(CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR, CLK_HOSTUSBCMN_480_OSC_SW_SHIFT, CLK_HOSTUSBCMN_480_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_HOSTUSBCMN_480_OSC_(x) 		itg_set_reg(CLK_HOSTUSBCMN_480_OSC_CTRL_REG_ADDR, x, CLK_HOSTUSBCMN_480_OSC_SW_SHIFT, CLK_HOSTUSBCMN_480_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_SEC_600_ 			itg_set_reg(CLK_SEC_600_CTRL_REG_ADDR, CLK_SEC_600_ENABLE_DATA, CLK_SEC_600_EN_SHIFT, CLK_SEC_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_SEC_600_ 			itg_set_reg(CLK_SEC_600_CTRL_REG_ADDR, CLK_SEC_600_DISABLE_DATA, CLK_SEC_600_EN_SHIFT, CLK_SEC_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_SEC_600_ 		itg_get_reg(CLK_SEC_600_CTRL_REG_ADDR, CLK_SEC_600_EN_SHIFT, CLK_SEC_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_SEC_600_(x) 		itg_set_reg(CLK_SEC_600_CTRL_REG_ADDR, x, CLK_SEC_600_EN_SHIFT, CLK_SEC_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_SEC_600_(div) 			itg_set_reg(CLK_SEC_600_CTRL_REG_ADDR, div, CLK_SEC_600_DIV_SHIFT, CLK_SEC_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_SEC_600_ 		itg_get_reg(CLK_SEC_600_CTRL_REG_ADDR, CLK_SEC_600_DIV_SHIFT, CLK_SEC_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_SEC_DATA_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_SEC_DATA_INIT_CTRL_REG_ADDR, CLK_SEC_DATA_INIT_SW_CLK_OSC_DATA, CLK_SEC_DATA_INIT_SW_SHIFT, CLK_SEC_DATA_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_SEC_DATA_INIT_SOURCE_CLK_SEC_600_ 	itg_set_reg(CLK_SEC_DATA_INIT_CTRL_REG_ADDR, CLK_SEC_DATA_INIT_SW_CLK_SEC_600_DATA, CLK_SEC_DATA_INIT_SW_SHIFT, CLK_SEC_DATA_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_SEC_DATA_INIT_ 		itg_get_reg(CLK_SEC_DATA_INIT_CTRL_REG_ADDR, CLK_SEC_DATA_INIT_SW_SHIFT, CLK_SEC_DATA_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_SEC_DATA_INIT_(x) 		itg_set_reg(CLK_SEC_DATA_INIT_CTRL_REG_ADDR, x, CLK_SEC_DATA_INIT_SW_SHIFT, CLK_SEC_DATA_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_SEC_200_ 			itg_set_reg(CLK_SEC_200_CTRL_REG_ADDR, CLK_SEC_200_ENABLE_DATA, CLK_SEC_200_EN_SHIFT, CLK_SEC_200_EN_MASK)
#define _DISABLE_CLOCK_CLK_SEC_200_ 			itg_set_reg(CLK_SEC_200_CTRL_REG_ADDR, CLK_SEC_200_DISABLE_DATA, CLK_SEC_200_EN_SHIFT, CLK_SEC_200_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_SEC_200_ 		itg_get_reg(CLK_SEC_200_CTRL_REG_ADDR, CLK_SEC_200_EN_SHIFT, CLK_SEC_200_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_SEC_200_(x) 		itg_set_reg(CLK_SEC_200_CTRL_REG_ADDR, x, CLK_SEC_200_EN_SHIFT, CLK_SEC_200_EN_MASK)
#define _DIVIDE_CLOCK_CLK_SEC_200_(div) 			itg_set_reg(CLK_SEC_200_CTRL_REG_ADDR, div, CLK_SEC_200_DIV_SHIFT, CLK_SEC_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_SEC_200_ 		itg_get_reg(CLK_SEC_200_CTRL_REG_ADDR, CLK_SEC_200_DIV_SHIFT, CLK_SEC_200_DIV_MASK)
#define _SWITCH_CLOCK_CLK_SEC_CFG_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_SEC_CFG_INIT_CTRL_REG_ADDR, CLK_SEC_CFG_INIT_SW_CLK_OSC_DATA, CLK_SEC_CFG_INIT_SW_SHIFT, CLK_SEC_CFG_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_SEC_CFG_INIT_SOURCE_CLK_SEC_200_ 	itg_set_reg(CLK_SEC_CFG_INIT_CTRL_REG_ADDR, CLK_SEC_CFG_INIT_SW_CLK_SEC_200_DATA, CLK_SEC_CFG_INIT_SW_SHIFT, CLK_SEC_CFG_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_SEC_CFG_INIT_ 		itg_get_reg(CLK_SEC_CFG_INIT_CTRL_REG_ADDR, CLK_SEC_CFG_INIT_SW_SHIFT, CLK_SEC_CFG_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_SEC_CFG_INIT_(x) 		itg_set_reg(CLK_SEC_CFG_INIT_CTRL_REG_ADDR, x, CLK_SEC_CFG_INIT_SW_SHIFT, CLK_SEC_CFG_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_SEC_TARG_ 			itg_set_reg(CLK_SEC_TARG_CTRL_REG_ADDR, CLK_SEC_TARG_ENABLE_DATA, CLK_SEC_TARG_EN_SHIFT, CLK_SEC_TARG_EN_MASK)
#define _DISABLE_CLOCK_CLK_SEC_TARG_ 			itg_set_reg(CLK_SEC_TARG_CTRL_REG_ADDR, CLK_SEC_TARG_DISABLE_DATA, CLK_SEC_TARG_EN_SHIFT, CLK_SEC_TARG_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_SEC_TARG_ 		itg_get_reg(CLK_SEC_TARG_CTRL_REG_ADDR, CLK_SEC_TARG_EN_SHIFT, CLK_SEC_TARG_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_SEC_TARG_(x) 		itg_set_reg(CLK_SEC_TARG_CTRL_REG_ADDR, x, CLK_SEC_TARG_EN_SHIFT, CLK_SEC_TARG_EN_MASK)
#define _SWITCH_CLOCK_CLK_SEC_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_SEC_TARG_CTRL_REG_ADDR, CLK_SEC_TARG_SW_CLK_OSC_DATA, CLK_SEC_TARG_SW_SHIFT, CLK_SEC_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_SEC_TARG_SOURCE_CLK_SEC_200_ 	itg_set_reg(CLK_SEC_TARG_CTRL_REG_ADDR, CLK_SEC_TARG_SW_CLK_SEC_200_DATA, CLK_SEC_TARG_SW_SHIFT, CLK_SEC_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_SEC_TARG_ 		itg_get_reg(CLK_SEC_TARG_CTRL_REG_ADDR, CLK_SEC_TARG_SW_SHIFT, CLK_SEC_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_SEC_TARG_(x) 		itg_set_reg(CLK_SEC_TARG_CTRL_REG_ADDR, x, CLK_SEC_TARG_SW_SHIFT, CLK_SEC_TARG_SW_MASK)
#define _DIVIDE_CLOCK_CLK_SEC_TARG_(div) 			itg_set_reg(CLK_SEC_TARG_CTRL_REG_ADDR, div, CLK_SEC_TARG_DIV_SHIFT, CLK_SEC_TARG_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_SEC_TARG_ 		itg_get_reg(CLK_SEC_TARG_CTRL_REG_ADDR, CLK_SEC_TARG_DIV_SHIFT, CLK_SEC_TARG_DIV_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER1_600_ 			itg_set_reg(CLK_BMCPER1_600_CTRL_REG_ADDR, CLK_BMCPER1_600_ENABLE_DATA, CLK_BMCPER1_600_EN_SHIFT, CLK_BMCPER1_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER1_600_ 			itg_set_reg(CLK_BMCPER1_600_CTRL_REG_ADDR, CLK_BMCPER1_600_DISABLE_DATA, CLK_BMCPER1_600_EN_SHIFT, CLK_BMCPER1_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_600_ 		itg_get_reg(CLK_BMCPER1_600_CTRL_REG_ADDR, CLK_BMCPER1_600_EN_SHIFT, CLK_BMCPER1_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_600_(x) 		itg_set_reg(CLK_BMCPER1_600_CTRL_REG_ADDR, x, CLK_BMCPER1_600_EN_SHIFT, CLK_BMCPER1_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_600_(div) 			itg_set_reg(CLK_BMCPER1_600_CTRL_REG_ADDR, div, CLK_BMCPER1_600_DIV_SHIFT, CLK_BMCPER1_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_600_ 		itg_get_reg(CLK_BMCPER1_600_CTRL_REG_ADDR, CLK_BMCPER1_600_DIV_SHIFT, CLK_BMCPER1_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER1_INIT_CTRL_REG_ADDR, CLK_BMCPER1_INIT_SW_CLK_OSC_DATA, CLK_BMCPER1_INIT_SW_SHIFT, CLK_BMCPER1_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_INIT_SOURCE_CLK_BMCPER1_600_ 	itg_set_reg(CLK_BMCPER1_INIT_CTRL_REG_ADDR, CLK_BMCPER1_INIT_SW_CLK_BMCPER1_600_DATA, CLK_BMCPER1_INIT_SW_SHIFT, CLK_BMCPER1_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_INIT_ 		itg_get_reg(CLK_BMCPER1_INIT_CTRL_REG_ADDR, CLK_BMCPER1_INIT_SW_SHIFT, CLK_BMCPER1_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_INIT_(x) 		itg_set_reg(CLK_BMCPER1_INIT_CTRL_REG_ADDR, x, CLK_BMCPER1_INIT_SW_SHIFT, CLK_BMCPER1_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER1_200_ 			itg_set_reg(CLK_BMCPER1_200_CTRL_REG_ADDR, CLK_BMCPER1_200_ENABLE_DATA, CLK_BMCPER1_200_EN_SHIFT, CLK_BMCPER1_200_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER1_200_ 			itg_set_reg(CLK_BMCPER1_200_CTRL_REG_ADDR, CLK_BMCPER1_200_DISABLE_DATA, CLK_BMCPER1_200_EN_SHIFT, CLK_BMCPER1_200_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_200_ 		itg_get_reg(CLK_BMCPER1_200_CTRL_REG_ADDR, CLK_BMCPER1_200_EN_SHIFT, CLK_BMCPER1_200_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_200_(x) 		itg_set_reg(CLK_BMCPER1_200_CTRL_REG_ADDR, x, CLK_BMCPER1_200_EN_SHIFT, CLK_BMCPER1_200_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_200_(div) 			itg_set_reg(CLK_BMCPER1_200_CTRL_REG_ADDR, div, CLK_BMCPER1_200_DIV_SHIFT, CLK_BMCPER1_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_200_ 		itg_get_reg(CLK_BMCPER1_200_CTRL_REG_ADDR, CLK_BMCPER1_200_DIV_SHIFT, CLK_BMCPER1_200_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER1_TARG_CTRL_REG_ADDR, CLK_BMCPER1_TARG_SW_CLK_OSC_DATA, CLK_BMCPER1_TARG_SW_SHIFT, CLK_BMCPER1_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_TARG_SOURCE_CLK_BMCPER1_200_ 	itg_set_reg(CLK_BMCPER1_TARG_CTRL_REG_ADDR, CLK_BMCPER1_TARG_SW_CLK_BMCPER1_200_DATA, CLK_BMCPER1_TARG_SW_SHIFT, CLK_BMCPER1_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_TARG_ 		itg_get_reg(CLK_BMCPER1_TARG_CTRL_REG_ADDR, CLK_BMCPER1_TARG_SW_SHIFT, CLK_BMCPER1_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_TARG_(x) 		itg_set_reg(CLK_BMCPER1_TARG_CTRL_REG_ADDR, x, CLK_BMCPER1_TARG_SW_SHIFT, CLK_BMCPER1_TARG_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER1_400_ 			itg_set_reg(CLK_BMCPER1_400_CTRL_REG_ADDR, CLK_BMCPER1_400_ENABLE_DATA, CLK_BMCPER1_400_EN_SHIFT, CLK_BMCPER1_400_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER1_400_ 			itg_set_reg(CLK_BMCPER1_400_CTRL_REG_ADDR, CLK_BMCPER1_400_DISABLE_DATA, CLK_BMCPER1_400_EN_SHIFT, CLK_BMCPER1_400_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_400_ 		itg_get_reg(CLK_BMCPER1_400_CTRL_REG_ADDR, CLK_BMCPER1_400_EN_SHIFT, CLK_BMCPER1_400_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_400_(x) 		itg_set_reg(CLK_BMCPER1_400_CTRL_REG_ADDR, x, CLK_BMCPER1_400_EN_SHIFT, CLK_BMCPER1_400_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_400_(div) 			itg_set_reg(CLK_BMCPER1_400_CTRL_REG_ADDR, div, CLK_BMCPER1_400_DIV_SHIFT, CLK_BMCPER1_400_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_400_ 		itg_get_reg(CLK_BMCPER1_400_CTRL_REG_ADDR, CLK_BMCPER1_400_DIV_SHIFT, CLK_BMCPER1_400_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_400_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER1_400_OSC_CTRL_REG_ADDR, CLK_BMCPER1_400_OSC_SW_CLK_OSC_DATA, CLK_BMCPER1_400_OSC_SW_SHIFT, CLK_BMCPER1_400_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_400_OSC_SOURCE_CLK_BMCPER1_400_ 	itg_set_reg(CLK_BMCPER1_400_OSC_CTRL_REG_ADDR, CLK_BMCPER1_400_OSC_SW_CLK_BMCPER1_400_DATA, CLK_BMCPER1_400_OSC_SW_SHIFT, CLK_BMCPER1_400_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_400_OSC_ 		itg_get_reg(CLK_BMCPER1_400_OSC_CTRL_REG_ADDR, CLK_BMCPER1_400_OSC_SW_SHIFT, CLK_BMCPER1_400_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_400_OSC_(x) 		itg_set_reg(CLK_BMCPER1_400_OSC_CTRL_REG_ADDR, x, CLK_BMCPER1_400_OSC_SW_SHIFT, CLK_BMCPER1_400_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_UFS_REF_ 			itg_set_reg(CLK_UFS_REF_CTRL_REG_ADDR, CLK_UFS_REF_ENABLE_DATA, CLK_UFS_REF_EN_SHIFT, CLK_UFS_REF_EN_MASK)
#define _DISABLE_CLOCK_CLK_UFS_REF_ 			itg_set_reg(CLK_UFS_REF_CTRL_REG_ADDR, CLK_UFS_REF_DISABLE_DATA, CLK_UFS_REF_EN_SHIFT, CLK_UFS_REF_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_UFS_REF_ 		itg_get_reg(CLK_UFS_REF_CTRL_REG_ADDR, CLK_UFS_REF_EN_SHIFT, CLK_UFS_REF_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_UFS_REF_(x) 		itg_set_reg(CLK_UFS_REF_CTRL_REG_ADDR, x, CLK_UFS_REF_EN_SHIFT, CLK_UFS_REF_EN_MASK)
#define _DIVIDE_CLOCK_CLK_UFS_REF_(div) 			itg_set_reg(CLK_UFS_REF_CTRL_REG_ADDR, div, CLK_UFS_REF_DIV_SHIFT, CLK_UFS_REF_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_UFS_REF_ 		itg_get_reg(CLK_UFS_REF_CTRL_REG_ADDR, CLK_UFS_REF_DIV_SHIFT, CLK_UFS_REF_DIV_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER1_250_ 			itg_set_reg(CLK_BMCPER1_250_CTRL_REG_ADDR, CLK_BMCPER1_250_ENABLE_DATA, CLK_BMCPER1_250_EN_SHIFT, CLK_BMCPER1_250_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER1_250_ 			itg_set_reg(CLK_BMCPER1_250_CTRL_REG_ADDR, CLK_BMCPER1_250_DISABLE_DATA, CLK_BMCPER1_250_EN_SHIFT, CLK_BMCPER1_250_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_250_ 		itg_get_reg(CLK_BMCPER1_250_CTRL_REG_ADDR, CLK_BMCPER1_250_EN_SHIFT, CLK_BMCPER1_250_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_250_(x) 		itg_set_reg(CLK_BMCPER1_250_CTRL_REG_ADDR, x, CLK_BMCPER1_250_EN_SHIFT, CLK_BMCPER1_250_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_250_(div) 			itg_set_reg(CLK_BMCPER1_250_CTRL_REG_ADDR, div, CLK_BMCPER1_250_DIV_SHIFT, CLK_BMCPER1_250_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_250_ 		itg_get_reg(CLK_BMCPER1_250_CTRL_REG_ADDR, CLK_BMCPER1_250_DIV_SHIFT, CLK_BMCPER1_250_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_250_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER1_250_OSC_CTRL_REG_ADDR, CLK_BMCPER1_250_OSC_SW_CLK_OSC_DATA, CLK_BMCPER1_250_OSC_SW_SHIFT, CLK_BMCPER1_250_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_250_OSC_SOURCE_CLK_BMCPER1_250_ 	itg_set_reg(CLK_BMCPER1_250_OSC_CTRL_REG_ADDR, CLK_BMCPER1_250_OSC_SW_CLK_BMCPER1_250_DATA, CLK_BMCPER1_250_OSC_SW_SHIFT, CLK_BMCPER1_250_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_250_OSC_ 		itg_get_reg(CLK_BMCPER1_250_OSC_CTRL_REG_ADDR, CLK_BMCPER1_250_OSC_SW_SHIFT, CLK_BMCPER1_250_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_250_OSC_(x) 		itg_set_reg(CLK_BMCPER1_250_OSC_CTRL_REG_ADDR, x, CLK_BMCPER1_250_OSC_SW_SHIFT, CLK_BMCPER1_250_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER1_143_ 			itg_set_reg(CLK_BMCPER1_143_CTRL_REG_ADDR, CLK_BMCPER1_143_ENABLE_DATA, CLK_BMCPER1_143_EN_SHIFT, CLK_BMCPER1_143_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER1_143_ 			itg_set_reg(CLK_BMCPER1_143_CTRL_REG_ADDR, CLK_BMCPER1_143_DISABLE_DATA, CLK_BMCPER1_143_EN_SHIFT, CLK_BMCPER1_143_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_143_ 		itg_get_reg(CLK_BMCPER1_143_CTRL_REG_ADDR, CLK_BMCPER1_143_EN_SHIFT, CLK_BMCPER1_143_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_143_(x) 		itg_set_reg(CLK_BMCPER1_143_CTRL_REG_ADDR, x, CLK_BMCPER1_143_EN_SHIFT, CLK_BMCPER1_143_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_143_(div) 			itg_set_reg(CLK_BMCPER1_143_CTRL_REG_ADDR, div, CLK_BMCPER1_143_DIV_SHIFT, CLK_BMCPER1_143_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_143_ 		itg_get_reg(CLK_BMCPER1_143_CTRL_REG_ADDR, CLK_BMCPER1_143_DIV_SHIFT, CLK_BMCPER1_143_DIV_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER1_800_ 			itg_set_reg(CLK_BMCPER1_800_CTRL_REG_ADDR, CLK_BMCPER1_800_ENABLE_DATA, CLK_BMCPER1_800_EN_SHIFT, CLK_BMCPER1_800_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER1_800_ 			itg_set_reg(CLK_BMCPER1_800_CTRL_REG_ADDR, CLK_BMCPER1_800_DISABLE_DATA, CLK_BMCPER1_800_EN_SHIFT, CLK_BMCPER1_800_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_800_ 		itg_get_reg(CLK_BMCPER1_800_CTRL_REG_ADDR, CLK_BMCPER1_800_EN_SHIFT, CLK_BMCPER1_800_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER1_800_(x) 		itg_set_reg(CLK_BMCPER1_800_CTRL_REG_ADDR, x, CLK_BMCPER1_800_EN_SHIFT, CLK_BMCPER1_800_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER1_800_(div) 			itg_set_reg(CLK_BMCPER1_800_CTRL_REG_ADDR, div, CLK_BMCPER1_800_DIV_SHIFT, CLK_BMCPER1_800_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER1_800_ 		itg_get_reg(CLK_BMCPER1_800_CTRL_REG_ADDR, CLK_BMCPER1_800_DIV_SHIFT, CLK_BMCPER1_800_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_800_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER1_800_OSC_CTRL_REG_ADDR, CLK_BMCPER1_800_OSC_SW_CLK_OSC_DATA, CLK_BMCPER1_800_OSC_SW_SHIFT, CLK_BMCPER1_800_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER1_800_OSC_SOURCE_CLK_BMCPER1_800_ 	itg_set_reg(CLK_BMCPER1_800_OSC_CTRL_REG_ADDR, CLK_BMCPER1_800_OSC_SW_CLK_BMCPER1_800_DATA, CLK_BMCPER1_800_OSC_SW_SHIFT, CLK_BMCPER1_800_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_800_OSC_ 		itg_get_reg(CLK_BMCPER1_800_OSC_CTRL_REG_ADDR, CLK_BMCPER1_800_OSC_SW_SHIFT, CLK_BMCPER1_800_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER1_800_OSC_(x) 		itg_set_reg(CLK_BMCPER1_800_OSC_CTRL_REG_ADDR, x, CLK_BMCPER1_800_OSC_SW_SHIFT, CLK_BMCPER1_800_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER0_600_ 			itg_set_reg(CLK_BMCPER0_600_CTRL_REG_ADDR, CLK_BMCPER0_600_ENABLE_DATA, CLK_BMCPER0_600_EN_SHIFT, CLK_BMCPER0_600_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER0_600_ 			itg_set_reg(CLK_BMCPER0_600_CTRL_REG_ADDR, CLK_BMCPER0_600_DISABLE_DATA, CLK_BMCPER0_600_EN_SHIFT, CLK_BMCPER0_600_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_600_ 		itg_get_reg(CLK_BMCPER0_600_CTRL_REG_ADDR, CLK_BMCPER0_600_EN_SHIFT, CLK_BMCPER0_600_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_600_(x) 		itg_set_reg(CLK_BMCPER0_600_CTRL_REG_ADDR, x, CLK_BMCPER0_600_EN_SHIFT, CLK_BMCPER0_600_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER0_600_(div) 			itg_set_reg(CLK_BMCPER0_600_CTRL_REG_ADDR, div, CLK_BMCPER0_600_DIV_SHIFT, CLK_BMCPER0_600_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER0_600_ 		itg_get_reg(CLK_BMCPER0_600_CTRL_REG_ADDR, CLK_BMCPER0_600_DIV_SHIFT, CLK_BMCPER0_600_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_INIT_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER0_INIT_CTRL_REG_ADDR, CLK_BMCPER0_INIT_SW_CLK_OSC_DATA, CLK_BMCPER0_INIT_SW_SHIFT, CLK_BMCPER0_INIT_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_INIT_SOURCE_CLK_BMCPER0_600_ 	itg_set_reg(CLK_BMCPER0_INIT_CTRL_REG_ADDR, CLK_BMCPER0_INIT_SW_CLK_BMCPER0_600_DATA, CLK_BMCPER0_INIT_SW_SHIFT, CLK_BMCPER0_INIT_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_INIT_ 		itg_get_reg(CLK_BMCPER0_INIT_CTRL_REG_ADDR, CLK_BMCPER0_INIT_SW_SHIFT, CLK_BMCPER0_INIT_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_INIT_(x) 		itg_set_reg(CLK_BMCPER0_INIT_CTRL_REG_ADDR, x, CLK_BMCPER0_INIT_SW_SHIFT, CLK_BMCPER0_INIT_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER0_200_ 			itg_set_reg(CLK_BMCPER0_200_CTRL_REG_ADDR, CLK_BMCPER0_200_ENABLE_DATA, CLK_BMCPER0_200_EN_SHIFT, CLK_BMCPER0_200_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER0_200_ 			itg_set_reg(CLK_BMCPER0_200_CTRL_REG_ADDR, CLK_BMCPER0_200_DISABLE_DATA, CLK_BMCPER0_200_EN_SHIFT, CLK_BMCPER0_200_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_200_ 		itg_get_reg(CLK_BMCPER0_200_CTRL_REG_ADDR, CLK_BMCPER0_200_EN_SHIFT, CLK_BMCPER0_200_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_200_(x) 		itg_set_reg(CLK_BMCPER0_200_CTRL_REG_ADDR, x, CLK_BMCPER0_200_EN_SHIFT, CLK_BMCPER0_200_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER0_200_(div) 			itg_set_reg(CLK_BMCPER0_200_CTRL_REG_ADDR, div, CLK_BMCPER0_200_DIV_SHIFT, CLK_BMCPER0_200_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER0_200_ 		itg_get_reg(CLK_BMCPER0_200_CTRL_REG_ADDR, CLK_BMCPER0_200_DIV_SHIFT, CLK_BMCPER0_200_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_TARG_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER0_TARG_CTRL_REG_ADDR, CLK_BMCPER0_TARG_SW_CLK_OSC_DATA, CLK_BMCPER0_TARG_SW_SHIFT, CLK_BMCPER0_TARG_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_TARG_SOURCE_CLK_BMCPER0_200_ 	itg_set_reg(CLK_BMCPER0_TARG_CTRL_REG_ADDR, CLK_BMCPER0_TARG_SW_CLK_BMCPER0_200_DATA, CLK_BMCPER0_TARG_SW_SHIFT, CLK_BMCPER0_TARG_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_TARG_ 		itg_get_reg(CLK_BMCPER0_TARG_CTRL_REG_ADDR, CLK_BMCPER0_TARG_SW_SHIFT, CLK_BMCPER0_TARG_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_TARG_(x) 		itg_set_reg(CLK_BMCPER0_TARG_CTRL_REG_ADDR, x, CLK_BMCPER0_TARG_SW_SHIFT, CLK_BMCPER0_TARG_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER0_400_ 			itg_set_reg(CLK_BMCPER0_400_CTRL_REG_ADDR, CLK_BMCPER0_400_ENABLE_DATA, CLK_BMCPER0_400_EN_SHIFT, CLK_BMCPER0_400_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER0_400_ 			itg_set_reg(CLK_BMCPER0_400_CTRL_REG_ADDR, CLK_BMCPER0_400_DISABLE_DATA, CLK_BMCPER0_400_EN_SHIFT, CLK_BMCPER0_400_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_400_ 		itg_get_reg(CLK_BMCPER0_400_CTRL_REG_ADDR, CLK_BMCPER0_400_EN_SHIFT, CLK_BMCPER0_400_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_400_(x) 		itg_set_reg(CLK_BMCPER0_400_CTRL_REG_ADDR, x, CLK_BMCPER0_400_EN_SHIFT, CLK_BMCPER0_400_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER0_400_(div) 			itg_set_reg(CLK_BMCPER0_400_CTRL_REG_ADDR, div, CLK_BMCPER0_400_DIV_SHIFT, CLK_BMCPER0_400_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER0_400_ 		itg_get_reg(CLK_BMCPER0_400_CTRL_REG_ADDR, CLK_BMCPER0_400_DIV_SHIFT, CLK_BMCPER0_400_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_400_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER0_400_OSC_CTRL_REG_ADDR, CLK_BMCPER0_400_OSC_SW_CLK_OSC_DATA, CLK_BMCPER0_400_OSC_SW_SHIFT, CLK_BMCPER0_400_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_400_OSC_SOURCE_CLK_BMCPER0_400_ 	itg_set_reg(CLK_BMCPER0_400_OSC_CTRL_REG_ADDR, CLK_BMCPER0_400_OSC_SW_CLK_BMCPER0_400_DATA, CLK_BMCPER0_400_OSC_SW_SHIFT, CLK_BMCPER0_400_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_400_OSC_ 		itg_get_reg(CLK_BMCPER0_400_OSC_CTRL_REG_ADDR, CLK_BMCPER0_400_OSC_SW_SHIFT, CLK_BMCPER0_400_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_400_OSC_(x) 		itg_set_reg(CLK_BMCPER0_400_OSC_CTRL_REG_ADDR, x, CLK_BMCPER0_400_OSC_SW_SHIFT, CLK_BMCPER0_400_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER0_125_ 			itg_set_reg(CLK_BMCPER0_125_CTRL_REG_ADDR, CLK_BMCPER0_125_ENABLE_DATA, CLK_BMCPER0_125_EN_SHIFT, CLK_BMCPER0_125_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER0_125_ 			itg_set_reg(CLK_BMCPER0_125_CTRL_REG_ADDR, CLK_BMCPER0_125_DISABLE_DATA, CLK_BMCPER0_125_EN_SHIFT, CLK_BMCPER0_125_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_125_ 		itg_get_reg(CLK_BMCPER0_125_CTRL_REG_ADDR, CLK_BMCPER0_125_EN_SHIFT, CLK_BMCPER0_125_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_125_(x) 		itg_set_reg(CLK_BMCPER0_125_CTRL_REG_ADDR, x, CLK_BMCPER0_125_EN_SHIFT, CLK_BMCPER0_125_EN_MASK)
#define _DIVIDE_CLOCK_CLK_BMCPER0_125_(div) 			itg_set_reg(CLK_BMCPER0_125_CTRL_REG_ADDR, div, CLK_BMCPER0_125_DIV_SHIFT, CLK_BMCPER0_125_DIV_MASK)
#define _GET_CLOCK_DIVIDE_STATUS_CLK_BMCPER0_125_ 		itg_get_reg(CLK_BMCPER0_125_CTRL_REG_ADDR, CLK_BMCPER0_125_DIV_SHIFT, CLK_BMCPER0_125_DIV_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_125_OSC_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER0_125_OSC_CTRL_REG_ADDR, CLK_BMCPER0_125_OSC_SW_CLK_OSC_DATA, CLK_BMCPER0_125_OSC_SW_SHIFT, CLK_BMCPER0_125_OSC_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_125_OSC_SOURCE_CLK_BMCPER0_125_ 	itg_set_reg(CLK_BMCPER0_125_OSC_CTRL_REG_ADDR, CLK_BMCPER0_125_OSC_SW_CLK_BMCPER0_125_DATA, CLK_BMCPER0_125_OSC_SW_SHIFT, CLK_BMCPER0_125_OSC_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_125_OSC_ 		itg_get_reg(CLK_BMCPER0_125_OSC_CTRL_REG_ADDR, CLK_BMCPER0_125_OSC_SW_SHIFT, CLK_BMCPER0_125_OSC_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_125_OSC_(x) 		itg_set_reg(CLK_BMCPER0_125_OSC_CTRL_REG_ADDR, x, CLK_BMCPER0_125_OSC_SW_SHIFT, CLK_BMCPER0_125_OSC_SW_MASK)
#define _ENABLE_CLOCK_CLK_BMCPER0_PLL6_ 			itg_set_reg(CLK_BMCPER0_PLL6_CTRL_REG_ADDR, CLK_BMCPER0_PLL6_ENABLE_DATA, CLK_BMCPER0_PLL6_EN_SHIFT, CLK_BMCPER0_PLL6_EN_MASK)
#define _DISABLE_CLOCK_CLK_BMCPER0_PLL6_ 			itg_set_reg(CLK_BMCPER0_PLL6_CTRL_REG_ADDR, CLK_BMCPER0_PLL6_DISABLE_DATA, CLK_BMCPER0_PLL6_EN_SHIFT, CLK_BMCPER0_PLL6_EN_MASK)
#define _GET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_PLL6_ 		itg_get_reg(CLK_BMCPER0_PLL6_CTRL_REG_ADDR, CLK_BMCPER0_PLL6_EN_SHIFT, CLK_BMCPER0_PLL6_EN_MASK)
#define _SET_CLOCK_ENABLE_STATUS_CLK_BMCPER0_PLL6_(x) 		itg_set_reg(CLK_BMCPER0_PLL6_CTRL_REG_ADDR, x, CLK_BMCPER0_PLL6_EN_SHIFT, CLK_BMCPER0_PLL6_EN_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_PLL6_SOURCE_CLK_OSC_ 	itg_set_reg(CLK_BMCPER0_PLL6_CTRL_REG_ADDR, CLK_BMCPER0_PLL6_SW_CLK_OSC_DATA, CLK_BMCPER0_PLL6_SW_SHIFT, CLK_BMCPER0_PLL6_SW_MASK)
#define _SWITCH_CLOCK_CLK_BMCPER0_PLL6_SOURCE_CLK_PLL6_ 	itg_set_reg(CLK_BMCPER0_PLL6_CTRL_REG_ADDR, CLK_BMCPER0_PLL6_SW_CLK_PLL6_DATA, CLK_BMCPER0_PLL6_SW_SHIFT, CLK_BMCPER0_PLL6_SW_MASK)
#define _GET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_PLL6_ 		itg_get_reg(CLK_BMCPER0_PLL6_CTRL_REG_ADDR, CLK_BMCPER0_PLL6_SW_SHIFT, CLK_BMCPER0_PLL6_SW_MASK)
#define _SET_CLOCK_SOURCE_STATUS_CLK_BMCPER0_PLL6_(x) 		itg_set_reg(CLK_BMCPER0_PLL6_CTRL_REG_ADDR, x, CLK_BMCPER0_PLL6_SW_SHIFT, CLK_BMCPER0_PLL6_SW_MASK)



#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_SYS2_SYSCON_PRESETN_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS2_SYSCON_PRESETN_SHIFT, RSTN_U0_SYS2_SYSCON_PRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_SYS2_SYSCON_PRESETN_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS2_SYSCON_PRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_SYS2_SYSCON_PRESETN_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_SYS2_SYSCON_PRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_SHIFT, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_NCNOC_SYSTOP_RSTN_CSR2_MASK)
#define _READ_RESET_STATUS_RSTGEN_MAIN_RSTN_SYS2_IOMUX_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_SYS2_IOMUX_SHIFT, MAIN_RSTN_SYS2_IOMUX_MASK)
#define _ASSERT_RESET_RSTGEN_MAIN_RSTN_SYS2_IOMUX_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_SYS2_IOMUX_MASK)
#define _CLEAR_RESET_RSTGEN_MAIN_RSTN_SYS2_IOMUX_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, MAIN_RSTN_SYS2_IOMUX_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_JTAG_MST_WRAP_HRESETN_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_JTAG_MST_WRAP_HRESETN_SHIFT, RSTN_U0_JTAG_MST_WRAP_HRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_JTAG_MST_WRAP_HRESETN_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_JTAG_MST_WRAP_HRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_JTAG_MST_WRAP_HRESETN_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_JTAG_MST_WRAP_HRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_SHIFT, RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U0_JTAG_MST_WRAP_APB_PRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U1_JTAG_MST_WRAP_HRESETN_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_JTAG_MST_WRAP_HRESETN_SHIFT, RSTN_U1_JTAG_MST_WRAP_HRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U1_JTAG_MST_WRAP_HRESETN_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_JTAG_MST_WRAP_HRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U1_JTAG_MST_WRAP_HRESETN_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_JTAG_MST_WRAP_HRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_SHIFT, RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U1_JTAG_MST_WRAP_APB_PRESETN_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U4_PCU_CORE_RST_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U4_PCU_CORE_RST_SHIFT, RSTN_U4_PCU_CORE_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U4_PCU_CORE_RST_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U4_PCU_CORE_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U4_PCU_CORE_RST_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U4_PCU_CORE_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U4_PCU_APB_RST_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U4_PCU_APB_RST_SHIFT, RSTN_U4_PCU_APB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U4_PCU_APB_RST_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U4_PCU_APB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U4_PCU_APB_RST_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U4_PCU_APB_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U5_PCU_CORE_RST_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U5_PCU_CORE_RST_SHIFT, RSTN_U5_PCU_CORE_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U5_PCU_CORE_RST_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U5_PCU_CORE_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U5_PCU_CORE_RST_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U5_PCU_CORE_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U5_PCU_APB_RST_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U5_PCU_APB_RST_SHIFT, RSTN_U5_PCU_APB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U5_PCU_APB_RST_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U5_PCU_APB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U5_PCU_APB_RST_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U5_PCU_APB_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U10_PCU_CORE_RST_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U10_PCU_CORE_RST_SHIFT, RSTN_U10_PCU_CORE_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U10_PCU_CORE_RST_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U10_PCU_CORE_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U10_PCU_CORE_RST_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U10_PCU_CORE_RST_MASK)
#define _READ_RESET_STATUS_RSTGEN_RSTN_U10_PCU_APB_RST_ 	itg_get_reg(SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U10_PCU_APB_RST_SHIFT, RSTN_U10_PCU_APB_RST_MASK)
#define _ASSERT_RESET_RSTGEN_RSTN_U10_PCU_APB_RST_ 	itg_assert_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U10_PCU_APB_RST_MASK)
#define _CLEAR_RESET_RSTGEN_RSTN_U10_PCU_APB_RST_ 	itg_clear_rst(SYS2_CRG_RSTGEN_SOFTWARE_RESET_ASSERT0_REG_ADDR, SYS2_CRG_RSTGEN_SOFTWARE_RESET_STATUS0_REG_ADDR, RSTN_U10_PCU_APB_RST_MASK)


#endif //_SYS2_CRG_MACRO_H_
