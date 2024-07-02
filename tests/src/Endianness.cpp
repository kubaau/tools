#include "Endianness.hpp"
#include "DumpMemory.hpp"
#include "GtestWrapper.hpp"

TEST(Endianness, isLittleEndian)
{
    constexpr u16 val = 1;
    dumpMemory(&val);
    print(isLittleEndian());
}
