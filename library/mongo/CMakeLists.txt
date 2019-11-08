include_directories(
  ../..
  ../../contrib/mongo-c-driver/libbson/src
  ../../contrib/mongo-c-driver/libmongoc/src
)

add_library(mongo STATIC wrappers.cpp)

target_link_libraries(mongo PUBLIC
  bson_static
  mongoc_static
  json
  generic
)
