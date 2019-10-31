#pragma once

#include <vector>

template <class T, class A = std::allocator<T>>
using TVector = std::vector<T, A>;

namespace NVector {
};