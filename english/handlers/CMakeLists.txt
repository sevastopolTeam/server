include_directories(
  ../..
)

add_subdirectory(admin)

add_library(english_handlers STATIC
  pagination.h
  routing.h
  users.h
)
