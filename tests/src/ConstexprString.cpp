#include "ConstexprString.hpp"
#include "GtestWrapper.hpp"

namespace
{
    void expectOffset(const char* s, char c, int offset, const char* (*f)(const char*, int))
    {
        EXPECT_EQ(offset, f(s, c) - s);
    }
    [[maybe_unused]] void expectOffset(const char* s, char c, int offset, char* (*f)(const char*, int))
    {
        EXPECT_EQ(offset, f(s, c) - s);
    }
}

// strchr

TEST(ConstexprString, strchrConstexpr_is_constexpr)
{
    static_assert(strchrConstexpr("aaa.cpp", '/') == nullptr, "");
    static_assert(strchrConstexpr("aa/a.cpp", '/')[1] == 'a', "");
}

TEST(ConstexprString, strchrConstexpr_returns_string_starting_with_first_occurence)
{
    EXPECT_EQ(string{"/a.cpp"}, strchrConstexpr("aa/a.cpp", '/'));
    EXPECT_EQ(strchr("aa/a.cpp", '/'), strchrConstexpr("aa/a.cpp", '/'));
}

TEST(ConstexprString, strchrConstexpr_returns_null_if_character_not_found)
{
    EXPECT_EQ(nullptr, strchrConstexpr("abc.def", 'x'));
    EXPECT_EQ(strchr("abc.def", 'x'), strchrConstexpr("abc.def", 'x'));
}

TEST(ConstexprString, strchrConstexpr_returned_character_offset_is_correct)
{
    expectOffset("abc.def", '.', 3, strchrConstexpr);
    expectOffset(".abcdef", '.', 0, strchrConstexpr);
    expectOffset("abcdef.", '.', 6, strchrConstexpr);
    expectOffset(".abc.d.ef", '.', 0, strchrConstexpr);
    expectOffset(".abcxdxef", 'x', 4, strchrConstexpr);

    expectOffset("abc.def", '.', 3, strchr);
    expectOffset(".abcdef", '.', 0, strchr);
    expectOffset("abcdef.", '.', 6, strchr);
    expectOffset(".abc.d.ef", '.', 0, strchr);
    expectOffset(".abcxdxef", 'x', 4, strchr);
}

// strrchr

TEST(ConstexprString, strrchrConstexpr_is_constexpr)
{
    static_assert(strrchrConstexpr("aaa.cpp", '/') == nullptr, "");
    static_assert(strrchrConstexpr("aa/a.cpp", '/')[1] == 'a', "");
}

TEST(ConstexprString, strrchrConstexpr_returns_string_starting_with_last_occurence)
{
    EXPECT_EQ(string{"/a.cpp"}, strrchrConstexpr("aa/a.cpp", '/'));
    EXPECT_EQ(strrchr("aa/a.cpp", '/'), strrchrConstexpr("aa/a.cpp", '/'));
}

TEST(ConstexprString, strrchrConstexpr_returns_null_if_character_not_found)
{
    EXPECT_EQ(nullptr, strrchrConstexpr("abc.def", 'x'));
    EXPECT_EQ(strrchr("abc.def", 'x'), strrchrConstexpr("abc.def", 'x'));
}

TEST(ConstexprString, strrchrConstexpr_returned_character_offset_is_correct)
{
    expectOffset("abc.def", '.', 3, strrchrConstexpr);
    expectOffset(".abcdef", '.', 0, strrchrConstexpr);
    expectOffset("abcdef.", '.', 6, strrchrConstexpr);
    expectOffset(".abc.d.ef", '.', 6, strrchrConstexpr);
    expectOffset(".abcxdxef", 'x', 6, strrchrConstexpr);

    expectOffset("abc.def", '.', 3, strrchr);
    expectOffset(".abcdef", '.', 0, strrchr);
    expectOffset("abcdef.", '.', 6, strrchr);
    expectOffset(".abc.d.ef", '.', 6, strrchr);
    expectOffset(".abcxdxef", 'x', 6, strrchr);
}

// strchrnul

TEST(ConstexprString, strchrnulConstexpr_is_constexpr)
{
    static_assert(*strchrnulConstexpr("aaa.cpp", '/') == '\0', "");
    static_assert(strchrnulConstexpr("aa/a.cpp", '/')[1] == 'a', "");
}

TEST(ConstexprString, strchrnulConstexpr_returns_string_starting_with_first_occurence)
{
    EXPECT_EQ(string{"/a.cpp"}, strchrnulConstexpr("aa/a.cpp", '/'));
#ifndef _WIN32
    EXPECT_EQ(strchrnul("aa/a.cpp", '/'), strchrnulConstexpr("aa/a.cpp", '/'));
#endif
}

TEST(ConstexprString, strchrnulConstexpr_returns_character_null_if_character_not_found)
{
    EXPECT_EQ(NULL, *strchrnulConstexpr("abc.def", 'x'));
#ifndef _WIN32
    EXPECT_EQ(*strchrnul("abc.def", 'x'), *strchrnulConstexpr("abc.def", 'x'));
#endif
}

TEST(ConstexprString, strchrnulConstexpr_returned_character_offset_is_correct)
{
    expectOffset("abc.def", '.', 3, strchrnulConstexpr);
    expectOffset(".abcdef", '.', 0, strchrnulConstexpr);
    expectOffset("abcdef.", '.', 6, strchrnulConstexpr);
    expectOffset(".abc.d.ef", '.', 0, strchrnulConstexpr);
    expectOffset(".abcxdxef", 'x', 4, strchrnulConstexpr);

#ifndef _WIN32
    expectOffset("abc.def", '.', 3, strchrnul);
    expectOffset(".abcdef", '.', 0, strchrnul);
    expectOffset("abcdef.", '.', 6, strchrnul);
    expectOffset(".abc.d.ef", '.', 0, strchrnul);
    expectOffset(".abcxdxef", 'x', 4, strchrnul);
#endif
}

TEST(ConstexprString, strchrnulConstexpr_returns_character_at_the_end_of_string_if_character_not_found)
{
    EXPECT_EQ(static_cast<ptrdiff_t>(strlen("aaa")), strchrnulConstexpr("aaa", '\0') - "aaa");
    EXPECT_EQ(static_cast<ptrdiff_t>(strlen("aaa")), strchrnulConstexpr("aaa", 'b') - "aaa");

#ifndef _WIN32
    EXPECT_EQ(strchrnul("aaa", '\0') - "aaa", strchrnulConstexpr("aaa", '\0') - "aaa");
    EXPECT_EQ(strchrnul("aaa", 'b') - "aaa", strchrnulConstexpr("aaa", 'b') - "aaa");
#endif
}
