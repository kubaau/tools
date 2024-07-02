#include "IsStlContainer.hpp"
#include "GtestWrapper.hpp"

TEST(IsStlContainer, is_stl_container)
{
    static_assert(IsStlContainer<array<int, 2>>::value, "");
    static_assert(IsStlContainer<deque<int>>::value, "");
    static_assert(IsStlContainer<forward_list<int>>::value, "");
    static_assert(IsStlContainer<list<int>>::value, "");
    static_assert(IsStlContainer<map<int, int>>::value, "");
    static_assert(IsStlContainer<multimap<int, int>>::value, "");
    static_assert(IsStlContainer<queue<int>>::value, "");
    static_assert(IsStlContainer<priority_queue<int>>::value, "");
    static_assert(IsStlContainer<set<int>>::value, "");
    static_assert(IsStlContainer<multiset<int>>::value, "");
    static_assert(IsStlContainer<stack<int>>::value, "");
    static_assert(IsStlContainer<unordered_map<int, int>>::value, "");
    static_assert(IsStlContainer<unordered_multimap<int, int>>::value, "");
    static_assert(IsStlContainer<unordered_set<int>>::value, "");
    static_assert(IsStlContainer<unordered_multiset<int>>::value, "");
    static_assert(IsStlContainer<vector<int>>::value, "");
    static_assert(not IsStlContainer<int>::value, "");

    struct S
    {
    };
    static_assert(not IsStlContainer<S>::value, "");
}
