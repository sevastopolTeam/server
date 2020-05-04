add_library(english_validators STATIC
    validator_common_english.cpp
    validator_login.cpp
    validator_user.cpp
    validator_translation.cpp
    validator_word_category.cpp
)

target_link_libraries(english_validators PUBLIC
    english_collections
    validators
)
