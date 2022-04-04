# Pitfalls

Some non-obvious issues that have arisen while writing code for the GAP8...

## JTAG Cable Usage

Bitcraze is working on a method of flashing the GAP8 and NINA OTA using WiFi and/or the Crazyradio, however it's still not fully complete so for now, the JTAG cable is still a necessity for doing much of anything with the AI-deck. Unfortunately, the JTAG cable seems to be a bit buggy, *especially* when taking power measurements. Sometimes the flasher will error out and report it's receiving all zero's or all one's when you attempt to flash an image. Usually when this happens, you'll have to manually kill the various processes launched by the flasher from the terminal, as well as turn off the Crazyflie/AI-deck, disconnect the AI-deck, reconnect it, then turn it back on. However, this doesn't always solve the issue, especially if you have the AI-deck/Crazyflie partly disassembled for taking power measurements. In the latter case, the fix seems to be to effectively pull apart the whole entire power measurement setup, disconnect every wire, and then reconnect it. It's a bit time consuming and annoying, but it seems to be the only effective solution at the moment.  

## SDK

As mentioned within [Toolchain.md](Toolchain.md), don't use the Bitcraze Docker image if you intend on doing anything with neural networks, the version of NNTool and AutoTiler that the Docker image ships with are out of date and have their fair share of bugs. 

## OS'

The GAP8 has 3 different OS' available as of the time of writing, PMSIS, FreeRTOS, and PULP-OS. All of them are RTOS', and all of them are rather barebones, only really providing a thin wrapper around the hardware. This project uses the PMSIS OS. The only thing to really say about these is that although at a very high level glance their API's somewhat resemble API's you might see on a traditional desktop OS, they usually aren't the same, and there's often somewhat hidden gotchas. Thus, be careful to read the API docs and/or look at the implementation, before using a set of functions.

## Memory Ordering

[This article is highly recommended](https://preshing.com/20120930/weak-vs-strong-memory-models/), but to sum it up, memory ordering is essentially the order in which CPUs make reads and writes to memory, and the order in which those reads/writes become visible to other processors. As the GAP8 is based on the RISC-V architecture, it, like the majority of RISC-V cores, is weakly ordered. Although for 90% of the code you write this won't be an issue, if you're trying to directly manipulate the GAP8's hardware and peripherals without using the GAP SDK's API's, or you're actively sharing variables in memory between cores, this is something you'll have to be aware of. 

Yet another challenge that adds onto this is that L2 memory is slow, if you write a value and then immediately try to read/write that value from another core, don't necessarily expect the other core to correctly "see" that value until it has finished being sent to RAM.

## Stack Allocation

Several issues to be aware of, for one thing, when calling a GAP SDK function that takes in a pointer to a struct in memory, make sure that that struct is allocated in the correct part of memory. Some functions expect the struct to stick around for a long period of time, and allocating a struct on the stack doesn't exactly guarantee this, as stack allocated variables tend to be destroyed at the end of the function call they're allocated in. I (Edward) had an issue while experimenting with FreeRTOS where my program kept randomly hitting access errors for seemingly no reason, and it turned out that it was because I was allocating a task struct on the stack, which was immediately being cleared the moment the program jumped into the new task. 

A second thing to be aware of, the default stack sizes used by the GAP8's Fabric Controller and it's cluster cores are very small, around 4KB for the Fabric Controller and only a single KB for each of the cluster cores. Depending on what you're doing, especially if you're using any neural networks, these stack sizes may have to be adjusted. Do be careful though that if you're using an AutoTiler model, you adjust the L1 memory available to the model as well as the stack size, otherwise the AutoTiler model may end up trying to read/write data meant for the heap onto stack memory and cause corruptions.

A final thing to be aware of is that the stack for both the Fabric Controller and cluster cores is located within L1 memory. As such, if talking to any peripherals or buses and you want to send stack data, you'll need to copy that data from the stack into L2 memory first.

## PMSIS API Heap Allocation

For real time applications, you generally shouldn't ever allocate or free memory using a standard heap allocator during program execution except during program startup and shutdown. However, when you do allocate memory, be extremely careful that you free any allocations you make in LIFO order. If you don't, the PMSIS heap allocator will lose track of its free space and likely cause an allocation failure next time you try making an allocation. So as an example, if you allocate 3 objects, but then you free the second object before freeing the other objects, your next allocation will likely fail.
![](InlineImages/pmsis_heap_allocator.png)
*In this example, various objects were allocated but then freed out of the order they were allocated in, as you can see, the PMSIS API's heap allocator essentially "forgot" it had hundreds of kilobytes free*

## Specifying Tasks For Cluster Cores

Although they share the same architecture and extensions as the Fabric Controller, treat the cluster cores as if they were some sort of hardware accelerator you purely submit cluster tasks to. If you're used to programming on desktop OS', you might assume you can simply launch separate threads and have some sort of scheduler distribute them across the cores. But alas, there is no way, instead the cluster cores are more akin to a graphics card, or a supercomputer. You submit one task, that one task gets forked and ran on different pieces of data across the number of cores specified by the -mPE compiler flag, then finally, the cluster will return the results of that parallel task back to the Fabric Controller.

## Atomic Operations

The default libgcc atomic operations aren't supported by the GAP8, attempting to use them will result in the program failing to link since there simply aren't any atomic operations implemented in libgcc. The GAP8 manual mentions one can use the L1 memory region for atomic operations, although I (Edward) haven't explored how to use this as of yet.

## Synchronization Primitives

The GAP SDK provides spinlocks, mutexes, etc. although for whatever reason, as of the time of writing, none of them appear on the official GreenWaves API docs. Thus, if you'd like to use a synchronization primitive that doesn't have a C++ wrapper already implemented, it's recommended to search for examples of how it's used within the GAP SDK.