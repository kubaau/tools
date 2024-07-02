#pragma once

#include <cassert>
#include <iostream>
#include "RandomContainers.hpp"
#include "RangeStlAlgorithms.hpp"
#include "Repeat.hpp"
#include "StackPop.hpp"

template <typename InputIt, typename OutputIt, class UnaryPred>
auto copyIf(InputIt begin, InputIt end, OutputIt out, UnaryPred pred, unsigned max_count)
{
    while (begin != end and max_count > 0)
    {
        if (pred(*begin))
        {
            *out++ = *begin;
            --max_count;
        }
        ++begin;
    }
}

template <class CFrom, class CTo, class UnaryPred>
auto copyIf(const CFrom& from, CTo& to, UnaryPred pred, unsigned max_count)
{
    using namespace std;
    return copyIf(cbegin(from), cend(from), end_inserter(to), move(pred), max_count);
}

template <class C, class UnaryPred>
auto copyIf(const C& c, UnaryPred pred, unsigned max_count)
{
    using namespace std;
    C result;
    copyIf(c, result, move(pred), max_count);
    return result;
}

template <class CFrom, class CTo>
auto copy_n_c(const CFrom& from, unsigned n, CTo& to)
{
    using namespace std;
    return copy_n(cbegin(from), n, end_inserter(to));
}

template <class CFrom, class CTo>
auto copy_n_s(const CFrom& from, unsigned n, CTo& to)
{
    using namespace std;
    return copy_n(cbegin(from), min({cend(from) - cbegin(from), cend(to) - cbegin(to), n}), begin(to));
}

template <class CFrom, class CTo>
auto copy_s(const CFrom& from, CTo& to)
{
    using namespace std;
    return copy_n_s(from, numeric_limits<unsigned>::max(), to);
}

template <class C, typename T, std::size_t size>
auto copyToCArray(const C& from, T (&to)[size])
{
    using namespace std;
    return copy(cbegin(from), cend(from), begin(to));
}

template <class C, typename T, std::size_t size>
auto copyToCArray_s(const C& from, T (&to)[size])
{
    using namespace std;
    return copy_n(cbegin(from), min(cend(from) - cbegin(from), size), begin(to));
}

template <class C, typename T>
auto erase(C& c, const T& value)
{
    using namespace std;
    return c.erase(remove(begin(c), end(c), value), end(c));
}

template <class C, typename T>
auto erase_one(C& c, const T& value)
{
    using namespace std;
    const auto it = find(c, value);
    if (it != end(c))
        c.erase(it);
}

/* won't work with bsearch - cannot cast pointer to iterator
template <class C, typename T>
auto erase_one_sorted(C& c, const T& value)
{
    using namespace std;
    if (auto ptr = bsearch(value, c))
        c.erase(static_cast<C::const_pointer>(ptr));
}
*/

template <class C, class UnaryPred>
auto erase_if(C& c, UnaryPred pred)
{
    using namespace std;
    return c.erase(remove_if(begin(c), end(c), move(pred)), end(c));
}

template <class C, class UnaryPred>
auto erase_one_if(C& c, UnaryPred pred)
{
    using namespace std;
    return c.erase(find(c, move(pred)));
}

template <typename It, class UniformRandomBitGenerator>
void shuffle_limited(It begin, It end, unsigned limit, UniformRandomBitGenerator&& g)
{
    using namespace std;

    limit = clamp(limit, 0u, static_cast<unsigned>(end - begin));
    for (auto i = 0u; i < limit; ++i)
    {
        const auto it = begin + i;
        iter_swap(it, it + randomInt(0, end - it - 1, forward<UniformRandomBitGenerator>(g)));
    }
}

template <typename It>
void shuffle_limited(It begin, It end, unsigned limit)
{
    return shuffle_limited(begin, end, limit, defaultRandomEngine());
}

template <class C, class UniformRandomBitGenerator>
void shuffle_limited(C& c, unsigned limit, UniformRandomBitGenerator&& g)
{
    using namespace std;
    shuffle_limited(begin(c), end(c), limit, forward<UniformRandomBitGenerator>(g));
}

template <class C>
void shuffle_limited(C& c, unsigned limit)
{
    shuffle_limited(c, limit, defaultRandomEngine());
}

template <class C>
auto forceUnique(C& c)
{
    using namespace std;
    return c.erase(unique(begin(c), end(c)), end(c));
}

