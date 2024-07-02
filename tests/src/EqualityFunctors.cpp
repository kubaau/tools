#include "EqualityFunctors.hpp"
#include "ContainerFilter.hpp"
#include "GtestWrapper.hpp"

TEST(EqualityFunctors, equals)
{
    V v1 = {1, 3, 7, 3};
    EXPECT_EQ((V{3, 3}), filter(v1, equals(3)));
}

TEST(EqualityFunctors, notEquals)
{
    V v1 = {1, 3, 7, 3};
    EXPECT_EQ((V{1, 3, 3}), filter(v1, notEquals(7)));
}
