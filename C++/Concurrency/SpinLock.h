#include <atomic>
#include <thread>

class SpinLock {

public:
    SpinLock() {
    }

    void Lock() {
        while (m_flag.test_and_set(std::memory_order_acquire)) {
            std::this_thread::yield();
            //;
        }
    }

    void Unlock() {
        m_flag.clear(std::memory_order_release);
    }

private:
    std::atomic_flag m_flag;

};
