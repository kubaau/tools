#include "Strong.hpp"
#include "Contains.hpp"
#include "GtestWrapper.hpp"

TEST(Strong, StrongType)
{
    DEFINE_STRONG_TYPE(StrongInt, int);

    constexpr StrongInt i = 7;
    EXPECT_EQ(7, *i);
    EXPECT_TRUE(i == StrongInt{7});
    EXPECT_FALSE(i == StrongInt{8});
    EXPECT_FALSE(i != StrongInt{7});
    EXPECT_TRUE(i != StrongInt{8});
    EXPECT_FALSE(i < StrongInt{7});
    EXPECT_TRUE(i < StrongInt{8});
    EXPECT_FALSE(i > StrongInt{7});
    EXPECT_TRUE(i > StrongInt{6});
    EXPECT_EQ(14, i << 1);
    EXPECT_EQ(3, i >> 1);

    auto j = StrongInt{7};
    EXPECT_EQ(7, j++);
    EXPECT_EQ(9, ++j);
    EXPECT_EQ(9, j--);
    EXPECT_EQ(7, --j);
    EXPECT_EQ(9, j += 2);
    EXPECT_EQ(6, j -= 3);

    set<StrongInt> s{i};
    EXPECT_TRUE(contains(s, i));
    EXPECT_FALSE(contains(s, StrongInt{6}));

    struct S
    {
        int a = 5;
    };
    DEFINE_STRONG_TYPE(StrongS, S);
    StrongS ss;
    EXPECT_EQ(5, ss->a);
}
