#pragma once
#include <atomic>
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

    //int* m_ref_counter = 0;
    std::atomic_int* m_ref_count {nullptr};
};


template<typename T>
SharedPointer<T>::SharedPointer(T* pointer) {
    m_raw_pointer = pointer;
    //m_ref_counter = new int;
    //*m_ref_counter = 1;
    m_ref_count = new std::atomic_int;
    m_ref_count->store(1);
}

template<typename T>
SharedPointer<T>::~SharedPointer() {
    const auto new_count = m_ref_count->fetch_sub(1);
    // std::cout << "ref count" << new_count << std::endl;
    if (new_count == 1) {
        delete m_raw_pointer;
        delete m_ref_count;
        m_ref_count = nullptr;
    }
}

template<typename T>
SharedPointer<T>::SharedPointer(const SharedPointer& pointer) {
    m_raw_pointer = pointer.m_raw_pointer;
    m_ref_count = pointer.m_ref_count;
    m_ref_count->fetch_add(1);
}

template<typename T>
SharedPointer<T>::SharedPointer( SharedPointer&& pointer) {
    m_raw_pointer = pointer.m_raw_pointer;
    m_ref_count = pointer.m_ref_count;
    pointer.m_raw_pointer = nullptr;
    pointer.m_ref_count = nullptr;
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator=(const SharedPointer& pointer) {
    m_raw_pointer = pointer.m_raw_pointer;
    m_ref_count = pointer.m_ref_count;
    m_ref_count->fetch_add(1);
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer&& pointer) {
    m_raw_pointer = pointer.m_raw_pointer;
    m_ref_count = pointer.m_ref_count;
    pointer.m_raw_pointer = nullptr;
    pointer.m_ref_count = nullptr;
}


// -----------------------------------------------------------------