#pragma once

#include <utility>
#include "SimpleTimer.hpp"

template <typename F, typename... Args>
auto timed(F f, Args&&... args)
{
    using namespace std;
    SimpleTimer timer;
    f(forward<Args>(args)...);
    return timer.elapsed();
}

template <typename F, typename... Args>
auto timedRet(F f, Args&&... args)
{
    using namespace std;
    SimpleTimer timer;
    const auto ret = f(forward<Args>(args)...);
    return make_pair(ret, timer.elapsed());
}
