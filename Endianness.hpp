#pragma once

#include "Typedefs.hpp"

inline auto isLittleEndian()
{
    constexpr u16 val = 1;
    static const auto ret = (val == *reinterpret_cast<const u8*>(&val));
    return ret;
}
