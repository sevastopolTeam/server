add_library(collections STATIC
    base.cpp
    collection.cpp
)

target_link_libraries(collections PUBLIC
    mongo
    records
    json
    generic
)
