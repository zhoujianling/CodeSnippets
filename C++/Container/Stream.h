#pragma once
#include <unordered_map>
#include <functional>
#include <memory>

// template<typename T>
// class StreamNode {
// public:
//     T& Head() {return m_val;}
//     StreamNode<T>* Tail() { return m_next(); }
//     // T& operator()() { return }
// private:
//     T m_val;
//     std::function<StreamNode<T>*(void)> m_next;
//     //StreamNode<T>* m_next;
// };

template<typename T>
class StreamNode {
public:
    StreamNode() {}
    StreamNode(const T& val) : m_val(val) {}
    StreamNode(const T& val, const std::function<std::shared_ptr<StreamNode<T> >(void)>& n) 
        : m_val(val) 
        , m_next(n)
        {}

    T& Head() {return m_val;}
    StreamNode<T>* Tail() { 
        //return *this(); 
        return m_next();
    }
    // std::shared_ptr<StreamNode<T> > operator()() { 
    //     // todo: do something ...
    //     //auto& derived = static_cast<Derived&>(*this);
    //     return nullptr;
    // }
    std::function<std::shared_ptr<StreamNode<T> >(void)> m_next;
private:
    T m_val;
    std::shared_ptr<StreamNode<T> > m_cached_tail = nullptr;
};

template<typename T>
void ForEach(StreamNode<T>* stream, const std::function<void(StreamNode<T>*)>& func ) {
    // func(stream);
    // if (stream->m_next) {
    //     ForEach()
    // }
    auto curr = stream;
    std::shared_ptr<StreamNode<T> > next;
    func(stream);
    while (curr->m_next) {
        next = curr->m_next();
        curr = next.get();
        func(curr);
    }
}


std::shared_ptr<StreamNode<int> > MakeStream() {
    return std::make_shared<StreamNode<int> > (0, []() {
        return std::make_shared<StreamNode<int> >(1, []() {
            return std::make_shared<StreamNode<int> >(2);
        });
    }); 
}
