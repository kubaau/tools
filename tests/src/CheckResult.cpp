#include "CheckResult.hpp"
#include "GtestWrapper.hpp"

TEST(CheckResult, check)
{
    EXPECT_NO_THROW(check(true));
    EXPECT_THROW(check(false), runtime_error);
}
