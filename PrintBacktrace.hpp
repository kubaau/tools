#pragma once

#include <execinfo.h>
#include <boost/core/demangle.hpp>
#include "Sigaction.hpp"
#include "SplitString.hpp"

namespace Detail
{
    inline auto demangleBacktraceSymbol(std::string s)
    {
        return boost::core::demangle(split(split(s, '(').back(), '+').front().c_str());
    }
} // namespace Detail

[[noreturn]] inline SigActionSignature(printBacktrace)
{
    using namespace std;

    array<void*, 20> bt;
    const auto caller_address = reinterpret_cast<ucontext_t*>(ucontext)->uc_mcontext.gregs[
#ifdef __i386__
        REG_EIP
#else
        REG_RIP
#endif
    ];

    ERROR_LOG << "Signal " << signal << " (" << strsignal(signal) << "), address is " << hex << info->si_addr
              << " from 0x" << caller_address << dec << ", pid = " << getpid();

    const auto bt_size = backtrace(bt.data(), bt.size());

    bt[1] = reinterpret_cast<void*>(caller_address); // overwrite sigaction with caller's address

    const auto bt_symbols = backtrace_symbols(bt.data(), bt_size);
    for (auto i = decltype(bt_size){1}; i < bt_size; ++i) // skip first stack frame (points here)
        ERROR_LOG << i << ": " << Detail::demangleBacktraceSymbol(bt_symbols[i]) << "(" << bt_symbols[i] << ")";
    free(bt_symbols);

    exit(EXIT_FAILURE);
}
