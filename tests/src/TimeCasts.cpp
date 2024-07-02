#include "TimeCasts.hpp"
#include "GtestWrapper.hpp"

TEST(TimeCasts, in)
{
    constexpr auto seconds = 3.6;
    EXPECT_EQ(seconds * 1000, inMilliseconds(seconds));
    EXPECT_EQ(seconds * 1000 * 1000, inMicroseconds(seconds));
    EXPECT_EQ(seconds * 1000 * 1000 * 1000, inNanoseconds(seconds));
    EXPECT_EQ(seconds / 60, inMinutes(seconds));
    EXPECT_EQ(seconds / 60 / 60, inHours(seconds));
    EXPECT_EQ(1.0, (in<ratio<36, 10>>(seconds)));
}
