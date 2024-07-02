#include "StringToInt.hpp"
#include "GtestWrapper.hpp"

TEST(StringToInt, toInt_char)
{
    EXPECT_EQ(0, toInt('0'));
    EXPECT_EQ(1, toInt('1'));
    EXPECT_EQ(2, toInt('2'));
    EXPECT_EQ(3, toInt('3'));
    EXPECT_EQ(4, toInt('4'));
    EXPECT_EQ(5, toInt('5'));
    EXPECT_EQ(6, toInt('6'));
    EXPECT_EQ(7, toInt('7'));
    EXPECT_EQ(8, toInt('8'));
    EXPECT_EQ(9, toInt('9'));
}

TEST(StringToInt, toInt_string)
{
    EXPECT_EQ(0, toInt("0"));
    EXPECT_EQ(1, toInt("1"));
    EXPECT_EQ(11, toInt("11"));
    EXPECT_EQ(234, toInt("234"));
    EXPECT_EQ(-1, toInt("-1"));
    EXPECT_EQ(-11, toInt("-11"));
    EXPECT_EQ(-234, toInt("-234"));
}

TEST(StringToInt, toVectorOfDigits)
{
    EXPECT_EQ(V8{0}, toVectorOfDigits("0"));
    EXPECT_EQ(V8{1}, toVectorOfDigits("1"));
    EXPECT_EQ((V8{1, 1}), toVectorOfDigits("11"));
    EXPECT_EQ((V8{2, 3, 4}), toVectorOfDigits("234"));
}

TEST(StringToInt, wordToByte)
{
    EXPECT_EQ(0, wordToByte("0"));
    EXPECT_EQ(0, wordToByte("00"));
    EXPECT_EQ(1, wordToByte("1"));
    EXPECT_EQ(1, wordToByte("01"));
    EXPECT_EQ(0xCE, wordToByte("CE"));
}

TEST(StringToInt, hexStringToBytes)
{
    EXPECT_EQ(Bytes{}, hexStringToBytes(""));
    EXPECT_EQ(Bytes{0}, hexStringToBytes("0"));
    EXPECT_EQ(Bytes{0}, hexStringToBytes("00"));
    EXPECT_EQ(Bytes{1}, hexStringToBytes("1"));
    EXPECT_EQ(Bytes{1}, hexStringToBytes("01"));
    EXPECT_EQ((Bytes{0, 1}), hexStringToBytes("00 01"));
    EXPECT_EQ((Bytes{0x0A, 0xCE}), hexStringToBytes("0A CE"));
    EXPECT_EQ((Bytes{0, 1, 0x1A, 0xB2, 0x3C}), hexStringToBytes("00 01 1A B2 3C"));
}
