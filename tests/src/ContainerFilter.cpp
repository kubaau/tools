#include "ContainerFilter.hpp"
#include "GtestWrapper.hpp"
#include "Numeric.hpp"

TEST(ContainerFilter, filter)
{
    auto is_even = [] (auto n) { return isEven(n); };

    V v1 = {0, 1, 2, 3, 4};
    auto v2 = filter(v1, is_even);
    EXPECT_EQ((V{0, 1, 2, 3, 4}), v1);
    EXPECT_EQ((V{0, 2, 4}), v2);

    S s1 = {0, 1, 2, 3, 4};
    auto s2 = filter(s1, is_even);
    EXPECT_EQ((S{0, 1, 2, 3, 4}), s1);
    EXPECT_EQ((S{0, 2, 4}), s2);

    v1 = filter(move(v1), is_even);
    EXPECT_EQ((V{0, 2, 4}), v1);
    v1 = filter(V{0, 1, 2}, is_even);
    EXPECT_EQ((V{0, 2}), v1);

    s1 = filter(move(s1), is_even);
    EXPECT_EQ((S{0, 2, 4}), s1);
    s1 = filter(S{0, 1, 2}, is_even);
    EXPECT_EQ((S{0, 2}), s1);
}
