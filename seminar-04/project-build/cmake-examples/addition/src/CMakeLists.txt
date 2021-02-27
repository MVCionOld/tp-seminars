cmake_minimum_required(VERSION 3.0)

project(AdditionLibrary)

set(SOURCE_LIB addition.cpp)

add_library(AdditionLibrary SHARED ${SOURCE_LIB})
