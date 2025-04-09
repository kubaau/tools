#pragma once

#include <chrono>
#include <mutex>
#include <string>
#include <unordered_map>

class HistorySimple
{
    using Clock = std::chrono::system_clock;
    using Timestamp = Clock::time_point;
    using ExpirationPeriod = Clock::duration;

    using Map = std::unordered_map<std::string, Timestamp>;
    using Mutex = std::mutex;

public:
    HistorySimple(ExpirationPeriod expiration_period = exp_zero()) noexcept : exp{std::move(expiration_period)} {}

#define LOCK_HISTORY \
    std::lock_guard<Mutex> lock { mtx }

    auto contains(const std::string& val) const noexcept
    {
        LOCK_HISTORY;
        return has_expiration() ? contains_unexpired(val) : history.contains(val);
    }

    auto insert(std::string&& val)
    {
        LOCK_HISTORY;
        history.emplace(std::forward<std::string>(val), now());
    }

    auto size() const noexcept
    {
        LOCK_HISTORY;
        return history.size();
    }

    auto empty() const noexcept
    {
        LOCK_HISTORY;
        return history.empty();
    }

    auto set_expiration_period(ExpirationPeriod p) noexcept
    {
        LOCK_HISTORY;
        exp = std::move(p);
    }

#undef LOCK_HISTORY

private:
    static Timestamp now() noexcept { return Clock::now(); }

    static constexpr ExpirationPeriod exp_zero() noexcept { return decltype(exp)::zero(); }

    bool has_expiration() const noexcept { return exp != exp_zero(); }

    bool is_expired(Map::value_type entry, const Timestamp& now) const noexcept { return entry.second + exp < now; }
    bool is_expired(Map::const_iterator it) const noexcept { return is_expired(*it, now()); }

    bool contains_unexpired(const std::string& val) const noexcept
    {
        const auto it = history.find(val);

        if (it == std::cend(history))
            return false;

        if (not is_expired(it))
            return true;

        const_cast<HistorySimple*>(this)->history.erase(it);
        return false;
    }

    mutable Mutex mtx;
    Map history;
    ExpirationPeriod exp;
};
