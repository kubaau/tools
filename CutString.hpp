#pragma once

#include <string>

namespace Detail
{
    inline auto getLengthAndCorrectN(std::string s, std::size_t& n)
    {
        const auto len = s.length();
        if (n > len)
            n = len;
        return len;
    }
}

inline auto cutFromBegin(std::string s, std::size_t n)
{
    const auto len = Detail::getLengthAndCorrectN(s, n);
    return s.substr(n, len - n);
}

inline auto cutFromEnd(std::string s, std::size_t n)
{
    const auto len = Detail::getLengthAndCorrectN(s, n);
    return s.substr(0, len - n);
}
