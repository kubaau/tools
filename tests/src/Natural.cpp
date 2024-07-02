#include "Natural.hpp"
#include "GtestWrapper.hpp"

TEST(Natural, isZeroByDefault)
{
    EXPECT_EQ(0, Natural{});
}

TEST(Natural, cannotBeCreatedWithNegativeValue)
{
    EXPECT_THROW(Natural{-1}, range_error);
    EXPECT_THROW(Natural{1 << 31}, range_error);
}

TEST(Natural, canBeCreatedWithNonNegativeValue)
{
    EXPECT_NO_THROW(Natural{0});
    EXPECT_NO_THROW(Natural{1});
}

TEST(Natural, negativeValueCannotBeAssigned)
{
    Natural n = 2;
    EXPECT_THROW(n = -1, range_error);
}

TEST(Natural, nonNegativeValueCanBeAssigned)
{
    Natural n;
    EXPECT_NO_THROW(n = 0);
    EXPECT_NO_THROW(n = 1);
    EXPECT_NO_THROW(n = Natural{2});
}

void f1(int) {}
TEST(Natural, castsToInt)
{
    f1(Natural{});
}

void f2(unsigned) {}
TEST(Natural, castsToUnsigned)
{
    f2(Natural{});
}

constexpr Natural n3 = 3;

TEST(Natural, canBeComparedToInt)
{
    EXPECT_EQ(3, n3);
    EXPECT_EQ(n3, 3);

    EXPECT_NE(4, n3);
    EXPECT_NE(n3, 4);

    EXPECT_LT(2, n3);
    EXPECT_LT(n3, 4);
    EXPECT_FALSE(3 < n3 or n3 < 3);

    EXPECT_GT(4, n3);
    EXPECT_GT(n3, 2);
    EXPECT_FALSE(3 > n3 or n3 > 3);

    EXPECT_LE(2, n3);
    EXPECT_LE(n3, 4);
    EXPECT_TRUE(3 <= n3 and n3 <= 3);

    EXPECT_GE(4, n3);
    EXPECT_GE(n3, 2);
    EXPECT_TRUE(3 >= n3 and n3 >= 3);
}

TEST(Natural, canBeComparedToUnsigned)
{
    EXPECT_EQ(3u, static_cast<unsigned>(n3));
    EXPECT_EQ(n3, 3u);

    EXPECT_NE(4u, n3);
    EXPECT_NE(n3, 4u);

    EXPECT_LT(2u, n3);
    EXPECT_LT(n3, 4u);
    EXPECT_FALSE(3u < n3 or n3 < 3u);

    EXPECT_GT(4u, n3);
    EXPECT_GT(n3, 2u);
    EXPECT_FALSE(3u > n3 or n3 > 3u);

    EXPECT_LE(2u, n3);
    EXPECT_LE(n3, 4u);
    EXPECT_TRUE(3u <= n3 and n3 <= 3u);

    EXPECT_GE(4u, n3);
    EXPECT_GE(n3, 2u);
    EXPECT_TRUE(3u >= n3 and n3 >= 3u);
}

TEST(Natural, canBeComparedToItself)
{
    Natural n4 = 4;
    EXPECT_EQ(n3, n3);
    EXPECT_NE(n3, n4);
    EXPECT_LT(n3, n4);
    EXPECT_GT(n4, n3);
    EXPECT_LE(n3, n4);
    EXPECT_GE(n4, n3);
}

constexpr auto max_int = numeric_limits<int>::max();

TEST(Natural, canBeCompared64bitIntegers)
{
    EXPECT_EQ(Natural{max_int}, i64{max_int});
    EXPECT_NE(Natural{max_int}, i64{max_int | 0x100000000});
    EXPECT_EQ(i64{max_int}, Natural{max_int});
    EXPECT_NE(i64{max_int | 0x100000000}, Natural{max_int});

    EXPECT_EQ(Natural{max_int}, u64{max_int});
    EXPECT_NE(Natural{max_int}, u64{max_int | 0x100000000});
    EXPECT_EQ(u64{max_int}, Natural{max_int});
    EXPECT_NE(u64{max_int | 0x100000000}, Natural{max_int});
}

