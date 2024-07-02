#pragma once

#include <type_traits>
#include "CustomRangeAlgorithms.hpp"
#include "ExtendedRangeStlAlgorithms.hpp"

namespace Detail
{
    using namespace std;
    using RValueYes = true_type;
    using RValueNo = false_type;
    using MutableIteratorYes = true_type;
    using MutableIteratorNo = false_type;

    template <class C, class UnaryPred>
    auto filterImpl(C&& c, UnaryPred pred, RValueYes, MutableIteratorYes)
    {
        erase_if(c, [pred](auto& i) { return not pred(i); });
        return move(c);
    }

    template <class C, class UnaryPred>
    auto filterImpl(C&& c, UnaryPred pred, RValueYes, MutableIteratorNo)
    {
        for (auto it = begin(c); it != end(c);)
            if (not pred(*it))
                it = c.erase(it);
            else
                ++it;
        return move(c);
    }

    template <class C, class UnaryPred>
    auto filterImpl(const C& c, UnaryPred pred, RValueNo, MutableIteratorNo)
    {
        return copy_if(c, move(pred));
    }

    template <class C, class UnaryPred>
    auto filterImpl(const C& c, UnaryPred pred, RValueNo rvalue_no, MutableIteratorYes)
    {
        return filterImpl(c, pred, rvalue_no, MutableIteratorNo{});
    }

    template <class C>
    MutableIteratorNo valuesAreMutable(C, float);

    template <class C>
    MutableIteratorYes valuesAreMutable(C, int, decltype(*declval<C>().begin() = *declval<C>().begin()) * = nullptr);

    template <class C>
    using ValuesAreMutable = decltype(valuesAreMutable(declval<C>(), 0));
}

template <class C, class UnaryPredicate>
auto filter(C&& c, UnaryPredicate pred) // if c is an rvalue, modify in place
{
    using namespace std;
    return Detail::filterImpl(forward<C>(c), move(pred), is_rvalue_reference<C&&>{}, Detail::ValuesAreMutable<C>{});
}
