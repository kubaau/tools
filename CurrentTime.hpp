#pragma once

#include <iomanip>
#include <sstream>
#include "ChronoWrappers.hpp"
#include "ClockGetTimeWindows.hpp"
#include "CutString.hpp"

namespace Detail
{
    inline auto currentNanoseconds()
    {
        timespec ts;
        clock_gettime(0, &ts);
        return ts.tv_nsec / 100;
    }
}

inline auto date()
{
    using namespace std;
    using namespace chrono;

    const auto time_t = system_clock::to_time_t(system_clock::now());
    const auto tm = *localtime(&time_t);

    ostringstream oss;

    oss << setfill('0');
    oss << setw(2) << tm.tm_mday << ".";
    oss << setw(2) << tm.tm_mon + 1 << ".";
    oss << tm.tm_year + 1900 << " ";
    oss << setw(2) << tm.tm_hour << ":";
    oss << setw(2) << tm.tm_min << ":";
    oss << setw(2) << tm.tm_sec << ".";
    oss << setw(7) << Detail::currentNanoseconds();

    return oss.str();
}

inline auto hour()
{
    return cutFromBegin(date(), 11);
}
