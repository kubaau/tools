#include "MemberOffset.hpp"

#include "GtestWrapper.hpp"
#include "VSCompatibility.hpp"

TEST(MemberOffset, offsetOfMember)
{
    struct S
    {
        u8 m1;
        __attribute__((aligned(8))) u64 m2;
        u16 m3[3];
        u16 pad;
        u32 m4;
        u8 m5;
        u8 m6;
        u32 m7;
        u8 m8;
        u16 m9;
    };
    EXPECT_EQ(0, offsetOfMember(&S::m1));
    EXPECT_EQ(8, offsetOfMember(&S::m2));
    EXPECT_EQ(16, offsetOfMember(&S::m3));
    EXPECT_EQ(24, offsetOfMember(&S::m4));
    EXPECT_EQ(28, offsetOfMember(&S::m5));
    EXPECT_EQ(29, offsetOfMember(&S::m6));
    EXPECT_EQ(32, offsetOfMember(&S::m7));
    EXPECT_EQ(36, offsetOfMember(&S::m8));
    EXPECT_EQ(38, offsetOfMember(&S::m9));
}
