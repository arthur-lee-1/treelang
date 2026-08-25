cmake_minimum_required(VERSION 3.16)

project(treelang VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(TREELANG_ENABLE_TESTS "Compile treelang tests" ON)

add_subdirectory(src)

if(TREELANG_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
