
#include "game.h"
#include <random>
#include <chrono>
#include <thread>

void Game::print_board(sf::RenderWindow &window)
{
    auto &snake = m_snake.get_body();

    window.clear(sf::Color::White);

    for (std::size_t i = 0; i < snake.size(); i++)
    {
        int x = snake[i].first;
        int y = snake[i].second;

        sf::RectangleShape rectangle({20.f, 20.f});
        rectangle.setPosition({20.f * static_cast<float>(x), 20.f * static_cast<float>(y)});
        if (i == 0)
        {
            rectangle.setFillColor(sf::Color(100, 200, 50));
        }
        else
        {
            rectangle.setFillColor(sf::Color(100, 250, 50));
        }
        window.draw(rectangle);
    }

    int x = m_apple.get_x();
    int y = m_apple.get_y();
    sf::RectangleShape rectangle({20.f, 20.f});
    rectangle.setPosition({20.f * static_cast<float>(x), 20.f * static_cast<float>(y)});
    rectangle.setFillColor(sf::Color(255, 0, 0));
    window.draw(rectangle);
}

bool Game::check_input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        m_snake.set_next_direction('w');
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        m_snake.set_next_direction('a');
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        m_snake.set_next_direction('s');
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        m_snake.set_next_direction('d');
    }
    /*
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
    {
        std::this_thread::sleep_for(std::chrono::seconds(100));
    }
    */

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

    int random_x{};
    int random_y{};
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
