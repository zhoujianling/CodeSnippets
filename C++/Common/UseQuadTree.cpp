#include "QuadTree.h"
#include <iostream>

using Vector2f = Vecmath::Vector2<float>;

int main(int argc, char** argv) {
    std::vector<Vector2f> ps;
    VectorPoints<float> points(ps);
    QuadTree<float> tree(&points); 
    
    return 0;
}