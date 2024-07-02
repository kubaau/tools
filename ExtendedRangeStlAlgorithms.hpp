#pragma once

#include "DefaultRandomEngine.hpp"
#include "RangeStlAlgorithms.hpp"

template <class C, class UnaryPred>
auto copy_if(const C& c, UnaryPred pred)
{
    using namespace std;
    C result;
    copy_if(c, result, move(pred));
    return result;
}

template <class Ret, class C, class UnaryOp>
auto transform(const C& c, UnaryOp f)
{
    using namespace std;
    Ret ret;
    transform(c, ret, move(f));
    return ret;
}

template <class Ret, class C1, class C2, class BinaryOp>
auto transform(const C1& c1, const C2& c2, BinaryOp f)
{
    using namespace std;
    Ret ret;
    transform(cbegin(c1), cend(c1), cbegin(c2), end_inserter(ret), move(f));
    return ret;
}

template <class C, typename T>
auto remove_copy(const C& c, const T& value)
{
    using namespace std;
    C result;
    remove_copy(c, result, value);
    return result;
}

template <class C, class UnaryPred>
auto remove_copy_if(const C& c, UnaryPred pred)
{
    using namespace std;
    C result;
    remove_copy_if(c, result, move(pred));
    return result;
}

template <class C, typename T>
auto replace_copy(const C& c, const T& old_value, const T& new_value)
{
    using namespace std;
    C result;
    replace_copy(c, result, old_value, new_value);
    return result;
}

template <class C, class UnaryPred, typename T>
auto replace_copy_if(const C& c, UnaryPred pred, const T& value)
{
    using namespace std;
    C result;
    replace_copy_if(c, result, move(pred), value);
    return result;
}

template <class C>
auto reverse_copy(const C& c)
{
    using namespace std;
    C result;
    reverse_copy(cbegin(c), cend(c), end_inserter(result));
    return result;
}

template <class C>
auto rotate(C& c, int n)
{
    using namespace std;
    return rotate(begin(c), begin(c) + n, end(c));
}

template <class C1, class C2>
auto rotate_copy(const C1& c1, int n, C2& c2)
{
    using namespace std;
    return rotate_copy(cbegin(c1), cbegin(c1) + n, cend(c1), end_inserter(c2));
}

template <class C>
auto rotate_copy(const C& c, int n)
{
    using namespace std;
    C result;
    rotate_copy(c, n, result);
    return result;
}

template <class C>
auto shuffle(C& c)
{
    return shuffle(c, defaultRandomEngine());
}

template <class C>
auto unique_copy(const C& c)
{
    using namespace std;
    C result;
    unique_copy(c, result);
    return result;
}

template <class C, class UnaryPred>
auto partition_copy(const C& c, UnaryPred pred)
{
    using namespace std;
    C result_true;
    C result_false;
    partition_copy(c, result_true, result_false, move(pred));
    return make_pair(result_true, result_false);
}

template <class C>
auto partial_sort(C& c, unsigned middle)
{
    using namespace std;
    return partial_sort(begin(c), begin(c) + middle, end(c));
}

template <class C, class Compare>
auto partial_sort(C& c, unsigned middle, Compare comp)
{
    using namespace std;
    return partial_sort(begin(c), begin(c) + middle, end(c), move(comp));
}

template <class C>
auto partial_sort_copy(const C& c)
{
    using namespace std;
    C result;
    return partial_sort_copy(c, result);
}

template <class C, class Compare, typename = std::enable_if_t<not IsStlContainer<Compare>::value>>
auto partial_sort_copy(const C& c, Compare comp)
{
    using namespace std;
    C result;
    return partial_sort_copy(c, result, move(comp));
}

template <class C>
auto nth_element(C& c, unsigned n)
{
    using namespace std;
    return nth_element(begin(c), begin(c) + n, end(c));
}

template <class C, class Compare>
auto nth_element(C& c, unsigned n, Compare comp)
{
    using namespace std;
    return nth_element(begin(c), begin(c) + n, end(c), move(comp));
}

template <class C>
auto merge(const C& c1, const C& c2)
{
    using namespace std;
    C result;
    merge(cbegin(c1), cend(c1), cbegin(c2), cend(c2), end_inserter(result));
    return result;
}

template <class C, class Compare>
auto merge(const C& c1, const C& c2, Compare comp)
{
    using namespace std;
    C result;
    merge(cbegin(c1), cend(c1), cbegin(c2), cend(c2), end_inserter(result), move(comp));
    return result;
}

