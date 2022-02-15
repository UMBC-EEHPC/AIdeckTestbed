# AIdeckTestbed Project

This project is designed to serve as a modular and reusable platform for conducting experiments and implementing ideas onto Bitcraze's AI-deck addon for its Crazyflie drones. The project is unfortunately rather messy, although it should still be able to serve as a strong foundation for building upon further.  Where possible, C++17 with GNU extensions is used, although unfortunately due to the underlying GAP SDK being primarily intended for C, it can be a bit difficult to take advantage of C++ language features such as const-correctness or lambdas in certain situations. In addition, the GAP SDK headers emit plenty of warnings when compiled under C++, mainly resulting from differences in the way type conversions are handled between C and C++. 

It is highly recommended that if contributing to this project, one installs clang-format and uses it to format their code according to the standard specified within .clang-format. For Visual Studio Code, the Microsoft C/C++ extension contains basic support for code linting and formatting, although it needs an additional extension to gain clang-format support. [xaver's clang-format extension](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format) works well for this purpose, although it will need a little bit of setup on first install.

The way this project is laid out is as follows:

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

/ - contains everything else including the program entry point
```