include_directories(
  ../..
)

add_library(records STATIC
    base_record.cpp
    record.cpp
)

target_link_libraries(records PUBLIC
    json
    generic
)