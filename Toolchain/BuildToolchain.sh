#!/usr/bin/env bash
set -e
# This file is ripped right from https://github.com/SerenityOS/serenity
# Thank you to all of the SerenityOS contributors who helped create this file
# This file will need to be run in bash, for now.


# === CONFIGURATION AND SETUP ===

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

echo "$DIR"

TARGET="riscv32-unknown-elf"
PREFIX="$DIR/Local"

MAKE=make
MD5SUM=md5sum
if [ "$(uname)" = "Darwin" ]; then
NPROC="sysctl -n hw.logicalcpu"
else
NPROC=nproc
fi

echo PREFIX is "$PREFIX"

mkdir -p "$DIR/Tarballs"

PULP_RISCV_GNU_TOOLCHAIN_CHKSUM="49dea1915979fdf91eb2ad4a8873e4cd88a6b811"
PULP_RISCV_GNU_TOOLCHAIN_NAME="pulp-riscv-gnu-toolchain"
PULP_RISCV_GNU_TOOLCHAIN_PKG="${PULP_RISCV_GNU_TOOLCHAIN_NAME}"
PULP_RISCV_GNU_TOOLCHAIN_BASE_URL="https://github.com/pulp-platform/pulp-riscv-gnu-toolchain.git"

OPENOCD_CHKSUM="b84d97ec4d2e601e704b54351e954b1c58d41683"
OPENOCD_NAME="gap8_openocd"
OPENOCD_PKG="${OPENOCD_NAME}"
OPENOCD_BASE_URL="https://github.com/GreenWaves-Technologies/gap8_openocd.git"

BINUTILS_CHKSUM="9354b50c27ac053d1c1f24abd3e8ac0496dc5da3"
BINUTILS_NAME="pulp-riscv-binutils-gdb"
BINUTILS_PKG="${BINUTILS_NAME}"
BINUTILS_BASE_URL="https://github.com/pulp-platform/pulp-riscv-binutils-gdb.git"

GCC_CHKSUM="335f3b6365b466ff65d400bd2182e267c2d3aae6"
GCC_NAME="pulp-riscv-gcc"
GCC_PKG="${GCC_NAME}"
GCC_BASE_URL="https://github.com/pulp-platform/pulp-riscv-gcc.git"

NEWLIB_CHKSUM="1e52935101d096bb2e9381c7b131d6b976f0acd9"
NEWLIB_NAME="pulp-riscv-newlib"
NEWLIB_PKG="${NEWLIB_NAME}"
NEWLIB_BASE_URL="https://github.com/pulp-platform/pulp-riscv-newlib.git"

GTEST_VERSION="1.11.0"
GTEST_MD5SUM="e8a8df240b6938bb6384155d4c37d937"
GTEST_NAME="release-$GTEST_VERSION"
GTEST_PKG="${GTEST_NAME}.tar.gz"
GTEST_BASE_URL="https://github.com/google/googletest/archive/refs/tags"

ANACONDA_VERSION="3-2020.07"
if [ "$(uname)" = "Linux" ]; then
ANACONDA_NAME="Anaconda${ANACONDA_VERSION}-Linux-x86_64"
ANACONDA_MD5SUM="1046c40a314ab2531e4c099741530ada"
elif [ "$(uname)" = "Darwin" ]; then
ANACONDA_NAME="Anaconda${ANACONDA_VERSION}-MacOSX-x86_64"
ANACONDA_MD5SUM="50f20c90b8b5bfdc09759c09e32dce68"
fi
ANACONDA_PKG="${ANACONDA_NAME}.sh"
ANACONDA_BASE_URL="https://repo.anaconda.com/archive"

GAP_SDK_CHKSUM="092a315287a149cf2280f8f47470c44e511f2090"

# === DOWNLOAD AND PATCH ===

