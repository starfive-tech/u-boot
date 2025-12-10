/* SPDX-License-Identifier: GPL-2.0+ */
#ifndef _UFS_H
#define _UFS_H

struct udevice;

/**
 * ufs_probe() - initialize all devices in the UFS uclass
 *
 * Return: 0 if Ok, -ve on error
 */
int ufs_probe(void);

/**
 * ufs_probe_dev() - initialize a particular device in the UFS uclass
 *
 * @index: index in the uclass sequence
 *
 * Return: 0 if successfully probed, -ve on error
 */
int ufs_probe_dev(int index);

/*
 * ufs_scsi_bind() - Create a new scsi device as a child of the UFS device and
 *		     bind it to the ufs_scsi driver
 * @ufs_dev: UFS device
 * @scsi_devp: Pointer to scsi device
 *
 * Return: 0 if Ok, -ve on error
 */
int ufs_scsi_bind(struct udevice *ufs_dev, struct udevice **scsi_devp);

/**
 * ufs_list_lus() - List all configured Logical Units (LUs) in a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 *
 * This function enumerates and prints information about all existing LUs
 * (Logical Units) on the specified UFS device.
 */
void ufs_list_lus(struct udevice *ufs_dev);

/**
 * ufs_create_lu() - Create a new Logical Unit (LU) on a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @lun:     Logical Unit Number to assign (0-7)
 * @size:    Size of the LU in blocks (4MB per block)
 * @attr:    Attributes for the LU (e.g., bootable, read-only flags)
 *
 * This function creates a new LU on the specified UFS device with the given
 * size and attributes.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_create_lu(struct udevice *ufs_dev, u8 lun, u32 size, u32 attr);

/**
 * ufs_update_lu() - Modify an existing Logical Unit (LU) on a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @lun:     Logical Unit Number of the LU to update
 * @size:    New size to set for the LU
 * @attr:    New attributes to set
 *
 * This function updates the size and/or attributes of an existing LU
 * on the specified UFS device.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_update_lu(struct udevice *ufs_dev, u8 lun, u32 size, u32 attr);

/**
 * ufs_remove_lu() - Remove a Logical Unit (LU) from a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @lun:     Logical Unit Number to remove
 *
 * This function removes a specified LU from the UFS device.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_remove_lu(struct udevice *ufs_dev, int lun);

/**
 * ufs_create_rpmb_lu() - Create a new RPMB Logical Unit (LU) on a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @region:     Logical Unit Number RPMB region (1-3)
 * @size:    Size of the LU in blocks (4MB per block)
 *
 * This function creates a new LU on the specified UFS device with the given
 * size and attributes.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_create_rpmb_lu(struct udevice *ufs_dev, u8 region, u32 size);

/**
 * ufs_remove_rpmb_lu() - Remove RPMB Logical Unit (LU) on a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @region:     Logical Unit Number RPMB region (1-3)
 *
 * This function remove exisitng RPMB LU on the specified UFS device with the given
 * region.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_remove_rpmb_lu(struct udevice *ufs_dev, u8 region);


/**
 * ufs_rpmb_read() - Read RPMB Logical Unit (LU) on a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @region:     Logical Unit Number RPMB region (0-3)
 * @addr:    Address to store read data
 * @lba:     Logical Block Address to start reading from
 * @blkcnt:  Number of blocks to read
 * @key_addr: Pointer to the RPMB authentication key
 *
 * This function read RPMB LU on the specified UFS device with the given
 * region, lba, and block count.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_rpmb_read(struct udevice *ufs_dev, u8 region, void *addr, u32 lba, u32 blkcnt, u8 *key_addr);

/**
 * ufs_rpmb_write() - Write RPMB Logical Unit (LU) on a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @region:     Logical Unit Number RPMB region (0-3)
 * @addr:    Address to store write data
 * @lba:     Logical Block Address to start reading from
 * @blkcnt:  Number of blocks to write
 * @key_addr: Pointer to the RPMB authentication key
 *
 * This function write RPMB LU on the specified UFS device with the given
 * region, lba, and block count.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_rpmb_write(struct udevice *ufs_dev, u8 region, void *addr, u32 lba, u32 blkcnt, u8 *key_addr);

/**
 * ufs_write_rpmb_key() - Provision RPMB Logical Unit (LU) region key on a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @region:     Logical Unit Number RPMB region (0-3)
 * @key_addr: Pointer to the RPMB authentication key
 *
 * This function perform RPMB LU key programming on the specified UFS device with the given
 * key address.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_write_rpmb_key(struct udevice *ufs_dev, u8 region, u8 *key_addr);

/**
 * ufs_write_protect() - Enable/Disable Write Protect on Logical Unit (LU) on a UFS device
 *
 * @ufs_dev: Pointer to the UFS device
 * @lun:     Logical Unit Number to set write protect
 * @write_en:  true to enable write protect, false to disable
 * @type:    Write protect type (0: NV-Type, 1: P-Type, 2: NV-AWP-Type)
 * @key_addr: Pointer to the RPMB authentication key
 *
 * This function enable or disable write protection to LUN on the specified UFS device with the given
 * arguement.
 *
 * Return: 0 on success, -ve on error
 */
int ufs_write_protect(struct udevice *ufs_dev, u32 lun, u8 write_en, u8 wpt, u8 *key_addr);

#endif
