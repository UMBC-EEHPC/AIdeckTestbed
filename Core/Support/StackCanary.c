#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdint.h>
#include <pmsis.h>

const uintptr_t __stack_chk_guard = 0xccc0ffee;

#ifdef __cplusplus
[[noreturn]]
#endif
void __stack_chk_fail()
{
    printf("Stack overrun!");
    pmsis_exit(-21);
}

#ifdef __cplusplus
}
#endif