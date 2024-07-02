#include "Combine.hpp"
#include "GtestWrapper.hpp"

TEST(Combine, line_combine)
{
    int LINE_COMBINE(i){};
    int LINE_COMBINE(i){};
    EXPECT_EQ(i6, i7);
}
