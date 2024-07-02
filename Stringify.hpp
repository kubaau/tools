#pragma once

#include <sstream>
#include "OutputOperators.hpp"

namespace Detail
{
    using namespace std;

    template <typename T>
    auto stringifyImpl(ostream& os, T&& arg)
    {
        os << arg;
    }

    template <typename T, typename... U>
    auto stringifyImpl(ostream& os, T&& arg, U&&... args)
    {
        os << arg << " ";
        stringifyImpl(os, forward<U>(args)...);
    }

    inline auto stringifyImpl(ostream&) {}
}

template <typename... Args>
auto stringify(Args&&... args)
{
    using namespace std;
    stringstream ss;
    Detail::stringifyImpl(ss, forward<Args>(args)...);
    return ss.str();
}
