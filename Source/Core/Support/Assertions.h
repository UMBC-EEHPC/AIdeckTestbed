#pragma once

#include <Core/Support/gap_sdk.h>

#define assert_gap8(x) \
    if (!(x)) { \
        printf("ASSERTION FAILED %s:%d %s on core %ld\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, pi_core_id()); \
        pmsis_exit(-1); \
    }

#define assert_not_reached_gap8() { \
    printf("ASSERTION TRIGGERED %s:%d %s on core %ld\n", __FILE__, __LINE__, __PRETTY_FUNCTION__, pi_core_id()); \
    pmsis_exit(-1); }
