/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */
//
// jh_reg.h
//
// JH registers Defines
//
// Description:
//
// Revision History:
//        DATE        VERSION  AUTHOR        NOTE
//        ----------  -------  -----------   ------------------------------
//        2019/04/29  0.1      Zavier           Initial
//

#ifndef _GLOBAL_REG_H
#define _GLOBAL_REG_H

// Pheripheral register access
#define REGW(a)             *((volatile UINT32 *)(a))
#define REGH(a)             *((volatile UINT16 *)(a))
#define REGB(a)             *((volatile UINT8 *)(a))


//CADENCE QSPI AHB
#define QSPI_BASE_AHB_ADDR  0x20000000UL

// OSPI
#define OSPI_BASE_ADDR		0x76000000UL

// DSP0
#define DSP_0_BASE_ADDR		0xA0000000UL

// DSP1
#define DSP_1_BASE_ADDR		0xA0100000UL

// NNE50
#define NNE50_BASE_ADDR		0x10800000UL

// SDIO0
#define SDIO0_BASE_ADDR     0x10000000UL

// SDIO1
#define SDIO1_BASE_ADDR     0x10010000UL


// DMAC
#define DMAC_DMA1P_BASE_ADDR    0x10500000UL

#define DMAC_DMA2P_BASE_ADDR	0x100b0000UL


#define SPI2AHB_BASE_ADDR   0x100f0000UL




// I2S_ADC
#define I2S_ADC_BASE_ADDR       0x10400000UL

// PDM
#define PDM_BASE_ADDR           0x10410000UL

// I2S_VAD
#define I2S_VAD_BASE_ADDR       0x10420000UL

// SPDIF
#define SPDIF_BASE_ADDR         0x10430000UL

// PWMDAC
#define PWMDAC_BASE_ADDR        0x10440000UL

// I2S_DAC_0
#define I2S_DAC_0_BASE_ADDR     0x10450000UL

// I2S_DAC_1
#define I2S_DAC_1_BASE_ADDR     0x10460000UL

// I2S_DAC16K
#define I2S_DAC16K_BASE_ADDR    0x10470000UL

// dom_audio_clkgen
#define AUDIO_CLK_GEN_BASE_ADDR        0x10480000UL

// dom_audio_rstgen
#define AUDIO_RST_GEN_BASE_ADDR        0x10490000UL

// dom_audio_sysctrl
#define AUDIO_SYS_CTRL_BASE_ADDR       0x104A0000UL

// USB
#define USB_BASE_ADDR           0x104C0000UL

// sgdma1p

// nne_csr

// noc_csr

// CLKGEN - csr
#define JH_CLKGEN_TOP_SV_BASE_ADDR     0x11800000UL
#define CLKGEN_BASE_ADDR                0x11800000UL

// OTP
#define OTP_BASE_ADDR                   0x11810000UL


// ddrphy0_csr
#define DDRPHY0_BASE_ADDR               0x11820000UL

// ddrphy1_csr
#define DDRPHY1_BASE_ADDR               0x11830000UL

// RSTGEN
#define RSTGEN_BASE_ADDR                0x11840000UL

// SYSCON-mainsys
#define SYSCON_SYSMAIN_CTRL_BASE_ADDR   0x11850000UL

// SYSCON-remap-vp6-noc
#define SYSCON_REMAP_VP6_NOC_BASE_ADDR  0x11854000UL

// SYSCON-iopad
#define SYSCON_IOPAD_CTRL_BASE_ADDR     0x11858000UL

// SYSCON-simu-test
#define SYSCON_SIMU_TEST_BASE_ADDR      0x1185C000UL

// QSPI
#define QSPI_BASE_ADDR		            0x11860000UL

// HS-UART0
#define UART0_HS_BASE_ADDR              0x11870000UL

// HS-UART1
#define UART1_HS_BASE_ADDR              0x11880000UL

#define UART0_BASE_ADDR	UART0_HS_BASE_ADDR
#define UART1_BASE_ADDR	UART1_HS_BASE_ADDR

// UART2
#define UART2_BASE_ADDR                 0x12430000UL

// UART3
#define UART3_BASE_ADDR                 0x12440000UL

// VENC
#define VENC_BASE_ADDR                  0x118E0000UL

