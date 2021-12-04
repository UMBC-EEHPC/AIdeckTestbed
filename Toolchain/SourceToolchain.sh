DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
export PATH="$DIR/Local/bin:$DIR/Local/Anaconda/bin:$PATH"
export PULP_RISCV_GCC_TOOLCHAIN_CI="$DIR/Local"
source "$DIR/gap_sdk/configs/ai_deck.sh"