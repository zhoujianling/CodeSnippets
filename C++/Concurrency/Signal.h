#include <condition_variable>
#include <mutex>

class Signal
{
public:
    Signal() {
    }

    void Emit() {
        // release mutex
        std::unique_lock<std::mutex> lock(m_mut);
        m_cond.notify_one();
    }

    void Wait() {
        // acquire mutex
        std::unique_lock<std::mutex> lock(m_mut);
        m_cond.wait(lock);
    }

private:
    std::condition_variable m_cond;

    std::mutex m_mut;
};

class Signal2
{
public:
    Signal2() {
    }

    void Emit() {
        // // release mutex
        // std::unique_lock<std::mutex> lock(m_mut);
        // m_cond.notify_one();
    }

    void Wait() {
        // // acquire mutex
        // std::unique_lock<std::mutex> lock(m_mut);
        // m_cond.wait(lock);
    }

private:
    std::condition_variable m_cond;

    std::mutex m_mut;
};