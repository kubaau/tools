#pragma once

template <typename T>
auto equals(const T& expected)
{
    return [&expected](const T& got) { return got == expected; };
}

template <typename T>
auto notEquals(const T& expected)
{
    return [&expected](const T& got) { return got != expected; };
}
