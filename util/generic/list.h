#pragma once

#include <list>

template <class T, class A = std::allocator<T>>
using TList = std::list<T, A>;

namespace NList {
}