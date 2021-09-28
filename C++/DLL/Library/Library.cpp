#include "LibraryHeader.h"

namespace library {

    int Add(int a, int b) {
        return a + b;
    }

    Hello::Hello(int val) : m_val(val) {}

    int Hello::Add2(int a, int b) {
        return m_val + a + b; 
    }

}

