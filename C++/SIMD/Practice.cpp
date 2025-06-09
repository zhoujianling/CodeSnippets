#include <iostream>
#include <array>
#include <vector>
#include <ctime>
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

void replaceNegativeNaive(float* data, size_t n)
{
    for (int i = 0; i < n; ++i)
    {
        if (data[i] < 0)
        {
            data[i] = 0;
        }
    }
}

void replaceNegativeTest()
{
    //std::array<float, 8> test { 1, 2, -3, 4, 5, 6, -7, 8};
    std::vector<float> testData;
    srand(time(0));
    int dataSize = 10000000 * 4;
    testData.resize(dataSize);
    for (int i = 0; i < dataSize; ++i)
    {
        int r0 = rand();
        testData[i] = r0 * (r0 % 2 == 0 ? 1 : -1);
    }
    auto testData2 = testData;
    {
        auto t0 = clock();
        replaceNegative(testData.data(), testData.size());
        auto t1 = clock();
        std::cout << "time cost(simd) is " << (t1 - t0) / 1000.0f << " s" << std::endl;
    }

    {
        auto t0 = clock();
        replaceNegativeNaive(testData2.data(), testData2.size());
        auto t1 = clock();
        std::cout << "time cost(normal) is " << (t1 - t0) / 1000.0f << " s" << std::endl;
    }

    // for (auto f : test)
    // {
    //     std::cout << f << std::endl;
    // }
}

// compile with `cl /EHsc Vector4.cpp` in developer prompt
int main(int argc, char** argv)
{
    replaceNegativeTest();
    return 0;
}