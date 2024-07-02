#include "FindActErase.hpp"
#include "GtestWrapper.hpp"

TEST(FindActErase, findActErase)
{
    int x = 0;

    auto add = [&x](auto n) { x += n; };

    S s{1, 2, 3};
    findActErase(s, 2, add);
    EXPECT_EQ(2, x);
    EXPECT_EQ((S{1, 3}), s);
    findActErase(s, 2, add);
    EXPECT_EQ(2, x);
    EXPECT_EQ((S{1, 3}), s);

    M m{{1, 2}, {3, 4}, {5, 6}};
    findActErase(m, 3, add);
    EXPECT_EQ(6, x);
    EXPECT_EQ((M{{1, 2}, {5, 6}}), m);
    findActErase(m, 3, add);
    EXPECT_EQ(6, x);
    EXPECT_EQ((M{{1, 2}, {5, 6}}), m);
}
