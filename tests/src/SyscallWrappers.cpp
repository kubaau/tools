#ifndef _WIN32
#include <cxxabi.h>
#include <boost/core/demangle.hpp>
#include "ThreadSafeLogger.hpp"

using namespace std;

extern "C" void __real___cxa_throw(void*, type_info*, void (*)(void*)) __attribute__((noreturn));
extern "C" void __wrap___cxa_throw(void* ex, type_info* type, void (*dest)(void*))
{
    WARN_LOG << "Exception thrown of type: " << (type ? boost::core::demangle(type->name()) : "unknown");
    __real___cxa_throw(ex, type, dest);
}
#endif
