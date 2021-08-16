/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright (c) 2021 StarFive Technology Co., Ltd. */

#ifndef __JH_IOPAD_H
#define __JH_IOPAD_H


/** @brief GPIO pins definition
 * for CONFIG_JH_EVB_V1
 */
#define UART0_RXD_PIN       5
#define UART0_TXD_PIN       6
#define UART0_CTS_PIN       7
#define UART0_RTS_PIN       8
#define UART1_RXD_PIN       9
#define UART1_TXD_PIN       10
#define I2C0_SCL_PIN        11
#define I2C0_SDA_PIN        12
#define UART3_RXD_PIN       13
#define UART3_TXD_PIN       14
#define QSPI_CSN1_PIN       15
#define I2C1_SCL_PIN        16
#define I2C1_SDA_PIN        17
#define I2C2_SCL_PIN        18
#define I2C2_SDA_PIN        19
#define VDD2PEN_OTP_PIN     26
#define SPI2AHB_CSN_PIN     29
#define SPI2AHB_SCK_PIN     30
#define SPI2AHB_D0_PIN      31
#define SPI2AHB_D1_PIN      32
#define SPI2AHB_D2_PIN      33
#define SPI2AHB_D3_PIN      34

#define BOOT_SEL0_PIN       60
#define BOOT_SEL1_PIN       61
#define BOOT_SEL2_PIN       62
#define BOOT_MODE_PIN       63

/** @brief For backward compatibility
 */
// the GPIO pin is not available on EVB, be sure NOT to use it
#define STUB_PIN_NOT_EXIST       0
// the GPIO pin is not defined yet, since the daughter board not ready
#define STUB_PIN_TBD             0

#define FPGA_UART0_TXD      UART0_TXD_PIN
#define FPGA_UART0_RXD      UART0_RXD_PIN
#define FPGA_UART0_CTSN     UART0_CTS_PIN
#define FPGA_UART0_RTSN     UART0_RTS_PIN

#define FPGA_UART1_TXD      UART1_TXD_PIN
#define FPGA_UART1_RXD      UART1_RXD_PIN

#define FPGA_UART2_TXD      FPGA_UART0_TXD///STUB_PIN_NOT_EXIST
#define FPGA_UART2_RXD      FPGA_UART0_RXD///STUB_PIN_NOT_EXIST
#define FPGA_UART2_CTSN     FPGA_UART0_CTSN///STUB_PIN_NOT_EXIST
#define FPGA_UART2_RTSN     FPGA_UART0_RTSN///STUB_PIN_NOT_EXIST

#define FPGA_UART3_TXD      UART3_TXD_PIN
#define FPGA_UART3_RXD      UART3_RXD_PIN

/*gpio I2C pin*/
#define I2C_SDA_AC108       I2C0_SDA_PIN//STUB_PIN_TBD
#define I2C_SCL_AC108       I2C0_SCL_PIN///STUB_PIN_TBD
#define I2C_SDA_ADV7513     I2C1_SDA_PIN
#define I2C_SCL_ADV7513     I2C1_SCL_PIN
#define I2C_SDA_SC2235      STUB_PIN_TBD
#define I2C_SCL_SC2235      STUB_PIN_TBD

#define HDMI_INTN           24

/*gpio SPDIF pin*/
#define SPDIF0              STUB_PIN_TBD
#define SPDIF1              STUB_PIN_TBD

#define PDM_DMIC_CLK_GPIOA43    STUB_PIN_TBD
#define PDM_DMIC1_GPIOA44       STUB_PIN_TBD
#define PDM_DMIC2_GPIOA45       STUB_PIN_TBD

/*gpio I2S pin*/
#define FPGA_BCLK_I2S_0       STUB_PIN_TBD
///#define FPGA_LRCLK_I2S_0      STUB_PIN_TBD
///#define FPGA_DOUT_I2S_0       STUB_PIN_TBD
///#define FPGA_BCLK_I2S_1       STUB_PIN_TBD
///#define FPGA_LRCLK_I2S_1      STUB_PIN_TBD
#define FPGA_ADC_I2S_BCLK     STUB_PIN_TBD
#define FPGA_ADC_I2S_LRCLK    STUB_PIN_TBD
#define FPGA_ADC_I2S_DATA0    STUB_PIN_TBD
#define FPGA_ADC_I2S_DATA1    STUB_PIN_TBD
#define FPGA_ADC_I2S_DATA2    STUB_PIN_TBD
#define FPGA_ADC_I2S_DATA3    STUB_PIN_TBD
#define FPGA_MCLK             STUB_PIN_TBD
#define FPGA_MCLK_I2S2        STUB_PIN_TBD
//#define FPGA_BCLK_I2S2        STUB_PIN_TBD
//#define FPGA_LRCLK_I2S2       STUB_PIN_TBD
//#define FPGA_DIN_I2S2         STUB_PIN_TBD

#endif
