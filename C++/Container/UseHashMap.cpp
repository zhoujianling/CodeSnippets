#include "HashMap.h"
#include <unordered_map>
#include <iostream>

void testHashMap() {
    HashMap<int, float> h;
    for (auto i = 0; i < 200; ++i) {
        h[i] = (i + 1.2f);
    }
    for (auto i = 0; i < 200; ++i) {
        std::cout << h[i] << " ";
    }
}

int main() {
    testHashMap();

    std::unordered_map<int, int> dd;
    // dd.erase()
    return 0;
}
