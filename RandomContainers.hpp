#pragma once

#include "ForwardDeclarations.hpp"
#include "Random.hpp"
#include "RangeStlAlgorithms.hpp"

template <class C, class Distribution>
void fillWithRandomValues(C& c, Distribution distribution)
{
    auto& dre = defaultRandomEngine();
    generate(c, [&distribution, &dre]() { return distribution(dre); });
}

template <class C, typename Int = int>
void fillWithRandomInts(C& c, Int min, Int max)
{
    return fillWithRandomValues(c, std::uniform_int_distribution<Int>{min, max});
}

template <class C, typename Float = float>
void fillWithRandomFloats(C& c, Float min, Float max)
{
    return fillWithRandomValues(c, std::uniform_real_distribution<Float>{min, max});
}

template <class C, class Distribution>
void fillWithRandomUniqueValues(C& c, Distribution distribution)
{
    auto& dre = defaultRandomEngine();
    using RandomValue = typename Distribution::result_type;
    std::unordered_set<RandomValue> randoms;
    generate(c, [&distribution, &dre, &randoms]() {
        RandomValue r;
        do
            r = distribution(dre);
        while (not randoms.insert(r).second);
        return r;
    });
}

template <class C, typename Int = int>
void fillWithRandomUniqueInts(C& c, Int min, Int max)
{
    std::vector<Int> rs(max - min + 1u);
    iota(rs, min);
    c = sample_unstable(rs, c.size());
}

template <class C, typename Float = float>
void fillWithRandomUniqueFloats(C& c, Float min, Float max)
{
    using namespace std;
    fillWithRandomUniqueValues(c, uniform_real_distribution<Float>{min, max});
}

template <typename Int = int>
auto randomInts(Int min, Int max, unsigned count)
{
    std::vector<Int> ret(count);
    fillWithRandomInts(ret, min, max);
    return ret;
}

template <typename Int = int>
auto randomUniqueInts(Int min, Int max, unsigned count)
{
    std::vector<Int> ret(count);
    fillWithRandomUniqueInts(ret, min, max);
    return ret;
}

template <typename Float = float>
auto randomFloats(Float min, Float max, unsigned count)
{
    std::vector<Float> ret(count);
    fillWithRandomFloats(ret, min, max);
    return ret;
}

template <typename Float = float>
auto randomUniqueFloats(Float min, Float max, unsigned count)
{
    std::vector<Float> ret(count);
    fillWithRandomUniqueFloats(ret, min, max);
    return ret;
}

template <typename Count, class UniformRandomBitGenerator>
auto shuffledIndexes(Count count, UniformRandomBitGenerator&& g)
{
    using namespace std;

    vector<unsigned> indexes(count);
    iota(indexes);
    shuffle(indexes, forward<UniformRandomBitGenerator>(g));
    return indexes;
}

template <typename Count>
auto shuffledIndexes(Count count)
{
    return shuffledIndexes(count, defaultRandomEngine());
}

template <class C, class UniformRandomBitGenerator>
auto randomIndex(const C& c, UniformRandomBitGenerator&& g)
{
    return randomInt(typename C::size_type{0}, c.size() - 1, std::forward<UniformRandomBitGenerator>(g));
}

template <class C>
auto randomIndex(const C& c)
{
    return randomIndex(c, defaultRandomEngine());
}

template <class C>
const auto& randomElement(const C& c)
{
    auto it = cbegin(c);
    advance(it, randomIndex(c));
    return *it;
}
