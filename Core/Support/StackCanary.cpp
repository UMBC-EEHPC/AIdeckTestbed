extern "C" {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wregister"
#include <stdio.h>
#include <stdint.h>
#include <pmsis.h>
#pragma GCC diagnostic pop

extern const uintptr_t __stack_chk_guard = 0xccc0ffee;

void __stack_chk_fail()
{
    printf("Stack overrun!");
    pmsis_exit(-21);
}

}