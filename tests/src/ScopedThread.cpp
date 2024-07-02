#include "ScopedThread.hpp"
#include "GtestWrapper.hpp"

TEST(ScopedThread, scoped_thread)
{
    int i = 0;
    auto f = [&] { ++i; };
    {
        ScopedThread{f};
        ScopedThread{[&] { ++i; }};

        thread t{f};
        ScopedThread{move(t)};
    }
    EXPECT_EQ(3, i);
}
