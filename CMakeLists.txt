cmake_minimum_required(VERSION 4.0)
project(expression_templates_for_matrices)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(expression_templates
        src/main.cpp
)

target_include_directories(expression_templates PRIVATE include)

add_executable(tests
        tests/test_matrix.cpp
        tests/test_matrix_expressions.cpp
)

target_link_libraries(tests PRIVATE gtest_main gtest)
target_include_directories(tests PRIVATE include)