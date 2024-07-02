#include "Stringify.hpp"
#include "GtestWrapper.hpp"

TEST(Stringify, stringify)
{
    auto s = stringify("abc", 1, 3.14, "def", V{1, 2, 3});
    print(s);
    EXPECT_EQ("abc 1 3.14 def {1, 2, 3}", s);
}
