#include "EnumToString.hpp"
#include "GtestWrapper.hpp"
#include "StringStream.hpp"

DEFINE_ENUM_WITH_STRING_CONVERSIONS(Option, (Disabled)(Enabled))
DEFINE_ENUM_CLASS_WITH_STRING_CONVERSIONS(OptionClass, (Disabled)(Enabled))

TEST(EnumToString, enum_with_string_conversions)
{
    Option o{};
    ostringstream oss;

    oss << o;
    EXPECT_EQ("Disabled", oss.str());
    clear(oss);

    oss << Enabled;
    EXPECT_EQ("Enabled", oss.str());
    clear(oss);

    oss << static_cast<Option>(-1);
    EXPECT_EQ("unknown Option", oss.str());
}

TEST(EnumToString, enum_class_with_string_conversions)
{
    OptionClass o{};
    ostringstream oss;

    oss << o;
    EXPECT_EQ("Disabled", oss.str());
    clear(oss);

    oss << OptionClass::Enabled;
    EXPECT_EQ("Enabled", oss.str());
    clear(oss);

    oss << static_cast<OptionClass>(-1);
    EXPECT_EQ("unknown OptionClass", oss.str());
}
