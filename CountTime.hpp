#pragma once

#include <boost/numeric/conversion/cast.hpp>
#include <chrono>

template <class T1, typename Count = typename T1::rep, class T2>
constexpr auto count(T2 time)
{
    return boost::numeric_cast<Count>(std::chrono::duration_cast<T1>(time).count());
}
