cmake_minimum_required(VERSION 3.30)
project(004)

set(CMAKE_CXX_STANDARD 20)

find_package(Curses REQUIRED)
#매크로 생성
#add_compile_definitions(NDEBUG)

add_executable(004 main.cpp
        tetris.cpp
        ui.cpp)

target_link_libraries(004 PRIVATE ${NCURSES_LIBRARIES} ncursesw)
target_include_directories(004 PRIVATE ${NCURSES_INCLUDE_DIR})
