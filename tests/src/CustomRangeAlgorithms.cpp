#include "CustomRangeAlgorithms.hpp"
#include "Endl.hpp"
#include "GtestWrapper.hpp"
#include "Numeric.hpp"

static auto is_even = [] (auto n) { return isEven(n); };

TEST(CustomRangeAlgorithms, copyIf)
{
    V v(9);
    iota(v);

    V out;
    copyIf(cbegin(v), cend(v), back_inserter(out), is_even, 3);
    EXPECT_EQ((V{0, 2, 4}), out);

    out.clear();
    copyIf(cbegin(v), cend(v), back_inserter(out), is_even, 0);
    EXPECT_EQ((V{}), out);

    out.clear();
    copyIf(cbegin(v), cend(v), back_inserter(out), is_even, 100);
    EXPECT_EQ((V{0, 2, 4, 6, 8}), out);
}

TEST(CustomRangeAlgorithms, copyIf_container)
{
    V v(9);
    iota(v);

    V out;
    copyIf(v, out, is_even, 3);
    EXPECT_EQ((V{0, 2, 4}), out);

    out.clear();
    copyIf(v, out, is_even, 0);
    EXPECT_EQ((V{}), out);

    out.clear();
    copyIf(v, out, is_even, 100);
    EXPECT_EQ((V{0, 2, 4, 6, 8}), out);
}

TEST(CustomRangeAlgorithms, copyIf_ret)
{
    V v(9);
    iota(v);

    V out;
    out = copyIf(v, is_even, 3);
    EXPECT_EQ((V{0, 2, 4}), out);

    out.clear();
    out = copyIf(v, is_even, 0);
    EXPECT_EQ((V{}), out);

    out.clear();
    out = copyIf(v, is_even, 100);
    EXPECT_EQ((V{0, 2, 4, 6, 8}), out);
}

TEST(CustomRangeAlgorithms, erase_one)
{
    V in{1, 2, 3, 2};
    erase_one(in, 2);
    EXPECT_EQ((V{1, 3, 2}), in);
    erase_one(in, 4);
    EXPECT_EQ((V{1, 3, 2}), in);
    erase_one(in, 1);
    erase_one(in, 3);
    erase_one(in, 2);
    EXPECT_TRUE(in.empty());
}

/*
TEST(CustomRangeAlgorithms, erase_one_sorted)
{
    V in{1, 2, 2, 3, 3, 4};
    erase_one_sorted(in, 2);
    EXPECT_EQ((V{1, 2, 3, 3, 4}), in);
    erase_one_sorted(in, 4);
    EXPECT_EQ((V{1, 2, 3, 3}), in);
    erase_one_sorted(in, 3);
    EXPECT_EQ((V{1, 2, 3}), in);
    erase_one_sorted(in, 1);
    erase_one_sorted(in, 2);
    erase_one_sorted(in, 3);
    EXPECT_TRUE(in.empty());
}
*/

TEST(CustomRangeAlgorithms, sortStackOnly)
{
    stack<int> s;
    sortStackOnly(s);
    EXPECT_TRUE(s.empty());
    s.push(5);
    sortStackOnly(s);
    EXPECT_EQ(5, s.top());
    EXPECT_EQ(1u, s.size());
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(1);
    sortStackOnly(s);
    EXPECT_EQ(5u, s.size());
    EXPECT_EQ(1, pop(s));
    EXPECT_EQ(2, pop(s));
    EXPECT_EQ(3, pop(s));
    EXPECT_EQ(4, pop(s));
    EXPECT_EQ(5, pop(s));
}

TEST(CustomRangeAlgorithms, allUnique)
{
    EXPECT_TRUE(allUnique(V{1, 2, 3}));
    EXPECT_FALSE(allUnique(V{1, 2, 2}));
}

TEST(CustomRangeAlgorithms, allUniqueUnsorted)
{
    EXPECT_TRUE(allUniqueUnsortedNlogN(V{1, 2, 3}));
    EXPECT_FALSE(allUniqueUnsortedNlogN(V{1, 2, 2}));
    EXPECT_TRUE(allUniqueUnsortedNlogN(V{3, 2, 1}));
    EXPECT_FALSE(allUniqueUnsortedNlogN(V{2, 3, 2}));

    EXPECT_TRUE(allUniqueUnsortedN(V{1, 2, 3}));
    EXPECT_FALSE(allUniqueUnsortedN(V{1, 2, 2}));
    EXPECT_TRUE(allUniqueUnsortedN(V{3, 2, 1}));
    EXPECT_FALSE(allUniqueUnsortedN(V{2, 3, 2}));
}

TEST(CustomRangeAlgorithms, reestablishOrder)
{
    V original = {3, 2, 1, 4, 7};
    V reordered = {1, 5, 7, 3};
    reestablishOrder(reordered, original);
    EXPECT_EQ((V{3, 1, 7, 5}), reordered);
}

TEST(CustomRangeAlgorithms, repeat)
{
    int i = 1;
    auto f1 = [&i]() { return i += 2; };
    EXPECT_EQ(9, runInLoop(4, f1));
    EXPECT_EQ(9, i);

    i = 0;
    auto f2 = [&i](auto lhs, auto rhs) { return i += lhs + rhs; };
    EXPECT_EQ(15, runInLoop(3, f2, 2, 3));
    EXPECT_EQ(15, i);
}

TEST(CustomRangeAlgorithms, printIf)
{
    V v = {0, 1, 2, 3, 4};
    printIf(v, is_even);
    endl();
}
