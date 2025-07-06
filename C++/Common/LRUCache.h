#pragma once
#include <list>
#include <map>
#include <unordered_map>

template<typename K, typename V, int CacheSize>
class LRUCache 
{
    using DataList = typename std::list<std::pair<K, V> >;
    using VIt = typename DataList::iterator;
    static_assert(CacheSize > 1);
public:
    void Put(K k, const V& v) {
        while (m_list.size() >= CacheSize) {
            m_map.erase(m_list.back().first);
            m_list.pop_back();
        }
        m_list.emplace_front(k, v);
        m_map[k] = m_list.begin();
    }

    bool Get(K k, V& v) {
        // using It = decltype(m_map.begin());
        auto it = m_map.find(k);
        if (it == m_map.end()) return false;
        v = it->second->second;
        {
            // auto eit = m_list.erase(it->second);  
            // m_list.insert(m_list.begin(), eit, eit + 1);
            m_list.splice(m_list.begin(), m_list, it->second); 
        }
        return true;
    }

private:
    std::unordered_map<K, VIt> m_map;
    DataList m_list;
};