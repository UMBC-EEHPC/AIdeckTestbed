#pragma once

#include <Core/Support/Assertions.h>
#include <Core/Support/gap_sdk.h>

namespace Core::Heap {

class L2Heap;
static L2Heap* g_l2_allocator;

class L2Heap {
public:
    L2Heap()
    {
        g_l2_allocator = this;
    }

    [[nodiscard]] void* allocate(size_t size)
    {
        return pi_l2_malloc(size);
    }
    void deallocate(void* ptr, size_t size)
    {
        return pi_l2_free(ptr, size);
    }

    static L2Heap& self()
    {
        return *g_l2_allocator;
    }
};

template<typename T>
struct L2Deleter {
    void operator()(T* ptr) const
    {
        L2Heap::self().deallocate(ptr, sizeof(T));
    }
};

}