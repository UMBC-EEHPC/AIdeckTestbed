#include <Core/Support/gap_sdk.h>
#include <stdint.h>

extern "C" {

extern const uintptr_t __stack_chk_guard = 0xccc0ffee;

void __stack_chk_fail()
{
    printf("Stack overrun!");
    pmsis_exit(-21);
}
}