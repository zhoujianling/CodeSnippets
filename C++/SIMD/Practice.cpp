#include <iostream>
#include <array>
#include <xmmintrin.h>

/**
 * 任务：将数组中所有负数替换为0，用SIMD实现无分支操作
 */

void replaceNegative(float* data, size_t n)
{
    auto zero = _mm_set_ps(0, 0, 0, 0);
    for (int i = 0; i * 4 < n; ++i)
    {
        auto v = _mm_load_ps(data + i * 4); 
        auto flags = _mm_cmplt_ps(zero, v); 
        auto r = _mm_and_ps(v, flags);
        _mm_store_ps(data + i * 4, r);
    }
} 

void replaceNegativeTest()
{
    std::array<float, 8> test { 1, 2, -3, 4, 5, 6, -7, 8};
    replaceNegative(test.data(), test.size());

    for (auto f : test)
    {
        std::cout << f << std::endl;
    }
}

int main(int argc, char** argv)
{
    replaceNegativeTest();
    return 0;
}