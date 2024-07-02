#pragma once

#include <boost/core/demangle.hpp>

template <typename T>
auto demangle()
{
    return boost::core::demangle(typeid(T).name());
}

template <typename T>
auto demangle(const T& arg)
{
    return boost::core::demangle(typeid(arg).name());
}
