cmake_minimum_required(VERSION 4.0)
project(expression_templates_for_matrices)

set(CMAKE_CXX_STANDARD 20)

add_executable(expression_templates src/main.cpp)

target_include_directories(expression_templates PRIVATE include)