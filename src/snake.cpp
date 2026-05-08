#include "snake.h"

using namespace std;

void Snake::go_right()
{
    auto head = m_body.front();

    int new_x = head.first + 1;
    int new_y = head.second;

    m_body.insert(m_body.begin(), {new_x, new_y});

    if (!m_grow)
    {
        m_body.pop_back(); // normal move
    }
    else
    {
        m_grow = false; // grow: skip removing tail once
    }

    m_direction = 'd';
}

void Snake::go_left()
{
    auto head = m_body.front();

    int new_x = head.first - 1;
    int new_y = head.second;

    m_body.insert(m_body.begin(), {new_x, new_y});

    if (!m_grow)
    {
        m_body.pop_back();
    }
    else
    {
        m_grow = false;
    }

    m_direction = 'a';
}

void Snake::go_up()
{
    auto head = m_body.front();

    int new_x = head.first;
    int new_y = head.second - 1;

    m_body.insert(m_body.begin(), {new_x, new_y});

    if (!m_grow)
    {
        m_body.pop_back();
    }
    else
    {
        m_grow = false; 
    }

    m_direction = 'w';
}

void Snake::go_down()
{
    auto head = m_body.front();

    int new_x = head.first;
    int new_y = head.second + 1;

    m_body.insert(m_body.begin(), {new_x, new_y});

    if (!m_grow)
    {
        m_body.pop_back();
    }
    else
    {
        m_grow = false;
    }

    m_direction = 's';
}

void Snake::go_dir()
{
    switch (m_direction)
    {
    case 'd':
        go_right();
        break;
    case 'a':
        go_left();
        break;
    case 'w':
        go_up();
        break;
    case 's':
        go_down();
        break;
    default:
        break;
    }
}

void Snake::set_direction(const char dir)
{
    if (m_direction == 'd' && dir == 'a') // Cannot switch directions
        return;
    if (m_direction == 'a' && dir == 'd')
        return;
    if (m_direction == 'w' && dir == 's')
        return;
    if (m_direction == 's' && dir == 'w')
        return;

    m_direction = dir;
}
