#include "calendar.h"

void Calendar::startApplication() const
{
    Controls c;
    c.initNcurses();
}

void Calendar::runApplication() const
{
    Menu menu;
    int menuItem = menu.mainMenu();

    if (menuItem == '\n')
        return;
}