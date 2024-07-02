#pragma once

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace Detail
{
    using namespace std;

    template <typename T>
    struct IsStlContainer : false_type
    {
    };
    template <typename T, size_t N>
    struct IsStlContainer<array<T, N>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<deque<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<forward_list<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<list<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<map<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<multimap<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<queue<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<priority_queue<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<set<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<multiset<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<stack<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<unordered_map<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<unordered_multimap<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<unordered_set<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<unordered_multiset<Args...>> : true_type
    {
    };
    template <typename... Args>
    struct IsStlContainer<vector<Args...>> : true_type
    {
    };
}

template <typename T>
struct IsStlContainer
{
    static constexpr auto value = Detail::IsStlContainer<std::decay_t<T>>::value;
};
