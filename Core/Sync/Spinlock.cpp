#include "Spinlock.h"

using namespace Core::Heap;

namespace Core::Sync {

Spinlock::Spinlock() {
    MEMORY_BARRIER()
    m_spinlock_meta = static_cast<int32_t*>(L1Heap::self().allocate(sizeof(int32_t)));
    m_spinlock = static_cast<spinlock_t*>(L2Heap::self().allocate(sizeof(spinlock_t)));
    MEMORY_BARRIER()
    cl_sync_init_spinlock(m_spinlock, m_spinlock_meta);
    MEMORY_BARRIER()
}

void Spinlock::lock() {
    MEMORY_BARRIER()
    cl_sync_spinlock_take(m_spinlock);
    MEMORY_BARRIER()
}

void Spinlock::unlock() {
    MEMORY_BARRIER()
    cl_sync_spinlock_release(m_spinlock);
    MEMORY_BARRIER()
}

Spinlock::~Spinlock() {
    MEMORY_BARRIER()
    L1Heap::self().deallocate(m_spinlock_meta, sizeof(int32_t));
    L2Heap::self().deallocate(m_spinlock, sizeof(spinlock_t));
}

}