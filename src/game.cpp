
#include "game.h"
#include <ncurses.h>
#include <random>

void Game::print_board()
{
    for (auto &row : m_render)
        std::fill(row.begin(), row.end(), '.');

    auto &snake = m_snake.get_body();

    for (std::size_t i = 0; i < snake.size(); i++)
    {
        int x = snake[i].first;
        int y = snake[i].second;

        m_render[y][x] = (i == 0) ? 'X' : 'O';
    }

    m_render[m_apple.get_y()][m_apple.get_x()] = 'A';

    for (std::size_t i = 0; i < m_render.size(); i++)
    {
        for (std::size_t j = 0; j < m_render[i].size(); j++)
        {
            mvprintw(static_cast<int>(i), static_cast<int>(j) * 2, "%c", m_render[i][j]);
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
            m_snake.set_direction('d');
            break;
        case 'a':
            m_snake.set_direction('a');
            break;
        case 'w':
            m_snake.set_direction('w');
            break;
        case 's':
            m_snake.set_direction('s');
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
    for (std::size_t i = 1; i < snake.size(); i++)
    {
        if (head.first == snake[i].first && head.second == snake[i].second)
            m_snake.set_alive(false);
    }

    // Check apple collision
    if (head.first == m_apple.get_x() && head.second == m_apple.get_y())
    {
        m_snake.increase_snake();
        spawn_apple();
    }
}

// Spawns apple randomly, checks to make sure it does not spawn on top of snake
void Game::spawn_apple()
{
    std::uniform_int_distribution<> distr(0, 9);

    int random_x {};
    int random_y {};
    bool test = true;
    auto snake = m_snake.get_body();

    while (test)
    {
        random_x = distr(m_gen);
        random_y = distr(m_gen);
        test = false;
        for (std::size_t i = 0; i < snake.size(); i++)
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
