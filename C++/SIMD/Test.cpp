#include <xmmintrin.h>

#include <iostream>

void TestAddSSE() {
    alignas(16) float A[4] = { 1.0f, 2.0f, 3.0f, 4.0f };
    alignas(16) float B[4] = { 2.0f, 4.0f, 6.0f, 8.0f };
    alignas(16) float R[4];

    __m128 a = _mm_load_ps(&A[0]);
    // __m128 a = _mm_set_ps(4.0f, 3.0f, 2.0f, 1.0f); // reverse order
    __m128 b = _mm_load_ps(&B[0]);
    __m128 r = _mm_add_ps(a, b);

    _mm_store_ps(&R[0], r);

    std::cout << " R: " << R[0] << ", " << R[1] << ", " << R[2] << ", " << R[3] << std::endl;
}

int main(int argc, char** argv) {
    TestAddSSE();
    return 0;
}