template <class C>
auto inplace_merge(C& c, unsigned middle)
{
    using namespace std;
    return inplace_merge(begin(c), begin(c) + middle, end(c));
}

template <class C>
auto set_difference(const C& c1, const C& c2)
{
    using namespace std;
    C result;
    set_difference(cbegin(c1), cend(c1), cbegin(c2), cend(c2), end_inserter(result));
    return result;
}

template <class C, class Compare>
auto set_difference(const C& c1, const C& c2, Compare comp)
{
    using namespace std;
    C result;
    set_difference(cbegin(c1), cend(c1), cbegin(c2), cend(c2), end_inserter(result), move(comp));
    return result;
}

template <class C>
auto set_intersection(const C& c1, const C& c2)
{
    using namespace std;
    C result;
    set_intersection(begin(c1), end(c1), begin(c2), end(c2), end_inserter(result));
    return result;
}

template <class C, class Compare>
auto set_intersection(const C& c1, const C& c2, Compare comp)
{
    using namespace std;
    C result;
    set_intersection(begin(c1), end(c1), begin(c2), end(c2), end_inserter(result), move(comp));
    return result;
}

template <class C>
auto set_symmetric_difference(const C& c1, const C& c2)
{
    using namespace std;
    C result;
    set_symmetric_difference(begin(c1), end(c1), begin(c2), end(c2), end_inserter(result));
    return result;
}

template <class C, class Compare>
auto set_symmetric_difference(const C& c1, const C& c2, Compare comp)
{
    using namespace std;
    C result;
    set_symmetric_difference(begin(c1), end(c1), begin(c2), end(c2), end_inserter(result), move(comp));
    return result;
}

template <class C>
auto set_union(const C& c1, const C& c2)
{
    using namespace std;
    C result;
    set_union(begin(c1), end(c1), begin(c2), end(c2), end_inserter(result));
    return result;
}

template <class C, class Compare>
auto set_union(const C& c1, const C& c2, Compare comp)
{
    using namespace std;
    C result;
    set_union(begin(c1), end(c1), begin(c2), end(c2), end_inserter(result), move(comp));
    return result;
}

template <typename T1, typename T2>
constexpr auto min2(const T1& a, const T2& b)
{
    using namespace std;
    return min(a, static_cast<T1>(b));
}

template <typename T1, typename T2, class Compare>
constexpr auto min2(const T1& a, const T2& b, Compare comp)
{
    using namespace std;
    return min(a, static_cast<T1>(b), move(comp));
}

template <typename T1, typename T2>
constexpr auto max2(const T1& a, const T2& b)
{
    using namespace std;
    return max(a, static_cast<T1>(b));
}

template <typename T1, typename T2, class Compare>
constexpr auto max2(const T1& a, const T2& b, Compare comp)
{
    using namespace std;
    return max(a, static_cast<T1>(b), move(comp));
}

template <typename T1, typename T2>
constexpr auto minmax2(const T1& a, const T2& b)
{
    using namespace std;
    return minmax2(a, static_cast<T1>(b));
}

template <typename T1, typename T2, class Compare>
constexpr auto minmax2(const T1& a, const T2& b, Compare comp)
{
    using namespace std;
    return minmax2(a, static_cast<T1>(b), move(comp));
}

template <class C>
auto adjacent_difference(const C& c)
{
    using namespace std;
    C result;
    adjacent_difference(cbegin(c), cend(c), end_inserter(result));
    return result;
}

template <class C, class BinaryOp>
auto adjacent_difference(const C& c, BinaryOp f)
{
    using namespace std;
    C result;
    adjacent_difference(cbegin(c), cend(c), end_inserter(result), move(f));
    return result;
}

template <class C>
auto partial_sum(const C& c)
{
    using namespace std;
    C result;
    partial_sum(cbegin(c), cend(c), end_inserter(result));
    return result;
}

template <class C, class BinaryOp>
auto partial_sum(const C& c, BinaryOp f)
{
    using namespace std;
    C result;
    partial_sum(cbegin(c), cend(c), end_inserter(result), move(f));
    return result;
}

template <class C>
auto front(const C& c)
{
    return *std::cbegin(c);
}

template <class C, typename T>
auto fill(C& c, const T& value, int n)
{
    c.resize(n);
    return fill(c, value);
}
