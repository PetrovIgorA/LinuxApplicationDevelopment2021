cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(07_Environmental LANGUAGES C)

find_library(RHASH rhash REQUIRED)

option(USE_READLINE "Use readline instead of getline" OFF)

add_executable(rhasher rhasher.c)
target_link_libraries(rhasher ${RHASH})

set(DEL_FIRST_LINE 0)
if (USE_READLINE)
    set(DEL_FIRST_LINE 1)
    find_library(READLINE readline REQUIRED)
    if (NOT READLINE)
        message(FATAL_ERROR "No readline library")
    else()
        target_link_libraries(rhasher ${READLINE})
        target_compile_definitions(rhasher PRIVATE HAVE_READLINE=1)
    endif()
endif()

add_custom_target(
    tests
    COMMAND ${CMAKE_SOURCE_DIR}/tests/tests.sh ${CMAKE_BINARY_DIR} ${DEL_FIRST_LINE}
    DEPENDS rhasher
)

