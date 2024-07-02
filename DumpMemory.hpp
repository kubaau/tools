#pragma once

#include <cstring>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "BitCount.hpp"
#include "IsStlContainer.hpp"
#include "PtrMagic.hpp"
#include "Repeat.hpp"
#include "Typedefs.hpp"

template <typename T>
auto toBinary(T val)
{
    using namespace std;
    ostringstream oss;
    constexpr auto bits = bitsIn<T>();
    constexpr auto mask = 1 << (bits - 1);
    for (auto i = 0u; i < bits; ++i, val <<= 1)
        oss << !!(val & mask);
    return oss.str();
}

enum class MemDumpType
{
    SIMPLE,
    FULL
};

template <typename T>
auto dumpMemory(const T* ptr, MemDumpType type = MemDumpType::FULL, std::size_t byte_count = sizeof(T))
{
    using namespace std;
    ostringstream oss;
    constexpr auto width =
#ifdef PRINT_BYTE_AS_HEX
        2;
    oss.fill('0');
    oss.setf(ios::hex, ios::basefield);
    oss.setf(ios::uppercase);
#else
        3;
#endif
    const auto byte = asBytePtr(ptr);
    if (type == MemDumpType::SIMPLE)
        repeat(byte_count) oss << setw(width) << +(byte[i]) << " ";
    else
        repeat(byte_count) oss << setw(width) << i << " --- " << setw(width) << +(byte[i]) << " --- "
                               << toBinary(byte[i]) << endl;
    return oss.str();
}

template <class C, typename = std::enable_if_t<IsStlContainer<C>::value>>
auto dumpMemory(const C& c, MemDumpType type = MemDumpType::FULL)
{
    return dumpMemory(c.data(), type, c.size() * sizeof(typename C::value_type));
}
