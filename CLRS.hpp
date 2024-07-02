#pragma once

#include "Numeric.hpp"
#include "RandomContainers.hpp"

template <typename It>
void insertionSort(It begin, It end)
{
    for (auto j = 1; j < end - begin; ++j)
    {
        const auto key = *(begin + j);
        int i = j - 1;
        while (i >= 0 and *(begin + i) > key)
        {
            *(begin + 1 + i) = *(begin + i);
            --i;
        }
        *(begin + 1 + i) = key;
    }
}

template <class C>
void insertionSort(C& c)
{
    using namespace std;
    insertionSort(begin(c), end(c));
}

template <typename It>
void mergeClrs(It begin, It mid, It end)
{
    using namespace std;

    using C = vector<typename It::value_type>;
    C left(begin, mid);
    C right(mid, end);

    auto i = 0u;
    auto j = 0u;
    for (auto it = begin; it != end; ++it)
    {
        if (i == left.size())
            *it = right[j++];
        else if (j == right.size())
            *it = left[i++];

        else if (left[i] <= right[j])
            *it = left[i++];
        else
            *it = right[j++];
    }
}

template <typename It>
void mergeSort(It begin, It end)
{
    const auto span = end - begin;
    if (span > 1)
    {
        const auto mid = begin + span / 2;
        mergeSort(begin, mid);
        mergeSort(mid, end);
        mergeClrs(begin, mid, end);
    }
}

template <class C>
void mergeSort(C& c)
{
    using namespace std;
    mergeSort(begin(c), end(c));
}

template <typename It>
void bubbleSort(It begin, It end)
{
    using namespace std;

    if (end - begin < 2)
        return;

    const auto last = end - 1;
    for (auto it = begin; it != last; ++it)
        for (auto jt = last; jt != it; --jt)
        {
            const auto prev = jt - 1;
            if (*jt < *prev)
                iter_swap(jt, prev);
        }
}

template <class C>
void bubbleSort(C& c)
{
    using namespace std;
    bubbleSort(begin(c), end(c));
}

template <typename It>
void selectionSort(It begin, It end)
{
    using namespace std;

    if (end - begin < 2)
        return;

    const auto last = end - 1;
    for (auto it = begin; it != last; ++it)
        iter_swap(it, min_element(it, end));
}

template <class C>
void selectionSort(C& c)
{
    using namespace std;
    selectionSort(begin(c), end(c));
}

template <typename It>
struct MaxSubarrayResult
{
    It begin;
    It end;
    typename It::value_type sum;
};

template <typename It>
MaxSubarrayResult<It> maxCrossingSubarray(It begin, It mid, It end)
{
    using namespace std;
    using T = typename It::value_type;

    T left_sum = numeric_limits<T>::min();
    T sum = 0;

    It max_left = mid;
    for (auto i = mid - begin - 1; i >= 0; --i)
    {
        sum += *(begin + i);
        if (sum > left_sum)
        {
            left_sum = sum;
            max_left = begin + i;
        }
    }

    T right_sum = numeric_limits<T>::min();
    sum = 0;

    It max_right = mid;
    for (auto it = mid; it != end; ++it)
    {
        sum += *it;
        if (sum > right_sum)
        {
            right_sum = sum;
            max_right = it + 1;
        }
    }

    return {max_left, max_right, left_sum + right_sum};
}

template <class C>
auto maxCrossingSubarray(const C& c)
{
    using namespace std;
    return maxCrossingSubarray(cbegin(c), cmid(c), cend(c));
}

template <typename It>
MaxSubarrayResult<It> maxSubarray(It begin, It end)
{
    if (begin == end)
        return {begin, end, typename It::value_type{}};

    if (begin + 1 == end)
        return {begin, end, *begin};

    const auto middle = mid(begin, end);
    const auto left_result = maxSubarray(begin, middle);
    const auto right_result = maxSubarray(middle, end);
    const auto crossing_result = maxCrossingSubarray(begin, middle, end);
    if (left_result.sum >= right_result.sum and left_result.sum >= crossing_result.sum)
        return left_result;
    if (right_result.sum >= left_result.sum and right_result.sum >= crossing_result.sum)
        return right_result;
    else
        return crossing_result;
}

