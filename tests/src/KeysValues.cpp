#include "KeysValues.hpp"
#include "GtestWrapper.hpp"

TEST(KeysValues, keys_values)
{
    M m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_EQ((V{1, 3, 5}), keys(m));
    EXPECT_EQ((V{2, 4, 6}), values(m));
}
