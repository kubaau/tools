#pragma once

#include <cassert>
#include <mutex>

template <typename T, class Lock = std::mutex>
class Guarded
{
public:
    Guarded(T& v, Lock& l) : value{&v}, lock{&l} { lock->lock(); }
    ~Guarded()
    {
        if (lock)
            lock->unlock();
    }

    Guarded(const Guarded&) = delete;
    Guarded& operator=(const Guarded&) = delete;

    Guarded(Guarded&& other) : value{other.value}, lock{other.lock} { other.reset(); }
    Guarded& operator=(Guarded&& other)
    {
        if (this == &other)
            return *this;

        value = other.value;
        lock = other.lock;
        other.reset();
        return *this;
    }

    T& operator*() const { return *value; }

    operator bool() const { return value; }

private:
    void reset()
    {
        value = {};
        lock = {};
    }

    T* value;
    Lock* lock;
};

template <typename T, class Lock = std::mutex>
class GuardedSoft
{
public:
    GuardedSoft(T& v, Lock& l) : value{&v}, lock{&l} {}
    ~GuardedSoft() = default;

    GuardedSoft(const GuardedSoft&) = default;
    GuardedSoft& operator=(const GuardedSoft&) = default;

    GuardedSoft(GuardedSoft&& other) : value{other.value}, lock{other.lock} { other.reset(); }
    GuardedSoft& operator=(GuardedSoft&& other)
    {
        if (this == &other)
            return *this;

        value = other.value;
        lock = other.lock;
        other.reset();
        return *this;
    }

    T& operator*() const
    {
        assert(isGuarded());
        return *value;
    }

    operator bool() const { return value and isGuarded(); }

private:
    void reset()
    {
        value = {};
        lock = {};
    }

    auto isGuarded() const
    {
        if (lock->try_lock())
        {
            lock->unlock();
            return false;
        }
        return true;
    }

    T* value;
    Lock* lock;
};
