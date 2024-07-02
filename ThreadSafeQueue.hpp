#pragma once

#include <condition_variable>
#include "ForwardDeclarations.hpp"
#include "Lock.hpp"
#include "QueuePop.hpp"
#include "Typedefs.hpp"

// something stinks here (or in the tests)

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue(Count limit = 0) : limit(limit) {}

    void push(T&& item)
    {
        UNIQUE_LOCK(lock)
        while (limit and q.size() >= limit)
        {
            push_cond.wait(lock);
        }
        q.push(std::forward<T>(item));
        pop_cond.notify_one();
    }

    auto pop()
    {
        UNIQUE_LOCK(lock)
        pop_cond.wait(lock, [this] { return not q.empty(); });
        return popAndNotify();
    }

    auto tryPop()
    {
        LOCK;
        if (q.empty())
            throw std::out_of_range{"Queue empty"};
        return popAndNotify();
    }

    auto empty() const
    {
        LOCK;
        return q.empty();
    }

    friend auto& operator<<(std::ostream& os, const ThreadSafeQueue& tsq)
    {
        LOCK_MTX(tsq.mtx);
        return os << tsq.q;
    }

private:
    auto popAndNotify()
    {
        const auto front = ::pop(q);
        push_cond.notify_one();
        return front;
    }

    std::queue<T> q;
    Count limit;
    mutable std::mutex mtx;
    mutable std::condition_variable pop_cond;
    mutable std::condition_variable push_cond;
};
