#pragma once

#include <Core/Support/Assertions.h>
#include <Core/Support/gap_sdk.h>

namespace Core::Heap {

class L1Heap;
static L1Heap* g_l1_allocator;

class L1Heap {
public:
    L1Heap()
    {
        g_l1_allocator = this;
    }

    [[nodiscard]] void* allocate(size_t size)
    {
        return pi_fc_l1_malloc(size);
    }
    void deallocate(void* ptr, size_t size)
    {
        return pi_fc_l1_free(ptr, size);
    }

    static L1Heap& self()
    {
        return *g_l1_allocator;
    }
};

template<typename T>
struct L1Deleter {
    void operator()(T* ptr) const
    {
        L1Heap::self().deallocate(ptr, sizeof(T));
    }
};

}