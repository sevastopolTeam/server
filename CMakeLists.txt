cmake_minimum_required(VERSION 3.1)
project(server)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/contrib/mongo-c-driver/libbson/src
  ${PROJECT_SOURCE_DIR}/contrib/mongo-c-driver/libmongoc/src
)

add_subdirectory(contrib)
add_subdirectory(library)
add_subdirectory(sources)
add_subdirectory(util)

add_executable(server
  main.cpp
)

target_link_libraries(server PUBLIC
  application
)