template <class C, class BinaryPred>
auto forceUnique(C& c, BinaryPred pred)
{
    using namespace std;
    return c.erase(unique(begin(c), end(c), move(pred)), end(c));
}

template <class C1, class C2, class C3, class UnaryPred>
auto stable_partition_copy(C1 c1, C2& c2, C3& c3, UnaryPred pred)
{
    using namespace std;
    auto it = stable_partition(c1, move(pred));
    copy(cbegin(c1), it, end_inserter(c2));
    copy(it, cend(c1), end_inserter(c3));
}

template <class C, class UnaryPred>
auto stable_partition_copy(const C& c, UnaryPred pred)
{
    using namespace std;
    C result_true;
    C result_false;
    stable_partition_copy(c, result_true, result_false, move(pred));
    return make_pair(result_true, result_false);
}

template <class PopulationIterator, class SampleIterator, class Distance, class UniformRandomBitGenerator>
SampleIterator sample(
    PopulationIterator first, PopulationIterator last, SampleIterator out, Distance n, UniformRandomBitGenerator&& g)
{
    using namespace std;

    const Distance population_size = last - first;
    const auto indexes = shuffledIndexes(population_size, forward<UniformRandomBitGenerator>(g));

    vector<bool> should_out(population_size, false);

    const auto limit = min(n, population_size);
    for (Distance i = 0; i < limit; ++i)
        should_out[indexes[i]] = true;

    for (Distance i = 0; i < population_size; ++first)
        if (should_out[i++])
            *out++ = *first;

    return out;
}

template <class C1, class C2, class UniformRandomBitGenerator>
auto sample(const C1& c1, C2& c2, unsigned n, UniformRandomBitGenerator&& g)
{
    using namespace std;
    return sample(cbegin(c1), cend(c1), end_inserter(c2), n, g);
}

template <class C1, class C2>
auto sample(const C1& c1, C2& c2, unsigned n)
{
    return sample(c1, c2, n, defaultRandomEngine());
}

template <class C, class UniformRandomBitGenerator>
auto sample(const C& c, unsigned n, UniformRandomBitGenerator&& g)
{
    using namespace std;
    C ret(n);
    return sample(cbegin(c), cend(c), begin(ret), n, g);
}

template <class C>
auto sample(const C& c, unsigned n)
{
    return sample(c, n, defaultRandomEngine());
}

template <class PopulationIterator, class SampleIterator, class Distance, class UniformRandomBitGenerator>
SampleIterator sample_unstable(
    PopulationIterator first, PopulationIterator last, SampleIterator out, Distance n, UniformRandomBitGenerator&& g)
{
    using namespace std;

    const Distance population_size = last - first;
    const auto indexes = shuffledIndexes(population_size, forward<UniformRandomBitGenerator>(g));

    const auto limit = min(n, population_size);
    repeat(limit)* out++ = *(first + indexes[i]);

    return out;
}

template <class C1, class C2, class UniformRandomBitGenerator>
auto sample_unstable(const C1& c1, C2& c2, std::size_t n, UniformRandomBitGenerator&& g)
{
    using namespace std;
    return sample_unstable(cbegin(c1), cend(c1), end_inserter(c2), n, g);
}

template <class C1, class C2>
auto sample_unstable(const C1& c1, C2& c2, std::size_t n)
{
    return sample_unstable(c1, c2, n, defaultRandomEngine());
}

template <class C, class UniformRandomBitGenerator>
auto sample_unstable(const C& c, std::size_t n, UniformRandomBitGenerator&& g)
{
    using namespace std;
    C ret(n);
    sample_unstable(cbegin(c), cend(c), begin(ret), n, g);
    return ret;
}

template <class C>
auto sample_unstable(const C& c, std::size_t n)
{
    return sample_unstable(c, n, defaultRandomEngine());
}

template <class InputIt, typename Size, class UnaryOp, typename = std::enable_if_t<not IsStlContainer<InputIt>::value>>
InputIt for_each_n(InputIt first, Size n, UnaryOp f)
{
    while (n--)
        f(*first++);
    return first;
}

template <class C, typename Size, class UnaryOp, typename = std::enable_if_t<IsStlContainer<C>::value>>
auto for_each_n(C& c, Size n, UnaryOp f)
{
    using namespace std;
    return for_each_n(begin(c), n, move(f));
}

template <class T>
auto destroy_at(T* p)
{
    p->~T();
}

