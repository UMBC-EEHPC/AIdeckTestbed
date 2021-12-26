gapy --target=ai_deck --platform=board --work-dir="$1" --config-ini="$1"/../uart.ini      run --image --binary="$1"/"$2"
gapy --target=ai_deck --platform=board --work-dir="$1" --config-ini="$1"/../uart.ini      run --flash --binary="$1"/"$2"
gapy --target=ai_deck  gen_flash_image --boot-loader "$1"/"$2"  -o "$1"/flash.img 
gapy --target=ai_deck --platform=board --work-dir="$1" --config-ini="$1"/../uart.ini      run --exec-prepare --exec --binary="$1"/"$2"

gap8-openocd -d0 -c 'gdb_port disabled; telnet_port disabled; tcl_port disabled' -f "$GAPY_OPENOCD_CABLE" -f target/gap8revb.tcl -f tcl/jtag_boot_entry.tcl -c 'gap8_jtag_load_binary_and_start "$1"/"$2" elf 0x1c000080'