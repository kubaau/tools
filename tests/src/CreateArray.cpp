#include "CreateArray.hpp"
#include "GtestWrapper.hpp"

TEST(CreateArray, createFilledArray)
{
    EXPECT_EQ((A<3>{{2, 2, 2}}), (createFilledArray<3>(2)));
    EXPECT_EQ((A<4>{{3, 3, 3, 3}}), (createFilledArray<4>(3)));
}

TEST(CreateArray, make_array)
{
    EXPECT_EQ((A<3>{{1, 2, 3}}), makeArray(1, 2, 3));
    EXPECT_EQ((A<3, unsigned>{{1, 2, 3}}), makeArray(1u, 2u, 3u));
    EXPECT_EQ((A<3, unsigned>{{1, 2, 3}}), makeArray(1u, 2u, u8{3}));
}