template <class ForwardIt>
auto destroy(ForwardIt first, ForwardIt last)
{
    using namespace std;
    while (first != last)
        destroy_at(addressof(*first++));
}

template <class ForwardIt, class Size>
auto destroy_n(ForwardIt first, Size n)
{
    using namespace std;
    while (n--)
        destroy_at(addressof(*first++));
    return first;
}

template <class C, class Compare>
auto qsort(C& c, Compare comp)
{
    using namespace std;
    return qsort(&*begin(c), c.size(), sizeof(C::value_type), move(comp));
}

template <typename T>
auto cCompare(const void* lhs, const void* rhs)
{
    const auto lhs_val = *static_cast<const T*>(lhs);
    const auto rhs_val = *static_cast<const T*>(rhs);
    return lhs_val > rhs_val ? 1 : rhs_val > lhs_val ? -1 : 0;
}

template <class C>
auto qsort(C& c)
{
    using namespace std;
    return qsort(c, cCompare<C::value_type>);
}

template <typename T, class C, class Compare>
auto bsearch(const T& val, const C& c, Compare comp)
{
    using namespace std;
    return bsearch(&val, &*cbegin(c), c.size(), sizeof(C::value_type), move(comp));
}

template <typename T, class C>
auto bsearch(const T& val, const C& c)
{
    using namespace std;
    return bsearch(val, c, cCompare<C::value_type>);
}

template <typename T>
auto swapNoTemp(T& lhs, T& rhs)
{
    if (lhs != rhs)
    {
        lhs += rhs;
        rhs = lhs - rhs;
        lhs -= rhs;
    }
}

template <typename T>
auto swapNoTemp2(T& lhs, T& rhs)
{
    if (lhs != rhs)
        lhs -= rhs = (lhs += rhs) - rhs;
}

template <typename T>
auto swapNoTemp3(T& lhs, T& rhs)
{
    lhs = std::array<T, 2>{rhs, rhs = lhs}[0];
}

template <typename T>
auto swapNoTemp4(T& lhs, T& rhs)
{
    if (lhs != rhs)
        lhs ^= rhs ^= lhs ^= rhs;
}

template <typename T>
void sortStackOnly(std::stack<T>& s)
{
    auto& s1 = s;
    std::stack<T> s2;

    while (not s1.empty())
    {
        const auto val1 = pop(s1);

        while (not s2.empty())
        {
            const auto val2 = s2.top();
            if (val1 > val2)
            {
                break;
            }
            s2.pop();
            s1.push(val2);
        }
        s2.push(val1);
    }

    while (not s2.empty())
        s1.push(pop(s2));
}

inline auto countRepeated(const std::vector<int>& numbers)
{
    using namespace std;

    map<int, int> number_counts;
    for (auto n : numbers)
        ++number_counts[n];

    return count_if(number_counts, [](auto n) { return n.second > 1; });
}

inline size_t countPairs(const std::vector<int>& numbers, int k)
{
    using namespace std;

    if (k == 0)
        return countRepeated(numbers);

    size_t pairs_count = 0;
    unordered_set<int> unique_numbers(cbegin(numbers), cend(numbers));
    for (auto n : unique_numbers)
        pairs_count += unique_numbers.count(n + k);
    return pairs_count;
}

template <class C>
bool allUnique(const C& c)
{
    using namespace std;
    return adjacent_find(c) == cend(c);
}

template <class C>
auto allUniqueUnsortedNlogN(C c)
{
    using namespace std;
    sort(c);
    return allUnique(c);
}

template <class C>
auto allUniqueUnsortedN(const C& c)
{
    using namespace std;
    unordered_set<typename C::value_type> s;
    for (const auto& i : c)
        if (not s.insert(i).second)
            return false;
    return true;
}

template <class C>
void reestablishOrder(C& reordered, const C& original)
{
    auto sameOrderAsOriginal = [&original](const auto& lhs, const auto& rhs) {
        return find(original, lhs) < find(original, rhs);
    };
    sort(reordered, sameOrderAsOriginal);
}

template <class F, typename... Args>
auto runInLoop(unsigned n, F f, Args&&... args)
{
    using namespace std;
    while (--n)
        f(forward<Args>(args)...);
    return f(forward<Args>(args)...);
}

template <class C, class UnaryPred>
void printIf(const C& c, UnaryPred pred)
{
    using namespace std;
    copy_if(cbegin(c), cend(c), ostream_iterator<typename C::value_type>(cout, " "), move(pred));
}
