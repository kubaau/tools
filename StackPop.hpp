#pragma once

#include <stack>

template <typename T>
auto pop(std::stack<T>& stack)
{
    const auto top = stack.top();
    stack.pop();
    return top;
}
