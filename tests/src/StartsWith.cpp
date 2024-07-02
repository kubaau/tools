#include "StartsWith.hpp"
#include "GtestWrapper.hpp"

TEST(StartsWith, startsWith)
{
    EXPECT_TRUE(startsWith("ala ma kota", "ala ma"));
    EXPECT_FALSE(startsWith("ala ma kota", "alama"));
}
