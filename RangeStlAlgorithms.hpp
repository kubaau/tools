#pragma once

#include <algorithm>
#include <numeric>
#include "ForwardDeclarations.hpp"
#include "Iterators.hpp"

template <class C, class UnaryPred>
auto all_of(const C& c, UnaryPred pred)
{
    using namespace std;
    return all_of(cbegin(c), cend(c), move(pred));
}

template <class C, class UnaryPred>
auto any_of(const C& c, UnaryPred pred)
{
    using namespace std;
    return any_of(cbegin(c), cend(c), move(pred));
}

template <class C, class UnaryPred>
auto none_of(const C& c, UnaryPred pred)
{
    using namespace std;
    return none_of(cbegin(c), cend(c), move(pred));
}

template <class C, class UnaryFunc>
auto for_each(const C& c, UnaryFunc f)
{
    using namespace std;
    return for_each(cbegin(c), cend(c), move(f));
}

template <class C, typename T>
auto count(const C& c, const T& value)
{
    using namespace std;
    return count(cbegin(c), cend(c), value);
}

template <class C, class UnaryPred>
auto count_if(const C& c, UnaryPred pred)
{
    using namespace std;
    return count_if(cbegin(c), cend(c), move(pred));
}

template <class C1, class C2>
auto mismatch(const C1& c1, const C2& c2)
{
    using namespace std;
    return mismatch(cbegin(c1), cend(c1), cbegin(c2));
}

template <class C1, class C2>
auto equal(const C1& c1, const C2& c2)
{
    using namespace std;
    return equal(cbegin(c1), cend(c1), cbegin(c2));
}

template <class C, typename T>
auto find(const C& c, const T& value)
{
    using namespace std;
    return find(cbegin(c), cend(c), value);
}

template <class C, class UnaryPred>
auto find_if(const C& c, UnaryPred pred)
{
    using namespace std;
    return find_if(cbegin(c), cend(c), move(pred));
}

template <class C, class UnaryPred>
auto find_if_not(const C& c, UnaryPred pred)
{
    using namespace std;
    return find_if_not(cbegin(c), cend(c), move(pred));
}

template <class C1, class C2>
auto find_end(const C1& c1, const C2& c2)
{
    using namespace std;
    return find_end(cbegin(c1), cend(c1), cbegin(c2), cend(c2));
}

template <class C1, class C2, class BinaryPred>
auto find_end(const C1& c1, const C2& c2, BinaryPred pred)
{
    using namespace std;
    return find_end(cbegin(c1), cend(c1), cbegin(c2), cend(c2), move(pred));
}

template <class C1, class C2>
auto find_first_of(const C1& c1, const C2& c2)
{
    using namespace std;
    return find_first_of(cbegin(c1), cend(c1), cbegin(c2), cend(c2));
}

template <class C1, class C2, class BinaryPred>
auto find_first_of(const C1& c1, const C2& c2, BinaryPred pred)
{
    using namespace std;
    return find_first_of(cbegin(c1), cend(c1), cbegin(c2), cend(c2), move(pred));
}

template <class C>
auto adjacent_find(const C& c)
{
    using namespace std;
    return adjacent_find(cbegin(c), cend(c));
}

template <class C1, class C2>
auto search(const C1& c1, const C2& c2)
{
    using namespace std;
    return search(cbegin(c1), cend(c1), cbegin(c2), cend(c2));
}

template <class C1, class C2, class BinaryPred>
auto search(const C1& c1, const C2& c2, BinaryPred pred)
{
    using namespace std;
    return search(cbegin(c1), cend(c1), cbegin(c2), cend(c2), move(pred));
}

template <class C, typename T>
auto search_n(const C& c, unsigned count, const T& value)
{
    using namespace std;
    return search_n(cbegin(c), cend(c), count, value);
}

template <class C, typename T, class BinaryPred>
auto search_n(const C& c, unsigned count, const T& value, BinaryPred pred)
{
    using namespace std;
    return search_n(cbegin(c), cend(c), count, value, move(pred));
}

template <class CFrom, class CTo>
auto copy(const CFrom& from, CTo& to)
{
    using namespace std;
    return copy(cbegin(from), cend(from), end_inserter(to));
}

template <class CFrom, class CTo, class UnaryPred>
auto copy_if(const CFrom& from, CTo& to, UnaryPred pred)
{
    using namespace std;
    return copy_if(cbegin(from), cend(from), end_inserter(to), move(pred));
}

template <class CFrom, class CTo>
auto copy_backward(const CFrom& from, CTo& to)
{
    using namespace std;
    return copy_backward(cbegin(from), cend(from), end(to));
}

template <class CFrom, class CTo>
auto move(const CFrom& from, CTo& to)
{
    using namespace std;
    return move(cbegin(from), cend(from), end_inserter(to));
}

