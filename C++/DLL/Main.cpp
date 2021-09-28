#include <iostream>

// #include "LibraryHeader.h"

namespace library {

    __declspec(dllimport) int Add(int a, int b);

}

int main(int argc, char** argv) {
    std::cout << "hello" << std::endl;
    std::cout << " add result: " << library::Add(1, 2) << std::endl;
    return 0;
}