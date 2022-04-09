#include <iostream>
#include <vector>
#include "STLAllocator.h"

// #include "windows.h"
// #include "memoryapi.h"

// void* ::operator new(size_t s) {
//     // std::cout << "1";
//     // auto* addr = :: operator new(s);
//     // return VirtualAlloc()
//     return malloc(s);
// }

// void* operator new(size_t s) {
//     return :: operator new (s);
// }

class Object {
public:
    Object() {
        std::cout << "object ctor..." << std::endl;
    }
private:
    int m_val = 0;
};

template<typename T>
void Test(T& t) {
    auto t0 = clock();
    int cnt = 10000000;
    for (int i = 0; i < cnt; ++i) {
        t.push_back(i);
    }
    auto t1 = clock();
    std::cout << (t1 - t0) / 1000.0f << std::endl;
}

// run in develop prompt,
int main(int argc, const char** argv) {
    std::vector<int> vs1;
    std::vector<int, SimpleAllocator<int> > vs;
    Test(vs);
    Test(vs1);
    // for (auto v : vs) {
    //     std::cout << "v is " << v << std::endl;
    // }
    // auto* o = new Object();
    // delete o;
    return 0;
}