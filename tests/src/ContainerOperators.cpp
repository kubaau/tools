#include "ContainerOperators.hpp"
#include "GtestWrapper.hpp"

TEST(ContainerOperators, range_add_i)
{
    using namespace RangeOperators;

    EXPECT_EQ((V{1}), (V{} + 1));
    EXPECT_EQ((V{1, 1}), (V{1} + 1));
    EXPECT_EQ((V{1, 2}), (V{1} + 2));
    EXPECT_EQ((V{2, 1}), (V{2} + 1));
    EXPECT_EQ((V{1, 2, 3, 2}), (V{1, 2, 3} + 2));

    V v{1, 1, 1};
    EXPECT_EQ((V{1, 1, 1, 2}), v + 2);
    EXPECT_EQ((V{1, 1, 1}), v);
    EXPECT_EQ((V{1, 1, 1, 2, 1, 1, 1}), v + 2 + v);

    // VU vu;
    // Uncopyable u{1};
    // vu = move(vu) + move(u);
    // EXPECT_EQ(u.val, vu.back().val);
}

TEST(ContainerOperators, range_add_c)
{
    using namespace RangeOperators;

    EXPECT_EQ((V{}), (V{} + V{}));
    EXPECT_EQ((V{1}), (V{1} + V{}));
    EXPECT_EQ((V{1}), (V{} + V{1}));
    EXPECT_EQ((V{1, 2}), (V{1} + V{2}));
    EXPECT_EQ((V{2, 1}), (V{2} + V{1}));
    EXPECT_EQ((V{1, 2, 3, 1, 2, 3}), (V{1, 2, 3} + V{1, 2, 3}));

    V v{1, 1, 1};
    EXPECT_EQ((V{1, 1, 1, 1, 1, 1}), v + v);
    EXPECT_EQ((V{1, 1, 1}), v);
    EXPECT_EQ((V{1, 1, 1, 1, 1, 1, 1, 1, 1}), v + v + v);

    // VU vu1;
    // vu1.emplace_back(1);
    // VU vu2;
    // vu2.emplace_back(2);
    // vu2 = move(vu1) + move(vu2);
    // EXPECT_EQ((VU{Uncopyable{1}, Uncopyable{2}}), vu3);
}

TEST(ContainerOperators, range_append_i)
{
    using namespace RangeOperators;

    V v;
    EXPECT_EQ((V{1}), v += 1);
    v = {1};
    EXPECT_EQ((V{1, 1}), v += 1);
    v = {2};
    EXPECT_EQ((V{2, 1}), v += 1);
    v = {1, 2, 3};
    EXPECT_EQ((V{1, 2, 3, 1}), v += 1);

    v = {1, 1, 1};
    EXPECT_EQ((V{1, 1, 1, 2}), v += 2);
    EXPECT_EQ((V{1, 1, 1, 2}), v);
}

TEST(ContainerOperators, rangeAppendC)
{
    using namespace RangeOperators;

    V v;
    EXPECT_EQ((V{}), (v += V{}));
    v = {1};
    EXPECT_EQ((V{1}), (v += V{}));
    v = {};
    EXPECT_EQ((V{1}), (v += V{1}));
    v = {1};
    EXPECT_EQ((V{1, 2}), (v += V{2}));
    v = {2};
    EXPECT_EQ((V{2, 1}), (v += V{1}));
    v = {1, 2, 3};
    EXPECT_EQ((V{1, 2, 3, 1, 2, 3}), (v += V{1, 2, 3}));

    v = {1, 1, 1};
    EXPECT_EQ((V{1, 1, 1, 1, 1, 1}), v += V{v});
    EXPECT_EQ((V{1, 1, 1, 1, 1, 1}), v);
}

TEST(ContainerOperators, range_append_compose)
{
    using namespace RangeOperators;

    V v1{1, 2, 3};
    V v2{4, 5, 6};
    // v1 += ((v2 + 0) += 7) += V{};
    EXPECT_EQ((V{4, 5, 6}), v2);
    // EXPECT_EQ((V{1, 2, 3, 4, 5, 6, 0, 7}), v1);
}

