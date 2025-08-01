#pragma once
#include "IIterator.h"


template<typename K, typename Iter>
struct IGraph : public IIterable<K, Iter> {
    virtual ~IGraph() = default;

};
