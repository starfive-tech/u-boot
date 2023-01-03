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
make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- PLATFORM=generic FW_PAYLOAD_PATH=/home/admin/u-boot/u-boot.bin FW_FDT_PATH=/home/admin/u-boot/arch/riscv/dts/starfive_visionfive2.dtb FW_TEXT_START=0x40000000
make ARCH=riscv CROSS_COMPILE=riscv64-linux-gnu- PLATFORM=generic FW_PAYLOAD_PATH=/home/admin/u-boot/u-boot.bin FW_FDT_PATH=/home/admin/u-boot/arch/riscv/dts/starfive_visionfive2.dtb FW_TEXT_START=0x40000000
cd ../Tools/uboot_its/
cp /home/admin/opensbi/build/platform/generic/firmware/fw_payload.bin ./
/home/admin/u-boot/tools/mkimage -f visionfive2-uboot-fit-image.its -A riscv -O u-boot -T firmware visionfive2_fw_payload.img
cp visionfive2_fw_payload.img /home/admin/kernel_deb/
cd ../spl_tool/
cp u-boot-spl.bin.normal.out ~/kernel_deb/
```


