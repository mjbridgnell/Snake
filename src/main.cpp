#include "game.h"
#include "snake.h"
#include <chrono>
#include <thread>
#include <optional>
#include <SFML/Graphics.hpp>

int g_high_score{};

bool play_again(sf::RenderWindow& window, const sf::Font font)
{
    sf::Text text;
    text.setFont(font);
    text.setString("GAME OVER\n"
        "Score: " + std::to_string(g_high_score) +
        "\nPlay Again? (y/n)" 
    );
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(
        bounds.left + bounds.width / 2.f,
        bounds.top + bounds.height / 2.f
    );

    text.setPosition(
        window.getSize().x / 2.f,
        window.getSize().y / 2.f
    );
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::N)
                {
                    return false;
                }
                if (event.key.code == sf::Keyboard::Y)
                {
                    return true;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(text);
        window.display();
    }
    return true;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({200, 200}), "MAX SNAKE :D");
    sf::Font font;

    if (!font.loadFromFile("src/arial.ttf"))
    {
        return 1;
    }

    while (window.isOpen())
    {
        Game my_game;

        while (true) // game loop
        {
            sf::Event event;

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::White);

            my_game.check_input();
            my_game.get_snake().go_dir();
            my_game.check_bounds();

            if (!my_game.get_snake().check_alive())
                break;

            my_game.print_board(window);

            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }

        int cur_score = my_game.get_snake().get_length();
        g_high_score = std::max(g_high_score, cur_score);

        window.clear(sf::Color::White);

        if (!play_again(window, font))
            return 0;
    }

    return 0;
}
