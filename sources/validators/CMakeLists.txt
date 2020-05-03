include_directories(
    ../..
)

add_library(validators STATIC
    validator.cpp
)

target_link_libraries(validators PUBLIC
    json
    generic
)
