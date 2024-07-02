#pragma once

#include <regex>
#include <sstream>
#include "ContainerFilter.hpp"

namespace Detail
{
    using CharDelims = std::set<char>;
    using Tokens = std::vector<std::string>;
}

inline auto unifyDelimiters(std::string s, const Detail::CharDelims& delims)
{
    if (delims.empty())
        throw std::logic_error{"Empty delimeter set provided"};

    for (auto& c : s)
        if (delims.count(c))
            c = front(delims);
    return s;
}

template <typename OutIt>
auto splitIt(const std::string& s, OutIt result, const Detail::CharDelims& delims = {' '})
{
    using namespace std;

    stringstream ss{unifyDelimiters(s, delims)};
    string item;
    while (getline(ss, item, front(delims)))
        if (not item.empty())
            *(result++) = item;
}

template <typename OutIt>
auto splitIt(const std::string& s, OutIt result, char delim)
{
    return splitIt(s, result, Detail::CharDelims{delim});
}

inline auto split(const std::string& s, const Detail::CharDelims& delims = {' '})
{
    using namespace std;
    Detail::Tokens tokens;
    splitIt(s, back_inserter(tokens), delims);
    return tokens;
}

inline auto split(const std::string& s, char delim)
{
    return split(s, Detail::CharDelims{delim});
}

inline auto split(const std::string& s, const std::regex& regex)
{
    std::sregex_token_iterator first{cbegin(s), cend(s), regex, -1}, last;
    return filter(Detail::Tokens{first, last}, [](const auto& token) { return not token.empty(); });
}

inline auto splitRegex(const std::string& s, const std::string& delim = "\\s+")
{
    return split(s, std::regex{delim});
}
