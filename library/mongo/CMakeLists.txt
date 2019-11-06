include_directories(
  ../..
  ../../contrib/mongo-c-driver/src/libbson/src
  ../../contrib/mongo-c-driver/src/libmongoc/src
)

add_library(mongo STATIC wrappers.cpp)

target_link_libraries(mongo PUBLIC
  bson_static
  mongoc_static
  json
  generic
)