TEST(ContainerOperators, range_subtract_i)
{
    using namespace RangeOperators;

    EXPECT_EQ((V{}), (V{} - 1));
    EXPECT_EQ((V{1}), (V{1} - 0));
    EXPECT_EQ((V{}), (V{1} - 1));
    EXPECT_EQ((V{1, 3}), (V{1, 2, 3} - 2));
    EXPECT_EQ((V{1, 3, 2}), (V{1, 2, 3, 2} - 2));

    V v{1, 2, 3};
    EXPECT_EQ((V{1, 3}), v - 2);
    EXPECT_EQ((V{1, 2, 3}), v);
}

TEST(ContainerOperators, range_subtract_c)
{
    using namespace RangeOperators;

    EXPECT_EQ((V{}), (V{} - V{}));
    EXPECT_EQ((V{1}), (V{1} - V{}));
    EXPECT_EQ((V{}), (V{} - V{1}));
    EXPECT_EQ((V{1}), (V{1} - V{2}));
    EXPECT_EQ((V{2}), (V{2} - V{1}));
    EXPECT_EQ((V{}), (V{1, 2, 3} - V{1, 2, 3}));
    EXPECT_EQ((V{2}), (V{1, 2, 3} - V{1, 3}));

    V v{1, 1, 1};
    EXPECT_EQ((V{}), v - v);
    EXPECT_EQ((V{1, 1, 1}), v);
    EXPECT_EQ((V{}), v - v - v);
}

TEST(ContainerOperators, range_remove_i)
{
    using namespace RangeOperators;

    V v;
    EXPECT_EQ((V{}), (v -= 1));
    v = {1};
    EXPECT_EQ((V{1}), (v -= 0));
    v = {1};
    EXPECT_EQ((V{}), (v -= 1));
    v = {1, 2, 3};
    EXPECT_EQ((V{1, 3}), (v -= 2));
    v = {1, 2, 3, 2};
    EXPECT_EQ((V{1, 3, 2}), (v -= 2));

    v = {1, 2, 3};
    EXPECT_EQ((V{1, 3}), v -= 2);
    EXPECT_EQ((V{1, 3}), v);
}

TEST(ContainerOperators, range_remove_c)
{
    using namespace RangeOperators;

    V v;
    EXPECT_EQ((V{}), (v -= V{}));
    v = {1};
    EXPECT_EQ((V{1}), (v -= V{}));
    v = {};
    EXPECT_EQ((V{}), (v -= V{1}));
    v = {1};
    EXPECT_EQ((V{1}), (v -= V{2}));
    v = {2};
    EXPECT_EQ((V{2}), (v -= V{1}));
    v = {1, 2, 3};
    EXPECT_EQ((V{}), (v -= V{1, 2, 3}));
    v = {1, 2, 3};
    EXPECT_EQ((V{2}), (v -= V{1, 3}));

    v = {1, 2, 3};
    EXPECT_EQ((V{}), v -= V{v});
    EXPECT_EQ((V{}), v);
}

TEST(ContainerOperators, range_remove_compose)
{
    using namespace RangeOperators;

    V v1{1, 2, 3};
    V v2 = v1;
    // v1 -= ((v2 - 2) -= 1) -= V{};
    EXPECT_EQ((V{1, 2, 3}), v2);
    // EXPECT_EQ((V{1, 2}), v1);
}

TEST(ContainerOperators, range_and)
{
    using namespace RangeOperators;

    EXPECT_EQ((V{}), (V{} & V{}));
    EXPECT_EQ((V{}), (V{1} & V{}));
    EXPECT_EQ((V{}), (V{} & V{1}));
    EXPECT_EQ((V{}), (V{1} & V{2}));
    EXPECT_EQ((V{}), (V{2} & V{1}));
    EXPECT_EQ((V{1}), (V{1} & V{1}));
    EXPECT_EQ((V{1}), (V{1} & V{1, 2}));
    EXPECT_EQ((V{1}), (V{1} & V{1, 1}));
    EXPECT_EQ((V{1, 2, 3}), (V{1, 2, 3} & V{1, 2, 3}));
    EXPECT_EQ((V{1, 3}), (V{1, 2, 3} & V{1, 3}));

    V v{1, 2, 3};
    EXPECT_EQ(v, v & v);
    EXPECT_EQ((V{1, 2, 3}), v);
}

