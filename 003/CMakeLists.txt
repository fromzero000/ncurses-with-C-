cmake_minimum_required(VERSION 3.30)
project(003)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)

add_executable(003 main.cpp
        tetris.cpp
        tetris.h
        ui.cpp
        ui.h)

target_link_libraries(003 PRIVATE ${NCURSES_LIBRARIES} ncursesw)
target_include_directories(003 PRIVATE ${NCURSES_INCLUDE_DIR})