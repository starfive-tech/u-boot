
#ifndef _SAIF_INIT_H_
#define _SAIF_INIT_H_

#include <asm/arch/plat_macro.h>
#include <asm/arch/bmcperiph0-macro/bmcperiph0_gpio_iomux_cfg_macro.h>
#include <asm/arch/bmcperiph0-macro/bmcperiph0_syscon_macro.h>
#include <asm/arch/bmcperiph0-macro/bmcperiph0_crg_macro.h>
#include <asm/arch/bmcperiph0-macro/dom_bmcperiph0_mem_map.h>
#include <asm/arch/bmcperiph0-macro/bmcperiph0_crg_macro.h>
#include <asm/arch/bmcperiph1-macro/bmcperiph1_crg_macro.h>
#include <asm/arch/bmcperiph1-macro/dom_bmcperiph1_mem_map.h>
#include <asm/arch/bmcperiph1-macro/bmcperiph1_iomux_cfg_macro.h>
#include <asm/arch/bmcperiph2-macro/bmcperiph2_crg_macro.h>
#include <asm/arch/bmcperiph2-macro/bmcperiph2_iomux_cfg_macro.h>
#include <asm/arch/bmcperiph2-macro/dom_bmcperiph2_mem_map.h>
#include <asm/arch/sys-macro/chip_top_mem_map.h>
#include <asm/arch/sys-macro/sys2_iomux_cfg_macro.h>
#include <asm/arch/sys-macro/sys2_crg_macro.h>
#include <asm/arch/sys-macro/sys1_crg_macro.h>
#include <asm/arch/sys-macro/sys0_crg_macro.h>
#include <asm/arch/sys-macro/irq_macro.h>
#include <asm/arch-jhb100/bmcperiph2-macro/bmcperiph2_sysreg_u0_bmcperiph2_sysreg__itg_bd_apb_s_apb__base_addr_macro.h>

void u0_dwc_ssi_sfc_enable(void);
void u6_dwc_i2c_smbus_enable(void);
void u0_dwc_ether_rmiiandrgmii_enable_patch(void);
void u0_dwc_ether_rmiiandrgmii_disable_patch(void);
void starfive_wdt0_jhb100_enable(void);
void starfive_wdt1_jhb100_enable(void);
void starfive_wdt2_jhb100_enable(void);
void starfive_wdt3_jhb100_enable(void);
void starfive_wdt4_jhb100_enable(void);

#endif /* _SAIF_INIT_H_ */
