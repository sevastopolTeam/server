#pragma once

#include <queue>

template<
    class T,
    class Container = std::deque<T>
>
using TQueue = std::queue<T, Container>;

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
>
using TPriorityQueue = std::priority_queue<T, Container, Compare>;

namespace NQueue {
}