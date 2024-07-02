#include "Lock.hpp"
#include "GtestWrapper.hpp"

TEST(Lock, lock)
{
    mutex mtx;
    {
        LOCK;
    }
    {
        UNIQUE_LOCK(lock);
    }
    mutex m1;
    LOCK_MTX(m1)
    mutex m2;
    UNIQUE_LOCK_MTX(lock, m2)
}
