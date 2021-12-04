#pragma once

#include <Core/Support/gap_sdk.h>
#include <Core/Heap/L1Heap.h>
#include "Sync.h"

namespace Core::Sync {

class Mutex {
    public:
        Mutex();
        void lock();
        void unlock();
        ~Mutex();
    private:
        pmsis_mutex_t* m_mutex;
};

class MutexLocker {
    public:
        [[gnu::always_inline]] inline explicit MutexLocker(Mutex& mutex) :
                m_mutex(mutex) { m_mutex.lock(); }

        [[gnu::always_inline]] inline explicit MutexLocker() = delete;
        MutexLocker(MutexLocker& rhs) = delete;
        MutexLocker(MutexLocker&& rhs) = delete;
        [[gnu::always_inline]] inline MutexLocker& operator=(Mutex& mutex) = delete;
        MutexLocker& operator=(MutexLocker& rhs) = delete;
        MutexLocker& operator=(MutexLocker&& rhs) = delete;

        [[gnu::always_inline]] inline void lock() { m_mutex.lock(); }
        [[gnu::always_inline]] inline void unlock() { m_mutex.unlock(); }

        [[gnu::always_inline]] inline ~MutexLocker() { m_mutex.unlock(); }
    private:
        Mutex& m_mutex;
};

}