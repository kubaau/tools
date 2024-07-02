#include "BufferPool.hpp"
#include "GtestWrapper.hpp"

TEST(BufferPool, buffer_pool)
{
    BufferPool<IOBuffer> pool{4, 1};

    const auto b1 = pool.get();
    const auto b2 = pool.get();
    EXPECT_NE(b1, b2);
    *b1 = {3, 7};
    *b2 = {4};
    EXPECT_EQ(3, b1->front());
    EXPECT_EQ(7, b1->back());
    EXPECT_EQ(IOBuffer{4}, *b2);

    BufferPool pool_bytes{1};
    const auto b = pool_bytes.get();
    b->push_back(5);
    EXPECT_EQ(5, b->back());
}
