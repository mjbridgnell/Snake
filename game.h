#include <vector>
#include <iostream>
#include "snake.h"

#ifndef GAME_H
#define GAME_H

#define BOARD_SIZE 10

class Game
{
    private:
        std::vector<std::vector<int>> m_board;
        Snake m_snake;

    public:
        Game() 
        : m_board {BOARD_SIZE, std::vector<int>(BOARD_SIZE)}
        , m_snake {Snake()}
        {}

        std::vector<std::vector<int>>& get_board() { return m_board; }
        Snake& get_snake() { return m_snake; }
        void print_board();
        bool check_input();
        void check_bounds();
};

#endif