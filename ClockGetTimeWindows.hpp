#pragma once

#ifdef _WIN32
#include <chrono>
#include "Typedefs.hpp"
#include "WindowsNoMinMax.hpp"

namespace Detail
{
    inline timespec unixTime()
    {
        i64 win_time;
        GetSystemTimeAsFileTime(reinterpret_cast<FILETIME*>(&win_time));

        win_time -= 116444736000000000; // 1 Jan 1601 to 1 Jan 1970
        constexpr auto exp7 = 10000000;

        timespec ret;
        ret.tv_sec = win_time / exp7;
        ret.tv_nsec = win_time % exp7 * 100;
        return ret;
    }
}

inline auto clock_gettime(int, timespec* spec)
{
    using namespace std;

    static timespec start_spec;
    static i64 ticks_per_sec;
    static i64 start_ticks;
    static double ticks_to_nano;
    static auto initialized = false;
    if (not initialized)
    {
        start_spec = Detail::unixTime();
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&ticks_per_sec));
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&start_ticks));
        ticks_to_nano = static_cast<double>(nano::den) / ticks_per_sec;
        initialized = true;
    }

    i64 current_ticks;
    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&current_ticks));
    current_ticks -= start_ticks;
    spec->tv_sec = start_spec.tv_sec + current_ticks / ticks_per_sec;
    spec->tv_nsec = start_spec.tv_nsec + static_cast<long>((current_ticks % ticks_per_sec) * ticks_to_nano);
    if (spec->tv_nsec >= nano::den)
    {
        spec->tv_sec++;
        spec->tv_nsec -= nano::den;
    }
    return 0;
}
#endif
