include_directories(
  ../..
)

add_subdirectory(admin)

add_library(english_handlers STATIC
  login.h
  registration.h
  routing.h
)
