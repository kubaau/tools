#pragma once

#include "RangeStlAlgorithms.hpp"

namespace Detail
{
    using namespace std;

    template <class C, typename T>
    auto containsImpl(const C& c, const T& i, float)
    {
        return find(c, i) != cend(c);
    }

    template <class C, typename T>
    auto containsImpl(const C& c, const T& i, int) -> EnableIfHasFindMethod<C, bool>
    {
        return c.find(i) != cend(c);
    }
}

template <typename T, class C = std::initializer_list<T>>
auto contains(const C& c, const T& i)
{
    return Detail::containsImpl(c, i, 0);
}

template <typename T>
auto contains(const std::string& s1, const T& s2)
{
    return s1.find(s2) != std::string::npos;
}

template <class T>
auto in(const T& value, const std::set<T>& c)
{
    return contains(c, value);
}
