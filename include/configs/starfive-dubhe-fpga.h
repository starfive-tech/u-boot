#ifndef __CONFIG_H
#define __CONFIG_H

#define CFG_EXTRA_ENV_SETTINGS								\
	"ipaddr=192.168.152.100\0"                          				\
	"netmask=255.255.255.0\0"                       				\
	"serverip=192.168.152.30\0"                        				\
	"dubhe_boot=booti 0xa1000000 - 0xa0000000;\0"			\
	"tftp_boot=tftp 0xa1000000 Image; tftp 0xa0000000 dubhe_fpga.dtb; 		\
		   run dubhe_boot;\0"				\

#endif /* __CONFIG_H */
