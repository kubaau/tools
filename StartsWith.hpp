#pragma once

#include <string>

inline auto startsWith(std::string str, std::string prefix)
{
    return str.rfind(prefix) == 0;
}
