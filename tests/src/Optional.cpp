#include "Optional.hpp"
#include "GtestWrapper.hpp"
#include "StringStream.hpp"

TEST(Optional, output_operator)
{
    optional<int> o;
    ostringstream oss;
    oss << o;
    EXPECT_EQ("<none>", oss.str());
    clear(oss);

    o = 7;
    oss << o;
    EXPECT_EQ("7", oss.str());
}
