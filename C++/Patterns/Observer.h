#pragma once

namespace patterns {

    template<typename T>
    class IObserver {
    
    public:
        virtual ~IObserver() {}

        virtual void OnDataChanged(T* ) = 0;
    };

    template<typename T>
    class IObservable {

    public:
        virtual ~IObservable() {}

        virtual void AddObserver(IObserver<T>* observer) = 0;

        virtual void RemoveObserver(IObserver<T>* observer) = 0;

        virtual void NotifyDataChanged() = 0;
    };

}