#pragma once

#include "ChronoWrappers.hpp"

class Timer
{
public:
    using Time = Duration::rep;

    Timer() { reset(); }

    auto delta() const { return delta_time.count(); }
    auto total() const { return total_time.count(); }
    auto deltaF() const { return static_cast<float>(delta()); }
    auto totalF() const { return static_cast<float>(total()); }

    void reset()
    {
        last_tick = now();
        delta_time = Duration::zero();
        total_time = delta_time;
        unpause();
    }

    Timer& tick()
    {
        const auto new_tick = now();
        if (paused)
            delta_time = Duration::zero();
        else
        {
            delta_time = new_tick - last_tick;
            total_time += delta_time;
        }
        last_tick = new_tick;
        return *this;
    }

    void pause() { paused = true; }
    void unpause() { paused = false; }

private:
    Duration delta_time;
    Duration total_time;
    bool paused;
    TimePoint last_tick;
};
