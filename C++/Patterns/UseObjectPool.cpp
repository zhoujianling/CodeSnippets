#include <string>
#include "ObjectPool.h"
#include <iostream>


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
};


int main(int argc, char** argv) {
    //Test t;
    //ObjectPool<Student> pool(1);
    //auto& inst = ObjectPool<Student>::GetInstance();

    std::vector<Test*> objects;
    for (int i = 0; i < 200; ++i) {
        objects.push_back(new Test(i));
    }
    for (auto* o : objects) {
        std::cout << "o val is " << o->m_val << std::endl;
        delete o;        
    }
    return 0;
}
