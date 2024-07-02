#ifdef _WIN32
#include "TimerWindows.hpp"
#include <chrono>
#include "CustomRangeAlgorithms.hpp"
#include "GtestWrapper.hpp"

TEST(TimerWindows, TimerWindows)
{
    TimerWindows t;
    auto f = [&t](auto time) 
    {
        this_thread::sleep_for(time);
        t.tick();
    };

    print(t.delta());
    print(t.total());

    f(17ms);
    print(t.delta());
    print(t.total());

    t.reset();
    print(t.delta());
    print(t.total());

    runInLoop(3, f, 10ms);
    print(t.delta());
    print(t.total());

    t.pause();
    runInLoop(3, f, 10ms);
    print(t.delta());
    print(t.total());

    t.unpause();
    runInLoop(3, f, 10ms);
    print(t.delta());
    print(t.total());

    this_thread::sleep_for(10ms);
    print(t.tick().delta());
}
#endif
