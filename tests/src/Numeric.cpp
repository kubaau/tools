#include "Numeric.hpp"
#include "ContainerFilter.hpp"
#include "Contains.hpp"
#include "GtestWrapper.hpp"

TEST(Numeric, factorial)
{
    EXPECT_EQ(1u, factorial(0));
    EXPECT_EQ(1u, factorial(1));
    EXPECT_EQ(2u, factorial(2));
    EXPECT_EQ(120u, factorial(5));
}

TEST(Numeric, isOdd)
{
    EXPECT_FALSE(isOdd(0));
    EXPECT_TRUE(isOdd(1));
    EXPECT_FALSE(isOdd(2));
    EXPECT_TRUE(isOdd(3));
}

TEST(Numeric, isEven)
{
    EXPECT_TRUE(isEven(0));
    EXPECT_FALSE(isEven(1));
    EXPECT_TRUE(isEven(2));
    EXPECT_FALSE(isEven(3));
}

TEST(Numeric, powerN)
{
    EXPECT_EQ(1, powerN(0, 0));
    EXPECT_EQ(0, powerN(0, 1));
    EXPECT_EQ(1, powerN(1, 0));
    EXPECT_EQ(1, powerN(1, 1));
    EXPECT_EQ(1, powerN(1, 2));
    EXPECT_EQ(1, powerN(2, 0));
    EXPECT_EQ(2, powerN(2, 1));
    EXPECT_EQ(4, powerN(2, 2));
    EXPECT_EQ(8, powerN(2, 3));
    EXPECT_EQ(27, powerN(3, 3));
}

TEST(Numeric, powerLogN)
{
    EXPECT_EQ(1, powerLogN(0, 0));
    EXPECT_EQ(0, powerLogN(0, 1));
    EXPECT_EQ(1, powerLogN(1, 0));
    EXPECT_EQ(1, powerLogN(1, 1));
    EXPECT_EQ(1, powerLogN(1, 2));
    EXPECT_EQ(1, powerLogN(2, 0));
    EXPECT_EQ(2, powerLogN(2, 1));
    EXPECT_EQ(4, powerLogN(2, 2));
    EXPECT_EQ(8, powerLogN(2, 3));
    EXPECT_EQ(27, powerLogN(3, 3));
}

TEST(Numeric, primeSieve)
{
    const auto s0 = primeSieve<0>();
    EXPECT_EQ((bitset<1>{false}), s0);

    const auto s10 = primeSieve<10>();
    EXPECT_FALSE(s10[0]);
    EXPECT_FALSE(s10[1]);
    EXPECT_TRUE(s10[2]);
    EXPECT_TRUE(s10[3]);
    EXPECT_FALSE(s10[4]);
    EXPECT_TRUE(s10[5]);
    EXPECT_FALSE(s10[6]);
    EXPECT_TRUE(s10[7]);
    EXPECT_FALSE(s10[8]);
    EXPECT_FALSE(s10[9]);
    EXPECT_FALSE(s10[10]);
}

TEST(Numeric, primesUpTo)
{
    const auto p0 = primesUpTo<0>();
    EXPECT_TRUE(p0.empty());

    const auto p1 = primesUpTo<1>();
    EXPECT_TRUE(p1.empty());

    EXPECT_EQ((vector<unsigned>{2}), primesUpTo<2>());
    EXPECT_EQ((vector<unsigned>{2, 3}), primesUpTo<3>());
    EXPECT_EQ((vector<unsigned>{2, 3, 5, 7}), primesUpTo<10>());
    EXPECT_EQ((vector<int>{2, 3, 5, 7}), (primesUpTo<10, int>()));
}

