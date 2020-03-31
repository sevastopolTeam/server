include_directories(
  ../..
)

add_library(english_collections STATIC
  session_collection.cpp
  user_collection.cpp
  word_collection.cpp
  main.cpp
)

target_link_libraries(english_collections PUBLIC
  mongo
  data_source
  english_records
  english_validators
  md5
)
