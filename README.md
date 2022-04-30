# AIdeckTestbed

![logo](Documentation/InlineImages/eehpc_logo.png)

**UMBC Energy Efficient High Performance Computing Lab**

**Faculty:** Dr. Tinoosh Mohsenin <tinoosh@umbc.edu>

[***Previous work***](https://github.com/GriffinBonner/ai-deck_obs_native)

## About

The project serves as a platform for conducting research into low power edge inference making on the GAP8-based AI-deck extension board for the Crazyflie 2.1 drones. 

## Documentation

| Link | Description |
| ------ | ------ |
| [AIdeckPeripherals](Documentation/AIdeckPeripherals.md) | An explanation of some peripherals associated with the AI-deck |
| [Build](Documentation/Build.md) | Some build instructions for compiling and using this project |
| [GAP8](Documentation/GAP8.md) | A writeup on the design of the GAP8 SoC used on the AI-deck |
| [Pitfalls](Documentation/Pitfalls.md) | A warning about potential issues one might face when programming embedded systems, particularly the GAP8 |
| [Project](Documentation/Project.md) | A description of how the project is arranged |
| [Toolchain](Documentation/Toolchain.md) | A description of the GAP8's custom set of tools and compilers, plus this project's Meson build system |

## License

AIdeckTestbed is licensed under the MIT License.

This project uses [GreenWaves Technologies' GAP SDK](https://github.com/GreenWaves-Technologies/gap_sdk) which is licensed under the Apache 2.0 license.

This project uses the [Embedded Template Library](https://github.com/ETLCPP/etl) which is licensed under the MIT license.

This project uses the [GoogleTest testing and mocking framework](https://github.com/google/googletest) which is licensed under the BSD 3-Clause license.