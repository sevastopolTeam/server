#pragma once

#include <unordered_set>

template<
    class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
>
using THashSet = std::unordered_set<Key, Hash, KeyEqual, Allocator>;

template<
    class Key,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<Key>
>
using TMultiHashSet = std::unordered_multiset<Key, Hash, KeyEqual, Allocator>;

namespace NHashSet {

};