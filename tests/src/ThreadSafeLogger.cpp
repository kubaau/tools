#include "ThreadSafeLogger.hpp"
#include "GtestWrapper.hpp"

TEST(ThreadSafeLogger, thread_safe_logger_op)
{
    V v = {1, 2, 3};
    TSL << v;

    S s = {3, 2, 1};
    TSL << s;

    M m{{1, 2}, {3, 4}, {5, 6}};
    TSL << m;

    TSL << v << " / " << s << " / " << m << " - wow!";
    LOG << v << " / " << s << " / " << m << " - wow!";

    LOG << 1;
    LOG << 2;
    TSL << 1;
    TSL << 2;

    vector<thread> ts(10);
    for (auto& t : ts)
        t = thread([&] {
            // for (int j = 0; j < 10; ++j)
            //    LOG << t.get_id() << " " << j;
        });

    for (auto& t : ts)
        t.join();
}

static string foo()
{
    FUNCTION_LOG;
    return __FUNCTION__;
}

TEST(ThreadSafeLogger, enable_disable)
{
    enableDebugLogs(EnableDebugLogs::NO);
    DEBUG_LOG << "no";
    enableDebugLogs(EnableDebugLogs::YES);
    DEBUG_LOG << "yes";
    enableDebugLogs(EnableDebugLogs::NOT_NOW);
    DEBUG_LOG << "yes";
    enableDebugLogs(EnableDebugLogs::NO);
    DEBUG_LOG << "no";
}

TEST(ThreadSafeLogger, op_called_recursively)
{
    enableDebugLogs(EnableDebugLogs::YES);
    DEBUG_LOG << foo();
    INFO_LOG << foo();
    WARN_LOG << foo();
    ERROR_LOG << foo();
}

TEST(ThreadSafeLogger, debug_var)
{
    enableDebugLogs(EnableDebugLogs::YES);
    auto xyz = 123;
    DEBUG_LOG_VAR(xyz);
    DEBUG_LOG_VAR(xyz) DEBUG_VAR(xyz);
    DEBUG_LOG DEBUG_VAR(xyz) DEBUG_VAR(xyz);
}

TEST(ThreadSafeLogger, thread_name)
{
    INFO_LOG << "fest";
    threadName("test");
    INFO_LOG << "best";
    threadName();
    INFO_LOG << "west";
}

TEST(ThreadSafeLogger, if_else)
{
    enableDebugLogs(EnableDebugLogs::NO);
    bool b = true;
    if (b)
        DEBUG_LOG << "aaa";
    else
        b = false;
    EXPECT_TRUE(b);
    enableDebugLogs(EnableDebugLogs::YES);
}
