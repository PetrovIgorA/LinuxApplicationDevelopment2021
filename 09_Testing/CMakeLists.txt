cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(09_Testing LANGUAGES CXX)

option(ENABLE_COVERAGE OFF)

if(ENABLE_COVERAGE)
    set(CMAKE_BUILD_TYPE Debug)
    include(cmake/CodeCoverage.cmake)
    append_coverage_compiler_flags()
endif()

add_library(buf SHARED buf.cpp)
target_include_directories(buf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(CTest)
enable_testing()
find_package(GTest REQUIRED)

add_executable(buf_tests test.cpp)
target_link_libraries(buf_tests buf ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)
target_include_directories(buf_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_test(NAME    buffer_tests 
         COMMAND buf_tests
)

add_custom_target(
    run_tests
    COMMAND buf_tests
    DEPENDS buf_tests
)

if(ENABLE_COVERAGE)
    setup_target_for_coverage_lcov(
            NAME coverage                 
            EXECUTABLE ctest -j ${n_cores}
            DEPENDENCIES buf_tests
    )
endif()
