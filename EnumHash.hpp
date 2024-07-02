#pragma once

#include <functional>
#include <type_traits>

template <typename E, typename = std::enable_if_t<std::is_enum<E>::value>>
auto enumHash(E e)
{
    using namespace std;
    using T = underlying_type_t<E>;
    return hash<T>{}(static_cast<T>(e));
}

template <typename E, typename = std::enable_if_t<std::is_enum<E>::value>>
struct EnumHash
{
    auto operator()(E e) const { return enumHash(e); }
};
