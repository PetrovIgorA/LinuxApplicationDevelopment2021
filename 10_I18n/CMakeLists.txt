cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(10_I18n LANGUAGES C)

add_executable(guess guess.c)
target_compile_definitions(guess PUBLIC PACKAGE="guess")

add_custom_target(
    update_translation
    COMMAND xgettext --keyword=_ guess.c -o ${CMAKE_BINARY_DIR}/guess.pot
    COMMAND msgmerge -U po/ru.po ${CMAKE_BINARY_DIR}/guess.pot
    COMMAND rm -f po/ru.po~
    DEPENDS guess.c
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
    run_russian
    COMMAND LANGUAGE=ru_RU ${CMAKE_BINARY_DIR}/guess
    DEPENDS guess update_translation
)