template <class CFrom, class CTo>
auto move_backward(const CFrom& from, CTo& to)
{
    using namespace std;
    return move_backward(cbegin(from), cend(from), end(to));
}

template <class C, typename T>
auto fill(C& c, const T& value)
{
    using namespace std;
    return fill(begin(c), end(c), value);
}

template <class C, typename T>
auto fill_n(C& c, unsigned n, const T& value)
{
    using namespace std;
    return fill_n(begin(c), n, value);
}

template <class C, class UnaryOp>
auto transform(C c, UnaryOp f)
{
    using namespace std;
    transform(cbegin(c), cend(c), begin(c), move(f));
    return c;
}

template <class CFrom, class CTo, class UnaryOp>
auto transform(const CFrom& from, CTo& to, UnaryOp f)
{
    using namespace std;
    return transform(cbegin(from), cend(from), end_inserter(to), move(f));
}

template <class C, class Generator>
auto generate(C& c, Generator g)
{
    using namespace std;
    return generate(begin(c), end(c), move(g));
}

template <class C, class Generator>
auto generate_n(C& c, unsigned n, Generator g)
{
    using namespace std;
    return generate_n(begin(c), n, move(g));
}

template <class C, typename T>
auto remove(C& c, const T& value)
{
    using namespace std;
    return remove(begin(c), end(c), value);
}

template <class C, class UnaryPred>
auto remove_if(C& c, UnaryPred pred)
{
    using namespace std;
    return remove_if(begin(c), end(c), move(pred));
}

template <class C1, class C2, typename T>
auto remove_copy(const C1& c1, C2& c2, const T& value)
{
    using namespace std;
    return remove_copy(cbegin(c1), cend(c1), end_inserter(c2), value);
}

template <class C1, class C2, class UnaryPred>
auto remove_copy_if(const C1& c1, C2& c2, UnaryPred pred)
{
    using namespace std;
    return remove_copy_if(cbegin(c1), cend(c1), end_inserter(c2), move(pred));
}

template <class C, typename T>
auto replace(C& c, const T& old_value, const T& new_value)
{
    using namespace std;
    return replace(begin(c), end(c), old_value, new_value);
}

template <class C, class UnaryPred, typename T>
auto replace_if(C& c, UnaryPred pred, const T& value)
{
    using namespace std;
    return replace_if(begin(c), end(c), move(pred), value);
}

template <class C1, class C2, typename T>
auto replace_copy(const C1& c1, C2& c2, const T& old_value, const T& new_value)
{
    using namespace std;
    return replace_copy(cbegin(c1), cend(c1), end_inserter(c2), old_value, new_value);
}

template <class C1, class C2, class UnaryPred, typename T>
auto replace_copy_if(const C1& c1, C2& c2, UnaryPred pred, const T& value)
{
    using namespace std;
    return replace_copy_if(cbegin(c1), cend(c1), end_inserter(c2), move(pred), value);
}

template <class C1, class C2>
auto swap_ranges(C1& c1, C2& c2)
{
    using namespace std;
    return swap_ranges(begin(c1), end(c1), begin(c2));
}

template <class C>
auto reverse(C& c)
{
    using namespace std;
    return reverse(begin(c), end(c));
}

template <class C1, class C2>
auto reverse_copy(const C1& c1, C2& c2)
{
    using namespace std;
    return reverse_copy(cbegin(c1), cend(c2), end_inserter(c2));
}

template <class C, class UniformRandomBitGenerator>
auto shuffle(C& c, UniformRandomBitGenerator&& g)
{
    using namespace std;
    return shuffle(begin(c), end(c), forward<UniformRandomBitGenerator>(g));
}

template <class C>
auto unique(C& c)
{
    using namespace std;
    return unique(begin(c), end(c));
}

template <class C, class BinaryPred>
auto unique(C& c, BinaryPred pred)
{
    using namespace std;
    return unique(begin(c), end(c), move(pred));
}

template <class C1, class C2>
auto unique_copy(const C1& c1, C2& c2)
{
    using namespace std;
    return unique_copy(begin(c1), end(c1), end_inserter(c2));
}

template <class C, class UnaryPred>
auto is_partitioned(const C& c, UnaryPred pred)
{
    using namespace std;
    return is_partitioned(cbegin(c), cend(c), move(pred));
}

template <class C, class UnaryPred>
auto partition(C& c, UnaryPred pred)
{
    using namespace std;
    return partition(begin(c), end(c), move(pred));
}

template <class C1, class C2, class C3, class UnaryPred>
auto partition_copy(const C1& c1, C2& c2, C3& c3, UnaryPred pred)
{
    using namespace std;
    return partition_copy(cbegin(c1), cend(c1), end_inserter(c2), end_inserter(c3), move(pred));
}

