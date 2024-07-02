#pragma once

#include "FunctionTraits.hpp"

namespace Detail
{
    template <class F>
    struct Complement
    {
        Complement(F f) : f(f) {}

        template <typename... Args>
        auto operator()(Args... args)
        {
            return not f(args...);
        }

    private:
        F f;
    };

    // auto t = [](auto i) { return i + 1; };
    // auto f = WellDefined<int(int)>(t); // f has well defined args and return type
    template <class F>
    using WellDefined = typename FunctionTraits<F>::Function;
}

template <class F>
auto complement(F f)
{
    return Detail::WellDefined<F>(Detail::Complement<F>(f));
}
