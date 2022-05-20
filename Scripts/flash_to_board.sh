#!/bin/bash

gapy --target=ai_deck --platform=board --work-dir="$1" --config-ini="$1"/../Scripts/uart.ini --config-opt=**/flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat --config-opt=flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat run --image --binary="$1"/"$2"
gapy --target=ai_deck --platform=board --work-dir="$1" --config-ini="$1"/../Scripts/uart.ini --config-opt=**/flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat --config-opt=flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat run --flash --binary="$1"/"$2"

FLASH_IMG_SIZE=$(wc -c < "$1"/target.board.devices.flash.img)
gap8-openocd -d0 -c "gdb_port disabled; telnet_port disabled; tcl_port disabled" -c "script interface/ftdi/olimex-arm-usb-tiny-h.cfg; script target/gap8revb.tcl; script tcl/flash_image.tcl; script tcl/jtag_boot.tcl; gap_flash_raw_hyper ${1}/target.board.devices.flash.img ${FLASH_IMG_SIZE} ${1}/../Toolchain/gap_sdk/utils/openocd_tools; exit;"

gapy --target=ai_deck  gen_flash_image --boot-loader "$1"/"$2"  -o "$1"/flash.img 

gapy --target=ai_deck --platform=board --work-dir="$1"  --config-opt=**/flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat   --config-opt=flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat   run --flash --force --binary="$1"/"$2"

gap8-openocd -d0 -c "gdb_port disabled; telnet_port disabled; tcl_port disabled" -c "script interface/ftdi/olimex-arm-usb-tiny-h.cfg; script target/gap8revb.tcl; script tcl/flash_image.tcl; script tcl/jtag_boot.tcl; gap_flash_raw_hyper ${1}/target.board.devices.flash.img ${FLASH_IMG_SIZE} ${1}/../Toolchain/gap_sdk/utils/openocd_tools; exit;"