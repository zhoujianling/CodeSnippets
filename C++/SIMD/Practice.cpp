#include <iostream>
#include <array>
#include <vector>
#include <ctime>
#include <cmath>
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

/*
任务：计算float数组所有元素之和
*/
float sumReduce(const float* data, size_t n)
{
    return 0.0f;
}

float sumReduceNaive(const float* data, size_t n)
{
    float sum = 0;
    for (int i = 0; i < n; ++i)
    {
        sum += data[i];
    } 
    return sum;
}

void sumReduceTest()
{

}

/*
任务：优化以下结构体数组的归一化操作
```c++
struct Vec3 { float x, y, z; };
void normalize(Vec3* points, size_t n);
```
思路，一次load 4个vec3，然后把4个vec3的x组到一起。算 x * x
再算 y * y
*/

void print_vec(__m128 v) {
    float* f = (float*)&v;
    printf("[%.1f, %.1f, %.1f, %.1f]\n", f[0], f[1], f[2], f[3]);
}

struct Vec3 { float x, y, z; };
Vec3 make_v3(float x, float y, float z) { 
    Vec3 v; v.x = x; v.y = y; v.z = z; return v;
}
void normalize(Vec3* points, size_t n)
{
    /*
        x1 y1 z1 x2
        y2 z2 x3 y3
        z3 x4 y4 z4
    */
    for (int i = 0; i < n; i += 4)
    {
        auto x1y1z1x2 = _mm_load_ps(&(points[i + 0].x));
        auto y2z2x3y3 = _mm_load_ps(&(points[i + 1].y));
        auto z3x4y4z4 = _mm_load_ps(&(points[i + 2].z));
        auto x3y3x4y4 = _mm_shuffle_ps(y2z2x3y3, z3x4y4z4, _MM_SHUFFLE(2, 1, 3, 2));
        //                                                             y4 x4 y3 x3 
        //auto x3y3x4y4_test = _mm_shuffle_ps(y2z2x3y3, z3x4y4z4, _MM_SHUFFLE(2, 1, 3, 2));
        //print_vec(x3y3x4y4_test);
        auto x1x2x3x4 = _mm_shuffle_ps(x1y1z1x2, x3y3x4y4, _MM_SHUFFLE(2, 0, 3, 0));
        auto y1z1y2z2 = _mm_shuffle_ps(x1y1z1x2, y2z2x3y3, _MM_SHUFFLE(1, 0, 2, 1));
        auto y1y2y3y4 = _mm_shuffle_ps(y1z1y2z2, x3y3x4y4, _MM_SHUFFLE(3, 1, 2, 0));
        auto z1z2z3z4 = _mm_shuffle_ps(y1z1y2z2, z3x4y4z4, _MM_SHUFFLE(3, 0, 3, 1));
        // print_vec(z1z2z3z4);

        auto x_sq = _mm_mul_ps(x1x2x3x4, x1x2x3x4);
        auto y_sq = _mm_mul_ps(y1y2y3y4, y1y2y3y4);
        auto z_sq = _mm_mul_ps(z1z2z3z4, z1z2z3z4);

        auto len_sq = _mm_add_ps(x_sq, y_sq);
        len_sq = _mm_add_ps(len_sq, z_sq);
        // print_vec(len_sq);
        auto rlen = _mm_rsqrt_ps(len_sq);
        x1x2x3x4 = _mm_mul_ps(x1x2x3x4, rlen); 
        y1y2y3y4 = _mm_mul_ps(y1y2y3y4, rlen); 
        z1z2z3z4 = _mm_mul_ps(z1z2z3z4, rlen); 
        
        auto x1x3y1y3 = _mm_shuffle_ps(x1x2x3x4, y1y2y3y4, _MM_SHUFFLE(2, 0, 2, 0));
        auto z1z3x2x4 = _mm_shuffle_ps(z1z2z3z4, x1x2x3x4, _MM_SHUFFLE(3, 1, 2, 0));
        auto y2y4z2z4 = _mm_shuffle_ps(y1y2y3y4, z1z2z3z4, _MM_SHUFFLE(3, 1, 3, 1));
        x1y1z1x2 = _mm_shuffle_ps(x1x3y1y3, z1z3x2x4, _MM_SHUFFLE(2, 0, 2, 0));
        y2z2x3y3 = _mm_shuffle_ps(y2y4z2z4, x1x3y1y3, _MM_SHUFFLE(3, 1, 2, 0)); 
        z3x4y4z4 = _mm_shuffle_ps(z1z3x2x4, y2y4z2z4, _MM_SHUFFLE(3, 1, 3, 1));

        _mm_stream_ps(&(points[i].x), x1y1z1x2);
        _mm_stream_ps(&(points[i + 1].y), y2z2x3y3);
        _mm_stream_ps(&(points[i + 2].z), z3x4y4z4);
    }
}
void normalizeNaive(Vec3* points, size_t n)
{
    for (int i = 0; i < n; ++i)
    {
        auto& v = points[i];
        float sq = v.x * v.x + v.y * v.y + v.z * v.z;
        float len = std::sqrt(sq);
        v.x /= len;
        v.y /= len;
        v.z /= len;
    }
}

void normalizeTest()
{
    std::vector<Vec3> data;
    data.resize(4000000);
    for (int i = 0; i < data.size() / 4; i ++)
    {
        data[i * 4 + 0] = make_v3(1.5, 0, 0);
        data[i * 4 + 1] = make_v3(-1.0, -0.9, 1.1);
        data[i * 4 + 2] = make_v3(0.0, -1.2, 0.5);
        data[i * 4 + 3] = make_v3(9.0, 3.0, 3.1);
    }

    auto data2 = data;
    {
        auto t0 = clock();
        normalizeNaive(data.data(), data.size());
        auto t1 = clock();
        std::cout << "time cost(naive) is " << (t1 - t0) / 1000.0f << " s" << std::endl;
        // for (auto& v : data)
        // {
        //     std::cout << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << std::endl;
        // }
    }
    {
        std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
        auto t0 = clock();
        normalize(data2.data(), data2.size());
        auto t1 = clock();
        std::cout << "time cost(simd) is " << (t1 - t0) / 1000.0f << " s" << std::endl;
        // for (auto& v : data2)
        // {
        //     std::cout << "x: " << v.x << ", y: " << v.y << ", z: " << v.z << std::endl;
        // }
    }
        //constexpr size_t s = sizeof(data);
}


// compile with `cl /EHsc /Ox Vector4.cpp` in developer prompt
// or `g++ -O3 -o Practive.exe Practice.cpp`
int main(int argc, char** argv)
{
    // replaceNegativeTest();
    // sumReduceTest();
    normalizeTest();
    return 0;
}