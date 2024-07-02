#pragma once

#include <boost/preprocessor.hpp>
#include <iostream>

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE(ignore, EnumName, value) \
    case EnumName::value: return BOOST_PP_STRINGIZE(value);

// usage: DEFINE_ENUM_WITH_STRING_CONVERSIONS_BASE(enum/enum class, EnumName, (Value1)(Value2))
#define DEFINE_ENUM_WITH_STRING_CONVERSIONS_BASE(EnumScope, EnumName, values)                          \
    EnumScope EnumName{BOOST_PP_SEQ_ENUM(values)};                                                     \
                                                                                                       \
    inline auto toString(EnumName v)                                                                   \
    {                                                                                                  \
        switch (v)                                                                                     \
        {                                                                                              \
            BOOST_PP_SEQ_FOR_EACH(DEFINE_ENUM_WITH_STRING_CONVERSIONS_TOSTRING_CASE, EnumName, values) \
            default: return "unknown " BOOST_PP_STRINGIZE(EnumName);                                   \
        }                                                                                              \
    }                                                                                                  \
                                                                                                       \
    inline auto& operator<<(std::ostream& os, EnumName value) { return os << toString(value); }

#define DEFINE_ENUM_WITH_STRING_CONVERSIONS(EnumName, values) \
    DEFINE_ENUM_WITH_STRING_CONVERSIONS_BASE(enum, EnumName, values)
#define DEFINE_ENUM_CLASS_WITH_STRING_CONVERSIONS(EnumName, values) \
    DEFINE_ENUM_WITH_STRING_CONVERSIONS_BASE(enum class, EnumName, values)
