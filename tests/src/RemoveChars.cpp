#include "RemoveChars.hpp"

#include "GtestWrapper.hpp"

TEST(RemoveChars, removeChars)
{
    const string base = "aaabbcde fgh? ?";

    string s = base;
    string remove = "a";
    string expected = "bbcde fgh? ?";
    EXPECT_EQ(removeChars(s, remove), expected);
    EXPECT_EQ(s, expected);

    s = base;
    remove = "ac";
    expected = "bbde fgh? ?";
    EXPECT_EQ(removeChars(s, remove), expected);
    EXPECT_EQ(s, expected);

    s = base;
    remove = "bd?";
    expected = "aaace fgh ";
    EXPECT_EQ(removeChars(s, remove), expected);
    EXPECT_EQ(s, expected);

    s = base;
    remove = "? e";
    expected = "aaabbcdfgh";
    EXPECT_EQ(removeChars(s, remove), expected);
    EXPECT_EQ(s, expected);

    s = base;
    remove = "????????  ";
    expected = "aaabbcdefgh";
    EXPECT_EQ(removeChars(s, remove), expected);
    EXPECT_EQ(s, expected);

    s = base;
    remove = s;
    expected = "";
    EXPECT_EQ(removeChars(s, remove), expected);
    EXPECT_EQ(s, expected);
}

TEST(RemoveChars, removeCharSet)
{
    string s = "aaabbcde fgh? ?";
    string expected = "bbcde fgh ";
    EXPECT_EQ(removeCharSet(s, {'a', '?'}), expected);
    EXPECT_EQ(s, expected);
}
