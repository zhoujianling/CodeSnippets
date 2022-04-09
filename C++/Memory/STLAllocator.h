#pragma once


// See StackOverflow replies to this answer for important commentary about inheriting from std::allocator before replicating this code.
template <typename T>
class SimpleAllocator: public std::allocator<T>
{
public:
    typedef size_t size_type;
    typedef T* pointer;
    typedef const T* const_pointer;

    template<typename _Tp1>
    struct rebind
    {
        typedef SimpleAllocator<_Tp1> other;
    };

    pointer constexpr allocate(size_type n, const void* hint=0) {
        // fprintf(stderr, "Alloc %d bytes.\n", n*sizeof(T));
        return std::allocator<T>::allocate(n, hint);
    }

    void constexpr deallocate(pointer p, size_type n) {
        // fprintf(stderr, "Dealloc %d bytes (%p).\n", n*sizeof(T), p);
        return std::allocator<T>::deallocate(p, n);
    }

    SimpleAllocator() throw(): std::allocator<T>() { 
        // fprintf(stderr, "Hello allocator!\n"); 
    }
    SimpleAllocator(const SimpleAllocator &a) throw(): std::allocator<T>(a) { }
    template <class U>                    
    SimpleAllocator(const SimpleAllocator<U> &a) throw(): std::allocator<T>(a) { }
    ~SimpleAllocator() throw() { }


};