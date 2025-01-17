#include "Guarded.hpp"

#include "GtestWrapper.hpp"

namespace
{
    auto foo(const Guarded<int>& gi)
    {
        EXPECT_EQ(*gi, 42);
    }

    auto bar(Guarded<int> gi)
    {
        *gi += 5;
        EXPECT_EQ(*gi, 47);
    }
}

TEST(Guarded, Guarded)
{
    int i = 42;
    mutex mtx;
    Guarded<int> gi{i, mtx};
    ASSERT_TRUE(gi);
    foo(gi);
    ASSERT_TRUE(gi);
    bar(move(gi));
    EXPECT_FALSE(gi);

    Guarded<int> gi2{i, mtx};
    gi = move(gi2);
    EXPECT_TRUE(gi);
    EXPECT_FALSE(gi2);

    EXPECT_EQ(i, 47);
}

namespace
{
    auto baz(const GuardedSoft<int>& gi)
    {
        EXPECT_EQ(*gi, 42);
    }

    auto qux(GuardedSoft<int> gi)
    {
        *gi += 5;
        EXPECT_EQ(*gi, 47);
    }
}

TEST(GuardedSoft, GuardedSoft)
{
    int i = 42;
    mutex mtx;
    GuardedSoft<int> gi{i, mtx};
    EXPECT_FALSE(gi);
    mtx.lock();
    EXPECT_TRUE(gi);
    baz(gi);
    EXPECT_TRUE(gi);
    qux(gi);
    EXPECT_TRUE(gi);

    GuardedSoft<int> gi2{i, mtx};
    gi = move(gi2);
    EXPECT_TRUE(gi);
    EXPECT_FALSE(gi2);

    EXPECT_EQ(i, 47);
    mtx.unlock();
}
