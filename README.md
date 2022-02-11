# AIdeckTestbed

Testbed for experimentation on the GAP8-based AI-deck platform.

## About

This is a somewhat hacked together project designed to benchmark the power usage and CPU cycles/time taken by different neural network models on the AI-deck. It can be run in the GVSOC emulator as well as on the AI-deck itself, although some preprocessor macros will need to be changed inside Benchmarks.h.

## Organization

The project is organized as follows:

```
Core/Containers/ - contains some helpers that wrap ETL
Core/Device/ - contains some C++ wrappers for AI-deck peripherals
Core/Heap/ - contains some C++ wrappers for heap allocation
Core/Support/ - contains some miscellaneous headers and miscellaneous C++ runtime functions
Core/Sync/ - contains some C++ wrappers for PMSIS synchronization primitives

Gapack/ - barely-even-started linear algebra library, not used in this project

Model/ - contains everything related to the neural net models
Model/Data/ - contains some miscellaneous required headers, some scripts for exporting the models to the AI-deck, and code required to generate the bilinear resize kernel for the AI-deck

Scripts/ - contains some helper scripts used by Meson during compilation

Toolchain/ - contains everything necessary to download, compile, and install GCC, Binutils, and the GAP8 SDK inside this repo directory

/ - contains everything else including program startup code
```

## Build

The following packages are required:

```bash
sudo apt-get install autoconf automake bison build-essential cmake curl doxygen flex git gtkwave libftdi-dev libftdi1 libjpeg-dev libsdl2-dev libsdl2-ttf-dev libsndfile1-dev graphicsmagick-libmagick-dev-compat libtool libusb-1.0-0-dev pkg-config python3-pip rsync scons texinfo wget libmpfr-dev libmpc-dev libgmp-dev texinfo gcc-10 g++-10 ninja-build
```

The version of meson that ships with Ubuntu/Debian is out of date, thus, it's recommended to install it with:

```bash
sudo pip3 install meson
```

Building the toolchain and SDK is rather simple, only requiring these commands:

```bash
cd Toolchain
./BuildToolchain.sh
source SourceToolchain.sh
```

The build script will pause at least twice, once to ask for a password in order to install OpenOCD using sudo, and again in order for you to follow some steps to acquire the AutoTiler library.

Once the toolchain is finished building, you can build the AIdeckTestbed project. By default, the mobilenet model is selected, and I didn't implement any way of switching this using the Meson script, so unfortunately you will have to switch to Resnet manually if you would like to try using that network. Rename resnet_meson.build to meson.build and rename resnet.tflite to ptq_int8.tflite.

```bash
meson build --cross-file ai_deck.ini
cd build
```

This will setup the build directory.

**g++ will throw plenty of warnings during compilation, unfortunately the SDK headers weren't written with C++ support in mind, and as such, g++ isn't happy. I want to fix this at some point but haven't gotten around to it yet.**

```bash
ninja size_gvsoc disassemble_gvsoc gvsoc
```

This will build the project to run under the GVSOC emulator.

```bash
ninja size_aideck disassemble_aideck aideck
```

This will build the project to run on the AI-deck.

Everytime you restart your shell you will likely need to execute the following commands inside the Toolchain directory.

```bash
source SourceToolchain.sh
```

This will add all of the required environment variables necessary to use the SDK, and it will also add the compiler installation directory to your path variable.

## License

AIdeckTestbed is licensed under the MIT License.

This project uses [GreenWaves Technologies' GAP SDK](https://github.com/GreenWaves-Technologies/gap_sdk) which is licensed under the Apache 2.0 license.

This project uses the [Embedded Template Library](https://github.com/ETLCPP/etl) which is licensed under the MIT License.
