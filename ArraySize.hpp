#pragma once

#include <type_traits>

template <typename SizeType = std::size_t, unsigned dimension = 0, typename ArrayType>
constexpr SizeType extent(const ArrayType&)
{
    return std::extent<ArrayType, dimension>::value;
}

template <typename Ret = std::size_t, typename T, std::size_t size>
constexpr auto arraySize(const T (&)[size])
{
    return static_cast<Ret>(size);
}

template <typename T, std::size_t size>
constexpr auto arraySizeInBytes(const T (&a)[size])
{
    return sizeof(a);
}
