cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(11_Documenting LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(guess guess.cpp)

add_custom_target(
    update_translation
    COMMAND xgettext --keyword=GETTEXT guess.cpp -o ${CMAKE_BINARY_DIR}/guess.pot
    COMMAND msgmerge -U po/ru.po ${CMAKE_BINARY_DIR}/guess.pot
    COMMAND rm -f po/ru.po~
    DEPENDS guess.cpp
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set(locale_path ${CMAKE_BINARY_DIR}/po/ru/LC_MESSAGES)
file(MAKE_DIRECTORY ${locale_path})
add_custom_target(
    generate_mo
    COMMAND msgfmt -o ${locale_path}/guess.mo ${CMAKE_SOURCE_DIR}/po/ru.po
    DEPENDS update_translation
)
add_dependencies(guess generate_mo)

add_custom_target(
    run_english
    COMMAND ${CMAKE_BINARY_DIR}/guess
    DEPENDS guess update_translation
)

add_custom_target(
    run_english_roman
    COMMAND ${CMAKE_BINARY_DIR}/guess -r
    DEPENDS guess update_translation
)

add_custom_target(
    run_russian
    COMMAND LANGUAGE=ru_RU ${CMAKE_BINARY_DIR}/guess
    DEPENDS guess update_translation
)

add_custom_target(
    run_russian_roman
    COMMAND LANGUAGE=ru_RU ${CMAKE_BINARY_DIR}/guess -r
    DEPENDS guess update_translation
)

add_custom_target(
    generate_and_show_man
    COMMAND help2man --no-info --output=${CMAKE_BINARY_DIR}/guess.l ${CMAKE_BINARY_DIR}/guess
    COMMAND man ${CMAKE_BINARY_DIR}/guess.l
    DEPENDS guess
)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYGEN_INPUT ${CMAKE_SOURCE_DIR})
    configure_file(${CMAKE_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf)
    add_custom_target(
        doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.conf
        DEPENDS guess.cpp
    )
else(DOXYGEN_FOUND)
    message(WARNING "Doxygen not found. Documentation will not generate")
endif(DOXYGEN_FOUND)
