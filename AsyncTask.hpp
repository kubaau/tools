#pragma once

#include <future>
#include <vector>

using AsyncTasks = std::vector<std::future<void>>;

template <typename... Args>
auto asyncTask(Args&&... args)
{
    using namespace std;
    return async(launch::async, forward<Args>(args)...);
}

inline void join(AsyncTasks& tasks)
{
    for (auto& task : tasks)
        task.get();
}
