#pragma once

#include "Iterators.hpp"

template <class It, typename T>
auto lowerBound(It begin, It end, const T& val)
{
    if (begin == end)
        return begin;
    const auto m = mid(begin, end);
    if (*m < val)
        return lowerBound(m + 1, end, val);
    else
        return lowerBound(begin, m, val);
}
