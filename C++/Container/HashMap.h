#include <functional>
#include <algorithm>
#include <vector>
#include <assert.h>


template<typename K, typename V>
struct Pair {
    K m_key;
    V m_value;
};


template<typename K, typename V>
struct HashNode {
    Pair<K, V> m_pair;

    HashNode* m_next = nullptr;
};

template<typename K, typename V>
class HashMap;

template<typename K, typename V>
struct HashMapIterator {
public:
    HashMapIterator(HashNode<K, V>* curr, int next_bucket_index, HashMap<K, V>* map);
    Pair<K, V>& operator*();
    HashMapIterator<K, V>& operator++();
    bool operator== (const HashMapIterator<K, V>& rhs) const;
    bool operator!= (const HashMapIterator<K, V>& rhs) const;

    HashNode<K, V>* m_curr = nullptr;
    int m_next_bucket_index = 0;
private:
    HashMap<K, V>* m_map = nullptr;
};

// -------------------------------------------------
// 
// -------------------------------------------------
template<typename K, typename V>
class HashMap {
    // int DEFAULT_CAPACITY = 10;
    friend class HashMapIterator<K, V>;
public:
    HashMap();
    ~HashMap();
    
    V& operator[] (const K& k);
    void Rehash(int bucket_num);
    bool Erase(const K& k);
    HashMapIterator<K, V> begin();
    HashMapIterator<K, V> end();

private:
    void ReleaseBuckets(HashNode<K, V>* buckets, int bucket_num);

private:
    HashNode<K, V>* m_buckets = nullptr;
    int m_capacity = 20;
    std::vector<bool> m_occupys;
};


#pragma region TempImpl
// -----------------------------
template<typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(HashNode<K, V>* curr, int next_bucket_index,
    HashMap<K, V>* map) {
    m_curr = curr;
    m_next_bucket_index = next_bucket_index; 
    m_map = map;
}

template<typename K, typename V>
Pair<K, V>& HashMapIterator<K, V>::operator*() {
    return m_curr->m_pair;
}

template<typename K, typename V>
HashMapIterator<K, V>& HashMapIterator<K, V>::operator++() {
    if (m_curr->m_next) {
        m_curr = m_curr->m_next;
        return *this;
    } else {
        const auto bucket_num = m_map->m_capacity;
        while (m_next_bucket_index < bucket_num && (!m_map->m_occupys[m_next_bucket_index])) {
            ++m_next_bucket_index;
        }
        if (m_next_bucket_index == bucket_num) {
            m_curr = nullptr;
            return *this;
        }
        m_curr = m_map->m_buckets + m_next_bucket_index;
        ++m_next_bucket_index;
        return *this;
    }
}

template<typename K, typename V>
bool HashMapIterator<K, V>::operator== (const HashMapIterator<K, V>& rhs) const {
    return m_map == rhs.m_map && m_curr == rhs.m_curr && 
        m_next_bucket_index == rhs.m_next_bucket_index;
}

template<typename K, typename V>
bool HashMapIterator<K, V>::operator!= (const HashMapIterator<K, V>& rhs) const {
    return !(*this == rhs);
}

// --------------------------------------
template<typename K, typename V>
HashMap<K, V>::HashMap() {
    m_buckets = new HashNode<K, V>[m_capacity];
    m_occupys.resize(m_capacity, false);
}

template<typename K, typename V>
HashMap<K, V>::~HashMap() {
    ReleaseBuckets(m_buckets, m_capacity);
}

template<typename K, typename V>
V& HashMap<K, V>::operator[] (const K& k) {
    using KK = typename std::decay<K>::type;
    const auto hash_code = std::hash<K>{}(k);
    const auto bucket_index = hash_code % m_capacity; 
    auto* bucket = &(m_buckets[bucket_index]);
    if (! m_occupys[bucket_index]) {
        bucket->m_pair.m_value = V();
    } else {
        auto* curr = bucket;
        while (curr->m_pair.m_key != k) {
            if (curr->m_next == nullptr) {
                curr->m_next = new HashNode<K, V>();
                curr->m_next->m_pair.m_key = k;
            }
            curr = curr->m_next;
        }
        bucket = curr;
    }
    bucket->m_pair.m_key = k;
    m_occupys[bucket_index] = true;
    return bucket->m_pair.m_value;
}

template<typename K, typename V>
bool HashMap<K, V>::Erase(const K& k) {
    const auto hash_code = std::hash<K>{}(k);
    const auto bucket_index = hash_code % m_capacity; 
    auto& bucket = m_buckets[bucket_index]; 
    if (! m_occupys[bucket_index]) {
        return false;
    }
    if (bucket.m_pair.m_key == k) {
        if (bucket.m_next == nullptr) {
            m_occupys[bucket_index] = false;
        } else {
            auto* next = bucket.m_next;
            bucket = *next;
            delete next;
        }
        return true;
    } else {
        auto* curr = &bucket;
        while (curr->m_next && curr->m_next->m_pair.m_key != k) {
            curr = curr->m_next;
        }
        if (curr->m_next) {
            auto* next = curr->m_next;
            curr->m_next = next->m_next;
            delete next;
            return true;
        }
        return false;
    }
}

template<typename K, typename V>
void HashMap<K, V>::Rehash(int bucket_num) {
    auto* old_buckets = m_buckets;
    int old_capacity = m_capacity;
    m_buckets = new HashNode<K, V>[bucket_num];
    m_capacity = bucket_num;
    ReleaseBuckets(old_buckets, old_capacity);
}

template<typename K, typename V>
void HashMap<K, V>::ReleaseBuckets(HashNode<K, V>* buckets, int bucket_num) {
    for (int i = 0; i < bucket_num; ++i) {
        auto* bucket = &(buckets[i]);
        //for (auto* bucket : m_buckets) {
        if (bucket->m_next == nullptr) continue;
        auto* curr = bucket->m_next;
        while (curr) {
            auto* next = curr->m_next;
            delete curr;
            curr = next;
        }
    }
    delete[] buckets;
}

template<typename K, typename V>
HashMapIterator<K, V> HashMap<K, V>::begin() {
    // return {m}
    int i = 0;
    for (; i < m_capacity; ++i) {
        if (m_occupys[i]) break;
    }
    return { m_buckets + i, i + 1, this };
}

template<typename K, typename V>
HashMapIterator<K, V> HashMap<K, V>::end() {
    return { nullptr, m_capacity, this };
}

// --------------------------------------
#pragma endregion TempImpl
