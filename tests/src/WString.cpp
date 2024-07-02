#ifdef _WIN32
#include "WString.hpp"

#include "GtestWrapper.hpp"

namespace
{
    const string str = "ala\nma kota";
    const wstring wstr = L"ala\nma kota";
}

TEST(WString, toString)
{
    EXPECT_EQ(str, toString(wstr));
}

TEST(WString, toWString)
{
    EXPECT_EQ(toWstring(str), wstr);
}
#endif