template <class C, class UnaryPred>
auto stable_partition(C& c, UnaryPred pred)
{
    using namespace std;
    return stable_partition(begin(c), end(c), move(pred));
}

template <class C, class UnaryPred>
auto partition_point(const C& c, UnaryPred pred)
{
    using namespace std;
    return partition_point(cbegin(c), cend(c), move(pred));
}

template <class C>
auto is_sorted(const C& c)
{
    using namespace std;
    return is_sorted(cbegin(c), cend(c));
}

template <class C, class Compare>
auto is_sorted(const C& c, Compare comp)
{
    using namespace std;
    return is_sorted(cbegin(c), cend(c), move(comp));
}

template <class C>
auto is_sorted_until(const C& c)
{
    using namespace std;
    return is_sorted_until(cbegin(c), cend(c));
}

template <class C, class Compare>
auto is_sorted_until(const C& c, Compare comp)
{
    using namespace std;
    return is_sorted_until(cbegin(c), cend(c), move(comp));
}

template <class C>
auto sort(C& c)
{
    using namespace std;
    return sort(begin(c), end(c));
}

template <class C, class Compare>
auto sort(C& c, Compare comp)
{
    using namespace std;
    return sort(begin(c), end(c), move(comp));
}

template <class C1, class C2, typename = std::enable_if_t<IsStlContainer<C2>::value>>
auto partial_sort_copy(const C1& c1, C2& c2)
{
    using namespace std;
    return partial_sort_copy(cbegin(c1), cend(c1), begin(c2), end(c2));
}

template <class C1, class C2, class Compare>
auto partial_sort_copy(const C1& c1, C2& c2, Compare comp)
{
    using namespace std;
    return partial_sort_copy(cbegin(c1), cend(c1), begin(c2), end(c2), move(comp));
}

template <class C>
auto stable_sort(C& c)
{
    using namespace std;
    return stable_sort(begin(c), end(c));
}

template <class C, class Compare>
auto stable_sort(C& c, Compare comp)
{
    using namespace std;
    return stable_sort(begin(c), end(c), move(comp));
}

template <class C, typename T>
auto lower_bound(const C& c, const T& value)
{
    using namespace std;
    return lower_bound(cbegin(c), cend(c), value);
}

template <class C, typename T, class Compare>
auto lower_bound(const C& c, const T& value, Compare comp)
{
    using namespace std;
    return lower_bound(cbegin(c), cend(c), value, move(comp));
}

template <class C, typename T>
auto upper_bound(const C& c, const T& value)
{
    using namespace std;
    return upper_bound(cbegin(c), cend(c), value);
}

template <class C, typename T, class Compare>
auto upper_bound(const C& c, const T& value, Compare comp)
{
    using namespace std;
    return upper_bound(cbegin(c), cend(c), value, move(comp));
}

template <class C, typename T>
auto binary_search(const C& c, const T& value)
{
    using namespace std;
    return binary_search(cbegin(c), cend(c), value);
}

template <class C, typename T, class Compare>
auto binary_search(const C& c, const T& value, Compare comp)
{
    using namespace std;
    return binary_search(cbegin(c), cend(c), value, move(comp));
}

template <class C, typename T>
auto equal_range(const C& c, const T& value)
{
    using namespace std;
    return equal_range(cbegin(c), cend(c), value);
}

template <class C, typename T, class Compare>
auto equal_range(const C& c, const T& value, Compare comp)
{
    using namespace std;
    return equal_range(cbegin(c), cend(c), value, move(comp));
}

template <class C, class It, typename = std::enable_if_t<IsIterator<It>::value>>
auto inplace_merge(C& c, It middle)
{
    using namespace std;
    return inplace_merge(begin(c), middle, end(c));
}

template <class C1, class C2>
auto includes(const C1& c1, const C2& c2)
{
    using namespace std;
    return includes(cbegin(c1), cend(c1), cbegin(c2), cend(c2));
}

template <class C1, class C2, class Compare>
auto includes(const C1& c1, const C2& c2, Compare comp)
{
    using namespace std;
    return includes(cbegin(c1), cend(c1), cbegin(c2), cend(c2), move(comp));
}

template <class C>
auto is_heap(const C& c)
{
    using namespace std;
    return is_heap(cbegin(c), cend(c));
}

template <class C, class Compare>
auto is_heap(const C& c, Compare comp)
{
    using namespace std;
    return is_heap(cbegin(c), cend(c), move(comp));
}

template <class C>
auto is_heap_until(const C& c)
{
    using namespace std;
    return is_heap_until(cbegin(c), cend(c));
}

template <class C, class Compare>
auto is_heap_until(const C& c, Compare comp)
{
    using namespace std;
    return is_heap_until(cbegin(c), cend(c), move(comp));
}

