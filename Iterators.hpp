#pragma once

#include "TypeTraits.hpp"

namespace Detail
{
    using namespace std;

    template <class C, typename = enable_if_t<HasMember_push_back<C>::value>>
    auto end_inserter(C& c, int)
    {
        using namespace std;
        return back_inserter(c);
    }

    template <class C, typename = enable_if_t<not HasMember_push_back<C>::value>>
    auto end_inserter(C& c, float)
    {
        using namespace std;
        return inserter(c, end(c));
    }
}

template <class C>
auto end_inserter(C& c)
{
    return Detail::end_inserter(c, 0);
}

template <class C>
auto begin_inserter(C& c)
{
    using namespace std;
    return inserter(c, begin(c));
}

template <typename It>
auto mid(It begin, It end)
{
    return begin + (end - begin) / 2;
}

template <class C>
auto mid(C& c)
{
    using namespace std;
    return mid(begin(c), end(c));
}

template <class C>
auto cmid(const C& c)
{
    using namespace std;
    return mid(cbegin(c), cend(c));
}
