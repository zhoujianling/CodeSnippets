#pragma once
#include <iostream>
#include <functional>

namespace Vecmath {

template<typename T, int N>
struct Vector {

    T m_vals[N];

    Vector<T, N> operator+ (const Vector<T, N>& rhs) const;
    Vector<T, N> operator- (const Vector<T, N>& rhs) const;
    Vector<T, N> operator* (T rhs) const;
    Vector<T, N> operator/ (T rhs) const;
    T operator[] (size_t index);

    T Dot(const Vector<T, N>& rhs);

    // template<typename T>
    T Length() const;
    T LengthSqaure() const;
    Vector<T, N> ComponentWiseOp(std::function<T(T)> op);
    
    // std::ostream& operator<< (std::ostream& ofs, Vector<T, N>& clazz); 
};

template<typename T>
struct Vector2 : public Vector<T, 2> {

    Vector2(T x, T y) 
    {
        Vector<T, 2>::m_vals[0] = x;
        Vector<T, 2>::m_vals[1] = y;
    }

    // Vector3<T> Cross(const Vector3<T>& rhs);
};


template<typename T>
struct Vector3 : public Vector<T, 3> {

    Vector3(T x, T y, T z); 

    // Vector3<T> Cross(const Vector3<T>& rhs);
};

using Vector3f = Vector3<float>;

#pragma region TemplateImpl

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator+ (const Vector<T, N>& rhs) const {
    auto result = *this;
    for (int i = 0; i < N; ++i) {
        result.m_vals[i] += rhs.m_vals[i];
    }
    return result;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator- (const Vector<T, N>& rhs) const {
    auto result = *this;
    for (int i = 0; i < N; ++i) {
        result.m_vals[i] -= rhs.m_vals[i];
    }
    return result;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator* (T rhs) const {
    auto result = *this;
    for (int i = 0; i < N; ++i) {
        result.m_vals[i] *= rhs;
    }
    return result;
}

template<typename T, int N>
Vector<T, N> Vector<T, N>::operator/ (T rhs) const {
    auto result = *this;
    for (int i = 0; i < N; ++i) {
        result.m_vals[i] /= rhs;
    }
    return result;
}

// template<typename T, int N>
// T Vector<T, N>::Length() const {
//     return std::sqrtf()
// }

// template<int N>
// float Vector<float, N>::Length() const {
//     // return std::sqr
//     return 0;
// }

template<typename T, int N>
T Vector<T, N>::LengthSqaure() const {
    return Dot(*this);
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