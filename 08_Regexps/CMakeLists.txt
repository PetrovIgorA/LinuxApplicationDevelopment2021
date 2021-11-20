cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(08_Regexps LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(esub esub.cpp)

message(STATUS "Use single quotes ('some string') in esub arguments for avoid problem with \\")

add_custom_target(
    tests
    COMMAND ${CMAKE_SOURCE_DIR}/tests/tests.sh ${CMAKE_BINARY_DIR}
    DEPENDS esub
)
