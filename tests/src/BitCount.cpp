#include "BitCount.hpp"
#include "GtestWrapper.hpp"

TEST(BitCount, bitsIn_type)
{
    EXPECT_EQ(8u, bitsIn<u8>());
    EXPECT_EQ(16u, bitsIn<u16>());
    EXPECT_EQ(32u, bitsIn<u32>());
    EXPECT_EQ(64u, bitsIn<u64>());
}

TEST(BitCount, bitsIn_value)
{
    EXPECT_EQ(8u, bitsIn(u8{}));
    EXPECT_EQ(16u, bitsIn(u16{}));
    EXPECT_EQ(32u, bitsIn(u32{}));
    EXPECT_EQ(64u, bitsIn(u64{}));
}

TEST(BitCount, countSetBits)
{
    EXPECT_EQ(0u, countSetBits(0));
    EXPECT_EQ(1u, countSetBits(1));
    EXPECT_EQ(1u, countSetBits(2));
    EXPECT_EQ(2u, countSetBits(3));
    EXPECT_EQ(1u, countSetBits(4));
    EXPECT_EQ(2u, countSetBits(5));
    EXPECT_EQ(2u, countSetBits(6));
    EXPECT_EQ(3u, countSetBits(7));
    EXPECT_EQ(1u, countSetBits(8));
    EXPECT_EQ(32u, countSetBits(-1));
    EXPECT_EQ(31u, countSetBits(-2));
}
