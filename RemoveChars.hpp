#pragma once

#include "CustomRangeAlgorithms.hpp"

inline auto& removeCharSet(std::string& s, const std::unordered_set<char>& charsToRemove)
{
    erase_if(s, [&charsToRemove](auto c) { return charsToRemove.contains(c); });
    return s;
}

inline auto& removeChars(std::string& s, const std::string& charsToRemove)
{
    // setify
    using namespace std;
    unordered_set<char> charSet;
    copy(cbegin(charsToRemove), cend(charsToRemove), begin_inserter(charSet));
    return removeCharSet(s, charSet);

    // erase_if + contains
    // erase_if(s, [&charsToRemove](auto c) { return charsToRemove.contains(c); });
    // return s;

    // std + c++17
    // s.erase(std::remove_if(
    //            s.begin(), s.end(), [&charsToRemove](auto c) { return charsToRemove.find(c) != std::string::npos; }),
    //        s.end());
    // return s;
}
