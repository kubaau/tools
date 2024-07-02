#pragma once

#include <utility>
#include "TypeTraits.hpp"

namespace Detail
{
    using namespace std;

    template <class C, typename T>
    auto insertImpl(C& c, const T& i, float)
    {
        return c.push_back(i);
    }

    template <class C, typename T>
    auto insertImpl(C& c, const T& i, int) -> EnableIfHasFindMethod<C, pair<typename C::iterator, bool>>
    {
        return c.insert(i);
    }
}

template <class C, typename T>
auto insert(C& c, const T& val)
{
    return Detail::insertImpl(c, val, 0);
}