template <class C>
auto maxSubarray(const C& c)
{
    using namespace std;
    return maxSubarray(cbegin(c), cend(c));
}

template <class C>
void permuteBySorting(C& c)
{
    using namespace std;

    struct Helper
    {
        typename C::value_type value;
        unsigned priority;

        bool operator<(const Helper& other) { return priority < other.priority; }
    };

    vector<Helper> helpers(c.size());
    auto dre = defaultRandomEngine();
    auto rid = uniform_int_distribution<unsigned>{};
    auto it = cbegin(c);
    generate(helpers, [&dre, &rid, &it]() { return Helper{*it++, rid(dre)}; });
    sort(helpers);
    auto ith = cbegin(helpers);
    for (auto& i : c)
        i = ith++->value;
}

inline auto heapParent(int index)
{
    return (index - 1) >> 1;
}
inline auto heapLeft(int index)
{
    return index * 2 + 1;
}
inline auto heapRight(int index)
{
    return heapLeft(index) + 1;
}

template <class C>
void maxHeapify(C& c, int index, int heap_size = -1)
{
    using namespace std;

    if (heap_size < 0)
        heap_size = static_cast<int>(c.size());

    const auto left = heapLeft(index);
    const auto right = heapRight(index);
    auto largest = index;

    if (left < heap_size and c[left] > c[largest])
        largest = left;
    if (right < heap_size and c[right] > c[largest])
        largest = right;

    if (largest != index)
    {
        swap(c[index], c[largest]);
        maxHeapify(c, largest, heap_size);
    }
}

template <class C>
auto isMaxHeap(const C& c)
{
    auto i = 0u;
    for (; i < c.size() / 2 - 1; ++i)
        if (c[i] < c[heapLeft(i)] or c[i] < c[heapRight(i)])
            return false;
    if (c[i] < c[heapLeft(i)] or (isOdd(c.size()) and c[i] < c[heapRight(i)]))
        return false;
    return true;
}

template <class C>
void buildMaxHeap(C& c)
{
    for (auto i = static_cast<int>(c.size() / 2); i >= 0; --i)
        maxHeapify(c, i);
}

template <class C>
void heapSort(C& c)
{
    using namespace std;

    buildMaxHeap(c);
    for (auto i = static_cast<int>(c.size() - 1); i > 0; --i)
    {
        swap(c[0], c[i]);
        maxHeapify(c, 0, i);
    }
}

template <class C>
auto heapMax(const C& c)
{
    return c.front();
}

template <class C>
auto heapPopMax(C& c)
{
    const auto max = heapMax(c);
    c.front() = c.back();
    c.pop_back();
    maxHeapify(c, 0);
    return max;
}

template <class C>
auto heapIncreaseKey(C& c, int index, typename C::const_reference key)
{
    using namespace std;

    c[index] = key;
    while (index > 0)
    {
        const auto parent = heapParent(index);
        if (c[index] <= c[parent])
            break;
        swap(c[index], c[parent]);
        index = parent;
    }
}

template <typename C>
auto maxHeapInsert(C& c, typename C::const_reference key)
{
    using namespace std;
    c.insert(end(c), numeric_limits<typename C::value_type>::min());
    heapIncreaseKey(c, static_cast<int>(c.size() - 1), key);
}

template <class C>
void buildMaxHeap2(C& c)
{
    using namespace std;

    C heap;
    for (const auto& i : c)
        maxHeapInsert(heap, i);
    swap(c, heap);
}

template <typename It>
auto isPartitioned(It begin, It mid, It end)
{
    using namespace std;
    while (begin != mid)
        if (*begin++ > *mid)
            return false;
    while (end != mid)
        if (*--end < *mid)
            return false;
    return true;
}

template <class C>
auto isPartitioned(const C& c, typename C::const_iterator mid)
{
    using namespace std;
    return isPartitioned(cbegin(c), mid, cend(c));
}

template <typename It>
auto partition(It begin, It end)
{
    using namespace std;

    if (end - begin < 2)
        return begin;

    const auto last_it = end - 1;
    auto i = begin;
    for (auto it = begin; it != last_it; ++it)
        if (*it <= *last_it)
            iter_swap(i++, it);
    iter_swap(i, last_it);
    return i;
}

