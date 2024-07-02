#pragma once

#include <array>
#include <bitset>
#include <cmath>
#include "CustomRangeAlgorithms.hpp"
#include "ExtendedRangeStlAlgorithms.hpp"
#include "Typedefs.hpp"

inline auto factorial(unsigned n)
{
    auto result = 1u;
    while (n)
        result *= n--;
    return result;
}

template <typename Int>
auto isOdd(Int n)
{
    return n & 1;
}

template <typename Int>
auto isEven(Int n)
{
    return not isOdd(n);
}

inline auto powerN(int n, unsigned power)
{
    u64 result = 1;
    for (auto i = 0u; i < power; ++i)
        result *= n;
    return result;
}

inline auto powerLogN(int n, unsigned power)
{
    u64 result = 1;
    while (power)
    {
        if (isOdd(power))
        {
            result *= n;
            --power;
        }
        n *= n;
        power /= 2;
    }
    return result;
}

template <unsigned N>
auto primeSieve()
{
    using namespace std;

    bitset<N + 1> sieve;
    sieve.set();
    sieve[0] = false;
    if (sieve.size() > 1)
        sieve[1] = false;

    const auto limit = sqrt(N);
    for (int i = 2; i <= limit; ++i)
        if (sieve[i])
            for (unsigned j = i * i; j <= N; j += i)
                sieve[j] = false;

    return sieve;
}

template <unsigned N, typename Int = unsigned>
auto primesUpTo()
{
    std::vector<Int> result;

    const auto sieve = primeSieve<N>();
    for (unsigned i = 2; i <= N; ++i)
        if (sieve[i])
            result.push_back(i);

    return result;
}

template <typename T>
auto powerSet(const std::set<T>& values)
{
    using namespace std;
    set<set<T>> result;

    const vector<T> values_vec(cbegin(values), cend(values));
    const auto power = 1 << values.size();
    for (int i = 0; i < power; ++i)
    {
        set<T> set_to_add;
        auto number = i;
        int index = 0;
        while (number)
        {
            if (number & 1)
                set_to_add.insert(values_vec[index]);
            number >>= 1;
            ++index;
        }
        result.insert(set_to_add);
    }

    return result;
}

namespace DetailNumeric
{
    using namespace std;

    template <typename T>
    void powerSet2(const set<T>& values, set<set<T>>& result)
    {
        result.insert(values);
        for (auto i = 0u; i < values.size(); ++i)
        {
            auto values2 = values;
            auto it = begin(values2);
            advance(it, i);
            values2.erase(it);
            powerSet2(values2, result);
        }
    }
}

template <typename T>
auto powerSet2(const std::set<T>& values)
{
    using namespace std;
    set<set<T>> result;
    DetailNumeric::powerSet2(values, result);
    return result;
}

template <typename T>
std::set<std::set<T>> powerSet3(const std::set<T>& values, unsigned index = 0)
{
    using namespace std;
    set<set<T>> result;

    if (index == values.size())
        result.insert(set<T>{});
    else
    {
        result = powerSet3(values, index + 1);

        auto it = begin(values);
        advance(it, index);
        for (const auto& s : result)
        {
            set<T> ss{cbegin(s), cend(s)};
            ss.insert(*it);
            result.insert(ss);
        }
    }

    return result;
}

template <typename T>
auto gcd(T a, T b)
{
    while (true)
    {
        if (a == 0)
            return b;
        b %= a;
        if (b == 0)
            return a;
        a %= b;
    }
}

template <typename T>
auto lcm(T a, T b)
{
    const auto gcd_val = gcd(a, b);
    return gcd_val ? (a / gcd_val * b) : 0;
}

template <typename T>
auto addFractions(T numerator1, T denominator1, T numerator2, T denominator2)
{
    using namespace std;

    if (denominator1 == 0 or denominator2 == 0)
        return make_pair(0, 0);

    const auto denominator = lcm(denominator1, denominator2);
    const auto numerator = numerator1 * denominator / denominator1 + numerator2 * denominator / denominator2;
    const auto gcd_val = gcd(numerator, denominator);
    return make_pair(numerator / gcd_val, denominator / gcd_val);
}

template <typename T>
auto addFractions(std::pair<T, T> frac1, std::pair<T, T> frac2)
{
    return addFractions(frac1.first, frac1.second, frac2.first, frac2.second);
}

template <typename T>
auto fibAdd(T& lhs, T& rhs)
{
    lhs += rhs;
    swapNoTemp(lhs, rhs);
}

inline auto fibs(unsigned count)
{
    using namespace std;
    vector<unsigned> fibs(count, 1);
    if (count > 0)
        adjacent_difference(cbegin(fibs), prev(cend(fibs)), begin(fibs) + 1, plus<unsigned>());
    return fibs;
}

inline auto fib(unsigned n)
{
    const auto sqrt5 = std::sqrt(5);
    const auto a = (1 + sqrt5) / 2.0;
    const auto b = (1 - sqrt5) / 2.0;
    return static_cast<unsigned>((pow(a, n) - pow(b, n)) / sqrt5);
}

template <typename T, typename = std::enable_if_t<std::is_floating_point<T>::value>>
constexpr auto eq(T lhs, T rhs)
{
    using namespace std;
    return fabs(lhs - rhs) < numeric_limits<T>::epsilon();
}

template <typename T1, typename T2>
unsigned mod(T1 val, T2 m)
{
    const auto cpp_mod = val % m;
    return cpp_mod >= 0 ? cpp_mod : cpp_mod + std::abs(m);
}

template <typename Result = double, class It>
auto avg(It begin, It end)
{
    using namespace std;
    const auto count = end - begin;
    return count ? accumulate(begin, end, Result{}) / count : Result{};
}

template <typename Result = double, class C>
auto avg(const C& c)
{
    using namespace std;
    return avg<Result>(cbegin(c), cend(c));
}

template <typename Result = double, typename T>
auto avg(std::initializer_list<T> vals)
{
    using namespace std;
    return avg<Result>(cbegin(vals), cend(vals));
}

template <typename T>
auto pows(T val, unsigned max)
{
    using namespace std;
    vector<T> pows(max + 1, val);
    pows.front() = 1;
    partial_sum(next(cbegin(pows)), cend(pows), next(begin(pows)), multiplies<T>());
    return pows;
}

template <typename T>
constexpr auto maxNoIf(T lhs, T rhs)
{
    return (lhs + rhs + ((lhs - rhs) >> (sizeof(T) * 8 - 1) | 1) * (lhs - rhs)) / 2;
}

inline auto maxArr(unsigned lhs, unsigned rhs)
{
    return rhs ? std::array<unsigned, 2>{{lhs, rhs}}[1 - !!(lhs / rhs)] : lhs;
}

inline auto minArr(unsigned lhs, unsigned rhs)
{
    return lhs ? std::array<unsigned, 2>{{lhs, rhs}}[1 - !!(rhs / lhs)] : lhs;
}

template <class C>
auto domainExcept(const C& c)
{
    using namespace std;
    constexpr auto min = numeric_limits<typename C::value_type>::min();
    constexpr auto max = numeric_limits<typename C::value_type>::max();
    C domain(max - min);
    iota(domain, min);
    return set_difference(domain, c);
}
