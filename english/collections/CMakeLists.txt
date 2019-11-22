include_directories(
  ../..
)

add_library(english_collections STATIC
  user_collection.cpp
)

target_link_libraries(english_collections PUBLIC
  mongo
  data_source
  english_records
  english_validators
  md5
)
