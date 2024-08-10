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

template <typename NumericLimitSource, typename Int = NumericLimitSource, class UniformRandomBitGenerator>
auto randomInt(UniformRandomBitGenerator&& g = defaultRandomEngine())
{
    using namespace std;
    using nl = numeric_limits<NumericLimitSource>;
    return static_cast<NumericLimitSource>(randomInt<Int>(nl::min(), nl::max(), move(g)));
}

template <typename NumericLimitSource, typename Int = NumericLimitSource>
auto randomInt()
{
    return randomInt<NumericLimitSource, Int>(defaultRandomEngine());
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
