add_library(english_collections STATIC
    session_collection.cpp
    user_collection.cpp
    translation_collection.cpp
    word_category_collection.cpp
    translation_to_category_collection.cpp
    common_set.cpp
)

target_link_libraries(english_collections PUBLIC
    collections
    english_records
    generic
)
