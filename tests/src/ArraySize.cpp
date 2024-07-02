#include "ArraySize.hpp"
#include "GtestWrapper.hpp"

TEST(ArraySize, extent)
{
    int a[3];
    int b[4][5];
    EXPECT_EQ(3u, ::extent(a));
    EXPECT_EQ(4u, ::extent(b));
    EXPECT_EQ(5, (::extent<int, 1>(b)));
}

TEST(ArraySize, arraySize)
{
    int a[3];
    EXPECT_EQ(3u, arraySize(a));
}

TEST(ArraySize, arraySizeInBytes)
{
    int a[3];
    EXPECT_EQ(12u, arraySizeInBytes(a));
    char b[3];
    EXPECT_EQ(3u, arraySizeInBytes(b));
}
