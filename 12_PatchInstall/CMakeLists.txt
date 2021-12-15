cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(12_PatchInstall LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(guess guess.cpp)

add_custom_target(
    update_translation
    COMMAND xgettext --keyword=GETTEXT guess.cpp -o ${CMAKE_BINARY_DIR}/guess.pot
    COMMAND msgmerge -U po/ru.po ${CMAKE_BINARY_DIR}/guess.pot
    COMMAND rm -f po/ru.po~
    DEPENDS guess.cpp
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

set(CMAKE_INSTALL_PREFIX "/usr")

set(locale_path share/locale/ru/LC_MESSAGES)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${locale_path})
add_custom_target(
    generate_mo
    COMMAND msgfmt -o ${CMAKE_BINARY_DIR}/${locale_path}/guess.mo ${CMAKE_SOURCE_DIR}/po/ru.po
    DEPENDS update_translation
)
add_dependencies(guess generate_mo)

add_custom_target(
    run_english
    COMMAND ./guess
    DEPENDS guess update_translation
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_custom_target(
    run_english_roman
    COMMAND ./guess -r
    DEPENDS guess update_translation
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_custom_target(
    run_russian
    COMMAND LANGUAGE=ru_RU ./guess
    DEPENDS guess update_translation
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_custom_target(
    run_russian_roman
    COMMAND LANGUAGE=ru_RU ./guess -r
    DEPENDS guess update_translation
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

set(man_path share/man/man1)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${man_path})

add_custom_target(
    generate_man ALL
    COMMAND help2man --no-info --output=${CMAKE_BINARY_DIR}/${man_path}/guess.l ${CMAKE_BINARY_DIR}/bin/guess
    DEPENDS guess
)
add_custom_target(
    show_man
    COMMAND man ${CMAKE_BINARY_DIR}/${man_path}/guess.l
    DEPENDS generate_man
)

install(
    PROGRAMS ${CMAKE_BINARY_DIR}/bin/guess
    DESTINATION bin
)

install(
    FILES ${CMAKE_BINARY_DIR}/${locale_path}/guess.mo
    DESTINATION ${locale_path}
)

install(
    FILES ${CMAKE_BINARY_DIR}/${man_path}/guess.l
    DESTINATION ${man_path}
)

