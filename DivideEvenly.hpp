#pragma once

#include <vector>

inline auto divideEvenly(std::size_t item_count, std::size_t bucket_count)
{
    using namespace std;

    vector<size_t> ret(bucket_count);

    if (ret.empty())
        return ret;

    const auto quot = item_count / bucket_count;
    const auto quot_plus1 = quot + 1;
    const auto rem = item_count % bucket_count;

    auto i = 0u;
    while (i < rem)
        ret[i++] = quot_plus1;
    while (i < bucket_count)
        ret[i++] = quot;
    return ret;
}

inline auto divideEvenly2(std::size_t item_count, std::size_t bucket_count)
{
    using namespace std;

    vector<size_t> ret;

    if (not bucket_count)
        return ret;

    const auto quot = item_count / bucket_count;
    ret.insert(end(ret), bucket_count, quot);
    const auto rem = item_count - quot * bucket_count;

    for (auto i = 0u; i < rem; ++i)
        ++ret[i];
    return ret;
}
