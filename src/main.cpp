#include "game.h"
#include "snake.h"
#include <chrono>
#include <thread>
#include <ncurses.h>

int g_high_score {};

bool start()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    timeout(0);

    Game my_game{};

    while (true) // game loop
    {
        my_game.check_input();
        my_game.get_snake().go_dir();
        my_game.check_bounds();

        if (!my_game.get_snake().check_alive())
            break;

        clear();
        my_game.print_board();
        refresh();

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    //clear();
    //my_game.print_board();

    int cur_score = my_game.get_snake().get_length();
    g_high_score = std::max(g_high_score, cur_score);

    mvprintw(12, 0, "GAME OVER");
    mvprintw(13, 0, "High Score: %d", g_high_score);
    mvprintw(14, 0, "PLAY AGAIN? (y/n)");

    refresh();

    int ch;
    while (true)
    {
        ch = getch();
        if (ch == 'y' || ch == 'n')
            break;
    }

    if (ch == 'n')
    {
        endwin();
        return false;;
    }

    clear();
    refresh();
    return true;
}

int main()
{
    bool keep_playing = true;
    while (keep_playing)
    {
        keep_playing = start();
    }
    return 0;
}