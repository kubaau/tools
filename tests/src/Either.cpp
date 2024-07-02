#include "Either.hpp"
#include "GtestWrapper.hpp"

TEST(Either, either)
{
    const auto to_be = either();
    EXPECT_TRUE(to_be or not to_be); // lel
}
