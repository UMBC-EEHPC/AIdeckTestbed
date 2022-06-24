#!/bin/sh
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../Scripts/uart.ini --config-opt=**/flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat --config-opt=flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat run --image --binary="$1"/"$2" --vcd #--trace=fc/insn
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../Scripts/uart.ini --config-opt=**/flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat --config-opt=flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat run --flash --binary="$1"/"$2" --vcd #--trace=fc/insn
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../Scripts/uart.ini --config-opt=**/flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat --config-opt=flash/content/partitions/readfs/files="$1"/ptq_int8_L3_Flash_Const.dat run --exec-prepare --exec --binary="$1"/"$2" --vcd #--trace=fc/insn