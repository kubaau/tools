#pragma once

template <class C, typename Key, typename Value>
auto valueOr(const C& c, const Key& key, const Value& default_val)
{
    const auto it = c.find(key);
    return it != cend(c) ? it->second : default_val;
}
