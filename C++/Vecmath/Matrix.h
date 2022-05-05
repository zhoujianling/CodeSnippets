#pragma once
#include "Vector.h"

namespace Vecmath {

template<typename T, uint32_t R, uint32_t C>
struct Matrix {
    T m_vals[R * C];

    T operator() (uint32_t r, uint32_t c);
};    


template<typename T>
struct Matrix4x4 : public Matrix<T, 4, 4> 
{

};

using Matrx4x4f = Matrix<float, 4, 4>;

// ---------------------------------------------
template<typename T, uint32_t R, uint32_t C>
T Matrix<T, R, C>::operator() (uint32_t r, uint32_t c) {
    return m_vals[r * C + c];
}

// ---------------------------------------------

}