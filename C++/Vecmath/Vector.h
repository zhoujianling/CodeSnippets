#pragma once
#include <iostream>

namespace Vecmath {

template<typename T, int N>
struct Vector {

    T m_vals[N];

    Vector<T, N> operator+ (const Vector<T, N>& rhs);
    Vector<T, N> operator- (const Vector<T, N>& rhs);
    Vector<T, N> operator* (T rhs);
    Vector<T, N> operator/ (T rhs);
    T operator[] (size_t index);

    T Dot(const Vector<T, N>& rhs);
    
    // std::ostream& operator<< (std::ostream& ofs, Vector<T, N>& clazz); 
};


template<typename T>
struct Vector3 : public Vector<T, 3> {

    Vector3(T x, T y, T z); 

    // Vector3<T> Cross(const Vector3<T>& rhs);
};

using Vector3f = Vector3<float>;

#pragma region TemplateImpl

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator+ (const Vector<T, N>& rhs) {
    auto result = *this;
    for (int i = 0; i < N; ++i) {
        result.m_vals[i] += rhs.m_vals[i];
    }
    return result;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator- (const Vector<T, N>& rhs) {
    auto result = *this;
    for (int i = 0; i < N; ++i) {
        result.m_vals[i] -= rhs.m_vals[i];
    }
    return result;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator* (T rhs) {
    auto result = *this;
    for (int i = 0; i < N; ++i) {
        result.m_vals[i] *= rhs;
    }
    return result;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator/ (T rhs) {
    auto result = *this;
    for (int i = 0; i < N; ++i) {
        result.m_vals[i] /= rhs;
    }
    return result;
}

template<typename T, int N>
T Vector<T, N>::operator[] (size_t index) {
    return m_vals[index];
}

template<typename T, int N>
T Vector<T, N>::Dot(const Vector<T, N>& rhs) {
    T result = {0}; 
    for (int i = 0; i < N; ++i) {
        result += (m_vals[i] * rhs.m_vals[i]);
    }
    return result;
}

template<typename T, int N>
std::ostream& operator<< (std::ostream& os, Vector<T, N>& vec) {
    os << "(";
    for (int i = 0; i < N; ++i) {
        if (i > 0) os << ", ";
        os << vec.m_vals[i];
    }
    os << ")";
    return os;
}
#pragma endregion TemplateImpl


template<typename T>
Vector3<T>::Vector3(T x, T y, T z) {
    Vector<T, 3>::m_vals[0] = x;
    Vector<T, 3>::m_vals[1] = y;
    Vector<T, 3>::m_vals[2] = z;
}

// template<typename T>
// Vector3<T> Vector3<T>::Cross(const Vector3<T>& rhs) {

// }

}