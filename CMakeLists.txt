cmake_minimum_required(VERSION 3.22)
project(terminal-utils C)

set(CMAKE_C_STANDARD 17)

add_executable(terminal-utils main.c pharm/pharm.c pharm/pharm.h tetris/tetris.c tetris/tetris.h)

target_link_libraries(${PROJECT_NAME} ncurses)
