#include <vector>
#include <iostream>
#include <random>
#include "snake.h"
#include "apple.h"

#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 10

class Game
{
    private:
        std::vector<std::vector<int>> m_board;
        Snake m_snake;
        Apple m_apple;
        std::mt19937 m_gen { std::random_device{}() };
        std::vector<std::vector<char>> m_render;

    public:
        Game() 
        : m_board { BOARD_SIZE, std::vector<int>(BOARD_SIZE) }
        , m_snake { Snake() }
        , m_render { BOARD_SIZE, std::vector<char>(BOARD_SIZE) }
        {
            spawn_apple();
        }

        std::vector<std::vector<int>>& get_board() { return m_board; }
        Snake& get_snake() { return m_snake; }
        void print_board();
        bool check_input();
        void check_bounds();
        void spawn_apple();
};

#endif