#pragma once

#include <queue>

template <typename T>
auto pop(std::queue<T>& queue)
{
    const auto front = queue.front();
    queue.pop();
    return front;
}
