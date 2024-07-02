#pragma once

#include "Typedefs.hpp"

template <typename T>
auto asBytePtr(const T* ptr)
{
    return reinterpret_cast<const Byte*>(ptr);
}

template <typename T>
auto moveNBytes(T*& ptr, int n)
{
    ptr = const_cast<T*>(reinterpret_cast<const T*>(asBytePtr(ptr) + n));
}
