#include "TimeLimitedThread.hpp"

#include "GtestWrapper.hpp"
#include "SimpleTimer.hpp"

struct TimeLimitedThreadTest : Test
{
    TimeLimitedThreadRunner sut;

    ~TimeLimitedThreadTest()
    {
        EXPECT_LT(timer.elapsed(), chrono::duration_cast<chrono::milliseconds>(duration).count() / 1000. * 1.2);
    }

    static constexpr auto duration = 200ms;
    static constexpr auto increments_per_method = 10;

    SimpleTimer timer;
    atomic<int> i = 0;
    TimeLimitedThreadRunner::Func incrementer = [&i = this->i]
    {
        thread_local auto increments = 0;
        if (increments < increments_per_method)
        {
            ++i;
            ++increments;
        }
        constexpr auto sleep_time =
            chrono::duration_cast<chrono::milliseconds>(duration) / increments_per_method - 10ms;
        this_thread::sleep_for(sleep_time);
    };
};

#if 1
TEST_F(TimeLimitedThreadTest, add_runFor)
{
    sut.add(incrementer);
    sut.add(incrementer, 3);
    sut.runFor(duration);
    EXPECT_EQ(i, increments_per_method * 4);
}

TEST_F(TimeLimitedThreadTest, runFor)
{
    constexpr auto count = 100;
    sut.runFor(duration, TimeLimitedThreadRunner::Funcs(count, incrementer));
    EXPECT_EQ(i, increments_per_method * count);
}

TEST_F(TimeLimitedThreadTest, runFor_tooLong)
{
    sut.runFor(duration,
               [this]
               {
                   this_thread::sleep_for(duration * 2);
                   ++i;
               });
    EXPECT_EQ(i, 0);
}
#endif
