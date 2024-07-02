#pragma once

template <typename T>
auto asPtr(void* ptr)
{
    return static_cast<T*>(ptr);
}

template <typename T1, typename T2>
auto as(const T2* ptr)
{
    return *reinterpret_cast<const T1*>(ptr);
}

template <typename T, typename Buffer>
auto as(const Buffer& data, int offset)
{
    return as<T>(data.data() + offset);
}