TEST(Numeric, powerSet)
{
    const auto ps0 = powerSet(S{});
    EXPECT_EQ(1u, ps0.size());
    EXPECT_TRUE(contains(ps0, (S{})));

    const auto ps1 = powerSet(S{1});
    EXPECT_EQ(2u, ps1.size());
    EXPECT_TRUE(contains(ps1, (S{})));
    EXPECT_TRUE(contains(ps1, (S{1})));

    const auto ps2 = powerSet(S{1, 2});
    EXPECT_EQ(4u, ps2.size());
    EXPECT_TRUE(contains(ps2, (S{})));
    EXPECT_TRUE(contains(ps2, (S{1})));
    EXPECT_TRUE(contains(ps2, (S{2})));
    EXPECT_TRUE(contains(ps2, (S{1, 2})));

    const auto ps3 = powerSet(S{1, 2, 3});
    EXPECT_EQ(8u, ps3.size());
    EXPECT_TRUE(contains(ps3, (S{})));
    EXPECT_TRUE(contains(ps3, (S{1})));
    EXPECT_TRUE(contains(ps3, (S{2})));
    EXPECT_TRUE(contains(ps3, (S{3})));
    EXPECT_TRUE(contains(ps3, (S{1, 2})));
    EXPECT_TRUE(contains(ps3, (S{1, 3})));
    EXPECT_TRUE(contains(ps3, (S{2, 3})));
    EXPECT_TRUE(contains(ps3, (S{1, 2, 3})));

    EXPECT_EQ(ps0, powerSet2(S{}));
    EXPECT_EQ(ps1, powerSet2(S{1}));
    EXPECT_EQ(ps2, powerSet2(S{1, 2}));
    EXPECT_EQ(ps3, powerSet2(S{1, 2, 3}));

    EXPECT_EQ(ps0, powerSet3(S{}));
    EXPECT_EQ(ps1, powerSet3(S{1}));
    EXPECT_EQ(ps2, powerSet3(S{1, 2}));
    EXPECT_EQ(ps3, powerSet3(S{1, 2, 3}));
}

TEST(Numeric, gcd)
{
    EXPECT_EQ(0, gcd(0, 0));
    EXPECT_EQ(5, gcd(0, 5));
    EXPECT_EQ(5, gcd(5, 0));
    EXPECT_EQ(1, gcd(1, 1));
    EXPECT_EQ(1, gcd(1, 5));
    EXPECT_EQ(1, gcd(5, 1));
    EXPECT_EQ(3, gcd(3, 6));
    EXPECT_EQ(3, gcd(6, 3));
    EXPECT_EQ(5, gcd(15, 25));
    EXPECT_EQ(5, gcd(25, 15));
}

TEST(Numeric, lcm)
{
    EXPECT_EQ(0, lcm(0, 0));
    EXPECT_EQ(0, lcm(0, 5));
    EXPECT_EQ(0, lcm(5, 0));
    EXPECT_EQ(1, lcm(1, 1));
    EXPECT_EQ(5, lcm(1, 5));
    EXPECT_EQ(5, lcm(5, 1));
    EXPECT_EQ(6, lcm(3, 6));
    EXPECT_EQ(6, lcm(6, 3));
    EXPECT_EQ(75, lcm(15, 25));
    EXPECT_EQ(75, lcm(25, 15));
}

TEST(Numeric, addFractions)
{
    EXPECT_EQ(make_pair(0, 0), addFractions(0, 0, 0, 0));
    EXPECT_EQ(make_pair(0, 0), addFractions(0, 0, 0, 1));
    EXPECT_EQ(make_pair(0, 0), addFractions(1, 1, 1, 0));
    EXPECT_EQ(make_pair(2, 1), addFractions(1, 1, 1, 1));
    EXPECT_EQ(make_pair(1, 1), addFractions(1, 2, 1, 2));
    EXPECT_EQ(make_pair(5, 6), addFractions(1, 3, 1, 2));
    EXPECT_EQ(make_pair(1, 2), addFractions(1, 4, 1, 4));
    EXPECT_EQ(make_pair(1, 1), addFractions(1, 4, 3, 4));
    EXPECT_EQ(make_pair(7, 4), addFractions(1, 4, 3, 2));

    EXPECT_EQ(make_pair(0, 0), addFractions(make_pair(0, 0), make_pair(0, 0)));
    EXPECT_EQ(make_pair(0, 0), addFractions(make_pair(0, 0), make_pair(0, 1)));
    EXPECT_EQ(make_pair(0, 0), addFractions(make_pair(1, 1), make_pair(1, 0)));
    EXPECT_EQ(make_pair(2, 1), addFractions(make_pair(1, 1), make_pair(1, 1)));
    EXPECT_EQ(make_pair(1, 1), addFractions(make_pair(1, 2), make_pair(1, 2)));
    EXPECT_EQ(make_pair(5, 6), addFractions(make_pair(1, 3), make_pair(1, 2)));
    EXPECT_EQ(make_pair(1, 2), addFractions(make_pair(1, 4), make_pair(1, 4)));
    EXPECT_EQ(make_pair(1, 1), addFractions(make_pair(1, 4), make_pair(3, 4)));
    EXPECT_EQ(make_pair(7, 4), addFractions(make_pair(1, 4), make_pair(3, 2)));
}

