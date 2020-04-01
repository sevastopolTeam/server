include_directories(
  ../..
)

add_library(english_records STATIC
  session_record.cpp
  user_record.cpp
  translation_record.cpp
)
