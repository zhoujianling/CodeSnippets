#include <vector>
#include <type_traits>

#define PAGE_SIZE 4096
// #include <string>
#include <iostream>


template<typename T>
class PooledObjectBase;

template<typename T>
class ObjectPool {
private:
    ObjectPool(int capacity)
        : m_capacity(capacity)
    {
        // static_assert(std::is_base_of<PooledObjectBase<T>, T>::value);
        auto* data = (T*) ::operator new (capacity * sizeof(T));
        m_ptrs.resize(capacity);
        for (int i = 0; i < capacity; i ++) {
            m_ptrs[i] = data + i;
            // m_objects.push_back(new T());
        }
        m_pooled_memories.push_back(data);
    }

    void EnlargePool(int capacity) {
        // T* data = :: new T[capacity];
        auto* data = (T*) ::operator new (capacity * sizeof(T));
        m_ptrs.reserve(m_ptrs.size() + capacity);
        for (int i = 0; i < capacity; i ++) {
            m_ptrs.push_back(data + i);
        }
        m_pooled_memories.push_back(data);

        // std::cout << "enlarge" << std::endl;
    }

    static constexpr int GetCapacity() {
        if constexpr (sizeof(T) <= 128) return PAGE_SIZE / sizeof(T);
        return 512;
    }

public:

    static ObjectPool<T>& GetInstance() {
        constexpr int capacity = GetCapacity();
        // constexpr int capacity = 512;
        // if constexpr (sizeof(T) <= 128) {
        //     capacity = PAGE_SIZE / sizeof(T);
        // }
        // constexpr int capacity = PAGE_SIZE / 
        static ObjectPool<T> inst(capacity);
        return inst;
    }

    ~ObjectPool() {
        for (auto* pool : m_pooled_memories) {
            ::operator delete(pool);
        }
        // for (auto* o : m_objects) delete o;
    }

    T* Get() {
        if (m_ptrs.empty()) {
            EnlargePool(m_capacity);
        }
        auto* o = m_ptrs.back();
        m_ptrs.pop_back();
        return o;
    }

    void Release(T* o) {
        m_ptrs.push_back(o);
    }

    int TotalCapacity() const {
        return m_capacity * m_pooled_memories.size();
    }

private:

    // all pointers
    std::vector<T*> m_ptrs;

    // pools
    std::vector<T*> m_pooled_memories;

    int m_capacity = 0;
};

template<typename T>
class PooledObjectBase {

public:
    static void* operator new(size_t n) {
        return ObjectPool<T>::GetInstance().Get();
    }

    static void operator delete(void* pointer) {
        ObjectPool<T>::GetInstance().Release((T*)pointer);
    }

};