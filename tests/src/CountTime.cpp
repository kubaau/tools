#include "CountTime.hpp"
#include "GtestWrapper.hpp"

using namespace std::chrono;

TEST(CountTime, countWorksForAllSupportedChronoTypes)
{
    constexpr auto time = 1h + 2min + 3s + 4ms + 5us;
    EXPECT_EQ(1, count<hours>(time));
    EXPECT_EQ(60 + 2, count<minutes>(time));
    EXPECT_EQ(3600 + 120 + 3, count<seconds>(time));
    EXPECT_EQ(3600000 + 120000 + 3000 + 4, count<milliseconds>(time));
    EXPECT_EQ(3600000000 + 120000000 + 3000000 + 4000 + 5, count<microseconds>(time));
}

TEST(CountTime, countCanBeOverriddenToReturnTypesOtherThanDefault)
{
    constexpr auto time = 1h + 2min + 3s;
    EXPECT_EQ(1, (count<hours, int>(time)));
    EXPECT_EQ(60u + 2u, (count<minutes, unsigned>(time)));
    EXPECT_EQ(float{3600 + 120 + 3}, (count<seconds, float>(time)));
}

TEST(CountTime, overridingCountToReturnTooSmallATypeResultsInBadCast)
{
    EXPECT_THROW((count<seconds, int>(seconds{numeric_limits<int>::max() + 1ll})), boost::bad_numeric_cast);
}
