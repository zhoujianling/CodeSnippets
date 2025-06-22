#pragma once
#include <type_traits>
#include <atomic>

template<typename Derived>
class ObjectBase
{
public:

    virtual ~ObjectBase() {}

    void AddRef()
    {
        m_counter.fetch_add(1);
    }

    void DecRef()
    {
        const auto count = m_counter.fetch_sub(1, std::memory_order_acquire);
        if (count == 1)
        {
            delete this;
        }
    }

private:
    std::atomic_int m_counter {0};
};

template<typename T>
class SharedPointer
{
    static_assert(std::is_base_of<ObjectBase<T>, T> ::value);
public:
    SharedPointer(T* pointer)
    {
        m_pointer = pointer;
        m_pointer->AddRef();
    }

    ~SharedPointer()
    {
        m_pointer->DecRef();
        m_pointer = nullptr;
    }

    SharedPointer(const SharedPointer<T>& another)
    {
        m_pointer = another.m_pointer;
        m_pointer->AddRef();
    }

    SharedPointer& operator= (const SharedPointer<T>& another)
    {
        m_pointer = another.m_pointer;
        m_pointer->AddRef();
        return *this;
    }

    SharedPointer(SharedPointer<T>&& another)
    {
        m_pointer = another.m_pointer;
        another.m_pointer = nullptr;

        m_pointer->AddRef();
    }

    SharedPointer& operator= (SharedPointer<T>&& another)
    {
        m_pointer = another.m_pointer;
        another.m_pointer = nullptr;

        m_pointer->AddRef();
        return *this;
    }

private:
    T* m_pointer{nullptr};
};