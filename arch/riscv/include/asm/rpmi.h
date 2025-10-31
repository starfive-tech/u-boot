/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2024 Ventana Micro Systems Ltd.
 */

#ifndef _ASM_RISCV_RPMI_H
#define _ASM_RISCV_RPMI_H

#define RPMI_MAJOR_VER				1
#define RPMI_MINOR_VER				0
#define RPMI_MSGPROTO_VERSION(major, minor)	(((major) << 16) | (minor))

/** RPMI Error Types */
enum rpmi_error {
	/* Success */
	RPMI_SUCCESS		= 0,
	/* General failure  */
	RPMI_ERR_FAILED		= -1,
	/* Service or feature not supported */
	RPMI_ERR_NOTSUPP	= -2,
	/* Invalid Parameter  */
	RPMI_ERR_INVALID_PARAM    = -3,
	/*
	 * Denied to insufficient permissions
	 * or due to unmet prerequisite
	 */
	RPMI_ERR_DENIED		= -4,
	/* Invalid address or offset */
	RPMI_ERR_INVALID_ADDR	= -5,
	/*
	 * Operation failed as it was already in
	 * progress or the state has changed already
	 * for which the operation was carried out.
	 */
	RPMI_ERR_ALREADY	= -6,
	/*
	 * Error in implementation which violates
	 * the specification version
	 */
	RPMI_ERR_EXTENSION	= -7,
	/* Operation failed due to hardware issues */
	RPMI_ERR_HW_FAULT	= -8,
	/* System, device or resource is busy */
	RPMI_ERR_BUSY		= -9,
	/* System or device or resource in invalid state */
	RPMI_ERR_INVALID_STATE	= -10,
	/* Index, offset or address is out of range */
	RPMI_ERR_BAD_RANGE	= -11,
	/* Operation timed out */
	RPMI_ERR_TIMEOUT	= -12,
	/*
	 * Error in input or output or
	 * error in sending or receiving data
	 * through communication medium
	 */
	RPMI_ERR_IO		= -13,
	/* No data available */
	RPMI_ERR_NO_DATA	= -14,
	RPMI_ERR_RESERVED_START	= -15,
	RPMI_ERR_RESERVED_END	= -127,
	RPMI_ERR_VENDOR_START	= -128,
};

#define RPMI_SRVGRP_VOLTAGE		0x6
#define RPMI_SRVGRP_CLOCK		0x7
#define RPMI_SRVGRP_DEVICE_POWER	0x8
#define RPMI_SRVGRP_PERFORMANCE		0x9
#define RPMI_SRVGRP_VENDOR_SECURE	0x8000

/* RPMI Voltage Service IDs */
enum rpmi_voltage_service_id {
	RPMI_VOLTAGE_SRV_ENABLE_NOTIFICATION = 0x01,
	RPMI_VOLTAGE_SRV_GET_NUM_DOMAINS = 0x02,
	RPMI_VOLTAGE_SRV_GET_ATTRIBUTES = 0x03,
	RPMI_VOLTAGE_SRV_GET_SUPPORTED_LEVELS = 0x04,
	RPMI_VOLTAGE_SRV_SET_DOMAIN_CONFIG = 0x05,
	RPMI_VOLTAGE_SRV_GET_DOMAIN_CONFIG = 0x06,
	RPMI_VOLTAGE_SRV_SET_LEVEL = 0x07,
	RPMI_VOLTAGE_SRV_GET_LEVEL = 0x08,
	RPMI_VOLTAGE_SRV_ID_MAX_COUNT,
};

/* RPMI Clock Service IDs */
enum rpmi_clock_service_id {
	RPMI_CLK_SRV_ENABLE_NOTIFICATION = 0x01,
	RPMI_CLK_SRV_GET_SYSTEM_CLOCKS = 0x02,
	RPMI_CLK_SRV_GET_ATTRIBUTES = 0x03,
	RPMI_CLK_SRV_GET_SUPPORTED_RATES = 0x04,
	RPMI_CLK_SRV_SET_CONFIG = 0x05,
	RPMI_CLK_SRV_GET_CONFIG = 0x06,
	RPMI_CLK_SRV_SET_RATE = 0x07,
	RPMI_CLK_SRV_GET_RATE = 0x08,
	RPMI_CLK_SRV_ID_MAX_COUNT,
};

/* RPMI Device Power Service IDs */
enum rpmi_device_power_service_id {
	RPMI_DP_SRV_ENABLE_NOTIFICATION = 0x01,	/* PuC event notification */
	RPMI_DP_SRV_GET_NUM_DOMAINS  = 0x02,	/* get number of power domains */
	RPMI_DP_SRV_GET_ATTRS = 0x03,		/* get power domain attributes */
	RPMI_DP_SRV_SET_STATE = 0x04,		/* set power domain state */
	RPMI_DP_SRV_GET_STATE = 0x05,		/* get power domain state */
	RPMI_DP_SRV_ID_MAX_COUNT,
};

/* RPMI Perf Service IDs */
enum rpmi_perf_service_id {
	RPMI_PERF_SRV_ENABLE_NOTIFICATION = 0x01,
	RPMI_PERF_SRV_GET_NUM_DOMAINS = 0x02,
	RPMI_PERF_SRV_GET_DOMAIN_ATTRIBUTES = 0x03,
	RPMI_PERF_SRV_GET_DOMAIN_LEVELS = 0x04,
	RPMI_PERF_SRV_GET_PERF_LEVEL = 0x05,
	RPMI_PERF_SRV_SET_PERF_LEVEL = 0x06,
	RPMI_PERF_SRV_GET_PERF_LIMIT = 0x07,
	RPMI_PERF_SRV_SET_PERF_LIMIT = 0x08,
	RPMI_PERF_SRV_GET_FAST_CHANNEL_ADDR = 0x09,
	RPMI_PERF_SRV_GET_PERF_HART_LIST = 0x0a,
	RPMI_PERF_SRV_ID_MAX_COUNT,
};

#endif /* _ASM_RISCV_RPMI_H */
