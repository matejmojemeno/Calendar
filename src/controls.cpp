#include "controls.h"

void Controls::initNcurses() const
{
    initscr();
    clear();
    cbreak();
    stopCursor();
    keypad(stdscr, true);
    initColors();
}

void Controls::initColors() const
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
}

void Controls::endNcurses() const
{
    clear();
    endwin();
}

void Controls::showCursor() const {
    echo();
    curs_set(1);
}

void Controls::stopCursor() const {
    noecho();
    curs_set(0);
}