add_library(english_handlers STATIC
    pagination.cpp
    common.cpp
    users.cpp
    ./admin/translations.cpp
    ./admin/sessions.cpp
)

target_link_libraries(english_handlers PUBLIC
    json
    httplib
    english_records
    english_collections
    english_validators
    data_source
    generic
)
