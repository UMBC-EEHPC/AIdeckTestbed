#include "Assertions.h"

void operator delete[](void* ptr)
{
    assert_not_reached_gap8();
}