TEST(Natural, additionAssignmentWorksAsExpected)
{
    Natural n = 1;
    int i = 2;
    unsigned u = 3;

    n += i;
    EXPECT_EQ(3, n);
    n += n += u;
    EXPECT_EQ(12, n);
}

TEST(Natural, additionAssignmentCannotResultInNegativeValue)
{
    EXPECT_THROW(Natural{} += -1, range_error);
    EXPECT_THROW(Natural{max_int} += 1, range_error);
}

TEST(Natural, subtractionAssignmentWorksAsExpected)
{
    Natural n = 20;
    int i = 10;
    unsigned u = 5;

    n -= i;
    EXPECT_EQ(10, n);
    n -= n -= u;
    EXPECT_EQ(0, n);
}

TEST(Natural, subtractionAssignmentCannotResultInNegativeValue)
{
    EXPECT_THROW(Natural{} -= 1, range_error);
}

TEST(Natural, multiplicationAssignmentWorksAsExpected)
{
    Natural n = 1;
    int i = 2;
    unsigned u = 3;

    n *= i;
    EXPECT_EQ(2, n);
    n *= n *= u;
    EXPECT_EQ(36, n);
}

TEST(Natural, multiplicationAssignmentCannotResultInNegativeValue)
{
    EXPECT_THROW(Natural{1} *= -1, range_error);
}

TEST(Natural, divisionAssignmentWorksAsExpected)
{
    Natural n = 6;
    int i = 2;
    unsigned u = 2;

    n /= i;
    EXPECT_EQ(3, n);
    n /= n /= u;
    EXPECT_EQ(1, n);
}

TEST(Natural, divisionAssignmentCannotResultInNegativeValue)
{
    EXPECT_THROW(Natural{1} /= -1, range_error);
}

TEST(Natural, moduloAssignmentWorksAsExpected)
{
    Natural n = 11;
    int i = 6;
    unsigned u = 2;

    n %= i;
    EXPECT_EQ(5, n);
    n %= n %= u;
    EXPECT_EQ(0, n);
}

TEST(Natural, moduloAssignmentCannotResultInNegativeValue)
{
    EXPECT_NO_THROW(Natural{2} %= -1);
    EXPECT_NO_THROW(Natural{2} %= -3);
}

TEST(Natural, bitwiseAndAssignmentWorksAsExpected)
{
    Natural n = 0xFFFF;
    int i = 0xF0F0;
    unsigned u = 0xAAAA;

    n &= i;
    EXPECT_EQ(0xF0F0, n);
    n &= n &= u;
    EXPECT_EQ(0xA0A0, n);
}

TEST(Natural, bitwiseAndAssignmentCannotResultInNegativeValue)
{
    EXPECT_NO_THROW(Natural{0x7FFFFFFF} &= -1);
}

TEST(Natural, bitwiseOrAssignmentWorksAsExpected)
{
    Natural n = 0xF0F0;
    int i = 0x0F00;
    unsigned u = 0x012A;

    n |= i;
    EXPECT_EQ(0xFFF0, n);
    n |= n |= u;
    EXPECT_EQ(0XFFFA, n);
}

TEST(Natural, bitwiseOrAssignmentCannotResultInNegativeValue)
{
    EXPECT_THROW(Natural{} |= 0xF0000000, range_error);
}

TEST(Natural, shiftLeftAssignmentWorksAsExpected)
{
    Natural n = 1;
    int i = 1;
    unsigned u = 1;

    n <<= i;
    EXPECT_EQ(2, n);
    n <<= n <<= u;
    EXPECT_EQ(64, n);
}

TEST(Natural, shiftLeftAssignmentCannotResultInNegativeValue)
{
    EXPECT_THROW(Natural{1} <<= 31, range_error);
}

TEST(Natural, shiftRightAssignmentWorksAsExpected)
{
    Natural n = 4;
    int i = 1;
    unsigned u = 1;

    n >>= i;
    EXPECT_EQ(2, n);
    n >>= n >>= u;
    EXPECT_EQ(0, n);
}

TEST(Natural, shiftRightAssignmentCannotResultInNegativeValue)
{
    EXPECT_NO_THROW(Natural{1} >>= 1);
}

TEST(Natural, preincrementationWorksAsExpected)
{
    Natural n = 1;
    EXPECT_EQ(2, ++n);
    EXPECT_EQ(2, n);
}

