#include "CLRS.hpp"
#include "Contains.hpp"
#include "GtestWrapper.hpp"

const vector<pair<V, V>> sorts = {
    make_pair(V{}, V{}),
    make_pair(V{1}, V{1}),
    make_pair(V{1, 1}, V{1, 1}),
    make_pair(V{1, 2}, V{1, 2}),
    make_pair(V{2, 1}, V{1, 2}),
    make_pair(V{1, 2, 1}, V{1, 1, 2}),
    make_pair(V{2, 1, 1}, V{1, 1, 2}),
    make_pair(V{2, 1, 3}, V{1, 2, 3}),
    make_pair(V{5, 3, 7, 9, -2, 3, 1, 8, -1}, V{-2, -1, 1, 3, 3, 5, 7, 8, 9}),
};

TEST(CLRS, insertionSort_partial)
{
    auto sort = sorts.back();
    insertionSort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

TEST(CLRS, insertionSort_container)
{
    for (auto v : sorts)
    {
        insertionSort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}

TEST(CLRS, mergeClrs)
{
    V v = {5, 3, 7, 8, 1, 2, 5, 9, 7, 6};
    mergeClrs(v.begin() + 1, v.begin() + 4, v.begin() + 8);
    EXPECT_EQ((V{5, 1, 2, 3, 5, 7, 8, 9, 7, 6}), v);
}

TEST(CLRS, mergeSort_partial)
{
    auto sort = sorts.back();
    mergeSort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

TEST(CLRS, mergeSort_container)
{
    for (auto v : sorts)
    {
        mergeSort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}

TEST(CLRS, bubbleSort_partial)
{
    auto sort = sorts.back();
    bubbleSort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

TEST(CLRS, bubbleSort_container)
{
    for (auto v : sorts)
    {
        bubbleSort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}

TEST(CLRS, selectionSort_partial)
{
    auto sort = sorts.back();
    selectionSort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

TEST(CLRS, selectionSort_container)
{
    for (auto v : sorts)
    {
        selectionSort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}

TEST(CLRS, maxCrossingSubarray)
{
    const V v = {-13, -3, 25, 20, -3, -16, 23, -18, -20, -7, -12, -5, -22, 15, -4, 7};
    const auto res_c = maxCrossingSubarray(v);
    EXPECT_EQ(begin(v) + 2, res_c.begin);
    EXPECT_EQ(begin(v) + 9, res_c.end);
    EXPECT_EQ(11, res_c.sum);

    const auto res_it = maxCrossingSubarray(begin(v) + 1, begin(v) + 5, begin(v) + 10);
    EXPECT_EQ(begin(v) + 2, res_it.begin);
    EXPECT_EQ(begin(v) + 7, res_it.end);
    EXPECT_EQ(49, res_it.sum);

    const V empty;
    const auto res_empty = maxCrossingSubarray(empty);
    EXPECT_EQ(begin(empty), res_empty.begin);
    EXPECT_EQ(begin(empty), res_empty.end);
    EXPECT_EQ(0, res_empty.sum);
}

TEST(CLRS, maxSubarray)
{
    const V v = {-13, -3, 25, 20, -3, -16, 23, -18, -20, -7, -12, -5, -22, 15, -4, 7};
    const auto res_c = maxSubarray(v);
    EXPECT_EQ(begin(v) + 2, res_c.begin);
    EXPECT_EQ(begin(v) + 7, res_c.end);
    EXPECT_EQ(49, res_c.sum);

    const auto res_it = maxSubarray(begin(v) + 8, end(v));
    EXPECT_EQ(begin(v) + 13, res_it.begin);
    EXPECT_EQ(end(v), res_it.end);
    EXPECT_EQ(18, res_it.sum);

    V empty;
    const auto res_empty = maxSubarray(empty);
    EXPECT_EQ(begin(empty), res_empty.begin);
    EXPECT_EQ(begin(empty), res_empty.end);
    EXPECT_EQ(0, res_empty.sum);
}

TEST(CLRS, permuteBySorting)
{
    V v = {-13, -3, 25, 20, -3, -16, 23, -18, -20, -7, -12, -5, -22, 15, -4, 7};
    auto v_orig = v;
    print(v);
    permuteBySorting(v);
    print(v);
    permuteBySorting(v);
    print(v);
    sort(v_orig);
    sort(v);
    EXPECT_EQ(v_orig, v);
}

TEST(CLRS, heapParent)
{
    EXPECT_EQ(-1, heapParent(0));
    EXPECT_EQ(0, heapParent(1));
    EXPECT_EQ(0, heapParent(2));
    EXPECT_EQ(1, heapParent(3));
    EXPECT_EQ(1, heapParent(4));
    EXPECT_EQ(2, heapParent(5));
    EXPECT_EQ(2, heapParent(6));
    EXPECT_EQ(3, heapParent(7));
    EXPECT_EQ(3, heapParent(8));
}

TEST(CLRS, heapLeft)
{
    EXPECT_EQ(1, heapLeft(0));
    EXPECT_EQ(3, heapLeft(1));
    EXPECT_EQ(5, heapLeft(2));
    EXPECT_EQ(7, heapLeft(3));
}

TEST(CLRS, heapRight)
{
    EXPECT_EQ(2, heapRight(0));
    EXPECT_EQ(4, heapRight(1));
    EXPECT_EQ(6, heapRight(2));
    EXPECT_EQ(8, heapRight(3));
}

TEST(CLRS, maxHeapify)
{
    V v = {3, 4, 10, 14, 7, 9, 16, 2, 8, 1};
    maxHeapify(v, 0, 0);
    EXPECT_EQ((V{3, 4, 10, 14, 7, 9, 16, 2, 8, 1}), v);
    maxHeapify(v, 0, 3);
    EXPECT_EQ((V{10, 4, 3, 14, 7, 9, 16, 2, 8, 1}), v);
    maxHeapify(v, 0);
    EXPECT_EQ((V{10, 4, 3, 14, 7, 9, 16, 2, 8, 1}), v);
    maxHeapify(v, 1);
    EXPECT_EQ((V{10, 14, 3, 8, 7, 9, 16, 2, 4, 1}), v);
}

TEST(CLRS, isMaxHeap)
{
    V v{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    EXPECT_FALSE(isMaxHeap(v));
    v = {16, 10, 14, 7, 8, 9, 4, 2, 3, 1};
    EXPECT_TRUE(isMaxHeap(v));
}

TEST(CLRS, buildMaxHeap)
{
    V v{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    buildMaxHeap(v);
    EXPECT_TRUE(isMaxHeap(v));
}

// TEST(CLRS, heapSort_partial)
//{
//    auto sort = sorts.back();
//    heapSort(sort.first.begin() + 2, sort.first.begin() + 6);
//    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
//}

TEST(CLRS, heapSort_container)
{
    for (auto v : sorts)
    {
        heapSort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}

TEST(CLRS, heapMax)
{
    V v{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    EXPECT_EQ(4, heapMax(v));
    buildMaxHeap(v);
    EXPECT_EQ(16, heapMax(v));
}

TEST(CLRS, heapPopMax)
{
    V v{4, 1, 9, 2, 16, 9, 10, 14, 8, 7};
    EXPECT_EQ(4, heapPopMax(v));
    EXPECT_EQ((V{9, 1, 10, 2, 16, 9, 7, 14, 8}), v);
    EXPECT_EQ(9, heapPopMax(v));
    EXPECT_EQ((V{10, 1, 9, 2, 16, 8, 7, 14}), v);
}

TEST(CLRS, heapIncreaseKey)
{
    V v{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    heapIncreaseKey(v, 5, 11);
    EXPECT_EQ((V{11, 1, 4, 2, 16, 3, 10, 14, 8, 7}), v);
    heapIncreaseKey(v, 3, 17);
    EXPECT_EQ((V{17, 11, 4, 1, 16, 3, 10, 14, 8, 7}), v);
    heapIncreaseKey(v, 3, 5);
    EXPECT_EQ((V{17, 11, 4, 5, 16, 3, 10, 14, 8, 7}), v);
}

TEST(CLRS, maxHeapInsert)
{
    V v{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    buildMaxHeap(v);
    EXPECT_TRUE(isMaxHeap(v));
    maxHeapInsert(v, 5);
    EXPECT_TRUE(isMaxHeap(v));
    EXPECT_TRUE(contains(v, 5));
    maxHeapInsert(v, 25);
    EXPECT_TRUE(isMaxHeap(v));
    EXPECT_TRUE(contains(v, 25));
}

TEST(CLRS, buildMaxHeap2)
{
    V v{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    buildMaxHeap2(v);
    EXPECT_TRUE(isMaxHeap(v));
}

TEST(CLRS, isPartitioned_partial)
{
    V v{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    EXPECT_TRUE(isPartitioned(v.begin() + 5, v.begin() + 6, v.begin() + 8));
    EXPECT_FALSE(isPartitioned(v.begin() + 5, v.begin() + 6, v.begin() + 9));
}

TEST(CLRS, isPartitioned_container)
{
    V v{3, 2, 1, 4, 4, 4, 7, 6};
    EXPECT_TRUE(isPartitioned(v, v.begin() + 4));
    v[4] = 5;
    EXPECT_FALSE(isPartitioned(v, v.begin() + 4));
}

TEST(CLRS, partition)
{
    V v{};
    EXPECT_EQ(v.begin(), partition(v.begin(), v.end()));
    EXPECT_EQ((V{}), v);

    v = {1};
    EXPECT_EQ(v.begin(), partition(v.begin(), v.end()));
    EXPECT_EQ((V{1}), v);

    v = {2, 1};
    EXPECT_EQ(v.begin(), partition(v.begin(), v.end()));
    EXPECT_EQ((V{1, 2}), v);

    v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    EXPECT_EQ(v.begin() + 4, partition(v.begin(), v.end()));
    EXPECT_TRUE(isPartitioned(v, v.begin() + 4));

    v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    EXPECT_EQ(v.begin() + 4, partition(v));
    EXPECT_TRUE(isPartitioned(v, v.begin() + 4));
}

TEST(CLRS, randomizedPartition)
{
    V v{};
    EXPECT_EQ(v.begin(), randomizedPartition(v.begin(), v.end()));
    EXPECT_EQ((V{}), v);

    v = {1};
    EXPECT_EQ(v.begin(), randomizedPartition(v.begin(), v.end()));
    EXPECT_EQ((V{1}), v);

    v = {2, 1};
    EXPECT_TRUE(isPartitioned(v, randomizedPartition(v.begin(), v.end())));

    v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    EXPECT_TRUE(isPartitioned(v, randomizedPartition(v.begin(), v.end())));

    v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    EXPECT_TRUE(isPartitioned(v, randomizedPartition(v)));
}

TEST(CLRS, medianIt3)
{
    V v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    EXPECT_EQ(v.begin() + 1, medianIt3(v.begin() + 1, v.begin() + 3, v.begin() + 4));
    EXPECT_EQ(v.begin() + 1, medianIt3(v.begin() + 4, v.begin() + 1, v.begin() + 3));
    EXPECT_EQ(v.begin() + 1, medianIt3(v.begin() + 4, v.begin() + 3, v.begin() + 1));
    EXPECT_EQ(v.begin() + 1, medianIt3(v.begin() + 3, v.begin() + 1, v.begin() + 4));
    EXPECT_EQ(v.begin() + 1, medianIt3(v.begin() + 1, v.begin() + 4, v.begin() + 3));
    EXPECT_EQ(v.begin() + 1, medianIt3(v.begin() + 3, v.begin() + 4, v.begin() + 1));
}

TEST(CLRS, median3Partition)
{
    V v{};
    EXPECT_EQ(v.begin(), median3Partition(v.begin(), v.end()));
    EXPECT_EQ((V{}), v);

    v = {1};
    EXPECT_EQ(v.begin(), median3Partition(v.begin(), v.end()));
    EXPECT_EQ((V{1}), v);

    v = {2, 1};
    EXPECT_TRUE(isPartitioned(v, median3Partition(v.begin(), v.end())));

    v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    EXPECT_TRUE(isPartitioned(v, median3Partition(v.begin(), v.end())));

    v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    EXPECT_TRUE(isPartitioned(v, median3Partition(v)));
}

TEST(CLRS, hoarePartition)
{
    vector<int> v{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    print(v);
    hoarePartition(v);
    print(v);
    hoareQuicksort(v);
    print(v);

    // V v{};
    // EXPECT_EQ(v.begin() + 1, hoarePartition(v.begin(), v.end()));
    // EXPECT_EQ((V{}), v);

    // v = {1};
    // EXPECT_EQ(v.begin() + 1, hoarePartition(v.begin(), v.end()));
    // EXPECT_EQ((V{1}), v);

    // v = {2, 1};
    // EXPECT_EQ(v.begin() + 1, hoarePartition(v.begin(), v.end()));
    // EXPECT_EQ((V{1, 2}), v);

    // v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    // EXPECT_EQ(v.begin() + 1, hoarePartition(v.begin(), v.end()));
    // EXPECT_TRUE(isPartitioned(v, v.begin() + 1));
    //
    // v = {4, 7, 9, 2, 16, 9, 10, 5, 8, 7};
    // EXPECT_EQ(v.begin() + 1, hoarePartition(v));
    // EXPECT_TRUE(isPartitioned(v, v.begin() + 1));
}

TEST(CLRS, quickSort_partial)
{
    auto sort = sorts.back();
    quickSort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

TEST(CLRS, quickSort_container)
{
    for (auto v : sorts)
    {
        quickSort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}

TEST(CLRS, randomizedQuicksort_partial)
{
    auto sort = sorts.back();
    randomizedQuicksort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

TEST(CLRS, randomizedQuicksort_container)
{
    for (auto v : sorts)
    {
        randomizedQuicksort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}

TEST(CLRS, median3Quicksort_partial)
{
    auto sort = sorts.back();
    median3Quicksort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

TEST(CLRS, median3Quicksort_container)
{
    for (auto v : sorts)
    {
        median3Quicksort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}

TEST(CLRS, hoareQuicksort_partial)
{
    auto sort = sorts.back();
    hoareQuicksort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

// TEST(CLRS, hoareQuicksort_container)
//{
//    for (auto v : sorts)
//    {
//        hoareQuicksort(v.first);
//        EXPECT_EQ(v.second, v.first);
//    }
//}

TEST(CLRS, tailRecursiveQuicksort_partial)
{
    auto sort = sorts.back();
    tailRecursiveQuicksort(sort.first.begin() + 2, sort.first.begin() + 6);
    EXPECT_EQ((V{5, 3, -2, 3, 7, 9, 1, 8, -1}), sort.first);
}

TEST(CLRS, tailRecursiveQuicksort_container)
{
    for (auto v : sorts)
    {
        tailRecursiveQuicksort(v.first);
        EXPECT_EQ(v.second, v.first);
    }
}