pushd "$DIR/Tarballs"
    if [ ! -e $PULP_RISCV_GNU_TOOLCHAIN_PKG ] ; then
        rm -rf $PULP_RISCV_GNU_TOOLCHAIN_PKG
        git clone "$PULP_RISCV_GNU_TOOLCHAIN_BASE_URL"
        pushd "$PULP_RISCV_GNU_TOOLCHAIN_PKG"
        git checkout "$PULP_RISCV_GNU_TOOLCHAIN_CHKSUM"
        patch -p1 < "$DIR"/Patches/riscv_linker_script.patch > /dev/null
        popd
    else
        echo "Skipped downloading openocd"
    fi

    if [ ! -e $OPENOCD_PKG ] ; then
        rm -rf $OPENOCD_PKG
        git clone "$OPENOCD_BASE_URL"
        pushd "$OPENOCD_PKG"
        git checkout "$OPENOCD_CHKSUM"
        popd
    else
        echo "Skipped downloading openocd"
    fi

    if [ ! -e $BINUTILS_PKG ] ; then
        rm -rf $BINUTILS_PKG
        git clone "$BINUTILS_BASE_URL"
        pushd "$BINUTILS_PKG"
        git checkout "$BINUTILS_CHKSUM"
        popd
    else
        echo "Skipped downloading binutils"
    fi

    if [ ! -e $GCC_PKG ] ; then
        rm -rf $GCC_PKG
        git clone "$GCC_BASE_URL"
        pushd "$GCC_NAME"
        git checkout "$GCC_CHKSUM"
        popd
        ln -s $GCC_NAME riscv-gcc
    else
        echo "Skipped downloading gcc"
    fi

    if [ ! -e $NEWLIB_PKG ] ; then
        rm -rf $NEWLIB_PKG
        git clone "$NEWLIB_BASE_URL"
        pushd "$NEWLIB_PKG"
        git checkout "$NEWLIB_CHKSUM"
        popd
    else
        echo "Skipped downloading newlib"
    fi

    md5="$($MD5SUM ${GTEST_PKG} | cut -f1 -d' ')"
    echo "gc md5='$md5'"
    if [ ! -e $GTEST_PKG ] || [ "$md5" != ${GTEST_MD5SUM} ] ; then
        rm -f $GTEST_PKG
        wget "$GTEST_BASE_URL/$GTEST_PKG"
    else
        echo "Skipped downloading googletest"
    fi

    md5="$($MD5SUM ${ANACONDA_PKG} | cut -f1 -d' ')"
    echo "gc md5='$md5'"
    if [ ! -e $ANACONDA_PKG ] || [ "$md5" != ${ANACONDA_MD5SUM} ] ; then
        rm -f $ANACONDA_PKG
        wget "$ANACONDA_BASE_URL/$ANACONDA_PKG"
    else
        echo "Skipped downloading anaconda"
    fi

    if [ "$(uname)" = "Darwin" ]; then
        pushd "$GCC_PKG"
        ./contrib/download_prerequisites
        popd
    fi

    if [ ! -d $GTEST_NAME ]; then
        echo "Extracting googletest..."
        tar -xzf $GTEST_PKG
    else
        echo "Skipped extracting googletest"
    fi

    echo "XXX install anaconda"
    bash "$ANACONDA_PKG" -b -f -p "$PREFIX"/Anaconda
    eval "$($PREFIX/Anaconda/bin/conda shell.bash hook)"
    conda init

    export PATH="$PREFIX/Anaconda/bin:$PATH"

popd


# === COMPILE AND INSTALL ===

mkdir -p "$PREFIX"
mkdir -p "$DIR/Build"
cp -R "$DIR/Tarballs/${OPENOCD_NAME}" "$DIR/Build/" || true
cp -R "$DIR/Tarballs/${NEWLIB_NAME}" "$DIR/Build/" || true
mkdir -p "$DIR/Build/binutils"
mkdir -p "$DIR/Build/gcc"
mkdir -p "$DIR/Build/gtest"

if [ -z "$MAKEJOBS" ]; then
    MAKEJOBS=$($NPROC)
fi

