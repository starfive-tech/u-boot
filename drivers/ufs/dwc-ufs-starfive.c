// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2025 StarFive Technology Co., Ltd.
 */

#include <asm/io.h>
#include <clk.h>
#include <common.h>
#include <dm.h>
#include <dm/device_compat.h>
#include <linux/delay.h>
#include <reset.h>
#include <scsi.h>
#include <ufs.h>

#include "ufs.h"

#define MAX_SCSI_BYTE_PER_REQUEST (16 * 4096) /* 1BLK = 4096byte */

#define	PERI1_SYSCON_56_OFF	0x38
#define SRAM_INIT_DONE_BIT	2	/* [0:Busy 1:Done] */
#define SRAM_EXT_LD_DONE_BIT	1	/* [0:Busy 1:Done] */

#define	PERI1_SYSCON_60_OFF	0x3C
#define REF_CLK_OEN_BIT		8	/* [0:Output Enabled 1:Output Disabled] */
#define UFS_RESET_I_BIT		9	/* UFS RESET logic level */
#define UFS_RESET_OEN_BIT	10	/* [0:Output Enabled 1:Output Disabled] */

#define GET_ATTR_SEL(n)	((((n) & 0xFFFF) << 16) | (((n) >> 16) & 0xFFFF))

struct dwc_ufs_priv {
	struct clk_bulk clks;
	struct reset_ctl_bulk resets;
	fdt_addr_t syscon_base;
};

struct m_phy_cali_para {
	u32 EXT_COARSE_TUNE_RATEA;
	u32 EXT_COARSE_TUNE_RATEB;
	u32 LANE0_ATT_IDAC_OFST;
	u32 LANE0_CTLE_IDAC_OFST;
	u32 LANE1_ATT_IDAC_OFST;
	u32 LANE1_CTLE_IDAC_OFST;
};

static struct m_phy_cali_para cali_default = {
	/* Sync from SCP */
	.EXT_COARSE_TUNE_RATEA = 37,
	.EXT_COARSE_TUNE_RATEB = 81,
	.LANE0_ATT_IDAC_OFST   = 138,
	.LANE0_CTLE_IDAC_OFST  = 142,
	.LANE1_ATT_IDAC_OFST   = 194,
	.LANE1_CTLE_IDAC_OFST  = 139,
};

static int dwc_ufs_c10_mphy_reg_write(struct ufs_hba *hba, u32 addr, u32 data)
{
	int result = 0;

	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x8116), (addr & 0xff)); /* Address Low */
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x8117), ((addr >> 8) & 0xff)); /* Address High */
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x8118), (data & 0xff)); /* Data Low */
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x8119), ((data >> 8) & 0xff)); /* Data High */
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x811c), 0x01); /* Write */
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0xd085), 0x01); /* Config Update */

	return result;
}

static int dwc_ufs_c10_mphy_reg_read(struct ufs_hba *hba, u32 addr, u32 *data)
{
	int result = 0;
	u32 data_lsb;
	u32 data_msb;

	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x8116), (addr & 0xff)); /* Address Low */
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x8117), ((addr >> 8) & 0xff)); /* Address High */
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x8118), 0xff);
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x8119), 0xff);
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x811c), 0x00); /* Read */
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0xd085), 0x01); /* Config Update */

	/* Read the data */
	*data = 0;
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x811a), 0x00);
	result |= ufshcd_dme_get(hba, GET_ATTR_SEL(0x811a), &data_lsb);
	result |= ufshcd_dme_set(hba, GET_ATTR_SEL(0x811b), 0x00);
	result |= ufshcd_dme_get(hba, GET_ATTR_SEL(0x811b), &data_msb);
	*data = ((data_msb & 0xFF) << 8) | (data_lsb & 0xFF);

	return result;
}

static int dwc_ufs_init_mphy(struct ufs_hba *hba, struct m_phy_cali_para *calibration,
			     struct dwc_ufs_priv *priv)
{
	/* Sync from SCP */
	u32 val, dme_val = 0;
	ulong start, timeout_ms = 100;

