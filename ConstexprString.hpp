#pragma once

namespace Detail
{
    constexpr auto strchrConstexprBase(const char* s, int c, bool nul)
    {
        const auto cc = static_cast<char>(c);

        do
        {
            if (*s == cc)
                return s;
        } while (*++s);

        return nul ? s : nullptr;
    }
}

constexpr auto strchrConstexpr(const char* s, int c)
{
    return Detail::strchrConstexprBase(s, c, false);
}

constexpr auto strchrnulConstexpr(const char* s, int c)
{
    return Detail::strchrConstexprBase(s, c, true);
}

constexpr auto strrchrConstexpr(const char* s, int c)
{
    const auto cc = static_cast<char>(c);

    decltype(s) ret = nullptr;

    do
    {
        if (*s == cc)
            ret = s;
    } while (*++s);

    return ret;
}
