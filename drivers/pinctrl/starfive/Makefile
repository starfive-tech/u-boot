
# SPDX-License-Identifier: GPL-2.0
# Core
obj-$(CONFIG_$(SPL_TPL_)PINCTRL_STARFIVE_JH7110) += pinctrl-starfive-jh7110.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100.o
# SoC Drivers
obj-$(CONFIG_$(SPL_TPL_)PINCTRL_STARFIVE_JH7110) += pinctrl-starfive-jh7110-sys.o
obj-$(CONFIG_$(SPL_TPL_)PINCTRL_STARFIVE_JH7110) += pinctrl-starfive-jh7110-aon.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-bmcperiph0.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-bmcperiph1.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-sys0.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-sys2.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-emmc.o
ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-bmcperiph2.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-bmcperiph2-pok.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-bmcperiph3.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-sys0h.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-sys1.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-adc0.o
obj-$(CONFIG_PINCTRL_STARFIVE_JHB100)	+= pinctrl-starfive-jhb100-adc1.o
endif
