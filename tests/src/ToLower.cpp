#include "ToLower.hpp"
#include "GtestWrapper.hpp"

TEST(ToLower, toLower)
{
    EXPECT_EQ("ala ma kota", toLower("Ala ma kota"));
    EXPECT_EQ("ala ma kota!", toLower("Ala ma kota!"));
    EXPECT_EQ("ala ma kota", toLower("AlA mA KoTa"));
    EXPECT_EQ("ala ma kota", toLower("ala ma kota"));
    EXPECT_EQ("", toLower(""));
    EXPECT_EQ("#", toLower("#"));
}
