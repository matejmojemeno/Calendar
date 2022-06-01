#include "controls.h"

void Controls::initNcurses() const
{
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, true);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    curs_set(0);
}

void Controls::endNcurses() const
{
    clear();
    endwin();
}

std::string Controls::getString() const
{
    echo();

    char string[42];
    getnstr(string, 42);

    return convertString(string);
}

std::string Controls::convertString(char string[]) const {
    std::string newString;
    int pos = 0;

    while (string[pos]) 
        newString.push_back(string[pos++]);
    
    return newString;
}