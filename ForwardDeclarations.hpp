#pragma once

#include "IsStlContainer.hpp"
#include "TypeTraits.hpp"

template <class C>
void iota(C&, typename C::const_reference = 0);

template <class C, class UniformRandomBitGenerator>
auto shuffle(C&, UniformRandomBitGenerator&&);

template <class C>
auto sample_unstable(const C&, std::size_t);

template <class C, typename T>
auto find(const C&, const T&);

template <typename It, typename = EnableIf<IsIterator<It>::value>>
std::ostream& operator<<(std::ostream&, const std::pair<It, It>&);

template <class C, typename = EnableIf<IsStlContainer<C>::value and not HasMember_pop<C>::value>>
std::ostream& operator<<(std::ostream&, const C&);

template <class C, typename = EnableIf<IsStlContainer<C>::value and HasMember_pop<C>::value>, typename = int>
std::ostream& operator<<(std::ostream&, C);

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream&, const std::pair<T1, T2>&);

template <class C, class Generator>
auto generate(C&, Generator);
