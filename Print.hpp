#pragma once

#include "Stringify.hpp"
#include "TypeTraits.hpp"

template <typename... Args>
void print(Args&&... args)
{
    using namespace std;
    cout << stringify(forward<Args>(args)...) << endl;
}

template <typename It, typename = std::enable_if_t<IsIterator<It>::value>>
void print(It begin, It end)
{
    print(std::make_pair(begin, end));
}
