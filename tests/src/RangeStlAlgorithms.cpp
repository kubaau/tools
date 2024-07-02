#include "RangeStlAlgorithms.hpp"
#include "GtestWrapper.hpp"
#include "Numeric.hpp"

using TestValues = vector<V>;

static auto is_even = [] (auto n) { return isEven(n); };

TEST(RangeStlAlgorithms, all_of)
{
    const TestValues values = {
        {2, 4, 6},
        {2, 4, 5},
    };

    for (const auto& v : values)
        EXPECT_EQ(all_of(cbegin(v), cend(v), is_even), all_of(v, is_even));
}

TEST(RangeStlAlgorithms, any_of)
{
    const TestValues values = {
        {1, 3, 5},
        {1, 3, 4},
    };

    for (const auto& v : values)
        EXPECT_EQ(any_of(cbegin(v), cend(v), is_even), any_of(v, is_even));
}

TEST(RangeStlAlgorithms, none_of)
{
    const TestValues values = {
        {1, 3, 5},
        {1, 3, 4},
    };

    for (const auto& v : values)
        EXPECT_EQ(none_of(cbegin(v), cend(v), is_even), none_of(v, is_even));
}

TEST(RangeStlAlgorithms, for_each)
{
    const TestValues values = {
        {1, 3, 5},
    };

    int sum1 = 0;
    int sum2 = 0;
    auto add1 = [&sum1](auto n) { sum1 += n; };
    auto add2 = [&sum2](auto n) { sum2 += n; };

    for (const auto& v : values)
    {
        for_each(cbegin(v), cend(v), add1);
        for_each(v, add2);
        EXPECT_EQ(sum1, sum2);
    }
}

TEST(RangeStlAlgorithms, count)
{
    const TestValues values = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0},
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1},
    };

    for (const auto& v : values)
        EXPECT_EQ(count(cbegin(v), cend(v), 1), count(v, 1));
}

TEST(RangeStlAlgorithms, transform)
{
    V in{1, 2, 3, 3};
    auto multiply_by_2 = [](auto i) { return i * 2; };
    const auto out = transform(in, multiply_by_2);
    EXPECT_EQ((V{2, 4, 6, 6}), out);
}
