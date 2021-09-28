#pragma once
#include <vector>

// #ifdef LIB_EXPORTS
// #define LIB_API __declspec(dllexport)
// #else
// #define LIB_API __declspec(dllimport)
// #endif

#define LIB_API __declspec(dllexport)

namespace library {

    LIB_API int Add(int a, int b);

    class LIB_API Hello {
    public:
        Hello(int val);

        int Add2(int a, int b);
    
    private:
        int m_val = 0;
    };

}