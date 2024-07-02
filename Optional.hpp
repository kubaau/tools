#pragma once

#include <iostream>
#include <optional>

template <typename T>
auto& operator<<(std::ostream& os, const std::optional<T>& opt)
{
    if (opt)
        os << *opt;
    else
        os << "<none>";
    return os;
}
