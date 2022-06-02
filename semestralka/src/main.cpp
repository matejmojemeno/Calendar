#include <iostream>
#include <ncurses.h>

//#include "stringParser.h"
//#include "menu.h"
//#include "displayMonth.h"
#include "eventWrapper.h"
//#include "controls.h"

using namespace std;

int main()
{
    Controls c; 
    EventWrapper e;
    c.initNcurses();

    try { e.getEvent(); }
    catch (std::invalid_argument &ia) {
        clear();
        attron(COLOR_PAIR(3));
        printw(ia.what());
        attroff(COLOR_PAIR(3));
    }

    getch();

    c.endNcurses();

    return 0;
}