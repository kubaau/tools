#include "ContainsKeys.hpp"

#include "GtestWrapper.hpp"

TEST(ContainsKeys, containsKeys)
{
    S s{1, 2, 3};
    EXPECT_TRUE(containsKeys(s, {}));
    EXPECT_TRUE(containsKeysOrdered(s, {}));
    EXPECT_TRUE(containsKeys(s, {1, 2, 3}));
    EXPECT_TRUE(containsKeysOrdered(s, {1, 2, 3}));
    EXPECT_FALSE(containsKeys(s, {1, 2, 3, 4}));
    EXPECT_FALSE(containsKeysOrdered(s, {1, 2, 3, 4}));
    EXPECT_FALSE(containsKeys(s, V{1, 2, 3, 4}));
    EXPECT_FALSE(containsKeysOrdered(s, V{1, 2, 3, 4}));

    M m{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_TRUE(containsKeys(m, {}));
    EXPECT_TRUE(containsKeysOrdered(m, {}));
    EXPECT_TRUE(containsKeys(m, {1, 3, 5}));
    EXPECT_TRUE(containsKeysOrdered(m, {1, 3, 5}));
    EXPECT_FALSE(containsKeys(m, {1, 4, 5}));
    EXPECT_FALSE(containsKeysOrdered(m, {1, 4, 5}));

    US us{1, 2, 3};
    EXPECT_TRUE(containsKeys(us, {}));
    EXPECT_TRUE(containsKeys(us, {1, 2, 3}));
    EXPECT_FALSE(containsKeys(us, {1, 2, 3, 4}));

    UM um{{1, 2}, {3, 4}, {5, 6}};
    EXPECT_TRUE(containsKeys(um, {}));
    EXPECT_TRUE(containsKeys(um, {1, 3, 5}));
    EXPECT_FALSE(containsKeys(um, {1, 4, 5}));
}
