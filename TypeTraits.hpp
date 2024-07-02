#pragma once

#include <iterator>
#include <type_traits>
#include "HasMember.hpp"

template <bool Condition, typename T = void>
using EnableIf = std::enable_if_t<Condition, T>;

template <bool Condition, typename T = void>
using DisableIf = std::enable_if_t<not Condition, T>;

template <class Condition, typename T = void>
using EnableIfType = std::enable_if_t<Condition::value, T>;

template <class Condition, typename T = void>
using DisableIfType = std::enable_if_t<not Condition::value, T>;

GENERATE_HAS_MEMBER(const_iterator)
GENERATE_HAS_MEMBER(size)
GENERATE_HAS_MEMBER(find)
GENERATE_HAS_MEMBER(mapped_type)
GENERATE_HAS_MEMBER(push_back)
GENERATE_HAS_MEMBER(MemCmparable)
GENERATE_HAS_MEMBER(tieAll)
GENERATE_HAS_MEMBER(period)
GENERATE_HAS_MEMBER(pop)

template <typename T, bool = true, typename = EnableIf<std::is_class_v<T>>>
class IsContainer
{
public:
    static constexpr auto value = HasMember_const_iterator<T>::value and HasMember_size<T>::value;
};
template <typename T>
class IsContainer<T, false>
{
public:
    static constexpr auto value = false;
};

template <typename T, typename = void>
struct IsIterator
{
    static constexpr auto value = false;
};

template <typename T>
struct IsIterator<T,
                  std::enable_if_t<not std::is_same<typename std::iterator_traits<T>::value_type, void>::value and
                                   not std::is_same<T, const char*>::value>>
{
    static constexpr auto value = true;
};

template <typename T1, typename T2>
using IsSameDecayed = std::is_same<std::decay_t<T1>, std::decay_t<T2>>;

template <typename C, typename Ret>
using EnableIfHasFindMethod = std::enable_if_t<HasMember_find<C>::value, Ret>;
