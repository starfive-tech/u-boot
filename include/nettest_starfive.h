/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * StarFive JHB100 nettest public interface
 */

#ifndef __NETTEST_STARFIVE_H__
#define __NETTEST_STARFIVE_H__

#include <stdbool.h>

/**
 * nettest_mac_status() - Get MAC test status
 * 
 * Return: true if MAC test passed, false otherwise
 */
bool nettest_mac_status(void);

/**
 * nettest_phy_status() - Get PHY test status
 * 
 * Return: true if PHY test passed, false otherwise
 */
bool nettest_phy_status(void);

#endif /* __NETTEST_STARFIVE_H__ */
