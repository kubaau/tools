#include "Timer.hpp"
#include "CustomRangeAlgorithms.hpp"
#include "GtestWrapper.hpp"

TEST(Timer, Timer)
{
    Timer t;
    auto f = [&t](auto time) {
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
    print(t.deltaF());
    print(t.totalF());

    this_thread::sleep_for(10ms);
    print(t.tick().delta());
}
