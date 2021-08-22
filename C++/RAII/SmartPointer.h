#pragma once
#include <type_traits>

// template <typename T>
// class EnableSharedFromThis {
//     friend class SharedPointer<T>;
// public:
//     // SharedPointer<T> 
// private:
//     int* m_ref_count_pointer = nullptr;
// };

// template<typename T>
// SharedPointer<T> MakeSharedFromThis(EnableSharedFromThis<T>* enable_shared) {
//     // todo: ...
// }

template <typename T>
class SharedPointer {
public:
    SharedPointer(T* pointer);

    ~SharedPointer();

    SharedPointer(const SharedPointer& pointer);

    SharedPointer(SharedPointer&& pointer);

    SharedPointer& operator=(const SharedPointer& pointer);
    SharedPointer& operator=(SharedPointer&& pointer);
private:
    T* m_raw_pointer = nullptr;

    int* m_ref_counter = 0;
};


template<typename T>
SharedPointer<T>::SharedPointer(T* pointer) {
    m_raw_pointer = pointer;
    m_ref_counter = new int;
    *m_ref_counter = 1;

    // if (std::is_base_of<EnableSharedFromThis, T>::value) {
    //     auto* enable_shared = (EnableSharedFromThis*)pointer;
    //     enable_shared->m_ref_count_pointer = m_ref_counter;
    //     // std::cout << "I am enable shared from this" << std::endl;
    // } else {
    //     // std::cout << "I am not enable shared from this" << std::endl;
    // }
}

template<typename T>
SharedPointer<T>::~SharedPointer() {
    (*m_ref_counter) --;
    if (*m_ref_counter == 0) {
        delete m_raw_pointer;
    }
}

template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer& pointer) {
    m_raw_pointer = pointer.m_raw_pointer;
    m_ref_counter = pointer.m_ref_counter;
    (*m_ref_counter)++;
}

template<typename T>
SharedPointer<T>::SharedPointer( SharedPointer&& pointer) {
    m_raw_pointer = pointer.m_raw_pointer;
    m_ref_counter = pointer.m_ref_counter;
    pointer.m_raw_pointer = nullptr;
    pointer.m_ref_counter = nullptr;
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& pointer) {
    m_raw_pointer = pointer.m_raw_pointer;
    m_ref_counter = pointer.m_ref_counter;
    (*m_ref_counter)++;
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer&& pointer) {
    m_raw_pointer = pointer.m_raw_pointer;
    m_ref_counter = pointer.m_ref_counter;
    pointer.m_raw_pointer = nullptr;
    pointer.m_ref_counter = nullptr;
}


// -----------------------------------------------------------------