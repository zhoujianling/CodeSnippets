#include <functional>
#include <algorithm>
#include <assert.h>


template<typename K, typename V>
struct Pair {
    K m_key;
    V m_value;
};


template<typename K, typename V>
struct HashNode {
    Pair<K, V> m_pair;
    // K m_key;    
    // V m_value;
    HashNode* m_next = nullptr;
    bool m_occupied = false;
};

template<typename K, typename V>
struct HashMapIterator {
public:
    HashMapIterator(HashNode<K, V>* curr, HashNode<K, V>* next_bucket);
    Pair<K, V>& operator*();
    HashMapIterator<K, V>& operator++();

    HashNode<K, V>* m_curr = nullptr;
    HashNode<K, V>* m_next_bucket = nullptr;
};

// -----------------------------
template<typename K, typename V>
HashMapIterator<K, V>::HashMapIterator(HashNode<K, V>* curr, HashNode<K, V>* next_bucket) {
    m_curr = curr;
    m_next_bucket = next_bucket; 
}

template<typename K, typename V>
Pair<K, V>& HashMapIterator<K, V>::operator*() {
    return m_curr->m_pair;
}

// template<typename K, typename V>
// HashMapIterator<K, V>& HashMapIterator<K, V>::operator++() {
//     if (m_curr->m_next) {

//     }
// }

// -------------------------------------------------
// 
// -------------------------------------------------
template<typename K, typename V>
class HashMap {
    // int DEFAULT_CAPACITY = 10;
public:
    HashMap();
    ~HashMap();
    
    V& operator[] (const K& k);
    void Rehash(int bucket_num);
    bool Erase(const K& k);

private:
    void ReleaseBuckets(HashNode<K, V>* buckets, int bucket_num);

private:
    HashNode<K, V>* m_buckets = nullptr;
    int m_capacity = 20;
};


#pragma region TempImpl
// --------------------------------------
template<typename K, typename V>
HashMap<K, V>::HashMap() {
    // const v1 = (xxx1.isDirectory() ? 1 : 0);
    // const v2 = (xxx2.isDirectory() ? 1 : 0);
    // return v1 - v2;
    m_buckets = new HashNode<K, V>[m_capacity];
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
    if (! bucket->m_occupied) {
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
    bucket->m_occupied = true;
    return bucket->m_pair.m_value;
}

template<typename K, typename V>
bool HashMap<K, V>::Erase(const K& k) {
    const auto hash_code = std::hash<K>{}(k);
    const auto bucket_index = hash_code % m_capacity; 
    auto& bucket = m_buckets[bucket_index]; 
    if (bucket.m_key == k && bucket.m_occupied) {
        bucket.m_occupied = false;
        return true;
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

// --------------------------------------
#pragma endregion TempImpl
