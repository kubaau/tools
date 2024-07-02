#include "Observer.hpp"
#include "GtestWrapper.hpp"

struct Observer : IObserver<int, float>
{
    void notify(int ii, float ff) override
    {
        i = ii;
        f = ff;
    }
    int i;
    float f;
};

struct Notifier : Observable<int, float>
{
    void foo() { notifyObservers(3, 5.5f); }
};

struct Forwarder : NotificationForwarder<int, float>
{
};

TEST(Observer, observer)
{
    Notifier n;
    {
        auto o = make_shared<Observer>();
        n.subscribe(o);
        n.foo();
        EXPECT_EQ(3, o->i);
        EXPECT_EQ(5.5f, o->f);
    }
    n.foo();
}

TEST(Observer, observer_with_forwarder)
{
    Notifier n;
    auto fw = make_shared<Forwarder>();
    {
        auto o = make_shared<Observer>();
        fw->subscribe(o);
        n.subscribe(fw);
        n.foo();
        EXPECT_EQ(3, o->i);
        EXPECT_EQ(5.5f, o->f);
    }
    n.foo();
}
