#!/bin/sh
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../uart.ini    run --image --binary="$1"/"$2" #--trace=fc/insn 
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../uart.ini    run --flash --binary="$1"/"$2" #--trace=fc/insn 
gapy --target=ai_deck --platform=gvsoc --work-dir=. --config-ini="$1"/../uart.ini    run --exec-prepare --exec --binary="$1"/"$2" #--trace=fc/insn 