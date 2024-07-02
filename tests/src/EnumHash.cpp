#include "EnumHash.hpp"
#include "GtestWrapper.hpp"

TEST(EnumHash, EnumHash)
{
    const auto val = 7;
    enum class EChar : char
    {
        E = val
    };
    enum class EInt : int
    {
        E = val
    };
    enum class EUnsigned : unsigned
    {
        E = val
    };

    EXPECT_EQ(hash<char>{}(val), enumHash(EChar::E));
    EXPECT_EQ(hash<int>{}(val), enumHash(EInt::E));
    EXPECT_EQ(hash<unsigned>{}(val), enumHash(EUnsigned::E));
    EXPECT_EQ(hash<char>{}(val), EnumHash<EChar>{}(EChar::E));
    EXPECT_EQ(hash<int>{}(val), EnumHash<EInt>{}(EInt::E));
    EXPECT_EQ(hash<unsigned>{}(val), EnumHash<EUnsigned>{}(EUnsigned::E));
}
