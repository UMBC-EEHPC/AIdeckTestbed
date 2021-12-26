DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
export GAP_RISCV_GCC_TOOLCHAIN="$DIR/Local"
export PATH="$DIR/Local/bin:$DIR/Local/Anaconda/bin:$PATH"
source "$DIR/gap_sdk/configs/ai_deck.sh"
export GAPY_OPENOCD_CABLE=interface/ftdi/olimex-arm-usb-tiny-h.cfg