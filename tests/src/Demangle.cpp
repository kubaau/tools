#include "Demangle.hpp"
#include "GtestWrapper.hpp"

TEST(Demangle, demangle_type)
{
    EXPECT_EQ("int", demangle<int>());
}

TEST(Demangle, demangle_value)
{
    EXPECT_EQ("int", demangle(7));
}
