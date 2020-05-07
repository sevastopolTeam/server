add_library(english_validators STATIC
    validator_common_english.cpp
    validator_login.cpp
    validator_user.cpp
    ./admin/validator_translation.cpp
    ./admin/validator_admin_user.cpp
    ./admin/validator_word_category.cpp
)

target_link_libraries(english_validators PUBLIC
    english_collections
    validators
)
