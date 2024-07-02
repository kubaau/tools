#pragma once

#include <array>
#include <type_traits>
#include <utility>

template <std::size_t N, typename T>
auto createFilledArray(const T& value)
{
    std::array<T, N> arr;
    arr.fill(value);
    return arr;
}

namespace Detail
{
    using namespace std;

    template <typename T, typename... Args>
    using MakeArrayResultType =
        array<conditional_t<is_same<T, void>::value, common_type_t<Args...>, T>, sizeof...(Args)>;
}

template <typename T = void, typename... Args>
constexpr auto makeArray(Args&&... args)
{
    return Detail::MakeArrayResultType<T, Args...>{{std::forward<Args>(args)...}};
}
