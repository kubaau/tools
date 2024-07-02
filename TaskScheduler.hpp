#pragma once

#include <functional>
#include <memory>

#include "ChronoWrappers.hpp"
#include "CustomRangeAlgorithms.hpp"
#include "Lock.hpp"
#include "Repeat.hpp"

using Repetitions = int;
constexpr Repetitions unlimited_repetitions = -1;
constexpr auto no_delay = std::chrono::nanoseconds{};

class ScheduledTask
{
    using Task = std::function<void()>;
    using Delay = std::chrono::nanoseconds;
    using TimePoint = std::chrono::time_point<Clock>;

public:
    ScheduledTask(Task task, Delay delay = {}, Repetitions repetitions = 1)
        : task(std::move(task)), delay(delay), repetitions(repetitions)
    {
        reset();
    }

    void reset()
    {
        reschedule();
        repetitions_so_far = 0;
    }

    void launch()
    {
        if (not isReady())
            return;

        if (repetitions == unlimited_repetitions or ++repetitions_so_far < repetitions)
            reschedule();
        else
            disable();

        task(); // this needs to be last because if this task schedules another task and gets copied, the change
                // to "active" may be lost
    }

    void disable() { active = false; }

    bool isStale() const { return not active; }

private:
    void reschedule() { launch_time = now() + delay; }
    bool isReady() const { return active and now() >= launch_time; }

    Task task;
    Delay delay;
    Repetitions repetitions;
    Repetitions repetitions_so_far;
    TimePoint launch_time;
    bool active = true;
};

using ScheduledTaskPtr = std::weak_ptr<ScheduledTask>;

class TaskScheduler
{
    using Mutex = std::recursive_mutex;

public:
    template <typename... Args>
    ScheduledTaskPtr schedule(Args&&... args)
    {
        LOCK_REMTX(mtx);
        using namespace std;
        return tasks.emplace_back(make_unique<ScheduledTask>(forward<Args>(args)...));
    }

    void launch()
    {
        LOCK_REMTX(mtx);
        repeat(tasks.size()) tasks[i]->launch();
        removeStaleTasks();
    }

private:
    void removeStaleTasks()
    {
        erase_if(tasks, [](const auto& task) { return task->isStale(); });
    }

    std::vector<std::shared_ptr<ScheduledTask>> tasks;
    mutable Mutex mtx;
};
