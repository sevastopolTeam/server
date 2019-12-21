#pragma once

#include <unordered_map>

template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator< std::pair<const Key, T> >
>
using THashMap = std::unordered_map<Key, T, Hash, KeyEqual, Allocator>;

template<
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator< std::pair<const Key, T> >
>
using TMultiHashMap = std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>;


namespace NHashMap {
}