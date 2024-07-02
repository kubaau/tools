#pragma once

#include <sstream>

template <class S>
inline auto clearStream(S& s)
{
    s.clear();
    s.str("");
}

template <typename T>
inline auto clear(std::basic_ostringstream<T>& s)
{
    clearStream(s);
}

template <typename T>
inline auto clear(std::basic_istringstream<T>& s)
{
    clearStream(s);
}