// VDEC
#define VDEC_BASE_ADDR                  0x118F0000UL

//MapConv
#define MAP_CONV_BASE                   0x12210000UL

//gc300 2D
#define GC300_BASE_ADDR                 0x10100000UL

// JPEG
#define JPEG_BASE_ADDR                  0x11900000UL

// GPIO
#define GPIO_BASE_ADDR		            0x11910000UL
#define EZGPIO_FULLMUX_BASE_ADDR		0x11910000UL

// DLA

// VP6_APB

// I2C0
#define I2C0_BASE_ADDR          0x118b0000UL

// I2C1
#define I2C1_BASE_ADDR          0x118c0000UL

// I2C2
#define I2C2_BASE_ADDR          0x12450000UL

// I2C3
#define I2C3_BASE_ADDR          0x12460000UL

// SPI0
#define SPI0_BASE_ADDR          0x11890000UL

// SPI1
#define SPI1_BASE_ADDR          0x118a0000UL

// SPI2
#define SPI2_BASE_ADDR          0x12410000UL

// SPI3
#define SPI3_BASE_ADDR          0x12420000UL


// INT controller 0
#define VP6_INTC0_BASE_ADDR     0x12400000UL

// INT controller 1
#define VP6_INTC1_BASE_ADDR     0x124B0000UL

// sec Engine
#define SEC_BASE_ADDR           0x100D0000UL

//GMAC
#define GMAC_BASE_ADDR          0x10020000UL

//NBDLA
#define NBDLA_BASE_ADDR         0x11940000UL
#define NBDLA_RAM_BASE_ADDR     0x19C00000UL

// TIMER --WDT
#define TIMER_BASE_ADDR         0x12480000UL

// pwm -- ptc
#define PWM_BASE_ADDR           0x12490000UL  //PTC



// INTC
#define INTC_BASE_ADDR          0xA10A0000UL

//INT CTRL
#define INT_CTRL_BASE_ADDR  0xA10A0000UL


// SYSCON
#define JH_SYSCON_BASE_ADDR 0xA1100000UL
///0xA90B0000

// PTC
#define PTC_BASE_ADDR       0xA3020000UL
///0xA9040000

// aon_clkgen
#define AON_CLKGEN_BASE_ADDR	 0xA3060000UL

// apb_sram
#define APB_SRAM_BASE_ADDR	     0xA3070000UL

// I2S_1
//#define I2S_1_BASE_ADDR     0xA1000000UL
///0xA8020000

// PCM
///#define PCM_BASE_ADDR       0xA1040000UL
/// 0xA8070000

// EFUSE
///#define EFUSE_BASE_ADDR     0xA1070000UL
///0xA9030000

#define DSITX_BASE_ADDR                 0x12100000UL
#define CSI2TX_BASE_ADDR                0x12220000UL
#define ISP_MIPI_CONTROLLER0_BASE_ADDR  0x19800000UL
#define ISP_MIPI_CONTROLLER1_BASE_ADDR  0x19830000UL

#define VOUT_SYS_CLKGEN_BASE_ADDR  0x12240000UL
#define VOUT_SYS_RSTGEN_BASE_ADDR  0x12250000UL
#define VOUT_SYS_SYSCON_BASE_ADDR  0x12260000UL

#define ISP_CLKGEN_BASE_ADDR        0x19810000UL
#define ISP_RSTGEN_BASE_ADDR        0x19820000UL
#define ISP_SYSCONTROLLER_BASE_ADDR 0x19840000UL

#define ISP0_AXI_SLV_BASE_ADDR      0x19870000UL
#define ISP1_AXI_SLV_BASE_ADDR      0x198A0000UL

//TRNG
#define TRNG_BASE_ADDR      0x118D0000UL

#define DRAM_MEM2SYS(addr) ((addr) >= 0x80000000UL && (addr) <= 0x87FFFFFFFUL  ?  ((addr) + 0xF80000000UL)  :  (addr))
#define DRAM_SYS2MEM(addr) ((addr) >= 0x1000000000UL && (addr) <= 0x107FFFFFFFUL  ?  ((addr) - 0xF80000000UL)  :  (addr))

#endif // _GLOBAL_REG_H
