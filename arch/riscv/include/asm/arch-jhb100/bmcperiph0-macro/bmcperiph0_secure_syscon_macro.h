//commit:06b6362e (HEAD -> b0.8.1_dv, origin/b0.8.1_dv)
#define BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_0_ADDR         (U0_BMCPERIPH0_SECURE_SYSCON__ITG_BD_APBS__BASE_ADDR + 0x0U)
#define U8_DWC_SENSORS_PD_WR_LOCK_WIDTH                    0x1U
#define U8_DWC_SENSORS_PD_WR_LOCK_SHIFT                    0x0U
#define U8_DWC_SENSORS_PD_WR_LOCK_MASK                     0x1U
#define BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_4_ADDR         (U0_BMCPERIPH0_SECURE_SYSCON__ITG_BD_APBS__BASE_ADDR + 0x4U)
#define U0_WDT_WDT_CLK_EN_I_WIDTH                          0x1U
#define U0_WDT_WDT_CLK_EN_I_SHIFT                          0x0U
#define U0_WDT_WDT_CLK_EN_I_MASK                           0x1U
#define U0_WDT_WDT_PAUSE_I_WIDTH                           0x1U
#define U0_WDT_WDT_PAUSE_I_SHIFT                           0x1U
#define U0_WDT_WDT_PAUSE_I_MASK                            0x2U
#define BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_8_ADDR         (U0_BMCPERIPH0_SECURE_SYSCON__ITG_BD_APBS__BASE_ADDR + 0x8U)
#define U1_WDT_WDT_CLK_EN_I_WIDTH                          0x1U
#define U1_WDT_WDT_CLK_EN_I_SHIFT                          0x0U
#define U1_WDT_WDT_CLK_EN_I_MASK                           0x1U
#define U1_WDT_WDT_PAUSE_I_WIDTH                           0x1U
#define U1_WDT_WDT_PAUSE_I_SHIFT                           0x1U
#define U1_WDT_WDT_PAUSE_I_MASK                            0x2U
#define BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_12_ADDR        (U0_BMCPERIPH0_SECURE_SYSCON__ITG_BD_APBS__BASE_ADDR + 0xcU)
#define U2_WDT_WDT_CLK_EN_I_WIDTH                          0x1U
#define U2_WDT_WDT_CLK_EN_I_SHIFT                          0x0U
#define U2_WDT_WDT_CLK_EN_I_MASK                           0x1U
#define U2_WDT_WDT_PAUSE_I_WIDTH                           0x1U
#define U2_WDT_WDT_PAUSE_I_SHIFT                           0x1U
#define U2_WDT_WDT_PAUSE_I_MASK                            0x2U
#define BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_16_ADDR        (U0_BMCPERIPH0_SECURE_SYSCON__ITG_BD_APBS__BASE_ADDR + 0x10U)
#define U3_WDT_WDT_CLK_EN_I_WIDTH                          0x1U
#define U3_WDT_WDT_CLK_EN_I_SHIFT                          0x0U
#define U3_WDT_WDT_CLK_EN_I_MASK                           0x1U
#define U3_WDT_WDT_PAUSE_I_WIDTH                           0x1U
#define U3_WDT_WDT_PAUSE_I_SHIFT                           0x1U
#define U3_WDT_WDT_PAUSE_I_MASK                            0x2U
#define BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_20_ADDR        (U0_BMCPERIPH0_SECURE_SYSCON__ITG_BD_APBS__BASE_ADDR + 0x14U)
#define U4_WDT_WDT_CLK_EN_I_WIDTH                          0x1U
#define U4_WDT_WDT_CLK_EN_I_SHIFT                          0x0U
#define U4_WDT_WDT_CLK_EN_I_MASK                           0x1U
#define U4_WDT_WDT_PAUSE_I_WIDTH                           0x1U
#define U4_WDT_WDT_PAUSE_I_SHIFT                           0x1U
#define U4_WDT_WDT_PAUSE_I_MASK                            0x2U
#define GET_U8_DWC_SENSORS_PD_WR_LOCK                      itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_0_ADDR,U8_DWC_SENSORS_PD_WR_LOCK_SHIFT,U8_DWC_SENSORS_PD_WR_LOCK_MASK)
#define SET_U8_DWC_SENSORS_PD_WR_LOCK(data)                itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_0_ADDR,data,U8_DWC_SENSORS_PD_WR_LOCK_SHIFT,U8_DWC_SENSORS_PD_WR_LOCK_MASK)
#define GET_U0_WDT_WDT_CLK_EN_I                            itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_4_ADDR,U0_WDT_WDT_CLK_EN_I_SHIFT,U0_WDT_WDT_CLK_EN_I_MASK)
#define SET_U0_WDT_WDT_CLK_EN_I(data)                      itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_4_ADDR,data,U0_WDT_WDT_CLK_EN_I_SHIFT,U0_WDT_WDT_CLK_EN_I_MASK)
#define GET_U0_WDT_WDT_PAUSE_I                             itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_4_ADDR,U0_WDT_WDT_PAUSE_I_SHIFT,U0_WDT_WDT_PAUSE_I_MASK)
#define SET_U0_WDT_WDT_PAUSE_I(data)                       itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_4_ADDR,data,U0_WDT_WDT_PAUSE_I_SHIFT,U0_WDT_WDT_PAUSE_I_MASK)
#define GET_U1_WDT_WDT_CLK_EN_I                            itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_8_ADDR,U1_WDT_WDT_CLK_EN_I_SHIFT,U1_WDT_WDT_CLK_EN_I_MASK)
#define SET_U1_WDT_WDT_CLK_EN_I(data)                      itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_8_ADDR,data,U1_WDT_WDT_CLK_EN_I_SHIFT,U1_WDT_WDT_CLK_EN_I_MASK)
#define GET_U1_WDT_WDT_PAUSE_I                             itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_8_ADDR,U1_WDT_WDT_PAUSE_I_SHIFT,U1_WDT_WDT_PAUSE_I_MASK)
#define SET_U1_WDT_WDT_PAUSE_I(data)                       itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_8_ADDR,data,U1_WDT_WDT_PAUSE_I_SHIFT,U1_WDT_WDT_PAUSE_I_MASK)
#define GET_U2_WDT_WDT_CLK_EN_I                            itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_12_ADDR,U2_WDT_WDT_CLK_EN_I_SHIFT,U2_WDT_WDT_CLK_EN_I_MASK)
#define SET_U2_WDT_WDT_CLK_EN_I(data)                      itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_12_ADDR,data,U2_WDT_WDT_CLK_EN_I_SHIFT,U2_WDT_WDT_CLK_EN_I_MASK)
#define GET_U2_WDT_WDT_PAUSE_I                             itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_12_ADDR,U2_WDT_WDT_PAUSE_I_SHIFT,U2_WDT_WDT_PAUSE_I_MASK)
#define SET_U2_WDT_WDT_PAUSE_I(data)                       itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_12_ADDR,data,U2_WDT_WDT_PAUSE_I_SHIFT,U2_WDT_WDT_PAUSE_I_MASK)
#define GET_U3_WDT_WDT_CLK_EN_I                            itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_16_ADDR,U3_WDT_WDT_CLK_EN_I_SHIFT,U3_WDT_WDT_CLK_EN_I_MASK)
#define SET_U3_WDT_WDT_CLK_EN_I(data)                      itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_16_ADDR,data,U3_WDT_WDT_CLK_EN_I_SHIFT,U3_WDT_WDT_CLK_EN_I_MASK)
#define GET_U3_WDT_WDT_PAUSE_I                             itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_16_ADDR,U3_WDT_WDT_PAUSE_I_SHIFT,U3_WDT_WDT_PAUSE_I_MASK)
#define SET_U3_WDT_WDT_PAUSE_I(data)                       itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_16_ADDR,data,U3_WDT_WDT_PAUSE_I_SHIFT,U3_WDT_WDT_PAUSE_I_MASK)
#define GET_U4_WDT_WDT_CLK_EN_I                            itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_20_ADDR,U4_WDT_WDT_CLK_EN_I_SHIFT,U4_WDT_WDT_CLK_EN_I_MASK)
#define SET_U4_WDT_WDT_CLK_EN_I(data)                      itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_20_ADDR,data,U4_WDT_WDT_CLK_EN_I_SHIFT,U4_WDT_WDT_CLK_EN_I_MASK)
#define GET_U4_WDT_WDT_PAUSE_I                             itg_get_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_20_ADDR,U4_WDT_WDT_PAUSE_I_SHIFT,U4_WDT_WDT_PAUSE_I_MASK)
#define SET_U4_WDT_WDT_PAUSE_I(data)                       itg_set_reg(BMCPERIPH0_SECURE_SYSCONITG__SYSCFG_20_ADDR,data,U4_WDT_WDT_PAUSE_I_SHIFT,U4_WDT_WDT_PAUSE_I_MASK)
