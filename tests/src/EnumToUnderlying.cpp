#include "EnumToUnderlying.hpp"
#include "GtestWrapper.hpp"

TEST(EnumToUnderlying, toUnderlying)
{
    enum class E : char
    {
        A = 'a'
    };
    EXPECT_EQ('a', toUnderlying(E::A));
}