pushd "$DIR/Build/"
    unset PKG_CONFIG_LIBDIR # Just in case

    if [ "$(uname)" = "Linux" ]; then
        pushd ${OPENOCD_NAME}
            ./bootstrap
            ./configure --program-prefix=gap8- \
                                            --prefix="$PREFIX" \
                                            --datarootdir="$PREFIX"/share/gap8-openocd \
                                            || exit 1
            echo "XXX build openocd"
            "$MAKE" -j "$MAKEJOBS" || exit 1
            echo "XXX install openocd"
            "$MAKE" install || exit 1

            
            sudo cp "$PREFIX"/share/gap8-openocd/openocd/contrib/60-openocd.rules /etc/udev/rules.d || exit 1
            sudo udevadm control --reload-rules && sudo udevadm trigger || exit 1
            sudo usermod -a -G dialout "$USER" || exit 1
        popd
    fi
    
    pushd binutils
        "$DIR"/Tarballs/"$BINUTILS_NAME"/configure --target=$TARGET \
                                                --prefix="$PREFIX" \
                                                --disable-nls \
                                                --without-isl \
                                                --disable-werror \
                                                --disable-gdb \
                                                || exit 1
        if [ "$(uname)" = "Darwin" ]; then
            # under macOS generated makefiles are not resolving the "intl"
            # dependency properly to allow linking its own copy of
            # libintl when building with --enable-shared.
            "$MAKE" -j "$MAKEJOBS" || true
            pushd intl
            "$MAKE" all-yes
            popd
        fi
        echo "XXX build binutils"
        "$MAKE" -j "$MAKEJOBS" || exit 1
        echo "XXX install binutils"
        "$MAKE" install || exit 1
    popd

    pushd gcc
        "$DIR"/Tarballs/"$GCC_NAME"/configure --target="$TARGET" \
                                                --prefix="$PREFIX" \
                                                --disable-shared \
                                                --disable-threads \
                                                --enable-languages=c \
                                                --with-system-zlib \
                                                --enable-tls \
                                                --disable-libmudflap \
                                                --disable-libssp \
                                                --disable-libquadmath \
                                                --disable-libgomp \
                                                --disable-nls \
                                                --without-isl \
                                                --enable-checking=yes \
                                                --enable-multilib \
                                                --with-abi=ilp32 \
                                                --with-arch=rv32imcxgap9 \
                                                'CFLAGS_FOR_TARGET=-Os  -mcmodel=medlow' \
                                                || exit 1

        echo "XXX build gcc and libgcc"
        "$MAKE" -j "$MAKEJOBS" all || exit 1
        echo "XXX install gcc and libgcc"
        "$MAKE" -j "$MAKEJOBS" install || exit 1
    popd

    pushd ${NEWLIB_NAME}
        export PATH="$PREFIX/bin:$PATH"
        ./configure --target="$TARGET" \
                                                --prefix="$PREFIX" \
                                                || exit 1
        echo "XXX build newlib"
        "$MAKE" -j "$MAKEJOBS" all || exit 1
        echo "XXX install newlib"
        "$MAKE" install || exit 1
    popd

    rm -rf gcc/*

    pushd gcc
        "$DIR"/Tarballs/"$GCC_NAME"/configure --target=$TARGET \
                                                --prefix="$PREFIX" \
                                                --disable-shared \
                                                --disable-threads \
                                                --enable-languages=c,c++ \
                                                --with-system-zlib \
                                                --enable-tls \
                                                --with-newlib \
                                                --with-headers="$PREFIX"/$TARGET/include \
                                                --disable-libmudflap \
                                                --disable-libssp \
                                                --disable-libquadmath \
                                                --disable-libgomp \
                                                --disable-nls \
                                                --without-isl \
                                                --enable-checking=yes \
                                                --enable-multilib \
                                                --with-abi=ilp32 \
                                                --with-arch=rv32imcxgap9 \
                                                'CFLAGS_FOR_TARGET=-Os  -mcmodel=medlow' \
                                                || exit 1

        echo "XXX build gcc and libgcc"
        "$MAKE" -j "$MAKEJOBS" all || exit 1
        echo "XXX install gcc and libgcc"
        "$MAKE" -j "$MAKEJOBS" install || exit 1
    popd

    pushd gtest
        cmake "$DIR"/Tarballs/googletest-$GTEST_NAME \
                                                -DCMAKE_INSTALL_PREFIX="$PREFIX" \
                                                || exit 1

        echo "XXX build googletest"
        "$MAKE" -j "$MAKEJOBS" || exit 1
        echo "XXX install googletest"
        "$MAKE" install || exit 1
    popd

popd

cp "$DIR"/Tarballs/"$PULP_RISCV_GNU_TOOLCHAIN_NAME"/riscv.ld "$PREFIX"/riscv32-unknown-elf/lib

# === DOWNLOAD OFFICIAL SDK ===
echo "XXX install nntools requirements"
git clone https://github.com/GreenWaves-Technologies/gap_sdk.git
pushd "$DIR/gap_sdk"
    git checkout "$GAP_SDK_CHKSUM"
    
    source configs/ai_deck.sh

    pip install -r tools/nntool/requirements.txt
    pip install -r requirements.txt

    git submodule update --init --recursive

    echo "XXX build gap8 sdk"
    make all PULP_RISCV_GCC_TOOLCHAIN="$PREFIX"

    make install INSTALL_DIR="$PREFIX"

popd