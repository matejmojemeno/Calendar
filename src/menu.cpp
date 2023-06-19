#include "menu.h"

const std::vector<const char *> Menu::menuItems = {"Calendar", "Events", "Exit"};
const std::vector<const char *> Menu::eventItems = {"Add event", "Import event", "Find event by name", "Find event by place", "Back"};

int Menu::menu(const std::vector<const char *> &menu) const
{
    displayMenu(menu, 0);
    int c = getch(), pos = 0;

    while (c != 4)
    {
        if (c == '\n')
            return pos;

        updatePos(c, pos, menu.size());
        refresh();
        displayMenu(menu, pos);

        c = getch();
    }
    
    return '\n';
}

int Menu::mainMenu() const
{
    return menu(menuItems);
}

int Menu::eventMenu() const
{
    return menu(eventItems);
}

void Menu::displayMenu(const std::vector<const char *> menu, int pos) const
{
    clear();
    int max = static_cast<int>(menu.size());
    for (int i = 0; i < max; i++)
    {
        if (i == pos)
            attron(HIGHLIGHT);
        mvprintw(i, 0, menu[i]);
        attroff(HIGHLIGHT);
    }
}

void Menu::updatePos(int c, int &pos, size_t menuSize) const
{
    if (c == KEY_UP)
        pos--;
    else if (c == KEY_DOWN)
        pos++;
    pos = (pos + static_cast<int>(menuSize)) % static_cast<int>(menuSize);
}