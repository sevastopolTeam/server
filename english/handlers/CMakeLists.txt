include_directories(
  ../..
)

add_subdirectory(admin)

add_library(english_handlers STATIC
  pagination.h
  common.h
  users.h
)
