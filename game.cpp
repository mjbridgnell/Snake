
#include "game.h"
#include <ncurses.h>
#include <random>

using namespace std;

void Game::print_board()
{
    auto &cur_snake = m_snake.get_body();

    for (int i = 0; i < m_board.size(); i++)
    {
        for (int j = 0; j < m_board[i].size(); j++)
        {
            char cell = '.';

            for (int k = 0; k < cur_snake.size(); k++)
            {
                if (j == cur_snake[k].first && i == cur_snake[k].second)
                {
                    if (k == 0)
                        cell = 'X';
                    else
                        cell = 'O';

                    break;
                }
            }

            if (m_apple.get_x() == j && m_apple.get_y() == i)
                cell = 'A';

            mvprintw(i, j * 2, "%c", cell);
        }
    }
}

bool Game::check_input()
{
    int ch;
    int last_valid = ERR;

    while ((ch = getch()) != ERR)
    {
        last_valid = ch;
    }

    if (last_valid != ERR)
    {
        switch (last_valid)
        {
        case 'd':
            m_snake.set_direction('r');
            break;
        case 'a':
            m_snake.set_direction('l');
            break;
        case 'w':
            m_snake.set_direction('u');
            break;
        case 's':
            m_snake.set_direction('d');
            break;
        case 'i':
            m_snake.increase_snake();
            break;
        }
    }

    return m_snake.check_alive();
}

void Game::check_bounds()
{
    // Check boundary collision
    auto head = m_snake.get_body().front();
    if (head.first > 9 || head.second > 9 || head.first < 0 || head.second < 0)
        m_snake.set_alive(false);

    // Check snake self collision
    auto snake = m_snake.get_body();
    for (int i = 1; i < snake.size(); i++)
    {
        if (head.first == snake[i].first && head.second == snake[i].second)
            m_snake.set_alive(false);
    }

    if (head.first == m_apple.get_x() && head.second == m_apple.get_y())
    {
        m_snake.increase_snake();
        spawn_apple();
    }
}

void Game::spawn_apple()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, 9);

    int random_x {};
    int random_y {};
    bool test = true;
    auto snake = m_snake.get_body();

    while (test)
    {
        random_x = distr(gen);
        random_y = distr(gen);
        test = false;
        for (int i = 0; i < snake.size(); i++)
        {
            if (random_x == snake[i].first && random_y == snake[i].second)
            {
                test = true;
            }
        }
    }

    m_apple.set_x(random_x);
    m_apple.set_y(random_y);
}