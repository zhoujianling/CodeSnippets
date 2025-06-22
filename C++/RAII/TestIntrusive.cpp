#include <iostream>

#include "SmartPointerIntrusive.h"

class Foo : public ObjectBase<Foo>
{
public:

    virtual ~Foo() 
    {
        std::cout << "Foo is destoryed" << std::endl;
    }


};

void TestIntrusive()
{
    Foo* foo = new Foo();
    SharedPointer<Foo> fp(foo);
}

int main(int argc, const char** argv)
{
    TestIntrusive();
}