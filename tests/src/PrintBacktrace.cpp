#ifndef _WIN32
#include "PrintBacktrace.hpp"
#include "GtestWrapper.hpp"

void foo3(char)
{
    char* null = nullptr;
    *null = 1;
}

void foo2()
{
    foo3('x');
}

void foo1(int)
{
    foo2();
}

void foo1() {}

TEST(PrintBacktrace, bt)
{
    installSigaction(SIGSEGV, printBacktrace);
    //foo1(1);
}
#endif
