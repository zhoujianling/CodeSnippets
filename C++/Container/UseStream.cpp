#include "Stream.h"
#include <iostream>

int main(int argc, const char** argv) {
    std::pair<int, int> p;
    //std::pair<int, std::function<StreamNode<int>*(void)> m_data;
    std::function<void(void)> f;
    //std::pair<int, std::function<void(void)> m_data;
    //StreamNode<int> n;
    auto s = MakeStream();
    ForEach<int>(s.get(), [](StreamNode<int>* curr){
        std::cout << curr->Head() << std::endl;
    });
    return 0;
}