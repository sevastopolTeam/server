include_directories(
  ../..
)

add_library(collections STATIC
    base.cpp
    collection.cpp
)

target_link_libraries(collections PUBLIC
  records
)
