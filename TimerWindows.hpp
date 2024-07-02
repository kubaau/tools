#pragma once

#include "Typedefs.hpp"
#include "WindowsNoMinMax.hpp"

template <typename T>
auto asLargeIntegerPtr(T& value)
{
    return reinterpret_cast<LARGE_INTEGER*>(&value);
}

class TimerWindows
{
public:
    TimerWindows()
    {
        u64 counts_per_sec = 0;
        QueryPerformanceFrequency(asLargeIntegerPtr(counts_per_sec));
        seconds_per_count = 1.0 / counts_per_sec;

        reset();
    }

    auto delta() const { return delta_time; }
    auto total() const { return total_time; }

    void reset()
    {
        queryPerformanceCounter(last_tick);
        delta_time = 0;
        total_time = 0;
        unpause();
    }

    TimerWindows& tick()
    {
        u64 new_tick;
        queryPerformanceCounter(new_tick);
        if (paused)
            delta_time = 0;
        else
        {
            delta_time = (new_tick - last_tick) * seconds_per_count;
            total_time += delta_time;
        }
        last_tick = new_tick;
        return *this;
    }

    void pause() { paused = true; }
    void unpause() { paused = false; }

private:
    void queryPerformanceCounter(u64& tick) { QueryPerformanceCounter(asLargeIntegerPtr(tick)); }

    double delta_time;
    double total_time;
    bool paused;
    u64 last_tick;
    double seconds_per_count;
};
