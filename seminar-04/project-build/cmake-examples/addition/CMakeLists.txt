cmake_minimum_required(VERSION 3.0)

project(AdditionProject)

set(MAIN_SOURCE main.cpp)

include_directories(include)

add_executable(AdditionProject ${MAIN_SOURCE})
add_subdirectory(src)
target_link_libraries(AdditionProject AdditionLibrary)
