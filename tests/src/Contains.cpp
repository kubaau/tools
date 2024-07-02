#include "Contains.hpp"
#include "GtestWrapper.hpp"

TEST(Contains, contains)
{
    V v{1, 2, 3};
    EXPECT_TRUE(contains(v, 1));
    EXPECT_TRUE(contains(v, 1.0));
    EXPECT_FALSE(contains(v, 0));
    EXPECT_FALSE(contains(v, 1.1));
    S s{1, 2, 3};
    EXPECT_TRUE(contains(s, 1));
    EXPECT_FALSE(contains(s, 0));
    M m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_TRUE(contains(m, 1));
    EXPECT_FALSE(contains(m, 2));

    EXPECT_TRUE(contains({1, 2, 3}, 2));
    EXPECT_FALSE(contains({1, 2, 3}, 4));
}
