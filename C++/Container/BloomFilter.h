#pragma once
#include <vector>
#include <algorithm>

// struct Hash

template <typename T>
class BloomFilter {
public:
    BloomFilter(int bits_count, int hash_count);

    void Add(const T& t);

    bool Query(const T& t);

private:
    void Apply(size_t hash_code);

    size_t Hash(const T& t, size_t hash_index);

private:
    std::vector<bool> m_bits;

    std::vector<std::hash<T> > m_hashes;
};

#pragma region TemplateImpl

template <typename T>
BloomFilter<T>::BloomFilter(int bits_count, int hash_count) {
    m_bits.resize(bits_count, false);
    m_hashes.resize(hash_count);
}

template <typename T>
void BloomFilter<T>::Add(const T& t) {

    for (size_t hash_index = 0; hash_index < m_hashes.size(); ++hash_index) {
        const auto hash_code = Hash(t, hash_index);
        Apply(hash_code);
    }
}

template <typename T>
void BloomFilter<T>::Apply(size_t hash_code) {
    const auto bits_count = m_bits.size();
    m_bits[hash_code % bits_count] = 1;
}

template <typename T>
size_t BloomFilter<T>::Hash(const T& t, size_t hash_index) {
    auto& h = m_hashes[hash_index];
    auto hash_code = h(t);
    hash_code = std::hash<size_t>()(hash_code + hash_index);
    return hash_code;
}

template <typename T>
bool BloomFilter<T>::Query(const T& t) {

    for (size_t hash_index = 0; hash_index < m_hashes.size(); ++hash_index) {
        const auto hash_code = Hash(t, hash_index);
        const auto bits_count = m_bits.size();
        if (! m_bits[hash_code % bits_count]) return false;
    }
    return true;
}


#pragma endregion
