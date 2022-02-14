# Toolchain

This document covers the GAP8 toolchain plus various libraries used in this project

# Background

There's a Docker image published by Bitcraze which has an entire GAP SDK + Toolchain instance setup inside of it, and although it works for simple applications, the GAP SDK it uses is, at least as of the time of writing, extremely out of date by a year or so. This caused plenty of headaches when attempting to begin exporting neural networks for the GAP8, so as a result, it is highly recommended one downloads and installs the latest GAP SDK along with the various bits required to use it, like GreenWaves' compiler and linker.

# Setting Up The Toolchain

This repository contains a bash script that will automatically download, compile, and install the GAP SDK, GCC, Binutils, Embedded Template Library, and GoogleTest. Unfortunately, as the script is somewhat cobbled together just like the rest of the project, it isn't very robust. If the build fails for any reason, you're likely going to either have to continue the rest of the build by hand, or delete the intermediate files and restart the build.

The build instructions are located within [Build.md](Build.md).

# GCC & Binutils

As the GAP8 contains some nonstandard extensions, GreenWaves Technologies maintains a custom fork of GCC 7.1.1 and Binutils 2.28, both of which are somewhat out of date at this point. Ideally LLVM can gain codegen support for the GAP8's custom instructions and compiler options at some point, but failing that, there's an up to date fork of GCC and Binutils maintained for the CV32E40P core used by the GAP8 which could possibly be adapted. 

Returning to GreenWaves' GCC, the main feature to be aware of is that one can specify the number of cluster cores available for cross compilation using the -mPE=X CFLAG, with X being the number of cluster cores one wants to use, it can range anywhere between 1 and 8. 

![](InlineImages/core_cycles.png)

# C++ Embedded Template Library

Although the BuildToolchain.sh script compiles g++ with libstdc++ enabled, libstdc++ mostly doesn't work as the Newlib port to the GAP8 is incomplete. As such, apart from std::initializer_list, this project doesn't use any of the C++ standard library and instead uses the Embedded Template Library (ETL). As the name would suggest, ETL is designed to be a sort of C++ standard library replacement optimized for embedded microcontrollers like the GAP8. Fortunately, despite the constraints faced by programming for microcontrollers, the ETL manages to provides a reimplementation of large portions of the most commonly used parts of the C++ standard library.

# GAP SDK

The main piece of software for interfacing with the GAP8 as well as the AI-deck's hardware, this contains implementations written in C of hardware drivers, math functions, image encoding functions, and more. This also comes with a GAP8 emulator, known as GVSOC. 