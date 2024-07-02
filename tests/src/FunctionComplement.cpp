#include "FunctionComplement.hpp"
#include "GtestWrapper.hpp"
#include "Numeric.hpp"

TEST(FunctionComplement, complement)
{
    auto is_odd = [](int i) { return isOdd(i); };
    auto is_even = complement(is_odd);
    EXPECT_TRUE(isOdd(7));
    EXPECT_FALSE(is_even(7));
    EXPECT_FALSE(isOdd(8));
    EXPECT_TRUE(is_even(8));
}
