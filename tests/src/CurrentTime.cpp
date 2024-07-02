#include "CurrentTime.hpp"
#include "GtestWrapper.hpp"

TEST(CurrentTime, date)
{
    print(date());
    this_thread::sleep_for(17ms);
    print(date());
}

TEST(CurrentTime, hour)
{
    print(hour());
    this_thread::sleep_for(17ms);
    print(hour());
}