	/* Set Rate A in CBRATESEL(offset=0x14) Selects Operating Rate: 0: rate A; 1: rate B*/
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x8114), 0);
	/* Set ref_clk_gating_support register(0x8132) CBREFCLKCTRL2[7:6] to 2’b10. */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x8132), 0x80);
	/* RX: Configure per lane RXSQCONTROL(0xX8009) implementation specific
	 * attribute with value 'h1. Set this for all connected lanes 0xX8009, where X can
	 * take value 4 to 5 to indicate RX lane 0 to RX lane 1
	 */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x48009), 1);
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x58009), 1);
	/* RX: Configure per lane RXRHOLDCTRLOPT (0xX8013) implementation specific
	 * attribute with value ‘h2. Set this for all connected lanes 0xX8013, where X can
	 * take value 4 to 5 to indicate RX lane 0 to RX lane 1.
	 */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x48013), 2);
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x58013), 2);
	/* Configure CB attribute EXT_COARSE_TUNE_RATEA (0x814D) with value from OTP.
	 * (section 4.10) For SOC init sequence, customer can update the value based on
	 * the calibration words from production(Support Dynamic Rate Change)
	 */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x814D), calibration->EXT_COARSE_TUNE_RATEA);
	/* Configure CB attribute EXT_COARSE_TUNE_RATEB (0x814E) with value 0x85.
	 * (section 4.10) For SOC init sequence, customer can update the value based on
	 * the calibration words from production(Support Dynamic Rate Change).
	 */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x814E), calibration->EXT_COARSE_TUNE_RATEB);
	/* Configure CB attribute CBCRCTRL(0x811F) with value ‘h1 to select Parallel
	 * interface for indirect access
	 */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0x811F), 1);
	/* Configure the VS_MphyCfgUpdt (0xD085) attribute to 1. The Write access to this
	 * attribute triggers a configuration update of all connected TX and RX M-PHY
	 * modules. It returns 0 upon read
	 */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0xD085), 1);

	/* Wait for MPHY ready */
	start = get_timer(0);
	val = readl((void *)priv->syscon_base + PERI1_SYSCON_56_OFF);
	do {
		val = readl((void *)priv->syscon_base + PERI1_SYSCON_56_OFF);

		if (((val & 4) >> SRAM_INIT_DONE_BIT))
			break;

		udelay(1);
	} while (get_timer(start) < timeout_ms);

	if (!((val & 4) >> SRAM_INIT_DONE_BIT)) {
		printf("Timeout waiting for SRAM init done\n");
		return -ETIMEDOUT;
	}

	val |= (1 << SRAM_EXT_LD_DONE_BIT);
	writel(val, (void *)priv->syscon_base + PERI1_SYSCON_56_OFF);

	/* Access SRAM contents through indirect register access if needed */
	/* Through indirect register access, Configure PHY CR register 0x7014 with same
	 * value as the one configured for EXT_COARSE_TUNE_RATEA in step 11 or
	 * EXT_COARSE_TUNE_RATEB in step 12. Programs
	 * RAWAONLANEN_DIG_MPLLA_COARSE_TUNE attribute of the PHY using
	 * broadcast feature.
	 */
	dwc_ufs_c10_mphy_reg_write(hba, 0x7014, calibration->EXT_COARSE_TUNE_RATEA);
	/* Through indirect register access, Configure PHY CR register
	 * SUP_DIG_MPLLA_MPLL_PWR_CTL_MPLL_SKIPCAL_COARSE_TUNE (0x0028) with
	 * same value as the one configured for EXT_COARSE_TUNE_RATEA in step 11 or
	 * EXT_COARSE_TUNE_RATEB in step 12.
	 */
	dwc_ufs_c10_mphy_reg_write(hba, 0x0028, calibration->EXT_COARSE_TUNE_RATEA);
	/* Program PHY CR register RAWAONLANEN_DIG_FAST_FLAGS (0x4N1c) with
	 * value 0x4 through indirect register access where N can take value 0 to 1 to
	 * indicate RX Lane 0 to Lane 1. (Bypass the RX-AFE calibrations)
	 */
	dwc_ufs_c10_mphy_reg_write(hba, 0x401c, 4);
	dwc_ufs_c10_mphy_reg_write(hba, 0x411c, 4);
	/* Set RAWAONLANEN_DIG_AFE_ATT_IDAC_OFST(0x4N00) = (ATT offset compensation value) */
	dwc_ufs_c10_mphy_reg_write(hba, 0x4000, calibration->LANE0_ATT_IDAC_OFST);
	dwc_ufs_c10_mphy_reg_write(hba, 0x4100, calibration->LANE1_ATT_IDAC_OFST);
	/* Set RAWAONLANEN_DIG_AFE_CTLE_IDAC_OFST(0x4N01) = (CTLE offset compensation value) */
	dwc_ufs_c10_mphy_reg_write(hba, 0x4001, calibration->LANE0_CTLE_IDAC_OFST);
	dwc_ufs_c10_mphy_reg_write(hba, 0x4101, calibration->LANE1_CTLE_IDAC_OFST);
	/*  Set RAWAONLANEN_DIG_RX_ADPT_DFE_TAP3 [9](0x4N1e) to 1 so that the
	 * offset calibration words (ONLANEN_DIG_AFE_ATT_IDAC_OFST and
	 * ONLANEN_DIG_AFE_CTLE_IDAC_OFST) are restored automatically by firmware
	 * upon power gating exit.
	 */
	dwc_ufs_c10_mphy_reg_read(hba, 0x401E, &dme_val);
	dwc_ufs_c10_mphy_reg_write(hba, 0x401E, dme_val | (1 << 9));
	dwc_ufs_c10_mphy_reg_read(hba, 0x411E, &dme_val);
	dwc_ufs_c10_mphy_reg_write(hba, 0x411E, dme_val | (1 << 9));
	/* Configure the VS_MphyCfgUpdt (0xD085) attribute to 1. The Write access to
	 * this attribute triggers a configuration update of all connected TX and RX M-PHY
	 * modules. It returns 0 upon read
	 */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0xD085), 1);
	/* Configure VS_mphy_disable(0xD0C1) with the value 0x0 */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0xD0C1), 0);
	/* Configure VS_DebugSaveConfigTime(0xD0A0). Set 0xD0A0[1:0] = 0x3 */
	ufshcd_dme_get(hba, GET_ATTR_SEL(0xD0A0), &dme_val);
	ufshcd_dme_set(hba, GET_ATTR_SEL(0xD0A0), dme_val | 0x3);
	/* Configure VS_ClkMuxSwitchingTimer (0xD0FB) with the value 0xA. */
	ufshcd_dme_set(hba, GET_ATTR_SEL(0xD0FB), 0xA);

	return 0;
}

