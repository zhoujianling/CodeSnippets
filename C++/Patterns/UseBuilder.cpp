#include "Builder.h"

int main(int argc, char** argv) {
    auto data = DataBuilder()
        .Param1(1)
        .Param2(0.0f)
        .Build();
    return 0;
}