/* does not work on clang ???
TEST(Natural, preincrementationCannotResultInNegativeValue)
{
    Natural n = max_int;
    EXPECT_THROW(++n, range_error);
}
*/

TEST(Natural, postincrementationWorksAsExpected)
{
    Natural n = 1;
    EXPECT_EQ(1, n++);
    EXPECT_EQ(2, n);
}

/* does not work on clang ???
TEST(Natural, postincrementationCannotResultInNegativeValue)
{
    Natural n = max_int;
    EXPECT_THROW(n++, range_error);
}
*/

TEST(Natural, predecrementationWorksAsExpected)
{
    Natural n = 1;
    EXPECT_EQ(0, --n);
    EXPECT_EQ(0, n);
}

TEST(Natural, predecrementationCannotResultInNegativeValue)
{
    Natural n = 0;
    EXPECT_THROW(--n, range_error);
}

TEST(Natural, postdecrementationWorksAsExpected)
{
    Natural n = 1;
    EXPECT_EQ(1, n--);
    EXPECT_EQ(0, n);
}

TEST(Natural, postdecrementationCannotResultInNegativeValue)
{
    Natural n = 0;
    EXPECT_THROW(--n, range_error);
}

TEST(Natural, negationWorksAsExpected)
{
    EXPECT_TRUE(not Natural{0});
    EXPECT_FALSE(not Natural{1});
}

TEST(Natural, logicalAndWorksAsExpected)
{
    EXPECT_TRUE(n3 and 3);
    EXPECT_TRUE(3 and n3);
    EXPECT_TRUE(n3 and 3u);
    EXPECT_TRUE(3u and n3);
    EXPECT_TRUE(n3 and n3);

    EXPECT_FALSE(n3 and 0);
    EXPECT_FALSE(0 and n3);
    EXPECT_FALSE(n3 and 0u);
    EXPECT_FALSE(0u and n3);

    Natural n0 = 0;
    EXPECT_FALSE(n0 and 3);
    EXPECT_FALSE(3 and n0);
    EXPECT_FALSE(n0 and 3u);
    EXPECT_FALSE(3u and n0);
    EXPECT_FALSE(n3 and n0);
    EXPECT_FALSE(n0 and n3);
}

TEST(Natural, logicalOrWorksAsExpected)
{
    EXPECT_TRUE(n3 or 3);
    EXPECT_TRUE(3 or n3);
    EXPECT_TRUE(n3 or 3u);
    EXPECT_TRUE(3u or n3);
    EXPECT_TRUE(n3 or n3);

    EXPECT_TRUE(n3 or 0);
    EXPECT_TRUE(0 or n3);
    EXPECT_TRUE(n3 or 0u);
    EXPECT_TRUE(0u or n3);

    Natural n0 = 0;
    EXPECT_TRUE(n0 or 3);
    EXPECT_TRUE(3 or n0);
    EXPECT_TRUE(n0 or 3u);
    EXPECT_TRUE(3u or n0);
    EXPECT_TRUE(n3 or n0);
    EXPECT_TRUE(n0 or n3);

    EXPECT_FALSE(n0 or 0);
    EXPECT_FALSE(0 or n0);
    EXPECT_FALSE(n0 or 0u);
    EXPECT_FALSE(0u or n0);
    EXPECT_FALSE(n0 or n0);
}

TEST(Natural, unaryPlusWorksAsExpected)
{
    EXPECT_EQ(3, +n3);
    EXPECT_EQ(n3, +n3);
}

TEST(Natural, unaryMinusWorksAsExpected)
{
    EXPECT_EQ(-3, -n3);
}

TEST(Natural, additionWorksAsExpected)
{
    EXPECT_EQ(3, Natural{1} + Natural{2});
    EXPECT_EQ(3, Natural{1} + 2);
    EXPECT_EQ(3, 1 + Natural{2});
}

TEST(Natural, negativeAdditionResultCannotBeAssigned)
{
    Natural n;
    EXPECT_THROW(n = n3 + -4, range_error);
    EXPECT_THROW(n = -4 + n3, range_error);
}

TEST(Natural, subtractionWorksAsExpected)
{
    EXPECT_EQ(1, Natural{3} - Natural{2});
    EXPECT_EQ(1, Natural{3} - 2);
    EXPECT_EQ(1, 3 - Natural{2});
}

