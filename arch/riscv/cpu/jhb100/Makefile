# SPDX-License-Identifier: GPL-2.0+
#
# Copyright (c) 2024 StarFive Technology Co., Ltd.

obj-y += boot_mapping.o
obj-y += boot_recovery.o
obj-y += cpu.o
obj-y += dram.o
obj-$(CONFIG_STARFIVE_JHB100_SECURE_VAB_AUTH) += secure_vab.o
obj-$(CONFIG_SPL_BUILD) += spl_spi_starfive.o
obj-$(CONFIG_SPL_BUILD) += starfive_pcu.o
obj-$(CONFIG_SPL_BUILD) += boot_fallback.o
obj-$(CONFIG_SPL_BUILD) += spl.o
ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_SBI) += sbi_ext.o
endif
