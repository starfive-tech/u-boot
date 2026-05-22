# SPDX-License-Identifier: GPL-2.0+

obj-$(CONFIG_CLK_JH7110) += clk-jh7110.o
obj-$(CONFIG_CLK_JH7110) += clk-jh7110-pll.o

# StarFive JHB100 Clock
obj-$(CONFIG_CLK_STARFIVE_COMMON)		+= jhb100/clk-starfive-common.o
obj-$(CONFIG_CLK_STARFIVE_JHB100_SYS)		+= jhb100/clk-jhb100-sys.o
obj-$(CONFIG_CLK_STARFIVE_JHB100_SYS)		+= jhb100/clk-jhb100-sys1.o
obj-$(CONFIG_CLK_STARFIVE_JHB100_SYS)		+= jhb100/clk-jhb100-sys2.o
obj-$(CONFIG_CLK_STARFIVE_JHB100_PER0)		+= jhb100/clk-jhb100-per0.o
obj-$(CONFIG_CLK_STARFIVE_JHB100_PER1)		+= jhb100/clk-jhb100-per1.o
ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_CLK_STARFIVE_JHB100_PER2)		+= jhb100/clk-jhb100-per2.o
obj-$(CONFIG_CLK_STARFIVE_JHB100_PER3)		+= jhb100/clk-jhb100-per3.o
endif
obj-$(CONFIG_CLK_STARFIVE_JHB100_USB)		+= jhb100/clk-jhb100-usb.o
obj-$(CONFIG_CLK_STARFIVE_JHB100_CPU)		+= jhb100/clk-jhb100-cpu.o
obj-$(CONFIG_CLK_STARFIVE_JHB100_VOUT)		+= jhb100/clk-jhb100-vout.o
