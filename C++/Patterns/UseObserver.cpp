#include "Observer.h"
#include <iostream>
#include <set>

class Data : public patterns::IObservable<Data> {

public:
    ~Data() override = default;

    void AddObserver(patterns::IObserver<Data>* observer) override {
        m_observers.insert(observer);
    }

    void RemoveObserver(patterns::IObserver<Data>* observer) override {
        auto iter = m_observers.find(observer);
        if (iter != m_observers.end()) {
            m_observers.erase(iter);
        }
    }

    void NotifyDataChanged() {            
        for (auto* observer : m_observers) {
            observer->OnDataChanged(this);
        }
    }

    int m_val = 0;

private:
    std::set<patterns::IObserver<Data>*> m_observers; 

};

class DataProcessor : public patterns::IObserver<Data> {

public:
    ~DataProcessor() override = default;

    void OnDataChanged(Data* ) override {
        std::cout << "I observer that data has changed" << std::endl;
    }
};

void UpdateData(Data& data) {
    data.m_val ++;
    data.NotifyDataChanged();    
}

int main(int argc, char** argv) {
    DataProcessor processor;
    Data data;
    data.AddObserver(&processor);

    UpdateData(data);
    return 0;
}