#pragma once

#include "IGraph.h"

#include <vector>
#include <map>

struct VectorIndexIterator : public IIterator<int, VectorIndexIterator> {
    VectorIndexIterator(int element_index)
        : m_element_index(element_index)
    {}

    // void operator++() { ++ m_element_index; }

    // int& operator*() { return m_element_index;}

    void Inc() { ++ m_element_index; }

    int& Deref() { return m_element_index; }

    int m_element_index = 0;
};

struct VectorGraph : public IGraph<int, VectorIndexIterator> {
public:
    VectorGraph(std::vector<std::map<int, float> >& data) : m_data(data) {}

    IIterator<int, VectorIndexIterator> begin() override {
        return VectorIndexIterator(0);
    }

    IIterator<int, VectorIndexIterator> end() override {
        return VectorIndexIterator(m_data.size());
    }

private:
    std::vector<std::map<int, float> >& m_data;

    // VectorIndexIterator
};

