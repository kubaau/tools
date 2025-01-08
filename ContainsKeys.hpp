#pragma once

#include "RangeStlAlgorithms.hpp"

namespace Detail
{
    using namespace std;

    template <class C>
    auto keyFindWithHint(const C& c, typename C::const_iterator hint, const typename C::key_type& k, float)
    {
        return find(hint, cend(c), k);
    }

    template <class C>
    auto keyFindWithHint(const C& c, typename C::const_iterator hint, const typename C::key_type& k, int)
        -> EnableIfHasMappedType<C, typename C::const_iterator>
    {
        return find_if(hint, cend(c), [&k](const auto& item) { return item.first == k; });
    }
}

template <class C, class KeysC = std::initializer_list<typename C::key_type>>
auto containsKeys(const C& c, const KeysC& keys)
{
    return all_of(keys, [&c](const auto& k) { return c.contains(k); });
}

template <class C, class Keys = std::initializer_list<typename C::key_type>>
auto containsKeysOrdered(const C& c, const Keys& keys)
{
    auto hint = cbegin(c);
    return all_of(keys,
                  [&c, &hint](const auto& k)
                  {
                      hint = Detail::keyFindWithHint(c, hint, k, 0);
                      return hint != cend(c);
                  });
}