static int dwc_ufs_link_startup_notify(struct ufs_hba *hba,
				       enum ufs_notify_change_status status)
{
	struct scsi_plat *scsi_plat;
	struct udevice *scsi_dev;
	struct dwc_ufs_priv *priv = dev_get_priv(hba->dev);

	device_find_first_child(hba->dev, &scsi_dev);
	if (!scsi_dev)
		return -ENODEV;

	/* Override common SCSI platform */
	scsi_plat = dev_get_uclass_plat(scsi_dev);
	scsi_plat->max_bytes_per_req = MAX_SCSI_BYTE_PER_REQUEST;

	if (status == PRE_CHANGE) {
		int ret = dwc_ufs_init_mphy(hba, &cali_default, priv);
		if (ret) {
			printf("Controller init fail ...\n");
			return -EBUSY;
		}
	}

	hba->quirks |= UFSHCD_QUIRK_SELECT_GEAR_RATE_A;

	return 0;
}

static struct ufs_hba_ops dwc_ufs_vops = {
	.link_startup_notify = dwc_ufs_link_startup_notify,
};

static int dwc_ufs_pltfm_bind(struct udevice *dev)
{
	struct udevice *scsi_dev;

	return ufs_scsi_bind(dev, &scsi_dev);
}

static int dwc_ufs_pltfm_probe(struct udevice *dev)
{
	struct dwc_ufs_priv *priv = dev_get_priv(dev);
	ofnode ufs_node, syscon_node;
	fdt_size_t size;
	u32 val;
	int err;

	err = clk_get_bulk(dev, &priv->clks);
	if (err < 0)
		return err;

	err = reset_get_bulk(dev, &priv->resets);
	if (err < 0)
		return err;

	err = clk_enable_bulk(&priv->clks);
	if (err)
		goto err_clk_enable;

	err = reset_deassert_bulk(&priv->resets);
	if (err)
		goto err_clk_enable;

	ufs_node = dev_ofnode(dev);
	syscon_node = ofnode_get_by_phandle(ofnode_read_u32_default
						(ufs_node, "starfive,syscon", 0));

	if (!ofnode_valid(syscon_node)) {
		printf("Failed to get per1_syscon ofnode\n");
		err = -EINVAL;
		goto err_ufshcd_probe;
	}

	priv->syscon_base = ofnode_get_addr_size_index(syscon_node, 0, &size);
	if (priv->syscon_base == FDT_ADDR_T_NONE) {
		printf("Failed to read per1_syscon base address\n");
		err = -EINVAL;
		goto err_ufshcd_probe;
	}

	/* Configure PHY setting */
	val = readl((void *)priv->syscon_base + PERI1_SYSCON_60_OFF);
	val &= ~(1 << REF_CLK_OEN_BIT);
	val &= ~(1 << UFS_RESET_OEN_BIT);
	val |= (1 << UFS_RESET_I_BIT);
	writel(val, (void *)priv->syscon_base + PERI1_SYSCON_60_OFF);

	err = ufshcd_probe(dev, &dwc_ufs_vops);
	if (err) {
		dev_err(dev, "ufshcd_probe() failed %d\n", err);
		goto err_ufshcd_probe;
	}

	return 0;

err_ufshcd_probe:
	reset_assert_bulk(&priv->resets);
	clk_disable_bulk(&priv->clks);
err_clk_enable:
	clk_release_bulk(&priv->clks);
	return err;
}

static int dwc_ufs_pltfm_remove(struct udevice *dev)
{
	struct dwc_ufs_priv *priv = dev_get_priv(dev);

	clk_disable_bulk(&priv->clks);
	clk_release_bulk(&priv->clks);

	return 0;
}

static const struct udevice_id dwc_ufs_pltfm_ids[] = {
	{ .compatible = "starfive,jhb100-ufs" },
	{ /* sentinel */ }
};

U_BOOT_DRIVER(designware_core_ufs) = {
	.name		= "designware-core-ufs",
	.id		= UCLASS_UFS,
	.of_match	= dwc_ufs_pltfm_ids,
	.bind		= dwc_ufs_pltfm_bind,
	.probe		= dwc_ufs_pltfm_probe,
	.remove		= dwc_ufs_pltfm_remove,
	.priv_auto	= sizeof(struct dwc_ufs_priv),
};
