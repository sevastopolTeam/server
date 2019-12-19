#pragma once

#include <set>

template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
>
using TSet = std::set<Key, Compare, Allocator>;

template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
>
using TMultiSet = std::multiset<Key, Compare, Allocator>;

namespace NSet {
}