template <class C>
auto partition(C& c)
{
    using namespace std;
    return partition(begin(c), end(c));
}

template <typename It>
auto randomizedPartition(It begin, It end)
{
    if (end - begin < 2)
        return begin;

    iter_swap(end - 1, begin + randomInt(0u, static_cast<unsigned>(end - 1 - begin)));
    return partition(begin, end);
}

template <class C>
auto randomizedPartition(C& c)
{
    using namespace std;
    return randomizedPartition(begin(c), end(c));
}

template <typename It>
auto medianIt3(It a, It b, It c)
{
    if (*a >= *b)
    {
        if (*a <= *c)
            return a; // bac
        else if (*b >= *c)
            return b; // cba
        else
            return c; // bca
    }
    if (*b <= *c)
        return b; // abc
    if (*a >= *c)
        return a; // cab
    return c;     // acb
}

template <typename It>
auto median3Partition(It begin, It end)
{
    const ptrdiff_t random_count = 3;

    if (end - begin < random_count)
        return partition(begin, end);

    const auto random_indexes = randomUniqueInts(0u, static_cast<unsigned>(end - 1 - begin), random_count);
    const auto median_it = medianIt3(begin + random_indexes[0], begin + random_indexes[1], begin + random_indexes[2]);
    iter_swap(end - 1, median_it);
    return partition(begin, end);
}

template <class C>
auto median3Partition(C& c)
{
    using namespace std;
    return median3Partition(begin(c), end(c));
}

template <typename It>
auto hoarePartition(It begin, It end)
{
    using namespace std;

    const auto x = *begin;
    auto i = begin;
    auto j = end - 1;
    while (true)
    {
        while (*i < x)
        {
            ++i;
        }
        while (*j > x)
        {
            if (j == begin)
                return j;
            else
                --j;
        }
        if (i < j)
            iter_swap(i, j);
        else
            return j + 1;
    }
}

template <class C>
auto hoarePartition(C& c)
{
    using namespace std;
    return hoarePartition(begin(c), end(c));
}

template <typename It>
void quickSort(It begin, It end)
{
    using namespace std;

    if (distance(begin, end) > 1)
    {
        const auto q = partition(begin, end);
        quickSort(begin, q);
        quickSort(q + 1, end);
    }
}

template <class C>
void quickSort(C& c)
{
    using namespace std;
    quickSort(begin(c), end(c));
}

template <typename It>
void randomizedQuicksort(It begin, It end)
{
    using namespace std;

    if (distance(begin, end) > 1)
    {
        const auto q = randomizedPartition(begin, end);
        randomizedQuicksort(begin, q);
        randomizedQuicksort(q, end);
    }
}

template <class C>
void randomizedQuicksort(C& c)
{
    using namespace std;
    randomizedQuicksort(begin(c), end(c));
}

template <typename It>
void median3Quicksort(It begin, It end)
{
    using namespace std;

    if (distance(begin, end) > 1)
    {
        const auto q = median3Partition(begin, end);
        median3Quicksort(begin, q);
        median3Quicksort(q, end);
    }
}

template <class C>
void median3Quicksort(C& c)
{
    using namespace std;
    median3Quicksort(begin(c), end(c));
}

template <typename It>
void hoareQuicksort(It begin, It end)
{
    using namespace std;

    if (distance(begin, end) > 1)
    {
        const auto q = hoarePartition(begin, end);
        hoareQuicksort(begin, q);
        hoareQuicksort(q, end);
    }
}

template <class C>
void hoareQuicksort(C& c)
{
    using namespace std;
    hoareQuicksort(begin(c), end(c));
}

template <typename It>
void tailRecursiveQuicksort(It begin, It end)
{
    using namespace std;

    while (distance(begin, end) > 1)
    {
        const auto q = partition(begin, end);
        tailRecursiveQuicksort(begin, q);
        begin = q;
    }
}

template <class C>
void tailRecursiveQuicksort(C& c)
{
    using namespace std;
    tailRecursiveQuicksort(begin(c), end(c));
}

// countingSort
// radixSort
// bucketSort
// compareExchange
// insertionSortCompareExchange
// min
// minmax
// randomizedSelect/select/nth_element
// median
