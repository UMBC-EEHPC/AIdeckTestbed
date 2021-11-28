#include "Assertions.h"

void operator delete[](void* ptr) {
    assert_gap8(ptr);
}