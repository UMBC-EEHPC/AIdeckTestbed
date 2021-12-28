# AIdeckTestbed

Testbed for experimentation on the GAP8-based AI deck platform

## About

I like C but it's a rather dreadful language to write long programs in, and I also don't particularly like using Make either. 
As such I decided to dissect the GAP8 build system and reimplement the necessary build steps in Meson/Ninja, as well as take advantage of C++17.

The project is rather small as of right now but I hope to eventually grow this into an all-encompassing platform for conducting research and writing programs targetting the GAP8-based AI deck platform.

## Build

The following packages are required:

```bash
sudo apt-get install autoconf automake bison build-essential cmake curl doxygen flex git gtkwave libftdi-dev libftdi1 libjpeg-dev libsdl2-dev libsdl2-ttf-dev libsndfile1-dev graphicsmagick-libmagick-dev-compat libtool libusb-1.0-0-dev pkg-config python3-pip rsync scons texinfo wget libmpfr-dev libmpc-dev libgmp-dev texinfo gcc-10 g++-10 ninja
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

The build script will pause at least twice, once to ask for the password in order to install OpenOCD, and again in order for you to follow the steps to acquire AutoTiler

Once building the Toolchain is completed, one can build the AIdeckTestbed with the following commands.

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

This will build the project to run on the AI deck itself.

## License

AIdeckTestbed is licensed under the MIT License.

This project uses [GreenWaves Technologies' GAP SDK](https://github.com/GreenWaves-Technologies/gap_sdk) which is licensed under the Apache 2.0 license.

This project uses the [Embedded Template Library](https://github.com/ETLCPP/etl) which is licensed under the MIT License.
