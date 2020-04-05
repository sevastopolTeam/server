include_directories(
  ../..
)

add_subdirectory(admin)

add_library(english_handlers STATIC
  routing.h
  users.h
)
