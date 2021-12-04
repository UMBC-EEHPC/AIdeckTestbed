#pragma once

#include <Core/Support/gap_sdk.h>
#include <Core/Heap/L1Heap.h>
#include <Core/Heap/L2Heap.h>
#include "Sync.h"

namespace Core::Sync {

class Spinlock {
    public:
        Spinlock();
        void lock();
        void unlock();
        [[gnu::always_inline]] inline bool test_and_set() { 
            return cl_sync_test_and_set_lock(m_spinlock);
        }
        ~Spinlock();
    private:
        int32_t* m_spinlock_meta;
        spinlock_t* m_spinlock;
};

class SpinlockLocker {
    public:
        [[gnu::always_inline]] inline explicit SpinlockLocker(Spinlock& mutex) :
                m_spinlock(mutex) { m_spinlock.lock(); }

        [[gnu::always_inline]] inline explicit SpinlockLocker() = delete;
        SpinlockLocker(SpinlockLocker& rhs) = delete;
        SpinlockLocker(SpinlockLocker&& rhs) = delete;
        [[gnu::always_inline]] inline SpinlockLocker& operator=(Spinlock& mutex) = delete;
        SpinlockLocker& operator=(SpinlockLocker& rhs) = delete;
        SpinlockLocker& operator=(SpinlockLocker&& rhs) = delete;

        [[gnu::always_inline]] inline void lock() { m_spinlock.lock(); }
        [[gnu::always_inline]] inline void unlock() { m_spinlock.unlock(); }

        [[gnu::always_inline]] inline ~SpinlockLocker() { m_spinlock.unlock(); }
    private:
        Spinlock& m_spinlock;
};

}