#include "StackPop.hpp"
#include "GtestWrapper.hpp"

TEST(StackPop, pop)
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(3, pop(s));
    EXPECT_EQ(2, pop(s));
    EXPECT_EQ(1, pop(s));
    EXPECT_TRUE(s.empty());
}
