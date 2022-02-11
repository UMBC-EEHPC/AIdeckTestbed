#include "Mutex.h"

using namespace Core::Heap;

namespace Core::Sync {

Mutex::Mutex()
{
    MEMORY_BARRIER()
    m_mutex = static_cast<pmsis_mutex_t*>(L1Heap::self().allocate(sizeof(pmsis_mutex_t)));
    MEMORY_BARRIER()
    eu_mutex_init(reinterpret_cast<uint32_t>(m_mutex));
    MEMORY_BARRIER()
}

void Mutex::lock()
{
    MEMORY_BARRIER()
    eu_mutex_lock(reinterpret_cast<uint32_t>(m_mutex));
    MEMORY_BARRIER()
}

void Mutex::unlock()
{
    MEMORY_BARRIER()
    eu_mutex_unlock(reinterpret_cast<uint32_t>(m_mutex));
    MEMORY_BARRIER()
}

Mutex::~Mutex()
{
    MEMORY_BARRIER()
    eu_mutex_unlock(reinterpret_cast<uint32_t>(m_mutex));
    MEMORY_BARRIER()
    L1Heap::self().deallocate(m_mutex, sizeof(pmsis_mutex_t));
}

}