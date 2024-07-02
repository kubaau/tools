#pragma once

#include "Numeric.hpp"

inline auto caesarShift(char c, int shift)
{
    const auto uc = static_cast<unsigned char>(c);

    if (not isalpha(uc))
        return c;

    const auto base = (islower(uc) ? 'a' : 'A');
    constexpr auto alphabet_length = 'z' - 'a' + 1;
    return static_cast<char>(base + mod(c + shift - base, alphabet_length));
}

inline auto caesarCipher(std::string s, int shift)
{
    return transform(move(s), [shift](auto c) { return caesarShift(c, shift); });
}
