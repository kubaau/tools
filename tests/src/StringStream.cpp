#include "StringStream.hpp"
#include "GtestWrapper.hpp"

TEST(StringStream, clear)
{
    ostringstream oss;
    oss << "aaa";
    EXPECT_EQ("aaa", oss.str());
    clear(oss);
    EXPECT_TRUE(oss.str().empty());
    oss << "bbb";
    EXPECT_EQ("bbb", oss.str());
    clearStream(oss);
    EXPECT_TRUE(oss.str().empty());

    istringstream iss{"aaa"};
    EXPECT_EQ("aaa", iss.str());
    clear(iss);
    EXPECT_TRUE(iss.str().empty());
    iss.str("bbb");
    EXPECT_EQ("bbb", iss.str());
    clearStream(iss);
    EXPECT_TRUE(iss.str().empty());
}
