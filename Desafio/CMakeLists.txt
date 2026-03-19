cmake_minimum_required(VERSION 3.19)
project(Desafio LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core LinguistTools)

qt_standard_project_setup()

qt_add_executable(Desafio
    main.cpp
    tablero.h
    tablero.cpp
    pieza.h
    pieza.cpp
    .gitignore
)

qt_add_translations(
    TARGETS Desafio
    TS_FILES Desafio_es_ES.ts
)

target_link_libraries(Desafio
    PRIVATE
        Qt::Core
)

install(TARGETS Desafio
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)