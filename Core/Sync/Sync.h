#pragma once

#define MEMORY_BARRIER() __asm__ __volatile__ ("" : : : "memory");