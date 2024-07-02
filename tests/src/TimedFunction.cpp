#include "TimedFunction.hpp"
#include "GtestWrapper.hpp"

TEST(TimedFunction, timed)
{
    auto f = [](auto time) { this_thread::sleep_for(time); };
    print(timed(f, 17ms));
    print(timed(f, 18ms));
    auto f_ret = [](auto time) {
        this_thread::sleep_for(time);
        return time.count();
    };
    print(timedRet(f_ret, 17ms));
    print(timedRet(f_ret, 18ms));
}
