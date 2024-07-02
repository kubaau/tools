#include "GtestWrapper.hpp"
#include "Pause.hpp"
#include "PrintGuru.hpp"
#include "PrintPikachu.hpp"
#include "TeeCout.hpp"

int main(int argc, char** argv)
{
#ifdef _WIN32
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    TeeCout tc{};
    InitGoogleTest(&argc, argv);
    // testing::internal::CaptureStdout();
    const auto failed_count = RUN_ALL_TESTS();
    // print(testing::internal::GetCapturedStdout());
    const auto args = readArgs(argc, argv);
    failed_count ? printGuru(args) : printPikachu(args);
#ifdef _WIN32
    pauseIO();
#endif
    return failed_count;
}
