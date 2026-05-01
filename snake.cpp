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

    m_direction = 'r';
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

    m_direction = 'l';
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

    m_direction = 'u';
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

    m_direction = 'd';
}

void Snake::go_dir()
{
    switch (m_direction)
    {
    case 'r':
        go_right();
        break;
    case 'l':
        go_left();
        break;
    case 'u':
        go_up();
        break;
    case 'd':
        go_down();
        break;
    default:
        break;
    }
}

void Snake::set_direction(char dir)
{
    if (m_direction == 'r' && dir == 'l') // Cannot switch directions
        return;
    if (m_direction == 'l' && dir == 'r')
        return;
    if (m_direction == 'u' && dir == 'd')
        return;
    if (m_direction == 'd' && dir == 'u')
        return;

    m_direction = dir;
}
