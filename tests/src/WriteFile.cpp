#include "WriteFile.hpp"

#include "GtestWrapper.hpp"
#include "ReadFile.hpp"

TEST(WriteFile, writeBinaryFile)
{
    IOBuffer data{'1', '2', '3'};
    constexpr auto path = "WriteFile.bin";
    writeBinaryFile(path, data);
    EXPECT_EQ(data, readBinaryFile(path));
}

TEST(WriteFile, writeTextFile)
{
    constexpr auto text = "ala\nma kota";
    constexpr auto path = "WriteFile.txt";
    writeTextFile(path, text);
    EXPECT_EQ(text, readTextFile(path));
}
