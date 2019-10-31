cmake_minimum_required(VERSION 3.1)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/contrib/mongo-c-driver/src/libbson/src
  ${PROJECT_SOURCE_DIR}/contrib/mongo-c-driver/src/libmongoc/src
  ${PROJECT_SOURCE_DIR}/contrib/httplib
  ${PROJECT_SOURCE_DIR}/contrib/json
)

add_subdirectory(contrib)
add_subdirectory(library)
add_subdirectory(util)

add_executable(server
  main.cpp
  application.cpp
)

target_link_libraries(server
  bson_static
  mongoc_static
  mongo
  httplib
  json
)
