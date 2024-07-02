#pragma once

#include "EnumToString.hpp"

DEFINE_ENUM_CLASS_WITH_STRING_CONVERSIONS(RangeOpenness, (Closed)(OpenLeft)(OpenRight)(Open))

template <typename T>
auto inRange(const T& val, const T& min, const T& max, RangeOpenness openness = RangeOpenness::Open)
{
    switch (openness)
    {
        case RangeOpenness::Closed: return val > min and val < max;
        case RangeOpenness::OpenLeft: return val >= min and val < max;
        case RangeOpenness::OpenRight: return val > min and val <= max;
        default: return val >= min and val <= max;
    }
}
