#include "FileChange.hpp"

#include "GtestWrapper.hpp"
#include "WriteFile.hpp"

constexpr auto file = "FileChange.txt";
/*
class FileChangeObserver : IObserver<std::filesystem::path>
{
public:
    void onFileChanged<file>() override { changed = true; }

    bool changed = false;
};

TEST(FileChange, FileChangeObserver)
{
    FileChangeObserverImpl fco;
    writeTextFile(file, "lol");
    EXPECT_TRUE(fco.changed);
}
*/
