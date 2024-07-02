#include "ChronoWrappers.hpp"
#include "GtestWrapper.hpp"

TEST(ChronoWrappers, now)
{
    const auto t1 = now();
    EXPECT_GE(now(), t1);
}
