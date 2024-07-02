#pragma once

#include "RangeStlAlgorithms.hpp"

inline auto toLower(std::string str)
{
    return transform(str, [](auto c) { return static_cast<char>(::tolower(c)); });
}
