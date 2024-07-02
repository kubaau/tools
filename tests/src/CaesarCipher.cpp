#include "CaesarCipher.hpp"
#include "GtestWrapper.hpp"

TEST(CaesarCipher, caesarShift)
{
    EXPECT_EQ('d', caesarShift('a', 3));
    EXPECT_EQ('e', caesarShift('b', 3));
    EXPECT_EQ('a', caesarShift('x', 3));
    EXPECT_EQ('b', caesarShift('y', 3));
    EXPECT_EQ('c', caesarShift('z', 3));
    EXPECT_EQ('d', caesarShift('z', 4));
    EXPECT_EQ('x', caesarShift('a', -3));
    EXPECT_EQ('y', caesarShift('b', -3));
    EXPECT_EQ('u', caesarShift('x', -3));
    EXPECT_EQ('v', caesarShift('y', -3));
    EXPECT_EQ('w', caesarShift('z', -3));
    EXPECT_EQ('v', caesarShift('z', -4));

    EXPECT_EQ('D', caesarShift('A', 3));
    EXPECT_EQ('E', caesarShift('B', 3));
    EXPECT_EQ('A', caesarShift('X', 3));
    EXPECT_EQ('B', caesarShift('Y', 3));
    EXPECT_EQ('C', caesarShift('Z', 3));
    EXPECT_EQ('D', caesarShift('Z', 4));
    EXPECT_EQ('X', caesarShift('A', -3));
    EXPECT_EQ('Y', caesarShift('B', -3));
    EXPECT_EQ('U', caesarShift('X', -3));
    EXPECT_EQ('V', caesarShift('Y', -3));
    EXPECT_EQ('W', caesarShift('Z', -3));
    EXPECT_EQ('V', caesarShift('Z', -4));
}

TEST(CaesarCipher, caesarCipher)
{
    EXPECT_EQ("deabc", caesarCipher("abxyz", 3));
    EXPECT_EQ("efbcd", caesarCipher("abxyz", 4));
    EXPECT_EQ("DEABC", caesarCipher("ABXYZ", 3));
    EXPECT_EQ("EFBCD", caesarCipher("ABXYZ", 4));
    EXPECT_EQ("xyuvw", caesarCipher("abxyz", -3));
    EXPECT_EQ("wxtuv", caesarCipher("abxyz", -4));
    EXPECT_EQ("XYUVW", caesarCipher("ABXYZ", -3));
    EXPECT_EQ("WXTUV", caesarCipher("ABXYZ", -4));
    EXPECT_EQ("abxyz", caesarCipher(caesarCipher("abxyz", 3), -3));
    EXPECT_EQ("ABXYZ", caesarCipher(caesarCipher("ABXYZ", 3), -3));
}
