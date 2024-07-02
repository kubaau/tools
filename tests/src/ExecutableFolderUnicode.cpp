#ifdef _WIN32
#define UNICODE
#include "ExecutableFolder.hpp"
#include "GtestWrapper.hpp"

TEST(ExecutableFolderUnicode, get_executable_folder)
{
    print(getExecutableFolder());
}
#endif
