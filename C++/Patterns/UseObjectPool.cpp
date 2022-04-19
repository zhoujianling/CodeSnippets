#include <string>
#include "ObjectPool.h"
#include <iostream>
#include <ctime>


struct Student {
    int m_id;
    float m_height;
    std::string m_name;

    Student(int id, float height, std::string name) 
        : m_id(id)
        , m_height(height)
        , m_name(name)
    {}

    void* operator new(size_t n) {

    }

};

class Test: public PooledObjectBase<Test> {
public:
    Test(int v) :
        m_val(v)
    {

    }

    int m_val = 0;

    char m_ch = '1';

    std::string m_str;
    int* m_ptr = nullptr;
};


int main(int argc, char** argv) {
    //Test t;
    //ObjectPool<Student> pool(1);
    //auto& inst = ObjectPool<Student>::GetInstance();

    std::vector<Test*> objects;
    auto& inst = ObjectPool<Test>::GetInstance();
    auto t1 = clock();
    // std::cout << "capacity: " << inst.TotalCapacity() << std::endl;
    srand(time(0));
    for (int i = 0; i < 2000000; ++i) {
        if (rand() % 5 < 2 && objects.size() > 0) {
            auto* o = objects.back();
            objects.pop_back();
            delete(o);
        } else {
            objects.push_back(new Test(i));
        }
    }
    // std::cout << "capacity: " << inst.TotalCapacity() << std::endl;
    for (auto* o : objects) {
        // std::cout << "o val is " << o->m_val << std::endl;
        delete o;        
    }
    auto t2 = clock();
    std::cout << (t2 - t1) / 1000.0f << " s" << std::endl;
    return 0;
}