TEST(Numeric, fibAdd)
{
    int a = 1, b = 1;
    fibAdd(a, b);
    EXPECT_EQ(1, a);
    EXPECT_EQ(2, b);
    fibAdd(a, b);
    fibAdd(a, b);
    fibAdd(a, b);
    fibAdd(a, b);
    EXPECT_EQ(8, a);
    EXPECT_EQ(13, b);
    fibAdd(a, b);
    EXPECT_EQ(13, a);
    EXPECT_EQ(21, b);
}

TEST(Numeric, fibs)
{
    EXPECT_EQ((Vu{}), fibs(0));
    EXPECT_EQ((Vu{1}), fibs(1));
    EXPECT_EQ((Vu{1, 1}), fibs(2));
    EXPECT_EQ((Vu{1, 1, 2}), fibs(3));
    EXPECT_EQ((Vu{1, 1, 2, 3, 5, 8, 13}), fibs(7));
}

TEST(Numeric, fib)
{
    EXPECT_EQ(0u, fib(0));
    EXPECT_EQ(1u, fib(1));
    EXPECT_EQ(1u, fib(2));
    EXPECT_EQ(2u, fib(3));
    EXPECT_EQ(13u, fib(7));
}

TEST(Numeric, eq_float)
{
    float f = 0.0f;
    EXPECT_TRUE(eq(f, 0.0f));
    EXPECT_FALSE(eq(f, 0.0f + numeric_limits<float>::epsilon()));
    EXPECT_FALSE(eq(f, 0.0f - numeric_limits<float>::epsilon()));
    f = 3.14f;
    EXPECT_TRUE(eq(f, 3.14f));
    EXPECT_FALSE(eq(f, 3.14f + numeric_limits<float>::epsilon()));
    EXPECT_FALSE(eq(f, 3.14f - numeric_limits<float>::epsilon()));

    double d = 0.0;
    EXPECT_TRUE(eq(d, 0.0));
    EXPECT_FALSE(eq(d, 0.0 + numeric_limits<double>::epsilon()));
    EXPECT_FALSE(eq(d, 0.0 - numeric_limits<double>::epsilon()));
    d = 3.14;
    EXPECT_TRUE(eq(d, 3.14));
    EXPECT_FALSE(eq(d, 3.14 + numeric_limits<double>::epsilon()));
    EXPECT_FALSE(eq(d, 3.14 - numeric_limits<double>::epsilon()));
}

TEST(Numeric, mod)
{
    EXPECT_EQ(0u, mod(1, 1));
    EXPECT_EQ(1u, mod(1, 2));

    EXPECT_EQ(2u, mod(8, 3));
    EXPECT_EQ(1u, mod(-8, 3));
    EXPECT_EQ(2u, mod(8, -3));
    EXPECT_EQ(1u, mod(-8, -3));

    EXPECT_EQ(0u, mod(8, 4));
    EXPECT_EQ(0u, mod(-8, 4));
    EXPECT_EQ(0u, mod(8, -4));
    EXPECT_EQ(0u, mod(-8, -4));
}

