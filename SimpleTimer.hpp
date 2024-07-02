#pragma once

#include "ChronoWrappers.hpp"

class SimpleTimer
{
public:
    SimpleTimer() { reset(); }

    auto elapsed() const { return Duration{now() - start}.count(); }
    auto elapsedF() const { return static_cast<float>(Duration{now() - start}.count()); }

    void reset() { start = now(); }

private:
    TimePoint start;
};
