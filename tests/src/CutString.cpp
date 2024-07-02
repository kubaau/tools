#include "CutString.hpp"
#include "GtestWrapper.hpp"

TEST(CutString, cutFromBegin)
{
    EXPECT_EQ("", cutFromBegin("", 3));
    EXPECT_EQ("", cutFromBegin("12", 3));
    EXPECT_EQ("456789", cutFromBegin("123456789", 3));
}

TEST(CutString, cutFromEnd)
{
    EXPECT_EQ("", cutFromEnd("", 3));
    EXPECT_EQ("", cutFromEnd("12", 3));
    EXPECT_EQ("123456", cutFromEnd("123456789", 3));
}
