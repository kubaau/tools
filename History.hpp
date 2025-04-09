#pragma once

#include <chrono>
#include <mutex>
#include <unordered_map>

namespace HistoryTypes
{
    using Clock = std::chrono::system_clock;
    using Timestamp = Clock::time_point;
    using ExpirationPeriod = Clock::duration;
    using PurgePeriod = ExpirationPeriod;

    template <typename T>
    using DefaultMap = std::unordered_map<T, Timestamp>;
}

template <typename T, class Map = HistoryTypes::DefaultMap<T>, class Mutex = std::mutex>
class History
{
    using Clock = HistoryTypes::Clock;
    using Timestamp = HistoryTypes::Timestamp;
    using ExpirationPeriod = HistoryTypes::ExpirationPeriod;
    using PurgePeriod = HistoryTypes::PurgePeriod;

public:
    History() noexcept : exp{exp_zero()}, prg{PurgePeriod::zero()} {}

    History(ExpirationPeriod expiration_period) noexcept : exp{std::move(expiration_period)}, prg{exp} {}

    History(ExpirationPeriod expiration_period, PurgePeriod purge_period) noexcept
        : exp{std::move(expiration_period)}, prg{std::move(purge_period)}
    {
    }

#define LOCK_HISTORY \
    std::lock_guard<Mutex> lock { mtx }

    auto contains(const T& val) const noexcept
    {
        LOCK_HISTORY;
        return has_expiration() ? contains_unexpired(val) : history.contains(val);
    }

    auto insert(T&& val)
    {
        LOCK_HISTORY;
        const auto ts = now();
        purge(ts);
        history.emplace(std::forward<T>(val), ts);
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

    auto purge() noexcept
    {
        LOCK_HISTORY;
        purge(now());
    }

    auto set_expiration_period(ExpirationPeriod p) noexcept
    {
        LOCK_HISTORY;
        exp = std::move(p);
    }

    auto set_purge_period(PurgePeriod p) noexcept
    {
        LOCK_HISTORY;
        prg = std::move(p);
    }

#undef LOCK_HISTORY

private:
    static auto now() noexcept { return Clock::now(); }

    static constexpr auto exp_zero() noexcept { return decltype(exp)::zero(); }
    static constexpr auto prg_zero() noexcept { return decltype(prg)::zero(); }

    auto has_expiration() const noexcept { return exp != exp_zero(); }

    auto is_expired(Map::value_type entry, const Timestamp& now) const noexcept { return entry.second + exp < now; }
    auto is_expired(Map::const_iterator it) const noexcept { return is_expired(*it, now()); }

    auto contains_unexpired(const T& val) const noexcept
    {
        const auto it = history.find(val);

        if (it == std::cend(history))
            return false;

        if (not is_expired(it))
            return true;

        const_cast<History*>(this)->history.erase(it);
        return false;
    }

    auto should_always_purge() const noexcept { return prg == prg_zero(); }

    auto should_purge_all() const noexcept { return exp < exp_zero(); }

    auto purge_all() noexcept { history.clear(); }

    auto purge_expired(const Timestamp& now) noexcept
    {
        if (not has_expiration())
            return;

        std::erase_if(history, [this, &now](const auto& entry) noexcept { return is_expired(entry, now); });
    }

    auto purge(const Timestamp& now) noexcept
    {
        if (not should_always_purge() and now <= next_purge)
            return;

        should_purge_all() ? purge_all() : purge_expired(now);

        next_purge = now + exp;
    }

    mutable Mutex mtx;
    Map history;
    ExpirationPeriod exp;
    PurgePeriod prg;
    Timestamp next_purge = now() + prg;
};
