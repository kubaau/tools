#pragma once

#include <chrono>

template <class Ratio, typename T>
auto in(T value)
{
    return value * Ratio::den / Ratio::num;
}
inline auto inNanoseconds(double seconds)
{
    return in<std::nano>(seconds);
}
inline auto inMicroseconds(double seconds)
{
    return in<std::micro>(seconds);
}
inline auto inMilliseconds(double seconds)
{
    return in<std::milli>(seconds);
}
inline auto inMinutes(double seconds)
{
    using namespace std;
    return in<ratio<chrono::minutes::period::num>>(seconds);
}
inline auto inHours(double seconds)
{
    using namespace std;
    return in<ratio<chrono::hours::period::num>>(seconds);
}