TEST(Numeric, avg_it_container)
{
    V v = {};
    EXPECT_EQ(0, avg(cbegin(v), cend(v)));
    EXPECT_EQ(0, avg(v));

    v = {1};
    EXPECT_EQ(1, avg(cbegin(v), cend(v)));
    EXPECT_EQ(1, avg(v));

    v = {1, 2};
    EXPECT_EQ(1.5, avg(cbegin(v), cend(v)));
    EXPECT_EQ(1.5, avg(v));

    v = {3, 1, 3, 3, 7};
    EXPECT_EQ(3.4, avg(cbegin(v), cend(v)));
    EXPECT_EQ(3.4, avg(v));

    v = {-3, 1, -3, 3, -7};
    EXPECT_EQ(-1.8, avg(cbegin(v), cend(v)));
    EXPECT_EQ(-1.8, avg(v));

    EXPECT_EQ(-1, avg<int>(cbegin(v), cend(v)));
    EXPECT_EQ(-1, avg<int>(v));

    vector<double> vd = {-3.1, 1.2, -3.3, 3.4, -7.5};
    EXPECT_EQ(-1.86, avg(cbegin(vd), cend(vd)));
    EXPECT_EQ(-1.86, avg(vd));
}

TEST(Numeric, avg_initializer_list)
{
    EXPECT_EQ(0, avg(initializer_list<int>{}));
    EXPECT_EQ(1, avg({1}));
    EXPECT_EQ(1.5, avg({1, 2}));
    EXPECT_EQ(3.4, avg({3, 1, 3, 3, 7}));
    EXPECT_EQ(-1.8, avg({-3, 1, -3, 3, -7}));
    EXPECT_EQ(-1, avg<int>({-3, 1, -3, 3, -7}));
    EXPECT_EQ(-1.86, avg({-3.1, 1.2, -3.3, 3.4, -7.5}));
}

TEST(Numeric, pows)
{
    EXPECT_EQ((V{1}), pows(0, 0));
    EXPECT_EQ((V{1, 0}), pows(0, 1));
    EXPECT_EQ((V{1, 0, 0, 0}), pows(0, 3));
    EXPECT_EQ((V{1}), pows(1, 0));
    EXPECT_EQ((V{1, 1}), pows(1, 1));
    EXPECT_EQ((V{1, 1, 1, 1}), pows(1, 3));
    EXPECT_EQ((V{1}), pows(2, 0));
    EXPECT_EQ((V{1, 2}), pows(2, 1));
    EXPECT_EQ((V{1, 2, 4, 8}), pows(2, 3));
}

TEST(Numeric, maxNoIf)
{
    EXPECT_EQ(0, maxNoIf(0, 0));
    EXPECT_EQ(-1, maxNoIf(-1, -1));
    EXPECT_EQ(5, maxNoIf(3, 5));
    EXPECT_EQ(5, maxNoIf(5, 3));
    EXPECT_EQ(3, maxNoIf(3, -5));
    EXPECT_EQ(3, maxNoIf(-5, 3));
    EXPECT_EQ(-3, maxNoIf(-5, -3));
}

namespace
{
    constexpr auto minus_1 = static_cast<unsigned>(-1);
    constexpr auto minus_3 = static_cast<unsigned>(-3);
    constexpr auto minus_5 = static_cast<unsigned>(-5);
}

TEST(Numeric, maxArr)
{
    EXPECT_EQ(0u, maxArr(0u, 0u));
    EXPECT_EQ(minus_1, maxArr(minus_1, minus_1));
    EXPECT_EQ(5u, maxArr(3u, 5u));
    EXPECT_EQ(5u, maxArr(5u, 3u));
    EXPECT_EQ(minus_5, maxArr(3u, minus_5));
    EXPECT_EQ(minus_5, maxArr(minus_5, 3u));
    EXPECT_EQ(minus_3, maxArr(minus_5, minus_3));
}

TEST(Numeric, minArr)
{
    EXPECT_EQ(0u, minArr(0u, 0u));
    EXPECT_EQ(minus_1, minArr(minus_1, minus_1));
    EXPECT_EQ(3u, minArr(3u, 5u));
    EXPECT_EQ(3u, minArr(5u, 3u));
    EXPECT_EQ(3u, minArr(3u, minus_5));
    EXPECT_EQ(3u, minArr(minus_5, 3u));
    EXPECT_EQ(minus_5, minArr(minus_5, minus_3));
}

TEST(Numeric, domainExcept)
{
    vector<u8> all(numeric_limits<u8>::max());
    iota(all);
    const auto odd = filter(all, [](auto n) { return isOdd(n); });
    const auto even = filter(all, [](auto n) { return isEven(n); });

    EXPECT_EQ(even, domainExcept(odd));
}
