include_directories(
  ../..
)

add_library(english_validators STATIC
  validator_common_english.cpp
  validator_user.cpp
)
