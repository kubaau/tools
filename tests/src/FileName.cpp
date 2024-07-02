#include "FileName.hpp"
#include "GtestWrapper.hpp"

TEST(FileName, FILE_NAME_SHIFT_is_constexpr)
{
    static_assert(FILE_NAME_SHIFT, "");
}

TEST(FileName, FILE_NAME_RCHR_CONSTEXPR_is_constexpr)
{
    static_assert(FILE_NAME_RCHR_CONSTEXPR, "");
}
