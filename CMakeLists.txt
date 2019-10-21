cmake_minimum_required(VERSION 3.1)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/contrib/httplib
  ${PROJECT_SOURCE_DIR}/contrib/mongo-c-driver/src/libbson/src
  ${PROJECT_SOURCE_DIR}/contrib/mongo-c-driver/src/libmongoc/src
)

add_subdirectory(
  contrib
)

add_executable(server
  application.cpp
  main.cpp
)

target_link_libraries(server
  mongoc_static
  bson_static
)
