#include "InRange.hpp"
#include "GtestWrapper.hpp"

TEST(InRange, inRange_open_byDefault)
{
    EXPECT_TRUE(inRange(0, 0, 0));
    EXPECT_TRUE(inRange(0, 0, 1));
    EXPECT_TRUE(inRange(1, 0, 1));
    EXPECT_TRUE(inRange(1, 0, 2));
    EXPECT_TRUE(inRange(3, 1, 7));
    EXPECT_FALSE(inRange(0, 1, 1));
    EXPECT_FALSE(inRange(0, 1, 7));
    EXPECT_FALSE(inRange(8, 1, 7));
}

TEST(InRange, inRange_closed)
{
    EXPECT_FALSE(inRange(0, 0, 0, RangeOpenness::Closed));
    EXPECT_FALSE(inRange(0, 0, 1, RangeOpenness::Closed));
    EXPECT_FALSE(inRange(1, 0, 1, RangeOpenness::Closed));
    EXPECT_TRUE(inRange(1, 0, 2, RangeOpenness::Closed));
    EXPECT_TRUE(inRange(3, 1, 7, RangeOpenness::Closed));
    EXPECT_FALSE(inRange(0, 1, 1, RangeOpenness::Closed));
    EXPECT_FALSE(inRange(0, 1, 7, RangeOpenness::Closed));
    EXPECT_FALSE(inRange(8, 1, 7, RangeOpenness::Closed));
}

TEST(InRange, inRange_openLeft)
{
    EXPECT_FALSE(inRange(0, 0, 0, RangeOpenness::OpenLeft));
    EXPECT_TRUE(inRange(0, 0, 1, RangeOpenness::OpenLeft));
    EXPECT_FALSE(inRange(1, 0, 1, RangeOpenness::OpenLeft));
    EXPECT_TRUE(inRange(1, 0, 2, RangeOpenness::OpenLeft));
    EXPECT_TRUE(inRange(3, 1, 7, RangeOpenness::OpenLeft));
    EXPECT_FALSE(inRange(0, 1, 1, RangeOpenness::OpenLeft));
    EXPECT_FALSE(inRange(0, 1, 7, RangeOpenness::OpenLeft));
    EXPECT_FALSE(inRange(8, 1, 7, RangeOpenness::OpenLeft));
}

TEST(InRange, inRange_openRight)
{
    EXPECT_FALSE(inRange(0, 0, 0, RangeOpenness::OpenRight));
    EXPECT_FALSE(inRange(0, 0, 1, RangeOpenness::OpenRight));
    EXPECT_TRUE(inRange(1, 0, 1, RangeOpenness::OpenRight));
    EXPECT_TRUE(inRange(1, 0, 2, RangeOpenness::OpenRight));
    EXPECT_TRUE(inRange(3, 1, 7, RangeOpenness::OpenRight));
    EXPECT_FALSE(inRange(0, 1, 1, RangeOpenness::OpenRight));
    EXPECT_FALSE(inRange(0, 1, 7, RangeOpenness::OpenRight));
    EXPECT_FALSE(inRange(8, 1, 7, RangeOpenness::OpenRight));
}
