#include "RandomChance.hpp"
#include "GtestWrapper.hpp"

TEST(RandomChance, chance)
{
    const auto to_be = chance(5);
    EXPECT_TRUE(to_be or not to_be);
}
