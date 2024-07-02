#include "DumpMemory.hpp"

#include "GtestWrapper.hpp"

TEST(DumpMemory, toBinary)
{
    EXPECT_EQ("00001011", toBinary(Byte{11}));
    EXPECT_EQ("01111010", toBinary(Byte{0x7A}));
    EXPECT_EQ("0000000000001011", toBinary(u16{11}));
    EXPECT_EQ("0000111101111010", toBinary(u16{0x0F7A}));
    EXPECT_EQ("11111111", toBinary(static_cast<Byte>(-1)));
    EXPECT_EQ("11111110", toBinary(static_cast<Byte>(-2)));
    EXPECT_EQ("1111111111110101", toBinary(i16{-11}));
    EXPECT_EQ("1111000010000110", toBinary(i16{-0x0F7A}));
    print(toBinary(0xABCDEFFF));
}

TEST(DumpMemory, dumpMemory_deducedByteCount)
{
    struct S
    {
        int n = 7;
        char c = 0x7A;
    };
    S s;
    print(dumpMemory(&s));
}

TEST(DumpMemory, dumpMemory_givenByteCount)
{
    V v = {1, 2, 3};
    print(dumpMemory(v.data(), MemDumpType::FULL, (v.size() - 1) * sizeof(V::value_type)));
}

TEST(DumpMemory, dumpMemory_container)
{
    V v = {1, 2, 3};
    print(dumpMemory(v));
}
