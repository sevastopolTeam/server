cmake_minimum_required(VERSION 3.1)
project(server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

include_directories(
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/contrib/mongo-c-driver/libbson/src
  ${PROJECT_SOURCE_DIR}/contrib/mongo-c-driver/libmongoc/src
)

add_subdirectory(contrib)
add_subdirectory(library)
add_subdirectory(sources)
add_subdirectory(util)

add_subdirectory(english)

add_executable(server
  main.cpp
)

target_link_libraries(server PUBLIC
  application
)
