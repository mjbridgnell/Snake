#include <vector>
#include <iostream>

#ifndef SNAKE_H
#define SNAKE_H

class Snake
{
private:
    std::vector<std::pair<int, int>> m_body;
    bool m_alive;
    bool m_grow;
    char m_direction;
    char m_next_direction;

public:
    Snake()
    {
        m_body.push_back({
            // Starting position (5, 5)
            5,
            5,
        });
        m_alive = true;
        m_grow = false;
        m_direction = 'd';
        m_next_direction = 'd';
    }

    void go_right();
    void go_left();
    void go_up();
    void go_down();
    void go_dir();
    void set_next_direction(const char);

    void set_alive(bool alive) { m_alive = alive; }
    void apply_direction() { m_direction = m_next_direction; }
    bool check_alive() { return m_alive; }
    std::vector<std::pair<int, int>> &get_body() { return m_body; }
    void increase_snake() { m_grow = true; }
    int get_length() { return m_body.size(); }
};

#endif