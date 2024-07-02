#include "Allocs.hpp"
#include <algorithm>
#include "GtestWrapper.hpp"

TEST(Allocs, malloc)
{
    auto p0 = mallocT<int>(0);
    free(p0);
    auto p1 = mallocT<int>(1);
    EXPECT_TRUE(p1);
    *p1 = 1;
    EXPECT_EQ(1, *p1);
    free(p1);
    auto p2 = mallocT<int>(2);
    EXPECT_TRUE(p2);
    *p2 = 2;
    *(p2 + 1) = 3;
    EXPECT_EQ(2, *p2);
    EXPECT_EQ(3, *(p2 + 1));
    free(p2);
}

TEST(Allocs, calloc)
{
    auto p0 = callocT<int>(0);
    free(p0);
    auto p1 = callocT<int>(1);
    EXPECT_TRUE(p1);
    EXPECT_EQ(0, *p1);
    *p1 = 1;
    EXPECT_EQ(1, *p1);
    free(p1);
    auto p2 = callocT<int>(2);
    EXPECT_TRUE(p2);
    EXPECT_EQ(0, *p2);
    EXPECT_EQ(0, *(p2 + 1));
    *p2 = 2;
    *(p2 + 1) = 3;
    EXPECT_EQ(2, *p2);
    EXPECT_EQ(3, *(p2 + 1));
    free(p2);
}

TEST(Allocs, realloc)
{
    auto pm = mallocT<u8>(4);
    generate(pm, pm + 4, []() -> u8 { return 1; });

    auto pr1 = reallocT<u16>(pm, 1);
    EXPECT_EQ(0x0101u, *pr1);

    auto pr2 = reallocT<u32>(pr1, 1);
    *pr2 = 2;
    EXPECT_EQ(2u, *pr2);

    auto pr3 = reallocT<u32>(pr2, 1);
    *pr3 = 3;
    EXPECT_EQ(3u, *pr3);

    free(pr3);
}

TEST(Allocs, aligned_alloc)
{
    auto pa = aligned_allocT<int>(1024, 1024 * 3);
    EXPECT_EQ(0u, reinterpret_cast<size_t>(pa) % 1024);
#ifndef _WIN32
    free(pa);
#else
    _aligned_free(pa);
#endif
}
