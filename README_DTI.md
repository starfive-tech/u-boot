# Update U-Boot
Beschreibung Update von u-boot. 

```
cd u-boot/
make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- -j8
cd ../Tools/spl_tool/
./create_sbl /home/admin/u-boot/spl/u-boot-spl.bin 0x01010101
cd ../uboot_its/
/home/admin/u-boot/tools/mkimage -f visionfive2-uboot-fit-image.its -A riscv -O u-boot -T firmware visionfive2_fw_payload.img
cp visionfive2_fw_payload.img ../../kernel_deb/
cd ..
cd spl_tool/
cp u-boot-spl.bin.normal.out ../../kernel_deb/
```