TEST(Natural, negativeSubtractionResultCannotBeAssigned)
{
    Natural n;
    EXPECT_THROW(n = n3 - 4, range_error);
    EXPECT_THROW(n = 2 - n3, range_error);
}

TEST(Natural, multiplicationWorksAsExpected)
{
    EXPECT_EQ(6, Natural{3} * Natural{2});
    EXPECT_EQ(6, Natural{3} * 2);
    EXPECT_EQ(6, 3 * Natural{2});
}

TEST(Natural, negativeMultiplicationResultCannotBeAssigned)
{
    Natural n;
    EXPECT_THROW(n = n3 * -1, range_error);
    EXPECT_THROW(n = -1 * n3, range_error);
}

TEST(Natural, divisionWorksAsExpected)
{
    EXPECT_EQ(3, Natural{6} / Natural{2});
    EXPECT_EQ(3, Natural{6} / 2);
    EXPECT_EQ(3, 6 / Natural{2});
}

TEST(Natural, negativeDivisionResultCannotBeAssigned)
{
    Natural n;
    EXPECT_THROW(n = n3 / -1, range_error);
    EXPECT_THROW(n = -4 / n3, range_error);
}

TEST(Natural, moduloWorksAsExpected)
{
    EXPECT_EQ(1, Natural{7} % Natural{3});
    EXPECT_EQ(1, Natural{7} % 3);
    EXPECT_EQ(1, 7 % Natural{3});
}

TEST(Natural, negativeModuloResultCannotBeAssigned)
{
    Natural n;
    EXPECT_THROW(n = -4 % n3, range_error);
}

TEST(Natural, bitwiseNotWorksAsExpected)
{
    EXPECT_EQ(static_cast<int>(0xF0F0F0F0), ~Natural{0x0F0F0F0F});
}

TEST(Natural, bitwiseAndWorksAsExpected)
{
    EXPECT_EQ(0x0A0A0A0A, Natural{0x0F5F5F5F} & 0x0AAAAAAA);
    EXPECT_EQ(0x0A0A0A0A, 0x0AAAAAAA & Natural{0x0F5F5F5F});
    EXPECT_EQ(0x0A0A0A0Au, Natural{0x0F5F5F5F} & 0xFAAAAAAA);
    EXPECT_EQ(0x0A0A0A0Au, 0xFAAAAAAA & Natural{0x0F5F5F5F});
    EXPECT_EQ(0x0A0A0A0A, Natural{0x0F5F5F5F} & Natural{0x0AAAAAAA});
}

TEST(Natural, bitwiseOrWorksAsExpected)
{
    EXPECT_EQ(0x0FFFFFFF, Natural{0x0F5F5F5F} | 0x0AAAAAAA);
    EXPECT_EQ(0x0FFFFFFF, 0x0AAAAAAA | Natural{0x0F5F5F5F});
    EXPECT_EQ(0xFFFFFFFF, Natural{0x0F5F5F5F} | 0xFAAAAAAA);
    EXPECT_EQ(0xFFFFFFFF, 0xFAAAAAAA | Natural{0x0F5F5F5F});
    EXPECT_EQ(0x0FFFFFFF, Natural{0x0F5F5F5F} | Natural{0x0AAAAAAA});
}

TEST(Natural, bitwiseXorWorksAsExpected)
{
    EXPECT_EQ(0x05F5F5F5, Natural{0x0F5F5F5F} ^ 0x0AAAAAAA);
    EXPECT_EQ(0x05F5F5F5, 0x0AAAAAAA ^ Natural{0x0F5F5F5F});
    EXPECT_EQ(0xF5F5F5F5, Natural{0x0F5F5F5F} ^ 0xFAAAAAAA);
    EXPECT_EQ(0xF5F5F5F5, 0xFAAAAAAA ^ Natural{0x0F5F5F5F});
    EXPECT_EQ(0x05F5F5F5, Natural{0x0F5F5F5F} ^ Natural{0x0AAAAAAA});
}

TEST(Natural, leftShiftWorksAsExpected)
{
    EXPECT_EQ(16, Natural{2} << 3);
}

TEST(Natural, rightShiftWorksAsExpected)
{
    EXPECT_EQ(2, Natural{16} >> 3);
}
