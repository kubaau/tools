#include "PtrMagic.hpp"
#include "GtestWrapper.hpp"

TEST(PtrMagic, moveNBytes_int)
{
    int n[3];
    auto p = n;
    moveNBytes(p, 8);
    EXPECT_EQ(n + 2, p);
    moveNBytes(p, -8);
    EXPECT_EQ(n, p);
    moveNBytes(p, 5);
    EXPECT_EQ(reinterpret_cast<size_t>(n) + 5, reinterpret_cast<size_t>(p));
}

TEST(PtrMagic, moveNBytes_const_short)
{
    const short n[5] = {};
    auto p = n;
    moveNBytes(p, 8);
    EXPECT_EQ(n + 4, p);
    moveNBytes(p, -8);
    EXPECT_EQ(n, p);
    moveNBytes(p, 5);
    EXPECT_EQ(reinterpret_cast<size_t>(n) + 5, reinterpret_cast<size_t>(p));
}
