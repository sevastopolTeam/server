#pragma once

#include <stack>

template<
    class T,
    class Container = std::deque<T>
>
using TStack = std::stack<T, Container>;

namespace NStack {
}