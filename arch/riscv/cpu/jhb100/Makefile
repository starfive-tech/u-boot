# SPDX-License-Identifier: GPL-2.0+
#
# Copyright (c) 2025 StarFive Technology Co., Ltd.

obj-y += boot_env.o
obj-y += boot_fdt.o
obj-y += boot_mapping.o
obj-y += boot_pti.o
obj-y += boot_recovery.o
obj-y += boot_update.o
obj-y += bootcmd_restore.o
obj-$(CONFIG_MMC) += bootcmd_emmc.o
obj-$(CONFIG_UFS) += bootcmd_ufs.o
obj-y += cache.o
obj-y += cpu.o
obj-y += dram.o
obj-y += secure_vab.o
obj-y += starfive_reset.o
ifdef CONFIG_SPL_BUILD
obj-$(CONFIG_MMC) += spl_mmc_starfive.o
obj-y += spl_spi_starfive.o
obj-$(CONFIG_UFS) += spl_ufs_starfive.o
obj-y += starfive_pcu.o
obj-y += boot_fallback.o
obj-y += spl.o
endif
ifndef CONFIG_SPL_BUILD
obj-$(CONFIG_STARFIVE_JHB100_MPXY_SEC)	+=jhb100-mpxy-sec.o
obj-$(CONFIG_SBI) += sbi_ext.o
endif
