#include "GtestWrapper.hpp"

TEST(VSCompatibility, ciso646)
{
    EXPECT_TRUE(1 and 1);
    EXPECT_FALSE(1 and 0);
    EXPECT_FALSE(0 and 1);
    EXPECT_FALSE(0 and 0);

    auto t = 1;
    EXPECT_TRUE((t = 1) and_eq 1);
    EXPECT_FALSE((t = 1) and_eq 0);
    EXPECT_FALSE((t = 0) and_eq 1);
    EXPECT_FALSE((t = 0) and_eq 0);

    EXPECT_TRUE(1 bitand 1);
    EXPECT_FALSE(1 bitand 0);
    EXPECT_FALSE(0 bitand 1);
    EXPECT_FALSE(0 bitand 0);
    EXPECT_EQ(2, 2 bitand 3);

    EXPECT_TRUE(1 bitor 1);
    EXPECT_TRUE(1 bitor 0);
    EXPECT_TRUE(0 bitor 1);
    EXPECT_FALSE(0 bitor 0);
    EXPECT_EQ(3, 2 bitor 3);

    EXPECT_EQ(-2, compl 1);
    EXPECT_EQ(-1, compl 0);
    EXPECT_EQ(0, compl-1);
    EXPECT_EQ(1, compl-2);

    EXPECT_FALSE(not 1);
    EXPECT_TRUE(not 0);

    EXPECT_FALSE((t = 1) not_eq 1);
    EXPECT_TRUE((t = 1) not_eq 0);
    EXPECT_TRUE((t = 0) not_eq 1);
    EXPECT_FALSE((t = 0) not_eq 0);

    EXPECT_TRUE(1 or 1);
    EXPECT_TRUE(1 or 0);
    EXPECT_TRUE(0 or 1);
    EXPECT_FALSE(0 or 0);

    EXPECT_TRUE((t = 1) or_eq 1);
    EXPECT_TRUE((t = 1) or_eq 0);
    EXPECT_TRUE((t = 0) or_eq 1);
    EXPECT_FALSE((t = 0) or_eq 0);

    EXPECT_EQ(0, 1 xor 1);
    EXPECT_EQ(1, 1 xor 0);
    EXPECT_EQ(1, 0 xor 1);
    EXPECT_EQ(0, 0 xor 0);

    EXPECT_EQ(0, (t = 1) xor_eq 1);
    EXPECT_EQ(1, (t = 1) xor_eq 0);
    EXPECT_EQ(1, (t = 0) xor_eq 1);
    EXPECT_EQ(0, (t = 0) xor_eq 0);

    //    <%
    //        int a<:3:> = <%1, 2, 3%>;
    //%:define MACRO EXPECT_EQ(3, a<:2:>)
    //        MACRO;
    //    %>
}
