#pragma once
#include <memory>

class Data {
    friend class DataBuilder;
public:

private:
    Data() = default;

    int m_val = 0;

    float m_val2 = 0.0f;
};

class DataBuilder {
public:
    DataBuilder() { m_data = std::make_shared<Data>(); }

    DataBuilder& Param1(int val) {
        m_data->m_val = val;
    }

    DataBuilder& Param2(float val) {
        m_data->m_val2 = val;
    }

    std::shared_ptr<Data> Build() {
        return m_data;
    }

private:
    std::shared_ptr<Data> m_data;

};
