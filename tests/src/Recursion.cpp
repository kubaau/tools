#include "Recursion.hpp"
#include "GtestWrapper.hpp"
#include "RangeStlAlgorithms.hpp"

TEST(Recursion, lowerBound)
{
    V v = {3, 4, 8, 11, 23, 54, 996, 8710, 911147, 10001010};
    for (auto i : {1, 0, 8, 64, 99, 114, 334, 8484, 41, 911147, 1000000000})
        EXPECT_EQ(lower_bound(v, i), lowerBound(cbegin(v), cend(v), i));
}
