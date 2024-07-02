#pragma once

#include <chrono>
#include <iostream>
#include "TypeTraits.hpp"

#define ENABLE_FOR_TIME_UNITS typename = EnableIf<HasMember_period<T>::value>

// This class doesn't seem to have an obvious use case ATM TBH. Keeping it here just in case.
class Time
{
public:
    using Unit = std::chrono::nanoseconds;
    using rep = Unit::rep;
    using period = Unit::period;

    template <class T = Unit, ENABLE_FOR_TIME_UNITS>
    constexpr Time(T t = {}) : time(t)
    {
    }

    template <class T, ENABLE_FOR_TIME_UNITS>
    constexpr auto count() const
    {
        return T{*this}.count();
    }

    constexpr auto operator+() const { return *this; }
    constexpr auto operator-() const { return Time{-time}; }

    template <class T, ENABLE_FOR_TIME_UNITS>
    constexpr auto& operator+=(T other)
    {
        time += Time{other}.time;
        return *this;
    }

    template <class T, ENABLE_FOR_TIME_UNITS>
    constexpr auto& operator-=(T other)
    {
        return *this += (-other);
    }

    /*constexpr*/ auto& operator*=(rep rep)
    {
        time *= rep;
        return *this;
    }

    /*constexpr*/ auto& operator/=(rep rep)
    {
        time /= rep;
        return *this;
    }

    template <class T, ENABLE_FOR_TIME_UNITS>
    constexpr auto operator+(T other) const
    {
        return Time{other} += *this;
    }

    template <class T, ENABLE_FOR_TIME_UNITS>
    constexpr auto operator-(T other) const
    {
        Time t = *this;
        t -= other;
        return t;
    }

    /*constexpr*/ auto operator*(rep other) const
    {
        Time t = *this;
        t.time *= other;
        return t;
    }

    /*constexpr*/ auto operator/(rep other) const
    {
        Time t = *this;
        t.time /= other;
        return t;
    }

    constexpr auto operator==(Time other) const { return time == other.time; }
    constexpr auto operator<(Time other) const { return time < other.time; }
    constexpr auto operator<=(Time other) const { return time <= other.time; }

    template <class T, ENABLE_FOR_TIME_UNITS>
    constexpr operator T() const
    {
        return std::chrono::duration_cast<T>(time);
    }

private:
    Unit time;
};

template <class T, ENABLE_FOR_TIME_UNITS>
constexpr bool operator==(T lhs, Time rhs)
{
    return Time{lhs} == rhs;
}
template <class T, ENABLE_FOR_TIME_UNITS>
constexpr auto operator!=(T lhs, Time rhs)
{
    return not(lhs == rhs);
}
template <class T, ENABLE_FOR_TIME_UNITS>
constexpr auto operator<(T lhs, Time rhs)
{
    return Time{lhs} < rhs;
}
template <class T, ENABLE_FOR_TIME_UNITS>
constexpr auto operator<=(T lhs, Time rhs)
{
    return Time{lhs} <= rhs;
}
template <class T, ENABLE_FOR_TIME_UNITS>
constexpr auto operator>(T lhs, Time rhs)
{
    return not(lhs <= rhs);
}
template <class T, ENABLE_FOR_TIME_UNITS>
constexpr auto operator>=(T lhs, Time rhs)
{
    return not(lhs < rhs);
}

auto& operator<<(std::ostream& os, Time time)
{
    return os << time.count<Time::Unit>() << "ns";
}
