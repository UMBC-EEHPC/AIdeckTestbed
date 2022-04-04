# Build

The following packages are required:

```bash
sudo apt-get install autoconf automake bison build-essential cmake curl doxygen flex git gtkwave libftdi-dev libftdi1 libjpeg-dev libsdl2-dev libsdl2-ttf-dev libsndfile1-dev graphicsmagick-libmagick-dev-compat libtool libusb-1.0-0-dev pkg-config python3-pip rsync scons texinfo wget libmpfr-dev libmpc-dev libgmp-dev texinfo gcc-10 g++-10 ninja-build
```

The version of meson that ships with Ubuntu/Debian is out of date, thus, it's recommended to install it with:

```bash
sudo pip3 install meson
```

Building the toolchain and SDK is rather simple, only requiring these commands

```bash
cd Toolchain
./BuildToolchain.sh
source SourceToolchain.sh
```

The build script will automatically download the Embedded Template Library and GAP SDK Git submodules, as well as download the submodules that they themselves use.

The build script will pause at least twice, once to ask for a password in order to install OpenOCD using sudo, and again in order for you to follow some steps to acquire the AutoTiler library.

Once the toolchain is finished building, one can build the AIdeckTestbed with the following commands.

```bash
meson build --cross-file ai_deck.ini
cd build
```

This will setup the build directory.

```bash
ninja size_gvsoc disassemble_gvsoc gvsoc
```

This will build the project to run under the GVSOC emulator.

```bash
ninja size_aideck disassemble_aideck aideck
```

This will build the project to run on the AI-deck.