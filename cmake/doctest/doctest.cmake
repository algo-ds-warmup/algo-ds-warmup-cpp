if(TARGET doctest::doctest)
  return()
endif()

message(STATUS "Third-party (external): creating target 'doctest::doctest'")

include(FetchContent)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG v2.4.9 
  GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(doctest)
