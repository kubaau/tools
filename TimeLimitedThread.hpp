#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>
#include <vector>

class TimeLimitedThreadRunner
{
    using Clock = std::chrono::high_resolution_clock;
    using Threads = std::vector<std::thread>;

public:
    using Func = std::function<void()>;
    using Funcs = std::vector<Func>;
    using Duration = Clock::duration;

    auto add(const Func& f, size_t count = 1)
    {
        while (count--)
            addOne(f);
    }

    auto runFor(const Clock::duration& dur)
    {
        using namespace std;
        {
            lock_guard lk{mtx};
            stop = Clock::now() + dur;
            cv.notify_all();
        }
        this_thread::sleep_for(dur);
        for (auto& t : threads)
            if (t.joinable())
                t.detach();
    }

    auto runFor(const Clock::duration& dur, const Funcs& funcs)
    {
        for (auto& f : funcs)
            addOne(f);
        runFor(dur);
    }

    auto runFor(const Clock::duration& dur, Func f)
    {
        addOne(std::move(f));
        runFor(dur);
    }

private:
    void addOne(Func f) { threads.emplace_back(&TimeLimitedThreadRunner::run, this, std::move(f)); }

    void run(Func f)
    {
        {
            std::unique_lock lk{mtx};
            cv.wait(lk, [this] { return stop != Clock::time_point{}; });
        }
        while (Clock::now() < stop)
            f();
    }

    std::mutex mtx;
    std::condition_variable cv;
    Clock::time_point stop;

    Threads threads;
};
