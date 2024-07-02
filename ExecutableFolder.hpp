#pragma once

#include <string>

#include "FileName.hpp"

#ifdef _WIN32
#ifdef UNICODE
#include "WString.hpp"
#else
#include <Windows.h>
#endif
#elif defined(__linux__)
#include <limits.h>
#include <unistd.h>
#endif

inline auto getExecutableFolder()
{
    using namespace std;

#if defined(_WIN32) and defined(UNICODE)
    wchar_t
#else
    char
#endif
        buf[
#ifdef _WIN32
            MAX_PATH
#else
            PATH_MAX
#endif
    ];

#ifdef _WIN32
    GetModuleFileName(0, buf, sizeof(buf));
#elif defined(__linux__)
    (void)readlink("/proc/self/exe", buf, sizeof(buf));
#endif

#if defined(_WIN32) and defined(UNICODE)
    return toString({buf, wcsrchr(buf, PATH_DELIMITER)});
#else
    return string{buf, strrchr(buf, PATH_DELIMITER)};
#endif
}
