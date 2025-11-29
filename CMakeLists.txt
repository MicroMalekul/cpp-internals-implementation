cmake_minimum_required(VERSION 3.14)
project(MyCppTasks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_subdirectory(cow-vector)
add_subdirectory(itertools)
add_subdirectory(lru-cache)
add_subdirectory(vector)