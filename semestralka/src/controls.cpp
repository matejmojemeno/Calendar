#include "controls.h"

void Controls::initNcurses()
{
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, true);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
}

void Controls::endNcurses()
{
    clear();
    endwin();
}