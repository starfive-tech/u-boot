// SPDX-License-Identifier: GPL-2.0+
/*
 * JHB100 Network Test Command
 *
 * Copyright (c) 2026 StarFive Technology Co., Ltd.
 */

#include <command.h>
#include <dm.h>
#include <net.h>
#include <linux/delay.h>
#include <nettest_starfive.h>
#include <asm/io.h>

struct nettest_starfive {
	bool mac;
	bool phy;
};

struct nettest_starfive nettest = {
	.mac = false,
	.phy = false,
};

bool nettest_mac_status(void)
{
	return nettest.mac;
}

bool nettest_phy_status(void)
{
	return nettest.phy;
}

static struct udevice *nettest_get_eth_dev_by_index(int eth_index)
{
	char dev_name[16];

	if (eth_index < 0 || eth_index > 3) {
		printf("Invalid ethernet index: %d (valid: 0-3)\n", eth_index);
		return NULL;
	}

	snprintf(dev_name, sizeof(dev_name), "eth%d", eth_index);
	return eth_get_dev_by_name(dev_name);
}

enum nettest_type {
	NETTEST_MAC,
	NETTEST_PHY,
};

static const char *nettest_type_str(enum nettest_type type)
{
	return (type == NETTEST_MAC) ? "MAC" : "PHY";
}

static int do_jhb100_nettest_loopback(struct udevice *dev, enum nettest_type type)
{
	const char *type_name = nettest_type_str(type);
	uchar test_packet[64];
	int ret;
	int i;
	int timeout_ms = 100;
	int rx_len;

	if (!dev) {
		printf("%s test failed: invalid Ethernet device\n", type_name);
		return CMD_RET_FAILURE;
	}

	eth_halt();

	/* Initialize the Ethernet device */
	nettest.mac = (type == NETTEST_MAC) ? true : false;
	nettest.phy = (type == NETTEST_PHY) ? true : false;
	ret = eth_get_ops(dev)->start(dev);
	if (ret < 0) {
		printf("%s test failed: eth_start error (%d)\n", type_name, ret);
		return CMD_RET_FAILURE;
	}
	nettest.mac = false;
	nettest.phy = false;

	/* Create test packet with random pattern */
	for (i = 0; i < sizeof(test_packet); i++)
		test_packet[i] = rand() & 0xFF;

	printf("Sending test packet (%ld bytes):\n", sizeof(test_packet));
	for (i = 0; i < 16; i++)
		printf("%02x ", test_packet[i]);
	printf("...\n");

	ret = eth_get_ops(dev)->send(dev, test_packet, sizeof(test_packet));
	if (ret) {
		printf("%s test failed: send error (%d)\n", type_name, ret);
		eth_get_ops(dev)->stop(dev);
		return CMD_RET_FAILURE;
	}

	while (timeout_ms > 0) {
		uchar *rx_pkt = NULL;

		/* Receive directly via device operation */
		rx_len = eth_get_ops(dev)->recv(dev, ETH_RECV_CHECK_DEVICE, &rx_pkt);

		if (rx_len > 0 && rx_pkt) {
			printf("Received packet (%d bytes):\n", rx_len);
			for (i = 0; i < (rx_len < 16 ? rx_len : 16); i++)
				printf("%02x ", rx_pkt[i]);
			printf("...\n");

			if (memcmp(test_packet, rx_pkt, sizeof(test_packet)) != 0) {
				printf("%s test failed: packet data mismatch\n", type_name);
				if (eth_get_ops(dev)->free_pkt)
					eth_get_ops(dev)->free_pkt(dev, rx_pkt, rx_len);
				eth_get_ops(dev)->stop(dev);
				return CMD_RET_FAILURE;
			}

			printf("%s loopback test passed!\n", type_name);
			if (eth_get_ops(dev)->free_pkt)
				eth_get_ops(dev)->free_pkt(dev, rx_pkt, rx_len);
			eth_get_ops(dev)->stop(dev);
			return CMD_RET_SUCCESS;
		}

		mdelay(100);
		timeout_ms--;
	}

	printf("%s test failed: no loopback packet received (timeout)\n", type_name);
	eth_get_ops(dev)->stop(dev);
	return CMD_RET_FAILURE;
}

static int do_jhb100_nettest_mac(struct udevice *dev)
{
	return do_jhb100_nettest_loopback(dev, NETTEST_MAC);
}

static int do_jhb100_nettest_phy(struct udevice *dev)
{
	return do_jhb100_nettest_loopback(dev, NETTEST_PHY);
}

static int do_jhb100_nettest(struct cmd_tbl *cmdtp, int flag, int argc,
			     char *const argv[])
{
	struct udevice *dev;
	int eth_index;

	if (argc != 3)
		return CMD_RET_USAGE;

	eth_index = simple_strtol(argv[1], NULL, 10);
	dev = nettest_get_eth_dev_by_index(eth_index);

	if (!dev) {
		printf("Failed to get Ethernet device at index: %d\n", eth_index);
		return CMD_RET_FAILURE;
	}

	if (!strcmp(argv[2], "mac"))
		return do_jhb100_nettest_mac(dev);

	if (!strcmp(argv[2], "phy"))
		return do_jhb100_nettest_phy(dev);

	return CMD_RET_USAGE;
}

U_BOOT_CMD(nettest, 3, 0, do_jhb100_nettest,
	   "JHB100 Ethernet loopback test utility (DesignWare GMAC)",
	   "<ctrl> mac\n"
	   "nettest <ctrl> phy\n"
	   "Available Ethernet controllers on JHB100:\n"
	   "  0 : eth0 (ethernet@11c00000) RMII\n"
	   "  1 : eth1 (ethernet@11c04000) SGMII\n"
	   "  2 : eth2 (ethernet@11b80000) RGMII\n"
	   "  3 : eth3 (ethernet@11b84000) SGMII\n\n"
	   "Notes:\n"
	   "  - MAC loopback tests internal GMAC TX/RX and DMA only.\n"
	   "  - PHY loopback tests external PHY digital path only.\n"
);
