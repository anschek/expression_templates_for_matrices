cmake_minimum_required(VERSION 3.20)
project(expression_templates_for_matrices)

cmake_policy(SET CMP0135 NEW)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(expression_templates src/main.cpp
        src/matrices/zero_matrix.cpp
        src/matrices/identity_matrix.cpp
)
target_include_directories(expression_templates PRIVATE include)

add_executable(tests
        tests/test_matrix.cpp
        tests/test_matrix_expressions.cpp
        tests/test_infrastructure.cpp
)
target_link_libraries(tests PRIVATE gtest_main gtest)
target_include_directories(tests PRIVATE include)

add_test(NAME matrix_tests COMMAND tests)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})