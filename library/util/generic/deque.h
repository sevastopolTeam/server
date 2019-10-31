#pragma once

#include <deque>

template<
    class T,
    class Allocator = std::allocator<T>
>
using TDeque = std::deque<T, Allocator>;

namespace NDeque {

};