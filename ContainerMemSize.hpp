#pragma once

template <class C>
auto memSize(const C& c)
{
    return c.size() * sizeof(typename C::value_type);
}
