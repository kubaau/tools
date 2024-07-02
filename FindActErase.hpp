#pragma once

#include "TypeTraits.hpp"

namespace Detail
{
    using namespace std;

    template <class C, typename T, class UnaryOp>
    void findActEraseImpl(C& c, const T& i, UnaryOp f, float)
    {
        const auto it = c.find(i);
        if (it != cend(c))
        {
            f(*it);
            c.erase(it);
        }
    }

    template <class C, typename T, class UnaryOp, typename = enable_if_t<HasMember_mapped_type<C>::value>>
    void findActEraseImpl(C& c, const T& i, UnaryOp f, int)
    {
        const auto it = c.find(i);
        if (it != cend(c))
        {
            f(it->second);
            c.erase(it);
        }
    }
}

template <class C, typename T, class UnaryOp>
auto findActErase(C& c, const T& i, UnaryOp f)
{
    return Detail::findActEraseImpl(c, i, std::move(f), 0);
}
