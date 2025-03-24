#include "DivideEvenly.hpp"

#include "GtestWrapper.hpp"

TEST(DivideEvenly, divideEvenly)
{
    EXPECT_EQ((Vsz{1, 1, 1, 1}), divideEvenly(4, 4));
    EXPECT_EQ((Vsz{1, 1, 0, 0}), divideEvenly(2, 4));
    EXPECT_EQ((Vsz{4}), divideEvenly(4, 1));
    EXPECT_EQ((Vsz{}), divideEvenly(4, 0));
    EXPECT_EQ(Vsz(8, 8), divideEvenly(64, 8));
    EXPECT_EQ((Vsz{9, 8, 8, 8, 8, 8, 8, 8}), divideEvenly(65, 8));
    EXPECT_EQ((Vsz{9, 9, 9, 9, 9, 8, 8, 8}), divideEvenly(69, 8));
}

TEST(DivideEvenly, divideEvenly2)
{
    EXPECT_EQ((Vsz{1, 1, 1, 1}), divideEvenly2(4, 4));
    EXPECT_EQ((Vsz{1, 1, 0, 0}), divideEvenly2(2, 4));
    EXPECT_EQ((Vsz{4}), divideEvenly2(4, 1));
    EXPECT_EQ((Vsz{}), divideEvenly2(4, 0));
    EXPECT_EQ(Vsz(8, 8), divideEvenly2(64, 8));
    EXPECT_EQ((Vsz{9, 8, 8, 8, 8, 8, 8, 8}), divideEvenly2(65, 8));
    EXPECT_EQ((Vsz{9, 9, 9, 9, 9, 8, 8, 8}), divideEvenly2(69, 8));
}
