#include "menu.h"

const std::array<const char *, 4> Menu::menuItems = {"Calendar", "Add Event", "Manual", "Exit"};

void Menu::startMenu () 
{
    displayMenu();
    int c = getch();

    while (c != 10) {
        updatePos(c);
        refresh();
        displayMenu();

        c = getch();
    }
} 

void Menu::displayMenu() const
{
    for (int i = 0; i < 4; i++) {
        if (i == pos)
            attron(COLOR_PAIR(1));
        mvprintw(i, 0, menuItems[i]);
        attroff(COLOR_PAIR(1));
    }
}

void Menu::updatePos(int c) 
{
    if (c == KEY_UP)
        pos--;
    else if (c == KEY_DOWN)
        pos++;
    pos = (pos + 4) % 4;
}