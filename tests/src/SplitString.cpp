#include "SplitString.hpp"
#include "Contains.hpp"
#include "GtestWrapper.hpp"

TEST(SplitString, unifyDelimeters)
{
    const auto s = unifyDelimiters("ala:ma kota", {':', ' '});
    EXPECT_TRUE(in(s, {"ala:ma:kota", "ala ma kota"}));
    EXPECT_THROW(unifyDelimiters("ala:ma kota", {}), logic_error);
}

TEST(SplitString, split_outputIterator)
{
    Vs s;
    splitIt("", back_inserter(s));
    EXPECT_EQ(Vs{}, s);
    splitIt("a", back_inserter(s));
    EXPECT_EQ(Vs{"a"}, s);
    splitIt("a b", back_inserter(s));
    EXPECT_EQ((Vs{"a", "a", "b"}), s);
    s.clear();
    splitIt("a  b", back_inserter(s));
    EXPECT_EQ((Vs{"a", "b"}), s);
    s.clear();
    splitIt("ala ma kota", back_inserter(s));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), s);
    splitIt("ala:ma:kota", begin(s), ':');
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), s);
    s.clear();
    s.resize(4);
    splitIt("ala::ma:kota", begin(s), ':');
    EXPECT_EQ((Vs{"ala", "ma", "kota", ""}), s);
    s.clear();
    splitIt("ala:ma kota", back_inserter(s), {':', ' '});
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), s);
    EXPECT_THROW(splitIt("ala:ma kota", back_inserter(s), set<char>{}), logic_error);
}

TEST(SplitString, split_returnVector)
{
    EXPECT_EQ(Vs{}, split(""));
    EXPECT_EQ(Vs{"a"}, split("a"));
    EXPECT_EQ((Vs{"a", "b"}), split("a b"));
    EXPECT_EQ((Vs{"a", "b"}), split("a  b"));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), split("ala ma kota"));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), split("ala:ma:kota", ':'));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), split("ala::ma:kota", ':'));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), split("ala:ma kota", Detail::CharDelims{':', ' '}));
    EXPECT_THROW(split("ala:ma kota", set<char>{}), logic_error);
}

TEST(SplitString, split_regex)
{
    EXPECT_EQ(Vs{}, splitRegex(""));
    EXPECT_EQ(Vs{"a"}, splitRegex("a"));
    EXPECT_EQ((Vs{"a", "b"}), splitRegex("a b"));
    EXPECT_EQ((Vs{"a", "b"}), splitRegex("a  b"));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), splitRegex("ala ma kota"));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), splitRegex("ala:ma:kota", ":"));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), splitRegex("ala::ma:kota", ":"));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), splitRegex("ala:ma kota", ":|\\s+"));
    EXPECT_EQ((Vs{"ala", "ma", "kota"}), split("ala:ma kota", regex{"\\s+|:"}));
}