TEST(ContainerOperators, range_and_eq)
{
    using namespace RangeOperators;

    V v;
    EXPECT_EQ((V{}), (v &= V{}));
    v = {1};
    EXPECT_EQ((V{}), (v &= V{}));
    v = {};
    EXPECT_EQ((V{}), (v &= V{1}));
    v = {1};
    EXPECT_EQ((V{}), (v &= V{2}));
    v = {2};
    EXPECT_EQ((V{}), (v &= V{1}));
    v = {1};
    EXPECT_EQ((V{1}), (v &= V{1}));
    v = {1};
    EXPECT_EQ((V{1}), (v &= V{1, 2}));
    v = {1};
    EXPECT_EQ((V{1}), (v &= V{1, 1}));
    v = {1, 2, 3};
    EXPECT_EQ((V{1, 2, 3}), (v &= V{1, 2, 3}));
    v = {1, 2, 3};
    EXPECT_EQ((V{1, 3}), (v &= V{1, 3}));

    v = {1, 2, 3};
    EXPECT_EQ(v, v & v);
    EXPECT_EQ((V{1, 2, 3}), v);
}

TEST(ContainerOperators, range_and_compose)
{
    using namespace RangeOperators;

    V v1{1, 2, 3};
    V v2 = v1;
    v1 &= (v2 & V{1, 3}) &= V{2, 3};
    EXPECT_EQ((V{1, 2, 3}), v2);
    EXPECT_EQ((V{3}), v1);
}

TEST(ContainerOperators, range_or)
{
    using namespace RangeOperators;

    EXPECT_EQ((V{}), (V{} | V{}));
    EXPECT_EQ((V{1}), (V{1} | V{}));
    EXPECT_EQ((V{1}), (V{} | V{1}));
    EXPECT_EQ((V{1, 2}), (V{1} | V{2}));
    EXPECT_EQ((V{1, 2}), (V{2} | V{1}));
    EXPECT_EQ((V{1, 2, 3}), (V{2, 3} | V{1, 3}));
    EXPECT_EQ((V{1}), (V{1} | V{1}));
    EXPECT_EQ((V{1, 2}), (V{1} | V{1, 2}));
    EXPECT_EQ((V{1, 1}), (V{1} | V{1, 1}));
    EXPECT_EQ((V{1, 2, 3}), (V{1, 2, 3} | V{1, 2, 3}));
    EXPECT_EQ((V{1, 2, 3}), (V{1, 2, 3} | V{1, 3}));
    EXPECT_EQ((V{1, 2, 2, 2, 2, 3}), (V{1, 2, 2, 3} | V{1, 2, 2, 2, 2}));

    V v{1, 2, 3};
    EXPECT_EQ(v, v | v);
    EXPECT_EQ((V{1, 2, 3}), v);
}

TEST(ContainerOperators, range_or_eq)
{
    using namespace RangeOperators;

    V v;
    EXPECT_EQ((V{}), (v |= V{}));
    v = {1};
    EXPECT_EQ((V{1}), (v |= V{}));
    v = {};
    EXPECT_EQ((V{1}), (v |= V{1}));
    v = {1};
    EXPECT_EQ((V{1, 2}), (v |= V{2}));
    v = {2};
    EXPECT_EQ((V{1, 2}), (v |= V{1}));
    v = {2, 3};
    EXPECT_EQ((V{1, 2, 3}), (v |= V{1, 3}));
    v = {1};
    EXPECT_EQ((V{1}), (v |= V{1}));
    v = {1};
    EXPECT_EQ((V{1, 2}), (v |= V{1, 2}));
    v = {1};
    EXPECT_EQ((V{1, 1}), (v |= V{1, 1}));
    v = {1, 2, 3};
    EXPECT_EQ((V{1, 2, 3}), (v |= V{1, 2, 3}));
    v = {1, 2, 3};
    EXPECT_EQ((V{1, 2, 3}), (v |= V{1, 3}));
    v = {1, 2, 2, 3};
    EXPECT_EQ((V{1, 2, 2, 2, 2, 3}), (v |= V{1, 2, 2, 2, 2}));

    v = {1, 2, 3};
    EXPECT_EQ(v, v |= v);
    EXPECT_EQ((V{1, 2, 3}), v);
}

TEST(ContainerOperators, range_or_compose)
{
    using namespace RangeOperators;

    V v1{1, 2, 3};
    V v2 = v1;
    v1 |= (v2 | V{3, 4}) |= V{1, 3, 4, 5};
    EXPECT_EQ((V{1, 2, 3}), v2);
    EXPECT_EQ((V{1, 2, 3, 4, 5}), v1);
}

