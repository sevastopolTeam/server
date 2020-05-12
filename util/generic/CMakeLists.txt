add_library(generic STATIC
    algorithm.cpp
    ctype.cpp
    deque.cpp
    hash_functions.cpp
    hashmap.cpp
    hashset.cpp
    holder.cpp
    iostream.cpp
    list.cpp
    map.cpp
    maybe.cpp
    noncopyable.cpp
    queue.cpp
    set.cpp
    stack.cpp
    string.cpp
    vector.cpp
)

target_link_libraries(generic PUBLIC
    md5
)
