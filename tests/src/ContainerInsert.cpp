#include "ContainerInsert.hpp"
#include "GtestWrapper.hpp"

TEST(ContainerInsert, insert)
{
    V v{1, 2, 3};
    insert(v, 3);
    EXPECT_EQ((V{1, 2, 3, 3}), v);

    S s{1, 2, 3};
    auto result = insert(s, 4);
    EXPECT_TRUE(result.second);
    EXPECT_EQ((S{1, 2, 3, 4}), s);
    result = insert(s, 4);
    EXPECT_FALSE(result.second);
    EXPECT_EQ((S{1, 2, 3, 4}), s);
}
