#include "MapValueOr.hpp"
#include "GtestWrapper.hpp"

TEST(MapValueOr, valueOr)
{
    M m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ(4, valueOr(m, 3, 0));
    EXPECT_EQ(0, valueOr(m, 7, 0));
}
