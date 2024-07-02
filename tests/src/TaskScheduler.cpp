#include "TaskScheduler.hpp"
#include "GtestWrapper.hpp"

TEST(TaskScheduler, task_scheduler)
{
    TaskScheduler ts;

    int counter = 0;

    auto f = [&] { ++counter; };
    ts.schedule(f);                          // 1
    ts.schedule([&] { ++counter; }, 1ms, 3); // 3
    auto t1 = ts.schedule(f, 1ns, 2);        // 1 (disable)
    auto t2 = ts.schedule(f, 1ns, 3);        // 10 (reset)
    ts.schedule([&] { ts.schedule(f); });    // 1

    repeat(10)
    {
        this_thread::sleep_for(2ms);
        ts.launch();
        if (auto st = t1.lock())
        {
            EXPECT_FALSE(st->isStale());
            st->disable();
            EXPECT_TRUE(st->isStale());
        }
        t2.lock()->reset();
    }

    EXPECT_FALSE(t2.lock()->isStale());

    EXPECT_EQ(16, counter);
}
