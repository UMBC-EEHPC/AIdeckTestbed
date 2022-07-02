#!/usr/bin/env bash
set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

TARGET="riscv32-unknown-elf"
BUILD_ARCH=$(uname -m)
PREFIX="$DIR/Local"

MAKE=make
MD5SUM=md5sum
NPROC=nproc

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

GTEST_VERSION="1.11.0"
GTEST_MD5SUM="e8a8df240b6938bb6384155d4c37d937"
GTEST_NAME="release-$GTEST_VERSION"
GTEST_PKG="${GTEST_NAME}.tar.gz"
GTEST_BASE_URL="https://github.com/google/googletest/archive/refs/tags"

ANACONDA_VERSION="2021.04"
ANACONDA_ARCH=$BUILD_ARCH
ANACONDA_NAME="Anaconda3-${ANACONDA_VERSION}-Linux-${ANACONDA_ARCH}"
if [[ $ANACONDA_ARCH == "aarch64" ]] ; then
ANACONDA_MD5SUM="14f48f5d1310478b11940a3b96eec7b6"
else
ANACONDA_MD5SUM="230f2c3c343ee58073bf41bd896dd76c"
fi
ANACONDA_PKG="${ANACONDA_NAME}.sh"
ANACONDA_BASE_URL="https://repo.anaconda.com/archive"

mkdir -p "$DIR/Downloads"

pushd "$DIR/Downloads"
    if [ ! -e $PULP_RISCV_GNU_TOOLCHAIN_PKG ] ; then
        rm -rf $PULP_RISCV_GNU_TOOLCHAIN_PKG
        git clone --depth=1 "$PULP_RISCV_GNU_TOOLCHAIN_BASE_URL"
        pushd "$PULP_RISCV_GNU_TOOLCHAIN_PKG"
        git checkout "$PULP_RISCV_GNU_TOOLCHAIN_CHKSUM"
        patch -p1 < "$DIR"/Patches/riscv_linker_script.patch > /dev/null
        popd
    else
        echo "Skipped downloading openocd"
    fi

    if [ ! -e $OPENOCD_PKG ] ; then
        rm -rf $OPENOCD_PKG
        git clone --depth=1 "$OPENOCD_BASE_URL"
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
	    patch -p1 < "$DIR"/Patches/riscv-gcc.patch > /dev/null
        popd
        ln -s $GCC_NAME riscv-gcc
    else
        echo "Skipped downloading gcc"
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

mkdir -p "$PREFIX"
mkdir -p "$DIR/Build"
cp -R "$DIR/Downloads/${OPENOCD_NAME}" "$DIR/Build/" || true
mkdir -p "$DIR/Build/binutils"
mkdir -p "$DIR/Build/gcc"
mkdir -p "$DIR/Build/gtest"

if [ -z "$MAKEJOBS" ]; then
    MAKEJOBS=$($NPROC)
fi

pushd "$DIR/Build/"
    unset PKG_CONFIG_LIBDIR # Just in case

    pushd ${OPENOCD_NAME}
        ./bootstrap
        ./configure --program-prefix=gap8- \
                                        --prefix="$PREFIX" \
                                        --datarootdir="$PREFIX"/share/gap8-openocd \
					--disable-werror \
                    --build=$BUILD_ARCH-unknown-linux-gnu \
                                        || exit 1
        "$MAKE" -j "$MAKEJOBS" || exit 1
        "$MAKE" install || exit 1

        sudo cp "$PREFIX"/share/gap8-openocd/openocd/contrib/60-openocd.rules /etc/udev/rules.d || exit 1
        sudo udevadm control --reload-rules && sudo udevadm trigger || exit 1
        sudo usermod -a -G dialout "$USER" || exit 1
    popd
    
    pushd binutils
        "$DIR"/Downloads/"$BINUTILS_NAME"/configure --target=$TARGET \
                                                --prefix="$PREFIX" \
                                                --disable-nls \
                                                --without-isl \
                                                --disable-werror \
                                                --disable-gdb \
                                                || exit 1
        "$MAKE" -j "$MAKEJOBS" || exit 1
        "$MAKE" install || exit 1
    popd

    pushd gcc
        "$DIR"/Downloads/"$GCC_NAME"/configure --target="$TARGET" \
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

        "$MAKE" -j "$MAKEJOBS" all || exit 1
        "$MAKE" -j "$MAKEJOBS" install || exit 1
    popd

    pushd gtest
        cmake "$DIR"/Downloads/googletest-$GTEST_NAME \
                                                -DCMAKE_INSTALL_PREFIX="$PREFIX" \
                                                || exit 1

        "$MAKE" -j "$MAKEJOBS" || exit 1
        "$MAKE" install || exit 1
    popd

popd

cp "$DIR"/Downloads/"$PULP_RISCV_GNU_TOOLCHAIN_NAME"/riscv.ld "$PREFIX"/riscv32-unknown-elf/lib