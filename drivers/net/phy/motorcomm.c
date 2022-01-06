/*
 * RealTek PHY drivers
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Copyright 2010-2011 Freescale Semiconductor, Inc.
 * author Andy Fleming
 *
 */
#include <config.h>
#include <common.h>
#include <phy.h>


#define REG_PHY_SPEC_STATUS		0x11
#define REG_DEBUG_ADDR_OFFSET		0x1e
#define REG_DEBUG_DATA 			0x1f
#define EXTREG_SLEEP_CONTROL 		0x27

#define YT8512_DUPLEX 			0x2000
#define YT8521_SPEED_MODE 		0xc000
#define YT8521_DUPLEX 			0x2000
#define YT8521_SPEED_MODE_BIT 		14
#define YT8521_DUPLEX_BIT 		13
#define YT8521_LINK_STATUS_BIT 		10

#define SPEED_UNKNOWN			-1

static int ytphy_read_ext(struct phy_device *phydev, u32 regnum)
{
	int ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_ADDR_OFFSET, regnum);
	if (ret < 0)
		return ret;

	return phy_read(phydev, MDIO_DEVAD_NONE, REG_DEBUG_DATA);
}

static int ytphy_write_ext(struct phy_device *phydev, u32 regnum, u16 val)
{
	int ret;

	ret = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_ADDR_OFFSET, regnum);
	if (ret < 0)
		return ret;

	return phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_DATA, val);
}

static int yt8511_config(struct phy_device *phydev)
{
	u16 val = 0;
	int err = 0;

	genphy_config_aneg(phydev);

	/* disable sleep mode */
	err = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_ADDR_OFFSET, EXTREG_SLEEP_CONTROL);
	if (err < 0) {
		printf("yt8511_config: write EXTREG_SLEEP_CONTROL error!\n");
		return err;
	}

	val = phy_read(phydev, MDIO_DEVAD_NONE, REG_DEBUG_DATA);
	val &= ~(1<<15);
	err = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_DATA, val);
	if (err < 0) {
		printf("yt8511_config: write REG_DEBUG_DATA error!\n");
		return err;
	}

	/* config PLL clock */
	err = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_ADDR_OFFSET, 0xc);
	if (err < 0) {
		printf("yt8511_config: write 0xc error!\n");
		return err;
	}

	val = phy_read(phydev, MDIO_DEVAD_NONE, REG_DEBUG_DATA);
	/* ext reg 0xc.b[2:1]
	00-----25M from pll;
	01---- 25M from xtl;(default)
	10-----62.5M from pll;
	11----125M from pll(here set to this value)
	*/

	val &= ~(3<<1);		//00-----25M from pll;
	val |= (1<<1);		//01-----25M from xtl; (default)
	err = phy_write(phydev, MDIO_DEVAD_NONE, REG_DEBUG_DATA, val);
	if (err < 0) {
		printf("yt8511_config: set PLL error!\n");
		return err;
	}

	return 0;
}

static int yt8521_config(struct phy_device *phydev)
{
	int ret, val;

	ytphy_write_ext(phydev, 0xa000, 0);

	genphy_config_aneg(phydev);

	/* disable auto sleep */
	val = ytphy_read_ext(phydev, EXTREG_SLEEP_CONTROL);
	if (val < 0) {
		printf("yt8521_config: read EXTREG_SLEEP_CONTROL error!\n");
		return val;
	}

	val &= ~(1<<15);
	ret = ytphy_write_ext(phydev, EXTREG_SLEEP_CONTROL, val);
	if (ret < 0) {
		printf("yt8521_config: write EXTREG_SLEEP_CONTROL error!\n");
		return ret;
	}

	/*  enable tx delay 450ps per step */
	val = ytphy_read_ext(phydev, 0xa003);
	if (val < 0) {
		printf("yt8521_config: read 0xa003 error!\n");
		return val;
	}
	val |= 0x3;
	ret = ytphy_write_ext(phydev, 0xa003, val);
	if (ret < 0) {
		printf("yt8521_config: set 0xa003 error!\n");
		return ret;
	}

	/* disable rx delay */
	val = ytphy_read_ext(phydev, 0xa001);
	if (val < 0) {
		printf("yt8521_config: read 0xa001 error!\n");
		return val;
	}
	val &= ~(1<<8);
	ret = ytphy_write_ext(phydev, 0xa001, val);
	if (ret < 0) {
		printf("yt8521_config: failed to disable rx_delay!\n");
		return ret;
	}

	/* enable RXC clock when no wire plug */
	ret = ytphy_write_ext(phydev, 0xa000, 0);
	if (ret < 0) {
		printf("yt8521_config: failed to enable RXC clock!\n");
		return ret;
	}

	val = ytphy_read_ext(phydev, 0xc);
	if (val < 0) {
		printf("yt8521_config: read 0xc error!\n");
		return val;
	}

	val &= ~(1 << 12);
	ret = ytphy_write_ext(phydev, 0xc, val);
	if (ret < 0) {
		printf("yt8521_config: set 0xc error!\n");
		return ret;
	}

	return 0;
}

static int yt8521_adjust_status(struct phy_device *phydev, int val, int is_utp)
{
	int speed_mode, duplex;
	int speed = SPEED_UNKNOWN;

	duplex = (val & YT8512_DUPLEX) >> YT8521_DUPLEX_BIT;
	speed_mode = (val & YT8521_SPEED_MODE) >> YT8521_SPEED_MODE_BIT;
	switch (speed_mode) {
	case 0:
		if (is_utp)
			speed = SPEED_10;
		break;
	case 1:
		speed = SPEED_100;
		break;
	case 2:
		speed = SPEED_1000;
		break;
	case 3:
		break;
	default:
		speed = SPEED_UNKNOWN;
		break;
	}

	phydev->speed = speed;
	phydev->duplex = duplex;

	return 0;
}

static int yt8521_parse_status(struct phy_device *phydev)
{
	int ret, val, link, link_utp;

	/* reading UTP */
	ret = ytphy_write_ext(phydev, 0xa000, 0);
	if (ret < 0)
		return ret;

	val = phy_read(phydev, MDIO_DEVAD_NONE, REG_PHY_SPEC_STATUS);
	if (val < 0)
		return val;

	link = val & (BIT(YT8521_LINK_STATUS_BIT));
	if (link) {
		link_utp = 1;
		yt8521_adjust_status(phydev, val, 1);
	} else {
		link_utp = 0;
	}

	if (link_utp) {
		phydev->link = 1;
		ytphy_write_ext(phydev, 0xa000, 0);
	} else {
		phydev->link = 0;
	}

	return 0;
}

static int yt8521_startup(struct phy_device *phydev)
{
	int retval;

	retval = genphy_update_link(phydev);
	if (retval)
		return retval;

	return yt8521_parse_status(phydev);
}

static struct phy_driver YT8511_driver = {
	.name = "YuTai YT8511",
	.uid = 0x0000010a,
	.mask = 0x00000fff,
	.features = PHY_GBIT_FEATURES,
	.config = &yt8511_config,
	.startup = &genphy_startup,
	.shutdown = &genphy_shutdown,
};

static struct phy_driver YT8521_driver = {
	.name = "YuTai YT8521",
	.uid = 0x0000011a,
	.mask = 0x00000fff,
	.features = PHY_GBIT_FEATURES,
	.config = &yt8521_config,
	.startup = &yt8521_startup,
	.shutdown = &genphy_shutdown,
};

int phy_yutai_init(void)
{
	phy_register(&YT8511_driver);
	phy_register(&YT8521_driver);

	return 0;
}
