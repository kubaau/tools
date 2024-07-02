#pragma once

#include <vector>
#include "FunctionTraits.hpp"

namespace Detail
{
    using namespace std;

    template <class F1, class F2>
    class FunctionComposition
    {
    public:
        FunctionComposition(F1 f1, F2 f2) : f1{f1}, f2{f2} {}

        auto operator()(typename FunctionTraits<F1>::template ArgType<0> arg) { return f2(f1(arg)); }

    private:
        F1 f1;
        F2 f2;
    };

    template <class F1, class F2>
    auto composeImpl(F1 p_first, F2 p_second)
    {
        static_assert(IsFunction<F1>::value, "only well defined functions can be composed");
        static_assert(IsFunction<F2>(), "only well defined functions can be composed");

        return FunctionComposition<F1, F2>{p_first, p_second};
    }

    template <class F1, class F2, class... Rest>
    auto composeImpl(F1 f1, F2 f2, Rest... rest)
    {
        return composeImpl(f1, composeImpl(f2, rest...));
    }
}

template <class... Fs>
auto compose(Fs... fs)
{
    return Detail::composeImpl(fs...);
}

template <class F>
class FunctorComposite
{
};

template <class F, typename... Args>
class FunctorComposite<F(Args...)>
{
    using Functor = std::function<void(Args...)>;

public:
    explicit FunctorComposite(std::initializer_list<Functor> fs) : fs(fs) {}

    void operator()(Args... args)
    {
        for (const auto& f : fs)
            f(args...);
    }

private:
    std::vector<Functor> fs;
};
