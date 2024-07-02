#pragma once

#include "Random.hpp"

template <typename Int>
auto chance(Int n)
{
    return randomInt(1, n) == n;
}
