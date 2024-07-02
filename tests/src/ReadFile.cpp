#include "ReadFile.hpp"

#include "FileFolder.hpp"
#include "GtestWrapper.hpp"

TEST(ReadFile, readBinaryFile)
{
    EXPECT_EQ((IOBuffer{'1', '2', '3'}), readBinaryFile(file_folder + "ReadFile.bin"));
}

TEST(ReadFile, readTextFile)
{
    EXPECT_EQ("ala\nma kota", readTextFile(file_folder + "ReadFile.txt"));
}
