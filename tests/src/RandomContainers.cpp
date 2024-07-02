#include "RandomContainers.hpp"
#include "CustomRangeAlgorithms.hpp"
#include "GtestWrapper.hpp"

TEST(RandomContainers, fillWithRandomValues)
{
    Vd v(10);
    fillWithRandomValues(v, normal_distribution<>{5.0, 0.1});
    print(v);
}

TEST(RandomContainers, fillWithRandomInts)
{
    V v(10);
    fillWithRandomInts(v, -3, 7);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(v.front() >= -3);
    EXPECT_TRUE(v.back() <= 7);
}

TEST(RandomContainers, fillWithRandomInts_unsigned)
{
    Vu v(10);
    fillWithRandomInts(v, 3u, 7u);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(v.front() >= 3);
    EXPECT_TRUE(v.back() <= 7);
}

TEST(RandomContainers, fillWithRandomFloats_double)
{
    Vd v(10);
    fillWithRandomFloats(v, -3.14, 7.17);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(v.front() >= -3.14);
    EXPECT_TRUE(v.back() <= 7.17);
}

TEST(RandomContainers, fillWithRandomFloats_float)
{
    Vf v(10);
    fillWithRandomFloats(v, -3.14f, 7.17f);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(v.front() >= -3.14);
    EXPECT_TRUE(v.back() <= 7.17);
}

TEST(RandomContainers, fillWithRandomUniqueValues)
{
    V v(10);
    fillWithRandomUniqueValues(v, binomial_distribution<>{9, 0.5});
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= 0);
    EXPECT_TRUE(v.back() <= 9);
}

TEST(RandomContainers, fillWithRandomUniqueInts_largeWidth)
{
    V v(10);
    fillWithRandomUniqueInts(v, 0, 100);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= 0);
    EXPECT_TRUE(v.back() <= 100);
}

TEST(RandomContainers, fillWithRandomUniqueInts_smallWidth)
{
    V v(10);
    fillWithRandomUniqueInts(v, 0, 9);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= 0);
    EXPECT_TRUE(v.back() <= 9);
}

TEST(RandomContainers, fillWithRandomUniqueInts_largeWidth_unsigned)
{
    Vu v(10);
    fillWithRandomUniqueInts(v, 0u, 100u);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.back() <= 100);
}

TEST(RandomContainers, fillWithRandomUniqueInts_smallWidth_unsigned)
{
    Vu v(10);
    fillWithRandomUniqueInts(v, 0u, 9u);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.back() <= 9);
}

TEST(RandomContainers, fillWithRandomUniqueFloats_double)
{
    Vd v(10);
    fillWithRandomUniqueFloats(v, -3.14, 7.17);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= -3.14);
    EXPECT_TRUE(v.back() <= 7.17);
}

TEST(RandomContainers, fillWithRandomUniqueFloats_float)
{
    Vf v(10);
    fillWithRandomUniqueFloats(v, -3.14f, 7.17f);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= -3.14);
    EXPECT_TRUE(v.back() <= 7.17);
}

TEST(RandomContainers, randomInts)
{
    auto v = randomInts(-3, 7, 10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(v.front() >= -3);
    EXPECT_TRUE(v.back() <= 7);
}

TEST(RandomContainers, randomInts_unsigned)
{
    auto v = randomInts(3u, 7u, 10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(v.front() >= 3);
    EXPECT_TRUE(v.back() <= 7);
}

TEST(RandomContainers, randomUniqueInts)
{
    auto v = randomUniqueInts(-3, 7, 10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= -3);
    EXPECT_TRUE(v.back() <= 7);
}

TEST(RandomContainers, randomUniqueInts_unsigned)
{
    auto v = randomUniqueInts(3u, 12u, 10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= 3);
    EXPECT_TRUE(v.back() <= 12);
}

TEST(RandomContainers, randomFloats_double)
{
    auto v = randomFloats(-3.14, 7.17, 10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(v.front() >= -3.14);
    EXPECT_TRUE(v.back() <= 7.17);
}

TEST(RandomContainers, randomFloats_float)
{
    auto v = randomFloats(-3.14f, 7.17f, 10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(v.front() >= -3.14);
    EXPECT_TRUE(v.back() <= 7.17);
}

TEST(RandomContainers, randomUniqueFloats_double)
{
    auto v = randomUniqueFloats(-3.14, 7.17, 10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= -3.14);
    EXPECT_TRUE(v.back() <= 7.17);
}

TEST(RandomContainers, randomUniqueFloats_float)
{
    auto v = randomUniqueFloats(-3.14f, 7.17f, 10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_TRUE(v.front() >= -3.14);
    EXPECT_TRUE(v.back() <= 7.17);
}

TEST(RandomContainers, shuffledIndexes)
{
    auto v = shuffledIndexes(10, mt19937{random_device{}()});
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_EQ(0u, v.front());
    EXPECT_EQ(9u, v.back());
}

TEST(RandomContainers, shuffledIndexes_default)
{
    auto v = shuffledIndexes(10);
    print(v);

    sort(v);
    print(v);
    EXPECT_TRUE(allUnique(v));
    EXPECT_EQ(0u, v.front());
    EXPECT_EQ(9u, v.back());
}

TEST(RandomContainers, randomIndex)
{
    V v(10);
    const auto i = randomIndex(v, mt19937{random_device{}()});
    EXPECT_TRUE(i < 10);
}

TEST(RandomContainers, randomIndex_default)
{
    V v(10);
    const auto i = randomIndex(v);
    EXPECT_TRUE(i < 10);
}

TEST(RandomContainers, randomElement)
{
    V v{1, 2, 3};
    const auto elem = randomElement(v);
    EXPECT_TRUE(elem == 1 or elem == 2 or elem == 3);
}
