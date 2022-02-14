# GAP8

This document details various bits of information about the GAP8 processor on the AI-deck as it is used by this project.

## The GAP8 Processor
![](InlineImages/ri5cy_overview.png)
*The GAP8 block diagram*

The GAP8 is an ultra low power 32 bit RISC-V processor which derives from the PULP (Parallel Ultra Low Power) project, using various bits and pieces as necessary. It contains 9 CV32E40P cores, with one serving as the main application processor, and the remaining 8 serving as cluster cores which accelerate compute-intensive workloads. The Fabric Controller has direct control over the hardware and interfaces on board the GAP8. The 8 cluster cores can be turned on/off as needed in order to save power.

## The CV32E40P Core

![](InlineImages/ri5cy_overview.png)
*The CV32E40P block diagram as seen in the RI5CY manual (note though that the internal implementation seen here isn't exactly the same as what's used within the GAP8)*

The main workhorse of the GAP8, this core was formerly known as the RI5CY when it was initially being developed by the PULP Project, but after its transfer to the OpenHW Group, is now known as CV32E40P. The CV32E40P is an in-order 4 stage 32-bit RISC-V core, implementing the Integer, Multiplication & Division, Floating Point, Compressed instructions, and custom Xpulp extensions. **However**, the CV32E40P as used by the GAP8 omits the floating point extension, and instead implements part of the supervisor mode extension along with some additional custom vector instructions. 

With 9 of these cores inside the GAP8, these cores enable edge inference-making, image postprocessing, cryptographic workloads, and more. 

## Memory

The GAP8 has 3 different levels on its memory hierarchy.

The first is L1 memory, which is split, 64KB of it is available for both the cluster cores and Fabric Controller, and then 16KB of it is available for only the Fabric Controller. L1 memory is extremely fast, only requiring a single cycle to access in 98% of cases according to the GAP8 manual.

The second is L2 memory, there's a lot more L2 memory than there is L1 memory, with the GAP8 containing around 512KB of L2 memory, the tradeoff being that L2 memory is slower to use than L1 memory. It takes nearly 5-6 cycles to read/write to L2 memory. L2 memory is also connected directly to the rest of the peripherals and buses on the GAP8, so as a result, when communicating with external hardware, this is the memory you'll be using.

Finally, there's L3 memory, unlike L2 and L1 memory, this isn't directly addressable by the processor as it's connected either over the HyperBus or the SPI interface. What this means is, you can't just write to L3 memory directly through dereferencing a pointer in C. Instead, you'll have to use the micro-DMA unit to request reads/writes, with the data being read/written through L2 memory, although luckily this is abstracted through the API's available in the GAP SDK. Some other downsides to L3 memory besides it being more difficult to access are that it's both significantly slower than even L2 memory, and it also draws significantly more power, thus it's recommended to disable it as soon as you're done using it. The big upside though, is that one can attach a virtually unlimited amount of memory over L3, dozens of megabytes or more. The neural networks exported from NNTool/AutoTiler tend to make use of it for storing tensors and other associated data that simply can't be fit into L1 or L2 memory all at once.

Having said all of that though, it's probably possible to take advantage of C++'s language features to create an "L3 pointer" that pretends to be a regular memory mapped pointer. 

## Timers

The GAP8 has a variety of timers, which are each fed by a variety of clock sources such as frequency locked loops (FLL), FLLs with a prescaler, a 32 kHz clock crystal, and external events. The actual timers available on the GAP8 are a little bit confusingly stated in the manual. It states there's 5 timers total, 4 advanced timers which each have 4 PWM outputs, as well as a single 32 bit SysTick timer. The 4 PWM timers make sense, however, there is no singular 32 bit SysTick timer, what this likely refers to is the 32 bit timer used by the Fabric Controller, as well as the other 32 bit timer used by the cluster cores as a group. These two 32 bit timers can be combined to form a 64 bit timer value. The Fabric Controller is the main timer used by this project, luckily the GAP SDK provides a simple wrapper for reading the current timer value, rt_time_get_us().

## UART

The GAP8 has a UART peripheral built right into it, although there doesn't seem to be any documentation on its available baudrates, it seems to be able to send at a rate of anywhere between around 100 to 625000 baud/second. Since it's UART, there's not much to say about it other than that the GAP SDK contains API bindings for interacting with it.

## JTAG

This generally isn't too important, just like with most JTAG implementations, it's simply used for uploading programs and debugging those programs.

## I2C

Most microcontrollers include a I2C interface, and the GAP8 is no exception, in fact, the GAP8 has two of them. On the AI-deck, it's used by the Himax camera to transmit data to/from the GAP8. 

## SPI

Another common microcontroller interface is SPI, and the GAP8 also has two SPI interfaces. The GAP8 supports connecting HyperRAM and HyperFlash over the SPI interface, although on the AI-deck, these are connected via the HyperBus. On the AI-deck, the SPI interface is instead mainly used by the NINA WiFi/Bluetooth module to transmit/receive data to the GAP8.

## HyperBus

This is the interface through which external HyperRAM and HyperFlash are connected to the GAP8 on the AI-deck. The tradeoff between the HyperBus and the SPI is that HyperBus has a higher bandwidth, 125mHz at a maximum, although it has higher latency, making it worse for smaller transfers. On the other hand, SPI has a lower bandwidth, only up to 50-60 mHz, although it has a lower latency, making it better at smaller transfers. 