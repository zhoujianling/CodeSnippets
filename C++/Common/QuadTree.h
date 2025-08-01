#pragma once
#include <vector>
#include <array>
#include <limits>
#include "IIterator.h"
#include "../Vecmath/Vector.h"


template<typename T>
struct Vector2Iterator{

    using V2 = Vecmath::Vector2<T>;
    Vector2Iterator(V2* data, size_t stride)
        : m_data(data)
        , m_stride(stride)
    {}

    void operator++() {  m_data = (V2*)(((char*)m_data) + m_stride); }

    V2& operator*() { return *m_data; }

    bool operator==(const Vector2Iterator& rhs) { return m_data == rhs.m_data; }
    bool operator!=(const Vector2Iterator& rhs) { return m_data != rhs.m_data; }

    // void Inc() { ((char*)m_data) += (m_stride); }

    // V2& Deref() { return *m_data; }

    V2* m_data = nullptr;
    size_t m_stride = 0u;
};


template <typename T>
class IPoints  {

public:
    virtual ~IPoints() {}

    virtual Vector2Iterator<T> begin() = 0;

    virtual Vector2Iterator<T> end() = 0;

    virtual size_t Count() const = 0;

    virtual const Vecmath::Vector2<T>& operator[] (size_t index) = 0;
};

template<typename T>
class VectorPoints : public IPoints<T> {
    using V2 = Vecmath::Vector2<T>;
public:
    VectorPoints(std::vector<V2>& points) 
    : m_points(points)
    {
    }

    ~VectorPoints() override = default;

    Vector2Iterator<T> begin() override {
        return Vector2Iterator<T>(m_points.data(), sizeof(V2));
    }

    Vector2Iterator<T> end() override {
        return Vector2Iterator<T>(m_points.data() + Count(), sizeof(V2));
    }

    size_t Count() const override {
        return m_points.size();
    }

    const V2& operator[] (size_t index) {
        return m_points[index];
    }
    
private:
    std::vector<V2> m_points;
};


struct QuadTreeDesc {
    bool m_is_smooth = false;
    bool m_is_loose = false;
};

template<typename T>
struct QuadTreeCell {
    Vecmath::Vector2<T> m_bounds_min;
    Vecmath::Vector2<T> m_bounds_max;

    std::array<int, 4> m_children_offsets; 
    std::vector<size_t> m_item_indices;

    bool IsInternal() const { return m_children_offsets[0] == -1; }
};

template <typename T>
class QuadTree {
    
public:
    QuadTree(IPoints<T>* points);

    const QuadTreeCell<T>& Root() const;

private:
    void Build();

private:
    IPoints<T>* m_points = nullptr;

    std::vector<QuadTreeCell<T> > m_cells;

};

#pragma region TemplateImpl

template <typename T>
QuadTree<T>::QuadTree(IPoints<T>* points) {
    Build();
}

template <typename T>
const QuadTreeCell<T>& QuadTree<T>::Root() const {
    return m_cells.front();
}

template <typename T>
void QuadTree<T>::Build() {
    using V2 = Vecmath::Vector2<T>; 
    V2 v2_min(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
    V2 v2_max(std::numeric_limits<T>::lowest(), std::numeric_limits<T>::lowest());
    for (auto p : *m_points) {
        v2_min = v2_min.ComponentWiseMin(p);
        v2_max = v2_max.ComponentWiseMax(p);
    }
    QuadTreeCell<T> root;
    root.m_bounds_max = v2_max;
    root.m_bounds_min = v2_min;
    m_cells.push_back(root);
    // const auto points_count = m_points->
}

#pragma endregion TemplateImpl

