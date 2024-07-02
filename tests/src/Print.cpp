#include "Print.hpp"
#include "GtestWrapper.hpp"

TEST(Print, print)
{
    print(1);
    print('a');
    print("abc");
    print("abc", "def");
    print(3.14);
    print(1, 'a', "abc", 3.14, V{1, 2, 3});
}

TEST(Print, print_it_pair)
{
    using M = map<int, int>;

    V v = {1, 2, 3};
    print(cbegin(v), cend(v));

    M m{{1, 2}, {3, 4}, {5, 6}};
    print(cbegin(m), cend(m));
}
