#include "SafeQueue.h"

#include <thread>
#include <iostream>

SafeQueue<int> g_queue;

void Thread1Run() {
    for (int i = 0; i < 100; ++i) {
        g_queue.Put(i);
        std::cout << " put " << i << std::endl;
    }
}

void Thread2Run() {
    for (int i = 0; i < 100; ++i) {
        const auto taken_val = g_queue.WaitAndTake();
        std::cout << " take " << taken_val << std::endl;
    }

}

int main(int argc, char** argv) {
    std::thread t1(Thread1Run);
    std::thread t2(Thread2Run);
    t1.join();
    t2.join();
    return 0;
}