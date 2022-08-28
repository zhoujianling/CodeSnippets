#include <iostream>
#include "SmartPointer.h"

// struct Object : public EnableSharedFromThis {
//     int m_val = 0;

//     Object(int v) : m_val(v) {
//         std::cout << "Object is constructed" << std::endl;
//     }

//     ~Object() {
//         std::cout << "Object is released" << std::endl;
//     }
// };

// SharedPointer<Object> Construct() {
//     SharedPointer<EnableSharedFromThis> test(new EnableSharedFromThis);
//     return SharedPointer<Object> (new Object(-2)); 
// }

class Object
{
public:
    Object() {

    }
    ~Object() {
        std::cout << "Object dtor" << std::endl;
    }
};

int main(int argc, const char** argv) {
    // auto pointer = Construct();
    //std::shared_ptr<int> p;
    SharedPointer<Object> p(new Object);
    return 0;
}