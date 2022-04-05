#include "HashMap.h"
#include <unordered_map>
#include <iostream>

void testHashMap() {
    HashMap<int, float> h;
    for (auto i = 0; i < 100; ++i) {
        h[i] = (i + 1.2f);
    }
    for (auto it = h.begin(); it != h.end(); ++it) {
        std::cout << (*it).m_value << " ";
    }

    // for (auto i = 0; i < 100; ++i) {
    //     std::cout << h[i] << " ";
    // }
    std::cout << std::endl;
    for (int i = 1; i < 55; i += 2) {
        h.Erase(i);
    }
    for(auto& kv : h) {
        std::cout << kv.m_value << " ";
    }
    // for (auto i = 0; i < 100; ++i) {
    //     std::cout << h[i] << " ";
    // }
}

int main() {
    testHashMap();

    std::unordered_map<int, int> dd;
    // dd.erase()
    return 0;
}
