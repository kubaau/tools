#include "ExtendedRangeStlAlgorithms.hpp"
#include "Contains.hpp"
#include "GtestWrapper.hpp"
#include "Numeric.hpp"

TEST(ExtendedRangeStlAlgorithms, transform_ret)
{
    V in{1, 2, 3, 3};
    auto multiply_by_2 = [](auto i) { return i * 2; };
    const auto out = transform<set<int>>(in, multiply_by_2);
    EXPECT_EQ((set<int>{2, 4, 6}), out);
}

TEST(ExtendedRangeStlAlgorithms, transform_ret_binary)
{
    V in1{1, 2, 3, 3};
    V in2{2, 3, 4, 4};
    auto add = [](auto lhs, auto rhs) { return lhs + rhs; };
    const auto out = transform<set<int>>(in1, in2, add);
    EXPECT_EQ((set<int>{3, 5, 7}), out);
}
TEST(ExtendedRangeStlAlgorithms, remove_copy_ret)
{
    V in{1, 2, 3, 2};
    V in_orig = in;
    EXPECT_EQ((V{1, 3}), remove_copy(in, 2));
    EXPECT_EQ(in_orig, in);
}

TEST(ExtendedRangeStlAlgorithms, remove_copy_if_ret)
{
    V in{1, 2, 3, 2};
    V in_orig = in;
    EXPECT_EQ((V{1, 3}), remove_copy_if(in, [](auto n) { return isEven(n); }));
    EXPECT_EQ(in_orig, in);
}

TEST(FrontTestSuite, front)
{
    EXPECT_EQ(2, front(array<int, 2>{2, 1}));

    EXPECT_EQ(2, front(deque<int>{2, 1}));

    EXPECT_EQ(2, front(forward_list<int>{2, 1}));

    EXPECT_EQ(2, front(list<int>{2, 1}));

    using P = map<int, int>::value_type;
    EXPECT_EQ((P{1, 0}), front(map<int, int>{{2, 0}, {1, 0}}));
    EXPECT_EQ((P{1, 0}), front(multimap<int, int>{{2, 0}, {1, 0}}));

    EXPECT_EQ(1, front(set<int>{2, 1}));
    EXPECT_EQ(1, front(multiset<int>{2, 1}));

    EXPECT_TRUE(contains({{2, 0}, {1, 0}}, front(unordered_map<int, int>{{2, 0}, {1, 0}})));
    EXPECT_TRUE(contains({{2, 0}, {1, 0}}, front(unordered_multimap<int, int>{{2, 0}, {1, 0}})));

    EXPECT_TRUE(contains({2, 1}, front(unordered_set<int>{2, 1})));
    EXPECT_TRUE(contains({2, 1}, front(unordered_multiset<int>{2, 1})));

    EXPECT_EQ(2, front(vector<int>{2, 1}));
}
