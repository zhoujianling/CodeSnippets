#pragma once


template<typename T, typename Derived>
struct IIterator {

    virtual ~IIterator() = default;    

    void operator++() {
        auto& derived = static_cast<Derived&>(*this);
        derived.Inc();
    }

    T& operator*() {
        auto& derived = static_cast<Derived&>(*this);
        return derived.Deref();
    }

    // virtual void Inc() = 0;

    // virtual T& Deref() = 0;
};

// template<typename Iter>
// struct IteratorWrapper /*: public IIterator<T>*/ {
//     IteratorWrapper(Iter iter): m_iter(iter) {}

//     void operator++() { return ++(m_iter); }

//     Iter& operator*() { return *m_iter; }
    
//     Iter m_iter;

// };

template<typename T, typename Iter>
struct IIterable {
    
    virtual ~IIterable() = default;

    virtual IIterator<T, Iter> begin() = 0;

    virtual IIterator<T, Iter> end() = 0;

};