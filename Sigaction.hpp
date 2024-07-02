#pragma once

#include <csignal>
#include "ErrorChecks.hpp"

using Signal = int;
using Signals = std::set<Signal>;
using SigAction = decltype(sigaction::sa_sigaction);
#define SigActionSignature(Action) \
    void Action([[maybe_unused]] Signal signal, [[maybe_unused]] siginfo_t* info, [[maybe_unused]] void* ucontext)

namespace Detail
{
    inline auto createSigaction(SigAction action)
    {
        struct sigaction sigact = {};
        sigact.sa_sigaction = action;
        sigact.sa_flags = SA_RESTART | SA_SIGINFO;
        return sigact;
    }
} // namespace Detail

inline auto failedSigaction(int result)
{
    return result != 0;
}
GENERATE_REVERSE_CHECK(Sigaction)

inline void installSigaction(Signal signal, SigAction action)
{
    const auto sigact = Detail::createSigaction(action);
    constexpr auto ignore_old_sigact = nullptr;
    checkSigaction(sigaction(signal, &sigact, ignore_old_sigact));
}

inline void installSigaction(Signals signals, SigAction action)
{
    for (auto signal : signals)
        installSigaction(signal, action);
}
