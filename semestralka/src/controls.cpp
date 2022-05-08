#include "controls.h"

//void Controls::initNcurses()
//{
//    initscr();
//    clear();
//    noecho();
//    cbreak();
//    keypad(stdscr, true);
//}

int Controls::readKey()
{
    return getch();
}