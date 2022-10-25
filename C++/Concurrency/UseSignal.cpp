#include "Signal.h"
#include <thread>
#include <future>
#include <chrono>
#include <iostream>

using namespace std::chrono_literals;

int main(int argc, const char** argv) {
    Signal signal;
    std::cout << "this thread id: " << std::this_thread::get_id() << std::endl;
    std::thread t([&](){
        std::cout << "async thread id: " << std::this_thread::get_id() << std::endl;
        std::cout << "before sleep 3s" << std::endl;
        std::this_thread::sleep_for(3s);
        std::cout << "after sleep 3s" << std::endl;
        signal.Emit();
    });
    std::cout << "before wait ..." << std::endl;
    signal.Wait();
    std::cout << "after wait ... " << std::endl;    
    return 0;
}