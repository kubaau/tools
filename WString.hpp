#pragma once

#include <Windows.h>

#include <string>

inline auto toString(const std::wstring& str)
{
    using namespace std;

    if (str.empty())
        return string{};

    const auto size = static_cast<int>(str.size());
    string ret(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, str.data(), size, ret.data(), size, nullptr, nullptr);
    return ret;
}

inline auto toWstring(const std::string& str)
{
    using namespace std;

    if (str.empty())
        return wstring{};

    const auto size = static_cast<int>(str.size());
    wstring ret(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.data(), size, ret.data(), size);
    return ret;
}
