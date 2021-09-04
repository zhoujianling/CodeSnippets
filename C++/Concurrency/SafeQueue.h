#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
struct SafeQueue {

    bool TryTake(T& out_val) {
        std::unique_lock<std::mutex> lock(m_mut);
        if (m_queue.empty()) return false;
        out_val = std::move(m_queue.front());
        m_queue.pop_front();
    }

    T WaitAndTake() {
        std::unique_lock<std::mutex> lock(m_mut);
        m_cond.wait(lock, [this]() { return !m_queue.empty(); } );
        auto&& taken_val = std::move(m_queue.front());
        m_queue.pop_front();
        return taken_val;
    }
    
    void Put(const T& val) {
        std::unique_lock<std::mutex> lock(m_mut);
        m_queue.push_back(val);
        m_cond.notify_one();
    }

private:
    std::deque<T> m_queue;

    std::mutex m_mut;

    std::condition_variable m_cond;
};