cmake_minimum_required(VERSION 3.10)

project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(SnakeGame
    src/main.cpp
    src/game.cpp
    src/snake.cpp
)

target_include_directories(SnakeGame PRIVATE include)

target_link_libraries(SnakeGame PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

target_compile_options(SnakeGame PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)