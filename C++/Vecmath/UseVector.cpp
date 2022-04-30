#include "Vector.h"
#include <iostream>

using namespace Vecmath;

struct A {
    int v = 3;
    bool b = false;
};

int main(int argc, const char** argv) {
    Vector3<float> v(1.3f, 2.0f, 3.0f);
    Vector3<float> v2(1.0f, 2.0f, 3.0f);
    auto v3 = v + v2;
    // Vector<float, 3> v;
    std::cout << v3 << std::endl;
    std::cout << v.Dot(v2) << std::endl;
    return 0;
}