#pragma once

#include <algorithm>
#include <iostream>

#include "ForwardDeclarations.hpp"
#include "QueuePop.hpp"
#include "StackPop.hpp"
#include "Typedefs.hpp"

template <typename T>
void printItem(std::ostream& os, const T& item)
{
    os << item;
}

inline void printItem(std::ostream& os, Byte item)
{
    os << +item;
}

template <typename It, typename>
std::ostream& operator<<(std::ostream& os, const std::pair<It, It>& its)
{
    const auto begin = its.first;
    const auto end = its.second;
    os << "{";
    if (begin != end)
    {
        using namespace std;
        const auto last_it = prev(end);
        for_each(begin, last_it, [&os](const auto& item) {
            printItem(os, item);
            os << ", ";
        });
        // copy(begin, prev(end), ostream_iterator<iterator_traits<It>::value_type>{os, ", "});
        // cannot see op<<(pair) because it's not in std
        printItem(os, *last_it);
    }
    os << "}";
    return os;
}

template <class C, typename>
std::ostream& operator<<(std::ostream& os, const C& c)
{
    using namespace std;
    return os << make_pair(cbegin(c), cend(c));
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pair)
{
    return os << "{" << pair.first << ", " << pair.second << "}";
}

template <class C, typename, typename>
std::ostream& operator<<(std::ostream& os, C c)
{
    os << "{";
    if (not c.empty())
        os << pop(c);
    while (not c.empty())
        os << ", " << pop(c);
    os << "}";
    return os;
}

namespace Detail
{
    using namespace std;

    template <size_t N, typename... T>
    enable_if_t<(N >= sizeof...(T))> print(ostream&, const tuple<T...>&)
    {
    }

    template <size_t N, typename... T>
    enable_if_t<(N < sizeof...(T))> print(ostream& os, const tuple<T...>& tuple)
    {
        os << ", " << get<N>(tuple);
        print<N + 1>(os, tuple);
    }

    template <typename... T>
    enable_if_t<(sizeof...(T) > 0)> print(ostream& os, const tuple<T...>& tuple, int)
    {
        os << get<0>(tuple);
        print<1>(os, tuple);
    }

    template <typename... T>
    enable_if_t<(sizeof...(T) == 0)> print(ostream&, const tuple<T...>&, int)
    {
    }
}

template <typename... T>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& tuple)
{
    os << "[";
    Detail::print(os, tuple, 0);
    return os << "]";
}
