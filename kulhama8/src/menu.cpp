#include "menu.h"

const std::array<const char *, 4> Menu::menuItems = {"Calendar", "Week calendar", "Events", "Exit"};
const std::array<const char *, 4> Menu::eventItems = {"Add event", "Import event", "Find event by name", "Back"};

void Menu::startMenu () 
{
    displayMenu(menuItems, 0);
    int c = getch(), pos = 0;

    while (c != 4) {
        if (c == '\n' && pos == 3)
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
        if (c == '\n' && pos == 3)
            break;
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
    if (pos == 0) {
        try {
            events.getEvent();}
        catch (std::invalid_argument &i) {
            exception(i);
        }
    }
    else if (pos == 1)
        try {
            events.getFileEvent();}
        catch (std::invalid_argument &i) {
            exception(i);
        }
    else if (pos == 2)
        try {
            events.manageEvent();}
        catch (std::invalid_argument &i) {
            exception(i);
        }
}

void Menu::exception(std::invalid_argument &i) const {
    clear();
    attron(ERROR);
    mvprintw(0, 0, i.what());
    printw(" Press a key to continue.");
    int c = getch();
    while (c == 410) {
        refresh();
        clear();
        mvprintw(0, 0, i.what());
        printw(" Press a key to continue.");

        c = getch();
    }
    attroff(ERROR);
}