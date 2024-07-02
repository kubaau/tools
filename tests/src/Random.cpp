#include "Random.hpp"
#include "GtestWrapper.hpp"
#include "Print.hpp"
#include "Typedefs.hpp"

static auto re = mt19937{random_device{}()};

TEST(Random, randomInt)
{
    const auto r = randomInt(-3, 7, mt19937{random_device{}()});
    print(r);
    EXPECT_TRUE(r >= -3 and r <= 7);

    EXPECT_EQ(5, randomInt(5, 5, mt19937{random_device{}()}));
    EXPECT_EQ(5, randomInt(5, 5, re));
}

TEST(Random, randomInt_unsigned)
{
    const auto r1 = randomInt(3u, 7u, mt19937{random_device{}()});
    print(r1);
    EXPECT_TRUE(r1 >= 3 and r1 <= 7);

    EXPECT_EQ(5u, randomInt(5u, 5u, mt19937{random_device{}()}));
    EXPECT_EQ(5u, randomInt(5u, 5u, re));

    auto i = 65538;
    const auto r2 = randomInt<u16>(0, static_cast<u16>(i), mt19937{random_device{}()});
    print(r2);
    EXPECT_TRUE(r2 <= 2);
}

TEST(Random, randomInt_default)
{
    const auto r = randomInt(-3, 7);
    print(r);
    EXPECT_TRUE(r >= -3 and r <= 7);

    EXPECT_EQ(5, randomInt(5, 5));
}

TEST(Random, randomInt_unsigned_default)
{
    const auto r = randomInt(3u, 7u);
    print(r);
    EXPECT_TRUE(r >= 3 and r <= 7);

    EXPECT_EQ(5u, randomInt(5u, 5u));
}

TEST(Random, randomFloat_double)
{
    const auto r = randomFloat(-3.14, 7.17, mt19937{random_device{}()});
    print(r);
    EXPECT_TRUE(r >= -3.14 and r <= 7.17);

    EXPECT_EQ(5.5, randomFloat(5.5, 5.5, mt19937{random_device{}()}));
    EXPECT_EQ(5.5, randomFloat(5.5, 5.5, re));
}

TEST(Random, randomFloat_float)
{
    const auto r = randomFloat(-3.14f, 7.17f, mt19937{random_device{}()});
    print(r);
    EXPECT_TRUE(r >= -3.14 and r <= 7.17);

    EXPECT_EQ(5.5, randomFloat(5.5f, 5.5f, mt19937{random_device{}()}));
    EXPECT_EQ(5.5, randomFloat(5.5f, 5.5f, re));
}

TEST(Random, randomFloat_double_default)
{
    const auto r = randomFloat(-3.14, 7.17);
    print(r);
    EXPECT_TRUE(r >= -3.14 and r <= 7.17);

    EXPECT_EQ(5.5, randomFloat(5.5, 5.5));
}

TEST(Random, randomFloat_float_default)
{
    const auto r = randomFloat(-3.14f, 7.17f);
    print(r);
    EXPECT_TRUE(r >= -3.14 and r <= 7.17);

    EXPECT_EQ(5.5, randomFloat(5.5f, 5.5f));
}
