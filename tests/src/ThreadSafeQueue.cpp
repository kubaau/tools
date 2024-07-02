#include "ThreadSafeQueue.hpp"
#include "Random.hpp"
#include "Repeat.hpp"
#include "ScopedThread.hpp"
#include "ThreadSafeLogger.hpp"

#include "GtestWrapper.hpp"

TEST(ThreadSafeQueue, tsq)
{
    ThreadSafeQueue<int> tsq;

    auto producer = [&] { tsq.push(randomInt(0, 10)); };
    auto consumer = [&] { DEBUG_LOG << tsq.pop(); };
    auto consumer_try = [&] {
        try
        {
            DEBUG_LOG << tsq.tryPop();
        }
        catch (const out_of_range& ex)
        {
            DEBUG_LOG << ex.what();
        }
    };

    {
        ScopedThread c{consumer};
        ScopedThread ct{consumer_try};
        this_thread::sleep_for(10ms);
        ScopedThread p{producer};
    }
    EXPECT_TRUE(tsq.empty());
}

TEST(ThreadSafeQueue, tsq_with_limit)
{
    ThreadSafeQueue<int> tsq{3};

    auto producer = [&] {
        repeat(6)
        {
            DEBUG_LOG << "Producer before: " << tsq;
            tsq.push(randomInt(0, 10));
            DEBUG_LOG << "Producer after: " << tsq;
        }
    };
    auto consumer = [&] {
        repeat(3)
        {
            this_thread::sleep_for(10ms);
            DEBUG_LOG << "Consumed: " << tsq.pop() << " " << tsq;
        }
    };
    auto consumer_try = [&] {
        try
        {
            DEBUG_LOG << "Try-consumed: " << tsq.tryPop() << " " << tsq;
        }
        catch (const out_of_range& ex)
        {
            DEBUG_LOG << ex.what();
        }
    };

    {
        ScopedThread c{consumer};
        ScopedThread ct{consumer_try};
        ScopedThread p{producer};
        ScopedThread ct2{consumer_try};
    }
    EXPECT_FALSE(tsq.empty());
}
