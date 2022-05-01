#include "IntrusiveList.h"
#include <iostream>

class TestItem: public IntrusiveListItemBase<TestItem> {

public:
    TestItem(int v) : m_val(v) {}
    int m_val = 0;
};

int main(int argc, const char** argv) {
    IntrusiveList<TestItem> l;

    // TestItem item;
    // item.m_val = 12;
    // auto& item2 = item.m_holder.GetData();
    // std::cout << item2.m_val << std::endl;
    l.Add(12);
    l.Add(13);
    // std::cout << l.Back().m_val << std::endl;

    // todo: compare list and intrusive-list
    for (auto& item : l) {
        std::cout << item.m_val << std::endl;
    }
    return 0;
}
