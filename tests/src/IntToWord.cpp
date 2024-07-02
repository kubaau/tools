#include "IntToWord.hpp"
#include "GtestWrapper.hpp"

TEST(IntToWord, toWord)
{
    EXPECT_EQ("zero", toWord(0));
    EXPECT_EQ("one", toWord(1));
    EXPECT_EQ("seventeen", toWord(17));
    EXPECT_EQ("twenty three", toWord(23));
}
