cmake_minimum_required(VERSION 3.10)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)

add_executable(SnakeGame
    src/main.cpp
    src/game.cpp
    src/snake.cpp
)

target_include_directories(SnakeGame PRIVATE include)

find_package(Curses REQUIRED)
target_link_libraries(SnakeGame ${CURSES_LIBRARIES})

target_compile_options(SnakeGame PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)