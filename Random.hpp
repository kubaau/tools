#pragma once

#include "DefaultRandomEngine.hpp"

template <typename Int, class UniformRandomBitGenerator>
auto randomInt(Int min, Int max, UniformRandomBitGenerator&& g)
{
    return std::uniform_int_distribution<Int>{min, max}(g);
}

template <typename Int>
auto randomInt(Int min, Int max)
{
    return randomInt(min, max, defaultRandomEngine());
}

template <typename Float, class UniformRandomBitGenerator>
auto randomFloat(Float min, Float max, UniformRandomBitGenerator&& g)
{
    return std::uniform_real_distribution<Float>{min, max}(g);
}

template <typename Float>
auto randomFloat(Float min, Float max)
{
    return randomFloat(min, max, defaultRandomEngine());
}