template <class C>
auto make_heap(C& c)
{
    using namespace std;
    return make_heap(begin(c), end(c));
}

template <class C, class Compare>
auto make_heap(C& c, Compare comp)
{
    using namespace std;
    return make_heap(begin(c), end(c), move(comp));
}

template <class C>
auto push_heap(C& c)
{
    using namespace std;
    return push_heap(begin(c), end(c));
}

template <class C, class Compare>
auto push_heap(C& c, Compare comp)
{
    using namespace std;
    return push_heap(begin(c), end(c), move(comp));
}

template <class C>
auto pop_heap(C& c)
{
    using namespace std;
    return pop_heap(begin(c), end(c));
}

template <class C, class Compare>
auto pop_heap(C& c, Compare comp)
{
    using namespace std;
    return pop_heap(begin(c), end(c), move(comp));
}

template <class C>
auto sort_heap(C& c)
{
    using namespace std;
    return sort_heap(begin(c), end(c));
}

template <class C, class Compare>
auto sort_heap(C& c, Compare comp)
{
    using namespace std;
    return sort_heap(begin(c), end(c), move(comp));
}

template <class C>
constexpr auto max_element(const C& c)
{
    using namespace std;
    return max_element(cbegin(c), cend(c));
}

template <class C, class Compare>
constexpr auto max_element(const C& c, Compare comp)
{
    using namespace std;
    return max_element(cbegin(c), cend(c), move(comp));
}

template <class C>
constexpr auto min_element(const C& c)
{
    using namespace std;
    return min_element(cbegin(c), cend(c));
}

template <class C, class Compare>
constexpr auto min_element(const C& c, Compare comp)
{
    using namespace std;
    return min_element(cbegin(c), cend(c), move(comp));
}

template <class C>
constexpr auto minmax_element(const C& c)
{
    using namespace std;
    return minmax_element(cbegin(c), cend(c));
}

template <class C, class Compare>
constexpr auto minmax_element(const C& c, Compare comp)
{
    using namespace std;
    return minmax_element(cbegin(c), cend(c), move(comp));
}

template <class C1, class C2>
auto lexicographical_compare(const C1& c1, const C2& c2)
{
    using namespace std;
    return lexicographical_compare(cbegin(c1), cend(c1), cbegin(c2), cend(c2));
}

template <class C1, class C2, class Compare>
auto lexicographical_compare(const C1& c1, const C2& c2, Compare comp)
{
    using namespace std;
    return lexicographical_compare(cbegin(c1), cend(c1), cbegin(c2), cend(c2), move(comp));
}

template <class C1, class C2>
auto is_permutation(const C1& c1, const C2& c2)
{
    using namespace std;
    return is_permutation(cbegin(c1), cend(c1), cbegin(c2), cend(c2));
}

template <class C1, class C2, class BinaryPred>
auto is_permutation(const C1& c1, const C2& c2, BinaryPred pred)
{
    using namespace std;
    return is_permutation(cbegin(c1), cend(c1), cbegin(c2), cend(c2), move(pred));
}

template <class C>
auto next_permutation(C& c)
{
    using namespace std;
    return next_permutation(begin(c), end(c));
}

template <class C, class Compare>
auto next_permutation(C& c, Compare comp)
{
    using namespace std;
    return next_permutation(begin(c), end(c), move(comp));
}

template <class C>
auto prev_permutation(C& c)
{
    using namespace std;
    return prev_permutation(begin(c), end(c));
}

template <class C, class Compare>
auto prev_permutation(C& c, Compare comp)
{
    using namespace std;
    return prev_permutation(begin(c), end(c), move(comp));
}

template <class C>
void iota(C& c, typename C::const_reference start)
{
    using namespace std;
    return iota(begin(c), end(c), start);
}

template <class C, typename T>
auto accumulate(const C& c, const T& init)
{
    using namespace std;
    return accumulate(cbegin(c), cend(c), init);
}

template <class C, typename T, class BinaryOp>
auto accumulate(const C& c, const T& init, BinaryOp f)
{
    using namespace std;
    return accumulate(cbegin(c), cend(c), init, move(f));
}

template <class C1, class C2, typename T>
auto inner_product(const C1& c1, const C2& c2, const T& init)
{
    using namespace std;
    return inner_product(cbegin(c1), cend(c1), cbegin(c2), init);
}

template <class C1, class C2, typename T, class BinaryOp1, class BinaryOp2>
auto inner_product(const C1& c1, const C2& c2, const T& init, BinaryOp1 f1, BinaryOp2 f2)
{
    using namespace std;
    return inner_product(cbegin(c1), cend(c1), cbegin(c2), init, move(f1), move(f2));
}
