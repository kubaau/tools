#include "QueuePop.hpp"
#include "GtestWrapper.hpp"

TEST(QueuePop, pop)
{
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    EXPECT_EQ(1, pop(q));
    EXPECT_EQ(2, pop(q));
    EXPECT_EQ(3, pop(q));
    EXPECT_TRUE(q.empty());
}
