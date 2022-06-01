#include <iostream>
#include "controls.h"
#include "menu.h"
#include "displayMonth.h"

int main()
{
    Controls a;
    a.initNcurses();
    Menu b; 
    b.startMenu();
    //if (b.pos == 0);

    //while(true);

    DisplayMonth c;
    c.controlDisplay();

    clear();
    printw(a.getString().c_str());
    getch();

    endwin();
}
