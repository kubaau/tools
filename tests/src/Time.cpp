#ifdef _WIN32
#include "Time.hpp"
#include "GtestWrapper.hpp"

using namespace std;
using namespace std::chrono;

TEST(Time, defaultConstructedTimeIsZero)
{
    EXPECT_EQ(0s, Time{});
}

TEST(Time, canBeComparedBothWays)
{
    EXPECT_EQ(0s, Time{});
    EXPECT_EQ(Time{}, 0s);
    EXPECT_NE(1s, Time{});
    EXPECT_NE(Time{}, 1s);
}

TEST(Time, canBeComparedStatically)
{
    static_assert(Time{} == 0s, "");
    static_assert(Time{} != 1s, "");
}

TEST(Time, cannotBeCreatedWithJustANumber)
{
    // Time t = 1;
    // Time t = 1.0;
}

TEST(Time, comparesCorrectly)
{
    EXPECT_EQ(Time{1s}, Time{1000ms});
    EXPECT_NE(Time{1s}, Time{1001ms});
    EXPECT_EQ(1s, Time{1000ms});
    EXPECT_NE(1s, Time{1001ms});

    EXPECT_LT(Time{1s}, Time{1001ms});
    EXPECT_FALSE(Time{1s} < Time{1s});
    EXPECT_LE(Time{1s}, Time{1001ms});
    EXPECT_LE(Time{1s}, Time{1s});
    EXPECT_LT(1s, Time{1001ms});
    EXPECT_FALSE(1s < Time{1s});
    EXPECT_LE(1s, Time{1001ms});
    EXPECT_LE(1s, Time{1s});

    EXPECT_GT(Time{1s}, Time{999ms});
    EXPECT_FALSE(Time{1s} > Time{1s});
    EXPECT_GE(Time{1s}, Time{999ms});
    EXPECT_GE(Time{1s}, Time{1s});
    EXPECT_GT(1s, Time{999ms});
    EXPECT_FALSE(1s > Time{1s});
    EXPECT_GE(1s, Time{999ms});
    EXPECT_GE(1s, Time{1s});
}

TEST(Time, castsToChronoTypes)
{
    constexpr milliseconds ms = Time{4s};
    EXPECT_EQ(4000u, ms.count());
    constexpr microseconds us = Time{2000ns};
    EXPECT_EQ(2u, us.count());
}

TEST(Time, providesTickCount)
{
    constexpr Time t = 1h;
    EXPECT_EQ(1, t.count<hours>());
    EXPECT_EQ(60, t.count<minutes>());
    EXPECT_EQ(3600, t.count<seconds>());
    EXPECT_EQ(3600000, t.count<milliseconds>());
    EXPECT_EQ(3600000000, t.count<microseconds>());
    EXPECT_EQ(3600000000000, t.count<nanoseconds>());
}

TEST(Time, supportsAssignment)
{
    Time t;
    t = 1001ms;
    EXPECT_EQ(1001ms, t);
    t = Time{1s};
    EXPECT_EQ(1s, t);
}

TEST(Time, supportsAdditionAssignment)
{
    Time t = 1s;
    t += t += 1ms;
    EXPECT_EQ(2002ms, t);
}

TEST(Time, supportsSubtractionAssignment)
{
    Time t1 = 1s;
    t1 -= 1ms;
    Time t2 = 2ms;
    t1 -= t2;
    EXPECT_EQ(997ms, t1);
}

TEST(Time, supportsMultiplicationAssignment)
{
    Time t = 1s;
    t *= 2;
    EXPECT_EQ(2s, t);
}

TEST(Time, supportsDivisionAssignment)
{
    Time t = 1s;
    t /= 2;
    EXPECT_EQ(500ms, t);
}

TEST(Time, supportsAddition)
{
    Time t = 1s;
    EXPECT_EQ(2001ms, t + t + 1ms);
}

TEST(Time, supportsSubtraction)
{
    Time t1 = 1s;
    Time t2 = 2ms;
    EXPECT_EQ(997ms, t1 - t2 - 1ms);
}

TEST(Time, supportsMultiplication)
{
    Time t = 1s;
    EXPECT_EQ(2s, t * 2);
}

TEST(Time, supportsDivision)
{
    Time t = 1s;
    EXPECT_EQ(500ms, t / 2);
}

TEST(Time, supportsOutputOperator)
{
    print(1s + 2ms + 3us + 4ns);
}
#endif
