#pragma once

#include <memory>
#include "CustomRangeAlgorithms.hpp"

template <typename... Args>
class IObserver
{
public:
    virtual ~IObserver() {}

    virtual void notify(Args...) = 0;
};

template <typename... Observables>
class IObservable
{
public:
    using WeakObserver = std::weak_ptr<IObserver<Observables...>>;

    virtual ~IObservable() {}

    virtual void subscribe(WeakObserver) = 0;
};

template <typename... Observables>
class Observable : public IObservable<Observables...>
{
public:
    using WeakObserver = std::weak_ptr<IObserver<Observables...>>;

    virtual void subscribe(WeakObserver obs) override { observers.push_back(obs); }

protected:
    virtual void notifyObservers(Observables... args)
    {
        removeExpired();
        notifyObserversImpl(args...);
    }

private:
    void notifyObserversImpl(Observables... args)
    {
        for (const auto& o : observers)
        {
            o.lock()->notify(args...);
        }
    }
    void removeExpired()
    {
        erase_if(observers, [](const auto& o) { return o.expired(); });
    }

    std::vector<WeakObserver> observers;
};

template <typename... Args>
class NotificationForwarder : public IObserver<Args...>, public Observable<Args...>
{
public:
    void notify(Args... args) override { Observable<Args...>::notifyObservers(args...); }
};
