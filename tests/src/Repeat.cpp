#include "Repeat.hpp"
#include "GtestWrapper.hpp"

TEST(Repeat, repeat_)
{
    int sum = 0;
    repeat(3) sum += i;
    EXPECT_EQ(3, sum);
    repeat_j(4) sum += j;
    EXPECT_EQ(9, sum);
    repeat(2u) sum += i;
    EXPECT_EQ(10, sum);
}
