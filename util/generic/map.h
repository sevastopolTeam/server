#pragma once

#include <map>

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
>
using TMap = std::map<Key, T, Compare, Allocator>;

template<
    class Key,
    class T,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<std::pair<const Key, T> >
>
using TMultiMap = std::multimap<Key, T, Compare, Allocator>;


namespace NMap {
}