TEST(ContainerOperators, range_xor)
{
    using namespace RangeOperators;

    EXPECT_EQ((V{}), (V{} ^ V{}));
    EXPECT_EQ((V{1}), (V{1} ^ V{}));
    EXPECT_EQ((V{1}), (V{} ^ V{1}));
    EXPECT_EQ((V{1, 2}), (V{1} ^ V{2}));
    EXPECT_EQ((V{1, 2}), (V{2} ^ V{1}));
    EXPECT_EQ((V{1, 2}), (V{2, 3} ^ V{1, 3}));
    EXPECT_EQ((V{}), (V{1} ^ V{1}));
    EXPECT_EQ((V{2}), (V{1} ^ V{1, 2}));
    EXPECT_EQ((V{1}), (V{1} ^ V{1, 1}));
    EXPECT_EQ((V{}), (V{1, 2, 3} ^ V{1, 2, 3}));
    EXPECT_EQ((V{2}), (V{1, 2, 3} ^ V{1, 3}));
    EXPECT_EQ((V{2, 2, 3}), (V{1, 2, 2, 3} ^ V{1, 2, 2, 2, 2}));

    V v{1, 2, 3};
    EXPECT_EQ((V{}), v ^ v);
    EXPECT_EQ((V{1, 2, 3}), v);
}

TEST(ContainerOperators, range_xor_eq)
{
    using namespace RangeOperators;

    V v;
    EXPECT_EQ((V{}), (v ^= V{}));
    v = {1};
    EXPECT_EQ((V{1}), (v ^= V{}));
    v = {};
    EXPECT_EQ((V{1}), (v ^= V{1}));
    v = {1};
    EXPECT_EQ((V{1, 2}), (v ^= V{2}));
    v = {2};
    EXPECT_EQ((V{1, 2}), (v ^= V{1}));
    v = {2, 3};
    EXPECT_EQ((V{1, 2}), (v ^= V{1, 3}));
    v = {1};
    EXPECT_EQ((V{}), (v ^= V{1}));
    v = {1};
    EXPECT_EQ((V{2}), (v ^= V{1, 2}));
    v = {1};
    EXPECT_EQ((V{1}), (v ^= V{1, 1}));
    v = {1, 2, 3};
    EXPECT_EQ((V{}), (v ^= V{1, 2, 3}));
    v = {1, 2, 3};
    EXPECT_EQ((V{2}), (v ^= V{1, 3}));
    v = {1, 2, 2, 3};
    EXPECT_EQ((V{2, 2, 3}), (v ^= V{1, 2, 2, 2, 2}));

    v = {1, 2, 3};
    EXPECT_EQ((V{}), v ^= v);
    EXPECT_EQ((V{}), v);
}

TEST(ContainerOperators, range_xor_compose)
{
    using namespace RangeOperators;

    V v1{1, 2, 3};
    V v2 = v1;
    v1 ^= (v2 ^ V{3, 4}) ^= V{1, 3, 4, 5};
    EXPECT_EQ((V{1, 2, 3}), v2);
    EXPECT_EQ((V{1, 5}), v1);
}

TEST(ContainerOperators, pairwise_append_c)
{
    using namespace PairwiseOperators;

    V v;
    EXPECT_EQ((V{}), (v += V{}));
    v = {1};
    EXPECT_EQ((V{1}), (v += V{}));
    v = {};
    EXPECT_EQ((V{1}), (v += V{1}));
    v = {1};
    EXPECT_EQ((V{3}), (v += V{2}));
    v = {2};
    EXPECT_EQ((V{3}), (v += V{1}));
    v = {1, 2, 3};
    EXPECT_EQ((V{2, 4, 6}), (v += V{1, 2, 3}));

    v = {1, 1, 1};
    EXPECT_EQ((V{2, 2, 2}), v += V{v});
    EXPECT_EQ((V{2, 2, 2}), v);
}

TEST(ContainerOperators, pairwise_append_compose)
{
    using namespace PairwiseOperators;

    V v1{1, 2, 3};
    V v2{4, 5, 6};
    v1 += v2 += V{3, 5, 8, 13} += V{-1, -2, -3};
    EXPECT_EQ((V{6, 8, 11, 13}), v2);
    EXPECT_EQ((V{7, 10, 14, 13}), v1);
}
