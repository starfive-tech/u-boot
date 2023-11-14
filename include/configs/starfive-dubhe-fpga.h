#ifndef __CONFIG_H
#define __CONFIG_H

#define CFG_EXTRA_ENV_SETTINGS								\
	"ipaddr=192.168.152.100\0"                          				\
	"netmask=255.255.255.0\0"                       				\
	"serverip=192.168.153.221\0"							\
	"gatewayip=192.168.152.1\0"							\
	"rootpath=/tftpboot/nfs\0"							\
	"dubhe_boot=booti 0xa1000000 - 0xa0000000;\0"			\
	"tftp_boot=tftp 0xa1000000 Image; tftp 0xa0000000 dubhe_fpga.dtb;"		\
		   "run dubhe_boot;\0"				\
	"set_tty=setenv bootargs ${bootargs} "				\
		"console=ttySIF0,115200 earlycon=sbi\0"		\
	"set_ip=setenv bootargs ${bootargs} ip=${ipaddr}:${serverip}:"		\
		"${gatewayip}:${netmask}:${hostname}:eth0:off\0"	\
	"bootargs_nfs=setenv bootargs root=/dev/nfs rw rootwait "			\
		"nfsroot=${serverip}:${rootpath},rw,tcp,v3,"		\
		"hard,sec=sys,local_lock=none,"				\
		"rsize=65536,wsize=65536,"				\
		"timeo=600,retrans=5\0"				\
	"nfs_boot=run bootargs_nfs set_tty set_ip;"			\
		   "run tftp_boot;\0"

#endif /* __CONFIG_H */
