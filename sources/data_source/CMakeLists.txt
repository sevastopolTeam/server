add_library(data_source STATIC
    data_source.cpp
)

target_link_libraries(data_source PUBLIC
    mongo
    collections
    english_collections
    generic
)
