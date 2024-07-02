#pragma once

#ifndef DEFINITELY_SINGLE_THREAD
#include <mutex>
#include <thread>
#endif

#include "CurrentTime.hpp"
#include "EnumToUnderlying.hpp"
#include "FileName.hpp"
#include "OutputOperators.hpp"
#include "Print.hpp"
#include "StringStream.hpp"

#ifndef DEFINITELY_SINGLE_THREAD
inline auto threadHexId()
{
    using namespace std;
    ostringstream oss;
    oss << "0x" << hex << this_thread::get_id();
    return oss.str();
}

inline auto threadName(std::string name = {})
{
    thread_local auto thread_name = threadHexId();
    if (not name.empty())
        thread_name = name;
    return thread_name;
}
#endif

class ThreadSafeLogger
{
#ifndef DEFINITELY_SINGLE_THREAD
    using mutex = std::recursive_mutex;
#endif

public:
    static auto& instance()
    {
#ifndef DEFINITELY_SINGLE_THREAD
        static mutex mtx;
        static ThreadSafeLogger instance{mtx};
#else
        static ThreadSafeLogger instance;
#endif
        return instance;
    }

#ifndef DEFINITELY_SINGLE_THREAD
    ThreadSafeLogger(ThreadSafeLogger&& moved) noexcept : mtx(moved.mtx), oss(std::move(moved.oss))
#else
    ThreadSafeLogger(ThreadSafeLogger&& moved) noexcept : oss(std::move(moved.oss))
#endif
    {
        moved.is_alive = false;
    }
    ~ThreadSafeLogger()
    {
        if (is_alive)
        {
            print(oss.str());
            clear(oss);
#ifndef DEFINITELY_SINGLE_THREAD
            mtx.unlock();
#endif
        }
    }

    template <typename T>
    void log(const T& what)
    {
        oss << what;
    }

#ifndef DEFINITELY_SINGLE_THREAD
    void lock() { mtx.lock(); }
#endif

private:
#ifndef DEFINITELY_SINGLE_THREAD
    ThreadSafeLogger(mutex& mtx) : mtx(mtx) {}

    mutex& mtx;
#else
    ThreadSafeLogger() {}
#endif
    std::ostringstream oss;
    bool is_alive = true;
};

template <typename T>
ThreadSafeLogger operator<<(ThreadSafeLogger&& logger, const T& what)
{
    using namespace std;
    logger.log(what);
    return move(logger);
}

template <typename T>
ThreadSafeLogger operator<<(ThreadSafeLogger& logger, const T& what)
{
#ifndef DEFINITELY_SINGLE_THREAD
    logger.lock();
#endif
    return std::move(logger) << what;
}

enum class EnableDebugLogs
{
    NO,
    YES,
    NOT_NOW
};
inline auto enableDebugLogs(EnableDebugLogs enable = EnableDebugLogs::NOT_NOW)
{
    static bool enable_debug_logs =
#ifdef _DEBUG
        true;
#else
        false;
#endif
    if (enable != EnableDebugLogs::NOT_NOW)
        enable_debug_logs = toUnderlying(enable);
    return enable_debug_logs;
}

#define TSL ThreadSafeLogger::instance()
#define LOG_PREFIX hour()
#ifndef DEFINITELY_SINGLE_THREAD
#define LOG_POSTFIX "/" << threadName() << "/" << FILE_NAME << ":" << __LINE__ << "/" << __FUNCTION__ << ":\t"
#else
#define LOG_POSTFIX "/" << FILE_NAME << ":" << __LINE__ << "/" << __FUNCTION__ << ":\t"
#endif
#define LOG TSL << LOG_PREFIX << LOG_POSTFIX

#define DEBUG_LOG                 \
    if (not enableDebugLogs()) {} \
    else                          \
        TSL << LOG_PREFIX << "/DBG" << LOG_POSTFIX
// do not remove this empty if branch; consider where the else belongs:
// if (cond)
//     DEBUG_LOG << "";
// else
//     foo();
// if logging is not in the else branch, then calling foo() depends on enableDebugLogs()

#define FUNCTION_LOG DEBUG_LOG << ""
#define INFO_LOG TSL << LOG_PREFIX << "/INF" << LOG_POSTFIX
#define WARN_LOG TSL << LOG_PREFIX << "/WRN" << LOG_POSTFIX
#define ERROR_LOG TSL << LOG_PREFIX << "/ERR" << LOG_POSTFIX

#define DEBUG_VAR(var) << "[" << #var " = " << var << "]"
#define DEBUG_LOG_VAR(var) DEBUG_LOG DEBUG_VAR(var)
