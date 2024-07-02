#include "SimpleTimer.hpp"
#include "GtestWrapper.hpp"

TEST(SimpleTimer, SimpleTimer)
{
    SimpleTimer t;
    print(t.elapsed());
    this_thread::sleep_for(17ms);
    print(t.elapsed());
    this_thread::sleep_for(17ms);
    print(t.elapsed());
    t.reset();
    print(t.elapsed());
    this_thread::sleep_for(17ms);
    print(t.elapsed());
    print(t.elapsedF());
}
