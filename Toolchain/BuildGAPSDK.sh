#!/usr/bin/env bash
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
PREFIX="$DIR/Local"

if [ -d "Local" ] then

    pushd "$DIR/gap_sdk"

        export GAP_RISCV_GCC_TOOLCHAIN="$PREFIX"
        
        source configs/ai_deck.sh

        git apply ../Patches/disable_flaky_werror.patch

        pip3 install -r requirements.txt
        pip3 install -r doc/requirements.txt

        git submodule update --init --recursive

        make sdk

        pushd "$DIR/gap_sdk/libs/frame_streamer"
            make all_target
        popd

    popd

else 
    echo "You need to first run BuildTools.sh before using this script!"
fi