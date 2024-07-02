#pragma once

#include <thread>

class ScopedThread
{
    using thread = std::thread;

public:
    ScopedThread(thread t) : t(std::move(t)) {}

    template <typename... T>
    ScopedThread(T&&... args) : t(std::forward<T>(args)...)
    {
    }

    ~ScopedThread()
    {
        if (t.joinable())
            t.join();
    }

private:
    thread t;
};
