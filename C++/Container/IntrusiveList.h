#pragma once
#include <type_traits>
#include <vector>

template <typename T>
struct IntrusiveListNode {
    IntrusiveListNode* m_next = nullptr;
    // IntrusiveListNode* m_prev = nullptr;

    T& GetData();
};

template<typename T, typename U> constexpr size_t OffsetOf(U T::*member)
{
    return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

template<typename Derived>
class IntrusiveListItemBase {
public:
    IntrusiveListNode<Derived> m_holder;

};

template <typename T>
struct IntrusiveListIterator {

    IntrusiveListIterator(IntrusiveListNode<T>* curr_node);
    
    T& operator*();
    IntrusiveListIterator<T>& operator++();
    bool operator== (const IntrusiveListIterator<T>& rhs) const;
    bool operator!= (const IntrusiveListIterator<T>& rhs) const;
    
    IntrusiveListNode<T>* m_curr_node = nullptr;
};

template <typename T>
class IntrusiveList {
public:
    IntrusiveList();

    void Add(T&& t);

    // void Pop();

    T& Back();

    size_t Count() const;

    bool Erase(IntrusiveListIterator<T>& it);
    
    IntrusiveListIterator<T> begin();
    IntrusiveListIterator<T> end();
private:
    // std::vector<IntrusiveListItem<T> > m_items; 
    // std::vector<uint32_t> m_available_item_indices;
    IntrusiveListNode<T> m_dummy_node;
    IntrusiveListNode<T>* m_tail_node = nullptr;
    size_t m_node_count = 0;
};

#pragma region TemplateImpl

template <typename T>
IntrusiveListIterator<T>::IntrusiveListIterator(IntrusiveListNode<T>* curr_node) 
    : m_curr_node(curr_node)
{
}
    
template <typename T>
T& IntrusiveListIterator<T>::operator*() {
    return m_curr_node->m_next->GetData();
}

template <typename T>
IntrusiveListIterator<T>& IntrusiveListIterator<T>::operator++() {
    m_curr_node = m_curr_node->m_next;
    return *this;
}

template <typename T>
bool IntrusiveListIterator<T>::operator== (const IntrusiveListIterator<T>& rhs) const {
    return m_curr_node = rhs.m_curr_node;
}

template <typename T>
bool IntrusiveListIterator<T>::operator!= (const IntrusiveListIterator<T>& rhs) const {
    return m_curr_node != rhs.m_curr_node;
}

template <typename T>
T& IntrusiveListNode<T>::IntrusiveListNode::GetData() {
    static_assert(std::is_base_of<IntrusiveListItemBase<T>, T>::value);
    // auto* item_ptr = static_cast<Derived*>(this + 1);
    auto* item_ptr = (T*)((char*)this - OffsetOf(&T::m_holder));
    return *item_ptr;
}

template <typename T>
IntrusiveList<T>::IntrusiveList() {
    m_tail_node = &m_dummy_node;
}

template <typename T>
void IntrusiveList<T>::Add( T&& t) {
    t.m_holder.m_next = nullptr;
    // t.m_holder.m_prev = m_tail_node;
    m_tail_node->m_next = & t.m_holder;
    m_tail_node = & t.m_holder;
    ++m_node_count;
}

// template <typename T>
// void IntrusiveList<T>::Pop() {
//     m_tail_node = m_tail_node->m_prev;
//     m_tail_node->m_next->m_prev = nullptr;
//     m_tail_node->m_next = nullptr;
//     --m_node_count;
// }

template <typename T>
T& IntrusiveList<T>::Back() {
    return m_tail_node->GetData();
}

template <typename T>
size_t IntrusiveList<T>::Count() const {
    return m_node_count;

}

template <typename T>
bool IntrusiveList<T>::Erase(IntrusiveListIterator<T>& it) {
    it.m_curr_node->m_next = it.m_curr_node->m_next->m_next;
    --m_node_count;
    return true;
}

template <typename T>
IntrusiveListIterator<T> IntrusiveList<T>::begin() {
    return {&m_dummy_node};
}

template <typename T>
IntrusiveListIterator<T> IntrusiveList<T>::end() {
    return {m_tail_node};
}

#pragma endregion TemplateImpl
