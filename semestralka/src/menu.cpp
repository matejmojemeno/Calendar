#include "menu.h"

const std::array<const char *, 4> Menu::menuItems = {"Calendar", "Week calendar", "Add Event", "Exit"};
const std::array<const char *, 4> Menu::eventItems = {"Add event", "Import event", "Manage events", "Find event by name"};

void Menu::startMenu () 
{
    displayMenu(menuItems, 0);
    int c = getch(), pos = 0;

    while (c != 4) {
        if (c == 10 && pos == 3)
            break;
        if (c == '\n')
            callFunc(pos);
    
        updatePos(c, pos);
        refresh();
        displayMenu(menuItems, pos);
        
        c = getch();
    }
} 

void Menu::eventMenu()
{
    displayMenu(eventItems, 0);
    int c = getch(), pos = 0;

    while (c != 4) {
        if (c == '\n')
            callEventFunc(pos);

        updatePos(c, pos);
        refresh();
        
        displayMenu(eventItems, pos);

        c = getch();
    }
}

void Menu::displayMenu(const std::array<const char *, 4> menu, int pos) const
{
    clear();
    int max = (int) menu.size();
    for (int i = 0; i < max; i++) {
        if (i == pos)
            attron(HIGHLIGHT);
        mvprintw(i, 0, menu[i]);
        attroff(HIGHLIGHT);
    }
}

void Menu::updatePos(int c, int &pos) 
{
    if (c == KEY_UP)
        pos--;
    else if (c == KEY_DOWN)
        pos++;
    pos = (pos + 4) % 4;
}

void Menu::callFunc(int pos) {
    Time time;
    if (pos == 0)
        d.controlDisplay(time, events.storage);
    else if (pos == 1)
        w.controlDisplay(time, events.storage);
    else if (pos == 2)
        eventMenu();
}

void Menu::callEventFunc(int pos) {
    if (pos == 0)
        events.getEvent();
    else if (pos == 1)
        events.getFileEvent();
    else if (pos == 2)
        events.findName();
}