#include "Iterators.hpp"
#include "GtestWrapper.hpp"

TEST(Iterators, end_inserter)
{
    V vi = {1, 2, 3};
    V vo;
    copy(cbegin(vi), cend(vi), end_inserter(vo));
    EXPECT_EQ(vi, vo);
    copy(cbegin(vi), cend(vi), end_inserter(vo));
    EXPECT_EQ((V{1, 2, 3, 1, 2, 3}), vo);

    S si = {1, 3, 2};
    S so;
    copy(cbegin(si), cend(si), end_inserter(so));
    EXPECT_EQ(si, so);
    copy(cbegin(si), cend(si), end_inserter(so));
    EXPECT_EQ((S{3, 2, 1}), so);
}

TEST(Iterators, begin_inserter)
{
    V vi = {1, 2, 3};
    V vo;
    copy(cbegin(vi), cend(vi), begin_inserter(vo));
    EXPECT_EQ(vi, vo);
    vi.back() = 4;
    copy(cbegin(vi), cend(vi), begin_inserter(vo));
    EXPECT_EQ((V{1, 2, 4, 1, 2, 3}), vo);

    S si = {1, 3, 2};
    S so;
    copy(cbegin(si), cend(si), begin_inserter(so));
    EXPECT_EQ(si, so);
    copy(cbegin(si), cend(si), begin_inserter(so));
    EXPECT_EQ((S{3, 2, 1}), so);
}

TEST(Iterators, mid_cmid)
{
    V v = {1, 2, 3, 4, 5};
    EXPECT_EQ(3, *mid(begin(v), end(v)));
    EXPECT_EQ(4, *mid(begin(v) + 1, end(v)));
    EXPECT_EQ(4, *mid(begin(v) + 2, end(v)));
    EXPECT_EQ(5, *mid(begin(v) + 3, end(v)));
    EXPECT_EQ(3, *mid(v));
    EXPECT_EQ(3, *cmid(v));
}
