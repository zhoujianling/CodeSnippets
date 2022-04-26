#include "IntrusiveList.h"
#include <iostream>

class TestItem: public IntrusiveListItemBase<TestItem> {

public:
    int m_val = 0;
};

int main(int argc, const char** argv) {
    //IntrusiveList<TestItem> list;

    TestItem item;
    item.m_val = 12;
    auto& item2 = item.m_holder.GetData();
    std::cout << item2.m_val << std::endl;
    return 0;
}
