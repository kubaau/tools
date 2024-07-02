#include "AsyncTask.hpp"
#include "ContainerOperators.hpp"
#include "GtestWrapper.hpp"

using namespace RangeOperators;

TEST(AsyncTask, asyncTask)
{
    int i = 0;
    AsyncTasks tasks;
    tasks += asyncTask([&] { ++i; });
    tasks += asyncTask([&] { ++i; });
    join(tasks);
    EXPECT_EQ(2, i);
}
