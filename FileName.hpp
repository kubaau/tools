#pragma once

#include <cstring>
#include "ConstexprString.hpp"

#ifndef _WIN32
#define PATH_DELIMITER '/'
#else
#define PATH_DELIMITER '\\'
#endif

template <int N>
constexpr auto shift(const char* str)
{
    return str + N;
}
constexpr int filenameIndex(const char* file, int index = 0, int slash_index = -1)
{
    return file[index] ? (file[index] == PATH_DELIMITER ? filenameIndex(file, index + 1, index) :
                                                          filenameIndex(file, index + 1, slash_index)) :
                         (slash_index + 1);
}
#define FILE_NAME_SHIFT shift<filenameIndex(__FILE__)>(__FILE__)

constexpr auto filenameIndexRchrConstexpr(const char* file)
{
    const auto rchr = strrchrConstexpr(file, PATH_DELIMITER);
    return rchr ? rchr + 1 : file;
}
#define FILE_NAME_RCHR_CONSTEXPR filenameIndexRchrConstexpr(__FILE__)

inline auto filenameIndexRchr(const char* file)
{
    const auto rchr = std::strrchr(file, PATH_DELIMITER);
    return rchr ? rchr + 1 : file;
}
#define FILE_NAME_RCHR filenameIndexRchr(__FILE__)

#define FILE_NAME FILE_NAME_RCHR_CONSTEXPR
