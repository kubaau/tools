#include "FileCommon.hpp"

#include "FileFolder.hpp"
#include "GtestWrapper.hpp"

TEST(FileCommon, open_and_jump)
{
    auto file = openFile(file_folder + "ReadFile.bin");
    char c;

    jumpToEnd(file);
    EXPECT_TRUE(file.get(c).eof());

    file.clear();

    jumpToStart(file);
    file.get(c);
    EXPECT_EQ('1', c);

    jump(file, std::ios_base::beg);
    file.get(c);
    EXPECT_EQ('1', c);

    file.seekg(1);
    file.get(c);
    EXPECT_EQ('2', c);
}
