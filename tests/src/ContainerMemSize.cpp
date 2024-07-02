#include "ContainerMemSize.hpp"
#include "GtestWrapper.hpp"

TEST(ContainerMemSize, memSize)
{
    EXPECT_EQ(12u, memSize(V{1, 2, 3}));
    EXPECT_EQ(0u, memSize(V{}));
}
