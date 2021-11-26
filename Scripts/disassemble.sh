#!/bin/sh
riscv32-unknown-elf-objdump -d -h -S -t -w --show-raw-insn "$1" > "$1.s"