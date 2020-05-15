add_library(english_records STATIC
    session_record.cpp
    user_record.cpp
    translation_record.cpp
    word_category_record.cpp
    translation_to_category_record.cpp
)

target_link_libraries(english_records PUBLIC
    generic
)
