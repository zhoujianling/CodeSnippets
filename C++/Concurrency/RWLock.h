#pragma once
#include <atomic>

class RWLock
{
public:
    RWLock() {

    }

    // acquire exclusive lock
    void LockExclusive() {
        int target = 0;
        while (! m_holder_stamp.compare_exchange_strong(target, -1, std::memory_order_acquire)) {
            target = 0;
        }
    }

    // release exclusive lock
    void UnlockExclusive() {
        m_holder_stamp.store(0, std::memory_order_release);
    }

    // acquire shared lock
    void LockShared() {
        int target = -1;
        do {
            do {
                target = m_holder_stamp.load(std::memory_order_acquire);
            } while (target == -1);
        } while (! m_holder_stamp.compare_exchange_strong(target, target + 1, std::memory_order_acquire));
    }

    void UnlockShared() {
        const auto curr = m_holder_stamp.fetch_sub(1, std::memory_order_release);
        // assert curr >= 1 
    }

private:
    std::atomic_int m_holder_stamp;
};