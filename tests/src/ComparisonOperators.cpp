#include "GtestWrapper.hpp" // must be first

#include "ComparisonOperators.hpp"

struct Pod1
{
    MEMCMPARABLE;
    int i;
    int x;
    int* i_ptr;
};

struct Pod2
{
    MEMCMPARABLE;
    int i;
    int x;
    int* i_ptr;
};
auto operator==(const Pod2& lhs, const Pod2& rhs)
{
    *lhs.i_ptr = 3;
    return tie(lhs.i, *lhs.i_ptr) == tie(rhs.i, *rhs.i_ptr);
}
auto operator!=(const Pod2& lhs, const Pod2& rhs)
{
    *lhs.i_ptr = 4;
    return tie(lhs.i, *lhs.i_ptr) != tie(rhs.i, *rhs.i_ptr);
}

struct Pod3
{
    auto tieAll() const { return tie(); }
};

struct Pod4
{
    int a;
    u64 b;
    auto tieAll() const { return tie(a, b); }
};

struct NotPod
{
    NotPod(int) {}
    auto tieAll() const { return tie(); }
};

TEST(ComparisonOperators, pod)
{
    int i = 2;
    EXPECT_EQ((Pod1{1, 2, &i}), (Pod1{1, 2, &i}));
    EXPECT_EQ(2, i);
    EXPECT_NE((Pod1{1, 2, &i}), (Pod1{2, 2, &i}));
    EXPECT_EQ(2, i);
    EXPECT_EQ((Pod2{1, 2, &i}), (Pod2{1, 2, &i}));
    EXPECT_EQ(3, i);
    EXPECT_NE((Pod2{1, 2, &i}), (Pod2{2, 2, &i}));
    EXPECT_EQ(4, i);

    Pod3 a;
    Pod3 b;
    EXPECT_EQ(a, b);

    Pod4 c{1, 2};
    Pod4 d{1, 2};
    EXPECT_EQ(c, d);

    EXPECT_EQ((NotPod{1}), (NotPod{1}));
    // EXPECT_NE((NotPod{1}), (NotPod{2}));
}

TEST(ComparisonOperators, container)
{
    using V = vector<int>;
    EXPECT_EQ((V{}), (V{}));
    EXPECT_EQ((V{1}), (V{1}));
    EXPECT_EQ((V{1, 2}), (V{1, 2}));
    EXPECT_EQ((V{1, 1, 1}), (V{1, 1, 1}));
    EXPECT_EQ((V{1, 2, 3}), (V{1, 2, 3}));
    EXPECT_NE((V{}), (V{1}));
    EXPECT_NE((V{1}), (V{1, 2}));
    EXPECT_NE((V{1, 2, 3}), (V{1, 2, 2}));
}
