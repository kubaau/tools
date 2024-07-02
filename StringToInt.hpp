#pragma once

#include <algorithm>
#include <iterator>
#include <sstream>
#include "Repeat.hpp"
#include "Typedefs.hpp"

constexpr auto toInt(char c)
{
    return c - '0';
}

inline auto toInt(const char* str)
{
    return std::stoi(str);
}

template <typename T = u8>
auto toVectorOfDigits(const std::string& str)
{
    const auto length = str.length();
    std::vector<T> ret(length);
    repeat(length) ret[i] = static_cast<T>(toInt(str[i]));
    return ret;
}

inline auto wordToByte(std::string word)
{
    constexpr auto ignore_str_end = nullptr;
    constexpr auto base = 16;
    return static_cast<Byte>(std::strtoul(word.c_str(), ignore_str_end, base));
}

inline auto hexStringToBytes(const std::string& str)
{
    using namespace std;

    Bytes bytes;
    istringstream ss{str};
    transform(istream_iterator<string>{ss}, {}, back_inserter(bytes), wordToByte);
    return bytes;
}
