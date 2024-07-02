#pragma once

#include <cstring>
#include "TypeTraits.hpp"

template <typename T, typename = std::enable_if_t<HasMember_tieAll<T>::value>>
auto operator==(const T& lhs, const T& rhs)
{
    return lhs.tieAll() == rhs.tieAll();
}
template <typename T, typename = std::enable_if_t<HasMember_tieAll<T>::value>>
auto operator!=(const T& lhs, const T& rhs)
{
    return not(lhs == rhs);
}
template <typename T, typename = std::enable_if_t<HasMember_tieAll<T>::value>>
auto operator<(const T& lhs, const T& rhs)
{
    return lhs.tieAll() < rhs.tieAll();
}
template <typename T, typename = std::enable_if_t<HasMember_tieAll<T>::value>>
auto operator<=(const T& lhs, const T& rhs)
{
    return lhs.tieAll() <= rhs.tieAll();
}
template <typename T, typename = std::enable_if_t<HasMember_tieAll<T>::value>>
auto operator>(const T& lhs, const T& rhs)
{
    return lhs.tieAll() > rhs.tieAll();
}
template <typename T, typename = std::enable_if_t<HasMember_tieAll<T>::value>>
auto operator>=(const T& lhs, const T& rhs)
{
    return lhs.tieAll() >= rhs.tieAll();
}

#define MEMCMPARABLE struct MemCmparable
template <typename T, typename = std::enable_if_t<HasMember_MemCmparable<T>::value>, typename V = void>
auto operator==(const T& lhs, const T& rhs)
{
    return std::memcmp(&lhs, &rhs, sizeof(T)) == 0;
}
template <typename T, typename = std::enable_if_t<HasMember_MemCmparable<T>::value>, typename V = void>
auto operator!=(const T& lhs, const T& rhs)
{
    return not(lhs == rhs);
}

template <class C1, class C2, typename = std::enable_if_t<IsContainer<C1>::value and IsContainer<C2>::value>>
auto operator==(const C1& c1, const C2& c2)
{
    return std::equal(c1, c2);
}
