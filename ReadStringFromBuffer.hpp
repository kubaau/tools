#pragma once

#include <sstream>
#include "Typedefs.hpp"

inline auto readString(const Buffer& data, int begin_offset, int end_offset)
{
    std::ostringstream oss;
    for (auto it = cbegin(data) + begin_offset; it != cbegin(data) + end_offset; ++it)
    {
        if (not *it)
            break;
        oss << *it;
    }
    return oss.str();
}
