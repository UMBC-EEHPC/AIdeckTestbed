# Build

The following packages are required:

```bash
sudo apt-get install autoconf automake bison build-essential cmake curl doxygen flex git gtkwave libftdi-dev libftdi1 libjpeg-dev libsdl2-dev libsdl2-ttf-dev libsndfile1-dev graphicsmagick-libmagick-dev-compat libtool libusb-1.0-0-dev pkg-config python3-pip rsync scons texinfo wget libmpfr-dev libmpc-dev libgmp-dev texinfo gcc-10 g++-10 ninja-build
```

The version of meson that ships with Ubuntu/Debian is out of date, thus, it's recommended to install it with:

```bash
sudo pip3 install meson
```

Building the toolchain requires the following commands

```bash
cd Toolchain
git submodule init
git submodule update --recursive
./BuildTools.sh
./BuildGAPSDK.sh
source SourceToolchain.sh
```

The build script will pause at least twice, once to ask for a password in order to install OpenOCD using sudo, and again in order for you to follow some steps to acquire the AutoTiler library.

Once you've built the compiler, linker, and debugger/flasher, you can generally leave those alone in between updates, in the future when you pull down the repository you'll likely only need to rebuild the GAP SDK.

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

### Warning: Make sure to run ninja clean or meson setup --wipe in between rebuilding the project for the GVSOC emulator or directly for the AIdeck, as well as in between changing the neural network. As for the former, although they mostly build the same code, there's some subtle differences in between what compiler flags and features get enabled for that same code, so as a result, building without cleaning will cause code designed specifically for GVSOC to get reused on the AIdeck, causing possible issues. Likewise, for the latter, the already-built code will continue referencing symbols created when converting the previous model.

```bash
ninja size_aideck disassemble_aideck aideck
```

This will build the project to run on the AI-deck.
