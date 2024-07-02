#pragma once

#include <climits>

template <typename T>
constexpr auto bitsIn()
{
    constexpr auto bits_in_byte = CHAR_BIT;
    return bits_in_byte * sizeof(T);
}

template <typename T>
constexpr auto bitsIn(const T&)
{
    return bitsIn<T>();
}

template <typename T>
auto countSetBits(T val)
{
    auto set_bits_count = 0u;
    for (auto i = 0u; i < bitsIn(val); ++i)
    {
        set_bits_count += val & 1;
        val >>= 1;
    }
    return set_bits_count;
}
