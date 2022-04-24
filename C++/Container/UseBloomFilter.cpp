#include "BloomFilter.h"
#include <string>
#include <iostream>

// struct Item {
//     int m_val = 0;
// };

void Test(std::string) {

}

int main(int argc, const char** argv) {
    BloomFilter<std::string> filter(4096, 3);

    const auto keys = {
        "apple", "banana", "alice", "000", "111", "", "code", "Apple"
    };
    for (const auto key : keys) {
        filter.Add(key);
    }

    if (filter.Query("apple")) {
        std::cout << "apple exist, " << std::endl;
    } else {
        std::cout << "apple not exist, " << std::endl;
    }
    if (filter.Query(" ")) {
        std::cout << "' ' exist, " << std::endl;
    } else {
        std::cout << "' ' not exist, " << std::endl;
    }
    if (filter.Query("banana1")) {
        std::cout << "banana1 exist, " << std::endl;
    } else {
        std::cout << "banana1 not exist, " << std::endl;
    }
    if (filter.Query("code")) {
        std::cout << "code exist, " << std::endl;
    } else {
        std::cout << "code not exist, " << std::endl;
    }
    return 0;
}
