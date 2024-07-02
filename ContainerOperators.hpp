#pragma once

#include "CustomRangeAlgorithms.hpp"
#include "ExtendedRangeStlAlgorithms.hpp"
#include "TypeTraits.hpp"

namespace RangeOperators
{
    template <class C1,
              class C2,
              typename = std::enable_if_t<IsContainer<C1>::value and not IsSameDecayed<C1, C2>::value>>
    auto& operator+=(C1& c, C2&& i)
    {
        using namespace std;
        c.insert(end(c), forward<C2>(i));
        return c;
    }
    template <class C1,
              class C2,
              typename = std::enable_if_t<IsContainer<C1>::value and IsSameDecayed<C1, C2>::value>,
              typename = void>
    auto& operator+=(C1& lhs, C2&& rhs)
    {
        copy(std::forward<C2>(rhs), lhs);
        return lhs;
    }

    template <class C, typename T>
    auto operator+(C c, T&& i)
    {
        return c += std::forward<T>(i);
    }

    template <class C1,
              class C2,
              typename = std::enable_if_t<IsContainer<C1>::value and not IsSameDecayed<C1, C2>::value>>
    auto& operator-=(C1& c, C2&& i)
    {
        erase_one(c, std::forward<C2>(i));
        return c;
    }
    template <class C1,
              class C2,
              typename = std::enable_if_t<IsContainer<C1>::value and IsSameDecayed<C1, C2>::value>,
              typename = void>
    auto& operator-=(C1& lhs, C2&& rhs)
    {
        using namespace std;
        lhs = set_difference(forward<C1>(lhs), forward<C2>(rhs));
        return lhs;
    }

    template <class C, typename T>
    auto operator-(C c, T&& i)
    {
        return c -= std::forward<T>(i);
    }

    template <class C>
    C& operator&=(C& lhs, const C& rhs)
    {
        lhs = set_intersection(lhs, rhs);
        return lhs;
    }
    template <class C>
    C operator&=(C&& c, const C& rhs)
    {
        C ret = c;
        return ret &= rhs;
    }

    template <class C>
    C operator&(C lhs, const C& rhs)
    {
        return lhs &= rhs;
    }

    template <class C>
    C& operator|=(C& lhs, const C& rhs)
    {
        lhs = set_union(lhs, rhs);
        return lhs;
    }
    template <class C>
    C operator|=(C&& c, const C& rhs)
    {
        C ret = c;
        return ret |= rhs;
    }

    template <class C>
    C operator|(C lhs, const C& rhs)
    {
        return lhs |= rhs;
    }

    template <class C>
    C& operator^=(C& lhs, const C& rhs)
    {
        lhs = set_symmetric_difference(lhs, rhs);
        return lhs;
    }
    template <class C>
    C operator^=(C&& c, const C& rhs)
    {
        C ret = c;
        return ret ^= rhs;
    }

    template <class C>
    C operator^(C lhs, const C& rhs)
    {
        return lhs ^= rhs;
    }
}

namespace PairwiseOperators
{
    template <class C>
    C& operator+=(C& lhs, const C& rhs)
    {
        using namespace std;

        if (lhs.size() < rhs.size())
            lhs.resize(rhs.size());

        transform(cbegin(rhs), cend(rhs), begin(lhs), begin(lhs), plus<typename C::value_type>());

        return lhs;
    }
    template <class C>
    C operator+=(C&& lhs, const C& rhs)
    {
        C ret = lhs;
        return ret += rhs;
    }
}
