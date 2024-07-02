#pragma once

#include <cerrno>
#include <stdexcept>
#include "PtrMagic.hpp"
#include "ThreadSafeLogger.hpp"

inline void appendErrno(std::ostream& os)
{
    os << ", errno = " << errno << " (" << strerror(errno) << ")";
}

template <typename Result>
bool die(Name func_name, const Result& result)
{
    using namespace std;
    ostringstream oss;
    oss << func_name << " failed, return value = " << result;
    if (errno)
        appendErrno(oss);
    throw runtime_error(oss.str());
}

#define GENERATE_CHECK(Function)                                  \
    template <typename Result>                                    \
    void check##Function(const Result& result)                    \
    {                                                             \
        succeeded##Function(result) or die(__FUNCTION__, result); \
    }                                                             \
    template <typename Result>                                    \
    auto checked##Function(const Result& result)                  \
    {                                                             \
        check##Function(result);                                  \
        return result;                                            \
    }

#define GENERATE_REVERSE_CHECK(Function)           \
    template <typename Result>                     \
    bool succeeded##Function(const Result& result) \
    {                                              \
        return not failed##Function(result);       \
    }                                              \
    GENERATE_CHECK(Function)

inline void coKurwa(const std::exception& ex)
{
    ERROR_LOG << "!!! " << ex.what();
}

inline void nicKurwa()
{
    ERROR_LOG << "!!! Unknown exception";
}

#define LOG_EXCEPTIONS                                \
    catch (const std::exception& ex) { coKurwa(ex); } \
    catch (...) { nicKurwa(); }
