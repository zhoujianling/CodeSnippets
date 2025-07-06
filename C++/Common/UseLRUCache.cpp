#include "LRUCache.h"
#include <string>
#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

struct TestItem {
    int m_id;
    std::string m_name;
    void* m_dummy;

    TestItem() {}
    TestItem(int id, std::string name) 
        : m_id(id)
        , m_name(name)
        {}
};

int main(int argc, const char** argv) {
    LRUCache<int, TestItem, 100> cache;
    
    std::vector<TestItem> items;
    std::vector<int> access_ids;
    for (int i = 0; i < 1000; ++i) {
        items.emplace_back(i, "test");
    }
    for (int i = 0; i < 4; ++i) {
        for (int id = 0; id < items.size(); ++id) {
            access_ids.push_back(id);
        }
    }
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(access_ids.begin(), access_ids.end(), std::default_random_engine(seed)); 

    int query_count = 0;
    int hit_count = 0;
    for (auto id : access_ids) {
        query_count += 1;
        TestItem item;
        if (cache.Get(id, item)) {
            hit_count += 1; 
        }
        else {
            item = items[id];
            cache.Put(id, item);
        }
    }
    std::cout << "hit rate: " << hit_count * 1.0 / query_count << std::endl;
    return 0;
}