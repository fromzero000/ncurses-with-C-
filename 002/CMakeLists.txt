cmake_minimum_required(VERSION 3.30)
project(002)

set(CMAKE_CXX_STANDARD 17)

find_package(Curses REQUIRED)

add_executable(002 main.cpp
        tetris.cpp
        tetris.h
        ui.cpp
        ui.h)

target_link_libraries(002 PRIVATE ${NCURSES_LIBRARIES} ncursesw)
target_include_directories(002 PRIVATE ${NCURSES_INCLUDE_DIR})