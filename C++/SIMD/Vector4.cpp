#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <xmmintrin.h>
#include "DirectXMath.h"

struct Vector4 {
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        float vals[4];
    };

    Vector4(float x, float y, float z, float w) {
        vals[0] = x;
        vals[1] = y;
        vals[2] = z;
        vals[3] = w;
    }

    Vector4 operator+ (const Vector4& rhs) const {
        return {x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w};
    }   

    Vector4 operator- (const Vector4& rhs) const {
        return {x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w};
    }   

    Vector4 operator* (const float r) {
        return {x * r, y * r, z * r, w * r};
    }   
};

Vector4 Lerp(const Vector4& v1, const Vector4& v2, float v) {
    return v1 + (v2 - v1) * v;
}

Vector4 LerpSIMD(const Vector4& v1, const Vector4& v2, float v) {
    __m128 a = _mm_load_ps(&v1.vals[0]);
    // __m128 a = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f); // reverse order
    __m128 b = _mm_load_ps(&v2.vals[0]);
    __m128 s = _mm_set_ps(v, v, v, v);
    
    __m128 r = _mm_mul_ps(_mm_sub_ps(b, a), s);
    // __m128 r2 = _mm_mul_ps(a, s2);
    __m128 res = _mm_add_ps(a, r);

    Vector4 result(0, 0, 0, 0);
    _mm_store_ps(&(result.vals[0]), res);
    // return v1 + (v2 - v1) * v;
    return result;
}

// compile with `cl /EHsc Vector4.cpp` in developer prompt
Vector4 LerpSIMD_DXMath(const Vector4& v1, const Vector4& v2, float v) {
    DirectX::XMFLOAT4 xmv1(&v1.vals[0]);
    DirectX::XMFLOAT4 xmv2(&v2.vals[0]);
    DirectX::XMFLOAT4 s(v, v, v, v);
    auto vv1 = DirectX::XMLoadFloat4(&xmv1);
    auto vv2 = DirectX::XMLoadFloat4(&xmv2);
    auto sv = DirectX::XMLoadFloat4(&s);
    auto v2_sub_v1 = DirectX::XMVectorSubtract(vv2, vv1);
    auto result_vec = DirectX::XMVectorMultiplyAdd(v2_sub_v1, sv, vv1);

    DirectX::XMFLOAT4 res;
    DirectX::XMStoreFloat4(&res, result_vec);
    return {res.x, res.y, res.z, res.w};
}

void TestLerp() {
    auto t0 = clock();
    Vector4 zero(0, 0, 0, 0);
    const auto try_count = 10000000;
    double y_sum = 0.0;
    for (int i = 0; i < try_count; ++i) {
        Vector4 t(i + 1, i, i - 1, i);
        auto tt = Lerp(t, zero, (i % 10000) * 1.0f / 12400.0f);
        y_sum += (tt.y + tt.x + tt.z + tt.w) * 0.01f;
    }
    auto t1 = clock();
    std::cout << "time cost(normal) is " << (t1 - t0) / 1000.0f << " s" << std::endl;
    std::cout << "y sum is " << y_sum << std::endl;

    y_sum = 0.0;
    for (int i = 0; i < try_count; ++i) {
        Vector4 t(i + 1, i, i - 1, i);
        auto tt = LerpSIMD(t, zero, (i % 10000) * 1.0f / 12400.0f);
        y_sum += (tt.y + tt.x + tt.z + tt.w) * 0.01f;
    }

    auto t2 = clock();
    std::cout << "time cost(simd) is " << (t2 - t1) / 1000.0f << " s" << std::endl;
    std::cout << "y sum is " << y_sum << std::endl;

    y_sum = 0.0;
    for (int i = 0; i < try_count; ++i) {
        Vector4 t(i + 1, i, i - 1, i);
        auto tt = LerpSIMD_DXMath(t, zero, (i % 10000) * 1.0f / 12400.0f);
        y_sum += (tt.y + tt.x + tt.z + tt.w) * 0.01f;
    }

    auto t3 = clock();
    std::cout << "time cost(simd) is " << (t3 - t2) / 1000.0f << " s" << std::endl;
    std::cout << "y sum is " << y_sum << std::endl;
}

int main(int argc, const char** argv) {
    TestLerp();
    return 0;
}